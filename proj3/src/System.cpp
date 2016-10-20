#include "Process.cpp"
#include "Processor.cpp"
#include "MemoryManager.cpp"
#include <vector>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
	
class System {
	public:
		System(int pagesize, int mainframes, int virpages, int procframelimit, int timequan, int numproc)
			: memman(pagesize, mainframes, virpages, procframelimit), mproc(numproc, timequan), ticks(0) {}
		
		void init() {
			memman._init();
			//memman.testinit();
		}		
	
		void run() {
			std::string strstate;
			while(true) {
				ticks++;
				mproc.tick();
				memman.tick();

				for(Process & p : processpool) { 
					// probably not exactly how i'd want to do this if i had a lot of processes, but luckily for me i don't
					if (ticks == p.arriveat && p.memreq > memman.checkAvail()) {
						holdq.push(&p);
					} else if (ticks == p.arriveat){
						if (memman.insert(&p) != -1) {
							std::cout << "Inserting " << p.name << " to readyq" << std::endl;
							readyq.push(&p);
							memman.setProcess(p.name, true);
						} else {
							pfwait.push_back(&p);
						}
					}		
				}

				std::vector<Process*> running = mproc.runcheck();
				//handle running processes
				for(Process *p : running) {
					std::cout << "Checking " << p->name << "..." << std::endl;
					if (p->done) {
						p->finish();
					} else if (p->needio) {
						iowait.push_back(p);
					} else if (p->needmem) {
						pfwait.push_back(p);
					} else if (p->ready) {
						readyq.push(p);
					}
				}

				// check if page faults can be accessed
				std::cout << (pfwait.empty() ? "no pfwait" : "pfwaits") << std::endl;
				if (!pfwait.empty()) {
					for(Process *pr : pfwait) {
						if(pr != nullptr && memman.request(pr->nextaddr) > 0) {
							pr = nullptr; // remove process from pfwait
						}
					}
				}

				// check for iowait
				std::cout << (iowait.empty() ? "no io" : "io waits") << std::endl;
				if (!iowait.empty()){
					for(Process *pr : iowait) {
						if(pr->iotick() == 0) {
							pr = nullptr; // remove process from iowait
						}
					}
				}
				
				// check holdq 
				std::cout << (holdq.empty() ? "no holds" : "holds") << std::endl;
				if (!holdq.empty()) {
					Process *pr = holdq.front();	
					if (pr->memreq < memman.checkAvail()) {
						if (memman.insert(pr) == pr->memreq) {
							readyq.push(pr);
						} else {
							pfwait.push_back(pr);	
						} 
						holdq.pop();
					}
				}
				
				// select new process to run
				std::cout << (mproc.avail() ? "proc avail" : "no proc avail") << std::endl;
				std::cout << (readyq.empty() ? "non ready" : "ready procs") << std::endl;
				if (mproc.avail() && !readyq.empty()) {
					mproc.insert(readyq.front());
					readyq.pop();
				}	
				strstate = state();
				std::cout << "Ticks: " << ticks << std::endl;
				std::cout << strstate << std::endl;
				if (exit == ticks) break;
				sleep(2);
			}
		}

		std::string state() {
			std::string out = "";
			for (Process p : processpool) {
				out += p.state();
				out += memman.state(p.name); 
				out += '\n';
			}
			return out;	
		}
	
		void setProcIO(std::string name, int iorqsttime, int iotime) {
			for (Process p : processpool) {
				if (name == p.name) {
					p.setIO(iorqsttime, iotime);
					break;
				}
			}
		}
			
		void setProcMem(std::string name, int memrqsttime, int addr) {
			for (Process p : processpool) {
				if (name == p.name) {
					p.setMem(memrqsttime, addr);
					break;
				}
			}
		}

		void setExit(int i) {
			exit = i;
		}

		void insertNewProcess(std::string name, int arrivaltime, int cputime, int size) {
			Process newproc(name, arrivaltime, cputime, size);
			processpool.push_back(newproc);
		}
		
	private:
		int ticks, exit;	
		Processor<Process> mproc;
		MemoryManager<Process> memman;
		std::queue<Process*> holdq, readyq;
		std::vector<Process*> pfwait, iowait;
		std::vector<Process> processpool;	
};

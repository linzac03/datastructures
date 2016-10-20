#include <vector>
#include <queue>
#include <string>
#include <unordered_map>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#define PAGE_INIT 0

template <typename Object>
class MemoryManager {
	private:
		struct Page {
			Object *process;
			bool active;
			int pgnum;
			Page() : active(false), process(nullptr), pgnum(0) {}
		};	
		struct PageTable {
			std::vector<Page*> pages;	
		};
		int pagesize, pagelimit, procframelimit, avail;
		std::vector<Page*> mainmem;
		std::vector<Page> vmem;
		std::queue<Page*> pageq;
		std::unordered_map<std::string,PageTable> ptables;
	
	public:
		MemoryManager(int pagesz, int mainframes, int virpages, int procframelt) 
			: vmem(virpages), mainmem(mainframes), pagesize(pagesz), pagelimit(virpages), procframelimit(procframelt), avail(0) {} 

		void _init() {
			int num = PAGE_INIT;	
			for (Page & p : vmem) {
				p.pgnum = avail;
				pageq.push(&p);
				avail += pagesize;
			}
		} //any other initialization that I need
		
		std::string testinit() {
			while (!pageq.empty()) {
				std::cout << pageq.front()->pgnum << std::endl;
				pageq.pop();
			}
		}
		
		void tick() {}
		
		int checkAvail() {
			return avail;
		}
	
		Page & translateAddress(int address) {
			// address/pagesize = page number
			// address mod pagesize = frame offset
			int offset = address % pagesize;
			Page & p = vmem[(address/pagesize) + (offset > 0 ? 1 : 0)];
			return p;		
		}

		bool isActive(int address) {	
			return translateAddress(address).active;
		}

		void activate(int address) {
			Page p = translateAddress(address);
			p.active = true;
			mainmem.push_back(&p);
		}

		void deactivate(int address) {
			Page p = translateAddress(address);
			p.active = false;
			for(typename std::vector<Page*>::iterator itr = mainmem.begin(); itr != mainmem.end(); ++itr) {
				if ((*itr)->process == p.process) {	
					*itr = nullptr; // this is so weird 
				}
			}
			//how do i know it was successful? do i really care? why do i not have any snacks or coffee?????
		}

		void setProcess(std::string name, bool act) {
			for (Page * p : ptables[name].pages)
			if (act) {
				activate(p->pgnum);
			}	else {
				deactivate(p->pgnum);
			}
		}

		Page *getNextPage() {
			if (!pageq.empty()) {
				Page *p = pageq.front();
				pageq.pop();
				return p;
			}
			return nullptr;
		}

		int insert(Object *newjob) {
			// the fields used here in newjob should be interfaced, oh well 
			int numpgs, allocated;
			Page *toalloc;
			PageTable newpt;

			allocated = 0;
			numpgs = (int)ceil((float)newjob->memreq / (float)pagesize);
			
			while (allocated < numpgs) {
				if ((toalloc = getNextPage()) != nullptr) {
					toalloc->process = newjob;
					newpt.pages.push_back(toalloc);
					allocated++;
					avail -= pagesize;
				} else {
					return -1;
					//throw error something went wrong
					//should be checking for amount of pages available before inserting job
				}
			}
			ptables[newjob->name] = newpt;	
			return allocated;
		}

		int remove(std::string process) {
			if(ptables.find(process) != ptables.end()) {
				for(Page *p : ptables[process].pages) {
					p->process = nullptr;
					p->active = false;
					pageq.push(p);
					avail += pagesize;
				}
				// should probably check if it exists first...
				return ptables.erase(process);
			}
			return 0;
		}

		int request(int addr) {
			int vaddr = translateAddress(addr).pgnum / pagesize;
			if (!vmem[vaddr].active && mainAvail() > pagesize) {
				mainmem.push_back(&vmem[vaddr]);
				return 0;
			}
			return -1; 
		}

		int mainAvail() {
			int a = 0;
			for (Page *p : mainmem) {
				if (p->process != nullptr) {
					a += pagesize;
				}
			}
			return a;
		}

		std::string state(std::string name) {
			std::string out = "{";
			for (Page *p : ptables[name].pages) {
				std::stringstream ss;
				ss << std::hex << p->pgnum;
				out += "0x";
				out += ss.str();
				out += ":";
				out += p->active ? "up" : "dn";
				out += ", ";	
			}	
			out += "} ";
			return out;
		}
}; 

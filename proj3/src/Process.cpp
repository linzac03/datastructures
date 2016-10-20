#include <string>
#include "states.cpp"
#include <iostream>
#include <unordered_map>

class Process {
	public:
		std::string name;
		bool done, needio, needmem, ready;
		int arriveat, memreq, ticksleft, nextaddr;
		Process(std::string str, int arrivaltime, int ctime, int size) 
			: name(str), memreq(size), ticks(0), ticksleft(ctime), pstate(ProcessState::NEWP), arriveat(arrivaltime), done(false), needio(false) {}

		int time_spent() {
			return ticks;
		}

		int tick() {
			ticks++;
			return ticksleft--;
		}

		int iotick() {
			return ioremaining--;
		}
			
		bool checkIOrqst() {
			// check for io request should be done after every tick
			if (ticks == iorqst) {
				return true;
			}	
			return false;
		}
	
		int checkMemrqst() {
			std::unordered_map<int,int>::iterator itr = memreqs.find(ticks);
			if (itr == memreqs.end()) {
				return -1;
			}
			nextaddr = itr->second;
			return itr->second;
		}	

		void finish() {
			//std::cout << name << " has finished" << std::endl;
			pstate = ProcessState::DONE;
		}	

		std::string state() {
			std::string out = "";
			out += name;
			out += " ";
			out += std::to_string(ticks);
			out += " ";
			return out; 
		}

		void setIO(int iort, int iot) {
			iorqst = iort;
			ioremaining = iot;
		}

		void setMem(int time, int addr) {
			std::unordered_map<int,int>::iterator	itr = memreqs.find(time);
			if (itr == memreqs.end()) {
				memreqs[time] = addr;
			} // fail silently i don't really care
		}

	private:
		int ticks, paddr, iorqst, ioremaining;
		std::unordered_map<int, int> memreqs;
		ProcessState::state_t pstate; //really just for convenience, may not use
};

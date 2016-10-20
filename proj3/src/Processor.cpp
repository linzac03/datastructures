#include <string>
#include <vector>
#include <iostream>

template <typename Object>
class Processor {
	public:
		std::vector<Object*> tmp;
		Processor(int n, int q) : procpool(n), quantum(q) {}
		void tick() {
			for(Proc p : procpool) {
				if (p.process != nullptr) {
					p.ticksleft = p.process->tick();
				}
			}	
		}
		
		bool avail() {
			for (Proc p : procpool) {
				if (p.process == nullptr) return true;
			}
			return false;
		}
		
		void insert(Object* & newjob) {
			for (Proc & p : procpool) {
				if (p.process != nullptr) continue;
				p.process = newjob;
				std::cout << "Inserted " << p.process->name << std::endl;
				break;
			}
		}
	
		std::vector<Object*> & runcheck() {
			tmp.clear();
			bool isdone, nio, pgfltocr;
			for(Proc & p : procpool) {
				if (p.process != nullptr) {
					isdone = (p.process->ticksleft == 0);
					nio = p.process->checkIOrqst();
					pgfltocr = p.process->checkMemrqst() > 0; //check for page fault?????????
					if (isdone) {
						p.process->done = true;
						tmp.push_back(p.process);
						p.process = nullptr;
					} else if (nio) {
						p.process->needio = true;
						tmp.push_back(p.process);
						p.process = nullptr;	
					} else if (pgfltocr) {
						p.process->needmem = true;
						tmp.push_back(p.process);
						p.process = nullptr;	
					} else if (p.process->time_spent() % quantum == 0) {
						p.process->ready = true;
						tmp.push_back(p.process);
						p.process = nullptr;
					}
				}
			}
			return tmp;	
		}
			
	private:
		struct Proc {
			int ticksleft;
			Object *process;
			Proc() : ticksleft(0), process(nullptr) {}		
		};
		int quantum;
		std::vector<Proc> procpool;
};


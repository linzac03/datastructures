#include <iostream>
#include <string>
#include "Scheduler.h"
#include "BHeap.cpp"

//Public
template <typename Comparable>
Scheduler<Comparable>::Scheduler() :
	waitq{new BinaryHeap<Comparable>()}, runq{new BinaryHeap<Comparable>()}, tprocs{0}, bprocs{0} {}

template <typename Comparable>
void Scheduler<Comparable>::status(){
	std::cout << "Wait Q: ";
	this->waitq->print(); 
	std::cout << std::endl;	
	std::cout << "Run Q: ";
	this->runq->print(); 
	std::cout << std::endl;	
	std::cout << "Free Procs: " << this->tprocs - this->bprocs << std::endl;	
}

template <typename Comparable>
void Scheduler<Comparable>::init(){
	int nprocs;
	std::string uin = "";
	std::cout << "Specify number of procs: ";
	std::getline(std::cin, uin);
  nprocs = std::stoi(uin);
  if (nprocs > 0) {
		this->tprocs = nprocs;
	}  	
}

template <typename Comparable>
void Scheduler<Comparable>::tick(){
	std::string uin = "";
	std::string tok = "";
	Comparable * newjob = nullptr;
	Comparable djob;
	Comparable rjob;
	std::string argv[3];
	int pos = 0;
	int ppos = 0;
	std::string delim = " ";
	
	//cin from user
	std::cout << "ItsYou@Google: ";
	std::getline(std::cin, uin);
	while (pos != std::string::npos) {
		pos = uin.find(delim);
		tok = uin.substr(0, pos);
		if (tok == "exit") {
			exit = 1;
			break;
		}

		argv[ppos++] = tok;
		uin.erase(0, pos + 1);
	}
		
	if (!exit) {
		//waitq insert
		if (argv[0] != "") {
			if (std::stoi(argv[1]) > 0 && std::stoi(argv[2]) > 0) {
				newjob = new Comparable(argv[0], std::stoi(argv[1]), std::stoi(argv[2]));
				this->submitjob(*newjob);	
			}
		}

		//decrement jticks
		if (!this->runq->isEmpty()) {
			this->runq->dectimer();
		//if job done release procs
			if (this->runq->getMin() == 0) {
				this->runq->deleteMin(djob);	
				this->bprocs -= djob.releaseprocs();	
			}
		}	
		//find next shortest job
		if (!this->waitq->isEmpty()) {
			rjob = this->waitq->getMin();
			if (this->checkavail(rjob.jprocs)) {
				this->runjob(rjob, rjob.jprocs);
				this->waitq->deleteMin();
			}
		}
	}
	
} 

template <typename Comparable>
void Scheduler<Comparable>::submitjob(Comparable & job){
	this->insertjob(job);
}

template <typename Comparable>
bool Scheduler<Comparable>::checkavail(int nprocs){
	return nprocs <= (this->tprocs - this->bprocs);
}

//Private

template <typename Comparable>
void Scheduler<Comparable>::finddelshortest(Comparable & job){
	this->waitq->deleteMin(&job);
}

template <typename Comparable>
void Scheduler<Comparable>::insertjob(Comparable & job){
	this->waitq->insert(job);
}

template <typename Comparable>
void Scheduler<Comparable>::runjob(Comparable & job, int procs){ //give procs to job
	this->runq->insert(job);	
	this->bprocs += procs;
}

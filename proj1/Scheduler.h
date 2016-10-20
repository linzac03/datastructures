#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "BHeap.h"

template <typename Object>
class Scheduler {
	public:
		int exit = 0;
		Scheduler();
		~Scheduler();
		void init();
		void tick();
		void submitjob(Object & job);
		bool checkavail(int nprocs);
		void status();

	private:
		BinaryHeap<Object> * waitq = nullptr;
		BinaryHeap<Object> * runq = nullptr;
		int tprocs;
		int bprocs;
		void insertjob(Object & job);
		void finddelshortest(Object & job);
		void runjob(Object & job, int nprocs); //give procs to job
		 		
};

#endif

#ifndef JOB_H
#define JOB_H
#include <string>
#include <iostream>

class Job {
	public:
		std::string jname;
		int jprocs;
		int jticks;	
		
		Job(std::string name, int nprocs, int nticks);
		Job();
		~Job() { }
		int releaseprocs();
		Job operator--(int);
		bool operator==(const Job & rhs) const;
		bool operator==(int rhs);
		bool operator<(const Job & rhs) const;
		bool operator<(int rhs);
		bool operator>(const Job & rhs) const;
		bool operator>(int rhs);		
		friend std::ostream & operator<<(std::ostream & stream, const Job & job) {
			stream << job.jname;
			return stream;
		}
};

#endif

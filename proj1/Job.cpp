#include "Job.h"
#include <limits>
#include <string> 

Job::Job(std::string name, int nprocs, int nticks) : 
	jname{name}, jprocs{nprocs}, jticks{nticks} {}

Job::Job() {}

int Job::releaseprocs() {
	return this->jprocs;
}

Job Job::operator--(int) {
	this->jticks--;
	return *this;
}

bool Job::operator==(const Job & rhs) const {
	return this->jticks == rhs.jticks;
}

bool Job::operator==(int rhs) {
	return this->jticks == rhs;
}

bool Job::operator<(const Job & rhs) const {
	return this->jticks < rhs.jticks;
}

bool Job::operator<(int rhs) {
	return this->jticks < rhs;
}

bool Job::operator>(const Job & rhs) const {
	return this->jticks > rhs.jticks;
}

bool Job::operator>(int rhs) {
	return this->jticks > rhs;
}


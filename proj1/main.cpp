#include "schedtest.cpp"
#include "Job.cpp"

int main() {
	SchedTest<Job> * scheduler = new SchedTest<Job>();
	scheduler->run();
}

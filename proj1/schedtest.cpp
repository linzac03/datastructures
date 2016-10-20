#include "scheduler.cpp"

template <typename Comparable>
class SchedTest {
	public:
		SchedTest() : testSched{new Scheduler<Comparable>()} {};
		~SchedTest() { delete testSched; }
		void run() {
			testSched->init();
			while(!testSched->exit) {
				testSched->status();
				testSched->tick();
			}
		}

	private:
		Scheduler<Comparable> * testSched;
};


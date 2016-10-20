namespace ProcessState { 
	enum state_t {
		NEWP, 
		HOLD, 
		PFWAIT, 
		READY, 
		RUNNING, 
		IOWAIT, 
		DONE
	};
}

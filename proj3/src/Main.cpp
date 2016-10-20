#include "System.cpp"
#include <string.h>
#include <sstream>
#include <iostream>

enum switch_case {
	ARRIVE,
	IOREQ,
	MEM,
	TERM,
	CONF
};

switch_case shash(std::string item) {
	if (item == "conf") return CONF;
	if (item == "arrive") return ARRIVE;
	if (item == "ioreq") return IOREQ;
	if (item == "mem") return MEM;
	if (item == "term") return TERM;
}

int main(int argc, char **argv) {
	int term, pagesize, mainframes, virpages, procframelimit, timequan, numproc, arrivaltime, cputime, memreq, iorqsttime, iotime;
	std::string instr, tmp, jobname;
	std::getline(std::cin, instr);
	std::istringstream confss(instr);
	
	confss >> tmp;
	if (tmp == "conf") {
		confss >> pagesize >> mainframes >> virpages >> procframelimit >> timequan >> numproc;
 	} else {
		fprintf(stderr, "No configuration...");
		return -1;
	}
	
	System sys(pagesize, mainframes, virpages, procframelimit, timequan, numproc);
	for(instr; std::getline(std::cin, instr);) {
		std::stringstream ss(instr);
		ss >> tmp;
		switch(shash(tmp)) {
			case ARRIVE:
				ss >> jobname >> arrivaltime >> cputime >> memreq;
				std::cout << jobname << std::endl;
				sys.insertNewProcess(jobname, arrivaltime, cputime, memreq);
				break;
			case IOREQ:
				ss >> jobname >> iorqsttime >> iotime;
				sys.setProcIO(jobname, iorqsttime, iotime);
				break;
			case MEM:
				ss >> jobname >> iorqsttime >> iotime;
				sys.setProcMem(jobname, iorqsttime, iotime);
				break;
			case TERM:
				ss >> term;
				sys.setExit(term);
				break;
			default:
				break;
		}	
	}
	sys.init(); //pretty much meminit
	sys.run();
	return 0; 
}


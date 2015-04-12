#include "defs.h"
#include <iostream>

class parser{

	int cacheL1;
	int cacheL2;
	string cacheType;

	int numRead;
	int numWrite;

	private:
		deque<int> MemoryReference;
		deque<std::string> Address;
		deque<std::string> Input;

	public:
		parser();
		void startSim(int argc, char **argv);
		void readTrace();
		int readParameters(int,char**);
		void printResult();
		int getCacheL1();
		int getCacheL2();
		string getCacheType();
};

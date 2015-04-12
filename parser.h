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
		deque<uint32_t> tag;
		deque<uint32_t> cacheLine;
		deque<uint32_t> offset;
		deque<std::string> Input;
		int cacheLines;
		int tagSize;
		int addressSize;

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

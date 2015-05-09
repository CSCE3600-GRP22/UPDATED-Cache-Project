#include "defs.h"
#include <iostream>

class parser{



	private:
		deque<int> MemoryReference;
		deque<uint32_t> tag;
		deque<uint32_t> tag2;
		deque<uint32_t> cacheLine;
		deque<uint32_t> cache2Line;
		deque<uint32_t> offset;
		deque<std::string> Input;
		int cacheLines;
		int cache2Lines;
		int tagSize;
		int tag2Size;
		int addressSize;
		int address2Size;
		int cacheL1;
		int cacheL2;
		string cacheType;
		int numRead;
		int numWrite;

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

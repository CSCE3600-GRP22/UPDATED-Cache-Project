#include "parser.h"
#include "cache.h"
void parser::startSim(int argc, char **argv){

	// if read parameters returns false (1) return out of main.
	if(this->readParameters(argc, argv))
		return;
	this->readTrace();
	cache cacheSim(cacheLines, cache2Lines);
	this->printResult();
	if(!cacheType.compare("direct"))
		cacheSim.runDirect(tag, cacheLine, offset, tag2, cache2Line);
	else if(!cacheType.compare("full"))
		cacheSim.runFull(tag, offset);
	return;
}
// initialize all needed variables
parser::parser(){
	cacheL1 = 32768;
	cacheL2 = 65536;
	cacheType = "direct";

	numRead = 0;
	numWrite = 0;
}

void parser::readTrace(){
	std::string line;
	std::stringstream ss;
	uint32_t bitLine, bitTag, bitCacheLine, bitOffset;
	// read trace file and count reads and write
	while(std::getline(std::cin,line)){
		char *token = std::strtok((char *)line.c_str(), " \n\t");
    while (token != NULL) {

			if(((int)token[0]-48) == 0 && (token[1] == '\0')){
				numWrite++;
				this->MemoryReference.push_back(0);
			}
			else if(((int)token[0]-48) == 1 && (token[1] == '\0')){
				numRead++;
				this->MemoryReference.push_back(1);
			}
			else{

				std::string input(token);
				ss << hex << input;
				ss >> bitLine;
				ss.clear();
				bitTag = bitLine >> 32 - tagSize;
				this->tag.push_back(bitTag);
				bitCacheLine = bitLine << tagSize;
				bitCacheLine = bitCacheLine >> (tagSize+5);
				this->cacheLine.push_back(bitCacheLine);
				bitOffset = bitLine & 31;
				this->offset.push_back(bitOffset);
				if(!cacheType.compare("direct")){
					bitTag = bitLine >> 32 - tag2Size;
					this->tag2.push_back(bitTag);
					bitCacheLine = bitLine << tag2Size;
					bitCacheLine = bitCacheLine >> (tag2Size+5);
					this->cache2Line.push_back(bitCacheLine);

				}
			}
			token = std::strtok(NULL, " ");
		}
	}
}


int parser::readParameters(int numArgs, char *parameters[]){

	// for each parameter
	for(int i = 0; i < numArgs; i++)
	{
		// push back each parameter into the input queue
		Input.push_back(parameters[i]);

		// update Level 1 and 2 cache values
		if(!strcmp(parameters[i],"-sizeL1"))
			cacheL1 = atoi(parameters[i+1]);
		else if(!strcmp(parameters[i],"-sizeL2"))
			cacheL2 = atoi(parameters[i+1]);
		// update cache type
		else if(!strcmp(parameters[i],"-type"))
			cacheType = parameters[i+1];
	}

	// error checking

	// cache size
	if(cacheL1 > cacheL2)
	{
		std::cout << "ERROR: Level 1 cache is greater than level 2 cache.\n";
		return 1;
	}

	// check cache power of two for each cache level
	if(!((cacheL1 & (cacheL1 - 1)) == 0))
	{
		std::cout << "ERROR: Level 1 cache is not a power of 2\n";
		return 1;
	}
	else if(!((cacheL2 & (cacheL2 - 1)) == 0))
	{
		std::cout << "ERROR: Level 2 cache is not a power of 2\n";
		return 1;
	}
	this->cacheLines = cacheL1 / 32;
	this->cache2Lines = cacheL2 / 32;
	if(!cacheType.compare("direct")){
		for(int i = 0; i < 27; i++){
			if(pow(2, i) == this->cacheLines){
				this->addressSize = i;
				this->tagSize = 32-(i+5);
				break;
			}
		}
		for(int i = 0; i < 27; i++){
			if(pow(2, i) == this->cache2Lines){
				this->address2Size = i;
				this->tag2Size = 32-(i+5);
				break;
			}
		}
	}else if(!cacheType.compare("full")){
		this->addressSize = this->address2Size = 0;
		this->tagSize = this->tag2Size = 27;
	}
	/*if(cacheLines == 1024){
		this->addressSize = 10;
		this->tagSize = 17;
	}else if(cacheLines == 512){
			this->addressSize = 9;
			this->tagSize = 18;
	}else if(cacheLines == 2048){
			this->addressSize = 11;
			this->tagSize = 16;
	}*/
	return 0;
}

void parser::printResult(){

	// print result message
	std::cout <<"Input:\n\t";

	std::cout << "$>";
	for(int i = 0; i < Input.size(); i++)
		std::cout << Input[i] << " ";

	std::cout << "\nOutput:\n\t";

	std::cout << "Input Parameters read:";
	std::cout << "\n\t\tSizeL1: " << cacheL1;
	std::cout << "\n\t\tSizeL2: " << cacheL2;
	std::cout << "\n\t\tType: "	<< cacheType;
	std::cout << "\n";

	std::cout << "\tMemory reference from read from file";
	std::cout << "\n\t\t" << numRead+numWrite << " Total";
	std::cout << "\n\t\t" << numRead << " Reads";
	std::cout << "\n\t\t" << numWrite << " Write";
	std::cout << "\n";

	std::cout << "\tCache Simulator Options";
	std::cout << "\n\t\t" << addressSize << " bits for the address Level 1";
	std::cout << "\n\t\t" << tagSize << " bits for the tag Level 1";
	std::cout << "\n\t\t" << "5 bits for the offset Level 1";
	std::cout << "\n\t\t" << cacheL1 << " KB of cache Level 1";
	std::cout << "\n\t\t" << cacheLines << " cache lines Level 1";
	std::cout << endl;
	std::cout << "\n\t\t" << address2Size << " bits for the address Level 2";
	std::cout << "\n\t\t" << tag2Size << " bits for the tag Level 2";
	std::cout << "\n\t\t" << "5 bits for the offset Level 2";
	std::cout << "\n\t\t" << cacheL2 << " KB of cache Level 2";
	std::cout << "\n\t\t" << cache2Lines << " cache lines Level 2";

	std::cout << "\n";
}

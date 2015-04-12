#include "parser.h"
void parser::startSim(int argc, char **argv){
	// if read parameters returns false (1) return out of main.
	if(this->readParameters(argc, argv))
		return;
	this->readTrace();
	this->printResult();
	return;
}
// initialize all needed variables
parser::parser(){
	cacheL1 = 0;
	cacheL2 = 0;
	cacheType = "";

	numRead = 0;
	numWrite = 0;
}

void parser::readTrace(){
	std::string line;

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
				this->Address.push_back(input);
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
}
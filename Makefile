CacheSim	: main.o parser.o cache.o
			  g++ -std=c++11 main.o parser.o cache.o -g -o CacheSim
main.o		: main.cpp parser.h cache.h
			  g++ -std=c++11 -c -g main.cpp
parser.o	: parser.cpp parser.h cache.h
				g++ -std=c++11 -c -g parser.cpp
cache.o		: cache.cpp parser.h cache.h
				g++ -std=c++11 -c -g cache.cpp
clean:
				rm *.o
run:
				./CacheSim -sizeL1 32768 -sizeL2 65536 -type direct < big_trace.trace
run64:
				./CacheSim -sizeL1 65536 -sizeL2 65536 -type direct < big_trace.trace
run16:
				./CacheSim -sizeL1 16384 -sizeL2 32768 -type direct < big_trace.trace

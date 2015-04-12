CacheSim	: main.o parser.o
			  g++ main.o parser.o -g -o CacheSim
main.o		: main.cpp parser.h
			  g++ -c -g main.cpp
parser.o	: parser.cpp parser.h
				g++ -c -g parser.cpp
clean:
				rm *.o
run:
				./CacheSim -sizeL1 512 -sizeL2 1024 -type direct < small_trace.txt

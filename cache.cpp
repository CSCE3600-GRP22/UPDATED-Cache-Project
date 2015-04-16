#include "parser.h"
#include "cache.h"
cache::cache(int size){
  block = new uint32_t[size];
  tags = new uint32_t[size];
  blockSize = size;
  hit = 0;
  miss = 0;
}


void cache::run(deque<uint32_t> tag, deque<uint32_t> address, deque<uint32_t> offset){
  uint32_t currentTag, currentAddress;
  while(!address.empty()){

    deque<uint32_t>::iterator currentTag = tag.begin();
    deque<uint32_t>::iterator currentAddress = address.begin();

    if(tags[(*currentAddress) % blockSize] == *currentTag){
      hit +=1;
    }else{
      miss += 1;
      tags[(*currentAddress) % blockSize] = *currentTag;
    }
    address.pop_front();
    tag.pop_front();
  }

  cout << "Number of HITS: \t" << dec << hit << endl;
  cout << "Number of MISSES:\t" << miss << endl << endl;
}

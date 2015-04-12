#include "parser.h"
#include "cache.h"
cache::cache(int size){
  block = new uint32_t[size];
  tags = new uint32_t[size];
  hit = 0;
  miss = 0;
}


void cache::run(deque<uint32_t> tag, deque<uint32_t> address, deque<uint32_t> offset){

  while(!tag.empty()){
    

  }

}

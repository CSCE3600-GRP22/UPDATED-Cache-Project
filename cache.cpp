#include "parser.h"
#include "cache.h"
cache::cache(int size, int size2){
  tags2 = new uint32_t[size2];
  tags = new uint32_t[size];
  blockSize = size;
  block2Size = size2;
  hit = 0;
  hit2 = 0;
  miss = 0;
  miss2 = 0;
}


void cache::runDirect(deque<uint32_t> tag, deque<uint32_t> address, deque<uint32_t> offset, deque<uint32_t> tag2, deque<uint32_t> address2){

  do{

    deque<uint32_t>::iterator currentTag = tag.begin();
    deque<uint32_t>::iterator currentAddress = address.begin();
    deque<uint32_t>::iterator currentTag2 = tag2.begin();
    deque<uint32_t>::iterator currentAddress2 = address2.begin();

    if(tags[(*currentAddress) % blockSize] == *currentTag){
      hit +=1;
    }else{
      miss += 1;
      tags[(*currentAddress) % blockSize] = *currentTag;
        if(tags2[(*currentAddress2) % block2Size] == *currentTag2){
          hit2 += 1;
        }else{
          miss2 += 1;
          tags2[(*currentAddress2) % block2Size] = *currentTag2;
        }
    }

    address.pop_front();
    tag.pop_front();
    address2.pop_front();
    tag2.pop_front();
  }while(!address.empty() || !tag.empty() || !address2.empty() || !tag2.empty());
  cout << "DIRECT" << endl;
  cout << "Number of HITS in L1: \t" << dec << hit << endl;
  cout << "Number of MISSES in L1:\t" << miss << endl << endl;
  cout << "Number of HITS in L2: \t" << dec << hit2 << endl;
  cout << "Number of MISSES in L2:\t" << miss2 << endl << endl;
}

void cache::runFull(deque<uint32_t> tag, deque<uint32_t> offset){
  srand(time(NULL));
  do{
    deque<uint32_t>::iterator currentTag = tag.begin();
    for(int i = 0; i < blockSize; i++){
      if(tags[i] == *currentTag){
        hit++;
        break;
      }else if(tags[i] == 0){
        miss++;
        tags[i] = *currentTag;
        for(int j = 0; j < block2Size; j++){
          if(tags2[j] == *currentTag){
            hit2++;
            break;
          }else if(tags2[j] == 0){
            miss2++;
            tags2[j] = *currentTag;
            break;
          }else if(j == (block2Size-1)){
            miss2++;
            int pos = rand() % blockSize;
            tags2[pos] = *currentTag;
          }
        }
        break;
      }else if(i == (blockSize-1)){
        miss++;
        int pos = rand() % blockSize;
        tags[pos] = *currentTag;
        for(int j = 0; j < block2Size; j++){
          if(tags2[j] == *currentTag){
            hit2++;
            break;
          }else if(tags2[j] == 0){
            miss2++;
            tags2[j] = *currentTag;
            break;
          }else if(j == (block2Size-1)){
            miss2++;
            int pos = rand() % blockSize;
            tags2[pos] = *currentTag;
          }
        }
      }
    }
    tag.pop_front();
  }while(!tag.empty());
  cout << "FULL" << endl;
  cout << "Number of HITS in L1: \t" << dec << hit << endl;
  cout << "Number of MISSES in L1:\t" << miss << endl << endl;
  cout << "Number of HITS in L2: \t" << dec << hit2 << endl;
  cout << "Number of MISSES in L2:\t" << miss2 << endl << endl;

}

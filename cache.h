#include "defs.h"
#include <iostream>


class cache{
  private:
    uint32_t *tags2;
    uint32_t *tags;
    int blockSize;
    int block2Size;
    int hit;
    int hit2;
    int miss;
    int miss2;
  public:
    cache(int size, int size2);
    void runDirect(deque<uint32_t> tag, deque<uint32_t> address, deque<uint32_t> offset, deque<uint32_t> tag2, deque<uint32_t> address2);
    void runFull(deque<uint32_t> tag, deque<uint32_t> offset);
};

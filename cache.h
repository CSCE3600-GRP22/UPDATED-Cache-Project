#include "defs.h"
#include <iostream>


class cache{
  private:
    uint32_t *block;
    uint32_t *tags;
    int hit;
    int miss;
  public:
    cache(int size);
    void run(deque<uint32_t> tag, deque<uint32_t> address, deque<uint32_t> offset);
};

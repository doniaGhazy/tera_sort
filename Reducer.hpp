#ifndef Reducer_H
#define Reducer_H
#include"heapSort.h"
#include "Thread.h"
#include "ShuffleBuffers.hpp"
class Reducer : public Thread
{
private:
    int index;
    ShuffleBuffer ** shuffleBuffer; //pointer of pointer to thge shuffleBuffeer 
    ShuffleBuffer* shBuffer; //pointer to shuffleBuffer
    int reducer_count; // number of reducer var
public:
    Reducer(ShuffleBuffer * p_shuffleBuffer,int reducer_count, int ind);
    void * threadMainBody (void * arg);
    ~Reducer();
};
Reducer::Reducer (ShuffleBuffer * p_shuffleBuffer,int p_reducer_count, int ind)
{
  
    shBuffer= p_shuffleBuffer;
    index- ind;
}
Reducer::~Reducer() 
{

}

void *Reducer::threadMainBody(void *arg) 
{
  //call shufflebuffer sort
     shBuffer->sort();
}
#endif

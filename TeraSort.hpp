#ifndef TeraSort_H
#define TeraSort_H
#include <iostream>
#include "Mapper.hpp"
#include "ShuffleBuffers.hpp"
#include "ThreadManager.h"
#include "Reducer.hpp"
#include "Thread.h"
#include"string.h"
using namespace std;

class TeraSort
{
  private:
    string p_input_filename;
    FILE  * file;
        void *a;
    string p_output_filename;
    int p_mapper_count;
    int percentsamp;
    int p_reducer_count;
    int avgcutpoints[];
    string file_name;
  public:
    Mapper *Mappers;
    Reducer *  reducer;
    ShuffleBuffer* shBuffer;
     ShuffleBuffers *shuffleBuffer;
    TeraSort(FILE* files, string ofilename, int mapper_count, int reducer_count, int percetsamp);
    void sort(int mapper_count, int reducer_count);
    ~TeraSort();
};
TeraSort::TeraSort(FILE* files, string ofilename, int mapper_count, int reducer_count, int percetsamp)
{   int D=0;
    int M=1000;
    ShuffleBuffers(D,M);    //calling Shuffle BufferS constructor
    file= files;
    //assigning everything based off of the construcor
    p_output_filename= ofilename;
    p_mapper_count=mapper_count;
    p_reducer_count= reducer_count;
    percentsamp= percetsamp;
 
}
void TeraSort::sort(int p_mapper_count,int p_reducer_count)
{
    cout<<" GO INTO SORT";
    ThreadManager *mappersThreadManager = new ThreadManager();  //new thread manager
    for (int i = 0; i < p_mapper_count; i++)
    mappersThreadManager->addThread(new Mapper(i, file,p_mapper_count, p_reducer_count, percentsamp, shuffleBuffer));   //Mapper constructor (looping to create array of mappers)
    /* phase 1 */
    cout<<"WENT INTO THE LOOP/CREATED THREADS ";
    mappersThreadManager->startRR();
    
    mappersThreadManager->barrier();

    shuffleBuffer->calcAverage();   //CREATEs AVERAGE CUTPOINTS for all mapper cutpoints

    /* phase 2 */
    mappersThreadManager->startRR();

    mappersThreadManager->barrier();
        //going to call mapper main function
    

    ThreadManager *reducersThreadManager = new ThreadManager();
    for (int i = 0; i < p_reducer_count; i++)
        reducersThreadManager->addThread(new Reducer(shBuffer, p_reducer_count, i));    //creates reducer array 
    reducersThreadManager->barrier();

    shuffleBuffer->save(file_name);     //adds all the data together into the new file
}
TeraSort::~TeraSort()
{
    
}
#endif
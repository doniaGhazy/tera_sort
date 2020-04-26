#ifndef MAPPER_H
#define MAPPER_H
#include <stdio.h>
#include <cstdlib>
#include "QuickSort.hpp"
#include "TeraSortItem.hpp"
#include "ShuffleBuffers.hpp"
#include <iostream>
#include <inttypes.h>
#include"string.h"
typedef unsigned __int128 uint128_t;
using namespace std;  

class Mapper : public Thread
{
private:
  
  teraitem_r *teradata;
  //terait
  TeraSortItem **terasortItems;
  TeraSortItem **terasortsample;
  ShuffleBuffers *shuffle_Buffers;
  int index; 
  FILE* pfile;
  int mapper_count;
  int p_index;
  int reducer_counts;
  int percentsample;
  bool second_phase;
  int number_of_sample;
  int size_of_data =100;
  uint128_t  * cutpoint;//[reducer_counts - 1];
  long fsize;
  public :
  teraitem_r  * teradatai;  
  long number_of_items;
  Mapper(int p_index, FILE *file, int p_mapper_count, int p_reducer_counts, int percentsamp, ShuffleBuffers *shuffle_Buffer);
  void ReadFile(FILE* pfile);
  void buildSample();
  void sortSample();
  void createCutPoints(); //uint128_t* cutpoint,int reducer_counts, int number_of_sample
  void Setcutpoint();
  void * operator new(size_t size ); 
  void Shuffle();
  void* threadMainBody(void * arg );
  ~Mapper();
};


Mapper::Mapper(int p_index,FILE *file, int p_mapper_count, int p_reducer_counts, int percentsamp, ShuffleBuffers *shuffle_Buffer)
{
  teradata = (teraitem_r *)calloc(number_of_items, sizeof(teraitem_r));   //array of teradata items
  terasortItems = (TeraSortItem **)calloc(number_of_items, sizeof(TeraSortItem *)); //array of pointers pointing to teradata itema
  for (int i = 0; i < number_of_items; i++)
    terasortItems[i] = new TeraSortItem(&teradata[i]);  //giving it the teradata item itself 
  
  mapper_count = p_mapper_count;  //assigning everything according to the parameters
  reducer_counts = p_reducer_counts;
      number_of_items =((fsize/size_of_data)/mapper_count);
      pfile= file;
      percentsample = percentsamp;
      number_of_sample = (percentsample / 100.0) * number_of_items;
      shuffle_Buffers= shuffle_Buffer;
}

void * Mapper:: operator new(size_t size) 
{ 
         void * p = malloc(size);     //overloading new mapper
        
        return p;
} 
void Mapper::ReadFile(FILE* pfile)
{
  size_t result;
  fseek(pfile, 0, SEEK_END);                                   // Move file pointer to the end
  fsize = ftell(pfile);                                   // Get current position = size of file
  rewind(pfile);                                               // rewind file pointer to point to the first byte in file
    fseek(pfile,((p_index-1/mapper_count)*fsize), SEEK_SET);    //seeks the pointer to the mappers section
    for (int i = 0; i < number_of_items; i++)
    {
      result = fread(&teradatai[i], 1, 100, pfile); //reads the amount of items needed and places them in teradata buffer
      if (result != number_of_items)                         //checking fread works
        cout << "ERROR READING FROM THE FILE INTO THE BUFFER";
    }
}

void Mapper::buildSample()
{
  terasortsample = (TeraSortItem **)calloc(number_of_items, sizeof(TeraSortItem*));
  for (int i = 0; i < number_of_sample; i++)
  {
    int x = (rand() % number_of_items + 1);
    while (teradatai[x].b1[0]== 1) //Marks the item so that if random number is generated more than once it does not take the same item more than once
    {
      x = (rand() % number_of_items + 1); 
    }
    terasortsample[i] = new TeraSortItem(&teradatai[x]);  //adds it to the Terasortsample
    teradatai[x].b1[0]==1;
    
  }
}
void Mapper::sortSample() 
{   quickSort <TeraSortItem> qs;
    qs.quick_Sort(terasortsample, number_of_sample);  //Sorts the sample using quick sort
}

void Mapper::createCutPoints() 
{
  //cout<<"NUMBER OF SAMPLE:  "<<number_of_sample;
  for (int i = 0; i < (reducer_counts - 1); i++)
  {
    //int j=((i+1) *100);
  //  uint128_t no = terasortSample[j]->key();
    cutpoint[i] = ((i+1) *number_of_sample)-1;    //Creates the cutpoint b
  }
}
void Mapper::Setcutpoint()
{
  for (int i = 0; i < (reducer_counts - 1); i++)
  {
    shuffle_Buffers->setCutPoint(cutpoint[i],index,i);
  }
}
void Mapper::Shuffle()
{ //one loop
  for (int i = 0; i < number_of_items; i++)
  // for (int j=0; j<reducer_count-1; j++ )
  {
    //THREAD??
    shuffle_Buffers->append(&teradatai[i], cutpoint);
  //  memcpy(shuffle_Buffer[i], teraSortItem[i], 100);
  }
}
void* Mapper::threadMainBody(void * arg )
{ //check in whichs phase the prog is in 
  // if the first phase, then build a sample
  // and sort it then,
  // create its cutpoints
  // loop over the number of mappers 
  //and set the cutpoints into the shuffleBuffer 
  // If it is in the second phase, then
  // Just do shuffling 
  if (!second_phase)
  {
    ReadFile(pfile);
    buildSample();
    sortSample();
    createCutPoints();
    for (int i=0; i< mapper_count; i++)
    Setcutpoint();
    second_phase = true;
  }
  else
  {
    Shuffle();
  }
}
Mapper::~Mapper() //deconstructor 
{
  
}
#endif

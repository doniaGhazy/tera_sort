#ifndef ShuffleBuffers_H
#define ShuffleBuffers_H
#include "ShuffleBuffer.hpp"
class ShuffleBuffers
{
private:
  
  int index; //index var
  int currentIndex; //current index var
  int p_mapper_count; //number of mapper var
  int p_reducer_count; //nummber of reducers var
  uint128_t **cutpoints; //pointer ppointer array
  uint128_t *avgcutpoints; //pointer to avg cut points of uint128 typ

public:
  ShuffleBuffer **shuffleBuffers; //pointer of pointer to shuffleBuffer 
  ShuffleBuffers(int count, int size); //overloaded constructor 
  
  void append(teraitem_r *teradata, uint128_t * avgcutpoints ); //insert fn to append teradate due to cutpoints
  void save(string file_name); //fn to save the the file name 
  ShuffleBuffer *operator[](int index); //overloading operators 
  void setCutPoint(uint128_t,int,int); //sets the cutpoint in the cutpoint array (because it is private)
  uint128_t * calcAverage(); //fn to calc the avg 

  
  ~ShuffleBuffers();
};

ShuffleBuffers::ShuffleBuffers(int count, int size)
{
  count = 0;                                  // set the count with zero
  shuffleBuffers = new ShuffleBuffer *[size]; //create an new array of type shuffle buffers
  for (int i = 0; i < size; i++)              // loop through the whole array and set its items to NULL.
    shuffleBuffers[i] = new ShuffleBuffer(size);
}

ShuffleBuffer *ShuffleBuffers::operator[](int index) //overloading operators 
{
  return shuffleBuffers[index]; //return the index of the shuffleBuffer as []
}
void ShuffleBuffers:: append(teraitem_r* teradata, uint128_t * avgcutpoints)
{ //check if the key value inside the tera date 
  // equal to the avg cut points, 
  // then, insert the tera data inside the shuffleBuffer array
  for (int i = 0; i < (p_reducer_count - 1); i++)
    if (TeraSortItem::calckey(teradata->key) > avgcutpoints[i]) 
      shuffleBuffers[i]->append(teradata);
}
void ShuffleBuffers:: setCutPoint(uint128_t cutpoint, int map_index, int cutpoint_index)
{ //assign the cutpoints of the map indec to the curr cut points 
  cutpoints[map_index][cutpoint_index] = cutpoint;
}
//fn to write the shuffleBuffers into output file
void ShuffleBuffers::save(string file_name)
{ 
  FILE *p_file;
  //loop over the reducer count numbers
  // write the data inside the output file 
  for (int i=0; i<p_reducer_count; i++)
  fwrite(shuffleBuffers[i],sizeof(teraitem_r),sizeof(ShuffleBuffer),p_file);
}
uint128_t * ShuffleBuffers::calcAverage()
{
  //create "new" for avgcutpoints pointer 
  //loop over the number of both mapper and reducer 
  // sum the avg to the cutpoints in every mapper 
  // get the avg cutpoint of every mapper and put them inside an array
  //return this avg 
    int avg=0;
  avgcutpoints = new uint128_t [p_reducer_count -1];
  for (int i = 0; i < p_reducer_count - 1; i++){
    for (int j = 0; j < p_mapper_count; j++)
      avg = avg + cutpoints[j][i];
    avgcutpoints[i] = avg / p_mapper_count;
    avg=0;
    }
  return avgcutpoints;
}
ShuffleBuffers::~ShuffleBuffers() //deconstructor 
{
  
}
#endif

#ifndef ShuffleBuffer_H
#define ShuffleBuffer_H
#include "TeraSortItem.hpp"
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include "Thread.h"
class ShuffleBuffer 
{
private:

   pthread_mutex_t locks;
 
  TeraSortItem **terasortObjects; // creating array pointing to objects of terasortItem
  int currentsize;     //declaring current size
  int size;       //creating size variable 
  int number_of_items; //number of items 

public:
 teraitem_r *teradata; //pointer for teradata items 
  ShuffleBuffer(int p_size);  //overloading constructor 
  void * operator new(size_t size ); 
  void append(teraitem_r *teradata); //append fn to insert teradata 
  void operator[](ShuffleBuffer *shuffleBuffer); //overloading [] operators
  bool operator>(Sortable *p_sortable); //overloading > operator
  bool operator<(Sortable *p_sortable); // overloading < operatopr
  bool operator>=(Sortable *p_sortable); //overloading >= operator 
  bool operator<=(Sortable *p_sortable); // overloading <= operator
  bool operator==(Sortable *p_sortable); //overloading == operator
  bool operator!=(Sortable *p_sortable); //overloading != operator
  ~ShuffleBuffer(); //deconstructor 
  void sort();
};

ShuffleBuffer::ShuffleBuffer(int p_size) // overloaded constructor 
{
  currentsize = 0; //intializing curr size to zero
  size = p_size; // assigning the p-size to size 
  teradata = (teraitem_r *)calloc(size, sizeof(teraitem_r *)); //allocating memory space fot teradata items
  terasortObjects = (TeraSortItem **)calloc(p_size, sizeof(TeraSortItem *)); //allocating array of pointers of type teraitemsort
  for (int i = 0; i < number_of_items; i++)
    terasortObjects[i] = new TeraSortItem(&teradata[i]); //looping over the number of items to move the cons
}
 

void ShuffleBuffer::append(teraitem_r *p_teradata) //insert new teradata to the buffer
{
  pthread_mutex_lock(&locks); //synchronization
  if (size == currentsize)
  {
    size += 100; //increase the size by 100
    teradata = (teraitem_r *)realloc(teradata, size * 100); //re allocate a space in memory 

  }
  memcpy(&teradata[currentsize++], p_teradata, 100);//to copy block of data from one source to another 
  pthread_mutex_unlock(&locks);//unlock the mutex
}
/*void ShuffleBuffer::operator[](ShuffleBuffer *shuffleBuffer)
{
}*/

void ShuffleBuffer::sort() 
{
     quickSort <TeraSortItem> qs; //instanctation of the quickSort 
     qs.quick_Sort(terasortObjects, number_of_items); //call the quick sort fn to start sorting 
}
ShuffleBuffer::~ShuffleBuffer() //deconstructor
{
}

#endif

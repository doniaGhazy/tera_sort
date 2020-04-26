#ifndef TeraSortItem_H
#define TeraSortItem_H
#include <string.h>
#include <algorithm>
#include <cstdint>
#include <inttypes.h>
typedef unsigned __int128 uint128_t;
using namespace std;
class Sortable
{
private:
public:
//pure virtual methods to be inherited to all child classes 
  Sortable(){}
  Sortable(Sortable &sortable){}
  virtual uint128_t key() = 0;
  //virtual void swap(TeraSortItem *p_sortable) = 0;
  virtual bool operator>(Sortable *p_sortable) = 0;
  virtual bool operator<(Sortable *p_sortable) = 0;
  virtual bool operator>=(Sortable *p_sortable) = 0;
  virtual bool operator<=(Sortable *p_sortable) = 0;
  virtual bool operator==(Sortable *p_sortable) = 0;
  virtual bool operator!=(Sortable *p_sortable) = 0;
  virtual ~Sortable(){}
};
typedef struct
{ //struct to read the file
  uint8_t key[10];
  uint8_t b1[2];
  char rowid[32];
  uint8_t b2[4];
  uint8_t filler[48];
  uint8_t b3[4];
} teraitem_r;

class TeraSortItem : public Sortable
  {
  private:
    teraitem_r *teraitem; //pointer to tera data item
  public:

    static uint128_t calckey(uint8_t * ky); //calc key fn 
    TeraSortItem(); // default constructor 
    //TeraSortItem::TeraSortItem(TeraSortItem &&teraSortItem);
    TeraSortItem(TeraSortItem &teraSortItem); // copy constractor
    TeraSortItem(teraitem_r *p_teraitem); //overloaded constructor 
    uint128_t key(); //to calc the key 
    void swap(TeraSortItem *p_sortable); //sn to swap two objects 
    void operator=(TeraSortItem *teraSortItem); //overloaded = operator 
    void * operator new(size_t size) ; //overload new operator 
    bool operator>(Sortable *p_sortable); //overloaded > operator 
    bool operator<(Sortable *p_sortable); //overloaded < operator 
    bool operator>=(Sortable *p_sortable); //overloaded >= operator 
    bool operator<=(Sortable *p_sortable); //overloaded <= operator 
    bool operator==(Sortable *p_sortable); //overloaded == operator 
    bool operator!=(Sortable *p_sortable); //overloaded != operator 
    ~TeraSortItem(); //deconstructor 
  };
  TeraSortItem::TeraSortItem()
  {

  }
  TeraSortItem::TeraSortItem(TeraSortItem &teraSortItem) // copy constractor
  {
    teraitem = new teraitem_r;
    *teraitem = *teraSortItem.teraitem;
    memcpy(teraitem,teraSortItem.teraitem,100);
  }
 
  TeraSortItem::TeraSortItem(teraitem_r *p_teraitem)//overloading constructor 
  {
    teraitem = p_teraitem;
  }
  void TeraSortItem::swap(TeraSortItem *p_sortable)
  {
  std::swap(this->teraitem,p_sortable->teraitem);
  }
void TeraSortItem:: operator=(TeraSortItem *teraSortItem)
  {
    memcpy(teraitem, teraSortItem->teraitem, sizeof(teraitem_r)); //memcpy fn to move data from one obkect to another 
  }
void * TeraSortItem:: operator new(size_t size) //overloading new operator 
{ 
         void * p = malloc(size); //allocate a new place in memory 
        // TeraSortItem()
        return p; 
} 
bool TeraSortItem:: operator>(Sortable *p_sortable) //overloading > operator
  {  
    //check if the key of the existing item is greater than the key of the incomming item 
    //so return true and false otherwise
    if (this->key()>p_sortable->key()) 
    return true;
    else
    return false;
  }
bool TeraSortItem:: operator<(Sortable *p_sortable) //overloading < operator
  {
    //check if the key of the existing item is less than the key of the incomming item 
    //so return true and false otherwise
    if (this->key()<p_sortable->key())
    return true;
    else
    return false;
  }
bool TeraSortItem:: operator>=(Sortable *p_sortable) //overloading >= operator
  {
    //check if the key of the existing item is greater than or equal the key of the incomming item 
    //so return true and false otherwise
    if (this->key()>=p_sortable->key())
    return true;
    else
    return false;
  }
bool TeraSortItem:: operator <= (Sortable * p_sortable)//overloading <= operator
  {
    //check if the key of the existing item is less than or equal the key of the incomming item 
    //so return true and false otherwise
    if (this->key()<=p_sortable->key())
    return true;
    else
    return false;
  }
bool TeraSortItem::operator == (Sortable * p_sortable) //overloading == operator
  {
    //check if the key of the existing item is equal to the key of the incomming item 
    //so return true and false otherwis
    if (this->key()==p_sortable->key())
    return true;
    else
    return false;
  }
bool TeraSortItem::operator != (Sortable * p_sortable) //overloading != operator
  {
    //check if the key of the existing item is not equal to the key of the incomming item 
    //so return true and false otherwise
    if (this->key()!=p_sortable->key())
    return true;
    else
    return false;
  }
uint128_t TeraSortItem::key() // to calc value of key 
{
  //exchange the value of the key of type 8byte into 128 byte but with revere order 
  //then return the value of the k i 128byte 
    uint8_t *v = teraitem->key;
    uint128_t k = 0;
    uint8_t *c = (uint8_t *)&k;
    c[0] = v[9];
    c[1] = v[8];
    c[2] = v[7];
    c[3] = v[6];
    c[4] = v[5];
    c[5] = v[4];
    c[6] = v[3];
    c[7] = v[2];
    c[8] = v[1];
    c[9] = v[0];
    return k;
}
uint128_t TeraSortItem::calckey(uint8_t * ky) // to calc the key value into unit128
{
    //cast the value of 128 byte into 8 byte and then return its value 
    uint8_t *v = ky;
    uint128_t k = 0;
    uint8_t *c = (uint8_t *)&k;
    c[0] = v[9];
    c[1] = v[8];
    c[2] = v[7];
    c[3] = v[6];
    c[4] = v[5];
    c[5] = v[4];
    c[6] = v[3];
    c[7] = v[2];
    c[8] = v[1];
    c[9] = v[0];
    return k;
}


TeraSortItem ::~TeraSortItem() // deconstructor 
{

}

#endif

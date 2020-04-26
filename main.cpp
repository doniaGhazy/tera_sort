#include "TeraSort.hpp"
#include"TeraSortItem.hpp"
#include <string.h>
#include "print.h"
#include "ThreadManager.h"
#include <fstream>
using namespace std;

int main() 
{
    int p_mapper_count;
    int p_reducer_count;
    char* p_input_filename;
    string p_output_filename;
    int percentsamp;
    FILE * pFile;
    pFile = fopen("unsorted-1gb","r");
    cout<<" Enter the number of mappers you want to sort your file :    "<<endl;
    cin>> p_mapper_count;
    cout<<"Enter the number of reducers you want to sort your file:     "<<endl;
    cin>> p_reducer_count;
    cout<<" Enter the percentage (number only ie: 20) of the file you want to take as a sample:     "<<endl;
    cin>> percentsamp;
    std:: ofstream outputfile;
    p_output_filename= "outputfile";
     TeraSort x(pFile,p_output_filename , p_mapper_count, p_reducer_count, percentsamp);
     x.sort(p_mapper_count, p_reducer_count);

     for (int i=0; i<p_mapper_count;i++)
       for (int j=0; j<(x.Mappers[i].number_of_items);j++)
        print_u128_u(x.shuffleBuffer->shuffleBuffers[i]->teradata[i].key[10]);
 return 0;  
}

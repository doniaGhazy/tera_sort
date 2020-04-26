#include "ThreadManager.h"


class MyThread: public Thread 
{
	private:
		int myId;
	public:
		MyThread(int p_myId);
		void * threadMainBody (void * arg);
		~MyThread ();
};

MyThread::MyThread(int p_myId):Thread(){
	myId = p_myId;
}
void * MyThread::threadMainBody (void * arg)
{
	for ( int i = 0 ; i < 1000000; i ++)
		printf ("This is thread # %d -> %d\n",myId,i);
}
MyThread::~MyThread()
{

}


int main ()
{
	ThreadManager threadManager;
	for ( int i = 0 ; i  < 20 ; i ++ )
		threadManager.addThread(new MyThread(i));
	threadManager.startRR();
	threadManager.barrier();
	return 0;
}

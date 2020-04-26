thread_test: thread_test.cpp Thread.cpp ThreadManager.cpp
	g++ thread_test.cpp Thread.cpp ThreadManager.cpp -o thread_test -lpthread

info:
	ps -T -p `ps -ef | grep thread_test | grep -v grep | awk '{print $$2}'` -o pid,tid,class,rtprio,ni,pri,psr,pcpu,stat,wchan:14,comm

clean:
	rm -rf thread_test

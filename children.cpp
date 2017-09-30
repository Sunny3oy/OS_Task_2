//part 1 task 2 by Sunny Mei
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <iostream>
#include <sys/wait.h>
using namespace std;

int main ()
{
	int status;//holds status info
	pid_t pid;//will handle the parent
	int childnum = 2;//fixed variables to control how many child process we want to make, in this case 2
	pid_t pids[2];//will handle the forks that we need to do

	cout<<"I am your father "<<getpid()<<"\n";//to get the parent process id

	for (int i = 0; i<childnum ; i++)//for loop will generate n childs
	{
		if((pids[i] = fork())<0)//does the fork
		{
			cout<<"error\n";//if we get error we go here		
		}
		else if (pids[i] == 0)//else the fork was success, should get 0
		{	//now we are in the child process, the child will run this part while the parent is still doing the for loop
			cout<<"\nI am the "<< i <<" child, my id is "<<getpid()<<"\n";//gets the child id
			cout<<"\nMy parent is "<<getppid()<<"\n";//confirm that the child has the same parent 
			exit(0);//we need to exit here to kill off the child process, we don't want the child to continue the for loop or the while loop
		}
	
	}
	while (childnum>0)//Since all children exit, only the parent will run this part
	{
		pid = waitpid(pids[childnum-1], &status,0);//is needed to wait until the child dies/exit
		cout<<"\nMy child "<<pid<< " has died\n";//gets the pid that the child had
		childnum--;//decrement to exit while loop		
	}

	return 0;
}

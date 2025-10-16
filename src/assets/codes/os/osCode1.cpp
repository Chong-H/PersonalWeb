#include<iostream>
#include<stdio.h>
#include<cstdlib>
#include<unistd.h>
#include<signal.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;
void stop(int signum) {
    if (signum == SIGQUIT) {
        printf("parent received signal SIGQUIT\n");
    } else if(signum == 16) {
	cout<<"process 1 recieved signal 16"<<endl;
        cout<<"child process 1 is killed by parent!"<<endl;
        exit(0);
    }else{
	cout<<"process 2 recieved signal 17"<<endl;
 	cout<<"child process 2 is killed by parent!"<<endl;
        exit(0);
	}
}


int main(void){
	int status[2]; 
	pid_t child1,child2;
	child1=fork();
	if(child1<0){
		cout<<"failed"<<endl;		
	}else if(child1==0){
                cout<<"\ntask 1 start"<<endl;	
		signal(SIGQUIT,SIG_IGN);	
		signal(16,stop);	
		pause();

	}else{//father process
		child2=fork();
		if(child2<0){
		cout<<"failed"<<endl;		
		}else if(child2==0&&child1>=0){//else if(child2==0){ only if child 1>=0
			
			cout<<"\ntask 2 start"<<endl;
			signal(SIGQUIT,SIG_IGN);
			signal(17,stop);

			pause();
		        
		}else{
		signal(SIGQUIT,stop);
		pause();

		kill(child1,16);
		waitpid(child1,&status[0],0);
		kill(child2,17);
		
		
		waitpid(child2,&status[1],0);
		cout<<"\nparent process is killed!"<<endl;
		exit(0);
		}
	}
	
	

	return 0;
}
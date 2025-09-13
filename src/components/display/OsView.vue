<template>
  <div class="project-info">
    <h2>操作系统实验项目</h2>

    <h3>软中断通信实验</h3>
    <p>
      由父进程创建两个子进程，通过终端输入 <code>Crtl+\</code> 组合键向父进程发送 SIGQUIT
      软中断信号。父进程收到信号后，分别向两个子进程发送整数值为 16 和 17
      的软中断信号，子进程收到后终止运行。父进程调用
      <code>wait()</code> 等待两个子进程终止，然后自我终止。
    </p>
    <img class="image" src="@/assets/os2.png" alt="软中断通信实验实验场景" />
    <CollapsibleCodeBlock :code="osCode1" :previewLines="8" />

    <h3>线程同步实验</h3>
    <p>
      编写 Linux 线程程序，利用线程信号量及 PV
      操作实现生产者—消费者同步关系。生产者线程生产产品，消费者线程消费产品，信号量保证仓库容量和互斥访问。
    </p>
    <img class="image" src="@/assets/os3.png" alt="线程同步实验场景" />
    <CollapsibleCodeBlock :code="osCode2" :previewLines="8" />

    <h3>进程调度实验</h3>
    <p>
      在 Linux 下编程实现进程调度策略算法的模拟程序，支持
      FCFS（先到先服务）、RR（轮循）、基于优先级的调度算法。通过输入进程参数，模拟不同调度策略下的执行过程。
    </p>
    <img class="image" src="@/assets/os4r.png" alt="进程调度实验场景" />
    <img class="image" src="@/assets/os4p.png" alt="进程调度实验场景" />
    <img class="image" src="@/assets/os4f.png" alt="进程调度实验场景" />
    <img class="image" src="@/assets/os4e.png" alt="进程调度实验场景" />
    <CollapsibleCodeBlock :code="osCode3" :previewLines="8" />

    <h3>内存管理实验</h3>
    <p>
      在 Linux 下编程实现虚存页面替换算法的模拟程序。根据用户输入参数，随机生成页访问顺序，支持
      OPT、FIFO、LRU 替换算法，并输出页替换流程结果和缺页次数。
    </p>
    <img class="image" src="@/assets/os5f.png" alt="内存管理实验场景" />
    <img class="image" src="@/assets/os5o.png" alt="内存管理实验场景" />
    <img class="image" src="@/assets/os5l.png" alt="内存管理实验场景" />
    <img class="image" src="@/assets/os5e.png" alt="内存管理实验场景" />
    <CollapsibleCodeBlock :code="osCode4" :previewLines="8" />
  </div>
</template>

<script setup lang="ts">
//@ts-ignore
import CollapsibleCodeBlock from './CollapsibleCodeBlock.vue'

const osCode1 = `
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


`

const osCode2 = `
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include<iostream>
#include <chrono>
#include<unistd.h>
#include <sys/wait.h>
#include<time.h>
#include<semaphore.h>


#define INIT_NUM  2  //仓库原有产品数
#define TOTAL_NUM   4 //仓库容量
    using namespace std;


sem_t p_sem,  //仓库空闲货架信号量，为0时说明仓库所有货架已满，停止生产货物
          c_sem,   //货物库存信号量，为0时说明货物已没有库存，停止消费货物
          sh_sem;  //货物操作信号量，放入和取出操作是互斥的原子操作
int buffer=INIT_NUM;

//func:
void *consumer(void *arg);
void *productor(void *arg);
int main() {
	sem_init(&p_sem,0,TOTAL_NUM-INIT_NUM);
	sem_init(&c_sem,0,INIT_NUM);//synchornize
	sem_init(&sh_sem,0,1);//mutual exclusion

	pthread_t t1,t2;
	pthread_create(&t1,NULL,productor,NULL);//thread t1 to produce
	pthread_create(&t2,NULL,consumer,NULL);//thread t2 to consume

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	cout<<"consumer exit!"<<endl;
	
	cout<<"mian exit!"<<endl;
	exit (0);
	
}

void *productor(void *arg){
int i=0;
while(i<3) {
	sleep(0.2);
  sem_wait(&p_sem);
  sem_wait(&sh_sem);
	buffer++;
	cout<<"\nproduce 1,exist"<<buffer<<" now"<<endl;
	i++;
  sem_post(&sh_sem);
  sem_post(&c_sem);
	
	}
cout<<"producer exit!"<<endl;
}

void *consumer(void *arg){
int i=0;
while(buffer>=1) {
	sleep(1);
        sem_wait(&c_sem);
 	sem_wait(&sh_sem);
	buffer--;
	cout<<"\nconsume 1,exist"<<buffer<<" now"<<endl;
	i++;
	sem_post(&sh_sem);
	sem_post(&p_sem);
	
	}
//exit(0);
}
`

const osCode3 = `
#include<iostream>
#include<queue>
#include<fstream>
#include<vector>
#include<stdlib.h>
using namespace std;
ifstream in;
struct pro {
	int i,s,t;
	int p;
	pro(int a,int s1, int b) : i(a),s(s1) ,t(b) {}
};
void printTimeList(int total);
void fifs(vector<pro> pl,vector<pro> rl) ;
void rr(vector<pro> pl,vector<pro> rl) ;//round robin
void p(vector<pro> pl,vector<pro> rl) ;
void dis(int i,int j,vector<pro>pl);
int main() {
	vector<pro> pl,//process list
	       rl;//ready list
	in.open("in.txt");
	int i=1;
	int j=0;

	while(i!=-99) {
		int t,s;
		in>>i;
		if(i==-99)	break;
		in>>s>>t;
		pro pro1(i,s,t);
		pl.push_back(pro1);
		j++;
	}
	int run=1;
	while(run) {
		i=0;

		dis(i,j,pl);
		cout<<"please input choice"<<endl;
		char ch;
		cin>> ch;
		if(ch=='r')  {

			system("clear");
			cout<<"r"<<endl;
			dis(i,j,pl);
			rr(pl,rl);
			//run=0;
			cout<<"\n----------------------------------------------------------------\n";
		}
		if(ch=='f') {
			system("clear");
			cout<<"f"<<endl;
			dis(i,j,pl);

			fifs( pl, rl);
			//run=0;
			cout<<"\n----------------------------------------------------------------\n";

		}
		if(ch=='p') {
			system("clear");
			cout<<"p"<<endl;
			dis(i,j,pl);

			p( pl, rl);
			cout<<"\n----------------------------------------------------------------\n";

			//run=0;
		} else if(ch=='e') {
			run=0;
			cout<<"----------------------\nend\n----------------------------------------------------------------\n";

		}
		//deal

	}
	while(i<j) {
		pl.erase(pl.begin());
		i++;
	}
	return 0;
}
void rr(vector<pro> pl, vector<pro> rl) {
	cout<<"you opted r"<<endl;
	std::vector<std::vector<int>> s;
	int time = 0;

	// process list to ready list
	for (int i = 0; i < pl.size(); i++) {
		if (pl[i].t > 0) {
			rl.push_back(pro(pl[i].i,pl[i].s,pl[i].t));
			std::vector<int> j;
			s.push_back(j);
		}
	}

	// calc time total
	int total = 0;
	for (int i = 0; i < rl.size(); i++) {
		if (rl[i].t > 0) total += rl[i].t;
	}

	// initialize s
	for (int i = 0; i < rl.size(); i++) {
		for (int i1 = 0; i1 < total; i1++) {
			s[i].push_back(0);
		}
	}

	// print time list
	printTimeList(total);

	queue <pro>eq;//execute queue

	// process ready list
	std::vector<bool> st(rl.size(), false); // 记录进程是否已经进入 CPU
	while (time < total ) {
		int flag = 0;
		int flagid = -1;
		for (int i = 0; i < rl.size(); i++) {
			if ((time >= rl[i].s) && (!st[i]) ) {
				flagid = i;
				flag = 1;
				st[i]=1;
				break;
			}
		}
		if (flag != 0) {
			eq.push(rl[flagid]);//in queue

			//往前顶一下
			pro a(0,0,0);
			a = eq.front();
			eq.pop();
			eq.push(a);

			int t=eq.front().i;
			int t11=0;
			if (!eq.empty()) {
				if((eq.front().i==t)&&(t11>0))	break;
				a = eq.front();
				s[a.i - 1][time] = 1;
				rl[a.i - 1].t--; // 减少进程的剩余执行时间
				a.t--;
				eq.front().t--;
				time++;
				t11++;

				//弹出空元素
				a=eq.back();
				if(a.t==0) {
					int sss=a.i;
					while(eq.front().i!=sss) {
						a=eq.front();
						eq.pop();
						eq.push(a);
					}
					a=eq.front();
					eq.pop();
				}
			} else {
				time++;
			}

		} else { // 没有新的进入 CPU
			//do noting

			pro a(0,0,0);
			a=eq.front();
			eq.pop();
			eq.push(a);
//			while(eq.front().t==0) { //find process unfinished execute
//				eq.pop();
//			}
			int t=eq.front().i;
			int t11=0;

			if (!eq.empty()) {
				if((eq.front().i==t)&&(t11>0))	break;
				a = eq.front();
				s[a.i - 1][time] = 1;
				rl[a.i - 1].t--; // 减少进程的剩余执行时间
				eq.front().t--;
				a.t--;
				time++;
				t11++;
			} else {
				time++;
			}
			//弹出空元素
			a=eq.back();
			if(a.t==0) {
				int sss=a.i;
				while(eq.front().i!=sss) {
					a=eq.front();
					eq.pop();
					eq.push(a);
				}
				a=eq.front();
				eq.pop();
			}
		}


	}
	// 打印结果
	for (int ii = 0; ii < s.size(); ii++) {
		cout<<"task "<<ii+1<<" :";
		for (int j = 0; j < s[ii].size(); j++)
			if (s[ii][j] == 1) {
				cout << "#  ";
			} else {
				cout << "   ";
			}
		cout << endl;
	}
}

void p(vector<pro> pl,vector<pro> rl) {//right
	vector<int> pri;
	pri.push_back(rand()%7);
	pri.push_back(rand()%7);
	pri.push_back(rand()%7);
	pri.push_back(rand()%7);
	pri.push_back(rand()%7);
	std::vector<std::vector<int>> s;
	int time = 0;
	cout<<"you opted priority"<<endl;
	// process list to ready list
	for (int i = 0; i < pl.size(); i++) {
		if (pl[i].t > 0) {
			rl.push_back(pro(pl[i].i,pl[i].s,pl[i].t));
			//rl[rl.size()-1].p=pl[i].t;
			rl[rl.size()-1].p=pri[i];
			std::vector<int> j;
			s.push_back(j);
		}
	}
	//print
	cout<<"priority list as follows"<<endl;
	cout<<"taskList: ";
	for(int i=0; i<rl.size(); i++) {
		cout<<rl[i].i<<"  ";
	}
	cout<<endl;
	cout<<"priority: ";
	for(int i=0; i<rl.size(); i++) {
		cout<<rl[i].p<<"  ";
	}
	cout<<endl;

	// calc time total
	int total = 0;
	for (int i = 0; i < rl.size(); i++) {
		if (rl[i].t > 0) total += rl[i].t;
	}

	// initialize s
	for (int i = 0; i < rl.size(); i++) {
		for (int i1 = 0; i1 < total; i1++) {
			s[i].push_back(-999);
		}
	}

	// print time list
	printTimeList(total);

	vector <pro>eq;//execute queue

	// process ready list
	std::vector<bool> st(rl.size(), false); // 记录进程是否已经进入 CPU
	int m=0;
	while (time < total ) {
		int flag0=0;
		for(int i=0; i<eq.size(); i++) {
//			if(eq[i].p==0||eq[i].t==0){
//				flag=0;
//			}

			if(eq[i].p!=0&&eq[i].t!=0) {
				flag0=1;
			}

		}
		if(flag0==0) {
			for(int i=0; i<eq.size(); i++) {
				eq[i].p=pri[i];
			}
		}
		int flag = 0;
		int flagid = -1;

		for (int i = 0; i < rl.size(); i++) {
			if ((time >= rl[i].s) && (!st[i]) ) {
				flagid = i;
				flag = 1;
				st[i]=1;
				break;
			}
		}
		if (flag != 0) {
			eq.push_back(rl[flagid]);//in queue
			s[flagid][time]=eq[eq.size()-1].p-1;
			eq[eq.size()-1].p-=1;
			eq[eq.size()-1].t-=1;
			time++;

		} else { // 没有新的进入 CPU
			//do noting
		}
		pro a(0,0,0);


		for(int i=eq.size()-1; i>0; i--) {
			if((eq[i].t>=1)) m=i;
		}

		for(int i=0; i<eq.size(); i++) {
			if((eq[m].p<=eq[i].p)&&(eq[i].t>=1)) m=i;
		}
		s[m][time]=eq[m].p-1;
		eq[m].p-=1;
		eq[m].t-=1;
		time++;


	}

	// 打印结果
	for (int ii = 0; ii < s.size(); ii++) {
		cout<<"task "<<ii+1<<" :";
		for (int j = 0; j < s[ii].size(); j++)
			if (s[ii][j] != -999) {
//				cout <<s[ii][j]<< "  ";
				cout << "#  ";
			} else {
				cout << "   ";
			}
		cout << endl;
	}
}

void printTimeList(int total) {
	std::cout << "\t";
	for (int i = 0; i < total+1; i++) {
		if (i <= 9) std::cout << i  << "  ";
		else std::cout << i  << " ";
	}
	std::cout << std::endl;
}



void fifs(vector<pro> pl,vector<pro> rl) {
	cout<<"you opted fifs"<<endl;
	int time=0;
	//cout<<"pl.size="<<pl.size();
	for(int i=0; i<pl.size(); i++) {
		if (pl[i].t>0)	rl.push_back(pl[i]);//to ready list
	}
	//process ready list
	int total=0;
	for(int i=0; i<rl.size(); i++) {
		if(rl[i].t>0) total+=rl[i].t;
	}
	cout<<"\t";
	for(int i=0; i<total; i++) {
		if (i<9) cout<<i+1<<"  ";
		if(i>=9)	cout<<i+1<<" ";
	}
	int k=rl.size();
	cout<<endl;
	for(int j=0; j<k; j++) {
		cout<<"task "<<rl[0].i<<" :";
		for(int a=0; a<time; a++) {
			cout<<"   ";//to ready list
		}
		pro pte=rl[0];//process to execute
		for(int s=0; s<pte.t; s++) {
			cout<<"#  ";
			time++;
		}
		cout<<endl;
		rl.erase(rl.begin());
	}
}
void dis(int i,int j,vector<pro>pl) {
	cout<<"Id\t\t"<<"TBegin\t\t"<<"TNeed\t\t"<<endl;
	while(i<j) {
		cout<<pl[i].i<<"\t\t"<<pl[i].s<<"\t\t"<<pl[i].t<<endl;
		i++;
	}
	cout<<endl;
	cout<<"please input choice: r / f / p / e"<<endl;
	cout<<"r:round robin"<<endl;
	cout<<"f:first in first server"<<endl;
	cout<<"p:priority"<<endl;
	cout<<"e:end process"<<endl;
}



`

const osCode4 = `
#include<iostream>
#include<stdlib.h>
#include<vector>
#include<fstream>
#include<time.h>
#define INT_MAX 99999//在Linux中手动定义，Windows中不需要这一句
using namespace std;
struct page {
	int pid;
	int t;//time for each page go to frame(fifo)
	int nttv;//next time to visit （opt）
	int fid=-999;//frame id for pages in
	page(int i,int f):pid(i),fid(f) {
		t=-999;
		nttv=INT_MAX;
	}
};
struct fra { //frame
	int fid;//frame id
	int pid;//frame 对应page id
	fra(int f,int p):fid(f),pid(p) {	}
};
struct pro {
	vector<page> pS;//page sequence
	vector <fra> fS;//frame sequence 
	int x;
	int y;
	vector<int> pgr;//page reference
	pro(int a,int b):x(a),y(b) {
		cout<<"page using sequence: "<<endl;
		for(int i=0; i<3*x; i++) {
			int s=rand()%a;
			pgr.push_back(s);
			cout<<s<<" ";
		}
		for(int i=0; i<b; i++) {
			fS.push_back(fra(i,-999));
		}
		for(int i=0; i<a; i++) {
			pS.push_back(page(i,-999));
		}
	}
};
int pgfault;
//fx
void opt(pro a);
void lru(pro a);
void fifo(pro a);
void pri(pro a);//print
int main(void) {
	ifstream in;
	in.open("in.txt");
    srand(time(NULL));


	int x,y;//page num, frame num
	cout<<"please input x , y"<<endl; 
	in>>x>>y;
	cout<<"x= "<<x<<" ,y= "<<y<<endl;
	pro mpro(x,y);
	cout<<endl;
	pri(mpro);
	cout<<endl;
	int run=1;
	while(run){
		char inn;
		pgfault=0;
		cout<<"please input control method(f,l,o)"<<endl;
		cout<<"f(first in first out) , l(last recently used) , o(optimal) :"<<endl;
		cin>>inn;
		if(inn=='f'){
			fifo (mpro);
			cout<<"\npage fault num="<<pgfault<<endl<<endl;
		}else if(inn=='l'){
			lru (mpro);
						cout<<"\npage fault num="<<pgfault<<endl<<endl;

		}else if(inn=='o'){
			opt (mpro);
						cout<<"\npage fault num="<<pgfault<<endl<<endl;

		}else{
			run=0;
		}
	}
	
	return 0;
}
void pri(pro a) {
	for(int i=0; i<a.fS.size(); i++) {
		if(a.fS[i].pid!=-999) {
			cout<<a.fS[i].pid<<" |";
		}
	}
	cout<<"\b ";
	cout<<endl;
}
void opt(pro a) {
	for(int i=0; i<3*a.x; i++) { //exe
		int flagin=0;
		//the page need is in frame
		for(int k=0; k<a.fS.size(); k++) {
			if(a.pgr[i]==a.fS[k].pid) {
				pri(a);
				flagin=1;
				//a.pS[i对应pid的p].frame
			}
		}

		//not in
		if(flagin==0) {
			pgfault++;
			int flagS=0;// frame have spare place
			int bre=1;//break;
			for(int j=0; j<a.fS.size(); j++) {
				if((a.fS[j].pid==-999)&&(bre==1)) {
					a.fS[j].pid=a.pgr[i];
					pri(a);
					bre=0;
					flagS=1;
					//a.pS[i对应pid的p].frame
				}
			}
			if(flagS==0) { //frame full;realloc
				for(int k=0; k<a.pS.size(); k++) {
					a.pS[k].nttv=INT_MAX;
				}
				for(int j=a.pgr.size()-1; j>i; j--) {//pgr中 find nttv
					for(int k=0; k<a.pS.size(); k++) {
						if(a.pS[k].pid==a.pgr[j]) {
							a.pS[k].nttv=j;
						}
					}
				}
				int k=-1;//最远不用的距离
				int idd=-1;
				for(int j=0; j<a.fS.size(); j++) {//find page to swap
					if(	a.pS[ a.fS[j].pid ].nttv>k ) {
						k=a.pS[ a.fS[j].pid ].nttv;
						idd=j;
					}
				}
						a.fS[idd].pid=a.pgr[i];
				
				for(int k=0; k<a.pS.size(); k++) {
					a.pS[k].nttv=INT_MAX;
				}
				pri(a);
			}
		}
	}
}
void lru(pro a){
	for(int i=0; i<3*a.x; i++) { //exe
		int flagin=0;
		//the page need is in frame
		for(int k=0; k<a.fS.size(); k++) {
			if(a.pgr[i]==a.fS[k].pid) {
				a.pS[a.pgr[i]].t=i;
				pri(a);
				flagin=1;
				
				//a.pS[i对应pid的p].frame
			}
		}

		//not in
		if(flagin==0) {
			pgfault++;
			int flagS=0;// frame have spare place
			int bre=1;//break;
			for(int j=0; j<a.fS.size(); j++) {
				if((a.fS[j].pid==-999)&&(bre==1)) {
					a.fS[j].pid=a.pgr[i];
					pri(a);
					bre=0;
					a.pS[a.pgr[i]].t=i;
					flagS=1;
					//a.pS[i对应pid的p].frame
				}
			}
			if(flagS==0) { //frame full;realloc
				int s=999;int idd=-9;
				for(int j=0;j<a.fS.size();j++){
					if(s>=a.pS[a.fS[j].pid].t){
						s=a.pS[a.fS[j].pid].t;
						idd=j;
						
					}
				}
				//swap
				a.fS[idd].pid=a.pgr[i];

				a.pS[a.pgr[i]].t=i;
				pri(a);
			}
		}
	}
}
void fifo(pro a){
	for(int i=0; i<3*a.x; i++) { //exe
		int flagin=0;
		//the page need is in frame
		for(int k=0; k<a.fS.size(); k++) {
			if(a.pgr[i]==a.fS[k].pid) {
				//a.pS[a.pgr[i]].t=i;
				pri(a);
				flagin=1;
				
				//a.pS[i对应pid的p].frame
			}
		}

		//not in
		if(flagin==0) {
			pgfault++;
			int flagS=0;// frame have spare place
			int bre=1;//break;
			for(int j=0; j<a.fS.size(); j++) {
				if((a.fS[j].pid==-999)&&(bre==1)) {
					a.fS[j].pid=a.pgr[i];
					pri(a);
					bre=0;
					a.pS[a.pgr[i]].t=i;
					flagS=1;
					//a.pS[i对应pid的p].frame
				}
			}
			if(flagS==0) { //frame full;realloc
				int s=999;int idd=-9;
				for(int j=0;j<a.fS.size();j++){
					if(s>=a.pS[a.fS[j].pid].t){
						s=a.pS[a.fS[j].pid].t;
						idd=j;
						
					}
				}
				//swap
				a.fS[idd].pid=a.pgr[i];

				a.pS[a.pgr[i]].t=i;
				pri(a);
			}
		}
	}
	
}

`
</script>

<style scoped>
.project-info {
  background: #fff;
  padding: 2rem;
  border-radius: 12px;
  box-shadow: 0 2px 8px rgba(0, 0, 0, 0.05);
  max-width: 1200px;
  margin: 2rem auto;
}
.project-info h2 {
  font-size: 2.2rem;
  font-weight: bold;
  margin-bottom: 1.5rem;
  color: #409eff;
  text-align: center;
}
.project-info h3 {
  font-size: 1.3rem;
  font-weight: bold;
  margin-top: 2rem;
  margin-bottom: 1rem;
  color: #67c23a;
}
.project-info p,
.project-info ul,
.project-info ol {
  font-size: 1.08rem;
  line-height: 1.8;
  margin-bottom: 0.8rem;
}
.code-block {
  background: #23272e;
  color: #e6e6e6;
  font-size: 0.95rem;
  padding: 1.2rem;
  border-radius: 8px;
  overflow-x: auto;
  margin: 1.5rem 0;
  line-height: 1.6;
  font-family: 'Fira Mono', 'Consolas', 'Menlo', 'Monaco', monospace;
}
.image {
  max-width: 100%;
  height: auto;
  display: block;
  margin: 1rem auto;
  border-radius: 8px;
  box-shadow: 0 2px 8px rgba(64, 158, 255, 0.08);
}
</style>


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
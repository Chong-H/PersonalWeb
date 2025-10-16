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
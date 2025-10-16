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


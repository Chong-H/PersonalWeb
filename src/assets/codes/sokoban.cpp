#include<iostream>
#include<fstream>
#include<queue>
#include<vector>
#include<string.h>
#include<limits.h>
#define maSize 999//棋盘最大容量，边长=log2(maSize) 
#define len 15//棋盘最大变成 
#include<unistd.h>
#include<stdlib.h>
#include<conio.h>
using namespace std;
ifstream in;
ofstream out;
char maze[len * len];

struct point {
	//public:
	int x;
	int y;

	point(): x(0), y(0) {}
	void init(int a, int b);
	point(int a, int b): x(a), y(b) {}
};
void point:: init(int a, int b) {
	x = a;
	y = b;
}
struct state {
	point box;
	point robot;
	int cs;//current steps
	int lb;//lower bound
	char maze[len * len];
	int step;
	state() {	}
	state(point box, point robot, int c, int d) {
		cs = c;
		lb = d;
		state::box.x = box.x, state::box.y = box.y;
		state::robot.x = robot.x;
		state::robot.y = robot.y;
	}
};
struct Compare {
	// 定义比较逻辑，这里以int为例
	bool operator()(const state& a, const state& b) {
		return a.lb > b.lb; // 升序排序（从队首向后看）
	}
};
int pstart_x, pstart_y, bstart_x, bstart_y, target_x, target_y;
void  dfs(point s, point e, char *maze, int row, int col, int &can, vector<point> trace); //robot是否能从s到e点
int fzxj(point b, point robot, int c, int bo, point t, char *maze, int row, int col, int &mycontinue); //box,currntStep,bound,targrt
int lowerbound(point robot, point t) {
	return (robot.x > t.x ? robot.x - t.x : t.x - robot.x) + (robot.y > t.y ? robot.y - t.y : t.y - robot.y);
}
void sortstate(queue<state> &q) {
	vector<state> sort;
	int qsize = q.size();
	while (sort.size() < qsize) {
		sort.push_back(q.front());
		q.pop();
	}

	while (q.size() < qsize) {
		int t = -1;
		int lbb = INT_MAX;
		for (int i = 0; i < sort.size(); i++) {
			if (sort[i].lb <= lbb) {
				lbb = sort[i].lb;
				t = i;
			}
		}
		q.push(sort[t]);
		sort.erase(sort.begin() + t);
	}
}
int visited[len * len];

int main() {
	//read maze ----------------------------------------
	in.open("in.txt");
	out.open("out.txt");
	for (int i = 0; i < len * len; i++) {
		maze[i] = 'u';
	}
	//input
	int n, m;
	in >> n >> m;
	point b, t, s;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			in >> maze[i * m + j];
			if (maze[i * m + j] == 'B') { //box
				bstart_x = i, bstart_y = j; //绠卞瓙
				b.x = i, b.y = j;
			} else if (maze[i * m + j] == 'T') { //target
				target_x = i, target_y = j; //鐩爣浣嶇疆
				t.x = i, t.y = j;
			} else if (maze[i * m + j] == 'S') { //robot start
				pstart_x = i, pstart_y = j; //鏈哄櫒浜?
				s.x = i, s.y = j;
			}
		}
	}
	int dir1 = 999; //direction;
//	while (dir > 0) {
	while(1){ 

		//print maze---------------
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cout << maze[i * m + j] << " ";
			}
			cout << endl;
		}

		//
	//	cout << " \nrecommended trace" << endl;
		int ans = 0;
//	b.x=2;
//	b.y=5;
		memset(visited, 0, sizeof(visited));
		int bo = lowerbound(b, t);
		int mycontinue = 1;
		ans = fzxj( b, s, 0, bo, t, maze, n, m, mycontinue) ;
	//	cout << "\n2022112510" << endl;
		if (ans == -1)cout << "走不通";
		if (ans == -99)cout << "越界到迷宫外";
		if (ans == -999)cout << "目的地/源地址为#";
		cout << "\nstep num = " << ans << endl;
		//end show
		cout << "\nplease input direction(8 for up, 4 for left" <<
		     ",6 for right,2 for down)" << endl;
		     
		     
		int dir = _getch() - '0';
		int newX, newY;
		//int ddx,ddy;
		int dirIndex=0;
		int dx[4] = {0, 0, -1, 1}; // 左、右、上、下
		int dy[4] = {-1, 1, 0, 0}; //  左、右、上、下
		if (dir == 8) {
			newX = s.x + dx[2];
			newY = s.y + dy[2];
			dirIndex=2;
		}//up
		
		else if (dir ==4) {
			newX = s.x + dx[0];    //left
			newY = s.y + dy[0];
			dirIndex=0;
			
		} else if (dir == 6) {
			newX = s.x + dx[1];    //right
			newY = s.y + dy[1];
			dirIndex=1;
		} else if (dir == 2) {
			newX = s.x + dx[3];    //down
			newY = s.y + dy[3];
			dirIndex=3;
		}else{
			cout<<"wrong"<<endl;
		}
		if (maze[newX * m + newY] == '#') {
			cout << "碰壁";   //碰壁#
			cout << "dir=" << dir << endl;
					sleep(0.2);
					system("cls");
		}
		if (maze[newX * m + newY] == 'B') {
			cout << "推箱子";
			if(maze[(newX + dx[dirIndex])*m+newY + dy[dirIndex]]=='.'){
				//TODO
				//char tmp = maze[(newX + dx[dirIndex])*m+newY + dy[dirIndex]];
							maze[(newX + dx[dirIndex])*m+newY + dy[dirIndex]] = 'B';
							maze[s.x*m+s.y] = '.';
							maze[newX*m+newY]='S';
							s.x = newX;
							s.y = newY;
							b.x=newX + dx[dirIndex];
							b.y=newY + dy[dirIndex];
							cout << "dir=" << dir << endl;
								//	sleep(0.1);
									system("cls");
			
			}else if(maze[(newX + dx[dirIndex])*m+newY + dy[dirIndex]]=='T'){
				cout<<"congratulations!"<<endl;
				cout<<"you win"<<endl;
				dir=-999;
				//cout << "dir=" << dir << endl;
				//		sleep(0.2);
						//system("cls");
			}
		}//推箱子B
		if (maze[newX * m + newY] == 'T' || maze[newX * m + newY] == '.') {
			cout << "移动";
			char tmp = maze[newX * m + newY];
			maze[newX * m + newY] = maze[s.x * m + s.y];
			maze[s.x * m + s.y] = tmp;
			s.x = newX;
			s.y = newY;
			
			cout << "dir=" << dir << endl;
					//sleep(0.1);
					system("cls");
		}//空* 或者 目标T
		
	}
	//
	return 0;
}

//	     box ,   robot		  currentStep,   bound,  target ,maze       rowNum  colNum
int fzxj(point b, point robot, int c,			int bo, point t, char *maze, int row, int col, int &mycontinue) {
	//init check
	//end point 不合法
	if ((b.x * col) + b.y > row * col || (b.x * col) + b.y < 0) {
		cout << "over matrix"; //越界
		return -99;
	}
	if ((maze[(b.x)*col + b.y] == '#')) {
		return -999;   //走不通
	}
	//start point 不合法
	if ((t.x * col) + t.y > row * col || (t.x * col) + t.y < 0) {
		cout << "over matrix"; //越界
		return -99;
	}
	if ((maze[(t.x)*col + t.y] == '#')) {
		return -999;   //走不通
	}
	//
	if (lowerbound(b, t) == 0) {

		cout << "last state:\n(" << b.x << "," << b.y << c << '0' << ")" << endl;
		mycontinue = 0;
		return 0;//找到最优方案
	}
	vector<point >trace;
	int minStep = INT_MAX;
	bo = lowerbound(b, t);
	state st(b, robot, c, bo); //box, robot, step, bound

	//state queue
	queue<state> q;
	//priority queue
	std::priority_queue<state, std::vector<state>, Compare> pq;
	q.push(st);
	pq.push(st);
	int flag1 = 1;
	visited[(st.box.x)*col + st.box.y] = 1;
	cout << "break 0 \n";
	while (flag1 && mycontinue) {
		if (pq.size() == 0) {
			flag1 = 0;
			return -1;
		}//都不行时退出}
		state qbegin = pq.top();
		if (lowerbound(qbegin.box, t) == 0) {
			mycontinue = 0;
			cout << "\nlast state:\n(" << qbegin.box.x << "," << qbegin.box.y << "," << qbegin.cs << "," << '0' << ")" << endl;
			return qbegin.cs;//找到最优方案
		}
		pq.pop();
		//cout<<"prepareToGo ";
		cout << qbegin.cs << " " << "(" << qbegin.box.x << "," << qbegin.box.y << " ," << qbegin.cs << "," << lowerbound(qbegin.box, t) << ")\t可选的方向:\t无";

		//------------------------------------------------------------------------------------------------
		int dx[4] = {0, 0, -1, 1}; // 左、右、上、下
		int dy[4] = {-1, 1, 0, 0}; //  左、右、上、下
		// 遍历所有可能的方向
		for (int dir = 0; dir < 4; dir++) {
			// 计算新位置
			int new_x = qbegin.box.x + dx[dir];
			int new_y = qbegin.box.y + dy[dir];

			// 检查新位置是否在迷宫内
			if (new_x >= 0 && new_x < row && new_y >= 0 && new_y < col) {
				// 检查新位置是否是可通行的（不是墙壁或障碍物）
				if (maze[new_x * col + new_y] == '.' || maze[new_x * col + new_y] == 'T' || maze[new_x * col + new_y] == 'B') {
					// 检查机器人是否可以从当前位置移动到新位置
					int cancan = 0;
					point new_box_pos(new_x, new_y);
					point new_robot_pos(qbegin.box.x, qbegin.box.y); // 假设机器人移动到箱子原来的位置
					dfs(qbegin.robot, point(qbegin.box.x - dx[dir], qbegin.box.y - dy[dir]), maze, row, col, cancan, trace);

					if (visited[(new_x)*col + new_y] == 1) {
						cancan = 0;
					}
					if (cancan == 1) {
						// 如果可以移动，创建新状态并将其加入队列
						state new_state(new_box_pos, new_robot_pos, qbegin.cs + 1, lowerbound(new_box_pos, t));
						pq.push(new_state);
						visited[new_x * col + new_y] = 1;
						// 打印移动方向，实际使用时可以去掉或替换为其他形式的输出
						switch (dir) {
							case 0:
								cout << "\bleft ";
								break;
							case 1:
								cout << "\bright ";
								break;
							case 2:
								cout << "\bup ";
								break;
							case 3:
								cout << "\bdown ";
								break;
						}
						cout << "(" << new_state.box.x << "," << new_state.box.y << ")\t";
					}
				}
			}
		}
		cout << endl;

	}
	return -1;
//q.push();
}

void  dfs(point s, point e, char *maze, int row, int col, int &can, vector<point> trace) {

	//end point 不合法
	if ((e.x * col) + e.y > row * col || (e.x * col) + e.y < 0) {
		cout << "over matrix"; //越界
	}
	if ((maze[(e.x)*col + e.y] == '#') || (maze[(s.x)*col + s.y] == 'B')) {} //走不通
	//start point 不合法
	if ((s.x * col) + s.y > row * col || (s.x * col) + s.y < 0) {
		cout << "over matrix"; //越界
	}
	if ((maze[(s.x)*col + s.y] == '#') || (maze[(s.x)*col + s.y] == 'B')) {} //走不通
	//合法
	trace.push_back(s);
	if (s.x == e.x && s.y == e.y) {
		can = 1;
		//cout<<"\nfound--------------------------------------"<<endl;
		while (!trace.empty()) {
			//cout<<"("<<trace[0].x<<","<< trace[0].y <<") ";
			trace.erase(trace.begin());
		}
		return ;
	}
	if (((maze[(s.x)*col + s.y - 1] == '.') || (maze[(s.x)*col + s.y - 1] == 'S') || (maze[(s.x)*col + s.y - 1] == 'T')) && (((s.x)*col + s.y - 1) < row * col) && (((s.x)*col + s.y - 1) >= 0)) {
		//can go left
		char retu = (maze[(s.x) * col + s.y - 1]);
		maze[(s.x)*col + s.y - 1] = '#';
		//trace.push_back(point(s.x,s.y-1));

		dfs(point(s.x, s.y - 1), e, maze, row, col, can, trace);

		maze[(s.x)*col + s.y - 1] = retu;
	}
	if (((maze[(s.x)*col + s.y + 1] == '.') || (maze[(s.x)*col + s.y + 1] == 'S') || (maze[(s.x)*col + s.y + 1] == 'T')) && (((s.x)*col + s.y + 1) < row * col) && (((s.x)*col + s.y + 1) >= 0)) {
		//can go right
		char retu = (maze[(s.x) * col + s.y + 1]);
		maze[(s.x)*col + s.y + 1] = '#';
		//trace.push_back(point(s.x,s.y+1));

		dfs(point(s.x, s.y + 1), e, maze, row, col, can, trace);

		maze[(s.x)*col + s.y + 1] = retu;
	}
	if (((maze[(s.x - 1)*col + s.y] == '.') || (maze[(s.x - 1)*col + s.y] == 'S') || (maze[(s.x - 1)*col + s.y] == 'T')) && (((s.x - 1)*col + s.y) < row * col) && (((s.x - 1)*col + s.y) >= 0)) {
		//can go up
		char retu = (maze[(s.x - 1) * col + s.y]);
		maze[(s.x - 1)*col + s.y] = '#';

		//trace.push_back(point(s.x-1,s.y));

		dfs(point(s.x - 1, s.y), e, maze, row, col, can, trace);

		maze[(s.x - 1)*col + s.y] = retu;
	}
	if (((maze[(s.x + 1)*col + s.y] == '.') || (maze[(s.x + 1)*col + s.y] == 'S') || (maze[(s.x + 1)*col + s.y] == 'T')) && (((s.x + 1)*col + s.y) < row * col) && (((s.x + 1)*col + s.y) >= 0)) {
		//can go right
		char retu = (maze[(s.x + 1) * col + s.y]);
		maze[(s.x + 1)*col + s.y] = '#';
		//trace.push_back(point(s.x+1,s.y));

		dfs(point(s.x + 1, s.y), e, maze, row, col, can, trace);

		maze[(s.x + 1)*col + s.y] = retu;

	}
	trace.pop_back();
}
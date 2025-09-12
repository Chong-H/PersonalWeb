<template>
  <div class="project-info">
    <h2>ProjectName：Sokoban推箱子游戏</h2>
    <h3>项目简介</h3>
    <p>
      Sokoban（推箱子）是一款经典的益智游戏，本项目实现了自动求解最优路径的功能。除分支限界算法外，核心还深度依赖A*算法（启发式搜索），并辅助使用DFS（深度优先搜索）进行可行性校验。
    </p>
    <h3>核心算法定位：分支限界 + A*算法</h3>
    <p>
      推箱子的最优路径搜索采用分支限界算法结合A*启发式搜索。<br />
      <strong>分支限界：</strong
      >通过优先队列管理待探索状态，利用“限界”剪去不可能找到最优解的分支，避免无效搜索。<br />
      <strong>A*算法：</strong>核心是f(n) = g(n) +
      h(n)，其中g(n)为已走步数，h(n)为箱子到目标的曼哈顿距离。优先队列按总代价估值排序，确保每次优先探索最有希望的状态。
    </p>
    <h3>辅助算法：DFS可行性校验</h3>
    <p>
      DFS用于校验机器人能否到达推箱子所需的位置（发力点），只有可达时才允许推动箱子。有效剪枝，提升搜索效率。
    </p>
    <h3>算法流程简述</h3>
    <ol>
      <li>初始化地图，确定箱子、机器人、目标位置。</li>
      <li>计算初始状态估值，加入优先队列。</li>
      <li>循环：每次取出估值最小状态，若箱子到达目标则返回步数。</li>
      <li>遍历四个方向，尝试推动箱子，DFS校验机器人可达性。</li>
      <li>有效新状态加入队列，已访问位置剪枝。</li>
      <li>队列空则无解。</li>
    </ol>
    <h3>关键函数与算法对应关系</h3>
    <table class="algo-table">
      <tr>
        <th>函数名</th>
        <th>核心作用</th>
        <th>依赖算法</th>
      </tr>
      <tr>
        <td>fzxj</td>
        <td>最优路径搜索（主函数）</td>
        <td>分支限界 + A*</td>
      </tr>
      <tr>
        <td>lowerbound</td>
        <td>计算启发式估值（曼哈顿距离）</td>
        <td>A* 启发函数</td>
      </tr>
      <tr>
        <td>dfs</td>
        <td>机器人移动可行性校验</td>
        <td>DFS（深度优先）</td>
      </tr>
      <tr>
        <td>Compare</td>
        <td>优先队列排序规则</td>
        <td>A* 估值排序</td>
      </tr>
      <tr>
        <td>visited</td>
        <td>箱子位置去重</td>
        <td>分支限界剪枝</td>
      </tr>
    </table>
    <h3>结论</h3>
    <p>
      本项目通过分支限界算法与A*启发式搜索结合，配合DFS可行性校验，实现了高效且准确的推箱子最优解搜索。分支限界负责状态管理与剪枝，A*引导搜索方向，DFS辅助校验，有效提升了算法性能和游戏体验。
    </p>
    <h3>预测路径（程序运行截图，其中B是box,S是人，T是目标位置）</h3>
    <img class="image" src="@/assets/sokoban.png" alt="推箱子游戏界面截图" />
    <h3>部分核心代码展示（C++）</h3>
    <CollapsibleCodeBlock :code="codeSokoban" :previewLines="8" />
  </div>
</template>

<script setup lang="ts">
// @ts-ignore   忽略这一行的类型检查。
import CollapsibleCodeBlock from './CollapsibleCodeBlock.vue'
const codeSokoban = `

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
.project-info ol {
  font-size: 1.08rem;
  line-height: 1.8;
  margin-bottom: 0.8rem;
}
.algo-table {
  width: 100%;
  border-collapse: collapse;
  margin: 1.2rem 0;
  font-size: 1rem;
}
.algo-table th,
.algo-table td {
  border: 1px solid #e0e0e0;
  padding: 0.5em 1em;
  text-align: left;
}
.algo-table th {
  background: #f5f7fa;
  color: #409eff;
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
</style>

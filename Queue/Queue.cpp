#include"Queue.h"

/*
* 循环分配器
	RoundRobin{
		Queue Q(clients);
		while(!ServiceClosed()){
			e = Q.dequeue(); // 队首客户出队
			serve(e);  // 服务该客户
			Q.enqueue(e);  // 重新入队
		}
	}
*/

/*
	银行服务模拟
*/
struct Customer {
	int Window; // 该顾客所属窗口
	unsigned int time;  // 服务时间
};

// 查找最短队列
int bestWindows(Queue<Customer> windows[], int nWin) {
	int minSize = windows[0].size(); 
	int optWin = 0;
	for (int i = 1; i < nWin; ++i) {
		if (minSize > windows[i].size())
		{
			minSize = windows[i].size();
			optWin = 1;
		}
	}
	return optWin;
}

// 模拟银行服务时间
void simulate(int nWin, int ServTime) {
	Queue<Customer>* Windows = new Queue<Customer>[nWin];  // 为每一个窗口都创建一个队列
	for (int now = 0; now < ServTime; now++) {
		if (rand() % (1 + nWin)) {  // 新顾客以该概率到达
			Customer c; c.time = 1 + rand() % 98;  // 该顾客服务时间随机确定
			c.Window = bestWindows(Windows, nWin);
			Windows[c.Window].enqueue(c);  // 新顾客添加到队列中
		}
	}
	for (int i = 0; i < nWin; i++) {
		if (!Windows[i].empty()) {
			if (--Windows[i].front().time <= 0) {
				Windows[i].dequeue();
			}
		}
	}
	delete[] Windows;
}


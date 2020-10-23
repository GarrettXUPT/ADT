#include"Queue.h"

/*
* ѭ��������
	RoundRobin{
		Queue Q(clients);
		while(!ServiceClosed()){
			e = Q.dequeue(); // ���׿ͻ�����
			serve(e);  // ����ÿͻ�
			Q.enqueue(e);  // �������
		}
	}
*/

/*
	���з���ģ��
*/
struct Customer {
	int Window; // �ù˿���������
	unsigned int time;  // ����ʱ��
};

// ������̶���
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

// ģ�����з���ʱ��
void simulate(int nWin, int ServTime) {
	Queue<Customer>* Windows = new Queue<Customer>[nWin];  // Ϊÿһ�����ڶ�����һ������
	for (int now = 0; now < ServTime; now++) {
		if (rand() % (1 + nWin)) {  // �¹˿��Ըø��ʵ���
			Customer c; c.time = 1 + rand() % 98;  // �ù˿ͷ���ʱ�����ȷ��
			c.Window = bestWindows(Windows, nWin);
			Windows[c.Window].enqueue(c);  // �¹˿���ӵ�������
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


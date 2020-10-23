#include"Stack.h"

template<typename T>
void Stack<T>::push(T const& e) {
	Vector<T>::insert(size(), e);
}

template<typename T>
T Stack<T>::pop() {
	return Vector<T>::remove(size() - 1);
}

template<typename T>
T& Stack<T>::top() {
	return (*this)[size() - 1];
}

template<typename T>
int Stack<T>::size() {
	return Vector<T>::size();
}

template<typename T>
bool Stack<T>::empty() {
	return size() == 0;
}

/*
	进制转化
	任给十进制整数n，将其转化为w进制的表示形式
*/

// 递归形式实现
void convert1(Stack<char>& S, __int64 n, int base) {  // 十进制n到base进制的转换
	static char digit[] = { '0', '1', '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9'
							, 'A' , 'B' , 'C' , 'D' , 'E' , 'F' };
	if (n > 0) {
		S.push(digit[n % base]);  // 输出低位
		convert1(S, n / base, base);   // 通过递归得到所有的更高位
	}
}

// 迭代形式实现
template<typename T>
void convert2(Stack<T>& S, __int64 n, int base) { // 十进制n到base进制的转换
	static char digit[] = { '0', '1', '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9'
							, 'A' , 'B' , 'C' , 'D' , 'E' , 'F' };
	while (n > 0) {
		int reminder = (int)(n % base);
		S.push(reminder);  // 由低到高压入栈中
		n /= base;
	}
}

/*
	括号匹配
*/
bool paren(const char exp[], int lo, int hi) {
	Stack<char> S;  // 使用栈记录已发现但是尚未进行匹配的左括号
	for (int i = 0; exp[i]; ++i) {
		switch (exp[i]){
		case '(': case '[':case'{': S.push(exp[i]); break;
		case ')':if ((S.empty() || ('(' != S.pop()))) return false; break;
		case ']':if ((S.empty() || ('[' != S.pop()))) return false; break;
		case '}':if ((S.empty() || ('{' != S.pop()))) return false; break;
		default:  break;  // 忽略非括号字符
		}
	}
	return S.empty();  // 若为空，则表示匹配完成，若不为空，则说明括号不匹配
}

// 皇后问题
struct Queen {  // 皇后类
	int x, y;
	Queen(int xx = 0, int yy = 0) : x(xx), y(yy) {};
	bool operator==(Queen const& q) {  // 检测皇后之间可能会发生的冲突
		return (x == q.x) || (y == q.y) || (x + y == q.x + q.y) || (x - y == q.x - q.y);
	}
	bool operator != (Queen const& q) { return !(*this == q); }  // 重载不等运算符
};

// 算法实现
int nCheck = 0;  int nsolu = 0;
void placeQueens(int N) {
	Stack<Queen> solu;
	Queen q(0, 0);
	do {
		if (N <= solu.size() || N <= q.y) {  // 若已出界，则回溯上一列
			q = solu.pop(); q.y++;
		}
		else
		{
			while ((q.y < N) && (0 <= solu.find(q, 0, solu.size()))) {  // 与已经放入的皇后进行对比
				q.y++; nCheck++;  // 尝试找到可摆放皇后的一列
			}
			if (N > q.y) {  // 若存在可摆放位置
				solu.push(q);
				if (N <= solu.size()) nsolu++;  // 若部分解已经成为全局解，则通过nsolu进行计数
				q.x++; q.y = 0;  // 转入下一行，试探下一个皇后
			}
		}
	} while ((0 < q.x) || (q.y < N));  // 所有分支被穷举或者剪枝，算法结束
}

/*
	迷宫寻径问题
*/
typedef enum{AVAILABLE, ROUTE, BACKTRACKED, WALL} Status;  // 迷宫单元的状态
typedef enum{UNKNOW, EAST, SOUTH, WEST, NORTH, NO_WAY} ESWN;  // 单元的相对邻接方向
#define LABY_WAY 24  // 最大迷宫尺寸

ESWN nextESWN(ESWN eswn) { return ESWN(eswn + 1); }

struct Cell {  // 迷宫结点
	int x, y; Status status;
	ESWN incoming, outgoing;  // 进入方向、走出方向
};

Cell laby[LABY_WAY][LABY_WAY];

// 邻格查询,反复确认当前节点的相邻接点
Cell* neighbor(Cell* cell) {  // 查询当前位置相邻接点
	switch (cell->outgoing) {
	case EAST:return cell + LABY_WAY;  // 向东
	case SOUTH: return cell + 1;  // 向南
	case WEST:return cell - LABY_WAY;  // 向西
	case NORTH: return cell - 1;  // 向北
	default:break;
	}
}

// 邻格接入,确认相邻节点可用以后，向前试探一步，同时路径延长一单元
Cell* advance(Cell* cell) {
	Cell* next;
	switch (cell->outgoing) {
	case EAST: next = cell + LABY_WAY; next->incoming = WEST;  // 现结点为西，那么说明源节点的出为动
	case NORTH: next = cell + 1; next->incoming = SOUTH;
	case WEST: next = cell - LABY_WAY; next->incoming = EAST;
	case SOUTH:next = cell - 1; next->incoming = NORTH;
	default:break;
	}
	return next;
}

// 算法实现
bool labyinth(Cell laby[LABY_WAY][LABY_WAY], Cell* s, Cell* t) {
	if ((AVAILABLE != s->status) || (AVAILABLE != t->status)) return false;  // //首先，起点和终点必须是能访问的
	Stack<Cell*> path;  // 使用栈记录通路
	s->incoming = UNKNOW; s->status = ROUTE; path.push(s);  // 起点  
	do {
		Cell* c = path.top();  // 检查当前栈顶
		if (c == t) return true;
		while (NO_WAY > (c->outgoing = nextESWN(c->outgoing))) {  // 注意检查所有方向
			if (AVAILABLE == neighbor(c)->status) break;  // 试图找到尚未探索的方向
		}
		if (NO_WAY <= c->outgoing) {  // 若所有方向都检查过了都不行，那么回溯一步
			c->status = BACKTRACKED; c = path.pop();
		}
		else  // 向前试探一步
		{
			path.push(c = advance(c));  //  //将c根据前面试探可行的方向移动之后，将移动后的c入栈（此时的C已经是一个新的cell指针了，没有指向之前的栈顶元素了
			c->outgoing = UNKNOW;  //新的c的出方向必然为未知
			c->status = ROUTE;  // 进入路径试探状态
		}
	} while (!path.empty());
	return false;
}


int main() {
	Stack<int> stak;
	convert2(stak, 6, 2);
	int length = stak.size();
	for (int i = 0; i < length; ++i) {
		cout << stak.pop() << endl;
	}
	return 0;
}
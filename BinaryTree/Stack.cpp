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
	����ת��
	�θ�ʮ��������n������ת��Ϊw���Ƶı�ʾ��ʽ
*/

// �ݹ���ʽʵ��
void convert1(Stack<char>& S, __int64 n, int base) {  // ʮ����n��base���Ƶ�ת��
	static char digit[] = { '0', '1', '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9'
							, 'A' , 'B' , 'C' , 'D' , 'E' , 'F' };
	if (n > 0) {
		S.push(digit[n % base]);  // �����λ
		convert1(S, n / base, base);   // ͨ���ݹ�õ����еĸ���λ
	}
}

// ������ʽʵ��
template<typename T>
void convert2(Stack<T>& S, __int64 n, int base) { // ʮ����n��base���Ƶ�ת��
	static char digit[] = { '0', '1', '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9'
							, 'A' , 'B' , 'C' , 'D' , 'E' , 'F' };
	while (n > 0) {
		int reminder = (int)(n % base);
		S.push(reminder);  // �ɵ͵���ѹ��ջ��
		n /= base;
	}
}

/*
	����ƥ��
*/
bool paren(const char exp[], int lo, int hi) {
	Stack<char> S;  // ʹ��ջ��¼�ѷ��ֵ�����δ����ƥ���������
	for (int i = 0; exp[i]; ++i) {
		switch (exp[i]){
		case '(': case '[':case'{': S.push(exp[i]); break;
		case ')':if ((S.empty() || ('(' != S.pop()))) return false; break;
		case ']':if ((S.empty() || ('[' != S.pop()))) return false; break;
		case '}':if ((S.empty() || ('{' != S.pop()))) return false; break;
		default:  break;  // ���Է������ַ�
		}
	}
	return S.empty();  // ��Ϊ�գ����ʾƥ����ɣ�����Ϊ�գ���˵�����Ų�ƥ��
}

// �ʺ�����
struct Queen {  // �ʺ���
	int x, y;
	Queen(int xx = 0, int yy = 0) : x(xx), y(yy) {};
	bool operator==(Queen const& q) {  // ���ʺ�֮����ܻᷢ���ĳ�ͻ
		return (x == q.x) || (y == q.y) || (x + y == q.x + q.y) || (x - y == q.x - q.y);
	}
	bool operator != (Queen const& q) { return !(*this == q); }  // ���ز��������
};

// �㷨ʵ��
int nCheck = 0;  int nsolu = 0;
void placeQueens(int N) {
	Stack<Queen> solu;
	Queen q(0, 0);
	do {
		if (N <= solu.size() || N <= q.y) {  // ���ѳ��磬�������һ��
			q = solu.pop(); q.y++;
		}
		else
		{
			while ((q.y < N) && (0 <= solu.find(q, 0, solu.size()))) {  // ���Ѿ�����Ļʺ���жԱ�
				q.y++; nCheck++;  // �����ҵ��ɰڷŻʺ��һ��
			}
			if (N > q.y) {  // �����ڿɰڷ�λ��
				solu.push(q);
				if (N <= solu.size()) nsolu++;  // �����ֽ��Ѿ���Ϊȫ�ֽ⣬��ͨ��nsolu���м���
				q.x++; q.y = 0;  // ת����һ�У���̽��һ���ʺ�
			}
		}
	} while ((0 < q.x) || (q.y < N));  // ���з�֧����ٻ��߼�֦���㷨����
}

/*
	�Թ�Ѱ������
*/
typedef enum{AVAILABLE, ROUTE, BACKTRACKED, WALL} Status;  // �Թ���Ԫ��״̬
typedef enum{UNKNOW, EAST, SOUTH, WEST, NORTH, NO_WAY} ESWN;  // ��Ԫ������ڽӷ���
#define LABY_WAY 24  // ����Թ��ߴ�

ESWN nextESWN(ESWN eswn) { return ESWN(eswn + 1); }

struct Cell {  // �Թ����
	int x, y; Status status;
	ESWN incoming, outgoing;  // ���뷽���߳�����
};

Cell laby[LABY_WAY][LABY_WAY];

// �ڸ��ѯ,����ȷ�ϵ�ǰ�ڵ�����ڽӵ�
Cell* neighbor(Cell* cell) {  // ��ѯ��ǰλ�����ڽӵ�
	switch (cell->outgoing) {
	case EAST:return cell + LABY_WAY;  // ��
	case SOUTH: return cell + 1;  // ����
	case WEST:return cell - LABY_WAY;  // ����
	case NORTH: return cell - 1;  // ��
	default:break;
	}
}

// �ڸ����,ȷ�����ڽڵ�����Ժ���ǰ��̽һ����ͬʱ·���ӳ�һ��Ԫ
Cell* advance(Cell* cell) {
	Cell* next;
	switch (cell->outgoing) {
	case EAST: next = cell + LABY_WAY; next->incoming = WEST;  // �ֽ��Ϊ������ô˵��Դ�ڵ�ĳ�Ϊ��
	case NORTH: next = cell + 1; next->incoming = SOUTH;
	case WEST: next = cell - LABY_WAY; next->incoming = EAST;
	case SOUTH:next = cell - 1; next->incoming = NORTH;
	default:break;
	}
	return next;
}

// �㷨ʵ��
bool labyinth(Cell laby[LABY_WAY][LABY_WAY], Cell* s, Cell* t) {
	if ((AVAILABLE != s->status) || (AVAILABLE != t->status)) return false;  // //���ȣ������յ�������ܷ��ʵ�
	Stack<Cell*> path;  // ʹ��ջ��¼ͨ·
	s->incoming = UNKNOW; s->status = ROUTE; path.push(s);  // ���  
	do {
		Cell* c = path.top();  // ��鵱ǰջ��
		if (c == t) return true;
		while (NO_WAY > (c->outgoing = nextESWN(c->outgoing))) {  // ע�������з���
			if (AVAILABLE == neighbor(c)->status) break;  // ��ͼ�ҵ���δ̽���ķ���
		}
		if (NO_WAY <= c->outgoing) {  // �����з��򶼼����˶����У���ô����һ��
			c->status = BACKTRACKED; c = path.pop();
		}
		else  // ��ǰ��̽һ��
		{
			path.push(c = advance(c));  //  //��c����ǰ����̽���еķ����ƶ�֮�󣬽��ƶ����c��ջ����ʱ��C�Ѿ���һ���µ�cellָ���ˣ�û��ָ��֮ǰ��ջ��Ԫ����
			c->outgoing = UNKNOW;  //�µ�c�ĳ������ȻΪδ֪
			c->status = ROUTE;  // ����·����̽״̬
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
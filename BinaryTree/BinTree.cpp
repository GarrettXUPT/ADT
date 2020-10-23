#include"BinTree.h"

/*
	�������ߣ����нڵ���ȵ����ֵΪ����
	������xΪ���ڵ������
*/
template<typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x) {
	return x->height = 1 + max(stature(x->lChild), stature(x->rChild));
}

/*
	����x��㼰�����Ƚ�������
*/
template<typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x) {
	while (x) {
		updateHeight(x);
		x = x->parent;
	}
}

/*
	����������������Լ���Ϊ���ڵ�
*/
template<typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e) {
	_size = 1;
	return _root = new BinNode(e);  // ��e��Ϊ���ڵ���뵽�յĶ�������
}

/*
	������xΪ���ڵ�����ӽڵ�
*/
template<typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e) {
	_size++;
	x->insertAsLC(e);
	updateHeightAbove(x);
	return x->lChild;
}

/*
	������xΪ���ڵ�����ӽڵ�
*/
template<typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e) {
	_size++;
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->rChild;
}

/*
	����s����Ϊx������������
*/
template<typename T>
BinNodePosi(T) BinTree<T>::attachAsLc(BinNodePosi(T) x, BinTree<T>* s) {  // Ĭ��x��û�����ӽڵ�
	if (x->lChild = s->_root) x->lChild->parent = x;  // ֱ�ӽ���
	_size += s->size; updateHeightAbove(x);  // ����ȫ����ģ��x�������ȵĸ߶�
	// ����s�����ͷ�
	s->_root = nullptr; s->_size = 0; release(s); s = nullptr;
	return x;  // ���ؽ���λ��
}

/*
	����s����Ϊx�����������в���
*/
template<typename T>
BinNodePosi(T) BinTree<T>::attachAsRc(BinNodePosi(T) x, BinTree<T>* s) {
	if (x->rChild = s->_root) x->rChild->parent = x;  // ֱ�ӽ���
	_size = s->size; updateHeightAbove(x);  // ����ȫ����ģ��x�������ȵĸ߶�
	s->_root = nullptr; s->_size = 0; release(s); s = nullptr;
	return x;  // ���ؽ���λ��
}


/*
	ɾ����xΪ���ڵ������������ֻɾ��x���
*/
template<typename T>
int BinTree<T>::remove(BinNodePosi(T) x) {
	FromParentTo(*x) = nullptr; // �ж����Ը��ڵ��ָ��
	updateHeightAbove(x->parent);  // �������ȸ߶�
	int n = removeAt(x);
	_size -= n;
	return n;
}

/*
	����ɾ����xΪ���ڵ����������
*/
template<typename T>
static int BinTree<T>::removeAt(BinNodePosi(T) x) {
	if (!x) return 0;  // �ݹ��Ϊ��������x���������ĸ��ڵ㣬��ֱ�ӷ���
	int n = 1 + removeAt(x->lChild) + remove(x->rChild);  // �ݹ�ɾ��
	release(x->data); release(x);  // �ͷŽ��x�е����ݼ��ڵ㱾��
	return n;
}

// ��������,�������ӵ�ǰ���з�������������װΪһ�Ŷ������������з���
template<typename T>
BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x) {
	FromParentTo(*x) = nullptr;  // �ж����Ը��ڵ��ָ�룬�жϸ��ڵ�ָ������ָ�룬��û���ͷ���
	updateHeightAbove(x->parent);  // ����ԭ�����������ȵĸ߶�
	BinTree<T>* s = new BinTree<T>; s->_root = x; x->parent = nullptr; // xΪ�����ĸ��ڵ�
	s->_size = x->size();  _size -= s->_size;   // ���¹�ģ
	return s;
}

// ǰ�����,�ݹ�ģʽ
template<typename T>
template<typename VST>
void BinTree<T>::travPre_R(BinNodePosi(T) x, VST& visit) {
	if (!x) return;  // ��������
	visit(x->data);
	travPre_R(x->lChild, visit);
}

// �ǵݹ�ģʽ
template<typename T>
template<typename VST>
void BinTree<T>::visitAlongLeftBranch(BinNodePosi(T) x, VST& visit, Stack<BinNodePosi(T)>& s) {
	while (x) {
		visit(x->data);  // ���ʵ�ǰ���
		s.push(x->rChild);  // ���Һ����ݴ�
		x = x->lChild;  // �������֧����һ��
	}
}

template<typename T>
template<typename VST>
void BinTree<T>::travPre_N(BinNodePosi(T) x, VST& visit) {
	Stack<BinNodePosi(T)> s;
	while (true) {
		visitAlongLeftBranch(x, visit, s);
		if (s.empty()) break;  // ֱ��ջ��
		x = s.pop();  // ������һ�������
	}
}

template<typename T>
template<typename VST>
void BinTree<T>::travIn_R(BinNodePosi(T) x, VST& visit) {
	if (!x) return;
	travIn_R(x->lChild, visit);
	visit(x->data);
	travIn_R(x->rChild, visit);
}

// ����������ǵݹ��
template<typename T>
template< typename VST>
void BinTree<T>::travIn(BinNodePosi(T) x, VST& visit) {
	bool backtrack = false;
	while (true) {
		if (!backtrack && HasLChild(*x)) x = x->lChild;  // �������������Ҳ��ǻ����γɵģ���ô����������������ҵ�������������Ľ��
		else {  // �������������߸ոջ���
			visit(x->data);
			if (HasRChild(*x)) {  // �������������������������
				x = x->rChild;  // ������������������
				backtrack = false;
			}
			else {  // ��û������������Ѱ��x����һ��ֱ�ӽ��,�ҽ����ݱ�־��
				if (!x = x->succ()) break;
				backtrack = true;  // ���ݱ�־��
			}
		}
	}
}

template<typename T>
template<typename VST>
void BinTree<T>::travPost_R(BinNodePosi(T) x, VST& visit) {
	if (!x) return;
	travPost_R(x->lChild, visit);
	travPost_R(x->rChild, visit);
	visit(x->data);
}

template<typename T>
void BinTree<T>::gotoHLVF(Stack<BinNodePosi(T)>& s) {  // ��ջ�����Ϊ���������У��ҵ������ɼ�Ҷ���
	while (BinNodePosi(T) x = s.top()) {
		if (HasLChild(*x)) {  // ����������
			if (HasRChild(*x)) s->push(x->rChild);  // �����Һ��ӣ���������ջ
			s->push(x->lChild);
		}
		else {
			s.push(x->rChild);
		}
	}
	s.pop();  // ����ջ���Ŀսڵ�
}

template<typename T>
template<typename VST>
void BinTree<T>::travPost(BinNodePosi(T) x, VST& visit) {
	Stack<BinNodePosi(T)> s;
	if (x) s.push(x);  // ���ڵ���ջ
	while (!s.empty()) {
		if (s.top() != x->parent) {
			gotoHLVF(s);  // �������ָ�Ϊ�����������ҵ�HLVF
		}
		x = s.pop(); visit(x->data);  // ����ջ�� �����з���
	}
}

template<typename T>
template<typename VST>
void BinTree<T>::travLevel(BinNodePosi(T) x, VST& visit) {
	Queue < BinNodePosi(T)> q;
	q.enqueue(this);
	while (!q.empty()) {
		BinNodePosi(T) x = q.dequeue(); visit(x->data);  // ȡ�����׽ڵ㲢���з���
		if (HasLChild(*x)) q.enqueue(x->lChild);  // �������
		if (HasRChild(*x)) q.enqueue(x->rChild);  // �Һ������
	}
}

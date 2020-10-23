#pragma once
#include"BST.h"

template<typename T>
class Splay :public BST<T> {
protected:
	BinNodePosi(T) Splay(BinNodePosi(T) v);
public:
	BinNodePosi(T)& search(const T& e);  // ���Ҷ�Ӧ���
	BinNodePosi(T) insert(const T& e);  // ����
	bool remove(const T& e);  // ɾ��
};

// �������ڵ������ӽڵ�Ĺ�ϵ
template<typename NodePosi>
inline void attachAsLChild(NodePosi p, NodePosi lc) {
	p->lchild = lc;
	lc->parent = p;
}

// �������ڵ������ӽڵ�Ĺ�ϵ
template<typename NodePosi>
inline void attachAsRChild(NodePosi p, NodePosi rc) {
	p->rchild = rc;
	rc->parent = p;
}

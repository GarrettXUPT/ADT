#pragma once
#include"BST.h"

template<typename T>
class Splay :public BST<T> {
protected:
	BinNodePosi(T) Splay(BinNodePosi(T) v);
public:
	BinNodePosi(T)& search(const T& e);  // 查找对应结点
	BinNodePosi(T) insert(const T& e);  // 插入
	bool remove(const T& e);  // 删除
};

// 建立父节点与左子节点的关系
template<typename NodePosi>
inline void attachAsLChild(NodePosi p, NodePosi lc) {
	p->lchild = lc;
	lc->parent = p;
}

// 建立父节点与右子节点的关系
template<typename NodePosi>
inline void attachAsRChild(NodePosi p, NodePosi rc) {
	p->rchild = rc;
	rc->parent = p;
}

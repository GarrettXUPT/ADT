#include"Quadlist.h"

template<typename T>
void Quadlist<T>::init() {
	header = new QuadlistNode<T>();  // 创建头哨兵结点
	trailer = new QuadlistNode<T>();  // 创建尾哨兵结点
	header->succ = trailer; trailer->succ = nullptr;
	trailer->pred = header; header->pred = nullptr;
	header->above = trailer->above = nullptr;
	header->below = trailer->below = nullptr;
	_size = 0;
}

template<typename T>
QuadlistNodePosi(T) Quadlist<T>::insertAfterAbove(T const& e, QuadlistNodePosi(T) p, QuadlistNodePosi(T) b) {  // 将e作为p的后继，b的上邻插入到Quadlist中
	_size++;
	return p->insertAsSuccAbove(e, p, b);
}

template<typename T>
T Quadlist<T>::remove(QuadlistNodePosi(T) p) {
	T e = p->entry;  // 备份待删除的词条
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	release(p); _size--;
	return e;
}

template<typename T>
int Quadlist<T>::clear() {
	int oldsize = _size;
	while (_size > 0) remove(header->succ);
	return oldsize;
}

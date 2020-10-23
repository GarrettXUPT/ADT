#include"Quadlist.h"

template<typename T>
void Quadlist<T>::init() {
	header = new QuadlistNode<T>();  // ����ͷ�ڱ����
	trailer = new QuadlistNode<T>();  // ����β�ڱ����
	header->succ = trailer; trailer->succ = nullptr;
	trailer->pred = header; header->pred = nullptr;
	header->above = trailer->above = nullptr;
	header->below = trailer->below = nullptr;
	_size = 0;
}

template<typename T>
QuadlistNodePosi(T) Quadlist<T>::insertAfterAbove(T const& e, QuadlistNodePosi(T) p, QuadlistNodePosi(T) b) {  // ��e��Ϊp�ĺ�̣�b�����ڲ��뵽Quadlist��
	_size++;
	return p->insertAsSuccAbove(e, p, b);
}

template<typename T>
T Quadlist<T>::remove(QuadlistNodePosi(T) p) {
	T e = p->entry;  // ���ݴ�ɾ���Ĵ���
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

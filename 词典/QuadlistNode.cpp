#include"QuadlistNode.h"

template<typename T>
QuadlistNodePosi(T) QuadlistNode<T>::insertAsSuccAbove(T const& e, QuadlistNodePosi(T) b) {  // ���뵽��ǰ�ڵ�ĺ��棬��b������
	QuadlistNodePosi(T) x = new QuadlistNode(e, this, this->succ, nullptr, b);  // �����½ڵ�
	this->succ->pred = x; this->succ = x;
	if (b) b->above = x;  // ���ô�ֱ��������
	return x;  // �����½ڵ��λ��
}
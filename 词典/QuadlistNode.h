#pragma once
/*
	������ڵ���
*/
#include"Entry.h"
#define QuadlistNodePosi(T) QuadlistNode<T>*
template<typename T>
class QuadlistNode {
public:
	T entry;  // Ԫ����������
	QuadlistNodePosi(T) pred; QuadlistNodePosi(T) succ;
	QuadlistNodePosi(T) above; QuadlistNodePosi(T) below;
	// ���캯��
	QuadlistNode() {}
	QuadlistNode(T e, QuadlistNodePosi(T) p = nullptr, QuadlistNodePosi(T) s = nullptr, QuadlistNodePosi(T) a = nullptr, QuadlistNodePosi(T) b = nullptr) :
		pred(p), succ(s), above(a), below(b) {}
	// �����ӿ�
	QuadlistNodePosi(T) insertAsSuccAbove(T const& e, QuadlistNodePosi(T) b = nullptr);
};

#include"ListNode.h"

template<typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const& e) {
	ListNodePosi(T) x = new ListNode(e, this->pred, this);  // �����½ڵ�
	this->pred->succ = x;  // ǰ���ĺ��ָ��ָ���½ڵ�
	this->pred = x;  // �ֽ���ǰָ��ָ���½ڵ�
	return x; // �����½ڵ�λ��
}

template<typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e) {
	ListNodePosi(T) x = new ListNode(e, this, this->succ);
	this->succ->pred = x; 
	this->succ = x;
	return x;
}

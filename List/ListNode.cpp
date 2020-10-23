#include"ListNode.h"

template<typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const& e) {
	ListNodePosi(T) x = new ListNode(e, this->pred, this);  // 创建新节点
	this->pred->succ = x;  // 前结点的后继指针指向新节点
	this->pred = x;  // 现结点的前指针指向新节点
	return x; // 返回新节点位置
}

template<typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e) {
	ListNodePosi(T) x = new ListNode(e, this, this->succ);
	this->succ->pred = x; 
	this->succ = x;
	return x;
}

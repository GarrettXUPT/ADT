#pragma once
#define ListNodePosi(T) ListNode<T>*
typedef int Rank;
template<typename T>
struct ListNode{
	// ��Ա
	T data;  ListNodePosi(T) pred; ListNodePosi(T) succ;
	// ���캯��
	ListNode() {}
	ListNode(T e, ListNodePosi(T) p = nullptr, ListNodePosi(T) s = nullptr) : data(e), pred(p), succ(s) {}
	// �����ӿ�
	ListNodePosi(T) insertAsPred(T const& e);
	ListNodePosi(T) insertAsSucc(T const& e);

};

#pragma once
#define ListNodePosi(T) ListNode<T>*
typedef int Rank;
template<typename T>
struct ListNode{
	// 成员
	T data;  ListNodePosi(T) pred; ListNodePosi(T) succ;
	// 构造函数
	ListNode() {}
	ListNode(T e, ListNodePosi(T) p = nullptr, ListNodePosi(T) s = nullptr) : data(e), pred(p), succ(s) {}
	// 操作接口
	ListNodePosi(T) insertAsPred(T const& e);
	ListNodePosi(T) insertAsSucc(T const& e);

};

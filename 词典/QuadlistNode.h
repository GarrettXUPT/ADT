#pragma once
/*
	四链表节点类
*/
#include"Entry.h"
#define QuadlistNodePosi(T) QuadlistNode<T>*
template<typename T>
class QuadlistNode {
public:
	T entry;  // 元素类型数据
	QuadlistNodePosi(T) pred; QuadlistNodePosi(T) succ;
	QuadlistNodePosi(T) above; QuadlistNodePosi(T) below;
	// 构造函数
	QuadlistNode() {}
	QuadlistNode(T e, QuadlistNodePosi(T) p = nullptr, QuadlistNodePosi(T) s = nullptr, QuadlistNodePosi(T) a = nullptr, QuadlistNodePosi(T) b = nullptr) :
		pred(p), succ(s), above(a), below(b) {}
	// 操作接口
	QuadlistNodePosi(T) insertAsSuccAbove(T const& e, QuadlistNodePosi(T) b = nullptr);
};

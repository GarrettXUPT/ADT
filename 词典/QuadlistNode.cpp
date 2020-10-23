#include"QuadlistNode.h"

template<typename T>
QuadlistNodePosi(T) QuadlistNode<T>::insertAsSuccAbove(T const& e, QuadlistNodePosi(T) b) {  // 插入到当前节点的后面，及b的上面
	QuadlistNodePosi(T) x = new QuadlistNode(e, this, this->succ, nullptr, b);  // 创建新节点
	this->succ->pred = x; this->succ = x;
	if (b) b->above = x;  // 设置垂直逆向链接
	return x;  // 但会新节点的位置
}
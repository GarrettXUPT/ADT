#include"BinNode.h"

template<typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(T const& e) {
	return lChild = new BinNode(e, this);
}

template<typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(T const& e) {
	return rChild = new BinNode(e, this);
}

template<typename T>
BinNodePosi(T) BinNode<T>::succ() {  // 获取当前节点的直接后继
	BinNodePosi(T) s = this;  // 记录后继的临时变量
	if (rChild) {  // 若有右孩子，那么直接后继结点一定会在右子树中
		s = rChild;
		while (HasLChild(*s))
		{
			s = s->lChild;  // 右子树中，最靠左的结点
		}
	}
	else  // 没有右孩子, 则为左子树中的最低点
	{
		// 若当前节点为右子节点，则，则向左向上移动，直到到达结点是不右子节点为止
		while (IsRChild(*s)) s = s->parent;   // 逆向的沿着右向分支，不断向左上方移动
		s = s->parent;  // 最后再朝右上移动一步，则到达直接后继
	}
}

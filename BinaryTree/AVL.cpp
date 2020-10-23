#include"AVL.h"


/*
	将结点e插入到AVL树中
*/
template<typename T>
BinNodePosi(T) AVL<T>::insert(const T& e) {
	BinNodePosi(T)& x = search(e); if (x) return x;  // 确认目标节点是否存在
	x = new BinNode(e, _hot);  _size++;  // 创建结点x，其父节点高度可能增加，祖父结点可能会失衡
	for (BinNodePosi(T) g = _hot; g; g = g->parent) {  // 从x的父节点出发，逐层检查各代祖先g
		if (!AvlBalanced(*g)) {  // 发现g结点失衡，采用3 + 4算法使之重新恢复平衡
			FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));  // 将子树连接其父亲结点
			break;
		}
		else {
			updateHeight(g);  // 更新其高度，即使是没有失衡，高度也可能增加了
		}
	}
	return x;  // 返回新节点
}

// 将树中的结点e删除
template<typename T>
bool AVL<T>::remove(const T& e) {
	BinNodePosi(T)& x = search(e); if (!x) return false;  // 确认该结点是否存在
	removeAt(x, _hot); _size--;
	for (BinNodePosi(T) g = _hot; g; g = g->parent) {
		if (!AvlBalanced(*g)) {
			g = FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
		}
		updateHeight(g);  // 更新其高度
	}
	return true;
}
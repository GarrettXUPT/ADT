#include"BST.h"

/*
	查找算法
	二叉搜索树查找算法的基本思路：从根节点出发，递归不断地缩小查找范围，知道发现目标，或者是查找范围缩小至空树也没有找到
*/
// 在以v为根节点的BST树中寻找e节点, _hot为后来的操作做准备
template<typename T>
BinNodePosi(T)& BST<T>::searchIn(BinNodePosi(T)& v, T const& e, BinNodePosi(T)& hot) {
	if (!v || (e == v->data)) return v;  // 搜索到空或者是找到目标元素
	hot = v;  // 记录当前节点
	return searchIn(((e < v->data) ? v->lChild : v->rChild), e, hot);
}

template<typename T>
BinNodePosi(T)& BST<T>::search(T const& e) {
	return searchIn(_root, e, _hot = nullptr);
}

template<typename T>
BinNodePosi(T) BST<T>::insert(T const& e) {
	BinNodePosi(T)& x = search(e); if (x) return x;  // 为了确认节点不存在，若e存在则直接返回
	x = new BinNode<T>(e, _hot);  // 创建新节点x，以_hot为父节点
	_size++;
	updateHeightAbove(x);  // 更新x节点与历代祖先的高度
	return x;
}

/*
	BST结点删除算法：删除位置v所指向的结点，通常要先进行搜索，找到该节点以后调用本函数，进行删除
	该函数返回值指向的实际被删除节点的接替者，_hot指向实际被删除结点的父节点---二者都有可能是NULL
*/
template<typename T>
BinNodePosi(T) BST<T>::removeAt(BinNodePosi(T)& v, BinNodePosi(T)& hot) {
	BinNodePosi(T) w = v;  // 实际要被删除的结点
	BinNodePosi(T) succ = nullptr;  // 实际被删除结点的接替者
	if (!HasLChild(*v)) {
		succ = v = v->rChild;   // 直接将v替换成为其右子树
	}
	else if (!HasRChild(*v)) {
		succ = v = v->lChild;
	}
	else {  // 若左右子树都存在，则选择v的直接后继结点作为实际被摘除的结点
		w = w->succ();  // 在子树中找到v的后继结点
		swap(v->data, w->data);  // 交换v和w中的数据
		BinNodePosi(T) u = w->parent;
		((u == v) ? u->rChild : u->lChild) = succ = w->rChild;  // 隔离结点w
	}
	hot = w->parent;  // 记录被删除结点的父节点
	if (succ) succ->parent = hot;  // 将删除结点的接替者与_hot相连
	release(w->data); release(w);
	return succ;
}

// 删除操作的最差情况不超过树的高度
template<typename T>
bool BST<T>::remove(T const& e) {
	BinNodePosi(T)& x = search(e); if (!x) return false;
	removeAt(x, _hot); size--;
	updateHeightAbove(_hot);
	return true;
}

template<typename T>
BinNodePosi(T) BST<T>::connect34(BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
									BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3) {
	a->lChild = T0; if (T0) T0->parent = a;
	a->rChild = T1; if (T1) T1->parent = a; updateHeight(a);
	c->lChild = T2; if (T2) T2->parent = c;
	c->rChild = T3; if (T3) T3->parent = c; updateHeight(c);
	b->lChild = a; a->parent = b;
	b->rChild = c; c->parent = b; updateHeight(b);
	return b;  // 该子树的新的根节点
}

// BST结点旋转变换的统一算法(3结点 + 4子树) 返回调整之后局部子树根节点的位置
template<typename T>
BinNodePosi(T) BST<T>::rotateAt(BinNodePosi(T) v) {  // v为非空的孙辈结点
	BinNodePosi(T) p = v->parent;  // v、p和g相对位置分为四种情况
	BinNodePosi(T) g = p->parent;
	if (IsLChild(*p)) {  // zig
		if (IsLChild(*v)) {  // zig-zig  右旋右旋
			p->parent = g->parent;  // 向上链接
			return connect34(v, p, g, v->lChild, v->rChild, p->lChild, g->parent);
		}
		else {  // zig/zag   右旋左旋
			v->parent = g->parent;  // 向上链接
			return connect34(v, p, g, p->lChild, v->lChild, v->rChild, g->rChild);
		}
	}
	else {  // zag
		if (IsRChild(*v)) {  // zag/zig  左旋右旋
			p->parent = g->parent; // 向上链接
			return connect34(p, v, g, g->lChild, p->lChild, v->lChild, v->rChild);
		}
		else { // zag/zag  左旋左旋
			v->parent = g->parent;  // 向上链接
			return connect34(g, v, p, g->lChild, v->lChild, v->rChild, p->rChild);
		}
	}

}
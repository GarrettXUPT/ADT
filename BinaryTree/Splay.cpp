#include"Splay.h"

template<typename T>
BinNodePosi(T) Splay<T>(BinNodePosi(T) v) {
	if (!v) return nullptr;  // 若v结点不存在，则直接返回空指针
	BinNodePosi(T) p; BinNodePosi(T) g;  // 建立v的父节点与祖父节点
	while ((p = v->parent) && (g = p->parent)) {  // 直下而上，反复对v做双层扩展
		BinNodePosi(T) r = g->parent;  // 每轮都以v的元祖父为父
		if (IsLChild(*v)) {  // zig-zig
			if (IsLChild(*p)) {
				attachAsLChild(g, p->rChild); attachAsLChild(p, v->rChild);
				attachAsRChild(p, g);  attachAsRChild(v, p);
			}
			else  // zig-zag
			{
				attachAsLChild(p, p->rChild);  attachAsRChild(p, v->rChild);
				attachAsLChild(v, g);  attachAsRChild(v, p);
			}
		}
		else if (IsRChild(*p)) {  // zag-zag
			attachAsRChild(g, p->lChild);  attachAsRChild(p, v->lChild);
			attachAsLChild(v, g);  attachAsLChild(v, p);
		}
		else {  // zag-zig
			attachAsRChild(p, v->lChild);  attachAsLChild(g, v->rChild);
			attachAsRChild(v, g);  attachAsLChild(v, p);
		}
		if (!r) {
			v->parent = nullptr;  // 若v没有曾祖父，那么v现在就是树根
		}
		else {
			(g == r->rChild) ? attachAsLChild(r, v) : attachAsRChild(r, v);
		}
		updateHeight(g); 
		updateHeight(p);
		updateHeight(v);
	}
	if (p = v->parent) {  // 若p还为非空，则继续单旋,即v还没有到达树根
		if (IsLChild(*v)) {
			attachAsLChild(p, v->rChild);  attachAsRChild(v, p);
		}
		else {
			attachAsRChild(p, v->lChild);  attachAsLChild(v, p);
		}
		updateHeight(p); updateHeight(v);
	}
	v->parent = nullptr;
	return v;
}

template<typename T>
BinNodePosi(T)& search(const T& e) {
	BinNodePosi(T) p = searchIn(_root, e, hot = nullptr);
	_root = Splay(p ? p : _hot);  // 将最后一个本访问的结点放到树根
	return _root;
}

template<typename T>
BinNodePosi(T) insert(const T& e) {
	if (!_root) {
		size++;
		return _root = new BinNode<T>(e);  // 若是空树，则将其作为根节点
	}
	if (e == search(e)->data) return _root;  // 确认目标节点不存在
	_size++; BinNodePosi(T) t = _root;  // 创建新节点
	if (_root->data < e) {
		t->parent = _root = new BinNode<T>(e, nullptr, t, t->rChild);
		if (HasRChild(*t)) {
			t->rChild->parent = _root;
			t->rChild = nullptr;
		}
	}
	else {
		t->parent = _root = new BinNode<T>(e, nullptr, t->lChild, t);
		if (HasLChild(*t)) {
			t->lChild->parent = _root;
			t->rChild = nullptr;
		}
	}
	updateHightAbove(t);  // 更新t以及其祖先的高度
	return _root;  // 新节点必然位于树根，所以将其返回
}

template<typename T>
bool remove(const T& e) {
	// root为空或者是树中没有该元素，则直接返回错误，但是要注意的是，此时e已经到了树根
	if (!_root || (e != search(e)->data)) return false;
	BinNodePosi(T) w = _root;  // 经过search，节点e已经被延展至树根
	if (!HasLChild(*_root)) {  // 若无左子树，则直接删除
		_root = _root->rChild;
		if (_root) {
			_root->parent = nullptr;
		}
	}
	else if (!HasRChild(*_root)) {   // 若无右子树，也直接删除
		_root = _root->lChild;
		if (_root) {
			_root->parent = nullptr;
		}
	}
	else {
		BinNodePosi(T) lTree = _root->lChild;
		lTree->parent = nullptr;  _root->lChild = nullptr;  // 暂时将左子树切除
		_root = _root->rChild;  _root->parent = nullptr;  // 只保留右子树
		search(w->data);  // 以原树根为目标，做一次查找，此次查找必定会失败，但是通过这次，使右子树最小节点延展到了树根
		_root->lChild = lTree;	// 只需将原左子树接回原位置
		lTree->parent = _root;  
	}
	release(w->data);  release(w); _size--;  // 释放结点，更新规模
	if (_root) updateHeight(_root);  // 此后，若树非空，则树根的高度需要更新
	return true;
}

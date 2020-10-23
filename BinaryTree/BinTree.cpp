#include"BinTree.h"

/*
	更新树高，所有节点深度的最大值为树高
	更新以x为根节点的树高
*/
template<typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x) {
	return x->height = 1 + max(stature(x->lChild), stature(x->rChild));
}

/*
	更新x结点及其祖先结点的树高
*/
template<typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x) {
	while (x) {
		updateHeight(x);
		x = x->parent;
	}
}

/*
	将结点插入空树，即自己作为根节点
*/
template<typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e) {
	_size = 1;
	return _root = new BinNode(e);  // 将e作为根节点插入到空的二叉树中
}

/*
	插入以x为根节点的左子节点
*/
template<typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e) {
	_size++;
	x->insertAsLC(e);
	updateHeightAbove(x);
	return x->lChild;
}

/*
	插入以x为根节点的右子节点
*/
template<typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e) {
	_size++;
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->rChild;
}

/*
	将树s，作为x的左子树插入
*/
template<typename T>
BinNodePosi(T) BinTree<T>::attachAsLc(BinNodePosi(T) x, BinTree<T>* s) {  // 默认x还没有左子节点
	if (x->lChild = s->_root) x->lChild->parent = x;  // 直接接入
	_size += s->size; updateHeightAbove(x);  // 更新全树规模与x所有祖先的高度
	// 将树s进行释放
	s->_root = nullptr; s->_size = 0; release(s); s = nullptr;
	return x;  // 返回接入位置
}

/*
	将树s，作为x的右子树进行插入
*/
template<typename T>
BinNodePosi(T) BinTree<T>::attachAsRc(BinNodePosi(T) x, BinTree<T>* s) {
	if (x->rChild = s->_root) x->rChild->parent = x;  // 直接接入
	_size = s->size; updateHeightAbove(x);  // 更新全树规模与x所有祖先的高度
	s->_root = nullptr; s->_size = 0; release(s); s = nullptr;
	return x;  // 返回接入位置
}


/*
	删除以x为根节点的子树或者是只删除x结点
*/
template<typename T>
int BinTree<T>::remove(BinNodePosi(T) x) {
	FromParentTo(*x) = nullptr; // 切断来自父节点的指针
	updateHeightAbove(x->parent);  // 更新祖先高度
	int n = removeAt(x);
	_size -= n;
	return n;
}

/*
	处理删除以x为根节点的子树事宜
*/
template<typename T>
static int BinTree<T>::removeAt(BinNodePosi(T) x) {
	if (!x) return 0;  // 递归基为空树，若x不是子树的根节点，则直接返回
	int n = 1 + removeAt(x->lChild) + remove(x->rChild);  // 递归删除
	release(x->data); release(x);  // 释放结点x中的数据及节点本身
	return n;
}

// 子树分离,将子树从当前树中分离出来，将其封装为一颗独立的子树进行返回
template<typename T>
BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x) {
	FromParentTo(*x) = nullptr;  // 切断来自父节点的指针，切断父节点指向它的指针，并没有释放它
	updateHeightAbove(x->parent);  // 更新原树中所有祖先的高度
	BinTree<T>* s = new BinTree<T>; s->_root = x; x->parent = nullptr; // x为新树的根节点
	s->_size = x->size();  _size -= s->_size;   // 更新规模
	return s;
}

// 前序遍历,递归模式
template<typename T>
template<typename VST>
void BinTree<T>::travPre_R(BinNodePosi(T) x, VST& visit) {
	if (!x) return;  // 到达树底
	visit(x->data);
	travPre_R(x->lChild, visit);
}

// 非递归模式
template<typename T>
template<typename VST>
void BinTree<T>::visitAlongLeftBranch(BinNodePosi(T) x, VST& visit, Stack<BinNodePosi(T)>& s) {
	while (x) {
		visit(x->data);  // 访问当前结点
		s.push(x->rChild);  // 将右孩子暂存
		x = x->lChild;  // 沿着左分支深入一层
	}
}

template<typename T>
template<typename VST>
void BinTree<T>::travPre_N(BinNodePosi(T) x, VST& visit) {
	Stack<BinNodePosi(T)> s;
	while (true) {
		visitAlongLeftBranch(x, visit, s);
		if (s.empty()) break;  // 直到栈空
		x = s.pop();  // 弹出下一批的起点
	}
}

template<typename T>
template<typename VST>
void BinTree<T>::travIn_R(BinNodePosi(T) x, VST& visit) {
	if (!x) return;
	travIn_R(x->lChild, visit);
	visit(x->data);
	travIn_R(x->rChild, visit);
}

// 中序遍历，非递归版
template<typename T>
template< typename VST>
void BinTree<T>::travIn(BinNodePosi(T) x, VST& visit) {
	bool backtrack = false;
	while (true) {
		if (!backtrack && HasLChild(*x)) x = x->lChild;  // 若有左子树，且不是回溯形成的，那么深入遍历左子树，找到左子树中最左的结点
		else {  // 若无左子树或者刚刚回溯
			visit(x->data);
			if (HasRChild(*x)) {  // 若存在右子树，则遍历右子树
				x = x->rChild;  // 深入右子树继续遍历
				backtrack = false;
			}
			else {  // 若没有右子树，则寻找x的下一个直接结点,且将回溯标志打开
				if (!x = x->succ()) break;
				backtrack = true;  // 回溯标志开
			}
		}
	}
}

template<typename T>
template<typename VST>
void BinTree<T>::travPost_R(BinNodePosi(T) x, VST& visit) {
	if (!x) return;
	travPost_R(x->lChild, visit);
	travPost_R(x->rChild, visit);
	visit(x->data);
}

template<typename T>
void BinTree<T>::gotoHLVF(Stack<BinNodePosi(T)>& s) {  // 以栈顶结点为根的子树中，找到最左侧可见叶结点
	while (BinNodePosi(T) x = s.top()) {
		if (HasLChild(*x)) {  // 尽可能向左
			if (HasRChild(*x)) s->push(x->rChild);  // 若有右孩子，则优先入栈
			s->push(x->lChild);
		}
		else {
			s.push(x->rChild);
		}
	}
	s.pop();  // 弹出栈顶的空节点
}

template<typename T>
template<typename VST>
void BinTree<T>::travPost(BinNodePosi(T) x, VST& visit) {
	Stack<BinNodePosi(T)> s;
	if (x) s.push(x);  // 根节点入栈
	while (!s.empty()) {
		if (s.top() != x->parent) {
			gotoHLVF(s);  // 在以右兄根为根的子树，找到HLVF
		}
		x = s.pop(); visit(x->data);  // 弹出栈顶 并进行访问
	}
}

template<typename T>
template<typename VST>
void BinTree<T>::travLevel(BinNodePosi(T) x, VST& visit) {
	Queue < BinNodePosi(T)> q;
	q.enqueue(this);
	while (!q.empty()) {
		BinNodePosi(T) x = q.dequeue(); visit(x->data);  // 取出队首节点并进行访问
		if (HasLChild(*x)) q.enqueue(x->lChild);  // 左孩子入队
		if (HasRChild(*x)) q.enqueue(x->rChild);  // 右孩子入队
	}
}

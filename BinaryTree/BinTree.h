#pragma once
#include"BinNode.h"
#include"Stack.h"
#include<cstdlib>
#include"Queue.h"

template<typename T>
class BinTree {
protected:
	int _size;  // 规模
	BinNodePosi(T) _root;  // 根节点
	virtual int updateHeight(BinNodePosi(T) x);  // 更新节点高度
	void updateHeightAbove(BinNodePosi(T) x);   // 更新结点x及其祖先的高度
public:
	BinTree() :_size(0), _root(nullptr) {}
	~BinTree() { if (_size > 0) remove(_root); }
	int& size() { return _size; }
	bool empty() { return _size == 0; }
	BinNodePosi(T)& root() { return _root; }
	BinNodePosi(T) insertAsRoot(T const& e);
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e);  // 作为x的左节点插入
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e);  // 作为x的右节点插入
	BinNodePosi(T) attachAsLc(BinNodePosi(T) x, BinTree<T>* s);  // 左子树接入
	BinNodePosi(T) attachAsRc(BinNodePosi(T) x, BinTree<T>* s);  // 左子树接入
	/*
		子树删除
	*/
	int remove(BinNodePosi(T) x);   // 删除以x为根节点的子树，返回该子树原来的规模
	static int removeAt(BinNodePosi(T) x);  // 删除二叉树中位置x处的节点及其后代，返回被删除结点的数值
	BinTree<T>* secede(BinNodePosi(T) x);  // 将子树x从原树上删除，并将其转化为一个独立的子树，即为子树分离

	template<typename VST> void travLevel(BinNodePosi(T) x, VST& visit);  // 层次遍历

	template<typename VST> void travIn_R(BinNodePosi(T) x, VST& visit);
	template<typename VST> void travIn(BinNodePosi(T) x, VST& visit);

	template<typename VST> void travPost_R(BinNodePosi(T) x, VST& visit);
	void gotoHLVF(Stack<BinNodePosi(T)>& s);
	template<typename VST> void travPost(BinNodePosi(T) x, VST& visit);

	template<typename VST> void travPre_R(BinNodePosi(T) x, VST& visit) { if (_root) _root->travPre(visit); }  // 二叉树前序遍历，递归形式
	template<typename VST> void travPre(VST& visit) { if (_root) _root->travPre(visit); }
	template<typename VST> void travPre_N(BinNodePosi(T) x, VST& visit);
	template<typename VST> void visitAlongLeftBranch(BinNodePosi(T) x, VST& visit, Stack<BinNodePosi(T)>& s);

	// 判断器 比较器
	bool operator<(BinTree<T> const& t) { return _root && t._root && (_root < t._root); }
	bool operator==(BinTree<T> const& t) { return _root && t._root && (_root == t._root); }
};

#pragma once
#include<iostream>

#define BinNodePosi(T) BinNode<T>* // 节点位置
#define stature(p) ((p) ? (p)->height : -1)  // 若为树，则返回其高度，若为空树，则返回-1

typedef enum { RB_RED, RB_BLACK } RBColor;

template<typename T>
struct BinNode {
	// 成员属性
	T data;
	BinNodePosi(T) parent; BinNodePosi(T) lChild; BinNodePosi(T) rChild;
	int height;   // 高度，当前节点的高度
	int npl;  // NULL Path Length(左堆式，可直接使用height代替)
	RBColor color;  // 颜色(红黑树)
	// 构造函数
	BinNode() :parent(nullptr), lChild(nullptr), rChild(nullptr), height(0), npl(1), color(RB_RED) {}
	BinNode(T e, BinNodePosi(T) p = nullptr, BinNodePosi(T) lc = nullptr, BinNodePosi(T) rc = nullptr, int h = 0, int l = 1, RBColor c = RB_RED) {}
	// 操作接口
	int size();
	BinNodePosi(T) insertAsLC(T const&);
	BinNodePosi(T) insertAsRC(T const&);
	BinNodePosi(T) succ();
	template<typename VST> void travLevel(VST&);  // 子树层次遍历
	template<typename VST> void travPre(VST&);  // 子树前序遍历
	template<typename VST> void travIn(VST&); // 子树中序遍历
	template<typename VST> void travPost(VST&);  // 子树后序遍历
	// 比较器，判别器
	bool operator<(BinNode const& bn) { return data < bn.data; }
	bool operator==(BinNode const& bn) { return data == bn.data; }
};


/*
	BinNode状态与性质的判别快捷方式
*/
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lChild)
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rChild)
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lChild)
#define HasRChild(x) ((x).RChild)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (!HasChild(x))

/*
	二叉树结点的关系结点
*/
#define sibling(p) (IsChild(*(p)) ? (p)->parent->rChild : (p)->parent->lChild)  // 兄弟结点
#define uncle(x) (IsLChild(*((x)->parent)) ? (x)->parent->parent->rChild : (x)->parent->parent->lChild)  // 叔叔结点
#define FromParentTo(x) (IsRoot(x) ? _root : (IsLChild(x) ? (x).parent->lChild : (x).parent->rChild))  // 来自父亲的指针



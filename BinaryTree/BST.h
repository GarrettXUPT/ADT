#pragma once
#include"BinTree.h"
/*
	此为二叉搜索树
*/
template<typename T>
class BST : public BinTree<T> {
protected:
	BinNodePosi(T) _hot;  // BST::search()最后访问的非空的节点位置
	// 按照3 + 4的结构连接3个结点及四棵树
	BinNodePosi(T) connect34(BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));
	BinNodePosi(T) rotateAt(BinNodePosi(T) x);  // 对x及其父亲、祖父做统一的旋转调整
public:
	BinNodePosi(T)& searchIn(BinNodePosi(T)& v, T const& e, BinNodePosi(T)& hot); 
	virtual BinNodePosi(T)& search(T const& e);  // 查找函数
	virtual BinNodePosi(T) insert(T const& e);  // 插入

	virtual bool remove(T const& e);  // 删除
	BinNodePosi(T) removeAt(BinNodePosi(T)& v, BinNodePosi(T)& hot); // 分情况实施删除操作
};
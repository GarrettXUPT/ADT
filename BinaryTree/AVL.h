#pragma once
#include"BST.h"
/*
	二叉树搜索树的性能取决于其高度，故在节点数目固定的情况下，应该尽可能地降低高度，对应地从书的形态上来看，也就是
	使左右子树高度尽可能接近，全树整体尽可能的平衡
	由n个结点组成的二叉树，它的高度是不可能小于logn(该对数向下取整)所以树高为该对数的二叉树，成为理想平衡二叉树
	在不至于影响二叉搜索树基本操作的渐进复杂度情况下，适当放松标准之后的平衡性就是适度平衡二叉树

	实现二叉树的基本构思：首先适度地放宽平衡性的评判标准，以扩大平衡树的覆盖的范围以及在所有二叉搜索树中所占的比例
	然后，按照某一个准则，对所有可能的搜索树做等价类划分。这些划分方案的精妙之处在于，不仅保证了每一等价类都包含
	一颗平衡搜索树，更重要的是，经过动态修改之后不再平衡的任一搜索树，就可以较小的代价，恢复为一个与其等价的平衡二叉树
*/

/*
	等价二叉搜索树的判断：中序遍历次序相同，则两个二叉树相互等价
	两个等价的二叉搜索树的特点就是：上下可变，左右不乱
	将失衡二叉树转化为等价的完全二叉树，就是围绕特定结点的旋转
*/

/*
	完全二叉树中各节点的平衡因子非0即1，所以完全二叉树必为AVL树，在渐进复杂度的意义下，AVL树也是平衡的
	AVL树与常规的二叉树一样，也支持插入删除操作，但是进行操作以后，就不可以保证还是AVL树
*/
#define Balanced(x) (stature((x).lChild) == (stature((x).rChild))  // 理想平衡条件
#define BalFac(x) ((stature(x).lChild) - (stature(x).rChild))  // 平衡因子,即为左右子树高度之差
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2))  // AVL平衡条件

/*
	恢复平衡的调整方案
	在左右孩子节点中选择更高者，若等高，则与父亲同侧者优先
*/
#define tallerChild(x) (stature((x)->lChild) > stature((x)->rChild) ? (x)->lChild : (stature((x)->rChild)) > (stature((x)->lChild)) (x)->rChild : (IsLChild(*(x)) ? (x)->lChild : (x)->rChild)))

template<typename T> 
class AVL : public BST<T> {
public:
	BinNodePosi(T) insert(const T& e);
	bool remove(const T& e);
};


#pragma once
#include<iostream>

#define BinNodePosi(T) BinNode<T>* // �ڵ�λ��
#define stature(p) ((p) ? (p)->height : -1)  // ��Ϊ�����򷵻���߶ȣ���Ϊ�������򷵻�-1

typedef enum { RB_RED, RB_BLACK } RBColor;

template<typename T>
struct BinNode {
	// ��Ա����
	T data;
	BinNodePosi(T) parent; BinNodePosi(T) lChild; BinNodePosi(T) rChild;
	int height;   // �߶ȣ���ǰ�ڵ�ĸ߶�
	int npl;  // NULL Path Length(���ʽ����ֱ��ʹ��height����)
	RBColor color;  // ��ɫ(�����)
	// ���캯��
	BinNode() :parent(nullptr), lChild(nullptr), rChild(nullptr), height(0), npl(1), color(RB_RED) {}
	BinNode(T e, BinNodePosi(T) p = nullptr, BinNodePosi(T) lc = nullptr, BinNodePosi(T) rc = nullptr, int h = 0, int l = 1, RBColor c = RB_RED) {}
	// �����ӿ�
	int size();
	BinNodePosi(T) insertAsLC(T const&);
	BinNodePosi(T) insertAsRC(T const&);
	BinNodePosi(T) succ();
	template<typename VST> void travLevel(VST&);  // ������α���
	template<typename VST> void travPre(VST&);  // ����ǰ�����
	template<typename VST> void travIn(VST&); // �����������
	template<typename VST> void travPost(VST&);  // �����������
	// �Ƚ������б���
	bool operator<(BinNode const& bn) { return data < bn.data; }
	bool operator==(BinNode const& bn) { return data == bn.data; }
};


/*
	BinNode״̬�����ʵ��б��ݷ�ʽ
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
	���������Ĺ�ϵ���
*/
#define sibling(p) (IsChild(*(p)) ? (p)->parent->rChild : (p)->parent->lChild)  // �ֵܽ��
#define uncle(x) (IsLChild(*((x)->parent)) ? (x)->parent->parent->rChild : (x)->parent->parent->lChild)  // ������
#define FromParentTo(x) (IsRoot(x) ? _root : (IsLChild(x) ? (x).parent->lChild : (x).parent->rChild))  // ���Ը��׵�ָ��



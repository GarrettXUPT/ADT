#pragma once
#include"BinNode.h"
#include"Stack.h"
#include<cstdlib>
#include"Queue.h"

template<typename T>
class BinTree {
protected:
	int _size;  // ��ģ
	BinNodePosi(T) _root;  // ���ڵ�
	virtual int updateHeight(BinNodePosi(T) x);  // ���½ڵ�߶�
	void updateHeightAbove(BinNodePosi(T) x);   // ���½��x�������ȵĸ߶�
public:
	BinTree() :_size(0), _root(nullptr) {}
	~BinTree() { if (_size > 0) remove(_root); }
	int& size() { return _size; }
	bool empty() { return _size == 0; }
	BinNodePosi(T)& root() { return _root; }
	BinNodePosi(T) insertAsRoot(T const& e);
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e);  // ��Ϊx����ڵ����
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e);  // ��Ϊx���ҽڵ����
	BinNodePosi(T) attachAsLc(BinNodePosi(T) x, BinTree<T>* s);  // ����������
	BinNodePosi(T) attachAsRc(BinNodePosi(T) x, BinTree<T>* s);  // ����������
	/*
		����ɾ��
	*/
	int remove(BinNodePosi(T) x);   // ɾ����xΪ���ڵ�����������ظ�����ԭ���Ĺ�ģ
	static int removeAt(BinNodePosi(T) x);  // ɾ����������λ��x���Ľڵ㼰���������ر�ɾ��������ֵ
	BinTree<T>* secede(BinNodePosi(T) x);  // ������x��ԭ����ɾ����������ת��Ϊһ����������������Ϊ��������

	template<typename VST> void travLevel(BinNodePosi(T) x, VST& visit);  // ��α���

	template<typename VST> void travIn_R(BinNodePosi(T) x, VST& visit);
	template<typename VST> void travIn(BinNodePosi(T) x, VST& visit);

	template<typename VST> void travPost_R(BinNodePosi(T) x, VST& visit);
	void gotoHLVF(Stack<BinNodePosi(T)>& s);
	template<typename VST> void travPost(BinNodePosi(T) x, VST& visit);

	template<typename VST> void travPre_R(BinNodePosi(T) x, VST& visit) { if (_root) _root->travPre(visit); }  // ������ǰ��������ݹ���ʽ
	template<typename VST> void travPre(VST& visit) { if (_root) _root->travPre(visit); }
	template<typename VST> void travPre_N(BinNodePosi(T) x, VST& visit);
	template<typename VST> void visitAlongLeftBranch(BinNodePosi(T) x, VST& visit, Stack<BinNodePosi(T)>& s);

	// �ж��� �Ƚ���
	bool operator<(BinTree<T> const& t) { return _root && t._root && (_root < t._root); }
	bool operator==(BinTree<T> const& t) { return _root && t._root && (_root == t._root); }
};

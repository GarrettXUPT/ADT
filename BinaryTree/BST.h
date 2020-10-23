#pragma once
#include"BinTree.h"
/*
	��Ϊ����������
*/
template<typename T>
class BST : public BinTree<T> {
protected:
	BinNodePosi(T) _hot;  // BST::search()�����ʵķǿյĽڵ�λ��
	// ����3 + 4�Ľṹ����3����㼰�Ŀ���
	BinNodePosi(T) connect34(BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));
	BinNodePosi(T) rotateAt(BinNodePosi(T) x);  // ��x���丸�ס��游��ͳһ����ת����
public:
	BinNodePosi(T)& searchIn(BinNodePosi(T)& v, T const& e, BinNodePosi(T)& hot); 
	virtual BinNodePosi(T)& search(T const& e);  // ���Һ���
	virtual BinNodePosi(T) insert(T const& e);  // ����

	virtual bool remove(T const& e);  // ɾ��
	BinNodePosi(T) removeAt(BinNodePosi(T)& v, BinNodePosi(T)& hot); // �����ʵʩɾ������
};
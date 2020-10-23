#include"BinNode.h"

template<typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(T const& e) {
	return lChild = new BinNode(e, this);
}

template<typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(T const& e) {
	return rChild = new BinNode(e, this);
}

template<typename T>
BinNodePosi(T) BinNode<T>::succ() {  // ��ȡ��ǰ�ڵ��ֱ�Ӻ��
	BinNodePosi(T) s = this;  // ��¼��̵���ʱ����
	if (rChild) {  // �����Һ��ӣ���ôֱ�Ӻ�̽��һ��������������
		s = rChild;
		while (HasLChild(*s))
		{
			s = s->lChild;  // �������У����Ľ��
		}
	}
	else  // û���Һ���, ��Ϊ�������е���͵�
	{
		// ����ǰ�ڵ�Ϊ���ӽڵ㣬�������������ƶ���ֱ���������ǲ����ӽڵ�Ϊֹ
		while (IsRChild(*s)) s = s->parent;   // ��������������֧�����������Ϸ��ƶ�
		s = s->parent;  // ����ٳ������ƶ�һ�����򵽴�ֱ�Ӻ��
	}
}

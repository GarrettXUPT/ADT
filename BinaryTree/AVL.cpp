#include"AVL.h"


/*
	�����e���뵽AVL����
*/
template<typename T>
BinNodePosi(T) AVL<T>::insert(const T& e) {
	BinNodePosi(T)& x = search(e); if (x) return x;  // ȷ��Ŀ��ڵ��Ƿ����
	x = new BinNode(e, _hot);  _size++;  // �������x���丸�ڵ�߶ȿ������ӣ��游�����ܻ�ʧ��
	for (BinNodePosi(T) g = _hot; g; g = g->parent) {  // ��x�ĸ��ڵ������������������g
		if (!AvlBalanced(*g)) {  // ����g���ʧ�⣬����3 + 4�㷨ʹ֮���»ָ�ƽ��
			FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));  // �����������丸�׽��
			break;
		}
		else {
			updateHeight(g);  // ������߶ȣ���ʹ��û��ʧ�⣬�߶�Ҳ����������
		}
	}
	return x;  // �����½ڵ�
}

// �����еĽ��eɾ��
template<typename T>
bool AVL<T>::remove(const T& e) {
	BinNodePosi(T)& x = search(e); if (!x) return false;  // ȷ�ϸý���Ƿ����
	removeAt(x, _hot); _size--;
	for (BinNodePosi(T) g = _hot; g; g = g->parent) {
		if (!AvlBalanced(*g)) {
			g = FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
		}
		updateHeight(g);  // ������߶�
	}
	return true;
}
#include"BST.h"

/*
	�����㷨
	���������������㷨�Ļ���˼·���Ӹ��ڵ�������ݹ鲻�ϵ���С���ҷ�Χ��֪������Ŀ�꣬�����ǲ��ҷ�Χ��С������Ҳû���ҵ�
*/
// ����vΪ���ڵ��BST����Ѱ��e�ڵ�, _hotΪ�����Ĳ�����׼��
template<typename T>
BinNodePosi(T)& BST<T>::searchIn(BinNodePosi(T)& v, T const& e, BinNodePosi(T)& hot) {
	if (!v || (e == v->data)) return v;  // �������ջ������ҵ�Ŀ��Ԫ��
	hot = v;  // ��¼��ǰ�ڵ�
	return searchIn(((e < v->data) ? v->lChild : v->rChild), e, hot);
}

template<typename T>
BinNodePosi(T)& BST<T>::search(T const& e) {
	return searchIn(_root, e, _hot = nullptr);
}

template<typename T>
BinNodePosi(T) BST<T>::insert(T const& e) {
	BinNodePosi(T)& x = search(e); if (x) return x;  // Ϊ��ȷ�Ͻڵ㲻���ڣ���e������ֱ�ӷ���
	x = new BinNode<T>(e, _hot);  // �����½ڵ�x����_hotΪ���ڵ�
	_size++;
	updateHeightAbove(x);  // ����x�ڵ����������ȵĸ߶�
	return x;
}

/*
	BST���ɾ���㷨��ɾ��λ��v��ָ��Ľ�㣬ͨ��Ҫ�Ƚ����������ҵ��ýڵ��Ժ���ñ�����������ɾ��
	�ú�������ֵָ���ʵ�ʱ�ɾ���ڵ�Ľ����ߣ�_hotָ��ʵ�ʱ�ɾ�����ĸ��ڵ�---���߶��п�����NULL
*/
template<typename T>
BinNodePosi(T) BST<T>::removeAt(BinNodePosi(T)& v, BinNodePosi(T)& hot) {
	BinNodePosi(T) w = v;  // ʵ��Ҫ��ɾ���Ľ��
	BinNodePosi(T) succ = nullptr;  // ʵ�ʱ�ɾ�����Ľ�����
	if (!HasLChild(*v)) {
		succ = v = v->rChild;   // ֱ�ӽ�v�滻��Ϊ��������
	}
	else if (!HasRChild(*v)) {
		succ = v = v->lChild;
	}
	else {  // ���������������ڣ���ѡ��v��ֱ�Ӻ�̽����Ϊʵ�ʱ�ժ���Ľ��
		w = w->succ();  // ���������ҵ�v�ĺ�̽��
		swap(v->data, w->data);  // ����v��w�е�����
		BinNodePosi(T) u = w->parent;
		((u == v) ? u->rChild : u->lChild) = succ = w->rChild;  // ������w
	}
	hot = w->parent;  // ��¼��ɾ�����ĸ��ڵ�
	if (succ) succ->parent = hot;  // ��ɾ�����Ľ�������_hot����
	release(w->data); release(w);
	return succ;
}

// ɾ�����������������������ĸ߶�
template<typename T>
bool BST<T>::remove(T const& e) {
	BinNodePosi(T)& x = search(e); if (!x) return false;
	removeAt(x, _hot); size--;
	updateHeightAbove(_hot);
	return true;
}

template<typename T>
BinNodePosi(T) BST<T>::connect34(BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
									BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3) {
	a->lChild = T0; if (T0) T0->parent = a;
	a->rChild = T1; if (T1) T1->parent = a; updateHeight(a);
	c->lChild = T2; if (T2) T2->parent = c;
	c->rChild = T3; if (T3) T3->parent = c; updateHeight(c);
	b->lChild = a; a->parent = b;
	b->rChild = c; c->parent = b; updateHeight(b);
	return b;  // ���������µĸ��ڵ�
}

// BST�����ת�任��ͳһ�㷨(3��� + 4����) ���ص���֮��ֲ��������ڵ��λ��
template<typename T>
BinNodePosi(T) BST<T>::rotateAt(BinNodePosi(T) v) {  // vΪ�ǿյ��ﱲ���
	BinNodePosi(T) p = v->parent;  // v��p��g���λ�÷�Ϊ�������
	BinNodePosi(T) g = p->parent;
	if (IsLChild(*p)) {  // zig
		if (IsLChild(*v)) {  // zig-zig  ��������
			p->parent = g->parent;  // ��������
			return connect34(v, p, g, v->lChild, v->rChild, p->lChild, g->parent);
		}
		else {  // zig/zag   ��������
			v->parent = g->parent;  // ��������
			return connect34(v, p, g, p->lChild, v->lChild, v->rChild, g->rChild);
		}
	}
	else {  // zag
		if (IsRChild(*v)) {  // zag/zig  ��������
			p->parent = g->parent; // ��������
			return connect34(p, v, g, g->lChild, p->lChild, v->lChild, v->rChild);
		}
		else { // zag/zag  ��������
			v->parent = g->parent;  // ��������
			return connect34(g, v, p, g->lChild, v->lChild, v->rChild, p->rChild);
		}
	}

}
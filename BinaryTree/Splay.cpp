#include"Splay.h"

template<typename T>
BinNodePosi(T) Splay<T>(BinNodePosi(T) v) {
	if (!v) return nullptr;  // ��v��㲻���ڣ���ֱ�ӷ��ؿ�ָ��
	BinNodePosi(T) p; BinNodePosi(T) g;  // ����v�ĸ��ڵ����游�ڵ�
	while ((p = v->parent) && (g = p->parent)) {  // ֱ�¶��ϣ�������v��˫����չ
		BinNodePosi(T) r = g->parent;  // ÿ�ֶ���v��Ԫ�游Ϊ��
		if (IsLChild(*v)) {  // zig-zig
			if (IsLChild(*p)) {
				attachAsLChild(g, p->rChild); attachAsLChild(p, v->rChild);
				attachAsRChild(p, g);  attachAsRChild(v, p);
			}
			else  // zig-zag
			{
				attachAsLChild(p, p->rChild);  attachAsRChild(p, v->rChild);
				attachAsLChild(v, g);  attachAsRChild(v, p);
			}
		}
		else if (IsRChild(*p)) {  // zag-zag
			attachAsRChild(g, p->lChild);  attachAsRChild(p, v->lChild);
			attachAsLChild(v, g);  attachAsLChild(v, p);
		}
		else {  // zag-zig
			attachAsRChild(p, v->lChild);  attachAsLChild(g, v->rChild);
			attachAsRChild(v, g);  attachAsLChild(v, p);
		}
		if (!r) {
			v->parent = nullptr;  // ��vû�����游����ôv���ھ�������
		}
		else {
			(g == r->rChild) ? attachAsLChild(r, v) : attachAsRChild(r, v);
		}
		updateHeight(g); 
		updateHeight(p);
		updateHeight(v);
	}
	if (p = v->parent) {  // ��p��Ϊ�ǿգ����������,��v��û�е�������
		if (IsLChild(*v)) {
			attachAsLChild(p, v->rChild);  attachAsRChild(v, p);
		}
		else {
			attachAsRChild(p, v->lChild);  attachAsLChild(v, p);
		}
		updateHeight(p); updateHeight(v);
	}
	v->parent = nullptr;
	return v;
}

template<typename T>
BinNodePosi(T)& search(const T& e) {
	BinNodePosi(T) p = searchIn(_root, e, hot = nullptr);
	_root = Splay(p ? p : _hot);  // �����һ�������ʵĽ��ŵ�����
	return _root;
}

template<typename T>
BinNodePosi(T) insert(const T& e) {
	if (!_root) {
		size++;
		return _root = new BinNode<T>(e);  // ���ǿ�����������Ϊ���ڵ�
	}
	if (e == search(e)->data) return _root;  // ȷ��Ŀ��ڵ㲻����
	_size++; BinNodePosi(T) t = _root;  // �����½ڵ�
	if (_root->data < e) {
		t->parent = _root = new BinNode<T>(e, nullptr, t, t->rChild);
		if (HasRChild(*t)) {
			t->rChild->parent = _root;
			t->rChild = nullptr;
		}
	}
	else {
		t->parent = _root = new BinNode<T>(e, nullptr, t->lChild, t);
		if (HasLChild(*t)) {
			t->lChild->parent = _root;
			t->rChild = nullptr;
		}
	}
	updateHightAbove(t);  // ����t�Լ������ȵĸ߶�
	return _root;  // �½ڵ��Ȼλ�����������Խ��䷵��
}

template<typename T>
bool remove(const T& e) {
	// rootΪ�ջ���������û�и�Ԫ�أ���ֱ�ӷ��ش��󣬵���Ҫע����ǣ���ʱe�Ѿ���������
	if (!_root || (e != search(e)->data)) return false;
	BinNodePosi(T) w = _root;  // ����search���ڵ�e�Ѿ�����չ������
	if (!HasLChild(*_root)) {  // ��������������ֱ��ɾ��
		_root = _root->rChild;
		if (_root) {
			_root->parent = nullptr;
		}
	}
	else if (!HasRChild(*_root)) {   // ������������Ҳֱ��ɾ��
		_root = _root->lChild;
		if (_root) {
			_root->parent = nullptr;
		}
	}
	else {
		BinNodePosi(T) lTree = _root->lChild;
		lTree->parent = nullptr;  _root->lChild = nullptr;  // ��ʱ���������г�
		_root = _root->rChild;  _root->parent = nullptr;  // ֻ����������
		search(w->data);  // ��ԭ����ΪĿ�꣬��һ�β��ң��˴β��ұض���ʧ�ܣ�����ͨ����Σ�ʹ��������С�ڵ���չ��������
		_root->lChild = lTree;	// ֻ�轫ԭ�������ӻ�ԭλ��
		lTree->parent = _root;  
	}
	release(w->data);  release(w); _size--;  // �ͷŽ�㣬���¹�ģ
	if (_root) updateHeight(_root);  // �˺������ǿգ��������ĸ߶���Ҫ����
	return true;
}

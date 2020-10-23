#include"List.h"

template<typename T>
void List<T>::init() {
	header = new ListNode<T>;  // ����ͷ�ڱ����
	trailer = new ListNode<T>;  // ����β�ڱ����
	header->succ = trailer; header->pred = nullptr;
	trailer->succ = nullptr; trailer->pred = header;
	_size = 0;
}

template<typename T>
ListNodePosi(T) List<T>::operator[](int r) const {
	ListNodePosi(T) p = first();  // ���׽�����
	while (0 < r--) p = p->succ;
	return p;
}

/*
	�������б��н��p��n��ǰ���У��ҵ�����e�����Ԫ��
*/
template<typename T>
ListNodePosi(T) List<T>::find(T const& e, int n, ListNodePosi(T) p) const {
	while (0 < n--) {
		if (e == p->data) return p;
		p = p->pred;
	}
	return nullptr;
}


template<typename T>
ListNodePosi(T) List<T>::insertAsFirst(T const& e) {
	_size++;
	return header->insertAsSucc(e);  // e��Ϊ�׸����ݽ�����
}


template<typename T>
ListNodePosi(T) List<T>::insertAsLast(T const& e) {
	_size++;
	return trailer->insertAsPred(e);
}


template<typename T>
ListNodePosi(T) List<T>::insertBefore(ListNodePosi(T) p, T const& e) {
	_size++;
	return p->insertAsPred(e);
}


template<typename T>
ListNodePosi(T) List<T>::insertAfter(ListNodePosi(T) p, T const& e) {
	_size++;
	return p->insertAsSucc(e);
}

/*
	����p��ʼn��Ԫ��
*/
template<typename T>
void List<T>::copyNodes(ListNodePosi(T) p, int n) {
	init();   // ����ͷβ�ڱ����
	while (n--) { insertAsLast(p->data); p = p->succ; }
}

/*
	�������캯��
*/
template<typename T>
List<T>::List(ListNodePosi(T) p, int n) {
	copyNodes(p, n);
}

/*
	������������
*/
template<typename T>
List<T>::List(List<T> const& L) {
	copyNodes(L.first(), L._size);
}

/*
	�����б��r��n��Ԫ��
*/
template<typename T>
List<T>::List(List<T> const& L, int r, int n) {
	copyNodes(L[r], n);
}

/*
	�Ƴ�Ԫ��
*/
template<typename T>
T List<T>::remove(ListNodePosi(T) p) {
	T e = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p; _size--;
	return e;
}

/*
	������������Ԫ�صĹ�ģ
*/
template<typename T>
int List<T>::clear() {
	int oldsize = _size;
	while (_size > 0) remove(header->succ);
	return oldsize;
}

template<typename T>
List<T>::~List() {
	clear();
	delete header, trailer;
}

/*
	ȥ��
*/
template<typename T>
int List<T>::deduplicate() {
	if (_size < 2) return 0;  // ��������ֻ��һ��Ԫ�ػ�����û��Ԫ��
	int oldsize = _size;
	ListNodePosi(T) p = header; Rank r = 0;  // ��ͷ��ʼ
	while (trailer != p) {
		ListNodePosi(T) q = find(p->data, r, p);
		q ? remove(q) : r++;
		p = p->succ;
	}
	return oldsize - _size;
}

/*
	����
*/
template<typename T>
void List<T>::traverse(void(*visit)(T&)) {
	for (ListNodePosi(T) p = header; p != trailer; p = p->succ) {
		visit(p->data);
	}
}

template<typename T>
template<typename VST>
void List<T>::traverse(VST& visit) {
	for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ) {
		visit(p->data);
	}
}

/*
	�����б�ȥ��
*/
template<typename T>
int List<T>::uniquify() {
	if (_size < 2) return 0;
	int oldsize = _size;
	ListNodePosi(T) p; ListNodePosi(T) q;
	for (p = header, q = p->succ; trailer != q; p = q, q = q->succ) {
		if (p->data == q->data) {
			remove(q);
			q = p;
		}
	}
	return oldsize - _size;
}

template<typename T>
ListNodePosi(T) List<T>::search(T const& e, int n, ListNodePosi(T) p) const{  // ����С�ڵ���e��λ��
	while (0 <= n--){
		if (((p = p->pred)->data) <= e) break;
	}
	return p;
}

template<typename T>
void List<T>::insertionSort(ListNodePosi(T) p, int n) {
	for (int r = 0; r < n; ++r) {
		insertAfter(search(p->data, r, p), p->data);
		p = p->succ;
		remove(p->pred);   // �Ӵ������б����Ƴ����β���ڵ�
	}
}

template<typename T>
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n) {
	ListNodePosi(T) max = p;
	for (ListNodePosi(T) cur = p; n > 1; n--) {
		if ((cur = cur->succ->data) > max->data) {
			max = cur;
		}
	}
	return max;
}

template<typename T>
void List<T>::selectionSort(ListNodePosi(T) p, int n) {
	ListNodePosi(T) head = p->pred;
	ListNodePosi(T) tail = p;
	for (int i = 0; i < n; ++i) {
		tail = tail->succ;  // ����������Ϊ[head, tail]
	}
	while (1 < n) {
		ListNodePosi(T) max = selectMax(head->succ, n);  // �ҳ����е������
		insertBefore(tail, remove(max));
		tail = tail->pred;
		n--;
	}
}

template<typename T>
void List<T>::merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T) q, int m) {  // p���n��Ԫ����q���m��Ԫ�أ��鲢����
	ListNodePosi(T) pp = p->pred;
	while (0 < m) {
		if ((0 < n) && (p->data <= q->data)) {
			if (q == (p = p->succ)) {
				break;
			}
			n--;
		}
		else  // p�����ҽ磬������p > q
		{
			insertBefore(p, L.remove((q = q->succ)->pred));  // ��q����pǰ
			m--;
		}
	}
	p = pp->succ;  // ȷ���鲢��������
}

template<typename T>
void List<T>::mergeSort(ListNodePosi(T)& p, int n) {
	if (n < 2) return;  // ������Χ�㹻С��Ȼ��ͷ���
	int m = n >> 1;  // ���е�Ϊ��
	ListNodePosi(T) q = p; 
	for (int i = 0; i < m; i++) q = q->succ;
	mergeSort(p, m); mergeSort(p, n - m);  // ��ǰ��ֵ�б��������
	merge(p, m, *this, q, n - m);
}
#include"List.h"

template<typename T>
void List<T>::init() {
	header = new ListNode<T>;  // 创建头哨兵结点
	trailer = new ListNode<T>;  // 创建尾哨兵结点
	header->succ = trailer; header->pred = nullptr;
	trailer->succ = nullptr; trailer->pred = header;
	_size = 0;
}

template<typename T>
ListNodePosi(T) List<T>::operator[](int r) const {
	ListNodePosi(T) p = first();  // 从首结点出发
	while (0 < r--) p = p->succ;
	return p;
}

/*
	在无序列表中结点p的n个前驱中，找到等于e的最后元素
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
	return header->insertAsSucc(e);  // e作为首个数据结点插入
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
	拷贝p开始n个元素
*/
template<typename T>
void List<T>::copyNodes(ListNodePosi(T) p, int n) {
	init();   // 创建头尾哨兵结点
	while (n--) { insertAsLast(p->data); p = p->succ; }
}

/*
	拷贝构造函数
*/
template<typename T>
List<T>::List(ListNodePosi(T) p, int n) {
	copyNodes(p, n);
}

/*
	拷贝整个链表
*/
template<typename T>
List<T>::List(List<T> const& L) {
	copyNodes(L.first(), L._size);
}

/*
	拷贝列表从r到n的元素
*/
template<typename T>
List<T>::List(List<T> const& L, int r, int n) {
	copyNodes(L[r], n);
}

/*
	移除元素
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
	清除，返回清除元素的规模
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
	去重
*/
template<typename T>
int List<T>::deduplicate() {
	if (_size < 2) return 0;  // 若链表中只有一个元素或者是没有元素
	int oldsize = _size;
	ListNodePosi(T) p = header; Rank r = 0;  // 从头开始
	while (trailer != p) {
		ListNodePosi(T) q = find(p->data, r, p);
		q ? remove(q) : r++;
		p = p->succ;
	}
	return oldsize - _size;
}

/*
	遍历
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
	有序列表去重
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
ListNodePosi(T) List<T>::search(T const& e, int n, ListNodePosi(T) p) const{  // 查找小于等于e的位置
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
		remove(p->pred);   // 从待排序列表中移除本次插入节点
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
		tail = tail->succ;  // 待排序区间为[head, tail]
	}
	while (1 < n) {
		ListNodePosi(T) max = selectMax(head->succ, n);  // 找出其中的最大者
		insertBefore(tail, remove(max));
		tail = tail->pred;
		n--;
	}
}

template<typename T>
void List<T>::merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T) q, int m) {  // p起的n个元素与q起的m个元素，归并排序
	ListNodePosi(T) pp = p->pred;
	while (0 < m) {
		if ((0 < n) && (p->data <= q->data)) {
			if (q == (p = p->succ)) {
				break;
			}
			n--;
		}
		else  // p超出右界，或者是p > q
		{
			insertBefore(p, L.remove((q = q->succ)->pred));  // 将q插在p前
			m--;
		}
	}
	p = pp->succ;  // 确立归并后的新起点
}

template<typename T>
void List<T>::mergeSort(ListNodePosi(T)& p, int n) {
	if (n < 2) return;  // 待排序范围足够小，然后就返回
	int m = n >> 1;  // 以中点为界
	ListNodePosi(T) q = p; 
	for (int i = 0; i < m; i++) q = q->succ;
	mergeSort(p, m); mergeSort(p, n - m);  // 对前后值列表进行排序
	merge(p, m, *this, q, n - m);
}
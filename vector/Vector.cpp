#include"Vector.h"
#include<iostream>
//
template<typename T>
void  Vector<T>::copyFrom(T* const A, Rank lo, Rank hi) {
	_capacity = 2 * (hi - lo);
	_elem = new T[_capacity];
	_size = 0;
	while (lo < hi)
	{
		_elem[_size++] = A[lo++];  // 依次复制
	}
}

template<typename T>
Vector<T>& Vector<T>::operator = (Vector<T> const& v){
	if (_elem) delete[] _elem;
	copyFrom(v._elem, 0, v.size());
	return*this;
}

template<typename T>
void Vector<T>::expand() {
	if (_size < _capacity) return;  // 容量还未用完，不必扩容
	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1];  // 容量加倍
	for (int i = 0; i < _size; ++i) {
		_elem[i] = oldElem[i];
	}
	delete[] oldElem;  // 释放源空间
}

template<typename T>
void Vector<T>::shrink() {
	if (_capacity < DEFAULT_CAPACITY) return;  // 不要将容量小于默认容量
	if ((_size << 2) > _capacity) return;  // 若容量小于25%也不需要扩容
	T* oldElem = _elem;
	_elem = new T[_capacity = _capacity >>= 1];  // 将容量减半
	for (int i = 0; i < _size; ++i) {
		_elem[i] = oldElem[i];
	}
	delete[] oldElem;
}

template<typename T>
T& Vector<T>::operator[](Rank r) const {
	if (r > _size) {
		cout << "out of range" << endl;
	}
	return _elem[r];
}

template<typename T>
void Vector<T>::permute(Vector<T>& v) {
	for (int i = v.size(); i > 0; --i) {
		swap(v[i - 1], v[rand() % i]);  // 将v[i - 1]和v[0, i - 1]中某一随机元素交换
	}
}

template<typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
	T* v = _elem + lo; // 将子向量视为_elem[lo, hi]视为另一个向量v[0, hi - lo]
	for (Rank i = hi - lo; i > 0; --i) {
		swap(v[i - 1], v[rand() % i]);  // 将v[i - 1]与v[0, i - 1]中某一元素随机交换
	}
}

template<typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const{
	if ((lo < 0) && (hi > _size)) cout << "out of range" << endl;
	while ((lo < hi--) && _elem[hi] != e);  // 从后向前顺序查找
	return hi;
}

template<typename T>
Rank Vector<T>::insert(Rank r, T const& e) {
	if ((r < 0) && (r > _size)) cout << "out of range" << endl;
	expand();  // 检测是否需要扩容
	for (int i = _size; i > r; --i) {
		_elem[i] = _elem[i - 1];
	}
	_elem[r] = e;
	_size++;
	return r;
}

template<typename T>
int Vector<T>::remove(Rank lo, Rank hi) {
	if (lo == hi) return 0;
	while (hi < _size) _elem[lo++] = _elem[hi++];  //将[hi, _size)中的元素 顺次向前移动hi - lo个单元
	_size = lo;
	shrink();  // 检测是否需要缩容
	return hi - lo;
}

template<typename T>
T Vector<T>::remove(Rank r) {
	T e = _elem[r];
	remove(r, r + 1);
	return e;
}

template<typename T>
int Vector<T>::deduplicate() {
	int oldSize = _size;
	Rank i = 1;
	while (i < _size) {
		find(_elem[i], 0, i) < 0 ? i++ : remove(i);
	}
	return oldSize - _size;  // 被删除的元素总数
}

template<typename T>
void Vector<T>::traverse(void(*visit)(T&)) {
	for (int i = 0; i < _size; ++i) {
		visit(_elem[i]);
	}
}

template<typename T>
template<typename VST>
void Vector<T>::traverse(VST& visit) {
	for (int i = 0; i < _size; ++i) {
		visit(_elem[i]);
	}
}

template<typename T>
int Vector<T>::disordered()const {  // 返回向量中逆序相邻元素对的总数
	int n = 0;  // 计数器
	for (int i = 1; i < _size; ++i) {  // 逐一检查_size - 1对相邻的元素
		if (_elem[i - 1] > _elem[i]) n++;  // 逆序计数
	}
	return n;  // 向量有序当且仅当n = 0
}

template<typename T>
int Vector<T>::uniquify() {
	Rank i = 0, j = 0;  // 各对互异"相邻"元素的秩
	while (++j < _size) {
		if (_elem[i] != _elem[j]) {
			_elem[++i] = _elem[j];  // 发现不同元素时，向前移至紧邻于前者右侧
		}
	}
	_size = ++i; shrink();  // 直接去除尾部多余元素
	return j - i;  // 被剔除的元素总数
}

template<typename T>
Rank Vector<T>::binarySearch1(Vector<T> const& v, T const& ele, Rank lo, Rank hi) {
	Rank mid = (hi + lo) / 2;
	if (ele == v[mid]) {
		return mid;
	}
	else
	{
		if (ele > v[mid]) {
			return binarySearch(v, ele, mid + 1, hi);
		}
		else
		{
			return binarySearch(v, ele, lo, mid - 1);
		}
	}
}

template<typename T>
Rank Vector<T>::binarySearch2(Vector<T> const& v, T const& ele, Rank lo, Rank hi) {
	while (lo <= hi) {
		Rank mid = (lo + hi) / 2;
		if (ele == v[mid]) {
			return mid;
		}else if (ele > v[mid]) {
			lo = mid + 1;
		}else{
			hi = mid - 1;
		}
	}
}

template<typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi) {
	while (!bubble(lo, hi--));
}

template<typename T>
bool Vector<T>::bubble(Rank lo, Rank hi) {
	bool sorted = true;
	while (lo++ < hi) {
		if (_elem[lo - 1] > _elem[lo]) {
			sorted = false;
			swap(_elem[lo - 1], _elem[lo]);
		}
	}
	return sorted;
}

void swap(int& a, int& b) {
	int tmp = a;
	a = b;
	b = tmp;
}
/*
	冒泡排序
*/
void bub(int* arr, int length) {
	for (int i = 0; i < length - 1; ++i) {
		for (int j = 0; j < length - i - 1; ++j) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

template<typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) {
	if (hi - lo < 2) return;
	int mid = (lo + hi) / 2;
	mergeSort(lo, mid);
	mergeSort(mid, hi);
	merge(lo, mid, hi);
}

template<typename T>
void Vector<T>::merge(Rank lo, Rank mid, Rank hi) {
	T* A = _elem + lo;
	int lb = mid - lo;
	T* B = new T[lb];  // [lo, mid]
	for (Rank i = 0; i < lb; B[i] = A[i++]);
	int lc = hi - mid;
	T* C = _elem + mid;  // [mid, hi]
	Rank i = 0, j = 0, k = 0;
	while ((j < lb) && (k < lc)) {
		while ((j < lb) && B[j] <= C[k]) A[i++] = B[j++];
		while ((k < lc) && C[k] <= B[j]) A[i++] = C[j++];
	}  // 此时B为空或者是C为空，即j = lb 或者是k = lc
	while (j < lb) A[i++] = B[j++];
	while (k < lc) A[i++] = C[k++];
	delete[] B;
}


int main() {
	int arr[] = { 1,3,2,5,4,7,1};
	int len = sizeof(arr) / sizeof(arr[0]);
	bub(arr, len);
	for (int ele : arr) {
		std::cout << ele << std::endl;
	}

}
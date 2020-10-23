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
		_elem[_size++] = A[lo++];  // ���θ���
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
	if (_size < _capacity) return;  // ������δ���꣬��������
	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1];  // �����ӱ�
	for (int i = 0; i < _size; ++i) {
		_elem[i] = oldElem[i];
	}
	delete[] oldElem;  // �ͷ�Դ�ռ�
}

template<typename T>
void Vector<T>::shrink() {
	if (_capacity < DEFAULT_CAPACITY) return;  // ��Ҫ������С��Ĭ������
	if ((_size << 2) > _capacity) return;  // ������С��25%Ҳ����Ҫ����
	T* oldElem = _elem;
	_elem = new T[_capacity = _capacity >>= 1];  // ����������
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
		swap(v[i - 1], v[rand() % i]);  // ��v[i - 1]��v[0, i - 1]��ĳһ���Ԫ�ؽ���
	}
}

template<typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
	T* v = _elem + lo; // ����������Ϊ_elem[lo, hi]��Ϊ��һ������v[0, hi - lo]
	for (Rank i = hi - lo; i > 0; --i) {
		swap(v[i - 1], v[rand() % i]);  // ��v[i - 1]��v[0, i - 1]��ĳһԪ���������
	}
}

template<typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const{
	if ((lo < 0) && (hi > _size)) cout << "out of range" << endl;
	while ((lo < hi--) && _elem[hi] != e);  // �Ӻ���ǰ˳�����
	return hi;
}

template<typename T>
Rank Vector<T>::insert(Rank r, T const& e) {
	if ((r < 0) && (r > _size)) cout << "out of range" << endl;
	expand();  // ����Ƿ���Ҫ����
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
	while (hi < _size) _elem[lo++] = _elem[hi++];  //��[hi, _size)�е�Ԫ�� ˳����ǰ�ƶ�hi - lo����Ԫ
	_size = lo;
	shrink();  // ����Ƿ���Ҫ����
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
	return oldSize - _size;  // ��ɾ����Ԫ������
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
int Vector<T>::disordered()const {  // ������������������Ԫ�ضԵ�����
	int n = 0;  // ������
	for (int i = 1; i < _size; ++i) {  // ��һ���_size - 1�����ڵ�Ԫ��
		if (_elem[i - 1] > _elem[i]) n++;  // �������
	}
	return n;  // ���������ҽ���n = 0
}

template<typename T>
int Vector<T>::uniquify() {
	Rank i = 0, j = 0;  // ���Ի���"����"Ԫ�ص���
	while (++j < _size) {
		if (_elem[i] != _elem[j]) {
			_elem[++i] = _elem[j];  // ���ֲ�ͬԪ��ʱ����ǰ����������ǰ���Ҳ�
		}
	}
	_size = ++i; shrink();  // ֱ��ȥ��β������Ԫ��
	return j - i;  // ���޳���Ԫ������
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
	ð������
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
	}  // ��ʱBΪ�ջ�����CΪ�գ���j = lb ������k = lc
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
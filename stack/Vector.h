#pragma once
#include<iostream>

using namespace std;

#define DEFAULT_CAPACITY 3

typedef int Rank;

template<typename T>
class Vector {
private:
	Rank _size;
	T* _elem;
	int _capacity;
protected:
	void expand();
	void shrink();
	void copyFrom(T* const, Rank, Rank);
public:
	Vector(int c = DEFAULT_CAPACITY) { _elem = new T[_capacity = c]; _size = 0; }
	Vector<T>& operator=(Vector<T> const&);
	Rank size() const { return _size; }
	T& operator[](Rank r) const;  // ͨ���±��ȡԪ��
	// ������
	void permute(Vector<T>& v);  // �������е�Ԫ�ش���˳��
	void unsort(Rank lo, Rank hi);  // ��������һ�������ڴ���˳��
	// �е�����Ƚ���
	static bool lt(T* a, T* b) { return lt(a, b); }
	static bool lt(T a, T b) { return a < b; }
	static bool eq(T* a, T* b) { return eq(*a, *b); }
	static bool eq(T a, T b) { return a == b; }
	// �������
	Rank find(T const& e, Rank lo, Rank hi) const;
	// ����
	Rank insert(Rank r, T const& e);
	// ɾ��
	int remove(Rank lo, Rank hi);  // ɾ������
	T remove(Rank r);  // ɾ������Ԫ��
	// Ψһ��
	int deduplicate();  // ɾ�����������е��ظ�Ԫ��
	// ����
	void traverse(void(*visit)(T&));  // ���ú���ָ��ı���
	template<typename VST>
	void traverse(VST& visit);  // ���ú�������ı���
	/*
		�����������
	*/
	int disordered() const;  // �������б�
	int uniquify();  // �޳��ظ�Ԫ��
	Rank binarySearch1(Vector<T> const& v, T const& ele, Rank lo, Rank hi);  // ���ֲ��ң��ݹ���ʽ
	Rank binarySearch2(Vector<T> const& v, T const& ele, Rank lo, Rank hi);  // ���ֲ��ң��ǵݹ���ʽ
	/*
		������
	*/
	bool bubble(Rank lo, Rank hi);  // ɨ�轻��
	void bubbleSort(Rank lo, Rank hi);  // ð������

	void mergeSort(Rank lo, Rank hi);
	void merge(Rank lo, Rank mid, Rank hi);
	



};

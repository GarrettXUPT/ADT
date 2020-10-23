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
	T& operator[](Rank r) const;  // 通过下标获取元素
	// 置乱器
	void permute(Vector<T>& v);  // 将向量中的元素打乱顺序
	void unsort(Rank lo, Rank hi);  // 将向量的一个区间内打乱顺序
	// 判等器与比较器
	static bool lt(T* a, T* b) { return lt(a, b); }
	static bool lt(T a, T b) { return a < b; }
	static bool eq(T* a, T* b) { return eq(*a, *b); }
	static bool eq(T a, T b) { return a == b; }
	// 无序查找
	Rank find(T const& e, Rank lo, Rank hi) const;
	// 插入
	Rank insert(Rank r, T const& e);
	// 删除
	int remove(Rank lo, Rank hi);  // 删除区间
	T remove(Rank r);  // 删除单个元素
	// 唯一化
	int deduplicate();  // 删除无序向量中的重复元素
	// 遍历
	void traverse(void(*visit)(T&));  // 利用函数指针的遍历
	template<typename VST>
	void traverse(VST& visit);  // 利用函数对象的遍历
	/*
		针对有序向量
	*/
	int disordered() const;  // 有序性判别
	int uniquify();  // 剔除重复元素
	Rank binarySearch1(Vector<T> const& v, T const& ele, Rank lo, Rank hi);  // 二分查找，递归形式
	Rank binarySearch2(Vector<T> const& v, T const& ele, Rank lo, Rank hi);  // 二分查找，非递归形式
	/*
		排序器
	*/
	bool bubble(Rank lo, Rank hi);  // 扫描交换
	void bubbleSort(Rank lo, Rank hi);  // 冒泡排序

	void mergeSort(Rank lo, Rank hi);
	void merge(Rank lo, Rank mid, Rank hi);
	



};

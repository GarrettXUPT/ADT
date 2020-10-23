#pragma once
#include<iostream>
#include"ListNode.h"

template<typename T>
class List {
private:
	int _size; ListNodePosi(T) header; ListNodePosi(T) trailer;
protected:
	void init();  // 列表创建时候的初始化
	ListNodePosi(T) insertAsFirst(T const& e);
	ListNodePosi(T) insertAsLast(T const& e);
	ListNodePosi(T) insertBefore(ListNodePosi(T) p, T const& e);
	ListNodePosi(T) insertAfter(ListNodePosi(T) p, T const& e);
public:
	/*
		构造函数
	*/
	void copyNodes(ListNodePosi(T) p, int n);  // 基于复制的构造函数
	List(){}
	List(ListNodePosi(T) p, int n);
	List(List<T> const& L);  // 复制整体列表
	List(List<T> const& L, int r, int n);  // 复制L中自第r项起的n项
	// 删除
	T remove(ListNodePosi(T) p);  // 删除p处结点，并返回该值
	/*
		析构函数
	*/
	~List();
	// 清空列表
	int clear();
	// 唯一化
	int deduplicate();
	// 遍历
	void traverse(void(*visit)(T&));
	template<typename VST>
	void traverse(VST& visit);

	Rank size()const { return _size; }
	bool empty() const { return _size <= 0; }
	ListNodePosi(T) first() const { return header->succ; }
	ListNodePosi(T) last() const { return trailer->pred; }
	ListNodePosi(T) operator[](int r) const;
	ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p) const;

	/*
		针对有序列表
	*/
	int uniquify();
	ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const;  // 找到不大于e的最后者
	void insertionSort(ListNodePosi(T) p, int n);  // 以p为结点的前n个元素排序
	ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);
	void selectionSort(ListNodePosi(T) p, int n);  // 列表使用选择排序法
	void merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T) q, int m);
	void mergeSort(ListNodePosi(T)& p, int n);
};
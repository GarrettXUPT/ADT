#pragma once
#include<iostream>
#include"ListNode.h"

template<typename T>
class List {
private:
	int _size; ListNodePosi(T) header; ListNodePosi(T) trailer;
protected:
	void init();  // �б���ʱ��ĳ�ʼ��
	ListNodePosi(T) insertAsFirst(T const& e);
	ListNodePosi(T) insertAsLast(T const& e);
	ListNodePosi(T) insertBefore(ListNodePosi(T) p, T const& e);
	ListNodePosi(T) insertAfter(ListNodePosi(T) p, T const& e);
public:
	/*
		���캯��
	*/
	void copyNodes(ListNodePosi(T) p, int n);  // ���ڸ��ƵĹ��캯��
	List(){}
	List(ListNodePosi(T) p, int n);
	List(List<T> const& L);  // ���������б�
	List(List<T> const& L, int r, int n);  // ����L���Ե�r�����n��
	// ɾ��
	T remove(ListNodePosi(T) p);  // ɾ��p����㣬�����ظ�ֵ
	/*
		��������
	*/
	~List();
	// ����б�
	int clear();
	// Ψһ��
	int deduplicate();
	// ����
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
		��������б�
	*/
	int uniquify();
	ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const;  // �ҵ�������e�������
	void insertionSort(ListNodePosi(T) p, int n);  // ��pΪ����ǰn��Ԫ������
	ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);
	void selectionSort(ListNodePosi(T) p, int n);  // �б�ʹ��ѡ������
	void merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T) q, int m);
	void mergeSort(ListNodePosi(T)& p, int n);
};
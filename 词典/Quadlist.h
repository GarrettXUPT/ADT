#pragma once
#include"QuadlistNode.h"
#include"Dictionary.h"
#include"Entry.h"
#include"List.h"
template<typename T>
class Quadlist {
private:
	int _size;  // ��ģ
	QuadlistNodePosi(T) header;  QuadlistNodePosi(T) trailer;  // ͷ�ڱ���β�ڱ�
protected:
	void init();  // ����������ʱ��Ҫ�ĳ�ʼ��
	int clear();
public:
	// ���캯��
	Quadlist() { init(); }
	// ��������
	~Quadlist() { clear(); delete header; delete trailer; }
	// ֻ�����ʽӿ�
	Rank size() const { return _size };
	bool empty() const { return _size <= 0; }
	QuadlistPosi(T) first() const { return header->succ; }
	QuadlistPosi(T) last() const { return trailer->pred; }
	bool vaild(QuadlistNodePosi(T) p) {  // �ж�λ��p�Ƿ�Ϸ�
		return (trailer != p) && (header != p);
	};
	// ��д�ӿ�
	T remove(QuadlistNodePosi(T) p);   // ɾ��(�Ϸ�)λ��p���Ľ�㣬���ر�ɾ��������ֵ
	QuadlistNodePosi(T) insertAfterAbove(T const& e, QuadlistNodePosi(T) p, QuadlistNodePosi(T) b = nullptr);
	// ����
	void traverse(void(*)(T&));   // �Ժ���ָ��ķ�ʽ�Ը��ڵ���б���
	template<typename VST> void traverse(VST&);  // �Ժ�������ķ�ʽ�Ը��ڵ���б���
};

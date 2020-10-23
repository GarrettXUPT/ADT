#pragma once
/*
	��ת����
*/
#include"Dictionary.h"
#include"Entry.h"
#include"Quadlist.h"

template<typename K, typename V>
class Skiplist : public Dictionary<K, V>, public List<Quadlist<Entry<K, V>*>*> {
protected:
	bool skipSearch(ListNode<QuadlistNode<Entry<K, V>*>*>*& qlist, QuadlistNode<Entry<K, V>*>*& p, K& k);  // �Խ��p��ʼ����
public:
	int size() { return empty() ? last()->data->size(); } // ����������ȡ�ײ�Quadlist�Ĺ�ģ
	int level() { return List::size(); }  // ���
	bool put(K, V);
	V* get(K k);
	bool remove(K k);
};
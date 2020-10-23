#pragma once
/*
	跳转表类
*/
#include"Dictionary.h"
#include"Entry.h"
#include"Quadlist.h"

template<typename K, typename V>
class Skiplist : public Dictionary<K, V>, public List<Quadlist<Entry<K, V>*>*> {
protected:
	bool skipSearch(ListNode<QuadlistNode<Entry<K, V>*>*>*& qlist, QuadlistNode<Entry<K, V>*>*& p, K& k);  // 以结点p开始搜索
public:
	int size() { return empty() ? last()->data->size(); } // 词条总数，取底层Quadlist的规模
	int level() { return List::size(); }  // 层高
	bool put(K, V);
	V* get(K k);
	bool remove(K k);
};
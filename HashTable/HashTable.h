#pragma once
#include"Bitmap.h"
#include"Dictionary.h"
#include"Entry.h"

template<typename K, typename V>
class HashTable :public Dictionary<K, V> {
private:
	Entry<K, V>** ht;  // 桶数组，存放词条指针
	int M;  // 桶数组容量  
	int N;  // 词条数量
	Bitmap* lazyRemoval;
#define lazilyRemoved(x) (lazyRemoval->isExit(x))
#define markAsRemoved(x) (lazyremoval->set(x))
protected:
	int probe4Hit(const K& k);  // 沿着关键码k对应的查找链，找到词条匹配的桶
	int probe4Free(const K& k);  // 沿着关键码k对应的查找链，找到收割可用的空桶
	void rehash();  // 重散列算法，扩充桶的数目，保证装填因子在警戒线以下

public:
	HashTable(int c = 5);  // 创建一个容量不小于c的散列表
	~HashTable();  // 释放桶数组及其中个元素所指向的词条
	int size() { return N; }
	bool put(K, V);  // 插入词条，该词条不可雷同否则会导致失败
	V* get(K k);  // 读取
	bool remove(K k);
};
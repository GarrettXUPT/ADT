#pragma once
#include"Bitmap.h"
#include"Dictionary.h"
#include"Entry.h"

template<typename K, typename V>
class HashTable :public Dictionary<K, V> {
private:
	Entry<K, V>** ht;  // Ͱ���飬��Ŵ���ָ��
	int M;  // Ͱ��������  
	int N;  // ��������
	Bitmap* lazyRemoval;
#define lazilyRemoved(x) (lazyRemoval->isExit(x))
#define markAsRemoved(x) (lazyremoval->set(x))
protected:
	int probe4Hit(const K& k);  // ���Źؼ���k��Ӧ�Ĳ��������ҵ�����ƥ���Ͱ
	int probe4Free(const K& k);  // ���Źؼ���k��Ӧ�Ĳ��������ҵ��ո���õĿ�Ͱ
	void rehash();  // ��ɢ���㷨������Ͱ����Ŀ����֤װ�������ھ���������

public:
	HashTable(int c = 5);  // ����һ��������С��c��ɢ�б�
	~HashTable();  // �ͷ�Ͱ���鼰���и�Ԫ����ָ��Ĵ���
	int size() { return N; }
	bool put(K, V);  // ����������ô���������ͬ����ᵼ��ʧ��
	V* get(K k);  // ��ȡ
	bool remove(K k);
};
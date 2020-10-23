#include"HashTable.h"

template<typename K, typename V>
HashTable<K, V>::HashTable(int c) {
	M = 19;  // ����Ͱ������������Բ�����2*N��������ΪͰ������,�˴������������ĺ��������滻
	N = 0; ht = new Entry<K, V> * [M];  // ����Ͱ���飬��֤װ�����Ӳ�����50%
	memset(ht, 0, sizeof((Entry<K, V>*) * M);  // ��ʼ����Ͱ
	lazyRemoval = new Bitmap(M);  // ����ɾ����Ǳ���ͼ
}

/*
	Ϊ�˼���������ѡȡ�����Խ�������һ�����������������������ļ��б���
	�����ļ��еļ�¼����[low, n)��ȡ��С������
*/
int primeNLT(int low, int n, char* file) {
	Bitmap B(file, n);
	while (low < n) {
		if (!B.isExist(low)) {
			low++;
		}
		else {
			return low;
		}
	}
	return low;  // ��û���������������򷵻�n
}

template<typename K, typename V>
HashTable<K, V>::~HashTable() {
	for (int i = 0; i < M; ++i) {  // ����Ͱ
		if (ht[i]) release(ht[i]);  // �ͷŷǿյ�Ͱ
	}
	release(ht);  // �ͷ�Ͱ����
	release(lazyRemoval);  // �ͷ�����ɾ�����
}

// �������Ҳ���
// �ڲ��ҹ����У�ֻ�е�ǰͰΪ�ջ����ǲ�������ɾ����ǵ�ʱ�򣬲����ж�Ϊ����ʧ��
template<typename K, typename V>
int HashTable<K, V>::probe4Hit(const K& k) {
	int r = hashCode(k) % M;  // �������෨ȷ���ո���̽��Ͱ��ַ��Ԫ
	// ���Ų��������������г�ͻ���Լ�������ɾ����Ͱ
	while ((ht[r] && (k != ht[r]->key))) {
		r = (r + 1) % M;  // ������̽
	}
	return r;  // ����r[t]�Ƿ�Ϊ�ռ����жϲ����Ƿ�ʧ��
}

template<typename K, typename V>
V* HashTable<K, V>::get(K k) {
	int r = probe4Hit(k);
	return ht[r] ? &(ht[r]->value) : nullptr;
}

template<typename K, typename V>
bool HashTable<K, V>::remove(K k) {
	int r = probe4Hit(k);
	if (!ht[r]) {
		return false;
	}
	release(ht[r]); ht = nullptr;  // �ͷ�Ͱ�д���
	markAsRemoved(r); N--;  // ��������ɾ����ǣ������´ʵ�Ĺ�ģ
	return true;
}

template<typename K, typename V>
int HashTable<K, V>::probe4Free(const K& k) {
	// �˴���hashCode����ʹ�ù�ϣ�������д���
	int r = hashCode(k) % M;
	while (ht[r]) {
		r = (r + 1) % M;  // �ҵ�һ����Ͱ�������Ƿ�������ɾ�����
	}
	return r;
}

// װ������ΪN/M
template<typename K, typename V>
bool HashTable<K, V>::put(K k, V v) {  // ɢ�д�������
	if (ht[probe4Hit[k]]) return false;  // ���ô�����ɢ�б������У���ô�Ͳ����ظ�����
	int r = probe4Free(k);  // Ϊ����Ѱ��һ����Ͱ
	ht[r] = new Entry<K, V>(k, v); ++N;
	if (N * 2 > M) rehash();  // װ�����Ӹ���50�Ժ������ɢ��
}


// ��ɢ��
template<typename K, typename V>
void HashTable<K, V>::rehash() {
	int old_capcatity = M;
	Entry<K, V>** old_ht = ht;
	M = primeNLT(2 * M, 104896, "guess");  // ��Ͱ�������ӱ�
	ht = new Entry<K, V> * [M];
	memset(ht, 0, sizeof(Entry<K, V>*) * M);
	release(lazyRemoval); lazyRemoval = new Bitmap(M);
	for (int i = 0; i < old_capcatity; ++i) {
		if (old_ht[i]) {  // ����Ͱ�����еķ�0ֵ���뵽��Ͱ��
			put(old_ht[i]->key, old_ht[i]->value); 
		}
	}
}
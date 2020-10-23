#include"HashTable.h"

template<typename K, typename V>
HashTable<K, V>::HashTable(int c) {
	M = 19;  // 设置桶数组的容量，以不超过2*N的素数作为桶的容量,此处可由求素数的函数进行替换
	N = 0; ht = new Entry<K, V> * [M];  // 开辟桶数组，保证装填因子不超过50%
	memset(ht, 0, sizeof((Entry<K, V>*) * M);  // 初始化各桶
	lazyRemoval = new Bitmap(M);  // 懒惰删除标记比特图
}

/*
	为了加速素数的选取，可以将不超过一定数额的素数都算出并存在文件中备查
	根据文件中的记录，在[low, n)内取最小的素数
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
	return low;  // 若没有这样的素数，则返回n
}

template<typename K, typename V>
HashTable<K, V>::~HashTable() {
	for (int i = 0; i < M; ++i) {  // 检查各桶
		if (ht[i]) release(ht[i]);  // 释放非空的桶
	}
	release(ht);  // 释放桶数组
	release(lazyRemoval);  // 释放懒惰删除标记
}

// 词条查找操作
// 在查找过程中，只有当前桶为空或者是不带懒惰删除标记的时候，才能判断为查找失败
template<typename K, typename V>
int HashTable<K, V>::probe4Hit(const K& k) {
	int r = hashCode(k) % M;  // 采用求余法确定收割试探的桶地址单元
	// 沿着查找链，跳过所有冲突的以及被懒惰删除的桶
	while ((ht[r] && (k != ht[r]->key))) {
		r = (r + 1) % M;  // 线性试探
	}
	return r;  // 根据r[t]是否为空即可判断查找是否失败
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
	release(ht[r]); ht = nullptr;  // 释放桶中词条
	markAsRemoved(r); N--;  // 设置懒惰删除标记，并更新词典的规模
	return true;
}

template<typename K, typename V>
int HashTable<K, V>::probe4Free(const K& k) {
	// 此处的hashCode可以使用哈希函数进行代替
	int r = hashCode(k) % M;
	while (ht[r]) {
		r = (r + 1) % M;  // 找到一个空桶，不管是否有懒惰删除标记
	}
	return r;
}

// 装填因子为N/M
template<typename K, typename V>
bool HashTable<K, V>::put(K k, V v) {  // 散列词条插入
	if (ht[probe4Hit[k]]) return false;  // 若该词条在散列表中已有，那么就不必重复插入
	int r = probe4Free(k);  // 为词条寻找一个空桶
	ht[r] = new Entry<K, V>(k, v); ++N;
	if (N * 2 > M) rehash();  // 装填因子高于50以后进行重散列
}


// 重散列
template<typename K, typename V>
void HashTable<K, V>::rehash() {
	int old_capcatity = M;
	Entry<K, V>** old_ht = ht;
	M = primeNLT(2 * M, 104896, "guess");  // 将桶的容量加倍
	ht = new Entry<K, V> * [M];
	memset(ht, 0, sizeof(Entry<K, V>*) * M);
	release(lazyRemoval); lazyRemoval = new Bitmap(M);
	for (int i = 0; i < old_capcatity; ++i) {
		if (old_ht[i]) {  // 将旧桶数组中的非0值插入到新桶中
			put(old_ht[i]->key, old_ht[i]->value); 
		}
	}
}
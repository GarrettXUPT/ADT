#include"Skiplist.h"

template<typename K, typename V>
bool Skiplist<K, V>::skipSearch(ListNode<QuadlistNode<Entry<K, V>*>*>*& qlist, QuadlistNode<Entry<K, V>*>*& p, K& k)  // 以结点p开始搜索
{
	// 向右向下查找关键码
	while (true) {
		while (p->succ && (p->entry->key <= k)) {
			p = p->succ;
		}
		p = p->pred;
		if (p->pred && (k == p->entry->key)) return true;  // 查找完成
		qlist = qlist->succ;  // 转入下一层
		if (!qlist->succ) return false;  // 若已经穿透底层，则查找失败
		p = p->pred ? p->below : qlist->data->first();  // 转至当前塔的下一个节点
	}
}

template<typename K, typename V>
V* Skiplist<K, V>::get(K k) {
	if (this->empty()) {
		return nullptr;
	}
	ListNode<Quadlist<Entry<K, V>*>*>* qlist = first();  // 从顶层Quadlist开始
	QuadlistNode<Entry<K, V>*>* p = qlist->data->first();  // 从首结点开始
	return skipSearch(qlist, p, k) ? &(p->entry->value) : nullptr;
}

template<typename K, typename V>
bool Skiplist<K, V>::put(K k, V v) {  // 跳转表词条插入法
	Entry<K, V>* e = new Entry<K, V>(k, v);
	if (this->empty()) { return insertAsFirst(new Quadlist<Entry<K, V>*>); }  // 插入首个词条
	ListNode<Quadlist<Entry<K, V>*>*>* qlist = first();  // 从顶层列表开始
	QuadlistNode<Entry<K, V>*>* p = qlist->data->first();  // 从首结点开始查起
	if (skipSearch(qlist, p, k)) {  // 查找当前适当的插入位置
		while (p->below) p = p->below;  // 若有相同的词条，就强制转到塔底
	}
	qlist = last();  // 紧随着p的右侧，一座新塔要自底而上逐层生长
	QuadlistNode<Entry<K, V>*>* b = qlist->data->insertAfterAbove(e, p);  // 将e插入到p的右侧，作为塔的基座
	while (rand() % 2) {  // 经过生长逐层减半机制，判断新塔是否还需要长高一层
		while (qlist->data->vaild(p) && !p->above) p = p->pred;  // 找出不低于此高度的最近前驱
		if (!qlist->data->vaild(p)) {  // 若该前驱是header
			if (qlist == first()) {  // 当前已经是最顶层
				this->insertAsFirst(new Quadlist<Entry<K, V>*>());  // 首先要创建一层
			}
			p = qlist->pred->data->first()->pred;  // 将p转至上一层的skiplist的header
		}
		else {
			p = p->above;  // 将p提升至该高度
		}
		qlist = qlist->pred;  // 上升一层
		b = qlist->data->insertAfterAbove(e, p, b);  // 将新节点插入到p之后，b之上
	}
	return true;
}

template<typename K, typename V>
bool Skiplist<K, V>::remove(K k) {
	if (this->empty()) return false;   // 此为空表
	ListNode<Quadlist<Entry<K, V>*>*>* qlist = first();  // 从顶层Quadlist的首结点开始
	QuadlistNode<Entry<K, V>*>* p = qlist->data->first();

	if (!skipSearch(qlist, p, k)) return false;  // 若不存在，则删除失败
	do {
		QuadlistNode<Entry<K, V>*>* lower = p->below;  // 记录下一层的结点
		qlist->data->remove(p);  // 删除当前层结点
		p = lower;
		qlist = qlist->succ;
	} while (qlist->succ);
	while (!this->empty() && first()->data->empty()) {
		List::remove(first());  // 清除可能不含词条的顶层Quadlist
	}
	return true;
}
#include"Skiplist.h"

template<typename K, typename V>
bool Skiplist<K, V>::skipSearch(ListNode<QuadlistNode<Entry<K, V>*>*>*& qlist, QuadlistNode<Entry<K, V>*>*& p, K& k)  // �Խ��p��ʼ����
{
	// �������²��ҹؼ���
	while (true) {
		while (p->succ && (p->entry->key <= k)) {
			p = p->succ;
		}
		p = p->pred;
		if (p->pred && (k == p->entry->key)) return true;  // �������
		qlist = qlist->succ;  // ת����һ��
		if (!qlist->succ) return false;  // ���Ѿ���͸�ײ㣬�����ʧ��
		p = p->pred ? p->below : qlist->data->first();  // ת����ǰ������һ���ڵ�
	}
}

template<typename K, typename V>
V* Skiplist<K, V>::get(K k) {
	if (this->empty()) {
		return nullptr;
	}
	ListNode<Quadlist<Entry<K, V>*>*>* qlist = first();  // �Ӷ���Quadlist��ʼ
	QuadlistNode<Entry<K, V>*>* p = qlist->data->first();  // ���׽�㿪ʼ
	return skipSearch(qlist, p, k) ? &(p->entry->value) : nullptr;
}

template<typename K, typename V>
bool Skiplist<K, V>::put(K k, V v) {  // ��ת��������뷨
	Entry<K, V>* e = new Entry<K, V>(k, v);
	if (this->empty()) { return insertAsFirst(new Quadlist<Entry<K, V>*>); }  // �����׸�����
	ListNode<Quadlist<Entry<K, V>*>*>* qlist = first();  // �Ӷ����б�ʼ
	QuadlistNode<Entry<K, V>*>* p = qlist->data->first();  // ���׽�㿪ʼ����
	if (skipSearch(qlist, p, k)) {  // ���ҵ�ǰ�ʵ��Ĳ���λ��
		while (p->below) p = p->below;  // ������ͬ�Ĵ�������ǿ��ת������
	}
	qlist = last();  // ������p���Ҳ࣬һ������Ҫ�Ե׶����������
	QuadlistNode<Entry<K, V>*>* b = qlist->data->insertAfterAbove(e, p);  // ��e���뵽p���Ҳ࣬��Ϊ���Ļ���
	while (rand() % 2) {  // ����������������ƣ��ж������Ƿ���Ҫ����һ��
		while (qlist->data->vaild(p) && !p->above) p = p->pred;  // �ҳ������ڴ˸߶ȵ����ǰ��
		if (!qlist->data->vaild(p)) {  // ����ǰ����header
			if (qlist == first()) {  // ��ǰ�Ѿ������
				this->insertAsFirst(new Quadlist<Entry<K, V>*>());  // ����Ҫ����һ��
			}
			p = qlist->pred->data->first()->pred;  // ��pת����һ���skiplist��header
		}
		else {
			p = p->above;  // ��p�������ø߶�
		}
		qlist = qlist->pred;  // ����һ��
		b = qlist->data->insertAfterAbove(e, p, b);  // ���½ڵ���뵽p֮��b֮��
	}
	return true;
}

template<typename K, typename V>
bool Skiplist<K, V>::remove(K k) {
	if (this->empty()) return false;   // ��Ϊ�ձ�
	ListNode<Quadlist<Entry<K, V>*>*>* qlist = first();  // �Ӷ���Quadlist���׽�㿪ʼ
	QuadlistNode<Entry<K, V>*>* p = qlist->data->first();

	if (!skipSearch(qlist, p, k)) return false;  // �������ڣ���ɾ��ʧ��
	do {
		QuadlistNode<Entry<K, V>*>* lower = p->below;  // ��¼��һ��Ľ��
		qlist->data->remove(p);  // ɾ����ǰ����
		p = lower;
		qlist = qlist->succ;
	} while (qlist->succ);
	while (!this->empty() && first()->data->empty()) {
		List::remove(first());  // ������ܲ��������Ķ���Quadlist
	}
	return true;
}
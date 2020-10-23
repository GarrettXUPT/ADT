#pragma once
#include"QuadlistNode.h"
#include"Dictionary.h"
#include"Entry.h"
#include"List.h"
template<typename T>
class Quadlist {
private:
	int _size;  // 规模
	QuadlistNodePosi(T) header;  QuadlistNodePosi(T) trailer;  // 头哨兵，尾哨兵
protected:
	void init();  // 创建四链表时需要的初始化
	int clear();
public:
	// 构造函数
	Quadlist() { init(); }
	// 析构函数
	~Quadlist() { clear(); delete header; delete trailer; }
	// 只读访问接口
	Rank size() const { return _size };
	bool empty() const { return _size <= 0; }
	QuadlistPosi(T) first() const { return header->succ; }
	QuadlistPosi(T) last() const { return trailer->pred; }
	bool vaild(QuadlistNodePosi(T) p) {  // 判断位置p是否合法
		return (trailer != p) && (header != p);
	};
	// 可写接口
	T remove(QuadlistNodePosi(T) p);   // 删除(合法)位置p处的结点，返回被删除结点的数值
	QuadlistNodePosi(T) insertAfterAbove(T const& e, QuadlistNodePosi(T) p, QuadlistNodePosi(T) b = nullptr);
	// 遍历
	void traverse(void(*)(T&));   // 以函数指针的方式对各节点进行遍历
	template<typename VST> void traverse(VST&);  // 以函数对象的方式对各节点进行遍历
};

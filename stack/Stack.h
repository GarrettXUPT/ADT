#pragma once
#include"Vector.cpp"

template<typename T>
class Stack : public Vector<T> {
public:
	void push(T const& e);
	T pop();
	T& top();
	Rank size();
	bool empty();
};



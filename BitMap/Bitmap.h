#pragma once
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

class Bitmap
{
private:
    vector<size_t> v;
public:
    Bitmap(size_t num) : v((num >> 5) + 1, 0) {}
    //set 1，将输入的数字在位图上进行标记
    void set(size_t num);
    //set 0，将该数值从位图上进行删除
    void clean(size_t num)
    {
        v[num >> 5] &= ~(1 << (num & 31));
    }
    //判断该数在位图中是否存在
    bool isExist(size_t num)
    {
        bool is = 0;
        size_t r = 1 << (num & 31); //r represents remainder
        if (r == (v[num >> 5] & r))
            is = 1;
        return is;
    }
};

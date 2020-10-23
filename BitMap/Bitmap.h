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
    //set 1���������������λͼ�Ͻ��б��
    void set(size_t num);
    //set 0��������ֵ��λͼ�Ͻ���ɾ��
    void clean(size_t num)
    {
        v[num >> 5] &= ~(1 << (num & 31));
    }
    //�жϸ�����λͼ���Ƿ����
    bool isExist(size_t num)
    {
        bool is = 0;
        size_t r = 1 << (num & 31); //r represents remainder
        if (r == (v[num >> 5] & r))
            is = 1;
        return is;
    }
};

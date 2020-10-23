
#include"Bitmap.h"
/*
    在C/C++中int类型有4个字节，也就是32位。当我们有1000万条不同数据时，我们只需要1000万个位来表示，也就是10000000/(8*1024*1024)MB，大约为1.25MB。
  我们可以用一个unsigned int类型的数组或者向量来表示位图，假设我们定义vector a，则 第i位可表示为a[i/32]的i%32位（其中，32*N+r = i，r为i%32，也就是i/32的余数）。
  由于计算机对位的操作比乘除法更有效率，这里计算i/32可以用位移操作：i>>5；计算i%32可以用1&31
*/

class Bitmap
{
private:
    vector<size_t> v;
public:
    Bitmap(size_t num) : v((num >> 5) + 1, 0) {}
    //set 1
    void set(size_t num)
    {
        //v[num >> 5] |= (1 << (num & 31)); // num & 31 equals num % 32  大端模式
        v[num >> 5] |= ((1 << 31) >> (num & 31)); // i & 31 equals i % 32 小端模式
    }
    //set 0
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
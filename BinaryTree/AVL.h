#pragma once
#include"BST.h"
/*
	������������������ȡ������߶ȣ����ڽڵ���Ŀ�̶�������£�Ӧ�þ����ܵؽ��͸߶ȣ���Ӧ�ش������̬��������Ҳ����
	ʹ���������߶Ⱦ����ܽӽ���ȫ�����御���ܵ�ƽ��
	��n�������ɵĶ����������ĸ߶��ǲ�����С��logn(�ö�������ȡ��)��������Ϊ�ö����Ķ���������Ϊ����ƽ�������
	�ڲ�����Ӱ��������������������Ľ������Ӷ�����£��ʵ����ɱ�׼֮���ƽ���Ծ����ʶ�ƽ�������

	ʵ�ֶ������Ļ�����˼�������ʶȵطſ�ƽ���Ե����б�׼��������ƽ�����ĸ��ǵķ�Χ�Լ������ж�������������ռ�ı���
	Ȼ�󣬰���ĳһ��׼�򣬶����п��ܵ����������ȼ��໮�֡���Щ���ַ����ľ���֮�����ڣ�������֤��ÿһ�ȼ��඼����
	һ��ƽ��������������Ҫ���ǣ�������̬�޸�֮����ƽ�����һ���������Ϳ��Խ�С�Ĵ��ۣ��ָ�Ϊһ������ȼ۵�ƽ�������
*/

/*
	�ȼ۶������������жϣ��������������ͬ���������������໥�ȼ�
	�����ȼ۵Ķ������������ص���ǣ����¿ɱ䣬���Ҳ���
	��ʧ�������ת��Ϊ�ȼ۵���ȫ������������Χ���ض�������ת
*/

/*
	��ȫ�������и��ڵ��ƽ�����ӷ�0��1��������ȫ��������ΪAVL�����ڽ������Ӷȵ������£�AVL��Ҳ��ƽ���
	AVL���볣��Ķ�����һ����Ҳ֧�ֲ���ɾ�����������ǽ��в����Ժ󣬾Ͳ����Ա�֤����AVL��
*/
#define Balanced(x) (stature((x).lChild) == (stature((x).rChild))  // ����ƽ������
#define BalFac(x) ((stature(x).lChild) - (stature(x).rChild))  // ƽ������,��Ϊ���������߶�֮��
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2))  // AVLƽ������

/*
	�ָ�ƽ��ĵ�������
	�����Һ��ӽڵ���ѡ������ߣ����ȸߣ����븸��ͬ��������
*/
#define tallerChild(x) (stature((x)->lChild) > stature((x)->rChild) ? (x)->lChild : (stature((x)->rChild)) > (stature((x)->lChild)) (x)->rChild : (IsLChild(*(x)) ? (x)->lChild : (x)->rChild)))

template<typename T> 
class AVL : public BST<T> {
public:
	BinNodePosi(T) insert(const T& e);
	bool remove(const T& e);
};

#include "stdafx.h"
#include <vector>
#include <initializer_list>
#include <tuple>

//=======================================================================
// { }�����ų�ʼ�����ʽ�ļ����÷�                                                                
//=======================================================================
struct	C
{
	int a;
	int b;
	string s;
	C* p;
	//virtual ~C() {}
};

void main()
{
	string ss = "dwd";

	//���Ը����ṹ����ʱ{}��ֵ�������ڽṹ�ı�������
	C c { 2, 3, ss };

	//���Ը�ֵ��initialize_list
	initializer_list<int> b = { 1,1,0,1 };

	//���Ը�ֵ��tuple��
	tuple<int, int, string> tp = { 1,2,"dwd" };

	//��ֵ��tupleʱ��������ȱʧ���ֶ�
	//tuple<int, int, string, int> tp = { 1,2,"dwd" };  //error
	
}
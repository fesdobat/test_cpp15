#include "stdafx.h"
#include <vector>
#include <initializer_list>
#include <tuple>

//=======================================================================
// { }大括号初始化表达式的几种用法                                                                
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

	//可以赋给结构。此时{}中值可以少于结构的变量数量
	C c { 2, 3, ss };

	//可以赋值给initialize_list
	initializer_list<int> b = { 1,1,0,1 };

	//可以赋值给tuple。
	tuple<int, int, string> tp = { 1,2,"dwd" };

	//赋值给tuple时，不能有缺失的字段
	//tuple<int, int, string, int> tp = { 1,2,"dwd" };  //error
	
}
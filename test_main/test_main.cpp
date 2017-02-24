#include "stdafx.h"

#include "test.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <iterator>
#include <list>
#include <numeric>
#include <stdarg.h>
#include <functional>
#include <set>
#include <chrono>
#include <regex>
#include <array>
#include <map>
#include <tuple>
#include <type_traits>
struct B;
struct A
{
	A() { cout << 1 <<endl; }
	~A() { cout << 11 <<endl; }
	shared_ptr<B> pb;
};

struct B
{
	B() { cout << 2 <<endl ; }
	~B() { cout << 21 <<endl ; }
	shared_ptr<A> pa;
};

struct C
{
	C() { cout << 3 <<endl ; }
	~C() { cout << 31 <<endl; }
	shared_ptr<B> pb;
};


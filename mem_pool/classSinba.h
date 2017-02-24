#include "mem_pool.h"

class Sinba
{
public:
	Sinba();
	~Sinba();

	static void* operator new(size_t size)
	{
		return s_pool.alloc();
	}
	static void operator delete(void* p)
	{
		return s_pool.free(p);
	}

public:
	int a;

private:
	static memory_pool<Sinba> s_pool;
};


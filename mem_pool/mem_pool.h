#include <vector>
#include <iostream>

using namespace std;

template<class T>
struct memory_pool
{
	static_assert(sizeof(T)>=sizeof(void*), "mem_pool's template class T is too small");
	struct node
	{
		node* next;
	};

	node* head= nullptr;
	vector<void*> _nodes;

	void* alloc()
	{
		if (!head)
		{
			head = (node*)::operator new(1024 * sizeof(T));
			_nodes.push_back(head);
			for (size_t i = 0; i < 1024; i++)
			{
				head[i].next = (node*)((char*)&head[i] + sizeof(T));
			}
			head[1023].next = NULL;
		}
		node* _ptr = head;
		head = head->next;
		return _ptr;
	}

	void free(void* _ptr)
	{
		node* p = (node*)_ptr;
		p->next = head;
		head = p;
	}


	~memory_pool()
	{
		for (auto& p : _nodes)
		{
			::operator delete(p);
		}
	}

};


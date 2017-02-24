// spaceworld_demo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <map>
#include <functional>
#include <assert.h>
#include <vector>
#include <list>
#include <algorithm>
#include <typeinfo>
#include <typeindex>
#include <set>
#include "spaceworld_impl.h"

#include <vector>

struct GameObject;

using CollisionFunc = function<void(GameObject*, GameObject*)>;

void DefaultCollision(GameObject * obj1, GameObject * obj2);

GameObject* GetObject(GameObject *& Obj);

bool g_debugShow1 = false;


struct GameObject
{
	
	static int aaaddwdwoicdwdw;
	//virtual int id() { return 0; }
	//virtual void get_deriveship(vector<int>& c) { c.push_back(0); }
	virtual ~GameObject() =0 {}

	//数据操作
	virtual const char* name() { return "DummyObj"; }

	virtual void OnCollision(GameObject* obj)
	{
		DefaultCollision(obj, this);
	}
};

struct	SpaceStation : public GameObject
{
	//virtual int id() { return 1; }
	//virtual void get_deriveship(vector<int>& c) { c.push_back(1); GameObject::get_deriveship(c); }

	virtual const char* name() { return "SpaceStation"; }

	virtual void OnCollision(GameObject* obj) override
	{
		GameObject::OnCollision(obj);
	}
};

struct	SpaceShip : public GameObject
{
	//virtual int id() { return 2; }
	//virtual void get_deriveship(vector<int>& c) { c.push_back(2); GameObject::get_deriveship(c); }

	virtual const char* name() { return "SpaceShip"; }


	virtual void OnCollision(GameObject* obj) override
	{
		GameObject::OnCollision(obj);
	}
};

struct	Asteroid : public GameObject
{
	//virtual int id() { return 3; }
	//virtual void get_deriveship(vector<int>& c) { c.push_back(3); GameObject::get_deriveship(c); }

	virtual const char* name() { return "Asteroid"; }

	virtual void OnCollision(GameObject* obj) override
	{
		GameObject::OnCollision(obj);
	}
};

struct	WarShip : public SpaceShip
{
	//virtual int id() { return 4; }
	//virtual void get_deriveship(vector<int>& c) { c.push_back(4); SpaceShip::get_deriveship(c); }
	
	virtual const char* name() { return "Warship"; }

	virtual void OnCollision(GameObject* obj) override
	{
		SpaceShip::OnCollision(obj);
	}
};

struct UltraAsteroid : public Asteroid
{
	//virtual int id() { return 5; }
	//virtual void get_deriveship(vector<int>& c) { c.push_back(5); Asteroid::get_deriveship(c); }

	virtual const char* name() { return "UltraAsteroid"; }

};

//registery GameObject's class hierarchy
auto& ClassMap()
{
	static auto _ClassMap = []()
	{
		map<type_index, type_index> _ClassMap;
		struct
		{
			decltype(_ClassMap)& map;
			template<class U, class V>
			void registry() {
				map.insert(make_pair(type_index(typeid(U)), type_index(typeid(V))));
			};
		} reg{ _ClassMap };

		//reg.registry<GameObject, void>();
		reg.registry<SpaceStation, GameObject>();
		reg.registry<SpaceShip, GameObject>();
		reg.registry<Asteroid, GameObject>();
		reg.registry<WarShip, SpaceShip>();
		reg.registry<UltraAsteroid, Asteroid>();
		 
		return _ClassMap;
	}();
	return _ClassMap;
}
ClassMapType& ClassMap_test()
{
	return ClassMap();
}
CollisionMapType& CollisionMap()
{
	//static auto _CollisionMap = InitCollisionMap();
	static auto _CollisionMap = []()
	{
		map<pair<type_index, type_index>, CollisionFunc> _CollisionMap;

		struct
		{
			decltype(_CollisionMap)& map;
			template<class U, class V>
			void registry(CollisionFunc f) 
			{
				type_index i1(typeid(U));
				type_index i2(typeid(V));
				i1 > i2 ? swap(i1, i2) : 0;
				map.insert(make_pair(make_pair(i1, i2), f));
			};

			template<class U, class V>
			CollisionFunc getfunc()
			{
				type_index i1(typeid(U));
				type_index i2(typeid(V));
				i1 > i2 ? swap(i1, i2) : 0;
				return map[make_pair(i1, i2)];
			}
		} reg{ _CollisionMap };

		reg.registry<GameObject, GameObject>(
			[](GameObject* obj1, GameObject* obj2) {printf("%s with %s, no damage!", obj1->name(), obj2->name()); });
		
		reg.registry<SpaceStation, SpaceShip>(
			[](GameObject* obj1, GameObject* obj2) {printf("%s parking in %s!", obj2->name(), obj1->name()); });
		
		reg.registry<SpaceStation, Asteroid>(
			[](GameObject* obj1, GameObject* obj2) {printf("%s with %s, both damage!", obj2->name(), obj1->name()); });
		
		reg.registry<SpaceShip, Asteroid>(reg.getfunc<SpaceStation, Asteroid>());
		
		reg.registry<Asteroid, Asteroid>(
			[](GameObject* obj1, GameObject* obj2) {printf("%s with %s, more asteroid!", obj2->name(), obj1->name()); });
		
		reg.registry<Asteroid, WarShip>(
			[](GameObject* obj1, GameObject* obj2) {printf("%s with %s, asteroid killed!", obj2->name(), obj1->name()); });
		
		reg.registry<SpaceStation, UltraAsteroid>(
			[](GameObject* obj1, GameObject* obj2) {printf("%s with %s, ultraasteroid kill everything!", obj2->name(), obj1->name()); });
		
		reg.registry<SpaceShip, UltraAsteroid>(reg.getfunc<SpaceStation, UltraAsteroid>());


		return _CollisionMap;
	}();
	return _CollisionMap;
}

auto FindCollisionFunc(type_index i1, type_index i2)
{
	//遍历类层次，找到自己的或者最近父类的碰撞函数
	list<CollisionFunc> procs;

	//生成一个index_type的所有父类
	auto get_deriveship = [](type_index i)
	{
		vector<type_index> col;
		while (1)
		{
			col.emplace_back(i);
			auto it = ClassMap().find(i);
			if (it != ClassMap().end())
			{
				i = it->second;
			}
			else
				break;
		}
		return col;
	};

	vector<type_index> cli1 = get_deriveship(i1);
	vector<type_index> cli2 = get_deriveship(i2);
#ifdef _DEBUG
	if (g_debugShow1)
	{
		auto print_decurship = [](auto& c, char* s)
		{
			cout << s;
			for (auto& i : c)
			{
				cout << i.name() << ' ';
			}
			cout << endl;
		};

		print_decurship(cli1, "Obj1: ");
		print_decurship(cli2, "obj2; ");
	}
#endif // _DEBUG

	//单次遍历中找到第一个可用的即返回
	auto seek_in_deriveshipi = [&cli1, &cli2, &procs]()
	{
		for (size_t i = 0; i < cli1.size(); i++)
		{
			for (size_t j = 0; j < cli2.size(); j++)
			{
				auto i1 = cli1[i];
				auto i2 = cli2[j];
				i1 > i2 ? swap(i1, i2) : 0;
				auto it = CollisionMap().find(make_pair(i1, i2));
				if (it != CollisionMap().end())
				{
#ifdef _DEBUG
					if (g_debugShow1)
						printf("CollisionFunc Find For: %s, %s\n", i1.name(), i2.name());
#endif // _DEBUG
					procs.emplace_back(it->second);
					goto Quit_for_fori;
				}
			}
		}
		Quit_for_fori : 0;
	};

	//双次遍历，以解决【矛和盾】问题
	seek_in_deriveshipi();
	swap(cli1, cli2);
	seek_in_deriveshipi();

	//去除重复proc
	procs.unique([](auto& lhs, auto& rhs) {
		return (lhs).target_type().hash_code()
			== (rhs).target_type().hash_code();
	});

#ifdef _DEBUG
	if (g_debugShow1)
	{
		cout << "final proc pool: ";
		for (auto& f : procs)
		{
			cout << f.target_type().name() << ' ';
		}
		cout << endl;
	}
#endif

	return procs;
}
void FillCollisionMap()
{
	auto map = CollisionMap();
	set<type_index> indexs;
	for (auto& i : map)
	{
		indexs.emplace(i.first.first);
		indexs.emplace(i.first.second);
	}

	printf("filling collisionmap...\n");
	int i = 0;

	for (auto& e1 : indexs)
	{
		for (auto& e2 : indexs)
		{
			auto i1 = e1, i2 = e2;
			i1 > i2 ? swap(i1, i2) : 0;
			auto procs = FindCollisionFunc(i1, i2);
			if (procs.empty())
				printf("no collisonfunc found for : %s, %s\n", i1.name(), i2.name());
			else if (procs.size() == 1)
			{
				if (map.count(make_pair(i1, i2)))
				{
					//printf("collisonfunc found for : %s, %s\n", i1.name(), i2.name());
					//printf("collsionfunc already exists. \n");
				}
				else
				{
					printf("fill %d: %s, %s,(%s)\n", ++i, i1.name(), i2.name(), procs.front().target_type().name());
					map.emplace(make_pair(i1, i2), procs.front());
				}
			}
			else
			{
				printf("more than 1 collisonfuncs found for : %s, %s\n", i1.name(), i2.name());
				printf("do not fill.\n");
			}
		}
	}
	printf("%d entrys filled... map total entrys : %d\n", i, map.size());
	CollisionMap().swap(map);
}
void show_type(const type_info& info)
{
	cout << info.name() << endl;
}
void DefaultCollision(GameObject* obj1, GameObject* obj2)
{
	type_index i1(typeid(*obj1));
	type_index i2(typeid(*obj2));
	i1 > i2 ? swap(i1, i2): 0; //obj和type_index的大小没关系，这里不用跟着换
	auto getproci = [](type_index i1, type_index i2)->CollisionFunc*
	{
		i1 > i2 ? swap(i1, i2) : 0;
		auto it = CollisionMap().find(make_pair(i1, i2));
		if (it != CollisionMap().end())
		{
#ifdef _DEBUG
			if (g_debugShow1)
				printf("CollisionFunc Find For: %s, %s\n", i1.name(), i2.name());
#endif // _DEBUG
			return &(it->second);
		}
		else
			return nullptr;
	};

	CollisionFunc* proc = getproci(i1, i2);
	if (proc)
		(*proc)(obj1, obj2);
	else
	{
		auto procs = FindCollisionFunc(i1, i2);
		for (auto& f : procs)
		{
			f(obj1, obj2);
		}
	}
}

void main()
{
	ClassMap();
	CollisionMap();
	FillCollisionMap();

 	while (1)
	{
		GameObject* obj1, *obj2;
		while (!GetObject(obj1)) {};
		while (!GetObject(obj2)) {};

		DefaultCollision(obj1, obj2);
		cout << endl << endl;
		delete obj1;
		delete obj2;
	}
}


GameObject* GetObject(GameObject*& Obj)
{
	cout << "please input a number within [1,2,3,4,5](0 to exit)" << endl;

	char i;
	cin >> i;
	switch (i)
	{
	case '1':
		Obj = new SpaceStation;
		break;
	case '2':
		Obj = new SpaceShip;
		break;
	case '3':
		Obj = new Asteroid;
		break;
	case '4':
		Obj = new WarShip;
		break;
	case '5':
		Obj = new UltraAsteroid;
		break;
	case '0':
		exit(1);
		break;
	case '`':
		g_debugShow1 = !g_debugShow1;
	default:
		Obj = nullptr;
	}
	if (!Obj)
		cout << "No Obj crearted!" << endl;
	return Obj;
}

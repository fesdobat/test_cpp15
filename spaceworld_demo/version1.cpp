// spaceworld_demo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <map>
#include <functional>


struct GameObject
{
	virtual int id() { return 0; }
	virtual ~GameObject() {}
};

struct	SpaceStation : public GameObject
{
	virtual int id() { return 1; }
};

struct	SpaceShip : public GameObject
{
	virtual int id() { return 2; }
};

struct	Asteroid : public GameObject
{
	virtual int id() { return 3; }
};

void GetObject(GameObject*& Obj)
{
	cout << "please input a number" << endl;

	int i;
	cin >> i;
	switch (i)
	{
	case 1:
		Obj = new SpaceStation;
		break;
	case 2:
		Obj = new SpaceShip;
		break;
	case 3:
		Obj = new Asteroid;
		break;
	case 0:
		exit(1);
	default:
		Obj = nullptr;
	}
}

auto InitCollisionMap()
{
	map<pair<int, int>, function<void(GameObject*, GameObject*)>> CollisionMap;
	
	CollisionMap[make_pair(1, 1)] =
		[](GameObject* obj1, GameObject* obj2) {cout << "station with station, no damage!" << endl; };
	CollisionMap[make_pair(1, 2)] =
		[](GameObject* obj1, GameObject* obj2) {cout << "ship park in station!" << endl; };
	CollisionMap[make_pair(2, 2)] =
		[](GameObject* obj1, GameObject* obj2) {cout << "ship with ship, no damage!" << endl; };
	CollisionMap[make_pair(1, 3)] =
		[](GameObject* obj1, GameObject* obj2) {cout << "asteroid with station, both destroyed!" << endl; };
	CollisionMap[make_pair(2, 3)] =
		[](GameObject* obj1, GameObject* obj2) {cout << "asteroid with ship, both destroyed!" << endl; };
	CollisionMap[make_pair(3, 3)] =
		[](GameObject* obj1, GameObject* obj2) {cout << "asteroid with asteroid, more asteroid!" << endl; };

	return CollisionMap;
}
void Collision(GameObject* obj1, GameObject* obj2)
{
	int i = obj1->id(), j = obj2->id();
	i > j ? swap(i, j), swap(obj1, obj2) : 0;
	static auto CollisionMap = InitCollisionMap();

	auto it = CollisionMap.find(make_pair(i, j));
	if(it != CollisionMap.end())
	{
		auto func = it->second;
		func(obj1, obj2);
	}
}

void main()
{
	while (1)
	{
		GameObject* obj1, *obj2;
		GetObject(obj1);
		GetObject(obj2);

		Collision(obj1, obj2);

		delete obj1;
		delete obj2;
	}
}


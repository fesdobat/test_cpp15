// spaceworld_demo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <map>
#include <functional>
#include <assert.h>

struct GameObject;

auto& CollisionMap();

void DefaultCollision(GameObject * obj1, GameObject * obj2);

void Collision(GameObject * obj1, GameObject * obj2);

void GetObject(GameObject *& Obj);

struct GameObject
{
	virtual int id() { return 0; }
	virtual ~GameObject() {}

	virtual void OnCollision(GameObject* obj) = 0
	{
		DefaultCollision(obj, this);
	}
};

struct	SpaceStation : public GameObject
{
	virtual int id() { return 1; }
	virtual void OnCollision(GameObject* obj) override
	{
		GameObject::OnCollision(obj);
	}
};

struct	SpaceShip : public GameObject
{
	virtual int id() { return 2; }
	virtual void OnCollision(GameObject* obj) override
	{
		GameObject::OnCollision(obj);
	}
};

struct	Asteroid : public GameObject
{
	virtual int id() { return 3; }
	virtual void OnCollision(GameObject* obj) override
	{
		GameObject::OnCollision(obj);
	}
};


auto& CollisionMap()
{
	//static auto _CollisionMap = InitCollisionMap();
	static auto _CollisionMap = []()->auto {
		map<pair<int, int>, function<void(GameObject*, GameObject*)>> _CollisionMap;

		_CollisionMap[make_pair(1, 1)] =
			[](GameObject* obj1, GameObject* obj2) {cout << "station with station, no damage!" << endl; };
		_CollisionMap[make_pair(1, 2)] =
			[](GameObject* obj1, GameObject* obj2) {cout << "ship park in station!" << endl; };
		_CollisionMap[make_pair(2, 2)] =
			[](GameObject* obj1, GameObject* obj2) {cout << "ship with ship, no damage!" << endl; };
		_CollisionMap[make_pair(1, 3)] =
			[](GameObject* obj1, GameObject* obj2) {cout << "asteroid with station, both destroyed!" << endl; };
		_CollisionMap[make_pair(2, 3)] =
			[](GameObject* obj1, GameObject* obj2) {cout << "asteroid with ship, both destroyed!" << endl; };
		_CollisionMap[make_pair(3, 3)] =
			[](GameObject* obj1, GameObject* obj2) {cout << "asteroid with asteroid, more asteroid!" << endl; };

		return _CollisionMap;
	}();
	return _CollisionMap;
}

void DefaultCollision(GameObject* obj1, GameObject* obj2)
{
	int i = obj1->id(), j = obj2->id();
	i > j ? swap(i, j), swap(obj1, obj2) : 0;

	auto it = CollisionMap().find(make_pair(i, j));
	if (it != CollisionMap().end())
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
		cout << endl << endl;
		delete obj1;
		delete obj2;
	}
}

void Collision(GameObject* obj1, GameObject* obj2)
{
	int i = obj1->id(), j = obj2->id();
	i > j ? swap(i, j), swap(obj1, obj2) : 0;

	obj2->OnCollision(obj1);
}


void GetObject(GameObject*& Obj)
{
	cout << "please input a number within [1,2,3](0 to exit)" << endl;

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

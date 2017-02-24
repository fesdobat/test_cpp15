#pragma once

#include <map>
#include <typeindex>
#include <functional>

struct GameObject;

using namespace std;

using CollisionFunc = function<void(GameObject*, GameObject*)>;

using CollisionMapType = map<pair<type_index, type_index>, CollisionFunc>;

CollisionMapType& CollisionMap();

void FillCollisionMap();

using ClassMapType = map<type_index, type_index>;

ClassMapType& ClassMap_test();
//
//  House.cpp
//  easyLua
//
//  Created by Katekov Anton on 8/16/17.
//  Copyright © 2017 katekovanton. All rights reserved.
//

#include "House.hpp"
#include "Person.hpp"



House::House(const std::vector<std::shared_ptr<Person>> &roomers, const GSize2D &size)
:_size(size)
,_roomers(roomers)
{}

House::~House()
{
    
}

#pragma mark - ScriptProxy_House

GSize2D House::ScriptProxy_GetSize()
{
    return _size;
}

int House::ScriptProxy_GetRoomersCount()
{
    return static_cast<int>(_roomers.size());
}

ScriptProxy_Person *House::ScriptProxy_GetRoomer(int index)
{
    return _roomers[index].get();
}

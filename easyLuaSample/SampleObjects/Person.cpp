//
//  Person.cpp
//  easyLua
//
//  Created by Katekov Anton on 8/16/17.
//  Copyright © 2017 katekovanton. All rights reserved.
//

#include "Person.hpp"



Person::Person(const std::string &name, const GPoint2D &position)
:_name(name)
,_position(position)
{}

Person::~Person()
{}

#pragma mark - ScriptProxy_Person

std::string Person::ScriptProxy_GetName()
{
    return _name;
}

void Person::ScriptProxy_SetName(std::string name)
{
    _name = name;
}

GPoint2D Person::ScriptProxy_GetPosition()
{
    return _position;
}

void Person::ScriptProxy_SetPosition(GPoint2D position)
{
    _position = position;
}

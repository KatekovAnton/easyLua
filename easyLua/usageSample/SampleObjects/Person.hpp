//
//  Person.hpp
//  easyLua
//
//  Created by Katekov Anton on 8/16/17.
//  Copyright © 2017 katekovanton. All rights reserved.
//

#ifndef Person_hpp
#define Person_hpp

#include <stdio.h>
#include <string>
#include "Geometry.h"
#include "ScriptProxy_Person.hpp"



class Person : public ScriptProxy_Person {
    
    std::string _name;
    GPoint2D _position;
    
public:
    
    Person(const std::string &name, const GPoint2D &position);
    ~Person();
    
    // any other methods of Person class
    // ...
    
#pragma mark - ScriptProxy_Person
    
    virtual std::string ScriptProxy_GetName() override;
    virtual void ScriptProxy_SetName(std::string name) override;
    virtual GPoint2D ScriptProxy_GetPosition() override;
    virtual void ScriptProxy_SetPosition(GPoint2D position) override;
    
};

#endif /* Person_hpp */

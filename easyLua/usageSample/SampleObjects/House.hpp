//
//  House.hpp
//  easyLua
//
//  Created by Katekov Anton on 8/16/17.
//  Copyright © 2017 katekovanton. All rights reserved.
//

#ifndef House_hpp
#define House_hpp

#include "ScriptProxy_House.hpp"
#include "Geometry.h"
#include <vector>
#include <memory>



class Person;



class House : public ScriptProxy_House {
    
    std::vector<std::shared_ptr<Person>> _roomers;
    GSize2D _size;
    
public:
    
    House(const std::vector<std::shared_ptr<Person>> &roomers, const GSize2D &size);
    ~House();
    
    void AddRoomer(std::shared_ptr<Person> roomer);
    // any other methods of House class
    // ...
    
#pragma mark - ScriptProxy_House
        
    virtual GSize2D ScriptProxy_GetSize() override;
    virtual int ScriptProxy_GetRoomersCount() override;
    virtual ScriptProxy_Person *ScriptProxy_GetRoomer(int index) override;
    
};

#endif /* House_hpp */

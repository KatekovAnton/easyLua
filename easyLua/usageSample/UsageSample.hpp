//
//  UsageSample.hpp
//  easyLua
//
//  Created by Katekov Anton on 8/15/17.
//  Copyright © 2017 katekovanton. All rights reserved.
//

#ifndef UsageSample_hpp
#define UsageSample_hpp

#include <stdio.h>
#include "LUAScriptDataSource.hpp"



class House;



class UsageSample : public LUAScriptDataSource {
    
    House *_house;
    
public:
    
    UsageSample();
    ~UsageSample();
    
    void Test();
    
};

#endif /* UsageSample_hpp */

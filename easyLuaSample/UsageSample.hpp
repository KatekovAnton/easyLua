//
//  UsageSample.hpp
//
//  Created by Anton Katekov on 01.01.2023.
//  Copyright (c) 2023 AntonKatekov. All rights reserved.
//

#ifndef UsageSample_hpp
#define UsageSample_hpp

#include <stdio.h>
#include "wrapper/LUAScriptDataSource.hpp"



class House;
class ByteBuffer;



class UsageSample : public LUAScriptDataSource {
    
    House *_house;
    
public:
    
    UsageSample(bool empty);
    ~UsageSample();
    
    void Test(ByteBuffer *destination);
    void TestSaved(ByteBuffer *source);
    
};

#endif /* UsageSample_hpp */

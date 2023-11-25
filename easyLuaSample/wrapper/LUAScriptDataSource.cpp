//
//  LUAScriptDataSource.cpp
//
//  Created by Anton Katekov on 01.01.2023.
//  Copyright (c) 2023 AntonKatekov. All rights reserved.
//

#include "LUAScriptDataSource.hpp"
#include "FileManger.h"



using namespace std;



#pragma mark - LUAContextDataSource

bool LUAScriptDataSource::CanLoadModule(LUAContext *context, const std::string &moduleName)
{
    string resultFileName = _rootFolder + moduleName + ".lua";
    shared_ptr<IFile> file = FileManager::SharedManager()->LoadFile(resultFileName);
    return file != nullptr;
}

LUAModuleData LUAScriptDataSource::LoadModule(LUAContext *context, const std::string &moduleName)
{
    LUAModuleData result;
    
    string resultFileName = _rootFolder + moduleName + ".lua";
    shared_ptr<IFile> file = FileManager::SharedManager()->LoadFile(resultFileName);
    
    result.moduleName = moduleName;
    result.moduleFullName = resultFileName;
    result.moduleText = file->GetContentAsString(); // possible error if no file
    
    return result;
}

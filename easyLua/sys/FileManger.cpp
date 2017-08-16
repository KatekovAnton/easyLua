//
//  FileManger.cpp
//  MAX
//
//  Created by Katekov Anton on 10/20/12.
//  Copyright © 2012 katekovanton. All rights reserved.
//

#include "FileManger.h"



FileManager *_instance = NULL;



IFile::IFile(const string &filename)
:
_filename(filename)
{
}

#ifdef TARGET_OS_IPHONE
#include "ios_fileManager.h"
FileManager * FileManager::SharedManager()
{
    if (!_instance)
        _instance = new iosFileManager();
    return _instance;
}
#endif 

#if defined TARGET_OS_MAC && !defined TARGET_IPHONE_SIMULATOR
#include "mac_fileManager.h"
FileManager * FileManager::SharedManager()
{
    if (!_instance)
         _instance = new mac_fileManager();
    
    return _instance;
}
#endif

string FileManager::GetFilePath(string filename)
{
    return "";
}

shared_ptr<IFile> FileManager::LoadFile(string name)
{
    return nullptr;
}

shared_ptr<IFile> FileManager::SaveFile(string name, const char *data, long dataLength, bool forceOverride)
{
    return nullptr;
}

shared_ptr<IFile> FileManager::CreateFile(string name, bool forceOverride)
{
    return SaveFile(name, "", 0, forceOverride);
}

void FileManager::RemoveFile(const string &name)
{
    shared_ptr<IFile> file = LoadFile(name);
    if (file == nullptr) {
        return;
    }
    string fullPath = FileManager::SharedManager()->GetFilePath(name);
    remove(fullPath.c_str());
}

//
//  FileManger.cpp
//
//  Created by Anton Katekov on 01.01.2023.
//  Copyright (c) 2023 AntonKatekov. All rights reserved.
//

#include "FileManger.h"



FileManager *_instance = NULL;



IFile::IFile(const std::string &filename)
:
_filename(filename)
{
}

#ifdef PROJECT_TARGET_OS_WIN32
#include "windows_fileManager.h"
FileManager* FileManager::SharedManager()
{
    if (!_instance)
        _instance = new windows_fileManager();
    return _instance;
}
#endif 

#if defined PROJECT_OS_MACOS
#include "mac_fileManager.h"
FileManager * FileManager::SharedManager()
{
    if (!_instance)
         _instance = new mac_fileManager();
    
    return _instance;
}
#endif

std::string FileManager::GetFilePath(std::string filename)
{
    return "";
}

std::shared_ptr<IFile> FileManager::LoadFile(std::string name)
{
    return nullptr;
}

std::shared_ptr<IFile> FileManager::SaveFile(std::string name, const char *data, long dataLength, bool forceOverride)
{
    return nullptr;
}

std::shared_ptr<IFile> FileManager::CreateFile(std::string name, bool forceOverride)
{
    return SaveFile(name, "", 0, forceOverride);
}

void FileManager::RemoveFile(const std::string &name)
{
    std::shared_ptr<IFile> file = LoadFile(name);
    if (file == nullptr) {
        return;
    }
    std::string fullPath = FileManager::SharedManager()->GetFilePath(name);
    remove(fullPath.c_str());
}

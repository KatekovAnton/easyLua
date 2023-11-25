//
//  mac_fileManager.h
//
//  Created by Anton Katekov on 01.01.2023.
//  Copyright (c) 2023 AntonKatekov. All rights reserved.
//

#ifndef __mac_fileManager__
#define __mac_fileManager__

#include <iostream>
#include "FileManger.h"



class mac_File : public IFile {
    
public:
    
    mac_File(const string &filename);
    ~mac_File();
    
    virtual string GetContentAsString();
    
    virtual void SaveString(const string &content);
    virtual void SaveBuffer(const char *buffer, unsigned long length);
};



class mac_fileManager : public FileManager {
public:
    
    virtual shared_ptr<IFile> LoadFile(string name);
    virtual shared_ptr<IFile> SaveFile(string name, const char *data, long dataLength, bool forceOverride);
    
    virtual string  GetFilePath(string filename);
};

#endif /* defined(__mac_fileManager__) */

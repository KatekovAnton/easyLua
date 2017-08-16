//
//  ios_fileManager.h
//  MAX
//
//  Created by Katekov Anton on 10/20/12.
//  Copyright © 2012 katekovanton. All rights reserved.
//

#ifndef __ios_fileManager__
#define __ios_fileManager__

#include <iostream>

#include "FileManger.h"

class iosFile : public IFile {
    
public:
    
    iosFile(const string &filename);
    ~iosFile();
    
    virtual string GetContentAsString();
    virtual char *GetRawContent(); //free buffer with delete[]
    
    virtual void SaveString(const string &content);
    virtual void SaveBuffer(const char *buffer, unsigned long length);
};

class iosFileManager : public FileManager {
public:
    
    virtual shared_ptr<IFile> LoadFile(string name);
    virtual shared_ptr<IFile> SaveFile(string name, const char *data, long dataLength, bool forceOverride);
    
    virtual string  GetFilePath(string filename);
    
};

#endif /* defined(__ios_fileManager__) */

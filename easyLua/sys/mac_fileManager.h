//
//  mac_fileManager.h
//  MAX
//
//  Created by Katekov Anton on 10/20/12.
//  Copyright © 2012 katekovanton. All rights reserved.
//

#ifndef __MAX__mac_fileManager__
#define __MAX__mac_fileManager__

#include <iostream>
#include "FileManger.h"



class mac_File : public IFile {
    
public:
    
    mac_File(const string &filename);
    ~mac_File();
    
    virtual string GetContentAsString();
    virtual char *GetRawContent(); //free buffer with delete[]
    
    virtual void SaveString(const string &content);
    virtual void SaveBuffer(const char *buffer, unsigned long length);
};



class mac_fileManager : public FileManager {
public:
    
    virtual shared_ptr<IFile> LoadFile(string name);
    virtual shared_ptr<IFile> SaveFile(string name, const char *data, long dataLength, bool forceOverride);
    
    virtual string  GetFilePath(string filename);
};

#endif /* defined(__MAX__mac_fileManager__) */

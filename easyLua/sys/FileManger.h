//
//  FileManger.h
//  MAX
//
//  Created by Katekov Anton on 10/20/12.
//  Copyright © 2012 katekovanton. All rights reserved.
//

#ifndef FileManger_h
#define FileManger_h

#include <iostream>
#include "Geometry.h"



using namespace std;



class IFile {
    
    friend class FileManager;
    
protected:
    string _filename;
    
public:
    
    IFile (const string &filename);
    virtual ~IFile() { }
    virtual string GetContentAsString() = 0;
    virtual char *GetRawContent() = 0; //free buffer with delete[]
    
    virtual void SaveString(const string &content) = 0;
    virtual void SaveBuffer(const char *buffer, unsigned long length) = 0;
    
};



class FileManager {
    
public:
	
    static FileManager *SharedManager();
    
    virtual string GetFilePath(string filename);
    
    virtual shared_ptr<IFile> LoadFile(string name);
    virtual shared_ptr<IFile> SaveFile(string name, const char *data, long dataLength, bool forceOverride);
    virtual shared_ptr<IFile> CreateFile(string name, bool forceOverride);
    virtual void RemoveFile(const string &name);
    
};

#endif /* defined(__FileManger__) */

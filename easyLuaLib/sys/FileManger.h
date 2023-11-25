//
//  FileManger.h
//
//  Created by Anton Katekov on 01.01.2023.
//  Copyright (c) 2023 AntonKatekov. All rights reserved.
//

#ifndef FileManger_h
#define FileManger_h

#include <iostream>
#include <memory>



typedef enum __FileManagerStorageType
{
    FileManagerStorageType_Default,
    FileManagerStorageType_External, // android only
} FileManagerStorageType;




class IFile {
    
    friend class FileManager;
    
protected:
    std::string _filename;
    
public:
    
    IFile (const std::string &filename);
    virtual ~IFile() { }
    virtual std::string GetContentAsString() = 0;
    
    virtual void SaveString(const std::string &content) = 0;
    virtual void SaveBuffer(const char *buffer, unsigned long length) = 0;
    
};



class FileManager {
    
public:
	
    static FileManager *SharedManager();
    
    virtual std::string GetFilePath(std::string filename);
    
    virtual std::shared_ptr<IFile> LoadFile(std::string name);
    virtual std::shared_ptr<IFile> SaveFile(std::string name, const char *data, long dataLength, bool forceOverride);
    virtual std::shared_ptr<IFile> CreateFile(std::string name, bool forceOverride);
    virtual void RemoveFile(const std::string &name);
    
};

#endif /* defined(__FileManger__) */

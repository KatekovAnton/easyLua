//
//  mac_fileManager.cpp
//
//  Created by Anton Katekov on 01.01.2023.
//  Copyright (c) 2023 AntonKatekov. All rights reserved.
//

#include "mac_fileManager.h"
#include <Cocoa/Cocoa.h>
#include "BinaryReader.h"



NSString *applicationDataDirectory()
{
    NSFileManager* fileManager = [[NSFileManager alloc] init];
    NSString* bundleID = [[NSBundle mainBundle] bundleIdentifier];
    NSArray* urlPaths = [fileManager URLsForDirectory:NSApplicationSupportDirectory
                                            inDomains:NSUserDomainMask];
    
    NSURL* appDirectory = [[urlPaths objectAtIndex:0] URLByAppendingPathComponent:bundleID isDirectory:YES];
    
    //TODO: handle the error
    if (![fileManager fileExistsAtPath:[appDirectory path]]) {
        [fileManager createDirectoryAtURL:appDirectory withIntermediateDirectories:NO attributes:nil error:nil];
    }
    return [appDirectory path];
}

mac_File::mac_File(const string &filename)
:IFile(filename)
{}

mac_File::~mac_File()
{}

string mac_File::GetContentAsString()
{
    if (FileManager::SharedManager()->GetFilePath(_filename).length() == 0)
        return "";
    
    BinaryReader *br = new BinaryReader(_filename);
    char *data = new char [br->GetLength() + 1];
    memset(data, 0, br->GetLength() + 1);
    br->ReadBuffer(br->GetLength(), data);
    delete br;
    
    string result(data);
    delete [] data;
    
    return result;
    
}

void mac_File::SaveString(const string &content)
{
    SaveBuffer(content.c_str(), content.length());
}

void mac_File::SaveBuffer(const char *buffer, unsigned long length)
{
    NSString *basePath = applicationDataDirectory();
    NSString* foolile = [basePath stringByAppendingPathComponent:[NSString stringWithUTF8String:_filename.c_str()]];
    std::string str = foolile.UTF8String;
    
    FILE *pFile = NULL;
    pFile = fopen (str.c_str(),"wb");
    if (pFile!=NULL)
    {
        fwrite (buffer , sizeof(char), length, pFile);
        fclose (pFile);
        NSLog(@"Save successful\n%@", foolile);
    }
}


string mac_fileManager::GetFilePath(string filename) {
    
    NSString *basePath = applicationDataDirectory();
    NSString* foolile = [basePath stringByAppendingPathComponent:[NSString stringWithUTF8String:filename.c_str()]];
    BOOL fileExists = [[NSFileManager defaultManager] fileExistsAtPath:foolile];
    NSString *filePath = nil;
    if (fileExists)
        filePath = foolile;
    
    
    if (!filePath) {
        size_t dotPosition = filename.find(".");
        string extension = filename.substr(dotPosition + 1);
        NSString* pureName = [[NSString stringWithUTF8String:filename.c_str()] substringToIndex:dotPosition];
        
        filePath = [[NSBundle mainBundle] pathForResource:pureName ofType:[NSString stringWithUTF8String:extension.c_str()]];
        
    }
    if (!filePath)
        filePath = @"";
    
    return string([filePath UTF8String]);
}

shared_ptr<IFile> mac_fileManager::LoadFile(string name)
{
    if (GetFilePath(name).length() == 0)
        return nullptr;
    shared_ptr<IFile> result = shared_ptr<IFile>(new mac_File(name));
    return result;
}

shared_ptr<IFile> mac_fileManager::SaveFile(string name, const char *data, long dataLength, bool forceOverride)
{
    if (GetFilePath(name).length() != 0 && !forceOverride)
        return shared_ptr<IFile>(new mac_File(name));
    
    shared_ptr<IFile> file = shared_ptr<IFile>(new mac_File(name));
    file->SaveBuffer(data, dataLength);
    
    return file;
}

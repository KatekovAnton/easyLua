//
//  ios_fileManager.cpp
//  MAX
//
//  Created by Katekov Anton on 10/20/12.
//  Copyright © 2012 katekovanton. All rights reserved.
//

#include "ios_fileManager.h"
#import <Foundation/Foundation.h>
#include "BinaryReader.h"



NSString *applicationDataDirectory()
{
    NSURL *directoryURL = [[[NSFileManager defaultManager] URLsForDirectory:NSDocumentDirectory inDomains:NSUserDomainMask] lastObject];
    return [[directoryURL path] stringByAppendingString:@"/"];
}

iosFile::iosFile(const string &filename)
:IFile(filename)
{}

iosFile::~iosFile()
{}

string iosFile::GetContentAsString()
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

char *iosFile::GetRawContent() //free buffer with delete[]
{
    string fullPath = FileManager::SharedManager()->GetFilePath(_filename);
    if (fullPath.length() == 0)
        return NULL;
    
    BinaryReader *br = new BinaryReader(_filename);
    char *data = new char [br->GetLength()];
    br->ReadBuffer(br->GetLength(), data);
    delete br;
    
    return data;
}

void iosFile::SaveString(const string &content)
{
    SaveBuffer(content.c_str(), content.length());
}

void iosFile::SaveBuffer(const char *buffer, unsigned long length)
{
    NSString *basePath = applicationDataDirectory();
    NSString* foolile = [basePath stringByAppendingPathComponent:[NSString stringWithUTF8String:_filename.c_str()]];
    
    NSError *error = nil;
    NSData *nsdata = [NSData dataWithBytes:(const void*)buffer length:length];
    [nsdata writeToFile:foolile atomically:YES];//writeToFile:foolile atomically:YES encoding:NSUTF8StringEncoding error:&error];
    if (error) {
        NSLog(@"Attention! Save unsuccessful\n%@", foolile);
    }
    else
        NSLog(@"Save successful\n%@", foolile);
}


string iosFileManager::GetFilePath(string filename) {
    
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

shared_ptr<IFile> iosFileManager::LoadFile(string name)
{
    if (GetFilePath(name).length() == 0)
        return nullptr;
    shared_ptr<IFile> result = shared_ptr<IFile>(new iosFile(name));
    return result;
}

shared_ptr<IFile> iosFileManager::SaveFile(string name, const char *data, long dataLength, bool forceOverride)
{
    if (GetFilePath(name).length() != 0 && !forceOverride)
        return shared_ptr<IFile>(new iosFile(name));
    
    shared_ptr<IFile> file = shared_ptr<IFile>(new iosFile(name));
    file->SaveBuffer(data, dataLength);
    
    return file;
}

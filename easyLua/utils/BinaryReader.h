//
//  BinaryReader.h
//  MAX
//
//  Created by Katekov Anton on 10/30/12.
//  Copyright © 2012 katekovanton. All rights reserved.
//

#ifndef BinaryReader_h
#define BinaryReader_h

#include <iostream>
#include <istream>
#include <fstream>
#include <iosfwd>
#include <stdio.h>
#include <cstdint>
#include "FileManger.h"

class AAsset;
class AAssetManager;

class BinaryReader {
    
#ifdef ANDROID
    friend class Application;
    AAsset *_file;
#else
    FILE            *_file;
#endif

    char            *_currentBuffer;
    char            *_internalBuffer;
    
    long            _filesize;
    long            _position;
    
    bool            _shouldDeallocBuffer;
    
public:
#ifdef ANDROID
    static AAssetManager* assetManager;
#endif
    
    std::string _name;
    
    char* GetInternalBuffer() const {return _internalBuffer;}
    
    BinaryReader(std::string filename);
    BinaryReader(char *buffer, unsigned int length);
    BinaryReader(char *buffer, unsigned int length, bool shouldDeallocBuffer);
    ~ BinaryReader();
	bool isValid() const { return !(!_file); };
    long GetPosition();
    int ReadInt();
    unsigned int ReadUInt();
    short ReadInt16();
    unsigned short ReadUInt16();
    float ReadSingle();
    char ReadChar();
    unsigned char ReadUChar();
    std::string ReadBadString();
    std::string ReadString();
	void ReadBuffer(long length, char *buf);
    void SetPosition(long position);
    
	long GetLength() { return _filesize; };
    
    std::string ReadFullAsString();
    
};

#endif /* defined(BinaryReader_h) */

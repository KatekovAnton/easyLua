//
//  ByteBuffer.cpp
//  MAX
//
//  Created by Anton Katekov on 25.04.14.
//  Copyright (c) 2014 AntonKatekov. All rights reserved.
//

#include "ByteBuffer.h"
#include <cstdlib>
#include <cstring>


ByteBuffer::ByteBuffer()
:_step(1024)
,_data(NULL)
{
    _size = 0;
    _dataSize = 0;
}

ByteBuffer::ByteBuffer(size_t step)
:_step(step)
,_data(NULL)
{
    _size = 0;
    _dataSize = 0;
}

ByteBuffer::~ByteBuffer()
{
    if (_data != NULL) {
        free(_data);
    }
}

unsigned char* ByteBuffer::getPointer()
{
    return _data;
}

size_t ByteBuffer::getDataSize()
{
    return _size;
}

size_t ByteBuffer::getFullSize()
{
    return _dataSize;
}

void ByteBuffer::dataAppended(size_t size)
{
    _size += size;
}

size_t ByteBuffer::getAvailableSize()
{
    return _dataSize - _size;
}

void ByteBuffer::appendData(const unsigned char* buffer, size_t size, size_t nitems)
{
    size_t rembuff = 0;
    size *= nitems;
    rembuff= _dataSize - _size; /* remaining space in buffer */
    
    if(size > rembuff)
    {
        increaseBufferBy(size - rembuff);
    }
    memcpy(_data + _size, buffer, size);
    _size = size + _size;
}

void ByteBuffer::increaseBuffer()
{
    increaseBufferBy(_step);
}

void ByteBuffer::increaseBufferBy(size_t additionalPlace)
{
    size_t times = additionalPlace / _step + 1;
    size_t additional = times * _step;
    if (_data != NULL) {
        unsigned char *newbuff = (unsigned char*)realloc((void*)_data, _dataSize + additional);
        memset(newbuff + _dataSize, 0, additional);
        
        _dataSize = _dataSize + additional;
        _data = newbuff;
    }
    else {
        unsigned char *newbuff = (unsigned char*)malloc(additional);
        memset(newbuff, 0, additional);
        
        _dataSize = additional;
        _data = newbuff;
    }
}

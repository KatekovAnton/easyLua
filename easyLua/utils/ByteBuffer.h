//
//  ByteBuffer.h
//  MAX
//
//  Created by Anton Katekov on 25.04.14.
//  Copyright (c) 2014 AntonKatekov. All rights reserved.
//

#ifndef __MAX__ByteBuffer__
#define __MAX__ByteBuffer__

#include <iostream>

class ByteBuffer {
    
    unsigned char *_data;
    size_t _size;
    size_t _dataSize;

    size_t _step;
    
public:
    ByteBuffer();
    ByteBuffer(size_t step);
    ~ByteBuffer();
    unsigned char* getPointer();
    size_t getDataSize();
    size_t getFullSize();
    size_t getAvailableSize();
    void appendData(const unsigned char* buffer, size_t size, size_t nitems);
    void increaseBuffer();
    void increaseBufferBy(size_t additionalPlace);
    
    void dataAppended(size_t size);

};

#endif /* defined(__MAX__ByteBuffer__) */

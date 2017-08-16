//
//  Geometry.h
//  MAX
//
//  Created by Katekov Anton on 10/30/12.
//  Copyright © 2012 katekovanton. All rights reserved.
//

#ifndef Geometry_h
#define Geometry_h

#include "math.h"


template <typename T> static __inline__
T ____min(T a, T b)
{
    return a<b?a:b;
}

template <typename T> static __inline__
T ____max(T a, T b)
{
    return a>b?a:b;
}

template <typename T> static __inline__
T ____abs(T a)
{
    return a>0?a:-a;
}


struct __GPoint2D {
    float x;
    float y;
    
    __GPoint2D() :x(0), y(0) {}
    __GPoint2D(float _x, float _y) :x(_x), y(_y) {}
    
    float getX() const {return x;}
    float getY() const {return y;}
    
    void setX(float value) {x = value;}
    void setY(float value) {y = value;}
};

typedef struct __GPoint2D GPoint2D;

static __inline__ GPoint2D
GPoint2DMult(const GPoint2D& v, const float s)
{
    return GPoint2D(v.x*s, v.y*s);
}

static __inline__ GPoint2D
GPoint2DAdd(const GPoint2D& v1, const GPoint2D& v2)
{
    return GPoint2D(v1.x + v2.x, v1.y + v2.y);
}

static __inline__ GPoint2D
GPoint2DSub(const GPoint2D& v1, const GPoint2D& v2)
{
    return GPoint2D(v1.x - v2.x, v1.y - v2.y);
}

static __inline__ float
GPoint2DDot(const GPoint2D& v1, const GPoint2D& v2)
{
    return v1.x*v2.x + v1.y*v2.y;
}

static __inline__ float
GPoint2DLengthSQ(const GPoint2D& v)
{
    return GPoint2DDot(v, v);
}

static __inline__ float
GPoint2DLength(const GPoint2D& v)
{
    return sqrtf(GPoint2DLengthSQ(v));
}

struct __GSize2D {
    float height;
    float width;
    
    __GSize2D() :width(0), height(0) {}
    __GSize2D(float _w, float _h) :width(_w), height(_h) {}
};

typedef struct __GSize2D GSize2D;

struct __GRect2D {
    GPoint2D   origin;
    GSize2D    size;
    
    __GRect2D() :origin(GPoint2D()), size(GSize2D()) {}
    __GRect2D(float x, float y, float width, float height) :origin(GPoint2D(x, y)), size(GSize2D(width, height)) {}
    
    float getX() const {return origin.x;}
    float getY() const {return origin.y;}
    
    float getW() const {return size.width;}
    float getH() const {return size.height;}
    
    void setX(float value) {origin.x = value;}
    void setY(float value) {origin.y = value;}
    
    void setW(float value) {size.width = value;}
    void setH(float value) {size.height = value;}
};

typedef struct __GRect2D GRect2D;

#endif

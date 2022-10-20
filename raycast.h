// Pre processor Directives
#ifndef RAYCAST_H
#define RAYCAST_H

// Header Files
#include "v3math.h"
#include "PPMConverterMain.h"

// Object Data Structure
typedef struct vector3dType{
    float x;
    float y;
    float z;
} vector3d;

//typedef enum objectName{Sphere, Plane};

typedef struct objectType{ 
    // objectName objectId;
    vector3dType color;
    vector3dType position;
    vector3dType normal;
    int radius;
} object;

typedef struct objectListType{
    objectType currObject;
    objectListType* nextObject;
} objectList;

typedef struct cameraType{
    vector3dType postion;
    float height;
    float width;
}camera;

// Function Prototypes
objectListType parseJsonFile(FILE inputFile);




#endif // RAYCAST_H
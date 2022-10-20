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

typedef struct objectType{ 
    enum objectTypes {Sphere, Plane} objectId;
    vector3d color;
    vector3d position;
    vector3d normal;
    int radius;
    object* nextObject;
}object;


typedef struct cameraType{
    vector3d postion;
    float height;
    float width;
}camera;

// Function Prototypes
object* parseJsonFile(char* inFileName, camera* Camera);




#endif // RAYCAST_H
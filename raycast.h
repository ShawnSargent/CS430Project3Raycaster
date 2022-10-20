// Pre processor Directives
#ifndef RAYCAST_H
#define RAYCAST_H

// Header Files
#include "v3math.h"
#include "PPMConverterMain.h"

// Object Data Structure
struct vector3dType{
    float x;
    float y;
    float z;
} vector3d;

typedef enum objectName{Sphere, Plane};

struct objectType{ 
    objectName objectId = Sphere;
    vector3dType color;
    vector3dType position;
    vector3dType normal;
    int radius;
    objectType* nextObject;
} object;


struct cameraType{
    vector3dType postion;
    float height;
    float width;
}camera;

// Function Prototypes
objectType* parseJsonFile(FILE inputFile);




#endif // RAYCAST_H
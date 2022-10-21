// Pre processor Directives
#ifndef RAYCAST_H
#define RAYCAST_H

// Header Files
#include "v3math.h"
#include "PPMConverterMain.h"

// Vector Data structure
// Used for representing a 3d vector
typedef struct vector3dType{

    // Represents the x coordinate
    float x;

    // Represents the y coordinate
    float y;

    // Represents the z coordinate
    float z;

} vector3d;

// Object Data Structure
// Used for storing objects inputted from the JSON file
typedef struct objectType
{ 
    // The objects inputted will either be a circle or a plane
    // This enumeration will represent that
    // Consider changing to a string 
    enum objectTypes {Sphere, Plane} objectId;

    vector3d color;

    vector3d position;

    vector3d normal;

    int radius;

    struct objectType* nextObject;

}object;

// Camera Data Structure
// Used to represent the current position of the camera
typedef struct cameraType
{
    vector3d postion;

    float height;

    float width;

}camera;

// Function Prototypes
object* parseJsonFile(char* inFileName, camera* camera);

uint8_t raycastToPixmap( object *headPtr, camera *theCamera,int width, int height, int channels );




#endif // RAYCAST_H
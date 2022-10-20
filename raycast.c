// Header File
#include "raycast.h"

// Function: main
// Purpose: do the desired programming task
int main( int argc, char **argv )
{

}


// Function: parseInputJSON()
// Purpose: imports .json file, which is file 
object* parseInputJSON( char* inFileName, camera* camera)
{
    // read input file
    FILE* fileHandle;
    fileHandle = fopen(inFileName, "r");
    int charLimit = 128;
    char* inLine[charLimit]; // 128 is max character limit arbitrarily defined

    // making head pointer for object linked list
    object* head = (object*) malloc(sizeof(object));
    fgets(inLine, charLimit, fileHandle);
    //Line format: camera, width: [num], hieght: [num]
    fscanf(fileHandle, "%s %s %d %c %s %d");
    // grab and assign the camera data

    // grab objects until we are at the end of file
    // return head pointer to object list
}

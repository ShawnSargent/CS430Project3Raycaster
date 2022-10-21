// Header File
#include "raycast.h"

// Function: main
// Purpose: do the desired programming task
int main( int argc, char **argv )
{
	// CHECK to see if the user supplied the correct CLI arguments
	if( argc > 5 || argc < 5 )
	{
		fprintf( stderr, "Error: Invalid arguments supplied to program.\n");

		fprintf( stderr, 
		"Usage Pattern: raycast width height input.scene output.ppm\n");

		fprintf( stderr, "Program End\n\n" );
		
		return -1;	
	}

	// Define Variables pertaining to input file

		// File type object to represent the input file 

		// Define a size that will be used to store the name of the input file
		const int fileNameSize = 50;

		// Define a variable to store the name of the input file 
		char inFileName[fileNameSize];

		// Define a variable to store the name of the input file 
		char outFileName[fileNameSize];

	// Define Variables pertaining to height and width, channels, and pixmap
	
		// Variable representing width at the 1st index inputted from the CLI
		int imageWidth;
        sscanf(argv[1], "%d", &imageWidth);

		// Variable representing height at the 2nd index inputted from the CLI
		int imageHeight;
        sscanf(argv[2], "%d", &imageHeight);

		// Define a variable to store the color channels of the input image 
		// (RGBA) has 4 channels
		int channels = 4;

	// Define Variables pertaining to objects and cameras

		// Define a variable that represents a temporary place to store the inputted pixmap
		// Also, allocate memory equal to the inputted values for width, height, and channels
		uint8_t *pixMap = NULL;

        // camera is going to be at 0,0,0

        camera theCamera;
        theCamera.postion.x = 0;
        theCamera.postion.y = 0;
        theCamera.postion.z = 0;

        // object linked list
        object* headPtr;

	// Copy the name of the input file to the local copy of the file name 
	strcpy( inFileName, argv[3] );

	// Copy the name of the output file 
	strcpy( outFileName, argv[4] );

	// CHECK to see if the input file open was a success

    headPtr = parseJsonFile( inFileName, &theCamera);

    if(headPtr == NULL){
        fprintf(stderr, "Empty Scene, no objects found\n");
        fprintf(stderr, "Ending Program");
        return -1;
    }

    raycastToPixmap();

    writeP6Data(inFileName, pixMap, width, height, channels );

    printf( "Raycast Operation Successful !\n" );

    printf( "Object transferred to pixel buffer successfully. !\n" );

    // free anything necessary
	return 0;

}


// Function: parseInputJSON()
// Purpose: imports .json file, which is file 
object* parseJsonFile( char* inFileName, camera* camera)
{
    // read input file
    FILE* fileHandle;

    fileHandle = fopen(inFileName, "r");
    
    if(fileHandle == NULL){
        fclose(fileHandle);

        fprintf(stderr, "ERROR: File could not be opened\n");

        return NULL;
    }

    int charLimit = 128; // 128 is max character limit arbitrarily defined 

    char inLine[charLimit]; 
    char temp[charLimit];
    float width, height;
    float temp1;
    float temp2;
    float temp3;
    float temp4;
    float temp5;
    float temp6;
    float temp7;
    float temp8;
    float temp9;
    int tempInt;


    // making head pointer for object linked list
    object* head;
    object* currPtr;
    currPtr = head;

    fgets(inLine, charLimit, fileHandle);

    // camera, width: %f, height: %f;
    sscanf(inLine, "camera, width: %f, height: %f", &width, &height );
    camera->height = height;
    camera->width = width;

    // <object>, color: [1, 0, 0], position: [0, 1, -5], radius: 2
    while(fgets(inLine, charLimit, fileHandle) != NULL){
        currPtr = (object*)malloc(sizeof(object));
        // grab the object name to determine how to parse
        sscanf(inLine, "%s", temp);
        if(strcmp(temp, "sphere,")){
            currPtr->objectId = Sphere;
            sscanf(inLine, "sphere, color: [%f, %f, %f], position: [%f, %f, %f], radius: %n",
            &temp1, &temp2, &temp3, &temp4, &temp5, &temp6, &tempInt);
            currPtr->color.x = temp1;
            currPtr->color.y = temp2;
            currPtr->color.z = temp3;
            currPtr->position.x = temp4;
            currPtr->position.y = temp5;
            currPtr->position.z = temp6;
            currPtr->radius = tempInt;
        }
        else if(strcmp(temp, "plane,")){
            currPtr->objectId = Plane;
            sscanf(inLine, "plane, color: [%f, %f, %f], position: [%f, %f, %f], : normal: [%f, %f, %f]",
            &temp1, &temp2, &temp3, &temp4, &temp5, &temp6, &temp7, &temp8, &temp9);
            currPtr->color.x = temp1;
            currPtr->color.y = temp2;
            currPtr->color.z = temp3;
            currPtr->position.x = temp4;
            currPtr->position.y = temp5;
            currPtr->position.z = temp6;
            currPtr->normal.x = temp7;
            currPtr->normal.y = temp8;
            currPtr->normal.z = temp9;
        }

        currPtr = currPtr->nextObject;
    }
    
    // return head pointer to object list
    return head;
}

// Function: raycastToPixMap
// Purpose: Take the inverted objects and put them on a pix map
uint8_t raycastToPixmap()
{
    // Define functions and variables 

		// Define a variable that represents R0 or the Origin of the ray
		// Of form: [ 0,0,0 ]
		// A ray is defined by: R(t) = R0 + t * Rd , t > 0 with R0 = [X0, Y0, Z0] and Rd = [Xd, Yd, Zd]

		// Define a variable that represents Rd or the Direction of the ray
		// Of form: [ deltaX, deltaY, deltaZ ]

		// Define a variable that represents the camera plane 

		// Define a temporary pixmap to be transfered to the actual pixmap at 
		// the end of the function 

		// Define a temporary distance variable that represents the distance between
		// the origin of the ray and the "hit"

		// Define a temporary object that represents the object at the current index 
		
	/*
	
		For the raytracing to occur logically, we must first start by accessing the
		positions of each object in the object list

		- This can come in the form of a loop
	
	*/

	// LOOP

		// Access Object
		// currentObject = ...

		// CHECK to see what kind of object it is (see if its a sphere)

			// If it is a sphere, perform sphere intersection operation

			// Assign properties to pixel



	

}
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
		int width;
        sscanf(argv[1], "%d", &width);

		// Variable representing height at the 2nd index inputted from the CLI
		int height;
        sscanf(argv[2], "%d", &height);

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

    // making head pointer for object linked list
    object* head = (object*) malloc(sizeof(object));
    object* currPtr;
    head->nextObject = currPtr;

    fgets(inLine, charLimit, fileHandle);

    // grab and assign the camera data
    // Line format: camera, width: [num], hieght: [num]
    sscanf(inLine, "camera, width: %f, height: %f", camera->width, camera->height);

    // grab objects until we are at the end of file
    while(fileHandle != EOF){
        fgets(inLine, charLimit, fileHandle);
        // fill currPtr with space
        currPtr = (object*) malloc(sizeof(object));
        // format is object_type, key: value, key: value, key: value
        // grab object type
        sscanf(inLine, "%s", temp);
        // if sphere parse for sphere
        if(strcmp(temp, "sphere") == 0){
            currPtr->objectId = Sphere;
            sscanf(inLine, "sphere, color: [%f, %f, %f], position: [%f, %f, %f], radius: %d"
                    , currPtr->color.x, currPtr->color.y, currPtr->color.z, 
                    currPtr->position.x, currPtr->position.y, currPtr->position.z
                    , currPtr->radius);
        // otherwise is plane
        }else{
            currPtr->objectId = Plane;
            sscanf(inLine, "plane, color: [%f, %f, %f], position: [%f, %f, %f], normal: [%f, %f, %f]"
                    , currPtr->color.x, currPtr->color.y, currPtr->color.z, 
                    currPtr->position.x, currPtr->position.y, currPtr->position.z
                    , currPtr->normal.x, currPtr->normal.y, currPtr->normal.z);
        }
        // move currptr to next ptr
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
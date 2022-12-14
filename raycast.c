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
		int channels = 3;

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

    if(headPtr == NULL)
    {
        fprintf(stderr, "Empty Scene, no objects found\n");

        fprintf(stderr, "Ending Program");

        return -1;
    }

    object* currPtr = headPtr;

    // uint8_t *pixMap = raycastToPixmap(headPtr, *theCamera, &pixmap, imageWidth, imageHeight, channels);

    writeP6Data(outFileName, pixMap, imageWidth, imageHeight, channels );

    printf( "Raycast Operation Successful !\n" );

    printf( "Object transferred to pixel buffer successfully. !\n" );

    // free anything necessary
    freeObjectList(headPtr);

	return 0;

}


// Function: parseInputJSON()
// Purpose: imports .json file, which is file 
object* parseJsonFile( char* inFileName, camera* camera)
{
    // read input file
    FILE* fileHandle;

    fileHandle = fopen(inFileName, "r");
    
    if( fileHandle == NULL )
    {
        fclose(fileHandle);

        fprintf(stderr, "ERROR: File could not be opened\n");

        return NULL;
    }

    int charLimit = 128; // 128 is max character limit arbitrarily defined 

    char inLine[charLimit];

    char temp[charLimit];

    float width, height;

    float temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8, temp9;
    int tempInt;

    // making head pointers for object linked list and 
    object* head = NULL;

    object* currPtr;

    object* newNode;

    currPtr = head;

    fgets(inLine, charLimit, fileHandle);

    // camera, width: %f, height: %f;
    sscanf(inLine, "camera, width: %f, height: %f", &width, &height );

    camera->height = height;

    camera->width = width;

    // <object>, color: [1, 0, 0], position: [0, 1, -5], radius: 2
    while(fgets(inLine, charLimit, fileHandle) != NULL)
    {

        newNode = (object*) malloc(sizeof(object));

        // grab the object name to determine how to parse
        sscanf(inLine, "%s", temp);

        if(strcmp(temp, "sphere,") == 0)
        {
            newNode->objectId = Sphere;

            sscanf(inLine, "sphere, color: [%f, %f, %f], position: [%f, %f, %f], radius: %d",
            &temp1, &temp2, &temp3, &temp4, &temp5, &temp6, &tempInt);

            newNode->color.x = temp1;

            newNode->color.y = temp2;

            newNode->color.z = temp3;

            newNode->position.x = temp4;

            newNode->position.y = temp5;

            newNode->position.z = temp6;

            newNode->radius = tempInt;
        }

        else if(strcmp(temp, "plane,") == 0)
        {
            newNode->objectId = Plane;

            sscanf(inLine, "plane, color: [%f, %f, %f], position: [%f, %f, %f], normal: [%f, %f, %f]",
            &temp1, &temp2, &temp3, &temp4, &temp5, &temp6, &temp7, &temp8, &temp9);

            newNode->color.x = temp1;

            newNode->color.y = temp2;

            newNode->color.z = temp3;

            newNode->position.x = temp4;

            newNode->position.y = temp5;

            newNode->position.z = temp6;

            newNode->normal.x = temp7;

            newNode->normal.y = temp8;

            newNode->normal.z = temp9;
        }

        newNode->nextObject = NULL;

        if( head == NULL )
        {
            head = newNode;

            currPtr = head;
        }
        else
        {
            currPtr->nextObject = newNode;

            currPtr = currPtr->nextObject;
        }
    }
    
    // return head pointer to object list
    return head;
}

// Function: raycastToPixMap
// Purpose: Take the inverted objects and put them on a pix map
uint8_t* raycastToPixmap( object *headPtr, camera theCamera, uint8_t *pixmap, int imageWidth, int imageHeight, int imageChannels )
{
    // Define functions and variables 

		uint8_t *tempMap = malloc( sizeof(uint8_t) * imageWidth * imageHeight * imageChannels );

        float cameraHeight = theCamera.height;

        float cameraWidth = theCamera.width;

        float pixHeight = cameraHeight/ imageHeight ;

        float pixWidth = cameraWidth/ imageHeight;

		// Define a variable that represents Rd or the Direction of the ray
		// Of form: [ deltaX, deltaY, deltaZ ]
        float rdVector[3];

        float *unitVector[3];
        
        float xCoordofCol;

        float yCoordOfRow;

        float zCoord;

        int currentPixMapEntry;

        for ( int outterIndex = 0; outterIndex < imageHeight; outterIndex++ )
        {
            yCoordOfRow = theCamera.postion.y - cameraHeight / 2 + pixHeight * ( outterIndex * .5 );

            rdVector[1] = yCoordOfRow;

            for ( int innerIndex = 0; innerIndex < imageWidth; innerIndex++ )
            {
                xCoordofCol = theCamera.postion.x - cameraWidth / 2 + pixWidth * ( innerIndex * .5 );

                zCoord = -1.00;

                rdVector[0] = xCoordofCol;

                rdVector[2] = -1;

                v3_normalize(*unitVector, rdVector);

                // localColor = shootRay( unitVector );

                // currentPixMapEntry = itoa( localColor );

                // Print to pixel buffer

            }   
        }

        pixmap = tempMap;
    
    return pixmap;
}


// Function: free ObjectList
// Purpose: free the allocated memory in the 
object* freeObjectList(object* headPtr)
{
    if(headPtr->nextObject != NULL)
    {
        freeObjectList(headPtr->nextObject);
    }

    free(headPtr);

    return NULL;
}
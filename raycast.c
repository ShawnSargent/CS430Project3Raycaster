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
		FILE *inputJSON;

		// Define a size that will be used to store the name of the input file
		const int fileNameSize = 50;

		// Define a variable to store the name of the input file 
		char inFileName[fileNameSize];

		// Define a variable to store the name of the input file 
		char outFileName[fileNameSize];

	// Define Variables pertaining to height and width, channels, and pixmap
	
		// Variable representing width at the 1st index inputted from the CLI
		int width = argv[1];

		// Variable representing height at the 2nd index inputted from the CLI
		int height = argv[2];

		// Define a variable to store the color channels of the input image 
		// (RGBA) has 4 channels
		int channels = 4;

	// Define Variables pertaining to objects and cameras

		// Define a variable that represents a temporary place to store the inputted pixmap
		// Also, allocate memory equal to the inputted values for width, height, and channels
		uint8_t *pixMap = NULL;

	// Copy the name of the input file to the local copy of the file name 
	strcpy( inFileName, argv[3] );

	// Copy the name of the output file 
	strcpy( outFileName, argv[4] );

	// Open the file input file
	inputJSON = fopen( inFileName, "r" );

	// CHECK to see if the input file open was a success
	if ( inputJSON == NULL )
	{
		// First, close the file 
		fclose( inputJSON );

		// Print Error message to stderr
		fprintf( stderr, "Error: Could not open Input file.\n");

		fprintf( stderr, "Make sure the input file name is correct.\n");

		fprintf( stderr, "Program End\n\n" );

		// Return unsuccessful operation
		return -1;	
	}
	else
	{
		parseInputJSON( inputJSON );

		raycastToPixmap();

		writeP6Data(inFileName, ... );

		printf( "Raycast Operation Successful !\n" );

		printf( "Object transferred to pixel buffer successfully. !\n" );

	}

	return 0;

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

// Function: raycastToPixMap
// Purpose: Take the inverted objects and put them on a pix map
uint8_t raycastToPixmap()
{

}
// Local Files
#include "PPMConverterMain.h"

// Main Driver Function
int main( int argc, char **argv )
{
	// Define a variable that represents the space inside the string array
	// The length of the instring is arbitrary. We just need it to be big 
	// enough to grab whatever we need	
	int strSize = 64;

	// Define a variable that represents the magicNumber inputted by the user
	char magicNum;

	// Define a variable that reprsents the data at each line in the input file
	char *inString= malloc( sizeof(char) * strSize );

	// Define a variable to store the name of the input file 
	char inFileName[strSize];

	// Define a variable to store the name of the output file 
	char outFileName[strSize];

	// Define a variable to represent the file being inputted (argv[1])
	FILE *inputFile;

	// Define a variable to story the pixmap made by the read/write functions
	uint8_t *pixMap = NULL;

	// Define a variable to store the width of the input image
	int width;
	
	// Define a variable to store the height of the input image 
	int height;
	
	// Define a variable to store the color channels of the input image 
	// (RGBA) has 4 channels
	int channels = 4;
	
	// Define a variable to store the value 
	int maxColor;

	// CHECK to see if the user supplied the correct CLI arguments
	if( argc > 4 || argc < 4 )
	{
		fprintf( stderr, "Error: Invalid arguments supplied to program.\n");

		fprintf( stderr, "Format: ppmrw [Magic Number] [InputFile].ppm [OutputFile].ppm\n");

		fprintf( stderr, "Program End\n\n" );
		
		return -1;	
	}

	// Copy the name of the input file to the local copy of the file name 
	strcpy( inFileName, argv[2] );

	// Copy the name of the output file 
	strcpy( outFileName, argv[3] );

	// Open the file input file
	inputFile = fopen( inFileName, "r" );

	// CHECK to see if the input file open was a success
	if ( inputFile == NULL )
	{
		// First, close the file 
		fclose( inputFile );

		// Print Error message to stderr
		fprintf( stderr, "Error: Could not open Input file.\n");

		fprintf( stderr, "Make sure the input file name is correct.\n");

		fprintf( stderr, "Program End\n\n" );

		// Return unsuccessful operation
		return -1;	
	}

	// Move to first line of input file
	fgets( inString, strSize, inputFile );

	// CHECK to see if the input file is in .ppm format
	if( inString[0] == 'P' )
	{
		// Grab the ppm magic number
		magicNum = inString[1];

		// Move to next line of input file, which is usually a comment
		fgets( inString, strSize, inputFile );

		// Filter out all the comments in the input file 
		while( inString[0] == '#' )
		{
			fgets( inString, strSize, inputFile );
		}

		// Format our width and height from the values in the input file
		sscanf( inString, "%d %d", &width, &height );

		// Move to the next line in the input file containing the max color value
		fgets( inString, strSize, inputFile );

		// Format our max color value from the values in the input file	
		sscanf( inString, "%d", &maxColor );

		// close input file
		fclose( inputFile );

		// check for if we are reading p3 or p6
		if(magicNum == '3')
		{
			readP3Data(inFileName, &pixMap, width, height, channels);
		}
		else if(magicNum == '6')
		{
			readP6Data(inFileName, &pixMap, width, height, channels);
		}

		// write to desired format
		if( *argv[1] == '3' )
		{
			writeP3Data(outFileName, pixMap, width, height, channels);
		}
		else if( *argv[1] == '6' )
		{
			writeP6Data(outFileName, pixMap, width, height, channels);
		}
		else
		{
			// Print Error message to stderr
			fprintf( stderr, "Error: Invalid Magic Number\n");

			fprintf( stderr, "Please choose either 3 (P3) or 6 (P6)\n");

			fprintf( stderr, "Program End.\n\n" );

			// Return unsuccessful operation
			return -1;		
		}

		// print success 
		printf("File converted successfully!\n");

	}

	// If the file does not start with a capital "P", we know its formatted incorrectly
	else
	{
		// First, close the file
		fclose( inputFile );

		// Print Error message to stderr
		fprintf( stderr, "Error: Invalid File Format\n");

		fprintf( stderr, "Please input a valid ppm file.\n");

		fprintf( stderr, "Program End.\n\n" );

		// Return unsuccessful operation
		return -1;
	}

	// Return successful operation 
	return 0;
}

void readP3Data( char* name, uint8_t **pixmap,
	int width, int height, int channels )
{
	// Define a variable to store the value of a P3 data entry that could
	// be converted to P6
	int convertNum;

	// Define an index variable for a loop to parse through the P3 data
	int currIndex = 0;

	// Define a variable that represents the space inside the string array
	// The length of the instring is arbitrary. We just need it to be big 
	// enough to grab whatever we need	
	int strSize = 64;

	// Define a variable that stores the information of each line in the input file 
	char inString[strSize];

	// Define a variable that represents a temporary place to store the inputted pixmap
	// Also, allocate memory equal to the inputted values for width, height, and channels
	uint8_t *tempMap = (uint8_t*)malloc( sizeof(uint8_t)* width * height * channels );

	// Open file via given input file name
	FILE *inFile = fopen( name, "r" );

	/*
		The next 5 fgets() statements move the file parser to a spot in the file 
		where it can read a continuous input stream of P6 data using fread()
	*/

	// Move to the line containing the magic number 
	fgets( inString, strSize, inFile );

	// Loop through the comments and move to the last line containing a comment
	while( inString[0] == '#' )
	{
		fgets( inString, strSize, inFile );
	}

	// Move to the line in the header file containing height and width	
	fgets( inString, strSize, inFile );

	// Move to the last line in the header of the input file containing Max Value	
	fgets( inString, strSize, inFile );

	// Move to the first line in the input file that contains the P6 data
	fgets( inString, strSize, inFile );

	// Loop until we hit the end of file or hit the maximum size of array
	while( *inString != EOF && currIndex < width * height * channels )
	{
		// Get each line of the P3 data, line by line 
		fgets( inString, strSize, inFile );

		// Parse through the captured line and store each data entry 
		// in convertNum
		sscanf( inString, "%d", &convertNum );

		// Populate the temporary pixmap with the P3 data from the input file
		tempMap[currIndex] = convertNum;

		// Increment index
		currIndex += 1;
	}

	// Transfer the data from the temporary pixmap back to the pixmap that was passed
	// into the function
	*pixmap = tempMap;

	// Finally, close the input file 
	fclose( inFile );
}

void readP6Data( char* name, uint8_t **pixmap,
	int width, int height, int channels )
{
	// First, open the input P6 file
	FILE *inFile = fopen( name, "r" );
	
	// Define a variable that represents the space inside the string array
	// The length of the instring is arbitrary. We just need it to be big 
	// enough to grab whatever we need
	int strSize = 64;

	// Define a variable that stores the information of each line in the input file 
	char inString[strSize];

	// Define a variable that represents a temporary place to store the inputted pixmap
	// Also, allocate memory equal to the inputted values for width, height, and channels
	uint8_t *tempMap = malloc( sizeof(uint8_t) * width * height * channels );
	
	/*
		The next 5 fgets() statements move the file parser to a spot in the file 
		where it can read a continuous input stream of P6 data using fread()
	*/

	// Move to the line containing the magic number 
	fgets( inString, strSize, inFile );
	
	// Loop through the comments and move to the last line containing a comment
	while( inString[0] == '#' )
	{
		fgets( inString, strSize, inFile );
	}

	// Move to the line in the header file containing height and width
	fgets( inString, strSize, inFile );
	
	// Move to the last line in the header of the input file containing Max Value
	fgets( inString, strSize, inFile );

	// Move to the first line in the input file that contains the P6 data
	fgets( inString, strSize, inFile );

	// Read the P6 Data from the input file 
	fread( tempMap, sizeof(uint8_t), width*height*channels, inFile );
	
	// Transfer the data from the temporary pixmap back to the pixmap that was passed
	// into the function
	*pixmap = tempMap;

	// Finally, close the input file 
	fclose( inFile );
}

void writeP3Data( char* name, uint8_t *pixmap, 
	int width, int height, int channels )
{
	// First, open the output file
	FILE *outFile = fopen( name, "w" );

	// Print out the Magic number in the header to the output file.
	fprintf( outFile,"P3\n" );

	// Print out comment section in the header to the output file.
	fprintf( outFile,"# made by PPM converter!\n" );

	// Print out the width and height in the header to the output file.
	fprintf( outFile,"%d %d\n", width, height );

	// Print out the max color value in the header to the output file.
	fprintf( outFile, "255\n" );

	// Loop through pixmap vector and print out the entries
	for( int i = 0; i < width * height * channels ; i++ )
	{
		// Print each entry of the pixmap to the output file
		fprintf( outFile, "%d\n", pixmap[i] );
	}

	// Finally, close the output file 
	fclose(outFile);
}

void writeP6Data( char* name, uint8_t *pixmap, 
	int width, int height, int channels )
{
	// First, open the output file
	FILE *outFile = fopen( name, "w" );

	// Print out the Magic number in the header to the output file.
	fprintf( outFile,"P6\n" );

	// Print out comment section in the header to the output file.
	fprintf( outFile,"# made by PPM converter!\n" );

	// Print out the width and height in the header to the output file.
	fprintf( outFile,"%d %d\n", width, height );

	// Print out the max color value in the header to the output file.
	fprintf( outFile, "255\n" );

	// Print out the pixmap to the output file
	fwrite( pixmap, sizeof(uint8_t), width * height * channels, outFile );

	// Finally, close the output file.
	fclose( outFile );

}
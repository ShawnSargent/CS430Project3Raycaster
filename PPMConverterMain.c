// Local Files
#include "PPMConverterMain.h"

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
// Header Files
#include <stdio.h>
#include "v3math.h"

// Function Name: v3_from_points
// Function Purpose: Calculate v3 vector from two 3 dimensional vectors
void v3_from_points(float *dst, float *a, float *b)
{

	int index = 0;

	for(index = 0; index < 3; index++)
	{
		dst[index] = b[index] - a[index];
	}	

}

// Function Name: v3_add
// Function Purpose: Give sum
void v3_add(float *dst, float *a, float *b)
{
	int index = 0;

	for(index = 0; index < 3; index++)
	{
		dst[index] = a[index] + b[index];
	}	

}

// Function Name: v3_subtract
// Function Purpose: Take difference
void v3_subtract(float *dst, float *a, float *b)
{

	int index = 0;

	for(index = 0; index < 3; index++)
	{
		dst[index] = a[index] - b[index];
	}	

}

// Function Name: v3_dot_product
// Function Purpose: Calculate dot product
float v3_dot_product(float *a, float *b)
{
	int index = 0;

	float dot_product = 0.0;

	for(index = 0; index < 3; index++)
	{
		dot_product = dot_product + (a[index] * b[index]);
	}

	return dot_product;
}

// Function Name: v3_cross_product
// Function Purpose: Calculate cross product
void v3_cross_product(float *dst, float *a, float *b)
{
	// It is assumed that we will strictly be dealing with v3 vectors 
	// so indicies are reached using hard-coded integers
	dst[0] = (a[1] * b[2]) - (a[2] * b[1]);

	dst[1] = (a[2] * b[0]) - (a[0] * b[2]);

	dst[2] = (a[0] * b[1]) - (a[1] * b[0]);
}

// Function Name: v3_scale
// Function Purpose: Scales an input vector by s 
void v3_scale(float *dst, float s)
{
	int index = 0;

	for(index = 0; index < 3; index++)
	{
		dst[index] =  s * (dst[index]);
	}

}

// Function Name: v3_angle
// Function Purpose: Calculate angle between a and b
float v3_angle(float *a, float *b)
{
    float dotProduct = v3_dot_product(a,b);

    float MagProduct  = v3_length(a) * v3_length(b);

    float radianConvert = 180 / 3.141592;

    float angleBetween = 0;

    if(MagProduct > 0)
	{
	    angleBetween = acos(dotProduct / MagProduct) * radianConvert;
    }
	else
	{
        angleBetween = 0;
    }
    return angleBetween;
}

// Function Name: v3_angle_quick
// Function Purpose: Calculate angle between a and b w/o cos^-1
float v3_angle_quick(float *a, float *b)
{
	float quickAngle = 0.0;

	float dotProductResult = v3_dot_product(a,b);

	float length1 = v3_length(a);

	float length2 = v3_length(b);

    float radianConvert = 180 / 3.141592;

	quickAngle = dotProductResult / (length1 * length2);

    quickAngle = quickAngle * radianConvert;

    return cos(quickAngle);
}

// Function Name: v3_reflect
// Function Purpose: Reflect the vector
void v3_reflect(float *dst, float *v, float *n)
{

	dst[0] = v[0] - 2 * (v3_dot_product(v,n) * n[0]);

	dst[1] = v[1] - 2 * (v3_dot_product(v,n) * n[1]);

	dst[2] = v[2] - 2 * (v3_dot_product(v,n) * n[2]);

}

// Function Name: v3_length
// Function Purpose: Calculate the vectors magnitude
float v3_length(float *a)
{
	float index0Power = 0.0;

	float index1Power = 0.0;

	float index2Power = 0.0;

	index0Power = a[0] * a[0];

	index1Power = a[1] * a[1];

	index2Power = a[2] * a[2];

    return fabs(sqrt( index0Power + index1Power + index2Power ));
}

// Function Name: v3_normalize
// Function Purpose: Find surface normals
void v3_normalize(float *dst, float *a)
{

// Unable to complete

}
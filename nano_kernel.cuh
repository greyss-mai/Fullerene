#ifndef NANO_KERNEL_H
#define NANO_KERNEL_H

#if USE_TEX
#define FETCH(t, i) tex1Dfetch(t##Tex, i)
#else
#define FETCH(t, i) t[i]
#endif

#include "vector_types.h"
typedef unsigned int uint;

#define NUM_PARTICLES   64  	    		//Predefined number of particles
#define GRID_SIZE       32					//Number of cells
#define CUBE			2*32				//The half of a size of simulation space
#define COVALENT		8					//The numer of neighbouring atoms
#define R_MIN			1.0					//minimal distance between atoms
#define AMU				1.66053892173e-27	//The unified atomic mass unit
#define eV				1.602176487e-19		//constant electron-Volt

#ifndef M_PI
#define M_PI			3.1415926535897932384626433832795
#endif


#endif
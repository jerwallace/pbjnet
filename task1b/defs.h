
/*******************************************************
 *
 *  Global Header File
 *
 *  Created by Sathish Gopalakrishnan 
 *    University of British Columbia
 *
 *
 ******************************************************/


/*-------------------------------------------------
 * 
 * These are some standard definitions.  Including
 * them here means that the include statements don't 
 * have to be repeated in each file.
 *
 *-------------------------------------------------*/

#include <unordered_map>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <iostream>
/*----------------------------------------------------
 * The maximum length of a line in the input file
 *----------------------------------------------------*/

#define BUFFERLENGTH 400
#define BIGINT (1e20)

#define MAX(a,b)  ((a)>(b)?(a):(b))

#define BOOL char
#define TRUE ((BOOL)1)
#define FALSE ((BOOL)0)

#include "misc.h"
#include "cam.h"
#include "ext.h"

using namespace std;

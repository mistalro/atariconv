// --------------------------------------------------------------------------
// File: atari.h 
//
// Purpose: Main header file to include all other header files
// 
// Author:  Michael S. A. Robb
//
// Date:    30th November 2000
//
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Define the list of functions in the API
// --------------------------------------------------------------------------

#ifndef _ATARI_H_
#define _ATARI_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define OPTION_TERMCAP

#ifdef OPTION_TERMCAP
#include <curses.h>
#include <term.h>
#endif

#include "options.h"
#include "basic.h"
#include "tokens.h"
#include "fileio.h"
#include "repair.h"
#include "dump.h"
#include "decode.h"
#include "mem.h"
#include "process.h"

#endif	/* _ATARI_H_ */

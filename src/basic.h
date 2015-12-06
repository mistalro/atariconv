// --------------------------------------------------------------------------
// File:    basic.h 
//
// Purpose: Header file defining main data structure for representing Atari
//          BASIC program
// 
// Author:  Michael S. A. Robb
//
// Date:    30th November 2010
// --------------------------------------------------------------------------

#ifndef _ATARI_BASIC_H_
#define _ATARI_BASIC_H_

// --------------------------------------------------------------------------
// Define the maximum number of variables permitted
// --------------------------------------------------------------------------

#define MAX_ATARIVARIABLES  128

// --------------------------------------------------------------------------
// Define the maximum number of characters in the unget buffer
// --------------------------------------------------------------------------

#define MAX_UNGETBUFFER 16

// --------------------------------------------------------------------------
// Data structure to represent a single Atari BASIC variable
// --------------------------------------------------------------------------

typedef struct atarivariable_st
{
char m_name[128];       // Name of the variable
int  m_type;            // Type of variable        VVTP 0
int  m_idnumber;        // The variable ID number  VVTP 1 
int  m_offset;          // Offset from STARP       VVTP 2..3
char m_value[8];        // BCD Value               VVTP 2..7
int  m_dim[2];          // Dimensions              VVTP 4..7
} ATARIVARIABLE;

// --------------------------------------------------------------------------
// Atari BASIC data structure
//
// This is the main data object. This stores all the different tables found
// in an ATARI BASIC tokenised file
// --------------------------------------------------------------------------

typedef struct ataribasic_st
{
int m_starp;            // String & array table & end of BASIC Program
int m_lomem;            // BASIC Bottom of memory
int m_vntp;             // Variable name table  
int m_vvtp;             // Variable value table
int m_vntd;             // (vvtp+1)
int m_stmtab;           // Beginning of BASIC program
int m_stmcur;           // Current statement

// ----- Variable list ----------------------------------------------------

int           m_varnum;                         // Number of variables
ATARIVARIABLE m_varlist[MAX_ATARIVARIABLES];    // List of variables

// ----- Stream buffering -------------------------------------------------

int            m_tokenbufsize;  // Number of bytes in the token buffer
unsigned char *m_ptokenbuffer;  // Pointer to token buffer
unsigned char *m_pgetptr;       // Pointer to current byte being read
int            m_getpos;        // Index to current byte being read
int            m_ungetcount;    // Number of unget bytes
int   m_ungetbuffer[MAX_UNGETBUFFER]; // List of unget bytes

// ----- Display options --------------------------------------------------

ATARIOPTIONS options;
} ATARIBASIC;

#endif	/* _ATARI_BASIC_H_ */

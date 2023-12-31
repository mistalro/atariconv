// --------------------------------------------------------------------------
// File:    options.h
//
// Purpose: Display and processing options
//
// Author:  Michael S. A. Robb
//
// Date:    30th November 2000
// --------------------------------------------------------------------------

#ifndef _OPTIONS_H_
#define _OPTIONS_H_

// ------------------------------------------------------------------------
// Display options
// ------------------------------------------------------------------------

typedef struct atarioptions_st
{
// ----- Output options ---------------------------------------------------

int m_verbose;          // Verbosity mode
int m_width;            // Width of screen
int m_showvariables;    // List variables
int m_showlastline;     // Show last line
int m_showheader;       // Show header
int m_dumpbuffer;       // Dump buffer
int m_dumplinetokens;   // Dump line buffer
int m_dumplineextended;	// Dumpe extended line buffer data
int m_dumplineascii;	// Dump line as ASCII
int m_usetermcap;       // Use terminfo for text inverse
int m_usehexfile;       // Use hex-dump files
int m_usebasfile;       // Use tokenised basic files
int m_rawataricompatible; // Output raw atari compatible

// ----- Repair options ---------------------------------------------------

int m_fixvartable;      // Fix variable table names
int m_numscalar;        // Count of scalar variables
int m_numstring;        // Count of string variables
int m_numarray;         // Count of array variables
} ATARIOPTIONS;

// -------------------------------------------------------------------------
// Options
// -------------------------------------------------------------------------

#define ataribasic_setscreenwidth( A, W ) \
        (A)->options.m_width = (W)

#define ataribasic_setshowvariables( A, M ) \
        (A)->options.m_showvariables = (M)

#define ataribasic_setdumpbuffer( A, M ) \
        (A)->options.m_dumpbuffer = (M)

#define ataribasic_setdumplineascii( A, M ) \
        (A)->options.m_dumplineascii = (M)

#define ataribasic_setdumplinetokens( A, M ) \
        (A)->options.m_dumplinetokens = (M)

#define ataribasic_setdumplineextended( A, M ) \
        (A)->options.m_dumplineextended = (M)

#define ataribasic_setshowlastline( A, M ) \
        (A)->options.m_showlastline = (M) 

#define ataribasic_setshowheader( A, H ) \
        (A)->options.m_showheader = (H)

#define ataribasic_setusetermcap( A, T ) \
        (A)->options.m_usetermcap = (T)

#define ataribasic_setusehexfile( A, U ) \
        (A)->options.m_usehexfile = (U)

#define ataribasic_setusebasfile( A, U ) \
        (A)->options.m_usebasfile = (U)

#define ataribasic_setfixvartable( A, F ) \
        (A)->options.m_fixvartable = (F)

#define ataribasic_setrawataricompat( A,F) \
	(A)->options.m_rawataricompatible= (F)

#endif	// _OPTIONS_H_

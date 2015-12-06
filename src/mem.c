// --------------------------------------------------------------------------
// File:    atari.c
//
// Purpose: Source file containing list of tokens and their ASCII symbols
//
// Author:  Michael S. A. Robb
//
// Date:    30th November 2000
// --------------------------------------------------------------------------

#include "atari.h"

// --------------------------------------------------------------------------
// Set up termcap
//
// Inputs: None
//
// Outputs: None
//
// Results: None
//
// Effects: The termcap system is initialised
// --------------------------------------------------------------------------

#ifdef OPTION_TERMCAP
void ataribasic_setuptermcap(void)
{
int error;
setupterm( getenv("TERM"), 1, &error );
}
#endif

// --------------------------------------------------------------------------
// Set up Atari options
// --------------------------------------------------------------------------

void atarioptions_init( ATARIOPTIONS *aptr )
{
// ----- Output options ------------------------

aptr->m_verbose = 0;
aptr->m_width = 80;
aptr->m_showvariables = 0;
aptr->m_showlastline = 0;
aptr->m_showheader = 0;
aptr->m_dumpbuffer = 0;
aptr->m_dumplinetokens = 0;
aptr->m_usetermcap = 1;
aptr->m_usehexfile = 0;
aptr->m_usebasfile = 0;

// ----- Useful statistics ---------------------

aptr->m_numscalar = 0;
aptr->m_numstring = 0;
aptr->m_numarray = 0;

// ----- Repair options ------------------------

aptr->m_fixvartable = 0;
}

// --------------------------------------------------------------------------
// Initialise the data to something sane
//
// Inputs: aptr - Atari BASIC context
//
// Outputs: None
//
// Results: None
//
// Effects: The Atari BASIC context is initialized
// --------------------------------------------------------------------------

void ataribasic_init( ATARIBASIC *aptr )
{
// ----- Header data ---------------------------

aptr->m_lomem = 0;
aptr->m_vntp = 0;
aptr->m_vntd = 0;
aptr->m_vvtp = 0;
aptr->m_stmtab = 0;
aptr->m_stmcur = 0;
aptr->m_starp = 0;

// ----- Variable list -------------------------

aptr->m_varnum = 0;

// ----- Stream buffering ----------------------

aptr->m_tokenbufsize =0;
aptr->m_ptokenbuffer = NULL;
aptr->m_pgetptr = NULL;
aptr->m_ungetcount = 0;

// ----- Set up options ------------------------

atarioptions_init( &aptr->options );

// ----- Set up termcap ------------------------

#ifdef OPTION_TERMCAP
ataribasic_setuptermcap();
#endif
}

// --------------------------------------------------------------------------
// Dellocate the memory
//
// Inputs:  aptr - The Atari BASIC context
//
// Outputs: None
//
// Effects: The context is deallocated
//
// Results: None
// --------------------------------------------------------------------------

void ataribasic_deallocate( ATARIBASIC *aptr )
{
if ( aptr->m_ptokenbuffer )
        free( aptr->m_ptokenbuffer );

aptr->m_ptokenbuffer = NULL;
aptr->m_tokenbufsize = 0;
}

// --------------------------------------------------------------------------
// Allocate the desired amount of memory
//
// Inputs:  aptr - Atari BASIC context
//          bytes - Number of bytes
//
// Outputs: None
//
// Results: None
//
// Effects: The selected amount of memory is allocated 
// --------------------------------------------------------------------------

void ataribasic_allocate( ATARIBASIC *aptr, int bytes )
{
if ( bytes < aptr->m_tokenbufsize )
        return;

ataribasic_deallocate( aptr );

aptr->m_ptokenbuffer = (unsigned char *) malloc( bytes );
aptr->m_tokenbufsize = bytes;
}

// --------------------------------------------------------------------------
// Delete the object
//
// Inputs:  aptr - Atari BASIC context
//
// Outputs: None
//
// Results: None
//
// Effects: The Atari BASIC context is deleted 
// --------------------------------------------------------------------------

void ataribasic_delete( ATARIBASIC*aptr)
{
ataribasic_deallocate( aptr );
free( aptr );
}


// --------------------------------------------------------------------------
// Create the object
//
// Inputs:  None
//
// Outputs: None
//
// Effects: The Atari BASIC context is created
//
// Results: Pointer to the new context
// --------------------------------------------------------------------------

ATARIBASIC *ataribasic_create( void )
{
ATARIBASIC *aptr;

aptr = (ATARIBASIC *) calloc( 1, sizeof(ATARIBASIC) );

ataribasic_init( aptr );

return( aptr );
}


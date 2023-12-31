// --------------------------------------------------------------------------
// File:    process.c
//
// Purpose: Source file containing main processing routine
//
// Author:  Michael S. A. Robb
//
// Date:    30th November 2000
// --------------------------------------------------------------------------

#include "atari.h"

// --------------------------------------------------------------------------
// Error handler
//
// Inputs: aptr - Current Atari file
//
// Outputs: None
//
// Effects: None
// 
// Results: None
// --------------------------------------------------------------------------

void ataribasic_error( ATARIBASIC *aptr )
{
fprintf(stderr, "Error:\n");
}

// --------------------------------------------------------------------------
// Read the data from an open file
//
// Inputs: aptr - Atari BASIC context
//
// Outputs: None
//
// Results: None
//
// Effects: The file is processed and displayed
// --------------------------------------------------------------------------

int ataribasic_listfile( ATARIBASIC *aptr )
{
int error;

ataribasic_resetbufferptr( aptr );      // Reset the buffer pointer

if ( aptr->options.m_dumpbuffer )
	{
        ataribasic_dumpbuffer( aptr );
	}

ataribasic_readheader( aptr );

if ( aptr->options.m_showheader )
	{
        ataribasic_header_display( aptr );
	}	

if ( aptr->options.m_fixvartable )
	{
        ataribasic_readlomemdata( aptr );
	}

ataribasic_readvarnames( aptr );

if ( error )
	{
        ataribasic_error( aptr );
	}

error = ataribasic_readvarvalues( aptr );

if (aptr->options.m_fixvartable )
	{
        ataribasic_varnamefromtype( aptr );
	}

if ( aptr->options.m_showvariables )
	{
  	ataribasic_varname_display( aptr );
	}

if ( error )
	{
        ataribasic_error( aptr );
	}

error = ataribasic_readprogram( aptr );

if ( error )
	{
        ataribasic_error( aptr );
	}

return( error );
}

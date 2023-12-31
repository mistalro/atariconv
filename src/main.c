// --------------------------------------------------------------------------
// File:    main.c
//
// Purpose: Command line interface to the ATARI BASIC file reader
//
// Author:  Michael S. A. Robb
// 
// Date:    November 2010
// --------------------------------------------------------------------------

#include "atari.h"

// --------------------------------------------------------------------------
// Global variables
// --------------------------------------------------------------------------

int g_verbose;	// Verbosity mode
int g_help;	// Display help

int g_width 	    = 80;	// Screen width
int g_showvariables = 0;	// Show variables
int g_showheader    = 0;	// Show headers
int g_showlastline  = 0;	// Show last line 
int g_usetermcap    = 0;	// Use termcap for inverse text
int g_usehexfile    = 0;	// Use hex encoded file
int g_usebasfile    = 1;	// Use tokenised BASIC file
int g_fixvartable   = 0;	// Fix variable table
int g_dumpbuffer    = 0;	// Dump token buffer
int g_dumplinetokens = 0;	// Dump token buffer per line
int g_dumplineextended = 0;	// Dump token buffer per line (extended)
int g_dumplineascii = 1;	// Dump token buffer as ASCII text
int g_rawataricompatible = 0;	// Dump token buffer atari compatible


// --------------------------------------------------------------------------
// Help text
// --------------------------------------------------------------------------

static char help_text[] =
{
"Usage: filename [-h][-v][-w][-F][-V][-L][-T][-H][-B] <filepath1> <filepath>\n"
"\n"
"Where: [-h] - Displays help text\n"
"       [-v] - Enables verbose mode\n"
"       [-w] - Set screen width\n"
"       [-A] - Dump token buffer as ASCII BASIC text [default]\n"
"       [-B] - Use BASIC file\n"
"       [-D] - Dump token buffer to standard output\n"
"       [-d] - Dump token buffer per line to standard output\n"
"       [-e] - Dump extended data per line to standard output\n"
"       [-F] - Fix variable table\n"
"       [-H] - Use hexdump file (Note: Must be separate individual file)\n"
"       [-L] - Show last line (command string used to save file)\n"
"       [-T] - Use termcap to display ATASCII inverse characters\n"
"       [-V] - Dump the variable table (including names)\n"
"       [-R] - Dump raw Atari compatible listing\n"
};

// --------------------------------------------------------------------------
// Display help text
// --------------------------------------------------------------------------

void display_help( void )
{
puts( help_text );
}

// --------------------------------------------------------------------------
// Process a single file
// --------------------------------------------------------------------------

void process_file( char *pfilename ) 
{
ATARIBASIC *aptr;

aptr = ataribasic_create();

ataribasic_setscreenwidth( aptr, g_width );
ataribasic_setshowvariables( aptr, g_showvariables );
ataribasic_setshowlastline( aptr, g_showlastline );
ataribasic_setshowheader( aptr, g_showheader );
ataribasic_setdumpbuffer( aptr, g_dumpbuffer );
ataribasic_setdumplinetokens( aptr, g_dumplinetokens );
ataribasic_setdumplineextended( aptr, g_dumplineextended );
ataribasic_setdumplineascii( aptr, g_dumplineascii );
ataribasic_setusetermcap( aptr, g_usetermcap );
ataribasic_setusehexfile( aptr, g_usehexfile );
ataribasic_setusebasfile( aptr, g_usebasfile );
ataribasic_setfixvartable( aptr, g_fixvartable );
ataribasic_setrawataricompat( aptr, g_rawataricompatible );

if ( ataribasic_loadfile( aptr, pfilename ) )
	{
	ataribasic_listfile( aptr );
	ataribasic_delete( aptr );
	}
else
	{
	printf( "Error: Could not load file <%s>\n", pfilename );
	}
}

// --------------------------------------------------------------------------
// Process command line arguments
// --------------------------------------------------------------------------

void process_arguments( int argc, char *argv[] )
{
int pn;

if ( argc==1 )
	{
	display_help();
	}

for ( pn = 1; pn < argc; pn++ )
	{
	if ( argv[pn][0] == '-' )
		{
		switch( argv[pn][1] )
			{
			case 'h':
				g_help++;
				break;

			case 'v':
				g_verbose++;
				break;

			case 'w':
				g_width = atoi( argv[pn]+2 );
				break;

			case 'A':
				g_dumplineascii ^= 1;
				break;

			case 'd':
				g_dumplinetokens ^= 1;
				break;

			case 'e':
				g_dumplineextended ^= 1;
				g_dumplinetokens ^= 1;
				break;

			case 'D':
				g_dumpbuffer ^= 1;
				break;

			case 'F':
				g_fixvartable ^= 1;
				break;

			case 'S':
				g_showheader ^= 1;
				break;

			case 'V':
				g_showvariables ^= 1;
				break;

			case 'L':
				g_showlastline ^= 1;
				break;
	
			case 'T':
				g_usetermcap ^= 1;
				break;
	
			case 'H':
				g_usehexfile = 1;
				g_usebasfile = 0;
				break;

			case 'B':
				g_usehexfile = 0;
				g_usebasfile = 1;
				break;
			case 'R':
				g_rawataricompatible = 1;
				break;

			default:
				break;
			}
		}
	else
		{
		process_file( argv[pn] );
		}
	}
}

// --------------------------------------------------------------------------
// First routine to be called
// --------------------------------------------------------------------------

int main( int argc, char *argv[] )
{
process_arguments( argc, argv );
}

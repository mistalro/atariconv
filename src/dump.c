// --------------------------------------------------------------------------
// File:    fileio.c
//
// Purpose: Source file containing low-level dump/display routines
//
// Author:  Michael S. A. Robb
//
// Date:    30th November 2000
// --------------------------------------------------------------------------

#include "atari.h"

// --------------------------------------------------------------------------
// Display the header
//
// Inputs:  aptr - Atari BASIC context
// 
// Outputs: None
//
// Results: None
//
// Effects: The values of the seven pointers are displayed
// --------------------------------------------------------------------------

void ataribasic_header_display( ATARIBASIC *aptr)
{
printf( "Atari BASIC Header\n");
printf( "------------------\n");
printf( "Lomem  = %04X\n", aptr->m_lomem );
printf( "Vntp   = %04X\n", aptr->m_vntp  );
printf( "Vntd   = %04X\n", aptr->m_vntd  );
printf( "Vvtp   = %04X\n", aptr->m_vvtp  );
printf( "Stmtab = %04X\n", aptr->m_stmtab );
printf( "Stmcur = %04X\n", aptr->m_stmcur );
printf( "Starp  = %04X\n", aptr->m_starp );
printf( "------------------\n");
}

// --------------------------------------------------------------------------
// Display the list of variable names
//
// Inputs:  aptr - Atari BASIC context
//
// Outputs: None
//
// Results: None
//
// Effects: The variables are displayed
// --------------------------------------------------------------------------

void ataribasic_varname_display( ATARIBASIC *aptr )
{
int vn;
ATARIVARIABLE *avptr;
char buffer[128];

avptr = aptr->m_varlist;

printf( "+---+-----------------+----------+\n" );
printf( "|#ID| Name            | Size     |\n" );
printf( "+---+-----------------+----------+\n" );

for ( vn = 0; vn < aptr->m_varnum; vn++, avptr++ )
        {
        printf( "|%03d|   %14s|", vn, avptr->m_name );

        buffer[0] = '\0';

        if ( (avptr->m_type & 0x40 ) == 0x40 )  // Array 
                {
                sprintf( buffer, "[%d,%d]",
                avptr->m_dim[0], avptr->m_dim[1] );
                }

        if ( (avptr->m_type & 0x80 ) == 0x80 )  // String 
                {
                sprintf( buffer, "$(%d,%d)",
                avptr->m_dim[0], avptr->m_dim[1] );
                }

        printf( "%9s |\n", buffer );
        }

printf( "+---+-----------------+----------+\n" );
}

// --------------------------------------------------------------------------
// Dump the load buffer
// 
// Inputs:  aptr - Atari BASIC context
//
// Outputs: None
//
// Results: None
//
// Effects: The buffer is dumped
// --------------------------------------------------------------------------

void ataribasic_dumpbuffer( ATARIBASIC *aptr )
{
int pn;
int col;
unsigned char *chptr;

chptr = aptr->m_ptokenbuffer;
col = 0;

printf( "-----------------------------------------\n");

for ( pn = 0; pn < aptr->m_tokenbufsize; pn++ )
        {
        printf( "%02X ", *chptr);
        chptr++;

        col++;
        if ( col == 0x10 )
                {
                printf( "\n");
                col = 0;
                }
        }

printf( "-----------------------------------------\n");
}

#ifdef OLD_VERSION
// --------------------------------------------------------------------------
// Dump the token buffer for the current line
// 
// Inputs:  aptr - Atari BASIC context
//
// Outputs: None
//
// Results: None
//
// Effects: The buffer is dumped
// --------------------------------------------------------------------------

int ataribasic_dumplinetokens( ATARIBASIC *aptr )
{
int pn, lineno, pos;
unsigned char *chptr;

chptr = aptr->m_pgetptr;

lineno = (chptr[1]<<8) + chptr[0];

if ( (lineno == 0x8000) &&(!aptr->options.m_showlastline ) )
	{
	return(lineno);
	}

printf( "%5d| ", lineno );

pos = 0;
while ( *chptr != ATARI_OP_LINEEND )
	{
	printf( "%02X ", *chptr);

	pos++;

	if (*chptr == ATARI_OP_STMTEND )
		{
		printf("| ");
		}

	if ( pos == 2 )
		{
		printf("| ");
		}
	chptr++;
	}

printf( "|\n");

return( lineno );
}
#endif

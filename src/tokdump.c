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

// ==========================================================================
// BASIC TOKEN
// ==========================================================================

// --------------------------------------------------------------------------
// Write a single keyword token
//
// Inputs:  aptr - Atari BASIC context
//          ptoken - The current token
//  
// Outputs: None
//
// Results: None
//
// Effects: The keyword string is written out
// --------------------------------------------------------------------------

void ataribasic_dump_token( ATARIBASIC *aptr, TOKEN_ENTRY *ptoken )
{
printf( "%02X", ptoken->token_id );

if ( aptr->options.m_dumplineextended )
	{
	if ( ptoken->token_str[0] )
		{
		printf( " '%s'", ptoken->token_str );
		}
	}

printf( "|" );
}

// ==========================================================================
// FLOATING POINT DATA
// ==========================================================================

// --------------------------------------------------------------------------
// Read numeric constant
//
// Inputs:  aptr - Atari BASIC context
//
// Outputs: None
//
// Results: None 
//
// Effects: The value of the numeric constant is displayed
// --------------------------------------------------------------------------

void ataribasic_dump_numconstant( ATARIBASIC *aptr )
{
int buffer[8];
char asciibuf[64];
int pn;

for ( pn= 0; pn < 6; pn++ )
	{
	buffer[pn] = ataribasic_getbyte( aptr );
	}

for ( pn= 0; pn < 6; pn++ )
	{
	printf( "%02X", buffer[pn] );

	if ( pn < 5 )
		{
		printf( " " );	
		}
	}	

if ( aptr->options.m_dumplineextended )
	{
	ataribasic_num2ascii( buffer, asciibuf );

	printf( " '%s' ", asciibuf );
	}

printf( "|");
}

// ==========================================================================
// STRING CONSTANTS
// ==========================================================================

// --------------------------------------------------------------------------
// Read string constant
//
// Inputs:  aptr - Atari BASIC context
//
// Outputs: None
//
// Results: None 
//
// Effects: The value of the string constant is displayed
// --------------------------------------------------------------------------

void ataribasic_dump_stringconstant( ATARIBASIC *aptr )
{
int len;
int opcode, revmode;

revmode = 0;

len = ataribasic_getbyte( aptr );

printf( "%02X|", len );
while ( len-- )
	{
	opcode = ataribasic_getbyte( aptr );

	printf( "%02X", opcode );

	if ( len > 0 )
		{
		printf( " ");
		}
	}
printf( "|");
}

// ==========================================================================
// DATA AND COMMENTS
// ==========================================================================

// --------------------------------------------------------------------------
// Process REM and DATA text
//
// Inputs: aptr - Atari BASIC context
//
// Outputs: None
//
// Results: None
//
// Effects: The contents of the REM or DATA statement are displayed
// --------------------------------------------------------------------------

void ataribasic_dump_text( ATARIBASIC *aptr )
{
int opcode, revmode;

revmode = 0;
// Last character in a data system is always ATARI_EOL

while ( (opcode = ataribasic_getbyte(aptr ) ) != ATARI_EOL )
	{
	printf( "%02X ", opcode );
	}

printf( "%02X| ", opcode );
}

// ==========================================================================
// CODE STATEMENTS
// ==========================================================================

// --------------------------------------------------------------------------
// Process the command token
//
// Inputs:  aptr - Atari BASIC context
//          opcode - Which statement opcode to process
//
// Outputs: None
//
// Results: true if REM or DATA statement processed
//          false otherwise
//
// Effects: None
//
// Notes:
//
// The command forms a sequence such as follows:
//
// <cmd> <op>* | <numconst-op> <number> |
//             | <strconst-op> <string> | , 
//             | <variable>             |
// 
// --------------------------------------------------------------------------

int ataribasic_dump_command_token( ATARIBASIC *aptr, int opcode )
{
TOKEN_ENTRY *pcmdtoken;

pcmdtoken = token_find_cmd( opcode );

if ( pcmdtoken )
	{
	ataribasic_dump_token( aptr, pcmdtoken );

	if ( pcmdtoken->token_id == ATARI_CMD_REM )
		{
		ataribasic_dump_text( aptr );
		return( true);
		}

	if ( pcmdtoken->token_id == ATARI_CMD_DATA )
		{
		ataribasic_dump_text( aptr );
		return(true );
		}
	}

return( false);
}

// --------------------------------------------------------------------------
// Process a single statement token
//
// Inputs:  aptr   - Atari BASIC context
//          opcode - Which statement opcode to process
// 
// Outputs: done - Pointer to integer indicating that process is done
//
// Results: Non-zero if there is more statement to process
//          Zero otherwise
//
// Effects: The token is displayed
// --------------------------------------------------------------------------

int ataribasic_dump_statement_token( ATARIBASIC *aptr, int opcode, int *done )
{
int byte;
TOKEN_ENTRY *ptk;

ptk = token_find( opcode );

switch (opcode )
	{
	case ATARI_OP_STMTEND:
		ataribasic_dump_token( aptr, ptk );
		*done = 1;
		break;

	case ATARI_OP_LINEEND:
		ataribasic_dump_token( aptr, ptk );
		*done = 1;
		break;

	case ATARI_OP_NUMCONST:   // Numeric constant - read the 6 bytes
		ataribasic_dump_numconstant( aptr );
		*done = 0;
		break;

	case ATARI_OP_STRCONST:   // String constant - read until EOL
		ataribasic_dump_stringconstant( aptr );
		*done = 0;
		break;

	case ATARI_OP_THEN:	   // Then statement - but GOTO or statement?
		ataribasic_dump_token( aptr, ptk );

		byte = ataribasic_peekbufferbyte( aptr );

		if ( byte == ATARI_OP_NUMCONST )
			{
                        // Read the num-const byte
			byte = ataribasic_getbufferbyte( aptr );

			// Now the BCD line number
			ataribasic_dump_numconstant( aptr );

			*done =0;
			return(0);
			}
		else
			{
			*done = 0;
			return(1);
			}
		break;

	default:		  // Regular operator - so write it out
		if ( ptk!=NULL )
			{
			ataribasic_dump_token( aptr, ptk );
			}
		*done = 0;
		break;
	}

return( 0 );	// 0
}

// --------------------------------------------------------------------------
// Process variable token
//
// Inputs: aptr - Atari BASIC context
//         opcode - The opcode
//
// Outputs: None
//
// Results: None
//
// Effects: The variable is displayed
// --------------------------------------------------------------------------

void ataribasic_dump_variable_token( ATARIBASIC *aptr, int opcode )
{
ATARIVARIABLE *avptr;

printf( "%02X", opcode );

if ( aptr->options.m_dumplineextended )
	{
	if ( opcode >= 0x80 ) // Opcode indexes a variable - so display it
		{
        	avptr = aptr->m_varlist+opcode-0x80;

		printf( " %s ", avptr->m_name  );
		}
        }

printf( "|");
}

// --------------------------------------------------------------------------
// Process an ATARI BASIC statement
//
// Inputs:  aptr - Atari BASIC context
//
// Outputs: None
//
// Results: Non-zero if end of line is reached
//
// Effects: The statement is processed
// --------------------------------------------------------------------------

int ataribasic_dump_statement( ATARIBASIC *aptr )
{
int done, lineoffset, opcode, opcmd, statoffset, gotcmd, cmd, byte, doret;
TOKEN_ENTRY *ptk;
TOKEN_ENTRY *pcmdtoken;
int result;

statoffset = ataribasic_getbyte( aptr );	// Statement offset

done = 0;
gotcmd = 0;

while ( !done )
	{
	opcode = ataribasic_getbyte( aptr );

	if ( !gotcmd )			// First byte is always a command
		{
		gotcmd++;

		// REM and DATA need to be handled separately
		if ( ataribasic_dump_command_token( aptr, opcode ) )
			return(1);
		}
	else
		{
		if ( ATARI_FUNCTION_OR_OPERATOR(opcode ) )
			{
			// Process statement token. If in the case of a THEN
			// keyword, it might be a compound statement rather
			// than an implied GOTO. Process that here.

			if ( ataribasic_dump_statement_token(
					aptr, opcode, &done ) )
				{
				return( done );
				}
			}
		else	// Regular variable, so write out out
			 ataribasic_dump_variable_token( aptr, opcode );
		}
	}

			// Indicate when ATARI_OP_LINEEND was received
return( opcode == ATARI_OP_LINEEND );
}

// --------------------------------------------------------------------------
// Process a single command within the line
//
// Inputs: aptr   - Atari BASIC context
//         lineno - Integer line number
//
// Outputs: None
//
// Results: None
//
// Effects: The selected line is processed
// --------------------------------------------------------------------------

int ataribasic_dumplinetokens( ATARIBASIC *aptr )
{
int lineno, lineoffset;

// First two bytes are the actual line number 
lineno = ataribasic_getpointer( aptr );

if ( (lineno == 0x8000 ) && !(aptr->options.m_showlastline) )
	{
        return( lineno);
	}

printf( "\n|%5d|", lineno );

// Following bytes are the line length, statement lengths, 
// sequences of operators, functions numeric and

lineoffset = ataribasic_getbyte( aptr );

// The remaining bytes are a sequence of operators, functions, numeric
// and string constants

while ( !ataribasic_dump_statement( aptr ) );

printf( "\n");
}

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

void ataribasic_writetoken( ATARIBASIC *aptr, TOKEN_ENTRY *ptoken )
{
printf( "%s", ptoken->token_str );
}

// ==========================================================================
// FLOATING POINT DATA
// ==========================================================================

// --------------------------------------------------------------------------
// Get a BCD digit for the Atari BASIC floating point value
//
// Inputs:  pbytes - Number of bytes
//          digit  - The input digit
//
// Outputs: None
//
// Results: The encoded value
//
// Effects: None
// --------------------------------------------------------------------------

int ataribasic_getdigit( int *pbytes, int digit )
{
int result;

result = pbytes[(digit>>1)+1];

if ( !(digit & 0x01) )
		result = result >> 4;

return( result & 0x0F );
}

// --------------------------------------------------------------------------
// Display an Atari basic floating point value
//
// Inputs: pbytes - Pointer to the six bytes
//         fresult - Pointer to the ASCII string
//
// Outputs: fresult - Pointer to the ASCII string
//
// Results: None
//
// Effects: None
//
// Notes:
//
// The six bytes used to represent a floating point value have the following
// purpose:
//
// +--------+---------+---------+---------+---------+---------+
// |0       | 1       | 2       | 3       | 4       | 5       |
// |76543210|76543210 |76543210 |76543210 |76543210 |76543210 |
// +-+------+----+----+----+----+----+----+----+----+----+----+
// | | exp  |num |num |num |num |num |num |num |num |num |num |
// | |      |    |    |    |    |    |    |    |    |    |    |
// | |      +----+----+----+----+----+----+----+----+----+----+
// | | Exponent                 |
// | | excess 64 power of ten   |
// | \--------------------------+
// |  Sign bit                  |
// \----------------------------+
//
// --------------------------------------------------------------------------

void ataribasic_num2ascii( int *pbytes, char *fresult )
{
int pos = 0, pn;
int digit, lastdigit, dotpos, expval, expsign, ival, shift, expmode;
float fpow, floatval;

// ----- First stage - Extract the exponent sign and value ------------------

expsign = (pbytes[0] & 0x80 ) == 0x80;
expval  =( pbytes[0] & 0x7F )- 0x40;   // excess 65 notation

expval *= 2;			// Shift powers of 10 to powers of 100
dotpos = 2 + expval;

// ----- Write out the sign -------------------------------------------------

if ( expsign )
		fresult[pos++] = '-';

// ----- Non-exponent data --------------------------------------------------

if ( (dotpos <= 0) && (dotpos >= -1))
		{
		fresult[pos++] = '0';
		fresult[pos++] = '.';

		for ( pn = 1; pn < -dotpos; pn++ )
				fresult[pos++] = '0';
		}

// ----- Find the last digit that is non-zero -------------------------------

lastdigit=9;

while ( (ataribasic_getdigit( pbytes, lastdigit ) == 0) && 
	(lastdigit >= dotpos) )
	lastdigit--;

// ----- If there are no digits, then we have a zero ------------------------

if ( (expval == -128) )
		fresult[pos++] = '0';
else
		{	   
		// Otherwise we have a fraction, integer or exponet value

		expmode = (dotpos < 0 ) || (dotpos > 12 );

		for ( pn = 0; pn <= lastdigit; pn++ )
			{
			digit = ataribasic_getdigit( pbytes, pn );

			if ( (pn != 0) || (digit != 0 ) )
				fresult[pos++] = digit + '0';

			if  (expmode && (pn==0 ) )
				fresult[pos++] = '.';

			if ( ( pn+1 == dotpos ) && (pn!=lastdigit) )
				fresult[pos++] = '.';
			}

		// ----- If the value is less than 1.0e-2, or greater than
		//	 1.0e+10, then use scientific notation

		if ( dotpos < 0 )
			{
			fresult[pos++] = 'E';
			fresult[pos++] = '-';
			expval = -expval;
			fresult[pos++] = ((expval /10)% 10) + '0';
			fresult[pos++] = ((expval % 10)) + '0';
			}
		else
			if ( dotpos > 12 )
				{
				fresult[pos++] = 'E';
				fresult[pos++] = '+';
				fresult[pos++] = ((expval /10)% 10) + '0';
				fresult[pos++] = ((expval % 10)) + '0';
				}
		}

// ----- Always terminate with a zero character -----------------------------

fresult[pos] = '\0';
}

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

void ataribasic_process_numconstant( ATARIBASIC *aptr )
{
int buffer[8];
char asciibuf[64];
int pn;

for ( pn= 0; pn < 6; pn++ )
	buffer[pn] = ataribasic_getbyte( aptr );

// Convert numeric value into ASCII text

ataribasic_num2ascii( buffer, asciibuf );

printf( "%s", asciibuf );
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

void ataribasic_process_stringconstant( ATARIBASIC *aptr )
{
int len;
int opcode, revmode;

revmode = 0;

len = ataribasic_getbyte( aptr );

printf("\"");
while ( len-- )
	{
	opcode = ataribasic_getbyte( aptr );

#ifdef OPTION_TERMCAP
	if ( aptr->options.m_usetermcap )
		{
		if ( (opcode & 0x80) && (!revmode) )
			{
			printf( "%s", enter_reverse_mode );
			revmode++;
			}

		if ( !(opcode & 0x80) && (revmode ) )
			{
			printf( "%s", exit_attribute_mode );
			revmode--;
			}
		}
#endif

	if ( aptr->options.m_rawataricompatible )
		printf( "%c", opcode & 0xff );
	else
		printf( "%c", opcode & 0x7f );
	}


#ifdef OPTION_TERMCAP
if ( aptr->options.m_usetermcap )
	printf( "%s", exit_attribute_mode );
#endif

printf("\"");
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

void ataribasic_process_text( ATARIBASIC *aptr )
{
int opcode, revmode;

revmode = 0;
// Last character in a data system is always ATARI_EOL

while ( (opcode = ataribasic_getbyte(aptr ) ) != ATARI_EOL )
	{
#ifdef OPTION_TERMCAP
	if ( aptr->options.m_usetermcap )
		{
		if ( (opcode & 0x80) && (!revmode) )
			printf( "%s", enter_reverse_mode );

		if ( !(opcode & 0x80) && (revmode ) )
			printf( "%s", exit_attribute_mode );
		}
#endif
	printf( "%c", opcode & 0x7F );
	}

#ifdef OPTION_TERMCAP
if ( aptr->options.m_usetermcap )
	printf( "%s", exit_attribute_mode );
#endif
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

int ataribasic_process_command_token( ATARIBASIC *aptr, int opcode )
{
TOKEN_ENTRY *pcmdtoken;

pcmdtoken = token_find_cmd( opcode );

if ( pcmdtoken )
	{
	ataribasic_writetoken( aptr, pcmdtoken );

	if ( pcmdtoken->token_id == ATARI_CMD_REM )
		{
		ataribasic_process_text( aptr );
		return( true);
		}

	if ( pcmdtoken->token_id == ATARI_CMD_DATA )
		{
		ataribasic_process_text( aptr );
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

int ataribasic_process_statement_token( 
		ATARIBASIC *aptr, int opcode, int *done )
{
int byte;
TOKEN_ENTRY *ptk;

ptk = token_find( opcode );

switch (opcode )
	{
	case ATARI_OP_STMTEND:
		*done = 1;
		ataribasic_writetoken( aptr, ptk );
		break;

	case ATARI_OP_LINEEND:
		*done = 1;
		break;

	case ATARI_OP_NUMCONST:   // Numeric constant - read the 6 bytes
		ataribasic_process_numconstant( aptr );
		*done = 0;
		break;

	case ATARI_OP_STRCONST:   // String constant - read until EOL
		ataribasic_process_stringconstant( aptr );
		*done = 0;
		break;

	case ATARI_OP_THEN:	   // Then statement - but GOTO or statement?
		ataribasic_writetoken( aptr, ptk );

		// It looks like the original programmers decided that
		// an implied goto would be faster than a declared goto 
		// to save decoding time. 
		// 
		// We have to test for the numeric constant here and 
		// directly process the statement token

		byte = ataribasic_peekbufferbyte( aptr ); // Have a look

		if ( byte == ATARI_OP_NUMCONST ) // Yes, a goto
			{
			// Read the num-const byte
			byte = ataribasic_getbufferbyte( aptr );

			// Now the BCD line number
			ataribasic_process_numconstant( aptr );
			*done = 0;
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
			ataribasic_writetoken( aptr, ptk );
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

void ataribasic_process_variable_token( ATARIBASIC *aptr, int opcode )
{
ATARIVARIABLE *avptr;

if ( opcode >= 0x80 ) // Opcode indexes a variable - so display it
	{
	avptr = aptr->m_varlist+opcode-0x80;
	printf( "%s", avptr->m_name );
  	}
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

int ataribasic_process_statement( ATARIBASIC *aptr )
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
		if ( ataribasic_process_command_token( aptr, opcode ) )
			return(1);
		}
	else
		{
		if ( ATARI_FUNCTION_OR_OPERATOR(opcode ) )
			{
			// Process statement token. If in the case of a THEN
			// keyword, it might be a compound statement rather
			// than an implied GOTO. Process that here.

			if ( ataribasic_process_statement_token(
					aptr, opcode, &done ) )
				{
				return( done );
				}
			}
		else	// Regular variable, so write out out
			 ataribasic_process_variable_token( aptr, opcode );
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

int ataribasic_dumplineascii( ATARIBASIC *aptr )
{
int lineno, lineoffset;

// First two bytes are the actual line number 
lineno = ataribasic_getpointer( aptr );

if ( (lineno == 0x8000 ) && !(aptr->options.m_showlastline) )
        return( lineno);

printf( "%d ", lineno );

// Following bytes are the line length, statement lengths, 
// sequences of operators, functions numeric and

lineoffset = ataribasic_getbyte( aptr );

// The remaining bytes are a sequence of operators, functions, numeric
// and string constants

while ( !ataribasic_process_statement( aptr ) );

	if ( aptr->options.m_rawataricompatible )
		printf( "%c",155);
	else
		printf( "\n");
}

// ==========================================================================
// HIGH LEVEL ROUTINES
// ==========================================================================

int ataribasic_process_line( ATARIBASIC *aptr )
{
int lineno;
unsigned int offset;

if ( aptr->options.m_dumplinetokens )
	{
	offset = ataribasic_tell( aptr );

	lineno = ataribasic_dumplinetokens( aptr );

	if ( aptr->options.m_dumplineascii )
		{
		ataribasic_seek( aptr, offset );
		}
	}

if ( aptr->options.m_dumplineascii )
	{
	lineno = ataribasic_dumplineascii( aptr );	
	}

return( lineno );
}

// --------------------------------------------------------------------------
// Read Atari Basic read program
//
// Inputs: aptr - Atari BASIC context
//
// Outputs: None
//
// Results: ATARI_NOERROR
//
// Effects: The selected set of lines are processed
// --------------------------------------------------------------------------

int ataribasic_readprogram( ATARIBASIC *aptr )
{
int lineno, pn, done;

done = 0;

if ( ! aptr->options.m_rawataricompatible ) {
	if ( !(aptr->options.m_dumplinetokens | aptr->options.m_dumplineascii) )
	{
	return( ATARI_NOERROR );
	}	

printf ("-----< Listing of file >-------------------------\n");
}

while ( ataribasic_process_line( aptr ) != 0x8000 );

if ( ! aptr->options.m_rawataricompatible )
	printf ("-------------------------------------------------\n");

return( ATARI_NOERROR );
}


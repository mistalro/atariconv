// --------------------------------------------------------------------------
// File:    fileio.c
//
// Purpose: Source file containing low-level file read routines
//
// Author:  Michael S. A. Robb
//
// Date:    30th November 2000
// --------------------------------------------------------------------------

#include "atari.h"

// --------------------------------------------------------------------------
// Convert an ASCII character to a nibble value
//
// Inputs:  ch - input hexadecimal character
//
// Outputs: None
//
// Results: Decimal value
//
// Effects: None
// --------------------------------------------------------------------------

int ataribasic_atoh( int ch )
{
if ( ch >= '0' && ch <= '9' )
        ch -= '0';

if ( ch >= 'A' && ch <= 'F' )
        ch -= 'A' - 10;

if ( ch >= 'a' && ch <= 'f' )
        ch -= 'a' - 10;

return( ch );
}

// --------------------------------------------------------------------------
// Read a single byte from a hexadecimal encoded file
//
// The file format consists of rows of 16 bytes encoded as two hexadecimal
// ASCII characters
//
// Inputs:  aptr - Atari BASIC
//          fp   - Current file handler
//
// Outputs: None
//
// Results: Decimal value of hexadecimal pair of characters
//
// Effects: None
// --------------------------------------------------------------------------

int ataribasic_gethexbyte( ATARIBASIC *aptr, FILE *fp )
{
int ch, cl;

// Skip white space
while ( !(isxdigit( ch = fgetc(fp) ) ) && !feof(fp) && (ch != '-') );  

if ( feof(fp ) )
        return( -1 );

if ( ch == '-' )                // Our EOF character
        return( -1 );

ch = ataribasic_atoh( ch );     // Read high nibble
cl = fgetc( fp );
cl = ataribasic_atoh( cl );     // Read low nibble

return( (ch << 4) + cl );       // Return byte
}

// --------------------------------------------------------------------------
// Reset the buffer ptr
//
// Inputs: aptr - Atari BASIC context
//
// Outputs: None
//
// Results: None
//
// Effects: The buffer pointer is reset
// --------------------------------------------------------------------------

void ataribasic_resetbufferptr( ATARIBASIC *aptr )
{
aptr->m_pgetptr = aptr->m_ptokenbuffer;
aptr->m_getpos = 0;
}

// --------------------------------------------------------------------------
// Use the internal buffer for all the BASIC programming data
//
// Inputs: aptr - Atari BASIC context
//
// Outputs: None
//
// Results: The current byte is returned
//
// Effects: The current buffer pointer is incremented
// --------------------------------------------------------------------------

int ataribasic_getbufferbyte( ATARIBASIC *aptr )
{
int value;

if ( aptr->m_getpos < aptr->m_tokenbufsize )
        {
        value = *aptr->m_pgetptr;
        aptr->m_pgetptr++;
        aptr->m_getpos++;
        return( value );
        }
else
        return( ATARI_EOF );
}

// --------------------------------------------------------------------------
// Get a peek at the current byte about to be read from the internal buffer
//
// Inputs:  aptr - Atari BASIC context
//
// Outputs: None
//
// Results: The current byte is returned
//
// Effects: None
// --------------------------------------------------------------------------

int ataribasic_peekbufferbyte( ATARIBASIC *aptr )
{
int value;

if ( aptr->m_getpos < aptr->m_tokenbufsize )
        {
        value = *aptr->m_pgetptr;

	return( value );
	}
else
	{
	return( ATARI_EOF );
	}
}

// --------------------------------------------------------------------------
// Set the read pointer to a location within the buffer
// 
// Inputs:  aptr - Atari BASIC context
// 
// Outputs: None
//
// Results: None
//
// Effects: None
// --------------------------------------------------------------------------

void ataribasic_seek( ATARIBASIC *aptr, unsigned int pos )
{
if ( pos <= aptr->m_tokenbufsize )
	{
	aptr->m_getpos = pos;
	aptr->m_pgetptr = aptr->m_ptokenbuffer + pos;
	}
}

// --------------------------------------------------------------------------
// These are the buffered getbyte routines, as the THEN statement can either
// result in an implied goto, or an actual statement
//
// Inputs:  aptr - Atari BASIC context
//
// Outputs: None
//
// Results: The first unread or unget byte
//
// Effects: Any unput characters are read, otherwise the current byte
//          pointer is incremented
// --------------------------------------------------------------------------

int ataribasic_getbyte( ATARIBASIC *aptr )
{
int byte;

if ( aptr->m_ungetcount )
        {
        aptr->m_ungetcount--;
        byte = aptr->m_ungetbuffer[aptr->m_ungetcount];
        }
else
        byte = ataribasic_getbufferbyte( aptr );

return( byte );
}

// --------------------------------------------------------------------------
// When we determine what comes after the THEN statement, we must put back
// the byte and process the bytes accordingly.
//
// Inputs: aptr - Atari BASIC context
//         byte - byte to unput
//
// Outputs: None
//
// Results: None
//
// Effects: The byte is added to the unget buffer
// --------------------------------------------------------------------------

void ataribasic_ungetbyte( ATARIBASIC *aptr, int byte )
{
if ( aptr->m_ungetcount < MAX_UNGETBUFFER )
        {
        aptr->m_ungetbuffer[aptr->m_ungetcount] = byte;
        aptr->m_ungetcount++;
        }
}

// --------------------------------------------------------------------------
// Read in a 16-bit pointer or line number - this is in the format of
// Lo-byte:Hi-byte
//
// Inputs: aptr - Atari BASIC context
// 
// Outputs: None
//
// Results: The value of the 16-bit pointer
// 
// Effects: None
// --------------------------------------------------------------------------

int ataribasic_getpointer( ATARIBASIC *aptr )
{
int plo, phi;

plo = ataribasic_getbyte( aptr );
phi = ataribasic_getbyte( aptr );

return( (phi << 8) + plo );
}

// --------------------------------------------------------------------------
// Read the header of an Atari Basic tokenised file
//
// Inputs:  aptr - Atari BASIC context
//
// Outputs: None
//
// Results: None
//
// Effects: The seven 16-bit pointers are set
// --------------------------------------------------------------------------

int ataribasic_readheader( ATARIBASIC *aptr )
{
aptr->m_lomem  = ataribasic_getpointer( aptr );
aptr->m_vntp   = ataribasic_getpointer( aptr );
aptr->m_vntd   = ataribasic_getpointer( aptr );
aptr->m_vvtp   = ataribasic_getpointer( aptr );
aptr->m_stmtab = ataribasic_getpointer( aptr );
aptr->m_stmcur = ataribasic_getpointer( aptr );
aptr->m_starp  = ataribasic_getpointer( aptr );
}

// --------------------------------------------------------------------------
// Read Atari Basic variable names
//
// Inputs:  aptr - Atari BASIC context
//
// Outputs: None
//
// Results: None
//
// Effects: None
// --------------------------------------------------------------------------

int ataribasic_readvarnames( ATARIBASIC *aptr )
{
int varcount = 0;
int ch = 32;
int chpos = 0;
int nbytes;

// --------------------------------------------------------------------------
// Skip over first set of bytes 
// --------------------------------------------------------------------------

if ( aptr->options.m_fixvartable )
        {
        nbytes = aptr->m_vvtp - aptr->m_vntd;

        while ( nbytes--)
                ch = ataribasic_getbyte( aptr );
        return( ATARI_NOERROR );        // !!!!!! Returned no value !!!!! 
        }

// --------------------------------------------------------------------------
// Now read the variables
// --------------------------------------------------------------------------

ATARIVARIABLE *avptr;

avptr = aptr ->m_varlist;

while ( ch != 0 )
        {
        ch = ataribasic_getbyte( aptr );
        avptr = aptr->m_varlist+varcount;

        if ( ch & 0x80 )  // MSB set, so end of variable name 
                {
                ch &= 0x7F;             // Flag read, so discard

                avptr->m_name[chpos++] = ch;  // Set character 
                avptr->m_name[chpos] = 0;     // NULL terminate 
                chpos = 0;
                varcount++;
                }
        else
                if ( ch == 0 )
                        {
                        avptr->m_name[chpos] = 0;
                        varcount++;
                        chpos = 0;
                        }
                else
                        { // Otherwise, just add character 
                        avptr->m_name[chpos++] = ch;
                        }
        }

aptr->m_varnum = varcount;  // Save number of variables 

return( ATARI_NOERROR );
}

// --------------------------------------------------------------------------
// Read string data
//
// Inputs:  aptr - Atari BASIC context
//
// Outputs: None
//
// Results: None
//
// Effects: None
// --------------------------------------------------------------------------

void ataribasic_readlomemdata( ATARIBASIC *aptr)
{
int nbytes, pn, byte;
nbytes = aptr->m_vntd - aptr->m_vntp;

printf( "Reading %d bytes of string data\n", nbytes );

for ( pn = 0; pn < nbytes; pn++ )
        {
        byte = ataribasic_getbyte( aptr );
//      printf( "%02d - %02X\n", pn, byte );
        }
}

// --------------------------------------------------------------------------
// Read Atari Basic variable values
//
// Inputs: aptr - Atari BASIC context
//         vn   - Which variable index
//
// Outputs: None
//
// Effects: The pointers and entries in the variable table are set up
// 
// Results: ATARI_NOERROR if no error has occurred
//
// Notes:
//
// VVTP - Variable value table. This table contains current information
//        on each variable. For each variable in the name, table, 8 bytes
//        are reserved in the value table. The information for each
//        variable type is:
//
//        +--------------+----+----+-----+-----+-----+-----+------+-----+
//        | Byte number  |  0 | 1  |  2  |  3  |  4  |  5  |  6   |  7  |
//        +--------------+----+----+-----+-----+-----+-----+------+-----+
//        | Scalar       | 00 |Var#|       6 Byte BCD constant          |
//        +--------------+----+----+-----------+-----------+------------+
//        | Array DIM'ed | 41 |Var#|Offset     |first DIM+1|second DIM+1|
//        | unDIM'ed     | 40 |    |from STARP |           |            |
//        +--------------+----+----+-----------+-----------+------------+
//        | String DIM'ed| 81 |Var#|Offset     |Length     | DIM        |
//        |              | 80 |    |from STARP |           |            |
//        +--------------+----+----+-----------+-----------+------------+
//
// --------------------------------------------------------------------------

int ataribasic_readvarvalue( ATARIBASIC *aptr, int vn )
{
int offset, dim1, dim2, length, dim, bn;
char bcdval[8];
ATARIVARIABLE *avptr;

avptr = aptr->m_varlist+vn;

avptr->m_type     = ataribasic_getbyte( aptr );
avptr->m_idnumber = ataribasic_getbyte( aptr );

switch( avptr->m_type )
        {
        case ATARI_VAR_SCALAR:
                for ( bn = 0; bn < 6; bn++ )
                        avptr->m_value[bn]
                                = ataribasic_getbyte(aptr);
                avptr->m_value[6] = 0;
                break;

        case ATARI_VAR_ARRAY_DIM:
        case ATARI_VAR_ARRAY_UNDIM:
                avptr->m_offset = ataribasic_getpointer( aptr );
                avptr->m_dim[0] = ataribasic_getpointer( aptr );
                avptr->m_dim[1] = ataribasic_getpointer( aptr );
                break;

        case ATARI_VAR_STRING_DIM:
        case ATARI_VAR_STRING_UNDIM:
                avptr->m_offset = ataribasic_getpointer( aptr );
                avptr->m_dim[0] = ataribasic_getpointer( aptr );
                avptr->m_dim[1] = ataribasic_getpointer( aptr );
                break;

        default:
                printf( "Unknown value %02X\n", avptr->m_type );
                break;
        }

return( ATARI_NOERROR );
}

// -------------------------------------------------------------------------
// Read the list of variable values
//
// Inputs: aptr - ATARI basic context
//
// Outputs: None
//
// Results: The number of variables
//
// Effects: The set of variables are read in
// -------------------------------------------------------------------------

int ataribasic_readvarvalues( ATARIBASIC *aptr )
{
int vn, bn, nvars;

nvars = ( aptr->m_stmtab - aptr->m_vvtp ) / 8;
if ( ! aptr->options.m_rawataricompatible ) {

	printf( "File number of variables= %d\n", nvars );
	printf( "Actual number of variables = %d\n", aptr->m_varnum-1 );

}
for ( vn = 0; vn < nvars; vn++ )
	ataribasic_readvarvalue( aptr, vn );
}

// -------------------------------------------------------------------------
// Load tokenised HEX file
//
// Inputs:  aptr - Atari BASIC context
//
// Outputs: None
//
// Results: Non-zero on success, zero otherwise
//
// Effects: The tokenised file is read in, if possible
// -------------------------------------------------------------------------

int ataribasic_loadhexfile( ATARIBASIC *aptr, char *pfilename )
{
struct stat statbuf;
FILE *fp;
int byte;
unsigned char *chptr;
char buffer[1024];

if ( stat( pfilename, &statbuf ) == -1 )
        {
        return(0);
        }

if ( !(S_ISLNK(statbuf.st_mode) || S_ISREG( statbuf.st_mode) ) )
	{
	printf( "Error: <%s> is not a regular file\n", pfilename );
	exit(0);
	}

if ( aptr->options.m_verbose )
	{
	printf( "Reading hex file <%s>\n", pfilename );
	}

ataribasic_allocate( aptr, statbuf.st_size*3+2 );

if ( (fp = fopen( pfilename, "r" ) ) )
	{
	fgets( buffer, 1023, fp );      // Skip over title

	chptr = aptr->m_ptokenbuffer;

	while ( ( byte = ataribasic_gethexbyte( aptr, fp ) ) != -1 )
		{
		*chptr++ = byte;
		}

	aptr->m_tokenbufsize++;
	fclose(fp);

	if ( aptr->options.m_verbose )
		{
		printf( "Done\n");
		}

	return(1);
	}
}

// -------------------------------------------------------------------------
// Load tokenised BASIC file
//
// Inputs:  aptr - Atari BASIC context
//
// Outputs: None
//
// Results: Non-zero on success, zero otherwise
//
// Effects: The tokenised file is read in, if possible
// -------------------------------------------------------------------------

int ataribasic_loadbasfile( ATARIBASIC *aptr, char *pfilename )
{
struct stat statbuf;
FILE *fp;

if ( stat( pfilename, &statbuf ) == -1 )
        {
        return(0);
        }

if ( !(S_ISLNK(statbuf.st_mode) || S_ISREG( statbuf.st_mode) ) )
	{
	printf( "Error: <%s> is not a regular file\n", pfilename );
	exit(0);
	}

if ( aptr->options.m_verbose )
	{
	printf( "Reading .BAS file <%s>\n", pfilename );
	}

ataribasic_allocate( aptr, statbuf.st_size+2 );

if ( (fp = fopen( pfilename, "rb" ) ) )
	{
	fread( aptr->m_ptokenbuffer, statbuf.st_size, 1, fp );

	aptr->m_tokenbufsize = statbuf.st_size;

	if ( aptr->options.m_verbose )
		{
		printf( "Done\n");
		}

	fclose( fp );
	return(1);
        }
}

// --------------------------------------------------------------------------
// Load a file of any type
//
// Inputs:  aptr      - Atari BASIC context
//          pfilename - Pointer to the filename
//
// Outputs: None
//
// Results: non-zero if the file was loaded, zero otherwise
//
// Effects: None
// --------------------------------------------------------------------------

int ataribasic_loadfile( ATARIBASIC *aptr, char *pfilename)
{
ataribasic_deallocate( aptr );

// ----- Read in hexadecimal dump files ------------------------------------

if ( aptr->options.m_usehexfile )
        {
        return( ataribasic_loadhexfile( aptr, pfilename ) );
        }

if ( aptr->options.m_usebasfile )
        {
        return( ataribasic_loadbasfile( aptr, pfilename ) );
        }

return(0);
}


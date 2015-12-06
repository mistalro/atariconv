/* --------------------------------------------------------------------------
 * File: fileio.h
 *
 * Purpose: file input routines
 * --------------------------------------------------------------------------
 */

#ifndef _ATARI_FILEIO_H_
#define _ATARI_FILEIO_H_

int  ataribasic_atoh( int ch );
int  ataribasic_gethexbyte( ATARIBASIC *aptr, FILE *fp );
void ataribasic_resetbufferptr( ATARIBASIC *aptr );
int  ataribasic_getbufferbyte( ATARIBASIC *aptr );
int  ataribasic_getbyte( ATARIBASIC *aptr );
void ataribasic_ungetbyte( ATARIBASIC *aptr, int byte );
int  ataribasic_getpointer( ATARIBASIC *aptr );
int  ataribasic_readheader( ATARIBASIC *aptr );
int  ataribasic_readvarnames( ATARIBASIC *aptr );
void ataribasic_readlomemdata( ATARIBASIC *aptr );
int  ataribasic_readvarvalue( ATARIBASIC *aptr, int vn );
int  ataribasic_readvarvalues( ATARIBASIC *aptr );
int  ataribasic_loadfile( ATARIBASIC *aptr, char *pfilename );

void ataribasic_seek( ATARIBASIC *aptr, unsigned int offset );

int  ataribasic_peekbufferbyte( ATARIBASIC *aptr );

#define ataribasic_tell( A ) \
	(A)->m_getpos

#endif	/* _ATARI_FILEIO_H_ */

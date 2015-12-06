/* --------------------------------------------------------------------------
 * File: dump.h
 *
 * Purpose: file input routines
 * --------------------------------------------------------------------------
 */

#ifndef _ATARI_DUMP_H_
#define _ATARI_DUMP_H_

void ataribasic_header_display( ATARIBASIC *aptr);
void ataribasic_varname_display( ATARIBASIC *aptr );
void ataribasic_dumpbuffer( ATARIBASIC *aptr );

int ataribasic_dumplinetokens( ATARIBASIC *aptr );

#endif	/* _ATARI_DUMP_H_ */

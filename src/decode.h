/* --------------------------------------------------------------------------
 * File: decode.h
 *
 * Purpose: Decoding of tokenised BASIC
 * --------------------------------------------------------------------------
 */

#ifndef _ATARI_DECODE_H_
#define _ATARI_DECODE_H_

void ataribasic_writetoken( ATARIBASIC *aptr,
                                TOKEN_ENTRY *ptoken );

int  ataribasic_getdigit( int *pbytes, int digit );
void ataribasic_num2ascii( int *pbytes, char *fresult );
void ataribasic_process_numconstant( ATARIBASIC *aptr );
void ataribasic_process_stringconstant( ATARIBASIC *aptr );

void ataribasic_process_text( ATARIBASIC *aptr );

int  ataribasic_process_command_token( ATARIBASIC *aptr, int opcode );

int  ataribasic_process_statement_token( ATARIBASIC *aptr, int opcode, 
                                        int *done );

void ataribasic_process_variable_token( ATARIBASIC *aptr, int opcode );

int  ataribasic_process_statement( ATARIBASIC *aptr );

void ataribasic_process_command( ATARIBASIC *aptr, int lineno );

int  ataribasic_dumplineascii( ATARIBASIC *aptr );

int  ataribasic_process_line( ATARIBASIC *aptr );

int  ataribasic_readprogram( ATARIBASIC *aptr );


#endif	/* _ATARI_DECODE_H_ */

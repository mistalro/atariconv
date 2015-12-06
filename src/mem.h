/* --------------------------------------------------------------------------
 * File: mem.h
 *
 * Purpose: Memory management
 * --------------------------------------------------------------------------
 */

#ifndef _ATARI_MEM_H_
#define _ATARI_MEM_H_

void    ataribasic_setuptermcap( void );
void    ataribasic_init( ATARIBASIC *aptr );
void    ataribasic_deallocate( ATARIBASIC *aptr );
void    ataribasic_allocate( ATARIBASIC *aptr, int bytes );
void    ataribasic_delete( ATARIBASIC*aptr);
ATARIBASIC *ataribasic_create( void );

#endif	/* _ATARI_MEM_H_ */

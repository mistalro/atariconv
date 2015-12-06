// --------------------------------------------------------------------------
// File:    repair.c
//
// Purpose: Source file containing variable name table repair routine
// --------------------------------------------------------------------------

#include "atari.h"

// -------------------------------------------------------------------------
// Repair mode 
//
// Inputs:  aptr - Atari BASIC context
//
// Outputs: None
//
// Effects: The string name of the variable is set from the data type
//
// Results: ATARI_NOERROR
// -------------------------------------------------------------------------

int ataribasic_varnamefromtype( ATARIBASIC *aptr)
{
int vn, nvars = ( aptr->m_stmtab - aptr->m_vvtp ) / 8;
ATARIVARIABLE *avptr;

for ( vn = 0; vn < nvars; vn++ )
        {
        avptr = aptr->m_varlist+vn;

        switch ( avptr->m_type )
                {
                case ATARI_VAR_SCALAR:
                        sprintf( avptr->m_name, "V%02d",
				 aptr->options.m_numscalar++ );
                        break;

                case ATARI_VAR_STRING_UNDIM:
                case ATARI_VAR_STRING_DIM:
                        sprintf( avptr->m_name, "A%02d(", 
				aptr->options.m_numstring++ );
                        break;

                case ATARI_VAR_ARRAY_UNDIM:
                case ATARI_VAR_ARRAY_DIM:
                        sprintf( avptr->m_name, "S%02d$", 
				aptr->options.m_numarray++ );
                        break;

                default:
                        printf( "Unknown type %02X\n", avptr->m_type );
                        break;
                }
        }
}


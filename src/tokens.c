// --------------------------------------------------------------------------
// File:    tokens.c
//
// Purpose: Source file containing list of tokens and their ASCII symbols
//
// Author:  Michael S. A. Robb
//
// Date:    30th November 2000
// --------------------------------------------------------------------------

#include "atari.h"

// --------------------------------------------------------------------------
// Atari BASIC Commands
// --------------------------------------------------------------------------

TOKEN_ENTRY command_list[] =
{
        { ATARI_CMD_REM,   "REM "   },
        { ATARI_CMD_DATA,  "DATA "  },
        { ATARI_CMD_INPUT, "INPUT " },
        { ATARI_CMD_COLOR, "COLOR " },
        { ATARI_CMD_LIST,  "LIST "  },
        { ATARI_CMD_ENTER, "ENTER " },
        { ATARI_CMD_LET,   "LET "   },
        { ATARI_CMD_IF,    "IF "    },
        { ATARI_CMD_FOR,   "FOR "   },
        { ATARI_CMD_NEXT,  "NEXT "  },
        { ATARI_CMD_GOTO,  "GOTO "  },
        { ATARI_CMD_GO_TO, "GOTO "  },
        { ATARI_CMD_GOSUB, "GOSUB " },
        { ATARI_CMD_TRAP,  "TRAP "  },
        { ATARI_CMD_BYE,   "BYE "   },
        { ATARI_CMD_CONT,  "CONT "  },
        { ATARI_CMD_COM,   "COM "   },
        { ATARI_CMD_CLOSE, "CLOSE " },
        { ATARI_CMD_CLR,   "CLR "   },
        { ATARI_CMD_DEG,   "DEG "   },
        { ATARI_CMD_DIM,   "DIM "   },
        { ATARI_CMD_END,   "END "   },
        { ATARI_CMD_NEW,   "NEW "   },
        { ATARI_CMD_OPEN,  "OPEN "  },
        { ATARI_CMD_LOAD,  "LOAD "  },
        { ATARI_CMD_SAVE,  "SAVE "  },
        { ATARI_CMD_STATUS,"STATUS " },
        { ATARI_CMD_NOTE,  "NOTE "  },
        { ATARI_CMD_POINT, "POINT " },
        { ATARI_CMD_XIO,   "XIO "   },
        { ATARI_CMD_ON,    "ON "    },
        { ATARI_CMD_POKE,  "POKE "  },
        { ATARI_CMD_PRINT, "PRINT " },
        { ATARI_CMD_RAD,   "RAD "   },
        { ATARI_CMD_READ,  "READ "  },
        { ATARI_CMD_RESTORE, "RESTORE " },
        { ATARI_CMD_RETURN,  "RETURN"   },
        { ATARI_CMD_RUN,    "RUN"   },
        { ATARI_CMD_STOP,   "STOP"  },
        { ATARI_CMD_POP,    "POP"   },
        { ATARI_CMD_QPRINT, "? "    },
        { ATARI_CMD_GET,    "GET "  },
        { ATARI_CMD_PUT,    "PUT "  },
        { ATARI_CMD_GRAPHICS, "GRAPHICS " },
        { ATARI_CMD_PLOT,     "PLOT "     },
        { ATARI_CMD_POSITION, "POSITION " },
        { ATARI_CMD_DOS,      "DOS "      },
        { ATARI_CMD_DRAWTO,   "DRAWTO "   },
        { ATARI_CMD_SETCOLOR, "SETCOLOR " },
        { ATARI_CMD_LOCATE,   "LOCATE "   },
        { ATARI_CMD_SOUND,    "SOUND "    },
	{ ATARI_CMD_LPRINT,    "LPRINT "  },
	{ ATARI_CMD_CSAVE,     "CSAVE " },
	{ ATARI_CMD_CLOAD,     "CLOAD " }, 
        { ATARI_CMD_IMPLIEDLET, ""        },	// Invisible
	{ ATARI_CMD_ERROR,      "ERROR - " },
};

// --------------------------------------------------------------------------
// ATARI Basic Operators
// --------------------------------------------------------------------------

TOKEN_ENTRY operator_list[] =
{
        { ATARI_OP_NUMCONST, "<numeric>" }, // Invisible
        { ATARI_OP_STRCONST, "<strconst>" }, // Invisible
        { ATARI_OP_NOTUSED1, "<notused1>" },
        { ATARI_OP_NOTUSED2, "<notused2>" },
        { ATARI_OP_COMMA,    "," },
        { ATARI_OP_DOLLAR,   "$" },
        { ATARI_OP_STMTEND,  ":" },
        { ATARI_OP_SEMICOLON, ";" },
        { ATARI_OP_LINEEND,   "<lineend>" }, // Invisible
        { ATARI_OP_GOTO,      " GOTO " },
        { ATARI_OP_GOSUB,     " GOSUB " },
        { ATARI_OP_TO,        " TO " },
        { ATARI_OP_STEP,      " STEP " },
        { ATARI_OP_THEN,      " THEN " },
        { ATARI_OP_HASH,      "#" },
        { ATARI_OP_NUM_LTE,   "<=" },
        { ATARI_OP_NUM_NE,      "<>" },
        { ATARI_OP_NUM_GTE,   ">=" },
        { ATARI_OP_NUM_LT,      "<" },
        { ATARI_OP_NUM_GT,      ">" },
        { ATARI_OP_NUM_EQ,      "=" },
        { ATARI_OP_NUM_POW,   "^" },
        { ATARI_OP_NUM_MULT,  "*" },
        { ATARI_OP_NUM_ADD,   "+" },
        { ATARI_OP_NUM_SUB,   "-" },
        { ATARI_OP_NUM_DIV,   "/" },
        { ATARI_OP_NUM_NOT,   "NOT " },
        { ATARI_OP_NUM_OR,      " OR " },
        { ATARI_OP_NUM_AND,   " AND " },
        { ATARI_OP_NUM_LEFTPAR, "(" },  // Invisible
        { ATARI_OP_NUM_RIGHTPAR, ")" },
        { ATARI_OP_NUM_ASSIGN, "=" },

        { ATARI_OP_STR_ASSIGN, "=" },
        { ATARI_OP_STR_LTE, "<=" },
        { ATARI_OP_STR_NE, "<>" },
        { ATARI_OP_STR_GTE, ">=" },
        { ATARI_OP_STR_LT,  "<" },
        { ATARI_OP_STR_GT,  ">" },
        { ATARI_OP_STR_EQ,  "=" },
        { ATARI_OP_STR_ADD, "+" },
        { ATARI_OP_STR_SUB, "-" },
        { ATARI_OP_STR_LEFTPAR, "(" },
        { ATARI_OP_ARRAY_LEFTPAR, "" }, // Invisible  
        { ATARI_OP_DIMARRAY_LEFTPAR, "" },      // Invisible
        { ATARI_OP_FUN_LEFTPAR, "(" },
        { ATARI_OP_DIMSTR_LEFTPAR, "(" },
        { ATARI_OP_ARRAY_COMMA,    "," }
};

// --------------------------------------------------------------------------
// ATARI Basic Functions
// --------------------------------------------------------------------------

TOKEN_ENTRY function_list[] =
{
        { ATARI_FUN_STR,  "STR$" },
        { ATARI_FUN_CHR,  "CHR$" },
        { ATARI_FUN_USR,  "USR" },
        { ATARI_FUN_ASC,  "ASC" },
        { ATARI_FUN_VAL,  "VAL" },
        { ATARI_FUN_LEN,  "LEN" },
        { ATARI_FUN_ADR,  "ADR" },
        { ATARI_FUN_ATN,  "ATN" },
        { ATARI_FUN_COS,  "COS" },
        { ATARI_FUN_PEEK, "PEEK" },
        { ATARI_FUN_SIN,  "SIN" },
        { ATARI_FUN_RND,  "RND" },
        { ATARI_FUN_FRE,  "FRE" },
        { ATARI_FUN_EXP,  "EXP" },
        { ATARI_FUN_LOG,  "LOG" },
        { ATARI_FUN_CLOG, "CLOG" },
        { ATARI_FUN_SQR,  "SQR" },
        { ATARI_FUN_SGN,  "SGN" },
        { ATARI_FUN_ABS,  "ABS" },
        { ATARI_FUN_INT,  "INT" },
        { ATARI_FUN_PADDLE, "PADDLE" },
        { ATARI_FUN_STICK,  "STICK" },
        { ATARI_FUN_PTRIG,  "PTRIG" },
        { ATARI_FUN_STRIG,  "STRIG" }
};


// --------------------------------------------------------------------------
// Find a command keyword
//
// Inputs: token
//
// Outputs: None
//
// Results: Non-null pointer if result matched, NULL otherwise
//
// Effects: None
// --------------------------------------------------------------------------

TOKEN_ENTRY *token_find_cmd( int token )
{
int pn;
TOKEN_ENTRY *ptoken = command_list;

for ( pn = 0; pn < sizeof(command_list)/sizeof(TOKEN_ENTRY); pn++, ptoken++ )
        if ( ptoken->token_id == token )
                return( ptoken );

return( NULL );
}

// --------------------------------------------------------------------------
// Find a command operator
//
// Inputs:  token - Token to match
//
// Outputs: None
//
// Results: Non-null pointer if match found, NULL otherwise
//
// Effects: None
// --------------------------------------------------------------------------

//#define SEARCH_BINARY

#ifdef SEARCH_BINARY
int command_comparefunc( const void *ps1, const void *ps2 ) 
{
TOKEN_ENTRY *pkey = (TOKEN_ENTRY *) ps1;
TOKEN_ENTRY *pitem = (TOKEN_ENTRY *) ps2;

if ( pkey->token_id < pitem->token_id )
	{
	return(-1);
	}
else
if ( pkey->token_id > pitem->token_id )
	{
	return(1);
	}
else
	return(0);
}

TOKEN_ENTRY *token_find_op( int token )
{
TOKEN_ENTRY temp, *pfind;

temp.token_id = token;

pfind = (TOKEN_ENTRY *) bsearch( (void *) &temp,
		(void *) command_list, 
		sizeof(command_list)/sizeof(TOKEN_ENTRY),	
		sizeof(TOKEN_ENTRY), 
		command_comparefunc );

if ( pfind )
	{
	return( pfind);
	}
else
	{
	return( NULL );
	}
}
#else
TOKEN_ENTRY *token_find_op( int token )
{
int pn;
TOKEN_ENTRY *ptoken = operator_list;

for ( pn = 0; pn < sizeof(command_list)/sizeof(TOKEN_ENTRY); pn++, ptoken++ )
	{
        if ( ptoken->token_id == token )
		{
                return( ptoken );
		}
	}

return( NULL );
}
#endif

// --------------------------------------------------------------------------
// Find a command function
//
// Inputs:  token - Token to match
//
// Outputs: None
//
// Results: Non-null pointer if match found, NULL otherwise
//
// Effects: None
// --------------------------------------------------------------------------

TOKEN_ENTRY *token_find_func( int token )
{
int pn;
TOKEN_ENTRY *ptoken = function_list;

for ( pn = 0; pn < sizeof(command_list)/sizeof(TOKEN_ENTRY); pn++, ptoken++ )
        if ( ptoken->token_id == token )
                return( ptoken );

return( NULL );
}

// --------------------------------------------------------------------------
// Find an operator or function
//
// Inputs:  token - Token to match
//
// Outputs: None
//
// Results: Non-null pointer if match found, NULL otherwise
//
// Effects: None
// --------------------------------------------------------------------------

TOKEN_ENTRY *token_find( int token )
{
TOKEN_ENTRY *pentry;

pentry = token_find_op( token );

if ( !pentry )
        pentry = token_find_func( token );

return( pentry );
}



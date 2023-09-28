/* --------------------------------------------------------------------------
 * File: tokens.h
 *
 * Purpose: Utility functions to match token strings
 * --------------------------------------------------------------------------
 */

#ifndef _ATARI_TOKENS_H_
#define _ATARI_TOKENS_H_

// --------------------------------------------------------------------------
// Define a token entry
// --------------------------------------------------------------------------

typedef int  TOKEN_ID;
typedef char TOKEN_STRING[12];

typedef struct token_st
  {
  TOKEN_ID     token_id;                // Token ID
  TOKEN_STRING token_str;               // Token String
  } TOKEN_ENTRY;


TOKEN_ENTRY *token_find_cmd( int token );
TOKEN_ENTRY *token_find_op( int token );
TOKEN_ENTRY *token_find_func( int token );
TOKEN_ENTRY *token_find( int token );

// --------------------------------------------------------------------------
// Command tokens
// --------------------------------------------------------------------------

#define ATARI_CMD_REM     0x00
#define ATARI_CMD_DATA    0x01
#define ATARI_CMD_INPUT   0x02
#define ATARI_CMD_COLOR   0x03
#define ATARI_CMD_LIST    0x04
#define ATARI_CMD_ENTER   0x05
#define ATARI_CMD_LET     0x06
#define ATARI_CMD_IF      0x07
#define ATARI_CMD_FOR     0x08
#define ATARI_CMD_NEXT    0x09
#define ATARI_CMD_GOTO    0x0A
#define ATARI_CMD_GO_TO   0x0B
#define ATARI_CMD_GOSUB   0x0C
#define ATARI_CMD_TRAP    0x0D
#define ATARI_CMD_BYE     0x0E
#define ATARI_CMD_CONT    0x0F
#define ATARI_CMD_COM     0x10
#define ATARI_CMD_CLOSE   0x11  // ?
#define ATARI_CMD_CLR     0x12
#define ATARI_CMD_DEG     0x13
#define ATARI_CMD_DIM     0x14
#define ATARI_CMD_END     0x15
#define ATARI_CMD_NEW     0x16
#define ATARI_CMD_OPEN    0x17
#define ATARI_CMD_LOAD    0x18
#define ATARI_CMD_SAVE    0x19
#define ATARI_CMD_STATUS  0x1A
#define ATARI_CMD_NOTE    0x1B
#define ATARI_CMD_POINT   0x1C
#define ATARI_CMD_XIO     0x1D
#define ATARI_CMD_ON      0x1E
#define ATARI_CMD_POKE    0x1F  // 2 value
#define ATARI_CMD_PRINT   0x20 
#define ATARI_CMD_RAD     0x21
#define ATARI_CMD_READ    0x22
#define ATARI_CMD_RESTORE 0x23
#define ATARI_CMD_RETURN  0x24
#define ATARI_CMD_RUN     0x25
#define ATARI_CMD_STOP    0x26
#define ATARI_CMD_POP     0x27
#define ATARI_CMD_QPRINT  0x28   /* Prints out as ? */
#define ATARI_CMD_GET     0x29
#define ATARI_CMD_PUT     0x2A
#define ATARI_CMD_GRAPHICS 0x2B    // 1 Value
#define ATARI_CMD_PLOT     0x2C 
#define ATARI_CMD_POSITION 0x2D
#define ATARI_CMD_DOS      0x2E
#define ATARI_CMD_DRAWTO   0x2F
#define ATARI_CMD_SETCOLOR 0x30
#define ATARI_CMD_LOCATE   0x31
#define ATARI_CMD_SOUND    0x32
#define ATARI_CMD_LPRINT   0x33
#define ATARI_CMD_CSAVE    0x34
#define ATARI_CMD_CLOAD    0x35
#define ATARI_CMD_IMPLIEDLET      0x36 // Implied let  [var] ASSIGN [EXPR]
#define ATARI_CMD_ERROR    0x37

#define ATARI_CMD_MIN      ATARI_CMD_REM
#define ATARI_CMD_MAX      ATARI_CMD_ERROR

// --------------------------------------------------------------------------
// Operators
// --------------------------------------------------------------------------

#define ATARI_OP_NUMCONST  0x0E
#define ATARI_OP_STRCONST  0x0F
#define ATARI_OP_NOTUSED1  0x10
#define ATARI_OP_NOTUSED2  0x11
#define ATARI_OP_COMMA     0x12
#define ATARI_OP_DOLLAR    0x13
#define ATARI_OP_STMTEND   0x14
#define ATARI_OP_SEMICOLON 0x15
#define ATARI_OP_LINEEND   0x16
#define ATARI_OP_GOTO      0x17
#define ATARI_OP_GOSUB     0x18
#define ATARI_OP_TO        0x19
#define ATARI_OP_STEP      0x1A
#define ATARI_OP_THEN      0x1B
#define ATARI_OP_HASH      0x1C
#define ATARI_OP_NUM_LTE   0x1D  /* <= */
#define ATARI_OP_NUM_NE    0x1E  /* <> */
#define ATARI_OP_NUM_GTE   0x1F  /* >= */
#define ATARI_OP_NUM_LT    0x20  /* < */
#define ATARI_OP_NUM_GT    0x21  /* > */
#define ATARI_OP_NUM_EQ    0x22  /* = */
#define ATARI_OP_NUM_POW   0x23  /* ^ */
#define ATARI_OP_NUM_MULT  0x24  /* * */
#define ATARI_OP_NUM_ADD   0x25  /* + */
#define ATARI_OP_NUM_SUB   0x26  /* - */
#define ATARI_OP_NUM_DIV   0x27  /* / */
#define ATARI_OP_NUM_NOT   0x28  /* NOT */
#define ATARI_OP_NUM_OR    0x29  /* OR */
#define ATARI_OP_NUM_AND   0x2A  /* AND */
#define ATARI_OP_NUM_LEFTPAR  0x2B
#define ATARI_OP_NUM_RIGHTPAR 0x2C
#define ATARI_OP_NUM_ASSIGN    0x2D

#define ATARI_OP_STR_ASSIGN    0x2E
#define ATARI_OP_STR_LTE       0x2F /* <= */
#define ATARI_OP_STR_NE        0x30 /* <> */
#define ATARI_OP_STR_GTE       0x31 /* >= */
#define ATARI_OP_STR_LT        0x32 /* < */
#define ATARI_OP_STR_GT        0x33 /* > */
#define ATARI_OP_STR_EQ        0x34 /* = */
#define ATARI_OP_STR_ADD       0x35 /* + Unary */
#define ATARI_OP_STR_SUB       0x36 /* - */
#define ATARI_OP_STR_LEFTPAR   0x37 /* ( */
#define ATARI_OP_ARRAY_LEFTPAR 0x38
#define ATARI_OP_DIMARRAY_LEFTPAR   0x39
#define ATARI_OP_FUN_LEFTPAR  0x3A
#define ATARI_OP_DIMSTR_LEFTPAR   0x3B
#define ATARI_OP_ARRAY_COMMA   0x3C

#define ATARI_OP_MIN   ATARI_OP_NUMCONST
#define ATARI_OP_MAX   ATARI_OP_ARRAY_COMMA

// --------------------------------------------------------------------------
// Functions
// --------------------------------------------------------------------------

#define ATARI_FUN_STR         0x3D
#define ATARI_FUN_CHR         0x3E
#define ATARI_FUN_USR         0x3F
#define ATARI_FUN_ASC         0x40
#define ATARI_FUN_VAL         0x41
#define ATARI_FUN_LEN         0x42
#define ATARI_FUN_ADR         0x43
#define ATARI_FUN_ATN         0x44
#define ATARI_FUN_COS         0x45
#define ATARI_FUN_PEEK        0x46
#define ATARI_FUN_SIN         0x47
#define ATARI_FUN_RND         0x48
#define ATARI_FUN_FRE         0x49
#define ATARI_FUN_EXP         0x4A
#define ATARI_FUN_LOG         0x4B
#define ATARI_FUN_CLOG        0x4C
#define ATARI_FUN_SQR         0x4D
#define ATARI_FUN_SGN         0x4E
#define ATARI_FUN_ABS         0x4F
#define ATARI_FUN_INT         0x50
#define ATARI_FUN_PADDLE      0x51
#define ATARI_FUN_STICK       0x52
#define ATARI_FUN_PTRIG       0x53
#define ATARI_FUN_STRIG       0x54

#define ATARI_FUN_MIN         ATARI_FUN_STR
#define ATARI_FUN_MAX         ATARI_FUN_STRIG

#define ATARI_TOKEN_MIN   ATARI_OP_NUMCONST
#define ATARI_TOKEN_MAX   ATARI_OP_ARRAY_COMMA

// --------------------------------------------------------------------------
// The EOL character
// --------------------------------------------------------------------------

#define ATARI_EOL              0x9B

// --------------------------------------------------------------------------
// Atari Errors
// --------------------------------------------------------------------------

#define ATARI_NOERROR  0x00
#define ATARI_EOF      0x01
#define ATARI_BADTOKEN 0x02

// --------------------------------------------------------------------------
// Variable types
//
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

#define ATARI_VAR_SCALAR       0x00

#define ATARI_VAR_ARRAY_UNDIM 0x40	// Undimensioned
#define ATARI_VAR_ARRAY_DIM   0x41	// Dimensioned

#define ATARI_VAR_STRING_DIM   0x81	// Undimensioned
#define ATARI_VAR_STRING_UNDIM 0x80	// Dimensioned

// --------------------------------------------------------------------------
// Some useful macros to determine the type of token
// --------------------------------------------------------------------------

#define ATARI_COMMAND(OP ) \
        ( ( (OP >= ATARI_CMD_MIN ) && ( (OP) <= ATARI_CMD_MAX) )

#define ATARI_OPERATOR(OP ) \
        ( ( (OP) >= ATARI_OP_MIN ) && ( (OP) <= ATARI_OP_MAX) )

#define ATARI_FUNCTION(OP ) \
        ( ( (OP) >= ATARI_FUN_MIN ) && ( (OP) <= ATARI_FUN_MAX) ) 

#define ATARI_FUNCTION_OR_OPERATOR(OP)  \
        ( ((OP)>=ATARI_OP_MIN) && ((OP)<=ATARI_FUN_MAX))

#endif	/* _ATARI_TOKENS_H_ */

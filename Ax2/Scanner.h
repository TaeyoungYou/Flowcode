/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2025
* Author: Taeyoung You, Juhyeon Oh
* Professors: Paulo Sousa
************************************************************
#
#
# *  ####### ####      #####   ##   ##    ####    #####   #####    #######  *
# *   ##   #  ##      ### ###  ##   ##   ##  ##  ### ###   ## ##    ##   #  *
# *   ##      ##      ##   ##  ##   ##  ##       ##   ##   ##  ##   ##      *
# *   ####    ##      ##   ##  ## # ##  ##       ##   ##   ##  ##   ####    *
# *   ##      ##      ##   ##  #######  ##       ##   ##   ##  ##   ##      *
# *   ##      ##  ##  ### ###  ### ###   ##  ##  ### ###   ## ##    ##   #  *
# *  ####    #######   #####   ##   ##    ####    #####   #####    #######  *
#
*/

/*
************************************************************
* File name: Scanner.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 Compilers, Lab Section: [303]
* Assignment: A22
* Date: March 09, 2025
* Purpose: This file is the main header for Scanner (.h)
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */

#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define the number of tokens */
#define NUM_TOKENS 51

enum TOKENS {
	/* basic token */
	Error,				/* 0: Error token */
	RunTimeError,
	EndOfToken,			/* 1: End of token */

	/* literal */
	IntLiteral,			/* 2: Integer literal */
	DoubleLiteral,		/* 3: Double literal */
	StringLiteral,		/* 4: String literal */
	BooleanLiteral,		/* 5: Boolean literal */

	/* identifier */
	VariableIdentifier, /* 6: Variable identifier */
	ConstantIdentifier,	/* 7: Constant identifier */
	MethodIdentifier,	/* 8: Method identifier */

	/* operators */
	/* assign operator */
	Assignment,			/* 18: '=' */

	/* delimeter */
	LeftParen,			/* 25: '(' */
	RightParen,			/* 26: ')' */
	LeftBrace,
	RightBrace,
	Colon,				/* 27: ':' */
	SemiColon,			/* 28: ';' */
	Comma,				/* 29: ',' */

	/* keyword */
	/* control keyword */
	If,					/* 30: if keyword */
	Elif,				/* 31: elif keyword */
	Else,				/* 32: else keyword */
	Then,				/* 33: then keyword */
	EndIf,				/* 34: endif keyword */
	/* iteration keyword */
	Repeat,				/* 35: repeat keyword */
	Check,				/* 36: check keyword */
	Break,				/* 37: break keyword */
	Continue,			/* 38: continue keyword */
	/* I/O keyword */
	Input,				/* 39: Input keyword */
	Output,				/* 40: Output keyword */
	/* function keyword */
	Return,				/* 41: return keyword */
	End,				/* 42: end keyword in function, declaration, begin */
	/* data type keyword*/
	Int,				/* 43: int keyword */
	Double,				/* 44: double keyword */
	String,				/* 45: string keyword */
	Boolean,			/* 46: bool keyword */
	Void,				/* 47: void keyword */
	/* other keyword */
	Begin,				/* 48: begin keyword */
	Declaration,		/* 49: declaration keyword */
	/* comment */
	Comment,			/* 50: '**' */
	/* End Of Line */
	EndOfLine,			/* 51: '\n */
};

/* TO_DO: Define the list of keywords */
static flowcode_string tokenStrTable[NUM_TOKENS] = {
	/* basic token */
	"Error",
	"RunTimeError",
	"EndOfToken",

	/* literal */
	"IntLiteral",
	"DoubleLiteral",
	"StringLiteral",
	"BooleanLiteral",

	/* identifier */
	"VariableIdentifier",
	"ConstantIdentifier",
	"MethodIdentifier",

	/* operators */
	/* assign operator */
	"Assignment",
	/* compare operator */
	"Equal",
	"NotEqual",
	"LessThan",
	"GreaterThan",
	"LessOrEqual",
	"GreaterOrEqual",

	/* delimeter */
	"LeftParen",
	"RightParen",
	"LeftBrace",
	"RightBrace",
	"Colon",
	"SemiColon",
	"Comma",

	/* keyword */
	/* logical operator */
	"LogicalAnd",
	"LogicalOr",
	"LogicalNot",
	/* control keyword */
	"If",
	"Elif",
	"Else",
	"Then",
	"EndIf",
	/* iteration keyword */
	"Repeat",
	"Check",
	"Break",
	"Continue",
	/* I/O keyword */
	"Input",
	"Output",
	/* function keyword */
	"Return",
	"End",
	/* data type keyword*/
	"Int",
	"Double",
	"String",
	"Boolean",
	"Void",
	/* other keyword */
	"Begin",
	"Declaration",
	/* comment */
	"Comment",
	/* End Of Line */
	"EndOfLine",
};

/* basic arithmetic operator */
typedef enum ArithmeticOperators { 
	Add,				/* 0: '+' */
	Subtract,			/* 1: '-' */
	Multiply,			/* 2: '*' */
	Divide,				/* 3: '/' */
	Modulo,				/* 4: '%' */
	Power,				/* 5: '^' */
} AriOperator;
/* comparsion operator */
typedef enum RelationalOperators { 
	Equal,				/* 0: '==' */
	NotEqual,			/* 1: '!=' */
	LessThan,			/* 2: '<' */
	GreaterThan,		/* 3: '>' */
	LessOrEqual,		/* 4: '<=' */
	GreaterOrEqual,		/* 5: '>=' */
} RelOperator;
/* logical operator */
typedef enum LogicalOperators {
	LogicalAnd,			/* 0: 'and' */
	LogicalOr,			/* 1: 'or' */
	LogicalNot,			/* 2: 'not' */
} LogOperator;

typedef enum SourceEndOfFile { 
	SEOF_0, 
	SEOF_255 
} EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	flowcode_int codeType;				/* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	flowcode_int intValue;				/* integer literal attribute (value) */
	flowcode_int keywordIndex;			/* keyword index in the keyword table */
	flowcode_int contentString;			/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	flowcode_float floatValue;				/* floating-point literal attribute (value) */
	flowcode_char idLexeme[VID_LEN + 1];	/* variable identifier token attribute */
	flowcode_char errLexeme[ERR_LEN + 1];	/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	flowcode_byte flags;			/* Flags information */
	union {
		flowcode_int intValue;				/* Integer value */
		flowcode_float floatValue;			/* Float value */
		flowcode_string stringContent;		/* String value */
		flowcode_bool boolValue;			/* Boolean value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	flowcode_int code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

/* Scanner */
typedef struct scannerData {
	flowcode_int scanHistogram[NUM_TOKENS];	/* Statistics of chars */
} ScannerData, * pScanData;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* lexeme classes */
// 무시할 공백 정의
#define SPACE			' '		// ' '
#define TAB				'\t'	// \t
// 특수 문자 정의
#define METHOD_START	':'		// : /* (optional)근데 우리 method에 ()도 들어가는데 그걸로는 판단 못하나여? */
#define METHOD_END		';'		// ;
#define END_OF_LINE		'\n'	// \n
#define ADD				'+'		// +
#define SUBTRACT		'-'		// -
#define DIVIDE			'/'		// /
#define MODULUS			'%'		// %
#define POWER			'^'		// ^
#define COMMA			','		// ,
#define PAREN_OP		'('		// (
#define PAREN_CL		')'		// )
#define BRACE_OP		'{'		// {
#define BRACE_CL		'}'		// }
#define EOS				'\0'	// End of source
#define EOF				0xFF	// End of File
// TT 정의
#define UNDERSCORE		'_'		// _
#define DOT				'.'		// .
#define ASTER			'*'		// *
#define ASSIGN			'='		// =
#define NOT				'!'		// !
#define	LESS			'<'		// >
#define GREATER			'>'		// <
#define STR_LI			'\''	// '
#define STR_CON			'\"'	// "
#define CAL_VAR			'$'		// $

#define LETTER 			0		// a-z,A-Z
#define NUMBER			1		// 0-9

/*  Special case tokens processed separately one by one in the token-driven part of the scanner:
 *  LPR_T, RPR_T, LBR_T, RBR_T, EOS_T, SEOF_T and special chars used for tokenis include _, & and ' */


/* TO_DO: Error states and illegal state */
#define ESNR	31		/* Error state with no retract */
#define ESWR	32		/* Error state with retract */
#define FS		24		/* Illegal state */

 /* TO_DO: State transition table definition */
#define NUM_STATES		28
#define CHAR_CLASSES	17

/* TO_DO: Transition table - type of states defined in separate table */
// 테이블 작성 필요!
static flowcode_int transitionTable[NUM_STATES][CHAR_CLASSES] = {
	/* State  | L(A-Z) | N(0-9) | U(_) | DOT(.)| MUL(*) | ASSIGN(=) | NOT(!) | LT(<) | GT(>) | SQUOTE(') | DQUOTE(") | STRC($) | OTHER | */
	/* S0  */ {    1,        1,     1,    ESNR,     ESNR,      ESNR,   ESNR,     ESNR,   ESNR,     10,         12,        ESNR,   ESNR }, /* NOFS(Initial State) */
	/* S1  */ {    1,        3,     3,       2,        2,         2,      2,       2,       2,      2,          2,           2,     2  }, /* NOFS */
	/* S2  */ {   FS,       FS,    FS,      FS,       FS,        FS,     FS,      FS,      FS,     FS,         FS,          FS,     FS }, /* FSWR(KEY) */
	/* S3  */ {    3,        3,     3,       4,        4,         4,      4,       4,       4,      4,          4,           4,     4  }, /* NOFS */
	/* S4  */ {   FS,       FS,    FS,      FS,       FS,        FS,     FS,      FS,      FS,     FS,         FS,          FS,     FS }, /* FSWR(ID) */
	/* S5  */ {    6,        5,     6,       7,        6,         6,      6,       6,       6,      6,          6,           6,     6  }, /* NOFS */
	/* S6  */ {   FS,       FS,    FS,      FS,       FS,        FS,     FS,      FS,      FS,     FS,         FS,          FS,     FS }, /* FSWR(INTEGER) */
	/* S7  */ { ESNR,        8,  ESNR,    ESNR,     ESNR,      ESNR,   ESNR,     ESNR,   ESNR,   ESNR,       ESNR,        ESNR,   ESNR }, /* NOFS */
	/* S8  */ {    9,        8,     9,       9,        9,         9,      9,       9,       9,      9,          9,           9,     9  }, /* NOFS */
	/* S9  */ {   FS,       FS,    FS,      FS,       FS,        FS,     FS,      FS,      FS,     FS,         FS,          FS,     FS }, /* FSWR(DOUBLE) */
	/* S10 */ {   10,       10,    10,      10,       10,        10,     10,      10,      10,     11,         10,          10,    10  }, /* NOFS */
	/* S11 */ {   FS,       FS,    FS,      FS,       FS,        FS,     FS,      FS,      FS,     FS,         FS,          FS,     FS }, /* FSWR(STRING LITERAL) */
	/* S12 */ {   12,       12,    12,      12,       12,        12,     12,      12,      12,     12,         13,          12,    12  }, /* NOFS */
	/* S13 */ {   FS,       FS,    FS,      FS,       FS,        FS,     FS,      FS,      FS,     FS,         FS,          FS,     FS }, /* FSWR(STRING CONCAN) */
	/* S14 */ {   15,       15,    15,      15,       16,        15,     15,      15,      15,     15,         15,          15,    15  }, /* NOFS */
	/* S15 */ {   FS,       FS,    FS,      FS,       FS,        FS,     FS,      FS,      FS,     FS,         FS,          FS,     FS }, /* FSWR(MULTIPLY) */
	/* S16 */ {   FS,       FS,    FS,      FS,       FS,        FS,     FS,      FS,      FS,     FS,         FS,          FS,     FS }, /* FSWR(COMMENT) */
	/* S17 */ {   19,       19,    19,      19,       19,        18,     19,      19,      19,     19,         19,          19,    19  }, /* NOFS */
	/* S18 */ {   FS,       FS,    FS,      FS,       FS,        FS,     FS,      FS,      FS,     FS,         FS,          FS,     FS }, /* FSWR(GE) */
	/* S19 */ {   FS,       FS,    FS,      FS,       FS,        FS,     FS,      FS,      FS,     FS,         FS,          FS,     FS }, /* FSWR(GREATER) */
	/* S20 */ {   22,       22,    22,      22,       22,        21,     22,      22,      22,     22,         22,          22,    22  }, /* NOFS */
	/* S21 */ {   FS,       FS,    FS,      FS,       FS,        FS,     FS,      FS,      FS,     FS,         FS,          FS,     FS }, /* FSWR(LE) */
	/* S22 */ {   FS,       FS,    FS,      FS,       FS,        FS,     FS,      FS,      FS,     FS,         FS,          FS,     FS }, /* FSWR(LESS) */
	/* S23 */ {   25,       25,    25,      25,       25,        24,     25,      25,      25,     25,         25,          25,    25  }, /* NOFS */
	/* S24 */ {   FS,       FS,    FS,      FS,       FS,        FS,     FS,      FS,      FS,     FS,         FS,          FS,     FS }, /* FSWR(EQUAL) */
	/* S25 */ {   FS,       FS,    FS,      FS,       FS,        FS,     FS,      FS,      FS,     FS,         FS,          FS,     FS }, /* FSWR(ASSIGNMENT) */
	/* S26 */ { ESNR,     ESNR,  ESNR,    ESNR,     ESNR,        27,   ESNR,     ESNR,   ESNR,   ESNR,       ESNR,        ESNR,   ESNR }, /* NOFS */
	/* S27 */ {   FS,       FS,    FS,      FS,       FS,        FS,     FS,      FS,      FS,     FS,         FS,          FS,     FS }, /* FSWR(NOT) */
};

/* Define accepting states types */
#define NOFS	0		/* Not Final State */
#define FSNR	1		/* Final State No Retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static flowcode_int stateType[NUM_STATES] = {
	NOFS, /* 00 */
	NOFS, /* 01 */
	FSWR, /* 02 (KEY) */
	NOFS, /* 03 */
	FSWR, /* 04 (IDENTIFIER) */
	NOFS, /* 05 */
	FSWR, /* 06 (INTEGER) */
	NOFS, /* 07 */
	NOFS, /* 08 */
	FSWR, /* 09 (DOUBLE) */
	NOFS, /* 10 */
	FSNR, /* 11 (STRING LITERAL) */
	NOFS, /* 12 */
	FSNR, /* 13 (STRING CONCANTENATE */
	NOFS, /* 14 */
	FSWR, /* 15 (MULTIPLY) */
	FSNR, /* 16 (COMMENT) */
	NOFS, /* 17 */
	FSNR, /* 18 (GREATER THAN EQUAL) */
	FSWR, /* 19 (GREATER) */
	NOFS, /* 20 */
	FSNR, /* 21 (LESS THAN EQUAL) */
	FSWR, /* 22 (LESS) */
	NOFS, /* 23 */
	FSNR, /* 24 (EUQAL) */
	FSWR, /* 25 (ASSIGNMENT) */
	NOFS, /* 26 */
	FSNR /* 27 (NOT) */

};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
flowcode_int			startScanner(BufferPointer psc_buf);
static flowcode_int		nextClass(flowcode_char c);					/* character class function */
static flowcode_int		nextState(flowcode_int, flowcode_char);		/* state machine function */
flowcode_void			printScannerData(ScannerData scData);
Token					tokenizer(flowcode_void);

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(flowcode_string lexeme);

/* Declare accepting states functions */
Token funcSL	(flowcode_string lexeme);
Token funcIL	(flowcode_string lexeme);
Token funcIdentifier	(flowcode_string lexeme);
Token funcComment   (flowcode_string lexeme);
Token funcKEY	(flowcode_string lexeme);
Token funcErr	(flowcode_string lexeme);

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[NUM_STATES] = {
	NULL,		/* -    [00] */
	NULL,		/* -    [01] */
	funcIdentifier,		/* MNID	[02] */
	funcKEY,	/* KEY  [03] */
	NULL,		/* -    [04] */
	funcSL,		/* SL   [05] */
	NULL,		/* -    [06] */
	funcComment,	/* COM  [07] */
	funcErr,	/* ERR1 [06] */
	funcErr		/* ERR2 [07] */
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 11

/* TO_DO: Define the list of keywords */
static flowcode_string keywordTable[KWT_SIZE] = {
	"data",		/* KW00 */
	"code",		/* KW01 */
	"int",		/* KW02 */
	"real",		/* KW03 */
	"string",	/* KW04 */
	"if",		/* KW05 */
	"then",		/* KW06 */
	"else",		/* KW07 */
	"while",	/* KW08 */
	"do",		/* KW09 */
	"return"	/* KW10 */
};

/* NEW SECTION: About indentation */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT TAB_CHR  /* Tabulation */

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	flowcode_char indentationCharType;
	flowcode_int indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

/* Number of errors */
flowcode_int numScannerErrors;

/* Scanner data */
ScannerData scData;

#endif

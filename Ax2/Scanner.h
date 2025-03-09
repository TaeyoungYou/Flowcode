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
	/* basic operator */
	Add,				/* 9:  '+' */
	Subtract,			/* 10: '-' */
	Multiply,			/* 11: '*' */
	Divide,				/* 12: '/' */
	Modulo,				/* 13: '%' */
	Power,				/* 14: '^' */
	/* logical operator */
	LogicalAnd,			/* 15: 'and' */
	LogicalOr,			/* 16: 'or' */
	LogicalNot,			/* 17: 'not' */
	/* assign operator */
	Assignment,			/* 18: '=' */
	/* compare operator */
	Equal,				/* 19: '==' */
	NotEqual,			/* 20: '!=' */
	LessThan,			/* 21: '<' */
	GreaterThan,		/* 22: '>' */
	LessOrEqual,		/* 23: '<=' */
	GreaterOrEqual,		/* 24: '>=' */

	/* delimeter */
	LeftParen,			/* 25: '(' */
	RightParen,			/* 26: ')' */
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
};

/* TO_DO: Define the list of keywords */
static flowcode_string tokenStrTable[NUM_TOKENS] = {
	"Error",
	"EndOfToken",
	"IntLiteral",
	"DoubleLiteral",
	"StringLiteral",
	"BooleanLiteral",
	"VariableIdentifier",
	"ConstantIdentifier",
	"MethodIdentifier",
	"Assignment",
	"LeftParen",
	"RightParen",
	"Colon",
	"SemiColon",
	"Comma",
	"If",
	"Elif",
	"Else",
	"Then",
	"EndIf",
	"Repeat",
	"Check",
	"Break",
	"Continue",
	"Input",
	"Output",
	"Return",
	"End",
	"Int",
	"Double",
	"String",
	"Boolean",
	"Void",
	"Begin",
	"Declaration",
	"Add",
	"Subtract",
	"Multiply",
	"Divide",
	"Modulo",
	"Power",
	"Equal",
	"NotEqual",
	"LessThan",
	"GreaterThan",
	"LessOrEqual",
	"GreaterOrEqual",
	"LogicalAnd",
	"LogicalOr",
	"LogicalNot",
	"Comment",
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
// 이부분이 메인! 필수로 고쳐야함 - int > char
#define LETTER 			0		// a-z,A-Z
#define NUMBER			1		// 0-9
#define UNDERSCORE		2		// _
#define METHOD_START	3		// : /* (optional)근데 우리 method에 ()도 들어가는데 그걸로는 판단 못하나여? */
#define SPACE			4		// ' ' OR \t 
#define POSITIVE		5		// +
#define NEGATIVE		6		// -
#define DIVIDE			7		// /
#define MODULUS			8		// %
#define POWER			9		// ^
#define COMMA			10		// ,
#define ASSIGN			11		// =
#define NOT				12		// !
#define	LESS			13		// >
#define GREATER			14		// <
#define END_LINE		15		// \n
#define BRACKET_OP		16		// (
#define BRACKET_CL		17		// )
#define CURLYBRA_OP		18		// {
#define CURLYBRA_CL		19		// }
#define STR_LI			20		// '
#define STR_CON			21		// "
#define ASTER			22		// *
#define DEC_P			23		// .
#define CAL_VAR			24		// $

#define EOS				'\0'	// End of source
#define EOF				0xFF	// End of File

/*  Special case tokens processed separately one by one in the token-driven part of the scanner:
 *  LPR_T, RPR_T, LBR_T, RBR_T, EOS_T, SEOF_T and special chars used for tokenis include _, & and ' */


/* TO_DO: Error states and illegal state */
#define ESNR	31		/* Error state with no retract */
#define ESWR	32		/* Error state with retract */
#define FS		33		/* Illegal state */

 /* TO_DO: State transition table definition */
#define NUM_STATES		12
#define CHAR_CLASSES	17

/* TO_DO: Transition table - type of states defined in separate table */
// 테이블 작성 필요!
static flowcode_int transitionTable[NUM_STATES][CHAR_CLASSES] = {
	/* State  | L(A-Z) | N(0-9) | U(_) | DOT(.) | ADD(+) | SUB(-) | MUL(*) | DIV(/) | MOD(%) | POW(^) | ASSIGN(=) | NOT(!) | LT(<) | GT(>) | SQUOTE(') | DQUOTE(") | STRC($) | COLON(:) | SEMI(;) | COMMA(,) | POPEN(() | PCLOSE()) | COPEN({) | CCLOSE(}) | OTHER | */
	/* S0  */  { 1, 6, 1, ES, ES, ES, 20, ES, ES, ES, ES, ES, ES, ES, 15, 17, ES, ES, ES, ES, 4, ES, OPERATOR_ORDER, ES, ES }, /* NOFS (INITIAL STATE) */
	/* S1  */  { FS, FS, FS, ES, ES, ES, ES, ES, ES, ES, 2, 5, ES, ES, ES, ES, ES, ES, ES, ES, 4, ES, ES, ES, ES }, /* FSNR (VARIABLE_ID) */
	/* S2  */  { FS, FS, FS, ES, ES, ES, ES, ES, ES, ES, 3, ES, ES, ES, FS, FS, ES, ES, ES, ES, OPERATOR_ORDER, ES, OPERATOR_ORDER, ES, ES }, /* FSNR (ASSIGNMENT) */
	/* S3  */  { FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS }, /* FSWR (EQUAL) */
	/* S4  */  { FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS }, /* FSNR (METHOD_ID) */
	/* S5  */  { ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, 6, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES }, /* NOFS */
	/* S6  */  { FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS }, /* FSNR (NOT OPERATOR) */
	/* S7  */  { ES, 8, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, OPERATOR_ORDER, ES, OPERATOR_ORDER, ES, ES }, /* NOFS */
	/* S8  */  { ES, FS, ES, 9, ES, ES, ES, ES, ES, ES, 2, 5, 11, 13, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES }, /* FSNR (INTEGER) */
	/* S9  */  { ES, 10, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES }, /* NOFS */
	/* S10 */  { ES, FS, ES, ES, ES, ES, ES, ES, ES, ES, 2, 5, 11, 13, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES }, /* FSNR (FLOAT NUMBER) */
	/* S11 */  { ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, 12, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES }, /* FSNR (LESS THAN) */
	/* S12 */  { FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS }, /* FSWR (LESS THAN OR EQUAL) */
	/* S13 */  { ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, 14, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES }, /* FSNR (GREATER THAN) */
	/* S14 */  { FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS }, /* FSWR (GREATER THAN OR EQUAL) */
	/* S15 */  { 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 16, 15, 15, 15, 15, 15, 15, 15, 15, 15 }, /* NOFS */
	/* S16 */  { FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS }, /* FSNR (STRING LITERAL) */
	/* S17 */  { 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 19, 17, 17, 17, 17, 17, 17, 17 }, /* NOFS */
	/* S18 */  { FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS }, /* FSNR (STRING CONCAT) */
	/* S19 */  { 1, ES, 1, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, 18, ES, ES, ES, ES, ES, ES, ES, ES, ES }, /* NOFS */
	/* S20 */  { ES, 8, ES, ES, 7, 7, 21, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, FS, ES, FS, ES, ES }, /* NOFS (COMMENT START) */
	/* S21 */  { 21, 21, 21, 21, 21, 21, 22, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21 }, /* NOFS */
	/* S22 */  { ES, ES, ES, ES, ES, ES, 23, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES, ES }, /* NOFS */
	/* S23 */  { FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS, FS }  /* FSNR (COMMENT END) */
};


/* Define accepting states types */
#define NOFS	0		/* Not Final State */
#define FSNR	1		/* Final State No Retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static flowcode_int stateType[NUM_STATES] = {
	/* TODO::*/
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
Token funcID	(flowcode_string lexeme);
Token funcCMT   (flowcode_string lexeme);
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
	funcID,		/* MNID	[02] */
	funcKEY,	/* KEY  [03] */
	NULL,		/* -    [04] */
	funcSL,		/* SL   [05] */
	NULL,		/* -    [06] */
	funcCMT,	/* COM  [07] */
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

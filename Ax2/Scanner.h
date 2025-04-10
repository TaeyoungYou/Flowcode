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
#define NUM_LEN 17   /* maximum number of digits for IL */

#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define the number of tokens */
#define BASE_TOKEN_LEN 54

enum TOKENS {
	/* ========== Basic Tokens ========== */
	Error,              /*  0: Error token (used when an error occurs) */
	RunTimeError,       /*  1: Used when a runtime error occurs */
	EndOfToken,         /*  2: End of token (end of file) */

	/* ========== Literal ========== */
	IntLiteral,         /*  3: Integer literal */
	DoubleLiteral,      /*  4: Double literal */
	StringLiteral,      /*  5: String literal */

	/* ========== Identifier ========== */
	Identifier,         /*  6: Identifier (Variable, function name, constant, etc.) */


	/* ========== Delimiters ========== */
	LeftParen,          /*  8: '(' (left bracket) */
	RightParen,         /*  9: ')' (right bracket) */
	LeftBrace,          /* 10: '{' (left curly brace) */
	RightBrace,         /* 11: '}' (right curly brace) */
	Colon,              /* 12: ':' (colon) */
	SemiColon,          /* 13: ';' (semicolon) */
	Comma,              /* 14: ',' (comma) */
	Dot,

	/* ========== Comment ========== */
	Comment,            /* 15: '** ... **' */

	/* ========== End of Line ========== */
	EndOfLine,          /* 16: '\n' (newline) */

	/* ========== Arithmetic Operators ========== */
	Add,                /* 17: '+' (addition operator) */
	Subtract,           /* 18: '-' (subtraction operator) */
	Multiply,           /* 19: '*' (multiplication operator) */
	Divide,             /* 20: '/' (division operator) */
	Modulo,             /* 21: '%' (modulo operator) */
	Power,              /* 22: '^' (Exponentiation operator) */

	/* ========== Comparison Operators ========== */
	/* ========== Operators ========== */
	/* 할당 연산자 (Assignment Operator) */
	Assignment,         /*  7: '=' (assignment operator) */
	Equal,              /* 23: '==' (equality) */
	NotEqual,           /* 24: '!=' (inequality) */
	LessThan,           /* 25: '<' (less than) */
	GreaterThan,        /* 26: '>' (greater than) */
	LessOrEqual,        /* 27: '<=' (less than or equal) */
	GreaterOrEqual,     /* 28: '>=' (greater than or equal) */

	/* ========== Keywords ========== */
	/* Logical Operators */
	LogicalAnd,         /* 29: 'and' (logical AND) */
	LogicalOr,          /* 30: 'or' (logical OR) */
	LogicalNot,         /* 31: 'not' (logical NOT) */

	/* Control Keywords */
	If,                 /* 32: 'if' (conditional statement) */
	Elif,               /* 33: 'elif' (else if condition) */
	Else,               /* 34: 'else' (defualt condition) */
	Then,               /* 35: 'then' (execution statement) */
	EndIf,              /* 36: 'endif' (end of conditional statement) */

	/* Iteration Keywords */
	Repeat,             /* 37: 'repeat' (loop statement) */
	Check,              /* 38: 'check' (loop check condition) */
	Break,              /* 39: 'break' (exit loop) */
	Continue,           /* 40: 'continue' (proceed to next iteration) */

	/* I/O Keywords */
	Input,              /* 41: 'Input' (input function) */
	Output,             /* 42: 'Output' (output function) */

	/* Function Keywords */
	Return,             /* 43: 'return' (function return) */
	End,                /* 44: 'end' (end of function or declaration) */

	/* Data Type Keywords */
	Int,                /* 45: 'int' (integer type) */
	Double,             /* 46: 'double' (floating-point type) */
	String,             /* 47: 'string' (string literal) */
	Boolean,            /* 48: 'bool' (boolean type) */
	Void,               /* 49: 'void' (no return value) */

	/* Other Keywords */
	Begin,              /* 50: 'begin' (start of a code block) */
	Declaration,        /* 51: 'declaration' (variable declaration) */
	Constant,           /* 52: 'constant' (constant declaration) */
	/* True ::TODO - true keyword */
	/* False ::TODO - false keyword */
	/* Void ::TODO - void keyword */
	/* Main ::TODO - Main function keyword */

	StringDoubleQuoteLiteral, /* String literal enclosed in double quotes */
};


static flowcode_string tokenStrTable[BASE_TOKEN_LEN] = {
	/* basic token */
	"Error",
	"RunTimeError",
	"EndOfToken",

	/* literal */
	"IntLiteral",
	"DoubleLiteral",
	"StringLiteral",

	/* identifier */
	"Identifier",

	/* operators */
	/* delimeter */
	"LeftParen",
	"RightParen",
	"LeftBrace",
	"RightBrace",
	"Colon",
	"SemiColon",
	"Comma",
	"Dot",
	/* comment */
	"Comment",
	/* End Of Line */
	"EndOfLine",

	"Add",
	"Subtract",
	"Multiply",
	"Divide",
	"Modulo",
	"Power",

	/* assign operator */
	"Assignment",
	"Equal",
	"NotEqual",
	"LessThan",
	"GreaterThan",
	"LessOrEqual",
	"GreaterOrEqual",

	"LogicalAnd",     // 0: 'and'
	"LogicalOr",      // 1: 'or'
	"LogicalNot",     // 2: 'not'
	/* control keyword */
	"If",            // 30: if keyword
	"Elif",          // 31: elif keyword
	"Else",          // 32: else keyword
	"Then",          // 33: then keyword
	"EndIf",         // 34: endif keyword
	/* iteration keyword */
	"Repeat",        // 35: repeat keyword
	"Check",         // 36: check keyword
	"Break",         // 37: break keyword
	"Continue",      // 38: continue keyword
	/* I/O keyword */
	"Input",         // 39: Input keyword
	"Output",        // 40: Output keyword
	/* function keyword */
	"Return",        // 41: return keyword
	"End",           // 42: end keyword (used in function, declaration, begin)
	/* data type keyword */
	"Int",           // 43: int keyword
	"Double",        // 44: double keyword
	"String",        // 45: string keyword
	"Boolean",       // 46: boolean keyword
	"Void",          // 47: void keyword
	/* other keyword */
	"Begin",         // 48: begin keyword
	"Declaration",   // 49: declaration keyword
	"Constant"       // 50: constant keyword

	"StringDoubleQuoteLiteral",
};

typedef enum SourceEndOfFile {
	SEOF_0,
	SEOF_255
} EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	flowcode_int codeType;				/* integer attributes accessor */
	EofOperator seofType;				/* source-end-of-file attribute code */
	flowcode_int intValue;				/* integer literal attribute (value) */
	flowcode_double doubleValue;		/* double literal attribute (value) */
	flowcode_int keywordIndex;			/* keyword index in the keyword table */
	flowcode_int contentString;			/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	flowcode_float floatValue;				/* floating-point literal attribute (value) */
	flowcode_string comment_content;
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
	flowcode_int scanHistogram[BASE_TOKEN_LEN];	/* Statistics of chars */
} ScannerData, * pScanData;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* lexeme classes */
// Define whitespace characters to be ignored
#define SPACE			' '		// ' '
#define TAB				'\t'	// \t
// Special Chars to be ignored
#define METHOD_START	':'		// :
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
#define EOF_T			0xFF	// End of File
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

/*  Special case tokens processed separately one by one in the token-driven part of the scanner:
 *  LPR_T, RPR_T, LBR_T, RBR_T, EOS_T, SEOF_T and special chars used for tokenis include _, & and ' */


 /* TO_DO: Error states and illegal state */
#define ESNR	50		/* Error state with no retract */
#define ESWR	51		/* Error state with retract */
#define FS		52		/* Illegal state */

 /* TO_DO: State transition table definition */
#define NUM_STATES		31
#define CHAR_CLASSES	17

/* TO_DO: Transition table - type of states defined in separate table */
/*
 * FLOWCODE Transition Table Criteria
 * The token determination is based solely on [ index / FS / ESNR ].
 * NSWR is not needed since states are already classified as NOFS, FSNR, or FSWR.
 *
 * Examples:
 *      intn=  -> Reads "intn" as a keyword until '=' appears, then transitions to FS and confirms it as a keyword.
 *      3..    -> Reads '3' as an integer, identifies '.' as a decimal point, but a second '.' confirms it as ESNR.
 *      3.14=  -> Syntactically incorrect (a literal should not be followed by '='), but '=' confirms '3.14' as a float
 *                and '=' as an assignment operator. Syntax validation is the parser’s responsibility.
 *      *<     -> Syntactically incorrect, but '<' confirms '*' as multiplication and '<' as the less-than operator.
 *                Syntax validation is the parser’s responsibility.
 *      *>=*<  -> Also an invalid syntax, but not ESNR because it can be split into tokens: *, >, =, *, <.
 *                Hence, it transitions to FS.
 *      "h'    -> Even if it transitions to FS, it cannot form a valid token, so it is confirmed as ESNR.
 *
 *      In summary, as long as a sequence can be split into valid tokens, it transitions to FS,
 *      but if FSWR fails to form a valid token, it is confirmed as ESNR.
 */
static flowcode_int transitionTable[NUM_STATES][CHAR_CLASSES] = {
	/* State  | L(A-Z) | N(0-9) | U(_) | DOT(.) | MUL(*) | ASSIGN(=) | NOT(!) | LT(<) | GT(>) | SQUOTE(') | DQUOTE(") | STRC($) | OTHER | */
	/* S0  */ {    6,       10,     8,    ESNR,	      1,	     16,    ESNR,     19,     22,         25,         28,     ESNR,    ESNR }, /* NOFS(Initial State) */
	/* S1  */ {   15,       15,    15,    ESNR,		  2,	     15,      15,     15,     15,         15,         15,     ESNR,      15 }, /* NOFS(First '*' detected) */
	/* S2  */ {    3,        3,     3,       3,	      4,	      3,       3,      3,      3,          3,          3,        3,       3 }, /* NOFS(Second '*' detected - Start of comment) */
	/* S3  */ {    3,        3,     3,       3,	      4,		  3,       3,      3,      3,          3,          3,        3,       3 }, /* NOFS(Comment content) */
	/* S4  */ {    3,        3,     3,       3,	      5,		  3,       3,      3,      3,          3,          3,        3,       3 }, /* NOFS(Potential end of comment detected) */
	/* S5  */ {   FS,       FS,    FS,      FS,	     FS,		 FS,      FS,     FS,     FS,         FS,         FS,       FS,      FS }, /* FSNR(End of comment detected) */
	/* S6  */ {    6,        8,     8,       7,	      7,		  7,       7,      7,      7,          7,          7,        7,       7 }, /* NOFS(Keyword/Identifier detected - Treating as Keyword) */
	/* S7  */ {   FS,       FS,    FS,      FS,	     FS,		 FS,      FS,     FS,     FS,         FS,         FS,       FS,      FS }, /* FSNR(End of Keyword detected) */
	/* S8  */ {    8,        8,     8,       9,	      9,		  9,       9,      9,      9,          9,          9,        9,       9 }, /* NOFS(Identifier detected) */
	/* S9  */ {   FS,       FS,    FS,      FS,	     FS,		 FS,      FS,     FS,     FS,         FS,         FS,       FS,      FS }, /* FSWR(End of Identifier detected) */
	/* S10 */ {   11,       10,    11,      12,	     11,		 11,      11,     11,     11,         11,         11,       11,      11 }, /* NOFS(Number (Integer/Float) detected) */
	/* S11 */ {   FS,       FS,    FS,      FS,	     FS,		 FS,      FS,     FS,     FS,         FS,         FS,       FS,      FS }, /* FSWR(End of Integer detected) */
	/* S12 */ { ESNR,       13,  ESNR,    ESNR,	   ESNR,	   ESNR,    ESNR,   ESNR,   ESNR,       ESNR,       ESNR,     ESNR,    ESNR }, /* NOFS(Decimal point detected - Possible float) */
	/* S13 */ {   14,       13,    14,      14,	     14,	     14,      14,     14,     14,         14,         14,       14,      14 }, /* NOFS(Fractional part of float detected) */
	/* S14 */ {   FS,       FS,    FS,      FS,	     FS,		 FS,      FS,     FS,     FS,         FS,         FS,       FS,      FS }, /* FSWR(End of Float detected) */
	/* S15 */ {   FS,       FS,    FS,      FS,	     FS,		 FS,      FS,     FS,     FS,         FS,         FS,       FS,      FS }, /* FSWR(End of Multiplication detected) */
	/* S16 */ {   17,       17,    17,      17,	     17,		 18,      17,     -1,     -1,         17,         17,       17,      17 }, /* NOFS(First '=' detected - Possible comparison operator) */
	/* S17 */ {   FS,       FS,    FS,      FS,	     FS,		 FS,      FS,     FS,     FS,         FS,         FS,       FS,      FS }, /* FSWR(End of '=' operator detected */
	/* S18 */ {   FS,       FS,    FS,      FS,	     FS,		 FS,      FS,     FS,     FS,         FS,         FS,       FS,      FS }, /* FSNR(Second '=' detected - End of '==' operator) */
	/* S19 */ {   20,       20,    20,      20,	     20,		 21,      20,     20,     20,         20,         20,       20,      20 }, /* NOFS(First '<' detected) */
	/* S20 */ {   FS,       FS,    FS,      FS,	     FS,		 FS,      FS,     FS,     FS,         FS,         FS,       FS,      FS }, /* FSWR(End of '<' operator detected) */
	/* S21 */ {   FS,       FS,    FS,      FS,	     FS,		 FS,      FS,     FS,     FS,         FS,         FS,       FS,      FS }, /* FSNR(Second '=' detected - End of '<=' operator) */
	/* S22 */ {   23,       23,    23,      23,	     23,		 24,      23,     23,     23,         23,         23,       23,      23 }, /* NOFS(First '>' detected) */
	/* S23 */ {   FS,       FS,    FS,      FS,	     FS,		 FS,      FS,     FS,     FS,         FS,         FS,       FS,      FS }, /* FSWR(End of '>' operator detected) */
	/* S24 */ {   FS,       FS,    FS,      FS,	     FS,		 FS,      FS,     FS,     FS,         FS,         FS,       FS,      FS }, /* FSNR(Second '=' detected - End of '>=' operator) */
	/* S25 */ {   26,       26,    26,      26,	     26,		 26,      26,     26,     26,         27,         26,       26,      26 }, /* NOFS(First single quote detected) */
	/* S26 */ {   26,       26,    26,      26,	     26,		 26,      26,     26,     26,         27,         26,       26,      26 }, /* NOFS(Single quote content) */
	/* S27 */ {   FS,       FS,    FS,      FS,	     FS,		 FS,      FS,     FS,     FS,         FS,         FS,       FS,      FS }, /* FSNR(Second single quote detected - End) */
	/* S28 */ {   29,       29,    29,      29,	     29,		 29,      29,     29,     29,         29,         30,       29,      29 }, /* NOFS(First double quote detected) */
	/* S29 */ {   29,       29,    29,      29,	     29,		 29,      29,     29,     29,         29,         30,       29,      29 }, /* NOFS(Double quote content) */
	/* S30 */ {   FS,       FS,    FS,      FS,	     FS,		 FS,      FS,     FS,     FS,         FS,         FS,       FS,      FS }, /* FSNR(Second double quote detected - End) */
};

#define QUO_STATE 5
#define QUO_CLASS 5

static flowcode_int transitionTableForDoubleQuote[QUO_STATE][QUO_CLASS] = {
	/* State  | alphabet | number | U(_) |  $ | other | */
	/* S0  */ {       1,       1,     1,   2,       1 }, /* NOFS (Initial State) */
	/* S1  */ {       1,       1,     1,   2,       1 }, /* NOFS (Any string) */
	/* S2  */ {       3,    ESNR,     3,ESNR,    ESNR }, /* NOFS ($ Detect literal) */
	/* S3  */ {       3,       3,     3,ESNR,       4 }, /* NOFS ($ Identifier) */
	/* S4  */ {      FS,      FS,    FS,  FS,      FS }, /* FSWR ($ End of Identifier) */
};

#define MAX_VAL 50
static flowcode_string varsDoubleQuote[MAX_VAL] = { 0 };

/* Define accepting states types */
#define NOFS	0		/* Not Final State */
#define FSNR	1		/* Final State No Retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static flowcode_int stateType[NUM_STATES] = {
	NOFS, /* 00 */
	NOFS, /* 01 */
	NOFS,
	NOFS,
	NOFS,
	FSNR,
	NOFS,
	FSWR,
	NOFS,
	FSWR,
	NOFS,
	FSWR,
	NOFS,
	NOFS,
	FSWR,
	FSWR,
	NOFS,
	FSWR,	// 17
	FSNR,
	NOFS,
	FSWR,
	FSNR,
	NOFS,
	FSWR,
	FSNR,
	NOFS,
	NOFS,
	FSNR,
	NOFS,
	NOFS,
	FSNR,
};

static flowcode_int stateTypeForDoubleQuote[QUO_STATE] = {
	NOFS,
	NOFS,
	NOFS,
	NOFS,
	FSWR,
};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
flowcode_int			startScanner(BufferPointer psc_buf);
flowcode_int		nextClass(flowcode_char c);					/* character class function */
flowcode_int		nextState(flowcode_int, flowcode_char);		/* state machine function */
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
Token funcMultiply(flowcode_string);
Token funcComment(flowcode_string);
Token funcIntegerLiteral(flowcode_string);
Token funcDoubleLiteral(flowcode_string);
Token funcString(flowcode_string);
Token funcDoubleString(flowcode_string);
Token funcIdentifier(flowcode_string);
Token funcKeyword(flowcode_string);
Token funcRelational(flowcode_string);
Token funcErr(flowcode_string);


/*
 * Accepting function (action) callback table (array) definition
 * If you do not want to use the typedef, the equvalent declaration is:
 */

 /* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[NUM_STATES] = {
	NULL, /* 00 */
	NULL, /* 01 */
	NULL,
	NULL,
	NULL,
	funcComment,
	NULL,
	funcKeyword,
	NULL,
	funcIdentifier,
	NULL,
	funcIntegerLiteral,
	NULL,
	NULL,
	funcDoubleLiteral,
	funcMultiply,
	NULL,
	funcRelational,
	funcRelational,
	NULL,
	funcRelational,
	funcRelational,
	NULL,
	funcRelational,
	funcRelational,
	NULL,
	NULL,
	funcString,
	NULL,
	NULL,
	funcDoubleString,
};

static PTR_ACCFUN finalStateTableForDoubleQuote[QUO_STATE] = {
	NULL,
	NULL,
	NULL,
	NULL,

};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 24
#define KEYWORD_START_INDEX 30

/* TO_DO: Define the list of keywords */
static flowcode_string keywordTable[KWT_SIZE] = {
	/* Logical Operators */
	"and",      // LogicalAnd
	"or",       // LogicalOr
	"not",      // LogicalNot

	/* Control Keywords */
	"if",       // If
	"elif",     // Elif
	"else",     // Else
	"then",     // Then
	"endif",    // EndIf

	/* Iteration Keywords */
	"repeat",   // Repeat
	"check",    // Check
	"break",    // Break
	"continue", // Continue

	/* I/O Keywords */
	"Input",    // Input
	"Output",   // Output

	/* Function Keywords */
	"return",   // Return
	"end",      // End

	/* Data Type Keywords */
	"int",      // Int
	"double",   // Double
	"string",   // String
	"boolean",  // Boolean
	"void",     // Void

	/* Other Keywords */
	"begin",       // Begin
	"declaration", // Declaration
	"cons"         // Constant
};

#define REL_SIZE 7
#define REL_START_INDEX 23
static flowcode_string relationTable[REL_SIZE] = {
	"=",
	"==",
	"!=",
	"<",
	">",
	"<=",
	">=",
};

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
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
#define BASE_TOKEN_LEN 53

enum TOKENS {
	/* ========== 기본 토큰 ========== */
	Error,              /*  0: Error token (에러 발생 시 사용) */
	RunTimeError,       /*  1: 런타임 에러 발생 시 사용 */
	EndOfToken,         /*  2: End of token (파일 끝) */

	/* ========== 리터럴 (Literal) ========== */
	IntLiteral,         /*  3: Integer literal (정수 리터럴) */
	DoubleLiteral,      /*  4: Double literal (실수 리터럴) */
	StringLiteral,      /*  5: String literal (문자열 리터럴) */

	/* ========== 식별자 (Identifier) ========== */
	Identifier,         /*  6: 일반적인 식별자 (변수, 함수 이름 등) */

	/* ========== 연산자 (Operators) ========== */
	/* 할당 연산자 (Assignment Operator) */
	Assignment,         /*  7: '=' (할당 연산자) */

	/* ========== 구분자 (Delimiters) ========== */
	LeftParen,          /*  8: '(' (왼쪽 괄호) */
	RightParen,         /*  9: ')' (오른쪽 괄호) */
	LeftBrace,          /* 10: '{' (왼쪽 중괄호) */
	RightBrace,         /* 11: '}' (오른쪽 중괄호) */
	Colon,              /* 12: ':' (콜론) */
	SemiColon,          /* 13: ';' (세미콜론) */
	Comma,              /* 14: ',' (쉼표) */

	/* ========== 주석 (Comment) ========== */
	Comment,            /* 15: '** ... **' (주석) */

	/* ========== 줄 끝 (End of Line) ========== */
	EndOfLine,          /* 16: '\n' (줄 바꿈) */

	/* ========== 산술 연산자 (Arithmetic Operators) ========== */
	Add,                /* 17: '+' (덧셈 연산자) */
	Subtract,           /* 18: '-' (뺄셈 연산자) */
	Multiply,           /* 19: '*' (곱셈 연산자) */
	Divide,             /* 20: '/' (나눗셈 연산자) */
	Modulo,             /* 21: '%' (나머지 연산자) */
	Power,              /* 22: '^' (거듭제곱 연산자) */

	/* ========== 비교 연산자 (Comparison Operators) ========== */
	Equal,              /* 23: '==' (같음) */
	NotEqual,           /* 24: '!=' (다름) */
	LessThan,           /* 25: '<' (작음) */
	GreaterThan,        /* 26: '>' (큼) */
	LessOrEqual,        /* 27: '<=' (작거나 같음) */
	GreaterOrEqual,     /* 28: '>=' (크거나 같음) */

	/* ========== 키워드 (Keywords) ========== */
	/* 논리 연산자 (Logical Operators) */
	LogicalAnd,         /* 29: 'and' (논리 AND) */
	LogicalOr,          /* 30: 'or' (논리 OR) */
	LogicalNot,         /* 31: 'not' (논리 NOT) */

	/* 제어문 키워드 (Control Keywords) */
	If,                 /* 32: 'if' (조건문) */
	Elif,               /* 33: 'elif' (조건문 - else if) */
	Else,               /* 34: 'else' (조건문 - 기본) */
	Then,               /* 35: 'then' (조건문 - 실행) */
	EndIf,              /* 36: 'endif' (조건문 종료) */

	/* 반복문 키워드 (Iteration Keywords) */
	Repeat,             /* 37: 'repeat' (반복문) */
	Check,              /* 38: 'check' (반복 검사) */
	Break,              /* 39: 'break' (반복 종료) */
	Continue,           /* 40: 'continue' (다음 반복 실행) */

	/* 입출력 키워드 (I/O Keywords) */
	Input,              /* 41: 'Input' (입력) */
	Output,             /* 42: 'Output' (출력) */

	/* 함수 키워드 (Function Keywords) */
	Return,             /* 43: 'return' (함수 반환) */
	End,                /* 44: 'end' (함수 종료, 선언 종료 등) */

	/* 데이터 타입 키워드 (Data Type Keywords) */
	Int,                /* 45: 'int' (정수형) */
	Double,             /* 46: 'double' (실수형) */
	String,             /* 47: 'string' (문자열) */
	Boolean,            /* 48: 'bool' (불리언 타입) */
	Void,               /* 49: 'void' (반환값 없음) */

	/* 기타 키워드 (Other Keywords) */
	Begin,              /* 50: 'begin' (코드 블록 시작) */
	Declaration,        /* 51: 'declaration' (변수 선언) */
	Constant,           /* 52: 'constant' (상수 선언) */
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
	/* assign operator */
	"Assignment",
	/* delimeter */
	"LeftParen",
	"RightParen",
	"LeftBrace",
	"RightBrace",
	"Colon",
	"SemiColon",
	"Comma",
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
#define EOF_T				0xFF	// End of File
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
#define ESNR	28		/* Error state with no retract */
#define ESWR	29		/* Error state with retract */
#define FS		30		/* Illegal state */

 /* TO_DO: State transition table definition */
#define NUM_STATES		28
#define CHAR_CLASSES	17

/* TO_DO: Transition table - type of states defined in separate table */
// 테이블 작성 필요!
//static flowcode_int transitionTable[NUM_STATES][CHAR_CLASSES] = {
//	/* State  | L(A-Z) | N(0-9) | U(_) | DOT(.)| MUL(*) | ASSIGN(=) | NOT(!) | LT(<) | GT(>) | SQUOTE(') | DQUOTE(") | STRC($) | OTHER | */
//	/* S0  */ {    1,        1,     1,    ESNR,		  ESNR,      ESNR,   ESNR,     ESNR,   ESNR,     10,         12,        ESNR,   ESNR }, /* NOFS(Initial State) */
//	/* S1  */ {    1,        3,     3,       2,        2,         2,      2,       2,       2,      2,          2,           2,     2  }, /* NOFS */
//	/* S2  */ {   FS,       FS,    FS,      FS,       FS,        FS,     FS,      FS,      FS,     FS,         FS,          FS,     FS }, /* FSWR(KEY) */
//	/* S3  */ {    3,        3,     3,       4,        4,         4,      4,       4,       4,      4,          4,           4,     4  }, /* NOFS */
//	/* S4  */ {   FS,       FS,    FS,      FS,       FS,        FS,     FS,      FS,      FS,     FS,         FS,          FS,     FS }, /* FSWR(ID) */
//	/* S5  */ {    6,        5,     6,       7,        6,         6,      6,       6,       6,      6,          6,           6,     6  }, /* NOFS */
//	/* S6  */ {   FS,       FS,    FS,      FS,       FS,        FS,     FS,      FS,      FS,     FS,         FS,          FS,     FS }, /* FSWR(INTEGER) */
//	/* S7  */ { ESNR,        8,  ESNR,    ESNR,     ESNR,      ESNR,   ESNR,     ESNR,   ESNR,   ESNR,       ESNR,        ESNR,   ESNR }, /* NOFS */
//	/* S8  */ {    9,        8,     9,       9,        9,         9,      9,       9,       9,      9,          9,           9,     9  }, /* NOFS */
//	/* S9  */ {   FS,       FS,    FS,      FS,       FS,        FS,     FS,      FS,      FS,     FS,         FS,          FS,     FS }, /* FSWR(DOUBLE) */
//	/* S10 */ {   10,       10,    10,      10,       10,        10,     10,      10,      10,     11,         10,          10,    10  }, /* NOFS */
//	/* S11 */ {   FS,       FS,    FS,      FS,       FS,        FS,     FS,      FS,      FS,     FS,         FS,          FS,     FS }, /* FSWR(STRING LITERAL) */
//	/* S12 */ {   12,       12,    12,      12,       12,        12,     12,      12,      12,     12,         13,          12,    12  }, /* NOFS */
//	/* S13 */ {   FS,       FS,    FS,      FS,       FS,        FS,     FS,      FS,      FS,     FS,         FS,          FS,     FS }, /* FSWR(STRING CONCAN) */
//	/* S14 */ {   15,       15,    15,      15,       16,        15,     15,      15,      15,     15,         15,          15,    15  }, /* NOFS */
//	/* S15 */ {   FS,       FS,    FS,      FS,       FS,        FS,     FS,      FS,      FS,     FS,         FS,          FS,     FS }, /* FSWR(MULTIPLY) */
//	/* S16 */ {   FS,       FS,    FS,      FS,       FS,        FS,     FS,      FS,      FS,     FS,         FS,          FS,     FS }, /* FSWR(COMMENT) */
//	/* S17 */ {   19,       19,    19,      19,       19,        18,     19,      19,      19,     19,         19,          19,    19  }, /* NOFS */
//	/* S18 */ {   FS,       FS,    FS,      FS,       FS,        FS,     FS,      FS,      FS,     FS,         FS,          FS,     FS }, /* FSWR(GE) */
//	/* S19 */ {   FS,       FS,    FS,      FS,       FS,        FS,     FS,      FS,      FS,     FS,         FS,          FS,     FS }, /* FSWR(GREATER) */
//	/* S20 */ {   22,       22,    22,      22,       22,        21,     22,      22,      22,     22,         22,          22,    22  }, /* NOFS */
//	/* S21 */ {   FS,       FS,    FS,      FS,       FS,        FS,     FS,      FS,      FS,     FS,         FS,          FS,     FS }, /* FSWR(LE) */
//	/* S22 */ {   FS,       FS,    FS,      FS,       FS,        FS,     FS,      FS,      FS,     FS,         FS,          FS,     FS }, /* FSWR(LESS) */
//	/* S23 */ {   25,       25,    25,      25,       25,        24,     25,      25,      25,     25,         25,          25,    25  }, /* NOFS */
//	/* S24 */ {   FS,       FS,    FS,      FS,       FS,        FS,     FS,      FS,      FS,     FS,         FS,          FS,     FS }, /* FSWR(EQUAL) */
//	/* S25 */ {   FS,       FS,    FS,      FS,       FS,        FS,     FS,      FS,      FS,     FS,         FS,          FS,     FS }, /* FSWR(ASSIGNMENT) */
//	/* S26 */ { ESNR,     ESNR,  ESNR,    ESNR,     ESNR,        27,   ESNR,     ESNR,   ESNR,   ESNR,       ESNR,        ESNR,   ESNR }, /* NOFS */
//	/* S27 */ {   FS,       FS,    FS,      FS,       FS,        FS,     FS,      FS,      FS,     FS,         FS,          FS,     FS }, /* FSWR(NOT) */
//};
static flowcode_int transitionTable[NUM_STATES][CHAR_CLASSES] = {
	/* State  | L(A-Z) | N(0-9) | U(_) | DOT(.) | MUL(*) | ASSIGN(=) | NOT(!) | LT(<) | GT(>) | SQUOTE(') | DQUOTE(") | STRC($) | OTHER | */
	/* S0  */ {    6,       -1,     8,    ESNR,	      1,	   ESNR,    ESNR,   ESNR,   ESNR,         -1,         -1,     ESNR,    ESNR }, /* NOFS(Initial State) */
	/* S1  */ {    0,       -1,    -1,    ESNR,		  2,	   ESNR,    ESNR,   ESNR,   ESNR,       ESNR,       ESNR,     ESNR,    ESNR }, /* NOFS(첫번째 * 감지) */
	/* S2  */ {    3,        3,     3,       3,	      4,	      3,       3,      3,      3,          3,          3,        3,       3 }, /* NOFS(두번째 * 감지 - 주석 시작) */
	/* S3  */ {    3,        3,     3,       3,	      4,		  3,       3,      3,      3,          3,          3,        3,       3 }, /* NOFS(주석 내용) */
	/* S4  */ {    3,        3,     3,       3,	      5,		  3,       3,      3,      3,          3,          3,        3,       3 }, /* NOFS(* 감지 - 주석 종료 가능성) */
	/* S5  */ {   FS,       FS,    FS,      FS,	     FS,		 FS,      FS,     FS,     FS,         FS,         FS,       FS,      FS }, /* FSNR(* 감지 - 주석 종료) */
	/* S6  */ {    6,        8,     8,       7,	      7,		  7,       7,      7,      7,          7,          7,        7,       7 }, /* NOFS(* 키워드/식별자 중 - 키워드로 감지) */
	/* S7  */ {   FS,       FS,    FS,      FS,	     FS,		 FS,      FS,     FS,     FS,         FS,         FS,       FS,      FS }, /* FSNR(* 감지 - 키워드 종료) */
	/* S8  */ {    8,        8,     8,       9,	      9,		  9,       9,      9,      9,          9,          9,        9,       9 }, /* NOFS(* 식별자 감지) */
	/* S9  */ {   FS,       FS,    FS,      FS,	     FS,		 FS,      FS,     FS,     FS,         FS,         FS,       FS,      FS }, /* FSWR(* 감지 - 식별자 종료) */
};

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
Token funcMultiply(flowcode_string);
Token funcComment(flowcode_string);
Token funcIntegerLiteral(flowcode_string);
Token funcDoubleLiteral(flowcode_string);
Token funcString(flowcode_string);
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
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 23
#define KEYWORD_START_INDEX 29

/* TO_DO: Define the list of keywords */
static flowcode_string keywordTable[KWT_SIZE] = {
	/* keyword */
	/* logical operator */
	"and",
	"or",
	"not",
	/* control keyword */
	"if",
	"elif",
	"else",
	"then",
	"endif",
	/* iteration keyword */
	"repeat",
	"check",
	"break",
	"continue",
	/* I/O keyword */
	"Input",
	"Output",
	/* function keyword */
	"return",
	"end",
	/* data type keyword*/
	"int",
	"double",
	"string",
	"boolean",
	"void",
	/* other keyword */
	"begin",
	"declaration",
};
#define REL_SIZE 6
static flowcode_string relationTable[REL_SIZE] = {
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

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
#define BASE_TOKEN_LEN 54

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


	/* ========== 구분자 (Delimiters) ========== */
	LeftParen,          /*  8: '(' (왼쪽 괄호) */
	RightParen,         /*  9: ')' (오른쪽 괄호) */
	LeftBrace,          /* 10: '{' (왼쪽 중괄호) */
	RightBrace,         /* 11: '}' (오른쪽 중괄호) */
	Colon,              /* 12: ':' (콜론) */
	SemiColon,          /* 13: ';' (세미콜론) */
	Comma,              /* 14: ',' (쉼표) */
	Dot,

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
	/* ========== 연산자 (Operators) ========== */
	/* 할당 연산자 (Assignment Operator) */
	Assignment,         /*  7: '=' (할당 연산자) */
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

	StringDoubleQuoteLiteral,
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
#define ESNR	50		/* Error state with no retract */
#define ESWR	51		/* Error state with retract */
#define FS		52		/* Illegal state */

 /* TO_DO: State transition table definition */
#define NUM_STATES		31
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


/** FLOWCODE의 Transition Table 기준
 *  토큰을 판단하는 기준은 오직 [ index / FS / ESNR ] 만 사용
 *  NSWR은 STATE에서 이미 NOFS / FSNR / FSWR 로 기준을 잡고 사용하기 때문에 필요 없음!
 *
 *  예)
 *		intn= -> intn까지 keyword로 읽다가 =가 나옴으로써 FS로 이동하면서 keyword로 확정!
 *		3..   -> 3에서 정수로 확인, .에서 실수로 확인, .이 다시 나옴으로써 이건 ESNR로 확정!
 *		3.14= -> 문법적으로 맞지 않음. 리터럴 오른쪽에는 =가 나오지 않음. 하지만, =으로써 3.14가 실수인걸로 확정! =는 assig으로 확정! 문법적인 건 parser에서 할일!
 *		*<    -> 문법적으로 맞지 않음. 하지만, <가 나옴으로써 *는 곱셈으로 확정! <도 less로 확정! 문법적인 건 parser에서 할일!
 *		*>=*< -> 같은 말도 안되는 문법. 이것도 ESNR이 아님. 각각 토큰으로 나눌수 있음! 8,>,=,*,< 으로 가능하기 때문에 FS로 감.
 *		"h'   -> 이건 FS로 가도 토큰 생성이 불가! ESNR로 확정!
 *
 *		즉, 문법적으론 말도 안되도 토큰으로 나눌 수만 있다면 FS로 감! 근데 FSWR했는데도 불구하고 토큰이 불가할때 ESNR로 확정!
 */
static flowcode_int transitionTable[NUM_STATES][CHAR_CLASSES] = {
	/* State  | L(A-Z) | N(0-9) | U(_) | DOT(.) | MUL(*) | ASSIGN(=) | NOT(!) | LT(<) | GT(>) | SQUOTE(') | DQUOTE(") | STRC($) | OTHER | */
	/* S0  */ {    6,       10,     8,    ESNR,	      1,	     16,    ESNR,     19,     22,         25,         28,     ESNR,    ESNR }, /* NOFS(Initial State) */
	/* S1  */ {   15,       15,    15,    ESNR,		  2,	     15,      15,     15,     15,         15,         15,     ESNR,      15 }, /* NOFS(첫번째 * 감지) */
	/* S2  */ {    3,        3,     3,       3,	      4,	      3,       3,      3,      3,          3,          3,        3,       3 }, /* NOFS(두번째 * 감지 - 주석 시작) */
	/* S3  */ {    3,        3,     3,       3,	      4,		  3,       3,      3,      3,          3,          3,        3,       3 }, /* NOFS(주석 내용) */
	/* S4  */ {    3,        3,     3,       3,	      5,		  3,       3,      3,      3,          3,          3,        3,       3 }, /* NOFS(감지 - 주석 종료 가능성) */
	/* S5  */ {   FS,       FS,    FS,      FS,	     FS,		 FS,      FS,     FS,     FS,         FS,         FS,       FS,      FS }, /* FSNR(감지 - 주석 종료) */
	/* S6  */ {    6,        8,     8,       7,	      7,		  7,       7,      7,      7,          7,          7,        7,       7 }, /* NOFS(키워드/식별자 중 - 키워드로 감지) */
	/* S7  */ {   FS,       FS,    FS,      FS,	     FS,		 FS,      FS,     FS,     FS,         FS,         FS,       FS,      FS }, /* FSNR(감지 - 키워드 종료) */
	/* S8  */ {    8,        8,     8,       9,	      9,		  9,       9,      9,      9,          9,          9,        9,       9 }, /* NOFS(식별자 감지) */
	/* S9  */ {   FS,       FS,    FS,      FS,	     FS,		 FS,      FS,     FS,     FS,         FS,         FS,       FS,      FS }, /* FSWR(감지 - 식별자 종료) */
	/* S10 */ {   11,       10,    11,      12,	     11,		 11,      11,     11,     11,         11,         11,       11,      11 }, /* NOFS(숫자(정수/실수) 감지 */
	/* S11 */ {   FS,       FS,    FS,      FS,	     FS,		 FS,      FS,     FS,     FS,         FS,         FS,       FS,      FS }, /* FSWR(감지 - 정수 종료) */
	/* S12 */ { ESNR,       13,  ESNR,    ESNR,	   ESNR,	   ESNR,    ESNR,   ESNR,   ESNR,       ESNR,       ESNR,     ESNR,    ESNR }, /* NOFS(실수 감지 - DOT) */
	/* S13 */ {   14,       13,    14,      14,	     14,	     14,      14,     14,     14,         14,         14,       14,      14 }, /* NOFS(감지 - 실수 부분) */
	/* S14 */ {   FS,       FS,    FS,      FS,	     FS,		 FS,      FS,     FS,     FS,         FS,         FS,       FS,      FS }, /* FSWR(감지 - 실수 종료) */
	/* S15 */ {   FS,       FS,    FS,      FS,	     FS,		 FS,      FS,     FS,     FS,         FS,         FS,       FS,      FS }, /* FSWR(감지 - 곱셈 종료) */
	/* S16 */ {   17,       17,    17,      17,	     17,		 18,      17,     -1,     -1,         17,         17,       17,      17 }, /* NOFS(첫번째 = 감지 - = 비교연산자) */
	/* S17 */ {   FS,       FS,    FS,      FS,	     FS,		 FS,      FS,     FS,     FS,         FS,         FS,       FS,      FS }, /* FSWR(감지 - = 연산자 종료) */
	/* S18 */ {   FS,       FS,    FS,      FS,	     FS,		 FS,      FS,     FS,     FS,         FS,         FS,       FS,      FS }, /* FSNR(두번째 = 감지 - == 연산자 종료) */
	/* S19 */ {   20,       20,    20,      20,	     20,		 21,      20,     20,     20,         20,         20,       20,      20 }, /* NOFS(첫번째 < 감지) */
	/* S20 */ {   FS,       FS,    FS,      FS,	     FS,		 FS,      FS,     FS,     FS,         FS,         FS,       FS,      FS }, /* FSWR(감지 - < 연산자 종료) */
	/* S21 */ {   FS,       FS,    FS,      FS,	     FS,		 FS,      FS,     FS,     FS,         FS,         FS,       FS,      FS }, /* FSNR(두번째 = 감지 - <= 연산자 종료) */
	/* S22 */ {   23,       23,    23,      23,	     23,		 24,      23,     23,     23,         23,         23,       23,      23 }, /* NOFS(첫번째 > 감지) */
	/* S23 */ {   FS,       FS,    FS,      FS,	     FS,		 FS,      FS,     FS,     FS,         FS,         FS,       FS,      FS }, /* FSWR(감지 - > 연산자 종료) */
	/* S24 */ {   FS,       FS,    FS,      FS,	     FS,		 FS,      FS,     FS,     FS,         FS,         FS,       FS,      FS }, /* FSNR(두번째 = 감지 - >= 연산자 종료) */
	/* S25 */ {   26,       26,    26,      26,	     26,		 26,      26,     26,     26,         27,         26,       26,      26 }, /* NOFS(첫번째 ' 감지) */
	/* S26 */ {   26,       26,    26,      26,	     26,		 26,      26,     26,     26,         27,         26,       26,      26 }, /* NOFS(Single Quotation 내용) */
	/* S27 */ {   FS,       FS,    FS,      FS,	     FS,		 FS,      FS,     FS,     FS,         FS,         FS,       FS,      FS }, /* FSNR(두번째 ' 감지 - 종료) */
	/* S28 */ {   29,       29,    29,      29,	     29,		 29,      29,     29,     29,         29,         30,       29,      29 }, /* NOFS(첫번째 " 감지) */
	/* S29 */ {   29,       29,    29,      29,	     29,		 29,      29,     29,     29,         29,         30,       29,      29 }, /* NOFS(Single Quotation 내용) */
	/* S30 */ {   FS,       FS,    FS,      FS,	     FS,		 FS,      FS,     FS,     FS,         FS,         FS,       FS,      FS }, /* FSNR(두번째 ' 감지 - 종료) */
};

#define QUO_STATE 5
#define QUO_CLASS 5

static flowcode_int transitionTableForDoubleQuote[QUO_STATE][QUO_CLASS] = {
	/* State  | alphabet | number | U(_) |  $ | other | */
	/* S0  */ {       1,       1,     1,   2,       1 }, /* NOFS (Initial State) */
	/* S1  */ {       1,       1,     1,   2,       1 }, /* NOFS (Any string) */
	/* S2  */ {       3,    ESNR,     3,ESNR,    ESNR }, /* NOFS ($ 문자 감지) */
	/* S3  */ {       3,       3,     3,ESNR,       4 }, /* NOFS ($ 식별자 내용) */
	/* S4  */ {      FS,      FS,    FS,  FS,      FS }, /* FSWR ($ 식별자 종료) */
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
	/* 논리 연산자 (Logical Operators) */
	"and",      // LogicalAnd
	"or",       // LogicalOr
	"not",      // LogicalNot

	/* 제어문 키워드 (Control Keywords) */
	"if",       // If
	"elif",     // Elif
	"else",     // Else
	"then",     // Then
	"endif",    // EndIf

	/* 반복문 키워드 (Iteration Keywords) */
	"repeat",   // Repeat
	"check",    // Check
	"break",    // Break
	"continue", // Continue

	/* 입출력 키워드 (I/O Keywords) */
	"Input",    // Input
	"Output",   // Output

	/* 함수 키워드 (Function Keywords) */
	"return",   // Return
	"end",      // End

	/* 데이터 타입 키워드 (Data Type Keywords) */
	"int",      // Int
	"double",   // Double
	"string",   // String
	"boolean",  // Boolean
	"void",     // Void

	/* 기타 키워드 (Other Keywords) */
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

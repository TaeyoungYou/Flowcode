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
* File name: Scanner.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 Compilers, Lab Section: [303]
* Assignment: A22
* Date: March 09 2025
* Purpose: This file contains all functionalities from Scanner.
************************************************************
*/

/* TO_DO: Adjust the function header */

 /* The #define _CRT_SECURE_NO_WARNINGS should be used in MS Visual Studio projects
  * to suppress the warnings about using "unsafe" functions like fopen()
  * and standard sting library functions defined in string.h.
  * The define does not have any effect in Borland compiler projects.
  */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>   /* standard input / output */
#include <ctype.h>   /* conversion functions */
#include <stdlib.h>  /* standard library functions and constants */
#include <string.h>  /* string functions */
#include <limits.h>  /* integer types constants */
#include <float.h>   /* floating-point types constants */

/* #define NDEBUG to suppress assert() call */
#include <assert.h>  /* assert() prototype */

/* project header files */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef BUFFER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/*
----------------------------------------------------------------
TO_DO: Global vars definitions
----------------------------------------------------------------
*/

/* Global objects - variables */
/* This buffer is used as a repository for string literals. */
extern BufferPointer stringLiteralTable;	/* String literal table */
flowcode_int line;								/* Current line number of the source code */
extern flowcode_int errorNumber;				/* Defined in platy_st.c - run-time error number */

extern flowcode_int stateType[NUM_STATES];
extern flowcode_string keywordTable[KWT_SIZE];

extern PTR_ACCFUN finalStateTable[NUM_STATES];
extern flowcode_int transitionTable[NUM_STATES][CHAR_CLASSES];

/* Local(file) global objects - variables */
static BufferPointer lexemeBuffer;			/* Pointer to temporary lexeme buffer */
static BufferPointer sourceBuffer;			/* Pointer to input source buffer */

/*
 ************************************************************
 * Intitializes scanner
 *		This function initializes the scanner using defensive programming.
 ***********************************************************
 */
 /* TO_DO: Follow the standard and adjust datatypes */

flowcode_int startScanner(BufferPointer psc_buf) {
	/* TO_DO: Start histogram */
	for (flowcode_int i=0; i<NUM_TOKENS;i++)
		scData.scanHistogram[i] = 0;
	/* Basic scanner initialization */
	/* in case the buffer has been read previously  */
	readerRecover(psc_buf);
	readerClear(stringLiteralTable);
	line = 1;
	sourceBuffer = psc_buf;
	return EXIT_SUCCESS; /*0*/
}

/*
 ************************************************************
 * Process Token
 *		Main function of buffer, responsible to classify a char (or sequence
 *		of chars). In the first part, a specific sequence is detected (reading
 *		from buffer). In the second part, a pattern (defined by Regular Expression)
 *		is recognized and the appropriate function is called (related to final states 
 *		in the Transition Diagram).
 ***********************************************************
 */
// Source Code에서 Token을 찾아내는 함수
Token tokenizer(flowcode_void) {

	/* TO_DO: Follow the standard and adjust datatypes */

	Token currentToken = { 0 }; /* token to return after pattern recognition. Set all structure members to 0 */
	flowcode_int c;			/* input symbol */
	flowcode_int state = 0;	/* initial state of the FSM */
	flowcode_int lexStart;	/* start offset of a lexeme in the input char buffer (array) */
	flowcode_int lexEnd;		/* end offset of a lexeme in the input char buffer (array)*/

	flowcode_int lexLength;	/* token length */
	flowcode_int i;			/* counter */
	///flowcode_char newc;		// new char

	/* Starting lexeme */
	flowcode_string lexeme;	/* lexeme (to check the function) */
	lexeme = (flowcode_string)malloc(VID_LEN * sizeof(flowcode_char));
	if (!lexeme)
		return currentToken;
	lexeme[0] = EOS;

	while (1) { /* endless loop broken by token returns it will generate a warning */
		c = readerGetChar(sourceBuffer);

		// TO_DO: Defensive programming
		if (c < 0 || c >= NCHAR)
			return currentToken;

		/* ------------------------------------------------------------------------
			Part 1: Implementation of token driven scanner.
			Every token is possessed by its own dedicated code
			-----------------------------------------------------------------------
		*/

		/* TO_DO: All patterns that do not require accepting functions */
		switch (c) {

		// 공백 문자 제거
		case SPACE:
		case TAB:
			break;

		// 특수문자 처리 - 특수문자: 한 글자로도 의미가 파악이 가능한 character
		case END_OF_LINE:
			currentToken.code = EndOfLine;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case METHOD_START:
			currentToken.code = Colon;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case METHOD_END:
			currentToken.code = SemiColon;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case PAREN_OP:
			currentToken.code = LeftParen;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case PAREN_CL:
			currentToken.code = RightParen;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case BRACE_OP:
			currentToken.code = LeftBrace;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case BRACE_CL:
			currentToken.code = RightBrace;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case COMMA:
			currentToken.code = Comma;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case ADD:
			currentToken.code = Add;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case SUBTRACT:
			currentToken.code = Subtract;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case DIVIDE:
			currentToken.code = Divide;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case MODULUS:
			currentToken.code = Modulo;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case POWER:
			currentToken.code = Power;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;

		/* Cases for END OF FILE */
		case EOS:
			currentToken.code = EndOfToken;
			scData.scanHistogram[currentToken.code]++;
			currentToken.attribute.seofType = SEOF_0;
			return currentToken;
		case EOF:
			currentToken.code = EndOfToken;
			scData.scanHistogram[currentToken.code]++;
			currentToken.attribute.seofType = SEOF_255;
			return currentToken;

		/* ------------------------------------------------------------------------
			Part 2: Implementation of Finite State Machine (DFA) or Transition Table driven Scanner
			Note: Part 2 must follow Part 1 to catch the illegal symbols
			-----------------------------------------------------------------------
		*/

		/* TO_DO: Adjust / check the logic for your language */

		default: // general case
			state = nextState(state, c);
			lexStart = readerGetPosRead(sourceBuffer);	// -1을 삭제! 이미 이 코드에는 처음이 -1임
			readerSetMark(sourceBuffer, lexStart);
			int pos = 0;
			while (stateType[state] == NOFS) {	// Final State까지 반복
				c = readerGetChar(sourceBuffer);
				state = nextState(state, c);
				pos++;
			}
			if (stateType[state] == FSWR)	// 한번 되돌려야하는 상황
				readerRetract(sourceBuffer);
			lexEnd = readerGetPosRead(sourceBuffer);	// 현재까지 읽은 read 포지션
			lexLength = lexEnd - lexStart - 1;			// read의 초기를 -1로 했기 때문에 추가로 -1
			lexemeBuffer = readerCreate((flowcode_int)lexLength + 2, 0, MODE_FIXED);	// 현재 읽은 unKnown-Token을 Buffer로 생성
			if (!lexemeBuffer) {
				fprintf(stderr, "Scanner error: Can not create buffer\n");
				exit(1);
			}
			readerRestore(sourceBuffer);
			for (i = 0; i < lexLength; i++)
				readerAddChar(lexemeBuffer, readerGetChar(sourceBuffer));	// unknown-token를 write를 작성을 함
			readerAddChar(lexemeBuffer, READER_TERMINATOR);					// 마지막에 널 포인터
			lexeme = readerGetContent(lexemeBuffer, 0);						// unknown-token
			// TO_DO: Defensive programming
			if (!lexeme)
				return currentToken;
			currentToken = (*finalStateTable[state])(lexeme);		// 갈 함수 정하고 Token반환
			readerRestore(lexemeBuffer);						// Marker로 재배치한다고?? - 함수 확인 필요!
			return currentToken;
		} // switch

	} //while

} // tokenizer


/*
 ************************************************************
 * Get Next State
	The assert(int test) macro can be used to add run-time diagnostic to programs
	and to "defend" from producing unexpected results.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	(*) assert() is a macro that expands to an if statement;
	if test evaluates to false (zero) , assert aborts the program
	(by calling abort()) and sends the following message on stderr:
	(*) Assertion failed: test, file filename, line linenum.
	The filename and linenum listed in the message are the source file name
	and line number where the assert macro appears.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	If you place the #define NDEBUG directive ("no debugging")
	in the source code before the #include <assert.h> directive,
	the effect is to comment out the assert statement.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	The other way to include diagnostics in a program is to use
	conditional preprocessing as shown bellow. It allows the programmer
	to send more details describing the run-time problem.
	Once the program is tested thoroughly #define DEBUG is commented out
	or #undef DEBUG is used - see the top of the file.
 ***********************************************************
 */
 /* TO_DO: Just change the datatypes */

flowcode_int nextState(flowcode_int state, flowcode_char c) {
	flowcode_int col;
	flowcode_int next;
	col = nextClass(c);
	next = transitionTable[state][col];
	if (DEBUG)
		printf("Input symbol: %c Row: %d Column: %d Next: %d \n", c, state, col, next);
	assert(next != FS);		// 허용되지않는 state라면 assert!
	if (DEBUG)
		if (next == FS) {	// assert가 울지 않는 한 들어가지 않음
			printf("Scanner Error: Illegal state:\n");
			printf("Input symbol: %c Row: %d Column: %d\n", c, state, col);
			exit(1);
		}
	return next;
}

/*
 ************************************************************
 * Get Next Token Class
	* Create a function to return the column number in the transition table:
	* Considering an input char c, you can identify the "class".
	* For instance, a letter should return the column for letters, etc.
 ***********************************************************
 */
/* TO_DO: Use your column configuration */

/* Adjust the logic to return next column in TT */
/*    [A-z],[0-9],    _,    &,   \', SEOF,    #, other
	   L(0), D(1), U(2), M(3), Q(4), E(5), C(6),  O(7) */

flowcode_int nextClass(flowcode_int c) {
	if(isalpha(c))		return 0;
	if(isdigit(c))		return 1;
	if(c == UNDERSCORE) return 2;
	if(c == DOT)		return 3;
	if(c == ASTER)		return 4;
	if(c == ASSIGN)		return 5;
	if(c == NOT)		return 6;
	if(c == LESS)		return 7;
	if(c == GREATER)	return 8;
	if(c == STR_LI)		return 9;
	if(c == STR_CON)	return 10;
	if(c == CAL_VAR)	return 11;
	return 12;	// other
}

/*
 ************************************************************
 * Acceptance State Function COM
 *		Function responsible to identify COM (comments).
 ***********************************************************
 */
 /* TO_DO: Adjust the function for IL */

Token funcComment(flowcode_string lexeme) {
	Token currentToken = { 0 };
	flowcode_int i = 0, len = (flowcode_int)strlen(lexeme);
	currentToken.attribute.contentString = readerGetPosWrte(stringLiteralTable);
	// ** ... ** 이므로, 2번째 문자부터 검사
	for (i = 2; i < len - 2; i++) {
		if (lexeme[i] == END_OF_LINE)
			line++;
	}
	currentToken.code = Comment;
	scData.scanHistogram[currentToken.code]++;
	return currentToken;
}


 /*
  ************************************************************
  * Acceptance State Function IL
  *		Function responsible to identify IL (integer literals).
  * - It is necessary respect the limit (ex: 2-byte integer in C).
  * - In the case of larger lexemes, error shoul be returned.
  * - Only first ERR_LEN characters are accepted and eventually,
  *   additional three dots (...) should be put in the output.
  ***********************************************************
  */
  /* TO_DO: Adjust the function for IL */
// Literal: Integer, Double, String, Boolean
Token funcIntegerLiteral(flowcode_string lexeme) {
	Token currentToken = { 0 };
	flowcode_long tlong;

	if (lexeme[0] != EOS && strlen(lexeme) > NUM_LEN) {
		currentToken = (*finalStateTable[ESNR])(lexeme);
	}
	else {
		tlong = atol(lexeme);
		if (tlong >= 0 && tlong <= SHRT_MAX) {
			currentToken.code = IntLiteral;
			scData.scanHistogram[currentToken.code]++;
			currentToken.attribute.intValue = (flowcode_int)tlong;
		}
		else {
			currentToken = (*finalStateTable[ESNR])(lexeme);
		}
	}
	return currentToken;
}

/*
************************************************************
 * Acceptance State Function SL
 *		Function responsible to identify SL (string literals).
 * - The lexeme must be stored in the String Literal Table
 *   (stringLiteralTable). You need to include the literals in
 *   this structure, using offsets. Remember to include \0 to
 *   separate the lexemes. Remember also to incremente the line.
 ***********************************************************
 */
/* TO_DO: Adjust the function for SL */
//
Token funcSL(flowcode_string lexeme) {
	Token currentToken = { 0 };
	flowcode_int i = 0, len = (flowcode_int)strlen(lexeme);
	currentToken.attribute.contentString = readerGetPosWrte(stringLiteralTable);
	for (i = 1; i < len - 1; i++) {
		if (lexeme[i] == NWL_CHR)
			line++;
		if (!readerAddChar(stringLiteralTable, lexeme[i])) {
			currentToken.code = RTE_T;
			scData.scanHistogram[currentToken.code]++;
			strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
			errorNumber = RTE_CODE;
			return currentToken;
		}
	}
	if (!readerAddChar(stringLiteralTable, EOS_CHR)) {
		currentToken.code = RTE_T;
		scData.scanHistogram[currentToken.code]++;
		strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
		errorNumber = RTE_CODE;
		return currentToken;
	}
	currentToken.code = STR_T;
	scData.scanHistogram[currentToken.code]++;
	return currentToken;
}

/*
 ************************************************************
 * Acceptance State Function ID
 *		In this function, the pattern for IDs must be recognized.
 *		Since keywords obey the same pattern, is required to test if
 *		the current lexeme matches with KW from language.
 *	- Remember to respect the limit defined for lexemes (VID_LEN) and
 *	  set the lexeme to the corresponding attribute (vidLexeme).
 *    Remember to end each token with the \0.
 *  - Suggestion: Use "strncpy" function.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for ID */
// Keyword가 아니면 Identifier - 아직까진 Variable, Constant, Method 중 어느 Identifier인지 모름
Token funcIdentifier(flowcode_string lexeme) {
	Token currentToken = { 0 };
	size_t length = strlen(lexeme);
	flowcode_int isID = FLOWCODE_FALSE;
	switch (lastch) {
		case AMP_CHR:
			currentToken.code = MNID_T;
			scData.scanHistogram[currentToken.code]++;
			isID = FLOWCODE_TRUE;
			break;
		default:
			// Test Keyword
			///lexeme[length - 1] = EOS_CHR;
			currentToken = funcKEY(lexeme);
			break;
	}
	if (isID == FLOWCODE_TRUE) {
		strncpy(currentToken.attribute.idLexeme, lexeme, VID_LEN);
		currentToken.attribute.idLexeme[VID_LEN] = EOS_CHR;
	}
	return currentToken;
}


/*
************************************************************
 * This function checks if one specific lexeme is a keyword.
 * - Tip: Remember to use the keywordTable to check the keywords.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for Keywords */
// Keyword
//	- Logical: and, or, not
//	- Control: if, elif, else, then, endif
//	- Iteration: repeat, check, break, continue
//	- I/O: Input, Output
//	- Funtional: return, end
//	- Data type: int, double, string, boolean, void
//	- others: begin, declaration
Token funcKEY(flowcode_string lexeme) {
	Token currentToken = { 0 };
	flowcode_int kwindex = -1, j = 0;
	flowcode_int len = (flowcode_int)strlen(lexeme);
	///lexeme[len - 1] = EOS_CHR;
	for (j = 0; j < KWT_SIZE; j++)
		if (!strcmp(lexeme, &keywordTable[j][0]))
			kwindex = j;
	if (kwindex != -1) {
		currentToken.code = KW_T;
		scData.scanHistogram[currentToken.code]++;
		currentToken.attribute.codeType = kwindex;
	}
	else {
		currentToken = funcErr(lexeme);
	}
	return currentToken;
}


/*
************************************************************
 * Acceptance State Function Error
 *		Function responsible to deal with ERR token.
 * - This function uses the errLexeme, respecting the limit given
 *   by ERR_LEN. If necessary, use three dots (...) to use the
 *   limit defined. The error lexeme contains line terminators,
 *   so remember to increment line.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for Errors */
// all the error
Token funcErr(flowcode_string lexeme) {
	Token currentToken = { 0 };
	flowcode_int i = 0, len = (flowcode_int)strlen(lexeme);
	if (len > ERR_LEN) {
		strncpy(currentToken.attribute.errLexeme, lexeme, ERR_LEN - 3);
		currentToken.attribute.errLexeme[ERR_LEN - 3] = EOS;
		strcat(currentToken.attribute.errLexeme, "...");
	}
	else {
		strcpy(currentToken.attribute.errLexeme, lexeme);
	}
	for (i = 0; i < len; i++)
		if (lexeme[i] == END_OF_LINE)
			line++;
	currentToken.code = Error;
	scData.scanHistogram[currentToken.code]++;
	return currentToken;
}


/*
 ************************************************************
 * The function prints the token returned by the scanner
 ***********************************************************
 */

flowcode_void printToken(Token t) {
	extern flowcode_string keywordTable[]; /* link to keyword table in */
	switch (t.code) {
	case RunTimeError:
		printf("RunTimeError\t\t%s", t.attribute.errLexeme);
		/* Call here run-time error handling component */
		if (errorNumber) {
			printf("%d", errorNumber);
			exit(errorNumber);
		}
		printf("\n");
		break;
	case Error:
		printf("Error\t\t%s\n", t.attribute.errLexeme);
		break;
	case EndOfToken:
		printf("EndOfToken\t\t%d\t\n", t.attribute.seofType);
		break;
	case MethodIdentifier:
		printf("MethodIdentifier\t\t%s\n", t.attribute.idLexeme);
		break;
	case StringLiteral:
		printf("StringLiteral\t\t%d\t ", (flowcode_int)t.attribute.codeType);
		printf("%s\n", readerGetContent(stringLiteralTable, (flowcode_int)t.attribute.codeType));
		break;
	case LeftParen:
		printf("LeftParen\n");
		break;
	case RightParen:
		printf("RightParen\n");
		break;
	case LBR_T:
		printf("LBR_T\n");
		break;
	case RBR_T:
		printf("RBR_T\n");
		break;
	case KW_T:
		printf("KW_T\t\t%s\n", keywordTable[t.attribute.codeType]);
		break;
	case CMT_T:
		printf("CMT_T\n");
		break;
	case EOS_T:
		printf("EOS_T\n");
		break;
	default:
		printf("Scanner error: invalid token code: %d\n", t.code);
	}
}

/*
 ************************************************************
 * The function prints statistics of tokens
 * Param:
 *	- Scanner data
 * Return:
 *	- Void (procedure)
 ***********************************************************
 */
flowcode_void printScannerData(ScannerData scData) {
	/* Print Scanner statistics */
	printf("Statistics:\n");
	printf("----------------------------------\n");
	int cont = 0;
	for (cont = 0; cont < NUM_TOKENS; cont++) {
		if (scData.scanHistogram[cont] > 0)
			printf("%s%s%s%d%s", "Token[", tokenStrTable[cont], "]=", scData.scanHistogram[cont], "\n");
	}
	printf("----------------------------------\n");
}

/*
TO_DO: (If necessary): HERE YOU WRITE YOUR ADDITIONAL FUNCTIONS (IF ANY).
*/

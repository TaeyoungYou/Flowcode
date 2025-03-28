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

#define FINAL_STATE_TABLE_SIZE (sizeof(finalStateTable) / sizeof(finalStateTable[0]))
/*
----------------------------------------------------------------
TO_DO: Global vars definitions
----------------------------------------------------------------
*/

/* Global objects - variables */
/* This buffer is used as a repository for string literals. */
extern BufferPointer stringLiteralTable; /* String literal table */
flowcode_int line; /* Current line number of the source code */
extern flowcode_int errorNumber; /* Defined in platy_st.c - run-time error number */

extern flowcode_int stateType[NUM_STATES];
extern flowcode_string keywordTable[KWT_SIZE];

extern PTR_ACCFUN finalStateTable[NUM_STATES];
extern flowcode_int transitionTable[NUM_STATES][CHAR_CLASSES];

/* Local(file) global objects - variables */
static BufferPointer lexemeBuffer; /* Pointer to temporary lexeme buffer */
static BufferPointer sourceBuffer; /* Pointer to input source buffer */

/*
 ************************************************************
 * Intitializes scanner
 *		This function initializes the scanner using defensive programming.
 ***********************************************************
 */
/* TO_DO: Follow the standard and adjust datatypes */

flowcode_int startScanner(BufferPointer psc_buf) {
    /* TO_DO: Start histogram */
    for (flowcode_int i = 0; i < BASE_TOKEN_LEN; i++)
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
// Function to identify tokens from the source code
Token tokenizer(flowcode_void) {
    /* TO_DO: Follow the standard and adjust datatypes */

    Token currentToken = {EndOfToken,}; /* token to return after pattern recognition. Set all structure members to 0 */
    flowcode_int c; /* input symbol */
    flowcode_int state = 0; /* initial state of the FSM */
    flowcode_int lexStart; /* start offset of a lexeme in the input char buffer (array) */
    flowcode_int lexEnd; /* end offset of a lexeme in the input char buffer (array)*/

    flowcode_int lexLength; /* token length */
    flowcode_int i; /* counter */
    ///flowcode_char newc;		// new char

    /* Starting lexeme */
    flowcode_string lexeme; /* lexeme (to check the function) */
    lexeme = (flowcode_string) malloc(VID_LEN * sizeof(flowcode_char));
    if (!lexeme)
        return currentToken;
    lexeme[0] = EOS;

    while (1) {
        /* endless loop broken by token returns it will generate a warning */
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
            // Remove space or tab
            case SPACE:
            case TAB:
                break;

            // Special character processing - Special characters: Single-character symbols that convey meaning
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
            case DOT:
                currentToken.code = Dot;
                scData.scanHistogram[currentToken.code]++;
                return currentToken;

            /* Cases for END OF FILE */
            case EOS:
                currentToken.code = EndOfToken;
                scData.scanHistogram[currentToken.code]++;
                currentToken.attribute.seofType = SEOF_0;
                return currentToken;
            case EOF_T:
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
                lexStart = readerGetPosRead(sourceBuffer); // Removed -1! The initial value is already set to -1 in this code.
                readerSetMark(sourceBuffer, lexStart);
                int pos = 0;
                while (stateType[state] == NOFS) {
                    // Repeat until reaching a Final State
                    c = readerGetChar(sourceBuffer);
                    state = nextState(state, c);
                    pos++;
                }
                if (stateType[state] == FSWR) // If the state requires retracting
                    readerRetract(sourceBuffer);
                lexEnd = readerGetPosRead(sourceBuffer); // Get the current read position
                lexLength = lexEnd - lexStart; // Since the initial read position was set to -1, no additional subtraction is needed
                lexemeBuffer = readerCreate((flowcode_int) lexLength + 4, 0, MODE_FIXED);
                // Create a buffer for the currently read unknown token
                if (!lexemeBuffer) {
                    fprintf(stderr, "Scanner error: Can not create buffer\n");
                    exit(1);
                }
                readerRestore(sourceBuffer);
                for (i = 0; i <= lexLength; i++) {
                    char ch = readerGetChar(sourceBuffer);
                    readerAddChar(lexemeBuffer, ch);  // Write unknown token into the buffer
                }
                readerAddChar(lexemeBuffer, READER_TERMINATOR); // Add a null terminator at the end
                if (DEBUG) printf("check contents : %s\n", lexemeBuffer->content);
                lexeme = readerGetContent(lexemeBuffer, 0); // unknown-token
            // TO_DO: Defensive programming
                if (!lexeme)
                    return currentToken;
                currentToken = (*finalStateTable[state])(lexeme); // Determine the function to call and return the token
                readerRestore(lexemeBuffer); // Reposition using the marker?? - Function verification needed!
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
    assert(next != FS); // Assert if the state is not allowed!
    if (DEBUG)
        if (next == FS) {
            // This code should never be reached unless an assertion fails
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

flowcode_int nextClass(flowcode_char c) {
    if (isalpha(c)) return 0;
    if (isdigit(c)) return 1;
    if (c == UNDERSCORE) return 2;
    if (c == DOT) return 3;
    if (c == ASTER) return 4;
    if (c == ASSIGN) return 5;
    if (c == NOT) return 6;
    if (c == LESS) return 7;
    if (c == GREATER) return 8;
    if (c == STR_LI) return 9;
    if (c == STR_CON) return 10;
    if (c == CAL_VAR) return 11;
    return 12; // other
}

/*
 ************************************************************
 * Acceptance State Function COM
 *		Function responsible to identify COM (comments).
 ***********************************************************
 */
/* TO_DO: Adjust the function for IL */

Token funcMultiply(flowcode_string lexeme) {
    Token currentToken = {0};
    currentToken.code = Multiply;
    scData.scanHistogram[currentToken.code]++;
    return currentToken;
}

Token funcComment(flowcode_string lexeme) {
    Token currentToken = {0};
    flowcode_int i = 0, len = (flowcode_int) strlen(lexeme);
    currentToken.attribute.comment_content = lexeme;
    // ** Since it starts with '...' (double asterisks), check from the second character **
    for (i = 2; i < len - 2; i++) {
        if (lexeme[i] == END_OF_LINE) {
            line++;
        }
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
// Literal: Integer, Double, String
Token funcIntegerLiteral(flowcode_string lexeme) {
    Token currentToken = {0};
    flowcode_long tlong;

    if (lexeme[0] != EOS && strlen(lexeme) > NUM_LEN) {
        currentToken = (*finalStateTable[ESNR])(lexeme);
    } else {
        tlong = atol(lexeme);
        if (tlong >= 0 && tlong <= SHRT_MAX) {
            currentToken.code = IntLiteral;
            scData.scanHistogram[currentToken.code]++;
            currentToken.attribute.intValue = (flowcode_int) tlong;
        } else {
            currentToken = (*finalStateTable[ESNR])(lexeme);
        }
    }
    return currentToken;
}

Token funcDoubleLiteral(flowcode_string lexeme) {
    Token currentToken = { 0 };
    flowcode_double tdouble;
    if (lexeme[0] != EOS && strlen(lexeme) > NUM_LEN) {
        currentToken = (*finalStateTable[ESNR])(lexeme);
    } else {
        tdouble = atof(lexeme);
        if (tdouble >= 0 && tdouble <= DBL_MAX) {
            currentToken.code = DoubleLiteral;
            scData.scanHistogram[currentToken.code]++;
            currentToken.attribute.doubleValue = tdouble;
        }
        else {
            currentToken = (*finalStateTable[ESNR])(lexeme);
        }
    }
    return currentToken;
}

Token funcString(flowcode_string lexeme) {
    Token currentToken = {0};
    flowcode_int i = 0, len = (flowcode_int) strlen(lexeme);
    currentToken.attribute.contentString = readerGetPosWrte(stringLiteralTable);
    for (i = 1; i < len - 1; i++) {
        if (lexeme[i] == END_OF_LINE)
            line++;
        if (!readerAddChar(stringLiteralTable, lexeme[i])) {
            currentToken.code = RunTimeError;
            scData.scanHistogram[currentToken.code]++;
            strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
            errorNumber = RTE_CODE;
            return currentToken;
        }
    }
    if (!readerAddChar(stringLiteralTable, EOS)) {
        currentToken.code = RunTimeError;
        scData.scanHistogram[currentToken.code]++;
        strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
        errorNumber = RTE_CODE;
        return currentToken;
    }
    currentToken.code = StringLiteral;
    scData.scanHistogram[currentToken.code]++;
    return currentToken;
}

Token funcDoubleString(flowcode_string lexeme) {
    Token currentToken = { 0 };
    flowcode_int i = 1, len = (flowcode_int)strlen(lexeme);
    flowcode_int varIndex = 0;
    char varBuffer[VID_LEN] = { 0 };
    flowcode_int varBufferIndex = 0;
    flowcode_bool isVariable = false;
    /* Store the current write position in the string literal table */
    currentToken.attribute.contentString = readerGetPosWrte(stringLiteralTable);

    for (i = 1; i < len - 1; i++) {
        if (lexeme[i] == CAL_VAR) {
            isVariable = true;
            varBufferIndex = 0;
            continue;
        }

        if (isVariable) {
            // Check variable name rules: [a-zA-Z_][a-zA-Z0-9_]* 
            if (isalnum(lexeme[i]) || lexeme[i] == '_') {
                varBuffer[varBufferIndex++] = lexeme[i];
                if (varBufferIndex >= VID_LEN - 1) {
                    break; // Stop if the variable name is too long 
                }
                continue;
            }
            // End of variable identifier
            varBuffer[varBufferIndex] = '\0';
            if (varBufferIndex > 0) {
                // Convert the variable name into an Identifier token
                Token varToken = funcIdentifier(varBuffer);
                printf("Detected Variable: $%s (Token Code: %d)\n", varBuffer, varToken.code);
                scData.scanHistogram[varToken.code]++;
                if (varIndex < MAX_VAL - 1) {
                    printf("Storing variable $ % s at varsDoubleQuote[% d]\n", varBuffer, varIndex);

                    // Dynamically allocate memory for storing the VID
                    varsDoubleQuote[varIndex] = (char*)malloc((strlen(varBuffer) + 1) * sizeof(char));
                    if (varsDoubleQuote[varIndex] == NULL) {
                        printf("Memory allocation failed for varsDoubleQuote[%d]\n", varIndex);
                    }
                    else {
                        strcpy(varsDoubleQuote[varIndex], varBuffer);
                    }
                    varIndex++;
                }
                else {
                    printf("varsDoubleQuote index exceeded! varIndex = %d, MAX_VAL = %d\n", varIndex, MAX_VAL);
                }
            }
            isVariable = false;
        } 
    if (!readerAddChar(stringLiteralTable, lexeme[i])) {
        currentToken.code = RunTimeError;
        scData.scanHistogram[currentToken.code]++;
        strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
        errorNumber = RTE_CODE;
        return currentToken;
        }
    }
    if (!readerAddChar(stringLiteralTable, EOS)) {
        currentToken.code = RunTimeError;
        scData.scanHistogram[currentToken.code]++;
        strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
        errorNumber = RTE_CODE;
        return currentToken;
    }
    currentToken.code = StringDoubleQuoteLiteral;
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
// If not a keyword, treat it as an Identifier - It is not yet determined whether it is a Variable, Constant, or Method.
Token funcIdentifier(flowcode_string lexeme) {
    Token currentToken = {0};
    size_t length = strlen(lexeme);

    currentToken.code = Identifier;
    scData.scanHistogram[currentToken.code]++;
    strncpy(currentToken.attribute.idLexeme, lexeme, VID_LEN);
    currentToken.attribute.idLexeme[VID_LEN] = EOS;

    return currentToken;
}


Token funcKeyword(flowcode_string lexeme) {
    Token currentToken = {0};
    flowcode_int keywordIndex = -1, j = 0;

    for (j = 0; j < KWT_SIZE; ++j) if (!strcmp(lexeme, &keywordTable[j][0])) keywordIndex = j + KEYWORD_START_INDEX;
    if (keywordIndex != -1) {
        currentToken.code = keywordIndex;
        scData.scanHistogram[currentToken.code]++;
        currentToken.attribute.codeType = keywordIndex;
    } else {
        currentToken = funcIdentifier(lexeme);
    }
    return currentToken;
}

Token funcRelational(flowcode_string lexeme) {
    Token currentToken = {0};
    flowcode_int relationIndex = -1, j = 0;

    for (j = 0; j < REL_SIZE; ++j) if (!strcmp(lexeme, &relationTable[j][0])) relationIndex = j + REL_START_INDEX;
    if (relationIndex != -1) {
        currentToken.code = relationIndex;
        scData.scanHistogram[currentToken.code]++;
        currentToken.attribute.codeType = relationIndex;
    } else {
        currentToken.code = Error;
        scData.scanHistogram[currentToken.code]++;
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
    Token currentToken = {0};
    flowcode_int i = 0, len = (flowcode_int) strlen(lexeme);
    if (len > ERR_LEN) {
        strncpy(currentToken.attribute.errLexeme, lexeme, ERR_LEN - 3);
        currentToken.attribute.errLexeme[ERR_LEN - 3] = EOS;
        strcat(currentToken.attribute.errLexeme, "...");
    } else {
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
        // 1. **Error and Basic Token Output**
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
        case Identifier:
            printf("Identifier\t\t%s\n", t.attribute.idLexeme);
            break;
        case IntLiteral:
            printf("IntLiteral\t\t%d\n", t.attribute.intValue);
            break;
        case DoubleLiteral:
            printf("DoubleLiteral\t\t%lf\n", t.attribute.doubleValue);
            break;
        case StringLiteral:
            printf("StringLiteral\t\t%d\t ", (flowcode_int) t.attribute.codeType);
            printf("%s\n", readerGetContent(stringLiteralTable, (flowcode_int) t.attribute.codeType));
            break;
        case StringDoubleQuoteLiteral:
            printf("StringLiteral\t\t%d\t ", (flowcode_int) t.attribute.codeType);
            printf("%s\n", readerGetContent(stringLiteralTable, (flowcode_int) t.attribute.codeType));
            printf("Variables: "); // Additional feature: Print variables that appear with $ symbol 
           
            /* Iterate through the varsDoubleQuote array to find and print non - null, non - empty variables */
            for (flowcode_int i = 0; i < MAX_VAL; i++) {
                if (varsDoubleQuote[i] == NULL) {
                    continue; // Skip if the variable is NULL
                }
                if (varsDoubleQuote[i][0] != '\0') {
                    printf("$%s ", varsDoubleQuote[i]);
                }
            }
            printf("\n");
        case LeftParen:
            printf("LeftParen\n");
            break;
        case RightParen:
            printf("RightParen\n");
            break;
        case LeftBrace:
            printf("LeftBrace\n");
            break;
        case RightBrace:
            printf("RightBrace\n");
            break;
        case Colon:
            printf("Colon\n");
            break;
        case SemiColon:
            printf("SemiColon\n");
            break;
        case Comma:
            printf("Comma\n");
            break;
        case Dot:
            printf("Dot\n");
            break;
        case Comment:
            printf("Comment\n%s\n", t.attribute.comment_content);
            break;
        case EndOfLine:
            printf("End of Line(\\n)\n");
            break;

        // 2. ** Arithmetic Operators **
        case Add:
            printf("Add(+) arithmetic operator\n");
            break;
        case Subtract:
            printf("Subtract(-) arithmetic operator\n");
            break;
        case Multiply:
            printf("Multiply(*) arithmetic operator\n");
            break;
        case Divide:
            printf("Divide(/) arithmetic operator\n");
            break;
        case Modulo:
            printf("Modulo(%%) arithmetic operator\n");
            break;
        case Power:
            printf("Power(^) arithmetic operator\n");
            break;

        // 3. ** Relational Operators **
        case Assignment:
            printf("Assignment(=) operator\n");
            break;
        case Equal:
            printf("Equal(==) relational operator\n");
            break;
        case NotEqual:
            printf("Not Equal(!=) relational operator\n");
            break;
        case LessThan:
            printf("Less Than(<) relational operator\n");
            break;
        case GreaterThan:
            printf("Greater Than(>) relational operator\n");
            break;
        case LessOrEqual:
            printf("Less Or Equal(<=) relational operator\n");
            break;
        case GreaterOrEqual:
            printf("Greater Or Equal(>=) relational operator\n");
            break;

        // 4. ** Keywords **
        case LogicalAnd:
            printf("Logical And(and) keyword\n");
            break;
        case LogicalOr:
            printf("Logical Or(or) keyword\n");
            break;
        case LogicalNot:
            printf("Logical Not(not) keyword\n");
            break;
        case If:
            printf("if keyword\n");
            break;
        case Elif:
            printf("elif keyword\n");
            break;
        case Else:
            printf("else keyword\n");
            break;
        case Then:
            printf("then keyword\n");
            break;
        case EndIf:
            printf("endif keyword\n");
            break;
        case Repeat:
            printf("repeat keyword\n");
            break;
        case Check:
            printf("check keyword\n");
            break;
        case Break:
            printf("break keyword\n");
            break;
        case Continue:
            printf("continue keyword\n");
            break;
        case Input:
            printf("Input I/O function keyword\n");
            break;
        case Output:
            printf("Output I/O function keyword\n");
            break;
        case Return:
            printf("return keyword\n");
            break;
        case End:
            printf("end keyword\n");
            break;
        case Int:
            printf("(int) integer type keyword\n");
            break;
        case Double:
            printf("(double) double type keyword\n");
            break;
        case String:
            printf("(string) string type keyword\n");
            break;
        case Boolean:
            printf("(bool) boolean type keyword\n");
            break;
        case Void:
            printf("(void) void type keyword\n");
            break;
        case Begin:
            printf("(begin) start flowcode source code keyword\n");
            break;
        case Declaration:
            printf("(declaration) declaration keyword\n");
            break;

        // 5. ** Default (Cannot find token...)**
        default:
            printf("Cannot find..!\n");
            break;
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

    /* Iterate through the token histogram and print non-zero values */
    for (cont = 0; cont < BASE_TOKEN_LEN; cont++) {
        if (scData.scanHistogram[cont] > 0)
            printf("%s%s%s%d%s", "Token[", tokenStrTable[cont], "]=", scData.scanHistogram[cont], "\n");
    }
    printf("----------------------------------\n");
}

/*
TO_DO: (If necessary): HERE YOU WRITE YOUR ADDITIONAL FUNCTIONS (IF ANY).
*/

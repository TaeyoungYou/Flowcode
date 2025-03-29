/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2025
* Author: Taeyoung You, Juhyeon Oh
* Professors: Paulo Sousa
************************************************************
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
* File name: Parser.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012]
* Assignment: A32.
* Date: May 01, 2023,
* Professor: Paulo Sousa
* Purpose: This file is the main header for Parser (.h)
************************************************************
*/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif
#ifndef READER_H_
#include "Reader.h"
#endif
#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global vars */
static Token			lookahead;
extern BufferPointer	stringLiteralTable;
extern flowcode_int		line;
extern Token			tokenizer(flowcode_void);
extern flowcode_string	keywordTable[KWT_SIZE];
static flowcode_int		syntaxErrorNumber = 0;

#define LANG_WRTE		"Output"
#define LANG_READ		"Input"
#define LANG_MAIN		"Main"

/* TO_DO: Define the number of BNF rules */
#define NUM_BNF_RULES 24

/* Parser */
typedef struct parserData {
	flowcode_int parsHistogram[NUM_BNF_RULES];	/* Number of BNF Statements */
} ParserData, * pParsData;

/* Number of errors */
flowcode_int numParserErrors;

/* Scanner data */
ParserData psData;

/* Function definitions */
flowcode_void startParser();
flowcode_void matchToken(flowcode_int);
flowcode_void syncErrorHandler(flowcode_int);
flowcode_void printError();
flowcode_void printBNFData(ParserData psData);

/* List of BNF statements */
enum BNF_RULES {
	BNF_program,
	BNF_type,
	BNF_declaration_section,
	BNF_var_declaration,
	BNF_var_declaration_line,
	BNF_identifier_list,
	BNF_identifier_tail,
	BNF_function_definition,
	BNF_parameter_list,
	BNF_parameter_tail,
	BNF_parameter,
	BNF_statement_list,
	BNF_statement,
	BNF_assignment_statement,
	BNF_expression,
	BNF_add_expre_tail,
	BNF_mul_expre,
	BNF_mul_expre_tail,
	BNF_pow_expre,
	BNF_factor,
	BNF_input_statement,
	BNF_output_statement,
	BNF_output_target,
	BNF_return_statement,
};


/* TO_DO: Define the list of keywords */
static flowcode_string BNFStrTable[NUM_BNF_RULES] = {
	"BNF_program",
	"BNF_type",
	"BNF_declaration_section",
	"BNF_var_declaration",
	"BNF_var_declaration_line",
	"BNF_identifier_list",
	"BNF_identifier_tail",
	"BNF_function_definition",
	"BNF_parameter_list",
	"BNF_parameter",
	"BNF_parameter_tail",
	"BNF_statement_list",
	"BNF_statement",
	"BNF_assignment_statement",
	"BNF_expression",
	"BNF_add_expre_tail",
	"BNF_mul_expre",
	"BNF_mul_expre_tail",
	"BNF_pow_expre",
	"BNF_factor",
	"BNF_input_statement",
	"BNF_output_statement",
	"BNF_output_target",
	"BNF_return_statement",
};


/* TO_DO: Place ALL non-terminal function declarations */
flowcode_void program();
flowcode_void type();
flowcode_void declarationSection();
flowcode_void varDeclaration();
flowcode_void varDeclarationLine();
flowcode_void identifierList();
flowcode_void identifierTail();
flowcode_void functionDefinition();
flowcode_void parameterList();
flowcode_void parameter();
flowcode_void parameterTail();
flowcode_void statementList();
flowcode_void statement();
flowcode_void assignmentStatement();
flowcode_void expression();
flowcode_void addExpreTail();
flowcode_void mulExpre();
flowcode_void mulExpreTail();
flowcode_void powExpre();
flowcode_void factor();
flowcode_void inputStatement();
flowcode_void outputStatement();
flowcode_void outputTarget();
flowcode_void returnStatement();


//flowcode_void comment();


/* TO_DO: Create ALL constants for keywords (sequence given in table.h) */
/* Constants - unnecessary - already implemented in Scanner.h */
// enum KEYWORDS {
// 	NO_ATTR = -1,
// 	KW_and,
// 	KW_or,
// 	KW_not,
// 	KW_if,
// 	KW_elif,
// 	KW_else,
// 	KW_then,
// 	KW_endif,
// 	KW_repeat,
// 	KW_check,
// 	KW_break,
// 	KW_continue,
// 	KW_Input,
// 	KW_Output,
// 	KW_return,
// 	KW_end,
// 	KW_int,
// 	KW_double,
// 	KW_string,
// 	KW_boolean,
// 	KW_void,
// 	KW_begin,
// 	KW_declaration,
// 	KW_cons,
// };

#endif
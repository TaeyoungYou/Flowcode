/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2025
* Author: Taeyoung You, Juhyeon Oh
* Professors: Khan, Sarah
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
* File name: Compilers.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 Compilers, Lab Section: [303]
* Assignment: A12, A22, A32.
* Date: Jan 26, 2025
* Professor: Khan, Sarah
* Purpose: This file defines the functions called by main function.
* Function list: mainReader(), mainScanner(), mainParser().
*************************************************************/

#ifndef COMPILERS_H_
#define COMPILERS_H_

#define DEBUG 0

/*
 * ............................................................................
 * ADVICE 1:
 * Please check the "TODO" labels to develop your activity.
 *
 * ADVICE 2: This file must be updated according to each assignment
 * (see the progression: reader > scanner > parser).
 * ............................................................................
 */

/* TO_DO: Adjust your language (cannot be "Sofia") */

/* TO_DO: Language name */
#define STR_LANGNAME	"FlowCode"

/* TO_DO: Logical constants - adapt for your language */
#define FLOWCODE_TRUE		1
#define FLOWCODE_FALSE		0
#define FLOWCODE_ERROR		(-1)	/* General error message */

#define FLOWCODE_INVALID	NULL

/*
------------------------------------------------------------
Data types definitions
NOTE: Some types may not be directly used by your language,
		but they can be necessary for conversions.
------------------------------------------------------------
*/

typedef int bool;
#define true 1;
#define false 0;

/* TO_DO: Define your typedefs */
typedef char			flowcode_char;
typedef char*			flowcode_string;
typedef int				flowcode_int;
typedef float			flowcode_float;
typedef void			flowcode_void;

typedef bool			flowcode_bool;
typedef unsigned char	flowcode_byte;

typedef long			flowcode_long;
typedef double			flowcode_double;

/*
------------------------------------------------------------
Programs:
1: Reader - invokes MainReader code
2: Scanner - invokes MainScanner code
3: Parser - invokes MainParser code
------------------------------------------------------------
*/
enum PROGRAMS {
	PGM_READER  = '1',
	PGM_SCANNER = '2',
	PGM_PARSER  = '3'
};

/*
------------------------------------------------------------
Main functions signatures
(Code will be updated during next assignments)
------------------------------------------------------------
*/
flowcode_int mainReader(flowcode_int argc, flowcode_string* argv);
flowcode_int mainScanner(flowcode_int argc, flowcode_string* argv);
flowcode_int mainParser(flowcode_int argc, flowcode_string* argv);

flowcode_void printLogo();

#endif

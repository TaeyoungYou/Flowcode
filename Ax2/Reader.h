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
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 Compilers, Lab Section: [303]
* Assignment: A12.
* Date: Jan 27, 2025
* Professor: Khan, Sarah
* Purpose: This file is the main header for Reader (.h)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#define READER_H_

/* TIP: Do not change pragmas, unless necessary .......................................*/
/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */
/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */
#include <string.h>

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer reader) */
enum READER_MODE {
	MODE_FIXED = 'f', /* Fixed mode (constant size) */
	MODE_ADDIT = 'a', /* Additive mode (constant increment to be added) */
	MODE_MULTI = 'm'  /* Multiplicative mode (constant increment to be multiplied) */
};

/* Constants about controls (not need to change) */
#define READER_TERMINATOR	'\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* You should add your own constant definitions here */
#define READER_MAX_SIZE	INT_MAX-1	/* maximum capacity */ 

#define READER_DEFAULT_SIZE			250		/* default initial buffer reader capacity */
#define READER_DEFAULT_INCREMENT	10		/* default increment factor */

#define NCHAR				128			/* Chars from 0 to 127 */

#define CHARSEOF			(-1)		/* EOF Code for Reader */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (FlowCode) .................................. */

/* TODO: Adjust datatypes */

/* Offset declaration */

/* BITS(7654.3210)*/
#define READER_DEFAULT_FLAG 0b0000 /* (0000.0000)_2 = (000)_10 */
#define FUL 0b0001 /* TO_DO: BIT 0: FUL = Buffer full flag  (0000.0001) */
#define EMP 0b0010 /* TO_DO: BIT 1: EMP = Buffer empty flag (0000.0010) */
#define REL 0b0100 /* TO_DO: BIT 2: REL = Rellocation memory flag (0000.0100) */
#define END 0b1000 /* TO_DO: BIT 3: END = End of buffer flag (0000.1000) */

/* Flag declaration - being changed to use */
typedef struct flag {
	flowcode_bool isEmpty;			/* indicates if the buffer is empty */
	flowcode_bool isFull;			/* indicates if the buffer is full */
	flowcode_bool isRel;			/* indicates if the buffer is reallocation */
	flowcode_bool isEnd;			/* indicates if the buffer is end point */
} Flag;

/* Offset declaration */
typedef struct position {
	flowcode_int wrte;			/* the offset to the add chars (in chars) */
	flowcode_int read;			/* the offset to the get a char position (in chars) */
	flowcode_int mark;			/* the offset to the mark position (in chars) */
} Position;

/* Buffer structure */
typedef struct bufferReader {
	flowcode_string	content;			/* pointer to the beginning of character array (character buffer) */
	flowcode_int	size;				/* current dynamic memory size (in bytes) allocated to character buffer */
	flowcode_int	increment;			/* character array increment factor */
	flowcode_char	mode;				/* operational mode indicator */
	Flag			flags;				/* contains flag bits */
	Position		positions;			/* Offset / position field */
	flowcode_int	histogram[NCHAR];	/* Statistics of chars */
	flowcode_int	numReaderErrors;	/* Number of errors from Reader */
	flowcode_byte	checksum;			/* offset bits for flags */
} Buffer, * BufferPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
BufferPointer	readerCreate		(flowcode_int, flowcode_int, flowcode_char);
BufferPointer	readerAddChar		(BufferPointer const, flowcode_char);
flowcode_bool	readerClear		    (BufferPointer const);
flowcode_bool	readerFree		    (BufferPointer const);
flowcode_bool	readerIsFull		(BufferPointer const);
flowcode_bool	readerIsEmpty		(BufferPointer const);
flowcode_bool	readerSetMark		(BufferPointer const, flowcode_int);
flowcode_int	readerPrint		    (BufferPointer const);
flowcode_int	readerLoad			(BufferPointer const, FILE* const);
flowcode_bool	readerRecover		(BufferPointer const);
flowcode_bool	readerRetract		(BufferPointer const);
flowcode_bool	readerRestore		(BufferPointer const);
flowcode_void	readerCalcChecksum	(BufferPointer const);
flowcode_bool	readerPrintFlags	(BufferPointer const);
flowcode_void	readerPrintStat     (BufferPointer const);
/* Getters */
flowcode_char	readerGetChar		(BufferPointer const);
flowcode_string	readerGetContent	(BufferPointer const, flowcode_int);
flowcode_int	readerGetPosRead	(BufferPointer const);
flowcode_int	readerGetPosWrte	(BufferPointer const);
flowcode_int	readerGetPosMark	(BufferPointer const);
flowcode_int	readerGetSize		(BufferPointer const);
flowcode_int	readerGetInc		(BufferPointer const);
flowcode_char	readerGetMode		(BufferPointer const);
flowcode_int	readerGetNumErrors	(BufferPointer const);

#endif

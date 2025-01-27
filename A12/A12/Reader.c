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
***********************************************************
* File name: Reader.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 Compilers, Lab Section: [303]
* Assignment: A12.
* Date: Jan 27, 2025
* Professor: Khan, Sarah
* Purpose: This file is the main code for Buffer/Reader (A12)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * - Please check the "TODO" labels to develop your activity.
 * - Review the functions to use "Defensive Programming".
 *.............................................................................
 */

#include <ctype.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

 /*
 ***********************************************************
 * Function name: readerCreate
 * Purpose: Creates the buffer reader according to capacity, increment
	 factor and operational mode ('f', 'a', 'm')
 * Author: Taeyoung You
 * History/Versions: S22
 * Called functions: calloc(), malloc()
 * Parameters:
 *   size = initial capacity
 *   increment = increment factor
 *   mode = operational mode
 * Return value: bPointer (pointer to reader)
 * Algorithm: Allocation of memory according to inicial (default) values.
 * TODO ......................................................
 *	- Adjust datatypes for your LANGUAGE.
 *   - Use defensive programming
 *	- Check boundary conditions
 *	- Check flags.
 *************************************************************
 */

BufferPointer readerCreate(flowcode_int size, flowcode_int increment, flowcode_char mode) {
	/* 변수 정의 */
	BufferPointer readerPointer;
	flowcode_int count = 0;

	/* size, increment, mode가 만약 0일 경우, default값으로 초기화 */
	if (!size)
		size = READER_DEFAULT_SIZE;
	if (!increment)
		increment = READER_DEFAULT_INCREMENT;
	if (!mode)
		mode = MODE_FIXED;

	readerPointer = (BufferPointer)calloc(1, sizeof(Buffer));	/* BufferPointer를 0으로 초기화하면서 동적할당 */
	if (!readerPointer) return FLOWCODE_INVALID;				/* 동적할당 실패시, NULL반환 */

	/* readerPointer의 요소들 초기화 */
	/* content 초기화 */
	readerPointer->content = (flowcode_string)malloc(size);		/* 구문(flowcode_string)을 동적할당하고, content에 초기화 */
	if (!readerPointer->content) return FLOWCODE_INVALID;		/* content의 동적할당 실패시, NULL 반환 */
	/* size 초기화 */
	readerPointer->size = size;
	/* increment 초기화 */
	readerPointer->increment = increment;
	/* mode 초기화 */
	readerPointer->mode = mode;
	/* flags 초기화 */
	readerPointer->flags.isEmpty = READER_DEFAULT_FLAG;
	readerPointer->flags.isFull = READER_DEFAULT_FLAG;
	readerPointer->flags.isRead = READER_DEFAULT_FLAG;
	readerPointer->flags.isMoved = READER_DEFAULT_FLAG;
	/* Position 초기화 */
	// readerPointer->positions									/* 일단 초기화 안함 - 잘모르겠음 */
	/* histogram 초기화 */
	for (int count; count < NCHAR; ++count) readerPointer->histogram[count] = 0;	/* NCHAR만큼의 요소들을 0으로 초기화 */
	/* numReaderErrors 초기화 */
	readerPointer->numReaderErrors = FLOWCODE_ERROR;
	/* checksum 초기화 */
	readerPointer->checksum = 1;								/* 읻단 1로 초기화 - 잘모르겠음 */
	/* TO_DO: Initialize flags */
	/* TO_DO: Default checksum */
	return readerPointer;
}


/*
***********************************************************
* Function name: readerAddChar
* Purpose: Adds a char to buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   ch = char to be added
* Return value:
*	readerPointer (pointer to Buffer Reader)
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

BufferPointer readerAddChar(BufferPointer readerPointer, flowcode_char ch) {
	flowcode_string tempReader = FLOWCODE_INVALID;
	flowcode_int newSize = 0;
	flowcode_char tempChar = ' ';
	/* TO_DO: Defensive programming */
	/* TO_DO: Reset Realocation */
	/* TO_DO: Test the inclusion of chars */
	if (readerPointer->positions.wrte * (flowcode_int)sizeof(flowcode_char) < readerPointer->size) {
		/* TO_DO: This buffer is NOT full */
	}
	else {
		/* TO_DO: Reset Full flag */
		switch (readerPointer->mode) {
		case MODE_FIXED:
			/* TO_DO: Update the last position with Terminator */
			break;
		case MODE_ADDIT:
			/* TO_DO: Update size for Additive mode */
			/* TO_DO: Defensive programming */
			break;
		case MODE_MULTI:
			/* TO_DO: Update size for Additive mode */
			/* TO_DO: Defensive programming */
			break;
		default:
			return FLOWCODE_INVALID;
		}
		/* TO_DO: Reallocate */
		/* TO_DO: Defensive programming */
		return readerPointer;
	}
	/* TO_DO: Update the flags */
	readerPointer->content[readerPointer->positions.wrte++] = ch;
	/* TO_DO: Updates histogram */
	return readerPointer;
}

/*
***********************************************************
* Function name: readerClear
* Purpose: Clears the buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
flowcode_bool readerClear(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Adjust the write, mark and read to zero */
	/* TO_DO: Adjust flags */
	return FLOWCODE_TRUE;
}

/*
***********************************************************
* Function name: readerFree
* Purpose: Releases the buffer address
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
flowcode_bool readerFree(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Free pointers */
	return FLOWCODE_TRUE;
}

/*
***********************************************************
* Function name: readerIsFull
* Purpose: Checks if buffer reader is full
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
flowcode_bool readerIsFull(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Check flag if buffer is FUL */
	return 0;
}


/*
***********************************************************
* Function name: readerIsEmpty
* Purpose: Checks if buffer reader is empty.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
flowcode_bool readerIsEmpty(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Check flag if buffer is EMP */
	return 0;
}

/*
***********************************************************
* Function name: readerSetMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
flowcode_bool readerSetMark(BufferPointer const readerPointer, flowcode_int mark) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Adjust mark */
	return FLOWCODE_TRUE;
}


/*
***********************************************************
* Function name: readerPrint
* Purpose: Prints the string in the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars printed.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
flowcode_int readerPrint(BufferPointer const readerPointer) {
	flowcode_int cont = 0;
	flowcode_char c;
	/* TO_DO: Defensive programming (including invalid chars) */
	c = readerGetChar(readerPointer);
	while (cont < readerPointer->positions.wrte) {
		cont++;
		printf("%c", c);
		c = readerGetChar(readerPointer);
	}
	return cont;
}

/*
***********************************************************
* Function name: readerLoad
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   fileDescriptor = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
flowcode_int readerLoad(BufferPointer readerPointer, FILE* const fileDescriptor) {
	flowcode_int size = 0;
	flowcode_char c;
	/* TO_DO: Defensive programming */
	while (!feof(fileDescriptor)) {
		c = (flowcode_char)fgetc(fileDescriptor);
		readerPointer = readerAddChar(readerPointer, c);
		size++;
	}
	/* TO_DO: Defensive programming */
	return size;
}

/*
***********************************************************
* Function name: readerRecover
* Purpose: Rewinds the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
flowcode_bool readerRecover(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Recover positions: read and mark must be zero */
	/* TO_DO: Update flags */
	return FLOWCODE_TRUE;
}


/*
***********************************************************
* Function name: readerRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
flowcode_bool readerRetract(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Retract (return 1 pos read) */
	return FLOWCODE_TRUE;
}


/*
***********************************************************
* Function name: readerRestore
* Purpose: Resets the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
flowcode_bool readerRestore(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Restore positions (read to mark) */
	return FLOWCODE_TRUE;
}



/*
***********************************************************
* Function name: readerGetChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Char in the getC position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
flowcode_char readerGetChar(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Check condition to read/wrte */
	return readerPointer->content[readerPointer->positions.read++];
}


/*
***********************************************************
* Function name: readerGetContent
* Purpose: Returns the pointer to String.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   pos = position to get the pointer
* Return value:
*	Position of string char.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
flowcode_string readerGetContent(BufferPointer const readerPointer, flowcode_int pos) {
	/* TO_DO: Defensive programming */
	return readerPointer->content + pos;
}



/*
***********************************************************
* Function name: readerGetPosRead
* Purpose: Returns the value of getCPosition.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The read position offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
flowcode_int readerGetPosRead(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return read */
	return 0;
}


/*
***********************************************************
* Function name: readerGetPosWrte
* Purpose: Returns the position of char to be added
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Write position
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
flowcode_int readerGetPosWrte(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return wrte */
	return 0;
}


/*
***********************************************************
* Function name: readerGetPosMark
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Mark position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
flowcode_int readerGetPosMark(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return mark */
	return 0;
}


/*
***********************************************************
* Function name: readerGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Size of buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
flowcode_int readerGetSize(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return size */
	return 0;
}

/*
***********************************************************
* Function name: readerGetInc
* Purpose: Returns the buffer increment.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The Buffer increment.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
flowcode_int readerGetInc(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return increment */
	return 0;
}

/*
***********************************************************
* Function name: readerGetMode
* Purpose: Returns the operational mode
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Operational mode.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
flowcode_char readerGetMode(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return mode */
	return '\0';
}

/*
***********************************************************
* Function name: readerShowStat
* Purpose: Shows the char statistic.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value: (Void)
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
flowcode_void readerPrintStat(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Updates the histogram */
}

/*
***********************************************************
* Function name: readerNumErrors
* Purpose: Returns the number of errors found.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of errors.
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
flowcode_int readerGetNumErrors(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Returns the number of errors */
	return 0;
}

/*
***********************************************************
* Function name: readerCalcChecksum
* Purpose: Calculates the checksum of the reader (8 bits).
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	[None]
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

flowcode_void readerCalcChecksum(BufferPointer readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Calculate checksum */
}

/*
***********************************************************
* Function name: readerPrintFlags
* Purpose: Sets the checksum of the reader (4 bits).
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	[None]
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

flowcode_bool readerPrintFlags(BufferPointer readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Shows flags */
	return FLOWCODE_TRUE;
}

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

	readerPointer = (BufferPointer)calloc(1, sizeof(Buffer));	/* BufferPointer를 동적할당 */
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
	/* Position 초기화 - 일단 각 요소 0으로 초기화 */
	readerPointer->positions.wrte = 0;
	readerPointer->positions.read = 0;
	readerPointer->positions.mark = 0;
	/* histogram 초기화 */
	for (count = 0; count < NCHAR; ++count) readerPointer->histogram[count] = 0;	/* NCHAR만큼의 요소들을 0으로 초기화 */
	/* numReaderErrors 초기화 */
	readerPointer->numReaderErrors = FLOWCODE_ERROR;
	/* checksum 초기화 - 일단 0로 초기화 (잘 모르겠음) */
	readerPointer->checksum = 0;

	return readerPointer;
}


/*
***********************************************************
* Function name: readerAddChar
* Purpose: Adds a char to buffer reader
* Author: -
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
* Author: Taeyoung You
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
	/* 변수 할당 */
	int i;

	/* 포인터 상수이지만 그래도 NULL을 가리키는 포인터인지 확인 및 안에 내용 중 동적 할당이 되어 있는지 확인 */
	if (!readerPointer && !readerPointer->content) return FLOWCODE_FALSE;

	/* 구조체 요소들 초기화 */
	memset(readerPointer->content, 0, readerPointer->size);
	readerPointer->size = READER_DEFAULT_SIZE;
	readerPointer->increment = READER_DEFAULT_INCREMENT;
	readerPointer->mode = MODE_FIXED;
	readerPointer->flags.isEmpty = READER_DEFAULT_FLAG;
	readerPointer->flags.isFull = READER_DEFAULT_FLAG;
	readerPointer->flags.isRead = READER_DEFAULT_FLAG;
	readerPointer->flags.isMoved = READER_DEFAULT_FLAG;
	readerPointer->positions.wrte = 0;
	readerPointer->positions.read = 0;
	readerPointer->positions.mark = 0;
	for (i = 0; i < NCHAR; ++i) readerPointer->histogram[i] = 0;
	readerPointer->numReaderErrors = FLOWCODE_ERROR;
	readerPointer->checksum = 0;

	return FLOWCODE_TRUE;
}

/*
***********************************************************
* Function name: readerFree
* Purpose: Releases the buffer address
* Author: Taeyoung You
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
	/* 포인터 상수이지만 그래도 NULL을 가리키는 포인터인지 확인 및 안에 내용 중 동적 할당이 되어 있는지 확인 */
	if (!readerPointer && !readerPointer->content) return FLOWCODE_FALSE;

	/* 동적 할당 해제 */
	free(readerPointer->content);
	free(readerPointer);
	return FLOWCODE_TRUE;
}

/*
***********************************************************
* Function name: readerIsFull
* Purpose: Checks if buffer reader is full
* Author: Taeyoung You
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
	/* readerPointer가 유효하지 않는 값을 가리킬때 (NULL) */
	if (!readerPointer) return FLOWCODE_FALSE;
	/* flag의 isFull의 boolean값을 보고 판단 */
	return readerPointer->flags.isFull;
}


/*
***********************************************************
* Function name: readerIsEmpty
* Purpose: Checks if buffer reader is empty.
* Author: Taeyoung You
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
	/* readerPointer가 유효하지 않는 값을 가리킬때 (NULL) */
	if (!readerPointer) return FLOWCODE_FALSE;
	/* flag의 isEmpty의 boolean값을 보고 판단 */
	return readerPointer->flags.isEmpty;
}

/*
***********************************************************
* Function name: readerSetMark
* Purpose: Adjust the position of mark in the buffer
* Author: Taeyoung You
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
	/* 변수 할당 */
	flowcode_int currentWrte;
	/* 유효한 BufferPointer인지 확인 */
	if (!readerPointer)	return FLOWCODE_FALSE;

	/* 현재 Position의 Wrte값 가져오기 */
	currentWrte = readerGetPosWrte(readerPointer);
	/* 0 ~ Wrte인지 확인 (Valid한 값인지) 후, set */
	if (0 <= mark && mark <= currentWrte) readerPointer->positions.mark = mark;
	return FLOWCODE_TRUE;
}


/*
***********************************************************
* Function name: readerPrint
* Purpose: Prints the string in the buffer.
* Author: Juhyeon Oh
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
	if (!readerPointer) /* check if the pointer is invalid */
		return FLOWCODE_ERROR;

	while (!(readerPointer->checksum & END)) {/* check if the buffer reaches the end of the file */
		c = readerGetChar(readerPointer);
		if (c == CHARSEOF) {
			break;
		}
		printf("%c", c); /* print character that was jsut read */
		cont++; /* increase the number of char printed (using as a tracker) */
	}
	return cont; /* return the number of char */
}

/*
***********************************************************
* Function name: readerLoad
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Author: Juhyeon Oh
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
	if (!readerPointer || !fileDescriptor) /* Check if readerPointer exists and file is valid */
		return FLOWCODE_ERROR;

	while (!feof(fileDescriptor)) { /* read each character until the end of file */
		c = (flowcode_char)fgetc(fileDescriptor); /* store each character from the file into the variable c */

		if (!readerAddChar(readerPointer, c)){
			ungetc(c, fileDescriptor); /* delete the invalid character and reset the read pointer to the previous one */
			break;
		}
		readerPointer = readerAddChar(readerPointer, c); /* apprend the value of variable c into the reader buffer */
		size++; /* increase the size of buffer */
	}
	/* TO_DO: Defensive programming */
	return size;
}

/*
***********************************************************
* Function name: readerRecover
* Purpose: Rewinds the buffer.
* Author: Juhyeon Oh
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
	if (!readerPointer) /* check if readerPointer doesn't exist */
		return FLOWCODE_FALSE;
	/* TO_DO: Recover positions: read and mark must be zero */
	readerPointer->positions.read == 0; /* if readerPointer exist, it reset read and mark offset to 0 */
	readerPointer->positions.mark == 0;
	/* TO_DO: Update flags */
	return FLOWCODE_TRUE;
}


/*
***********************************************************
* Function name: readerRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Author: Juhyeon Oh
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
	if (!readerPointer) /* bufferPointer cannot be NULL(check valiation) */
		return FLOWCODE_FALSE;
	if (readerGetPosRead(readerPointer) < 0) /* Read pointer must be greater than starting point(0) */
		return FLOWCODE_FALSE;
	/* TO_DO: Retract (return 1 pos read) */
	readerPointer->positions.read--; /* Decrease the read pointer by 1 */
	return FLOWCODE_TRUE;
}


/*
***********************************************************
* Function name: readerRestore
* Purpose: Resets the buffer.
* Author: Juhyeon Oh
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
	if (!readerPointer) /* validate invalid value in readerPointer */
		return FLOWCODE_FALSE;
	if (readerGetPosMark(readerPointer) < 0 || readerGetPosMark(readerPointer) > readerGetPosWrte(readerPointer)) /* check if the mark offset is between 0 and current wrte */
		return FLOWCODE_FALSE;
	/* TO_DO: Restore positions (read to mark) */
	readerPointer->positions.read = readerGetPosMark(readerPointer);
	return FLOWCODE_TRUE;
}



/*
***********************************************************
* Function name: readerGetChar
* Purpose: Returns the char in the getC position.
* Author: Juhyeon Oh
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
	if (!readerPointer)
		return CHARSEOF; /* BufferPointer must exist but cannot return NULL bc the return type is flowcode_char */

	/* TO_DO: Check condition to read/wrte */
	if (readerPointer->positions.read == readerPointer->positions.wrte) { /* means END OF FILE */
		readerPointer->checksum |= END;
		return '\0';
	}
	return readerPointer->content[readerPointer->positions.read++]; /* return the char that poninter currently points to then increase the postion of read */
}


/*
***********************************************************
* Function name: readerGetContent
* Purpose: Returns the pointer to String.
* Author: Juhyeon Oh
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
	if (!readerPointer) /* if readerPointer is invalid, it returns NULL */
		return FLOWCODE_INVALID;
	if (pos < 0 || pos > readerPointer->positions.wrte) /* Check position is within valid range(positive integer & smaller than current wrte position) */
		return FLOWCODE_INVALID; 
	return readerPointer->content + pos; /* return position of content pointing to */
}



/*
***********************************************************
* Function name: readerGetPosRead
* Purpose: Returns the value of getCPosition.
* Author: Juhyeon Oh
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
	if (!readerPointer) /* if readerPointer is invalid, it returns error(-1) */
		return FLOWCODE_ERROR;
	/* TO_DO: Return read */
	return readerPointer->positions.read;
}


/*
***********************************************************
* Function name: readerGetPosWrte
* Purpose: Returns the position of char to be added
* Author: Juhyeon Oh
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
	if (!readerPointer)
		return FLOWCODE_ERROR; /* if the return pointer doesn't exist, it will return error(-1) */
	/* TO_DO: Return wrte */
	return readerPointer->positions.wrte;
}


/*
***********************************************************
* Function name: readerGetPosMark
* Purpose: Returns the position of mark in the buffer
* Author: Juhyeon Oh
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
	if (!readerPointer)
		return FLOWCODE_ERROR; /* if the return pointer doesn't exist, it will return error(-1) */
	/* TO_DO: Return mark */
	return readerPointer->positions.mark; 
}


/*
***********************************************************
* Function name: readerGetSize
* Purpose: Returns the current buffer capacity
* Author: Juhyeon Oh
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
	if (!readerPointer) /* if readerPointer is invalid, it returns error(-1) */
		return FLOWCODE_ERROR;
	/* TO_DO: Return size */
	return readerPointer->size;
}

/*
***********************************************************
* Function name: readerGetInc
* Purpose: Returns the buffer increment.
* Author: Juhyeon Oh
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
	if (!readerPointer) /* if readerPointer is invalid, it returns error(-1) */
		return FLOWCODE_ERROR;
	/* TO_DO: Return increment */
	return readerPointer->increment;
}

/*
***********************************************************
* Function name: readerGetMode
* Purpose: Returns the operational mode
* Author: Juhyeon Oh
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
	if (!readerPointer) /* if readerPointer is invalid, it returns CHARSEOF (-1) */
		return CHARSEOF;
	/* TO_DO: Return mode */
	return readerPointer->mode;
}

/*
***********************************************************
* Function name: readerShowStat
* Purpose: Shows the char statistic.
* Author: Juhyeon Oh
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
	if (!readerPointer) return; /* check if the buffer points to NULL */
	/* TO_DO: Updates the histogram */
	printf("Reader statistics:\n");

	flowcode_int count = 0; /* Counter to track the number of printed items (Max 10) */

	/* Loop through all ASCII characters (0 to NCHAR-1) */
	for (flowcode_int i = 0; i < NCHAR; i++) {
		if (readerPointer->histogram[i] > 0) { /*  Only print characters that appeared at least once */
			if (0 <= i || i <= 127) {
				printf("B[%c]=%d", i, readerPointer->histogram[i]); /* Print the character using a required format (i.e.B[a]=7)*/
			}

			count++;

			if (count % 10 == 0) { /* Print a newline after every 10 elements */
				printf("\n");
			}
			else {
				printf(","); /* Separate elements with a comma */
			}
		}
	}
}

/*
***********************************************************
* Function name: readerNumErrors
* Purpose: Returns the number of errors found.
* Author: Juhyeon Oh
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
	if (!readerPointer) /* if the pointer is invalid return error */
		return FLOWCODE_ERROR; 
	/* TO_DO: Returns the number of errors */
	return readerPointer->numReaderErrors; 
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
* Author: Juhyeon Oh
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
	if (!readerPointer) /* check if the buffer points to NULL */
		return FLOWCODE_FALSE;
	/* TO_DO: Shows flags */
	/* Print the status of each flag using bitwise operations */
	printf("FUL offset: %d", (readerPointer->checksum & FUL)? FLOWCODE_TRUE: FLOWCODE_FALSE); /* Check if the 'FUL' (Buffer Full) flag is set */
	printf("EMP offset: %d", (readerPointer->checksum & EMP)? FLOWCODE_TRUE: FLOWCODE_FALSE); /* Check if the 'EMP' (Buffer Empty) flag is set */
	printf("REL offset: %d", (readerPointer->checksum & REL)? FLOWCODE_TRUE: FLOWCODE_FALSE); /* Check if the 'REL' (Buffer Relocate) flag is set */
	printf("END offset: %d", (readerPointer->checksum & END)? FLOWCODE_TRUE: FLOWCODE_FALSE); /* Check if the 'END' (Buffer End) flag is set */

	return FLOWCODE_TRUE;
}

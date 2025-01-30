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

 /* ASCII CODE TABLE */
const flowcode_string ascii_table[NCHAR] = {
		"NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL",
		"BS", "TAB", "LF", "VT", "FF", "CR", "SO", "SI",
		"DLE", "DC1", "DC2", "DC3", "DC4", "NAK", "SYN", "ETB",
		"CAN", "EM", "SUB", "ESC", "FS", "GS", "RS", "US",
		"SP", "!", "\"", "#", "$", "%", "&", "'",
		"(", ")", "*", "+", ",", "-", ".", "/",
		"0", "1", "2", "3", "4", "5", "6", "7",
		"8", "9", ":", ";", "<", "=", ">", "?",
		"@", "A", "B", "C", "D", "E", "F", "G",
		"H", "I", "J", "K", "L", "M", "N", "O",
		"P", "Q", "R", "S", "T", "U", "V", "W",
		"X", "Y", "Z", "[", "\\", "]", "^", "_",
		"`", "a", "b", "c", "d", "e", "f", "g",
		"h", "i", "j", "k", "l", "m", "n", "o",
		"p", "q", "r", "s", "t", "u", "v", "w",
		"x", "y", "z", "{", "|", "}", "~", "DEL"
};

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
	flowcode_int count;

	/* size, increment, mode가 만약 0일 경우, default값으로 초기화 */
	if (size <= 0)
		size = READER_DEFAULT_SIZE;
	if (increment <= 0)
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
	readerPointer->flags.isEmpty = FLOWCODE_TRUE;
	readerPointer->flags.isFull = FLOWCODE_FALSE;
	readerPointer->flags.isRel = FLOWCODE_FALSE;
	readerPointer->flags.isEnd = FLOWCODE_FALSE;
	/* Position 초기화 - 일단 각 요소 0으로 초기화 */
	readerPointer->positions.wrte = 0;
	readerPointer->positions.read = 0;
	readerPointer->positions.mark = 0;
	/* histogram 초기화 */
	for (count = 0; count < NCHAR; ++count) readerPointer->histogram[count] = 0;	/* NCHAR만큼의 요소들을 0으로 초기화 */
	/* numReaderErrors 초기화 */
	readerPointer->numReaderErrors = 0;
	/* checksum 초기화 */
	readerPointer->checksum = READER_DEFAULT_FLAG;

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
	/* arguments의 값 확인 */
	if (!readerPointer) return FLOWCODE_INVALID;
	if (ch < 0 || NCHAR <= ch) return FLOWCODE_INVALID;
	/* TO_DO: Reset Realocation */
	/* TO_DO: Test the inclusion of chars */
	if (readerPointer->positions.wrte * (flowcode_int)sizeof(flowcode_char) < readerGetSize(readerPointer)) {
		readerPointer->flags.isFull = FLOWCODE_FALSE;
	}
	else {
		/* 현재 상태는 FULL 또는 그 이상이기 때문에 Flag 설정 */
		readerPointer->flags.isFull = FLOWCODE_TRUE;
		/* MODE에 따라 재할당 방식이 바뀜 */
		switch (readerPointer->mode) {
		case MODE_FIXED:				/* 재할당 불가: constant size */
			return FLOWCODE_INVALID;
		case MODE_ADDIT:				/* 재할당 가능: 선형적으로 증가 */
			newSize = readerGetSize(readerPointer) + readerGetInc(readerPointer);
			if (newSize < readerGetSize(readerPointer)) return FLOWCODE_INVALID;
			break;
		case MODE_MULTI:				/* 재할당 가능: 곱으로 증가*/
			newSize = readerGetSize(readerPointer) * readerGetInc(readerPointer);
			if (newSize < readerGetSize(readerPointer)) return FLOWCODE_INVALID;
			break;
		default:
			return FLOWCODE_INVALID;
		}
		tempReader = realloc(readerPointer->content, newSize);
		/* 혹시 Scanner나 Parser할때, 중요할 부분 같애서 comment 남김 */
		/* 새로운 사이즈로 재할당을 할때, 힙 메모리에서 공간부족으로 NULL이 반환이 된다면 readerPointer->flags.isRel을 TRUE로 바꿔야 함 */
		/* 이런 상황이 생긴다면 새로운 메모리에 할당 후, 이 isRel플래그를 인지하여 안에 있는 값들을 새로운 메모리에 옮겨야 함 */
		if (!tempReader) return FLOWCODE_INVALID;

		/* 새로 할당한 메모리 및 사이즈를 정의 */
		readerPointer->content = tempReader;
		readerPointer->size = newSize;
		readerPointer->flags.isFull = FLOWCODE_FALSE;
	}
	/* 그러다면, 여기선 memory가 여유가 있을 때 ch를 handle한다는 건데 */
	
	readerPointer->content[readerPointer->positions.wrte++] = ch;
	readerPointer->histogram[ch]++;
	readerPointer->flags.isEmpty = FLOWCODE_FALSE;

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
	if (!readerPointer) return FLOWCODE_FALSE;
	/* 구조체 요소들 초기화 */
	memset(readerPointer->content, 0, readerPointer->size);
	readerPointer->size = READER_DEFAULT_SIZE;
	readerPointer->increment = READER_DEFAULT_INCREMENT;
	readerPointer->mode = MODE_FIXED;
	readerPointer->flags.isEmpty = FLOWCODE_TRUE;
	readerPointer->flags.isFull = FLOWCODE_FALSE;
	readerPointer->flags.isRel = FLOWCODE_FALSE;
	readerPointer->flags.isEnd = FLOWCODE_FALSE;
	readerPointer->positions.wrte = 0;
	readerPointer->positions.read = 0;
	readerPointer->positions.mark = 0;
	for (i = 0; i < NCHAR; ++i) readerPointer->histogram[i] = 0;
	readerPointer->numReaderErrors = 0;
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
	if (!readerPointer) return FLOWCODE_FALSE;

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
	/* 범위 밖의 mark 포지션이면 false */
	if (mark < 0 || currentWrte < mark) return FLOWCODE_FALSE;

	readerPointer->positions.mark = mark;
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
	flowcode_int count = 0;
	flowcode_char c;

	if (!readerPointer) return FLOWCODE_ERROR;

	/* TO_DO: Defensive programming (including invalid chars) */
	while (count < readerPointer->positions.wrte) {
		c = readerGetChar(readerPointer);
		printf("%c", c);
		count++;
	}
	return readerPointer->positions.read;
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
	BufferPointer tempPointer;
	flowcode_char c;
	/* TO_DO: Defensive programming */
	if (!readerPointer || !fileDescriptor) /* Check if readerPointer exists and file is valid */
		return FLOWCODE_ERROR;

	/* back up */
	tempPointer = readerPointer;

	while (!feof(fileDescriptor)) { /* read each character until the end of file */
		c = (flowcode_char)fgetc(fileDescriptor); /* store each character from the file into the variable c */

		/* apprend the value of variable c into the reader buffer */
		if (!(tempPointer = readerAddChar(readerPointer, c))){
			ungetc(c, fileDescriptor); /* delete the invalid character and reset the read pointer to the previous one */
			break;
		}
		readerPointer = tempPointer;
	}
	/* TO_DO: Defensive programming */
	return readerPointer->positions.wrte;
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
	readerPointer->positions.read = 0; /* if readerPointer exist, it reset read and mark offset to 0 */
	readerPointer->positions.mark = 0;
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
	if (readerGetPosRead(readerPointer) <= 0) /* Read pointer must be greater than starting point(0) */
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
		readerPointer->flags.isEnd=FLOWCODE_TRUE; /* created code with bitwise offset flags END or bitwise operator */
		return READER_TERMINATOR;
	}
	return readerPointer->content[++readerPointer->positions.read]; /* return the char that poninter currently points to then increase the postion of read */
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
	flowcode_int i;
	/* TO_DO: Defensive programming */
	if (!readerPointer) return;
	/* TO_DO: Updates the histogram */
	for (i = 0; i < NCHAR; ++i) {
		printf("B[%-3s]=%-2d\t", ascii_table[i], readerPointer->histogram[i]);
		if ((i+1) % 8 == 0) printf("\n");
	}
	printf("\n");
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
	printf("\t* FUL offset: %d\n", readerPointer->flags.isFull); /* Check if the 'FUL' (Buffer Full) flag is set */
	printf("\t* EMP offset: %d\n", readerPointer->flags.isEmpty); /* Check if the 'EMP' (Buffer Empty) flag is set */
	printf("\t* REL offset: %d\n", readerPointer->flags.isRel); /* Check if the 'REL' (Buffer Relocate) flag is set */
	printf("\t* END offset: %d\n", readerPointer->flags.isEnd); /* Check if the 'END' (Buffer End) flag is set */

	return FLOWCODE_TRUE;
}

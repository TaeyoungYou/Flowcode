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
	/* Variable definitions */
	BufferPointer readerPointer;
	flowcode_int count;

	/* If size, increment, or mode is 0, initialize them with default values */
	if (size <= 0)
		size = READER_DEFAULT_SIZE;
	if (increment <= 0)
		increment = READER_DEFAULT_INCREMENT;
	if (!mode)
		mode = MODE_FIXED;

	readerPointer = (BufferPointer)calloc(1, sizeof(Buffer));	/* Dynamically allocate memory for readerPointer */
	if (!readerPointer) return FLOWCODE_INVALID;				/* Returns NULL, if memory allocation fails */

	/* Initialize the elements of readerPointer */
	/* Initialize content */
	readerPointer->content = (flowcode_string)malloc(size * sizeof(flowcode_char));		/* Dynamically allocate memory for the statement (flowcode_string) and initialize content */
	if (!readerPointer->content) return FLOWCODE_INVALID;		/* Return NULL if memory allocation for content fails  */
	/* Initialize size */
	readerPointer->size = size;
	/* Initialize increment */
	readerPointer->increment = increment;
	/* initialize mode */
	readerPointer->mode = mode;
	/* Initalize flags */
	readerPointer->flags.isEmpty = FLOWCODE_TRUE;
	readerPointer->flags.isFull = FLOWCODE_FALSE;
	readerPointer->flags.isRel = FLOWCODE_FALSE;
	readerPointer->flags.isEnd = FLOWCODE_FALSE;
	/* Initialize position */
	readerPointer->positions.wrte = 0;
	readerPointer->positions.read = -1;
	readerPointer->positions.mark = 0;
	/* Initialize histogram */
	for (count = 0; count < NCHAR; ++count) readerPointer->histogram[count] = 0;	/* Initialize NCHAR elements to 0 */
	/* Initialize numReaderErrors */
	readerPointer->numReaderErrors = 0;
	/* Initialize checksum */
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

	/* Validate the arguments */ 
	if (!readerPointer) return FLOWCODE_INVALID; /* Return FLOWCODE_INVALID if readerPointer is NULL */
	if (ch < 0 || NCHAR <= ch) return FLOWCODE_INVALID; /* Return FLOWCODE_INVALID if ch is out of valid range */
	
	/* TO_DO: Reset Realocation */
	/* TO_DO: Test the inclusion of chars */
	
	/* Check if there is enough space to add a new character */
	if ((readerPointer->positions.wrte * (flowcode_int)sizeof(flowcode_char)) + 1 < readerGetSize(readerPointer)) {
		readerPointer->flags.isFull = FLOWCODE_FALSE; /* Mark buffer as not full */
	}
	else {
		/* Buffer is full or exceeds its current size, so update the flag */
		readerPointer->flags.isFull = FLOWCODE_TRUE;

		/* Reallocation strategy depends on the mode */
		switch (readerPointer->mode) {
		case MODE_FIXED:				 /* No reallocation allowed: constant size */
			return FLOWCODE_INVALID;
		case MODE_ADDIT:				/* Reallocation allowed: increase size linearly */
			newSize = readerGetSize(readerPointer) + readerGetInc(readerPointer);
			if (newSize < readerGetSize(readerPointer)) return FLOWCODE_INVALID; /* Prevent overflow */
			break;
		case MODE_MULTI:				/* Reallocation allowed: increase size exponentially */
			newSize = readerGetSize(readerPointer) * readerGetInc(readerPointer);
			if (newSize < readerGetSize(readerPointer)) return FLOWCODE_INVALID; /* Prevent overflow */
			break;
		default:
			return FLOWCODE_INVALID; /* Invalid mode */
		}
		tempReader = realloc(readerPointer->content, newSize);
		
		/* Important note for Scanner or Parser handling If memory reallocation fails due to insufficient heap space,
		readerPointer->flags.isRel should be set to TRUE. If this situation occurs, a new memory allocation should be performed,
		and the data from the previous memory should be transferred accordingly */
		if (!tempReader) return FLOWCODE_INVALID;

		/* Update readerPointer with the newly allocated memory and size */
		readerPointer->content = tempReader;
		readerPointer->size = newSize;
		readerPointer->flags.isFull = FLOWCODE_FALSE;  /* Buffer is no longer full */
		readerPointer->flags.isRel = FLOWCODE_TRUE; /* Indicates reallocation occurred */

		return readerPointer;
	}
	/* If there is enough memory, handle character insertion */
	
	/* Store the character in the buffer at the write position */
	readerPointer->content[readerPointer->positions.wrte++] = ch;
	readerPointer->histogram[ch]++; /* Update histogram count for the inserted character */
	readerPointer->flags.isEmpty = FLOWCODE_FALSE; /* Mark the buffer as not empty */

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
	/* Variable definition */
	int i;

	/* Check if the pointer is NULL and ensure dynamic memory is allocated */
	if (!readerPointer) return FLOWCODE_FALSE;
	
	/* Initialize struct elements */
	memset(readerPointer->content, 0, readerPointer->size); /* Clear content buffer */
	readerPointer->size = READER_DEFAULT_SIZE;				/* Reset size to default */
	readerPointer->increment = READER_DEFAULT_INCREMENT;	/* Reset increment value */
	readerPointer->mode = MODE_FIXED;						/* Set mode to fixed */
	
	/* Reset flag values */
	readerPointer->flags.isEmpty = FLOWCODE_TRUE;			/* Mark buffer as empty */
	readerPointer->flags.isFull = FLOWCODE_FALSE;			/* Mark buffer as not full */
	readerPointer->flags.isRel = FLOWCODE_FALSE;			/* Reset reallocation flag */
	readerPointer->flags.isEnd = FLOWCODE_FALSE;			/* Reset end-of-buffer flag */

	/* Reset position indicators */
	readerPointer->positions.wrte = 0;						/* Reset write position */
	readerPointer->positions.read = -1;						/* Reset read position */
	readerPointer->positions.mark = 0;						/* Reset mark position */

	for (i = 0; i < NCHAR; ++i) readerPointer->histogram[i] = 0; /* Clear character histogram */
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
	/* Check if the pointer is NULL to ensure that dynamic memory has been allocated */
	if (!readerPointer) return FLOWCODE_FALSE;

	/* Free dynamically allocated memory for content */
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
	/* Check if readerPointer is NULL (invalid pointer) */
	if (!readerPointer) return FLOWCODE_FALSE;
	/* Return the boolean value of the isFull flag */
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
	/* Check if readerPointer is NULL (invalid pointer) */
	if (!readerPointer) return FLOWCODE_FALSE;
	/* Return the boolean value of the isEmpty flag */
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
	/* Variable declaration */
	flowcode_int currentWrte;
	
	/* Check if the BufferPointer is valid */
	if (!readerPointer)	return FLOWCODE_FALSE;

	/* Get the current write position */
	currentWrte = readerGetPosWrte(readerPointer);

	/* Return false if the mark position is out of range */
	if (mark < 0 || currentWrte < mark) return FLOWCODE_FALSE;

	readerPointer->positions.mark = mark; /* Set the mark position */
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
	/* Variable declaration */
	flowcode_int count = 0;
	flowcode_char c;

	/* Check if readerPointer is NULL (invalid pointer) */
	if (!readerPointer) return FLOWCODE_ERROR;

	/* TO_DO: Defensive programming (including invalid chars) */
	while (count < readerPointer->positions.wrte) {
		/* Retrieve the next character from the reader */
		c = readerGetChar(readerPointer);
  		printf("%c", c);	/* Print the character */
		count++;			/* Increment the counter */
	}
	return readerPointer->positions.read; /* Return the current read position */
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
	/* Variable declaration */
	BufferPointer tempPointer;
	flowcode_char c;
	/* TO_DO: Defensive programming */
	if (!readerPointer || !fileDescriptor) /* Check if readerPointer exists and file is valid */
		return FLOWCODE_ERROR;

	/* Backup the original readerPointer */
	tempPointer = readerPointer;

	while (!feof(fileDescriptor)) { /* Eead each character until the end of file */
		c = (flowcode_char)fgetc(fileDescriptor); /* Read a character from the file and store it in variable c */

		/* Apprend the value of variable c into the reader buffer */
		if (!(tempPointer = readerAddChar(readerPointer, c))){
			ungetc(c, fileDescriptor); /* Remove the invalid character and reset the read pointer to the previous one */
			break;
		}
		/* If memory reallocation has occurred, reassign the buffer pointer */
		if (tempPointer->flags.isRel) {
			tempPointer = readerAddChar(readerPointer, c);
			tempPointer->flags.isRel = FLOWCODE_FALSE;
		}

		/* Update readerPointer */
		readerPointer = tempPointer;
	}
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
	if (!readerPointer) /* Check if readerPointer doesn't exist */
		return FLOWCODE_FALSE;
	/* TO_DO: Recover positions: read and mark must be zero */
	readerPointer->positions.read = -1; /* If readerPointer exist, it reset read and mark offset */
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
	if (!readerPointer) /* BufferPointer cannot be NULL(check valiation) */
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
	if (!readerPointer) /*  Validate if readerPointer is NULL (invalid pointer) */
		return FLOWCODE_FALSE;

	/* Check if the mark position is within the valid range (between 0 and the current write position) */
	if (readerGetPosMark(readerPointer) < 0 || readerGetPosMark(readerPointer) > readerGetPosWrte(readerPointer))
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
	flowcode_char ch;
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return CHARSEOF; /* BufferPointer must exist but cannot return NULL bc the return type is flowcode_char BufferPointer must exist, 
							but cannot return NULL since the return type is flowcode_char */

	/* Retrieve the next character from the buffer */
	ch = readerPointer->content[++readerPointer->positions.read];

	/* TO_DO: Check condition to read/wrte */
	/* If the read position reaches the write position, it indicates the end of the buffer (EOF) */
	if (readerPointer->positions.read + 1 == readerPointer->positions.wrte) { /* means END OF FILE */
		readerPointer->flags.isEnd = FLOWCODE_TRUE; /* Flag indicating EOF using bitwise offset or operator */
		return READER_TERMINATOR;/* Return the termination character */
	}
	return ch; /* return the char that poninter currently points to then increase the postion of read */
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
	if (!readerPointer) /* If readerPointer is invalid, it returns NULL */
		return FLOWCODE_INVALID;
	if (pos < 0 || pos > readerPointer->positions.wrte) /* Check position is within valid range(positive integer & smaller than current wrte position) */
		return FLOWCODE_INVALID; 
	return readerPointer->content + pos; /* Return position of content pointing to */
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
	if (!readerPointer) /* If readerPointer is invalid, it returns error(-1) */
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
		return FLOWCODE_ERROR; /* If the return pointer doesn't exist, it will return error(-1) */
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
		return FLOWCODE_ERROR; /* If the return pointer doesn't exist, it will return error(-1) */
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
	if (!readerPointer) /* If readerPointer is invalid, it returns error(-1) */
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
	if (!readerPointer) /* If readerPointer is invalid, it returns error(-1) */
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
	if (!readerPointer) /* If readerPointer is invalid, it returns CHARSEOF (-1) */
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
	if (!readerPointer) return;  /* Check if readerPointer is NULL; if so, return without processing */
	/* TO_DO: Updates the histogram */
	for (i = 0; i < NCHAR; ++i) {
		/* Print the character's histogram count using the ASCII table reference */
		printf("B[%-3s]=%-2d\t", ascii_table[i], readerPointer->histogram[i]);

		/* Print a newline after every 8 entries for better readability */
		if ((i+1) % 8 == 0) printf("\n");
	}
	/* Print a final newline for output formatting */
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
	if (!readerPointer) /* If the pointer is invalid return error */
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
	if (!readerPointer) /* Check if the buffer points to NULL */
		return FLOWCODE_FALSE;
	/* TO_DO: Shows flags */
	/* Print the status of each flag using bitwise operations */
	printf("\t* FUL offset: %d\n", readerPointer->flags.isFull); /* Check if the 'FUL' (Buffer Full) flag is set */
	printf("\t* EMP offset: %d\n", readerPointer->flags.isEmpty); /* Check if the 'EMP' (Buffer Empty) flag is set */
	printf("\t* REL offset: %d\n", readerPointer->flags.isRel); /* Check if the 'REL' (Buffer Relocate) flag is set */
	printf("\t* END offset: %d\n", readerPointer->flags.isEnd); /* Check if the 'END' (Buffer End) flag is set */

	return FLOWCODE_TRUE;
}

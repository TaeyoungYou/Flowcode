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
* File name: Compilers.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 Compilers, Lab Section: [303]
* Assignment: A12, A22, A32.
* Date: Jan 26, 2025
* Professor: Khan, Sarah
* Purpose: This file is the main program of Compilers Project
* Function list: main().
************************************************************
*/


#include <stdio.h>
#include <stdlib.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

/*
 * ............................................................................
 * ADVICE 1:
 * Please check the "TODO" labels to develop your activity.
 *
 * ADVICE 2: This file must be updated according to each assignment
 * (see the progression: reader > scanner > parser).
 * ............................................................................
 */

/*
***********************************************************
* Function name: main
* Purpose: Main function
* Author: Khan, Sarah
* History/Versions: Ver F22
* Called functions: mainReader(), mainScanner(), mainParser()
* Parameters: Command line arguments - argc, argv
* Return value: Status
* Algorithm: -
*************************************************************
*/

flowcode_int main(int argc, char** argv) {
	flowcode_int i;
	printLogo();
	if (DEBUG) {
		for (i = 0; i < argc; ++i)
			printf("argv[%d] = %s\n", i, argv[i]);
	}
	if (argc < 2) {
		printf("%s%c%s%c%s%c%s", "OPTIONS:\n* [",
			PGM_READER, "] - Reader\n* [",
			PGM_SCANNER, "] - Scanner\n* [",
			PGM_PARSER, "] - Parser\n");
		return EXIT_FAILURE;
	}
	flowcode_char option = argv[1][0];
	switch (option) {
	case PGM_READER:
		printf("%s%c%s", "\n[Option '", PGM_READER, "': Starting READER .....]\n\n");
		mainReader(argc, argv);
		break;
	case PGM_SCANNER:
		printf("%s%c%s", "\n[Option '", PGM_SCANNER, "': Starting SCANNER .....]\n\n");
		mainScanner(argc, argv);
		break;
	case PGM_PARSER:
		printf("%s%c%s", "\n[Option '", PGM_PARSER, "': Starting PARSER .....]\n\n");
		mainParser(argc, argv);
		break;
	default:
		printf("%s%c%s%c%s%c%s", "* OPTIONS:\n- [",
			PGM_READER, "] - Reader\n- [",
			PGM_SCANNER, "] - Scanner\n- [",
			PGM_PARSER, "] - Parser\n");
		break;
	}
	return EXIT_SUCCESS;
}

/*
***********************************************************
* Function name: printLogo
* Purpose: Print Logo
* Author: Taeyoung You
* History/Versions: Ver S23
* Called functions: -
* Parameters: -
* Return value: (Null)
* Algorithm: -
*************************************************************
*/

/* TO_DO: Update your logo with your own language message */

// flowcode_void printLogo() {
// 	printf("%s%s%s%s%s%s%s%s%s",
// 		"\t===========================================================================\n",
// 		"\t*  ####### ####      #####   ##   ##    ####    #####   #####    #######  *\n",
// 		"\t*   ##   #  ##      ### ###  ##   ##   ##  ##  ### ###   ## ##    ##   #  *\n",
// 		"\t*   ##      ##      ##   ##  ##   ##  ##       ##   ##   ##  ##   ##      *\n",
// 		"\t*   ####    ##      ##   ##  ## # ##  ##       ##   ##   ##  ##   ####    *\n",
// 		"\t*   ##      ##      ##   ##  #######  ##       ##   ##   ##  ##   ##      *\n",
// 		"\t*   ##      ##  ##  ### ###  ### ###   ##  ##  ### ###   ## ##    ##   #  *\n",
// 		"\t*  ####    #######   #####   ##   ##    ####    #####   #####    #######  *\n",
// 		"\t===========================================================================\n"
// 	);
// }

#define RESET   "\033[0m"
#define BRIGHT  "\033[97m"    // 흰색
#define LIGHT   "\033[37m"    // 밝은 회색
#define NORMAL  "\033[90m"    // 회색
#define DARK    "\033[38;5;240m"    // 어두운 회색
#define DIM     "\033[38;5;236m" // 딤 그레이 (256컬러)

flowcode_void printLogo() {
	const char* lines[] = {
		"\t===========================================================================\n",
		"\t*  ####### ####      #####   ##   ##    ####    #####   #####    #######  *\n",
		"\t*   ##   #  ##      ### ###  ##   ##   ##  ##  ### ###   ## ##    ##   #  *\n",
		"\t*   ##      ##      ##   ##  ##   ##  ##       ##   ##   ##  ##   ##      *\n",
		"\t*   ####    ##      ##   ##  ## # ##  ##       ##   ##   ##  ##   ####    *\n",
		"\t*   ##      ##      ##   ##  #######  ##       ##   ##   ##  ##   ##      *\n",
		"\t*   ##      ##  ##  ### ###  ### ###   ##  ##  ### ###   ## ##    ##   #  *\n",
		"\t*  ####    #######   #####   ##   ##    ####    #####   #####    #######  *\n",
		"\t===========================================================================\n"
	};

	const char* shades[] = { DARK, DIM, NORMAL, RESET, BRIGHT, RESET, NORMAL, DIM, DARK };
	int lineCount = sizeof(lines) / sizeof(lines[0]);

	for (int i = 0; i < lineCount; ++i) {
		printf("%s%s%s", shades[i], lines[i], RESET);
	}
}

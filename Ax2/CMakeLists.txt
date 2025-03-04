#
# CMakeList.txt : CMake project for Compilers, include source and define project specific logic here.
#
#
# *  ####### ####      #####   ##   ##    ####    #####   #####    #######  *
# *   ##   #  ##      ### ###  ##   ##   ##  ##  ### ###   ## ##    ##   #  *
# *   ##      ##      ##   ##  ##   ##  ##       ##   ##   ##  ##   ##      *
# *   ####    ##      ##   ##  ## # ##  ##       ##   ##   ##  ##   ####    *
# *   ##      ##      ##   ##  #######  ##       ##   ##   ##  ##   ##      *
# *   ##      ##  ##  ### ###  ### ###   ##  ##  ### ###   ## ##    ##   #  *
# *  ####    #######   #####   ##   ##    ####    #####   #####    #######  *
#                                      "

cmake_minimum_required (VERSION 3.8)

project ("FlowCode_Compiler")

# Add source to this project's executable: check name and dependences
add_executable (FlowCode_Compiler
	"Compilers.h"	"Compilers.c"
	"Reader.h"		"Reader.c"		"MainReader.c"
	# TO_DO: Add A22 (Scanner) and A32 (Parser)
	"Scanner.h"		"Scanner.c"		"MainScanner.c"
	#"Parser.h"		"Parser.c"		"MainParser.c"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET FlowCode_Compiler PROPERTY CXX_STANDARD 20)
endif()

# TO_DO: Add tests and install targets if needed.

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
* File name: Parser.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A32.
* Date: May 01 2023
* Purpose: This file contains all functionalities from Parser.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef PARSER_H_
#include "Parser.h"
#endif

/* Parser data */
extern ParserData psData; /* BNF statistics */

/*
************************************************************
 * Process Parser
 ***********************************************************
 */
/* TO_DO: This is the function to start the parser - check your program definition */

flowcode_void startParser()
{
    /* TO_DO: Initialize Parser data */
    flowcode_int i = 0;
    for (i = 0; i < NUM_BNF_RULES; i++)
    {
        psData.parsHistogram[i] = 0;
    }
    /* Proceed parser */
    lookahead = tokenizer();
    if (lookahead.code != EndOfToken)
    {
        program();
    }
    matchToken(EndOfToken);
    printf("%s%s\n", STR_LANGNAME, ": Source file parsed");
}


/*
 ************************************************************
 * Match Token
 ***********************************************************
 */
/* TO_DO: This is the main code for match - check your definition */
flowcode_void matchToken(flowcode_int tokenCode)
{
    if (lookahead.code == tokenCode)
    {
        if (lookahead.code == EndOfToken) return;

        lookahead = tokenizer();

        if (lookahead.code == Error)
        {
            printError();
            lookahead = tokenizer();
            syntaxErrorNumber++;
        }
    }
    else
    {
        syncErrorHandler(tokenCode);
    }
}

/*
 ************************************************************
 * Syncronize Error Handler
 ***********************************************************
 */
/* TO_DO: This is the function to handler error - adjust basically datatypes */
flowcode_void syncErrorHandler(flowcode_int syncTokenCode)
{
    printError();
    syntaxErrorNumber++;
    while (lookahead.code != syncTokenCode)
    {
        if (lookahead.code == EndOfToken)
            exit(syntaxErrorNumber);
        lookahead = tokenizer();
    }
    if (lookahead.code != EndOfToken)
        lookahead = tokenizer();
}

/*
 ************************************************************
 * Print Error
 ***********************************************************
 */
/* TO_DO: This is the function to error printing - adjust basically datatypes */
flowcode_void printError()
{
    //	extern numParserErrors;			/* link to number of errors (defined in Parser.h) */
    Token t = lookahead;
    printf("%s%s%3d\n", STR_LANGNAME, ": Syntax error:  Line:", line);
    printf("*****  Token code:%3d Attribute: ", t.code);
    switch (t.code)
    {
    case Error:
    case RunTimeError:
        printf("*ERROR*: %s\n", t.attribute.errLexeme);
        break;
    case EndOfToken:
        printf("EndOfToken_T\t\t%d\t\n", t.attribute.seofType);
        break;
    case Identifier:
        printf("Identifier_T:\t\t%s\t\n", t.attribute.idLexeme);
        break;
    case StringLiteral:
    case StringDoubleQuoteLiteral:
        printf("String_T: %s\n", readerGetContent(stringLiteralTable, t.attribute.contentString));
        break;
    case IntLiteral:
        printf("Integer_T: %s\n", readerGetContent(stringLiteralTable, t.attribute.contentString));
        break;
    case DoubleLiteral:
        printf("Double_T: %s\n", readerGetContent(stringLiteralTable, t.attribute.contentString));
        break;
    case LogicalAnd:
    case LogicalOr:
    case LogicalNot:
    case If:
    case Elif:
    case Else:
    case Then:
    case EndIf:
    case Repeat:
    case Check:
    case Break:
    case Continue:
    case Input:
    case Output:
    case Return:
    case End:
    case Int:
    case Double:
    case String:
    case Boolean:
    case Void:
    case Begin:
    case Declaration:
    case Constant:
        printf("Keyword_T: %s\n", keywordTable[t.attribute.codeType]);
        break;
    case LeftParen:
        printf("LeftParen_T\n");
        break;
    case RightParen:
        printf("RightParen_T\n");
        break;
    case LeftBrace:
        printf("LeftBrace_T\n");
        break;
    case RightBrace:
        printf("RightBrace_T\n");
        break;
    case Colon:
        printf("Colon_T\n");
        break;
    case SemiColon:
        printf("SemiColon_T\n");
        break;
    case Comma:
        printf("Comma_T\n");
        break;
    case Dot:
        printf("Dot_T\n");
        break;
    case Comment:
        printf("Comment_T\n");
        break;
    case EndOfLine:
        printf("EndOfLine_T\n");
        break;
    default:
        printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", t.code);
        numParserErrors++; // Updated parser error
    }
}

/*
 ************************************************************
 * Program statement
 * BNF: <program> -> Begin Colon EndOfLine <declaration_section> <function_definition> End SemiColon | ε
 * FIRST(<program>)= { Begin }.
 ***********************************************************
 */
flowcode_void program()
{
    /* Update program statistics */
    psData.parsHistogram[BNF_program]++;
    /* Program code */
    if (lookahead.code == Begin)
    {
        matchToken(Begin);
        matchToken(Colon);
        matchToken(EndOfLine);
        declarationSection();
        functionDefinition();
        matchToken(End);
        matchToken(SemiColon);
    }
    else if (lookahead.code == EndOfToken)
    {
        /* End Of Token and Done */
    }
    else
    {
        printError();
    }

    printf("%s%s\n", STR_LANGNAME, ": Program parsed");
}

/*
 ************************************************************
 * Type
 * BNF: <type> -> <type> -> Int | Double | String | Boolean
 * FIRST(<type>)= { Int, Double, String, Boolean }.
 ***********************************************************
 */
flowcode_void type()
{
    switch (lookahead.code)
    {
    case Int:
    case Double:
    case String:
    case Boolean:
        matchToken(lookahead.code);
        printf("%s%s\n", STR_LANGNAME, ": Type parsed");
        break;
    default:
        printError();
    }
}

/*
 ************************************************************
 * Declaration Section
 * BNF: <declaration_section> -> Declaration Colon EndOfLine <var_declaration> End SemiColon EndOfLine
 * FIRST(<declaration_section>)= { Declaration }.
 ***********************************************************
 */
flowcode_void declarationSection()
{
    psData.parsHistogram[BNF_declaration_section]++;
    if (lookahead.code == Declaration)
    {
        matchToken(Declaration);
        matchToken(Colon);
        matchToken(EndOfLine);
        varDeclaration();
        matchToken(End);
        matchToken(SemiColon);
        matchToken(EndOfLine);
        printf("%s%s\n", STR_LANGNAME, ": Declaration Section parsed");
    }
    else
    {
        printError();
    }
}

/*
 ************************************************************
 * Var Declaration
 * BNF: <var_declaration> -> <var_declaration_line> <var_declaration> | ε
 * FIRST(<var_declaration>) = { Int, Double, String, Boolean, ε }.
 * FOLLOW(<var_declaration>) = { End }.
 ***********************************************************
 */
flowcode_void varDeclaration()
{
    psData.parsHistogram[BNF_var_declaration]++;
    switch (lookahead.code)
    {
    case Int:
    case Double:
    case String:
    case Boolean:
        varDeclarationLine();
        varDeclaration();
        printf("%s%s\n", STR_LANGNAME, ": Var Declaration parsed");
        break;
    case End:
        break;
    default:
        printError();
    }
}

/*
 ************************************************************
 * Var Declaration Line
 * BNF: <var_declaration_line> -> <type> <identifier_list> EndOfLine
 * FIRST(<var_declaration_line>) = { Int, Double, String, Boolean }.
 ***********************************************************
 */
flowcode_void varDeclarationLine()
{
    psData.parsHistogram[BNF_var_declaration_line]++;
    switch (lookahead.code)
    {
    case Int:
    case Double:
    case String:
    case Boolean:
        type();
        identifierList();
        matchToken(EndOfLine);
        printf("%s%s\n", STR_LANGNAME, ": Var Declaration Line parsed");
        break;
    default:
        printError();
    }
}

/*
 ************************************************************
 * Identifier List
 * BNF: <identifier_list> -> Identifier <identifier_tail>
 * FIRST(<identifier_list>) = { Identifier }.
 ***********************************************************
 */
flowcode_void identifierList()
{
    psData.parsHistogram[BNF_identifier_list]++;
    if (lookahead.code == Identifier)
    {
        matchToken(Identifier);
        identifierTail();
        printf("%s%s\n", STR_LANGNAME, ": Identifier List parsed");
    }
    else
    {
        printError();
    }
}

/*
 ************************************************************
 * Identifier Tail
 * BNF: <identifier_tail> -> Comma Identifier <identifier_tail> | ε
 * FIRST(<identifier_tail>) = { Comma, ε }.
 * FOLLOW(<identifier_tail>) = { EndOfLine }.
 ***********************************************************
 */
flowcode_void identifierTail()
{
    psData.parsHistogram[BNF_identifier_tail]++;
    switch (lookahead.code)
    {
    case Comma:
        matchToken(Comma);
        matchToken(Identifier);
        identifierTail();
        printf("%s%s\n", STR_LANGNAME, ": Identifier Tail parsed");
        break;
    case EndOfLine:
        break;
    default:
        printError();
    }
}

/*
 ************************************************************
 * Function Definition
 * BNF: <function_definition> -> <type> Identifier LeftParen <parameter_list> RightParen Colon EndOfLine <statement_list> End SemiColon EndOfLine
 * FIRST(<function_definition>)= { Int, Double, String, Boolean }.
 ***********************************************************
 */
flowcode_void functionDefinition()
{
    psData.parsHistogram[BNF_function_definition]++;
    switch (lookahead.code)
    {
    case Int:
    case Double:
    case String:
    case Boolean:
        type();
        matchToken(Identifier);
        matchToken(LeftParen);
        parameterList();
        matchToken(RightParen);
        matchToken(Colon);
        matchToken(EndOfLine);
        statementList();
        matchToken(EndOfLine);
        matchToken(SemiColon);
        matchToken(EndOfLine);
        printf("%s%s\n", STR_LANGNAME, ": Function Definition parsed");
        break;
    default:
        printError();
    }
}

/*
 ************************************************************
 * Parameter List
 * BNF: <parameter_list> -> <parameter> <parameter_tail> | ε
 * FIRST(<parameter_list>) = { Int, Double, String, Boolean, ε }.
 * FOLLOW(<parameter_list>) = { RightParen }.
 ***********************************************************
 */
flowcode_void parameterList()
{
    psData.parsHistogram[BNF_parameter_list]++;
    switch (lookahead.code)
    {
    case Int:
    case Double:
    case String:
    case Boolean:
        parameter();
        parameterTail();
        printf("%s%s\n", STR_LANGNAME, ": Parameter List parsed");
        break;
    case RightParen:
        break;
    default:
        printError();
    }
}

/*
 ************************************************************
 * Parameter
 * BNF: <parameter> -> <type> Identifier
 * FIRST(<parameter_list>) = { Int, Double, String, Boolean }.
 ***********************************************************
 */
flowcode_void parameter()
{
    psData.parsHistogram[BNF_parameter]++;
    switch (lookahead.code)
    {
    case Int:
    case Double:
    case String:
    case Boolean:
        type();
        matchToken(Identifier);
        printf("%s%s\n", STR_LANGNAME, ": Parameter parsed");
        break;
    default:
        printError();
    }
}

/*
 ************************************************************
 * Parameter Tail
 * BNF: <parameter_tail> -> Comma <parameter> <parameter_tail> | ε
 * FIRST(<parameter_tail>) = { Comma, ε }.
 * FOLLOW(<parameter_tail>) = { RightParen }.
 ***********************************************************
 */
flowcode_void parameterTail()
{
    psData.parsHistogram[BNF_parameter_tail]++;
    switch (lookahead.code)
    {
    case Comma:
        type();
        parameter();
        parameterTail();
        printf("%s%s\n", STR_LANGNAME, ": Parameter Tail parsed");
        break;
    case RightParen:
        break;
    default:
        printError();
    }
}

/*
 ************************************************************
 * Statement List
 * BNF: <statement_list> -> <statement> <statement_list> | ε
 * FIRST(<statement_list>) = { Identifier, Input, Output, Return, ε }.
 * FOLLOW(<statement_list>) = { End }.
 ***********************************************************
 */
flowcode_void statementList()
{
    psData.parsHistogram[BNF_statement_list]++;
    switch (lookahead.code)
    {
    case Identifier:
    case Input:
    case Output:
    case Return:
        statement();
        statementList();
        printf("%s%s\n", STR_LANGNAME, ": Statement List parsed");
        break;
    case End:
        break;
    default:
        printError();
    }
}

/*
 ************************************************************
 * Statements
 * BNF: <statement> -> <assignment_statement> | <input_statement> | <output_statement> | <return_statement>
 * FIRST(<statements>) = { Identifier, Input, Output, Return }
 ***********************************************************
 */
flowcode_void statement()
{
    psData.parsHistogram[BNF_statement]++;
    switch (lookahead.code)
    {
    case Identifier:
        assignmentStatement();
        break;
    case Input:
        inputStatement();
        break;
    case Output:
        outputStatement();
        break;
    case Return:
        returnStatement();
        break;
    default:
        printError();
        return;
    }
    printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
}

/*
 ************************************************************
 * Assignment Statement
 * BNF: <assignment_statement> -> Identifier Assignment <expression> EndOfLine
 * FIRST(<assignment_statement>) = { Identifier }.
 ***********************************************************
 */
flowcode_void assignmentStatement()
{
    psData.parsHistogram[BNF_assignment_statement]++;
    if (lookahead.code == Identifier)
    {
        matchToken(Identifier);
        matchToken(Assignment);
        expression();
        matchToken(EndOfLine);
        printf("%s%s\n", STR_LANGNAME, ": Assignment Statement parsed");
    }
    else
    {
        printError();
    }
}

/*
 ************************************************************
 * Expression
 * BNF: <expression> -> <mul_expre> <add_expre_tail>
 * FIRST(<expression>) = { Identifier, IntLiteral, StringLiteral, DoubleLiteral, LeftParen }.
 ***********************************************************
 */
flowcode_void expression()
{
    psData.parsHistogram[BNF_expression]++;
    switch (lookahead.code)
    {
    case Identifier:
    case IntLiteral:
    case DoubleLiteral:
    case StringLiteral:
    case LeftParen:
        mulExpre();
        addExpreTail();
        addExpreTail();
        printf("%s%s\n", STR_LANGNAME, ": Expression parsed");
        break;
    default:
        printError();
    }
}

/*
 ************************************************************
 * Add, Subtract Expression Tail
 * BNF: <add_expre_tail> -> Add <mul_expre> <add_expre_tail> | Subtract <mul_expre> <add_expre_tail> | ε
 * FIRST(<add_expre_tail>) = { Add, Subtract, ε }.
 * FOLLOW(<add_expre_tail>) = { EndOfLine, RightParen }.
 ***********************************************************
 */
flowcode_void addExpreTail()
{
    psData.parsHistogram[BNF_add_expre_tail]++;
    switch (lookahead.code)
    {
    case Add:
        matchToken(Add);
        mulExpre();
        addExpreTail();
        break;
    case Subtract:
        matchToken(Subtract);
        mulExpre();
        addExpreTail();
        break;
    case EndOfLine:
    case RightParen:
        break;
    default:
        printError();
        return;
    }
    printf("%s%s\n", STR_LANGNAME, ": Add, Subtract Expression Tail parsed");
}

/*
 ************************************************************
 * Middle Non-terminal for Power and Mul
 * BNF: <mul_expre> -> <pow_expre> <mul_expre_tail>
 * FIRST(<mul_expre>) = { Identifier, IntLiteral, StringLiteral, DoubleLiteral, LeftParen }.
 ***********************************************************
 */
flowcode_void mulExpre()
{
    psData.parsHistogram[BNF_mul_expre]++;
    switch (lookahead.code)
    {
    case Identifier:
    case IntLiteral:
    case DoubleLiteral:
    case StringLiteral:
    case LeftParen:
        powExpre();
        mulExpreTail();
        printf("%s%s\n", STR_LANGNAME, ": Middle Non-terminal for Power and Mul parsed");
        break;
    default:
        printError();
    }
}

/*
 ************************************************************
 * Mul Expression Tail
 * BNF: <mul_expre_tail> -> Multiply <pow_expre> <mul_expre_tail> | Divide <pow_expre> <mul_expre_tail> | Modulo <pow_expre> <mul_expre_tail> | ε
 * FIRST(<mul_expre_tail>) = { Multiply, Divide, Modulo, ε }.
 * FOLLOW(<mul_expre_tail>) = { Add, Subtract, EndOfLine, RightParen }.
 ***********************************************************
 */
flowcode_void mulExpreTail()
{
    psData.parsHistogram[BNF_mul_expre_tail]++;
    switch (lookahead.code)
    {
    case Multiply:
        matchToken(Multiply);
        powExpre();
        mulExpreTail();
        break;
    case Divide:
        matchToken(Divide);
        powExpre();
        mulExpreTail();
        break;
    case Modulo:
        matchToken(Modulo);
        powExpre();
        mulExpreTail();
        break;
    case Add:
    case Subtract:
    case EndOfLine:
    case RightParen:
        break;
    default:
        printError();
        return;
    }
    printf("%s%s\n", STR_LANGNAME, ": Mul Expression Tail parsed");
}

/*
 ************************************************************
 * Power Expression
 * BNF: <pow_expre> -> <factor> Power <pow_expre> | <factor>
 * FIRST(<pow_expre>) = { Identifier, IntLiteral, StringLiteral, DoubleLiteral, LeftParen }.
 ***********************************************************
 */
flowcode_void powExpre()
{
    psData.parsHistogram[BNF_pow_expre]++;
    switch (lookahead.code)
    {
    case Identifier:
    case IntLiteral:
    case DoubleLiteral:
    case StringLiteral:
    case LeftParen:
        factor();
        if (lookahead.code == Power)
        {
            matchToken(Power);
            powExpre();
        }
        printf("%s%s\n", STR_LANGNAME, ": Power Expression parsed");
        break;
    default:
        printError();
    }
}

/*
 ************************************************************
 * Factor
 * BNF: <factor> -> Identifier | IntLiteral | StringLiteral | DoubleLiteral | LeftParen <expression> RightParen
 * FIRST(<factor>) = { Identifier, IntLiteral, StringLiteral, DoubleLiteral, LeftParen }.
 ***********************************************************
 */
flowcode_void factor()
{
    psData.parsHistogram[BNF_factor]++;
    switch (lookahead.code)
    {
    case Identifier:
        matchToken(Identifier);
        break;
    case IntLiteral:
        matchToken(IntLiteral);
        break;
    case DoubleLiteral:
        matchToken(DoubleLiteral);
        break;
    case StringLiteral:
        matchToken(StringLiteral);
        break;
    case LeftParen:
        matchToken(LeftParen);
        expression();
        matchToken(RightParen);
        break;
    default:
        printError();
        return;
    }
    printf("%s%s\n", STR_LANGNAME, ": Factor parsed");
}

/*
 ************************************************************
 * Input Statement
 * BNF: <input_statement> -> Input Colon <identifier_list> SemiColon EndOfLine
 * FIRST(<input_statement>) = { Input }.
 ***********************************************************
 */
flowcode_void inputStatement()
{
    psData.parsHistogram[BNF_input_statement]++;
    if (lookahead.code == Input)
    {
        matchToken(Input);
        matchToken(Colon);
        identifierList();
        matchToken(SemiColon);
        matchToken(EndOfLine);
        printf("%s%s\n", LANG_READ, ": Input Statement parsed");
    }
    else
    {
        printError();
    }
}

/*
 ************************************************************
 * Output Statement
 * BNF: <output_statement> -> Output Colon <output_target> SemiColon EndOfLine
 * FIRST(<output_statement>) = { Output }.
 ***********************************************************
 */
flowcode_void outputStatement()
{
    psData.parsHistogram[BNF_output_statement]++;
    if (lookahead.code == Output)
    {
        matchToken(Output);
        matchToken(Colon);
        outputTarget();
        matchToken(SemiColon);
        matchToken(EndOfLine);
        printf("%s%s\n", LANG_WRTE, ": Output Statement parsed");
    }
    else
    {
        printError();
    }
}

/*
 ************************************************************
 * Output Target
 * BNF: <output_target> -> Identifier | StringLiteral | StringDoubleQuoteLiteral
 * FIRST(<output_target>) = { Identifier, StringLiteral, StringDoubleQuoteLiteral }.
 ***********************************************************
 */
flowcode_void outputTarget()
{
    psData.parsHistogram[BNF_output_target]++;
    switch (lookahead.code)
    {
    case Identifier:
        matchToken(Identifier);
        break;
    case StringLiteral:
        matchToken(StringLiteral);
        break;
    case StringDoubleQuoteLiteral:
        matchToken(StringDoubleQuoteLiteral);
        break;
    default:
        printError();
        return;
    }
    printf("%s%s\n", LANG_WRTE, ": Output Target parsed");
}

/*
 ************************************************************
 * Return Statement
 * BNF: <return_statement> -> Return <expression> EndOfLine
 * FIRST(<return_statement>) = { Return }.
 ***********************************************************
 */
flowcode_void returnStatement()
{
    psData.parsHistogram[BNF_return_statement]++;
    if (lookahead.code == Return)
    {
        matchToken(Return);
        expression();
        matchToken(EndOfLine);
        printf("%s%s\n", STR_LANGNAME, ": Return Statement parsed");
    }else
    {
        printError();
    }

}

/*
 ************************************************************
 * comment
 * BNF: comment
 * FIRST(<comment>)= {CMT_T}.
 ***********************************************************
 */
// flowcode_void comment()
// {
//     psData.parsHistogram[BNF_comment]++;
//     matchToken(CMT_T, NO_ATTR);
//     printf("%s%s\n", STR_LANGNAME, ": Comment parsed");
// }

/*
 ************************************************************
 * The function prints statistics of BNF rules
 * Param:
 *	- Parser data
 * Return:
 *	- Void (procedure)
 ***********************************************************
 */
/*
sofia_void printBNFData(ParserData psData) {
}
*/
flowcode_void printBNFData(ParserData psData)
{
    /* Print Parser statistics */
    printf("Statistics:\n");
    printf("----------------------------------\n");
    int cont = 0;
    for (cont = 0; cont < NUM_BNF_RULES; cont++)
    {
        if (psData.parsHistogram[cont] > 0)
            printf("%s%s%s%d%s", "Token[", BNFStrTable[cont], "]=", psData.parsHistogram[cont], "\n");
    }
    printf("----------------------------------\n");
}

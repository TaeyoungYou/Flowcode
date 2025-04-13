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
#include <math.h>

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

    while (lookahead.code == Comment || lookahead.code == EndOfLine) {
        if (lookahead.code == Comment) {
            commentStatement();
        }
        else {
            matchToken(EndOfLine);
        }
    }

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
    printf(RED "%s%s%3d\n" RESET, STR_LANGNAME, ": Syntax error:  Line:", line);
    printf(RED "*****  Token code:%3d Attribute: " RESET, t.code);


    numParserErrors++; // Updated parser error
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
        printf("Keyword_T: %s\n", keywordTable[t.code - LogicalAnd]);
        break;
       /* printf("Keyword_T: %s\n", keywordTable[t.attribute.codeType]);
        break;*/
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
    }
}

flowcode_void removeNewLine()
{
    while (lookahead.code == EndOfLine)
    {
        lookahead = tokenizer();
    }
}

/*
 ************************************************************
 * Program statement
 * BNF: <program> -> Begin Colon EndOfLine <declaration_section> <main_function> <custom_function_section> End SemiColon | ε
 * FIRST(<program>)= { Begin }.
 ***********************************************************
 */
flowcode_void program()
{
    removeNewLine();
    /* Update program statistics */
    psData.parsHistogram[BNF_program]++;
    /* Program code */
    if (lookahead.code == Begin)
    {   
        matchToken(Begin);
        matchToken(Colon);
        matchToken(EndOfLine);
        removeNewLine();
        declarationSection();
        removeNewLine();
        mainFunction();
        removeNewLine();
        customFunctionSection();
        removeNewLine();
        matchToken(End);
        matchToken(SemiColon);
        removeNewLine();
    }
    else if (lookahead.code == EndOfToken)
    {
        /* End Of Token and Done - Empty */
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
 * BNF: <type> -> <type> -> Int | Double | String | Boolean | void
 * FIRST(<type>)= { Int, Double, String, Boolean, Void }.
 ***********************************************************
 */
flowcode_void type()
{
    psData.parsHistogram[BNF_type]++;
    switch (lookahead.code)
    {
    case Int:
    case Double:
    case String:
    case Boolean:
        matchToken(lookahead.code);
        printf("%s%s\n", STR_LANGNAME, ": Type parsed");
        break;
    case Void:
        matchToken(lookahead.code);
        printf("%s%s\n", STR_LANGNAME, ": Type parsed (void)");
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
 * FOLLOW(<identifier_tail>) = { EndOfLine, SemiColon }.
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
    case SemiColon:
        break;
    default:
        printError();
    }
}

/*
 ************************************************************
 * Main Function
 * BNF: <main_function> -> Boolean Main LeftParen <parameter_list> RightParen Colon EndOfLine <statement_list> End SemiColon EndOfLine
 * FIRST(<main_function>)= { Boolean }.
 ***********************************************************
 */
flowcode_void mainFunction()
{
    psData.parsHistogram[BNF_main_function]++;
    switch (lookahead.code)
    {
    case Boolean:
        matchToken(Boolean);
        matchToken(Main); 
        matchToken(LeftParen);
        parameterList();
        matchToken(RightParen);
        matchToken(Colon);
        matchToken(EndOfLine);
        statementList();
        matchToken(End);
        matchToken(SemiColon);
        matchToken(EndOfLine);
        break;
    default:
        printError();
    }
}

/*
 ************************************************************
 * Custom Function Section
 * BNF: <custom_function_section> -> <function_definition> <custom_function_section> | ε
 * FIRST(<custom_function_section>)= { Int, Double, String, Boolean, ε }.
 * FOLLOW(<custom_function_section>) = { End }.
 ***********************************************************
 */
flowcode_void customFunctionSection()
{
    removeNewLine();
    psData.parsHistogram[BNF_custom_function_section]++;
    switch (lookahead.code)
    {
    case Int:
    case Double:
    case String:
    case Boolean:
    case Void:
        functionDefinition();
        customFunctionSection();
        break;
    case End:
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
    removeNewLine();
    psData.parsHistogram[BNF_function_definition]++;
    switch (lookahead.code)
    {
    case Int:
    case Double:
    case String:
    case Boolean:
    case Void:
        type();
        matchToken(Identifier);
        matchToken(LeftParen);
        parameterList();
        matchToken(RightParen);
        matchToken(Colon);
        matchToken(EndOfLine);
        statementList();
        matchToken(End);
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
        matchToken(Comma);
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
 * BNF: <statement_list> -> <statement> <statement_list>
 * FIRST(<statement_list>) = { Identifier, Input, Output, Return, ε }.
 * FOLLOW(<statement_list>) = { End }.
 ***********************************************************
 */
flowcode_void statementList()
{
    removeNewLine();
    psData.parsHistogram[BNF_statement_list]++;
    switch (lookahead.code)
    {
    case Comment:
    case Identifier:
    case Input:
    case Output:
    case Return:
    case Check:
        statement();
        statementList();
        printf("%s%s\n", STR_LANGNAME, ": Statement List parsed");
        break;
    case If:
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
 * BNF: <statement> -> <input_statement> | <output_statement> | <return_statement> | <repeat_statement> | <identifier_leading_statement>
 * FIRST(<statements>) = { Identifier, Input, Output, Return, Check }
 ***********************************************************
 */
flowcode_void statement()
{
    psData.parsHistogram[BNF_statement]++;
    switch (lookahead.code)
    {
    case Identifier:
        identifierLeadingStatement();
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
    case Check:
        repeatStatement();
        break;
    case If:
        ifStatement();
        break;
    case Comment:
        commentStatement();
        break;
    default:
        printError();
        return;
    }
    printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
}

/*
 ************************************************************
 * Identifier Leading Statement
 * BNF: <identifier_leading_statement> -> Identifier <identifier_statement_tail>
 * FIRST(<identifier_leading_statement>) = { Identifier }.
 ***********************************************************
 */
flowcode_void identifierLeadingStatement()
{
    psData.parsHistogram[BNF_identifier_leading_statement]++;
    if (lookahead.code == Identifier)
    {
        matchToken(Identifier);
        identifierStatementTail();
        printf("%s%s\n", STR_LANGNAME, ": Identifier Leading Statement parsed");
    }
    else
    {
        printError();
    }
}

/*
 ************************************************************
 * Identifier Statement Tail
 * BNF: <identifier_statement_tail> -> Assignment <expression> EndOfLine | Colon <argument_list> SemiColon EndOfLine
 * FIRST(<identifier_statement_tail>) = { Assignment, Colon }.
 ***********************************************************
 */
flowcode_void identifierStatementTail()
{
    psData.parsHistogram[BNF_identifier_statement_tail]++;
    switch (lookahead.code)
    {
    case Assignment:
        matchToken(Assignment);
        expression();
        matchToken(EndOfLine);
        break;
    case Colon:
        matchToken(Colon);
        argumentList();
        matchToken(SemiColon);
        matchToken(EndOfLine);
        break;
    default:
        printError();
        return;
    }
    printf("%s%s\n", STR_LANGNAME, ": Identifier Statement Tail parsed");
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
 * FOLLOW(<add_expre_tail>) = { EndOfLine, RightParen, Comma, SemiColon }.
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
    case Comma:
    case SemiColon:
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
 * FOLLOW(<mul_expre_tail>) = { Add, Subtract, EndOfLine, RightParen, Comma, SemiColon }.
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
    case Comma:
    case SemiColon:
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
 * BNF: <factor> -> IntLiteral | StringLiteral | DoubleLiteral | LeftParen <expression> RightParen | Identifier | Identifier Colon <argument_list>
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
        if (lookahead.code == Colon)
        {
            matchToken(Colon);
            argumentList();
            matchToken(SemiColon);
        }
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
        /* ::TODO - implement to find variable in Double Quotation, and replace */
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
    }
    else
    {
        printError();
    }
}

/*
 ************************************************************
 * Repeat Statement
 * BNF: <repeat_statement> -> Check <condition> Colon EndOfLine <repeat_statement_list> Repeat SemiColon EndOfLine
 * FIRST(<repeat_statement>) = { Check }.
 ***********************************************************
 */
flowcode_void repeatStatement()
{
    psData.parsHistogram[BNF_repeat_statement]++;
    if (lookahead.code == Check)
    {
        matchToken(Check);
        condition();
        matchToken(Colon);
        matchToken(EndOfLine);
        repeatStatementList();
        matchToken(Repeat);
        matchToken(SemiColon);
        matchToken(EndOfLine);
        printf("%s%s\n", STR_LANGNAME, ": Repeat Statement parsed");
    }
    else
    {
        printError();
    }
}

/*
 ************************************************************
 * Repeat Statement List
 * BNF: <repeat_statement_list> -> <repeat_statement_line> <repeat_statement_list> | ε
 * FIRST(<repeat_statement_list>) = { Identifier, Input, Output, Return, Check, Break, Continue, ε }.
 * FOLLOW(<repeat_statement_list>) = { Repeat }.
 ***********************************************************
 */
flowcode_void repeatStatementList()
{
    removeNewLine();
    psData.parsHistogram[BNF_repeat_statement_list]++;
    switch (lookahead.code)
    {
    case Identifier:
    case Input:
    case Output:
    case Return:
    case Check:
    case Break:
    case Continue:
        repeatStatementLine();
        repeatStatementList();
        printf("%s%s\n", STR_LANGNAME, ": Repeat Statement List parsed");
        break;
    case Repeat:
        break;
    default:
        printError();
    }
}

/*
 ************************************************************
 * Repeat Statement Line
 * BNF: <repeat_statement_line> ->  <input_statement> | <output_statement> | <return_statement> | <repeat_statement> | <identifier_leading_statement> | Break EndOfLine | Continue EndOfLine
 * FIRST(<repeat_statement_line>) = { Identifier, Input, Output, Return, Check, Break, Continue }.
 ***********************************************************
 */
flowcode_void repeatStatementLine()
{
    psData.parsHistogram[BNF_repeat_statement_line]++;
    switch (lookahead.code)
    {
    case Identifier:
        identifierLeadingStatement();
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
    case Check:
        repeatStatement();
        break;
    case Break:
        matchToken(Break);
        matchToken(EndOfLine);
        break;
    case Continue:
        matchToken(Continue);
        matchToken(EndOfLine);
        break;
    default:
        printError();
    }
    printf("%s%s\n", STR_LANGNAME, ": Repeat Statement Line parsed");
}

/*
 ************************************************************
 * If Statement
 * BNF:  <if statement> -> If <condition> Then Colon EndOfLine <statement_list> <elseif_clause> <else_clause_opt> EndIf SemiColon EndOfLine
 *       <elseif_clauses> -> <elseif_clause> <elseif_clauses> | ε
 *       <elseif_clause> → Elif <condition> Then Colon EndOfLine <statement_list> EndOfLine
 *       <else_clause_opt> -> <else_clause> | ε
 *       <else_clause> → Else Colon EndOfLine <statement_list> EndOfLine
 * FIRST(<repeat_statement>) = { If }.
 ***********************************************************
 */
flowcode_void ifStatement() {

    psData.parsHistogram[BNF_if_statement]++;
    if (lookahead.code == If) {
        matchToken(If);
        condition();
        printf("After condition, lookahead.code = %d\n", lookahead.code);
        matchToken(Then);
        matchToken(Colon);
        matchToken(EndOfLine);
       
        statementList();
        elseifClauses();      
        elseClauseOpt();
      
        matchToken(EndIf);
        matchToken(SemiColon);
        matchToken(EndOfLine);

        printf("%s%s\n", STR_LANGNAME, ": If Statement parsed");
    }
    else {
        printError();
    }
}

/*
 ************************************************************
 * Elif Clauses
 * BNF: <elseif_clauses> -> <elseif_clause> <elseif_clauses> | ε
 ************************************************************
 */
flowcode_void elseifClauses() {
    while (lookahead.code == Elif) {
        elseifClause();
    }
}

/*
 ************************************************************
 * Elif Statement
 * BNF:  <elseif_clause> → Elif <condition> Then Colon EndOfLine <statement_list> EndOfLine
 * FIRST(<repeat_statement>) = { Elif }.
 ***********************************************************
 */
flowcode_void elseifClause() {
    if (lookahead.code == Elif)
    {
        psData.parsHistogram[BNF_elseif_clause]++;

        matchToken(Elif);
        condition();
        matchToken(Then);
        matchToken(Colon);
        matchToken(EndOfLine);
        statementList();
        matchToken(EndOfLine);

        printf("%s%s\n", STR_LANGNAME, ": Elif Clause parsed");
    }
    else {
        printError();
    }
}

/************************************************************
*Else clause option
* BNF: <else_clause_opt> -> <else_clause> | ε
* FIRST(<repeat_statement>) = { Else }.
* **********************************************************
*/
flowcode_void elseClauseOpt() {
if (lookahead.code == Else) {
    elseClause();
}
}

/************************************************************
*Else clause option
* BNF: <else_clause> → Else Colon EndOfLine <statement_list> EndOfLine
* FIRST(<repeat_statement>) = { Else }.
* **********************************************************
*/
flowcode_void elseClause() {
        psData.parsHistogram[BNF_else_clause]++;

        matchToken(Else);
        matchToken(Colon);
        matchToken(EndOfLine);
        statementList();
        matchToken(EndOfLine);
        
        printf("%s%s\n", STR_LANGNAME, ": Else Clause parsed");
}


/*
 ************************************************************
 * Condition
 * BNF: <condition> -> <bool_term> <bool_expr_tail>
 * FIRST(<condition>) = { LogicalNot, True, False, Identifier, IntLiteral, DoubleLiteral, StringLiteral, LeftParen }.
 ***********************************************************
 */
flowcode_void condition()
{
    psData.parsHistogram[BNF_condition]++;
    switch (lookahead.code)
    {
    case LogicalNot:
    case True:
    case False:
    case Identifier:
    case IntLiteral:
    case DoubleLiteral:
    case StringLiteral:
    case LeftParen:
        boolTerm();
        boolExprTail();
        printf("%s%s\n", STR_LANGNAME, ": Condition parsed");
        break;
    default:
        printError();
    }
}

/*
 ************************************************************
 * Boolean Expression Tail
 * BNF: <bool_expr_tail> -> LogicalAnd <bool_term> <bool_expr_tail> | LogicalOr <bool_term> <bool_expr_tail> | ε
 * FIRST(<bool_expr_tail>) = { LogicalAnd, LogicalOr, ε }.
 * FOLLOW(<bool_expr_tail>) = { Colon, RightParen }.
 ***********************************************************
 */
flowcode_void boolExprTail()
{
    psData.parsHistogram[BNF_bool_exp_tail]++;
    switch (lookahead.code)
    {
    case LogicalAnd:
        matchToken(LogicalAnd);
        boolTerm();
        boolExprTail();
        break;
    case LogicalOr:
        matchToken(LogicalOr);
        boolTerm();
        boolExprTail();
        break;
    case Colon:
    case RightParen:
        break;
    default:
        printError();
        return;
    }
    printf("%s%s\n", STR_LANGNAME, ": Boolean Expression Tail parsed");
}

/*
 ************************************************************
 * Boolean Term
 * BNF: <bool_term> -> LogicalNot <basic_bool> | <basic_bool>
 * FIRST(<bool_term>) = { LogicalNot, True, False, Identifier, IntLiteral, DoubleLiteral, StringLiteral, LeftParen }.
 ***********************************************************
 */
flowcode_void boolTerm()
{
    psData.parsHistogram[BNF_bool_term]++;
    switch (lookahead.code)
    {
    case LogicalNot:
        matchToken(LogicalNot);
        basicBool();
        break;
    case True:
    case False:
    case Identifier:
    case IntLiteral:
    case DoubleLiteral:
    case StringLiteral:
    case LeftParen:
        basicBool();
        break;
    default:
        printError();
        return;
    }
    printf("%s%s\n", STR_LANGNAME, ": Boolean Term parsed");
}

/*
 ************************************************************
 * Basic Boolean
 * BNF: <basic_bool> -> <basic_bool> -> True | False | <operand> <compare_op> <operand> | LeftParen <bool_term> <bool_expr_tail> RightParen
 * FIRST(<basic_bool>) = { True, False, Identifier, IntLiteral, DoubleLiteral, StringLiteral, LeftParen }.
 ***********************************************************
 */
flowcode_void basicBool()
{
    psData.parsHistogram[BNF_basic_bool]++;
    switch (lookahead.code)
    {
    case True: 
        matchToken(True);
        break;
    case False:
         matchToken(False);
         break;
    case Identifier:
    case IntLiteral:
    case DoubleLiteral:
    case StringLiteral:
        operand();
        if (lookahead.code == Equal || lookahead.code == NotEqual ||
            lookahead.code == LessThan || lookahead.code == GreaterThan ||
            lookahead.code == LessOrEqual || lookahead.code == GreaterOrEqual) {
            compareOp();
            operand();
        }
        break;
        /*compareOp();
        operand();*/
        break;
    case LeftParen:
        matchToken(LeftParen);
        boolTerm();
        boolExprTail();
        matchToken(RightParen);
        break;
    default:
        printError();
        return;
    }
    printf("%s%s\n", STR_LANGNAME, ": Basic Boolean parsed");
}

/*
 ************************************************************
 * Operand
 * BNF: <operand> -> Identifier | IntLiteral | DoubleLiteral | StringLiteral | True | False
 * FIRST(<operand>) = { Identifier, IntLiteral, DoubleLiteral, StringLiteral, True, False }.
 ***********************************************************
 */
flowcode_void operand()
{
    psData.parsHistogram[BNF_operand]++;
    switch (lookahead.code)
    {
    case True:
        matchToken(True);
        break;
    case False:
        matchToken(False);
        break;
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
    default:
        printError();
        return;
    }
    printf("%s%s\n", STR_LANGNAME, ": Operand parsed");
}

/*
 ************************************************************
 * Compare operation
 * BNF: <compare_op> -> Equal | NotEqual | LessThan | GreaterThan | LessOrEqual | GreaterOrEqual
 * FIRST(<compare_op>) = { Equal, NotEqual, LessThan, GreaterThan, LessOrEqual, GreaterOrEqual }.
 ***********************************************************
 */
flowcode_void compareOp()
{
    psData.parsHistogram[BNF_compare_op]++;
    switch (lookahead.code)
    {
    case Equal:
        matchToken(Equal);
        break;
    case NotEqual:
        matchToken(NotEqual);
        break;
    case LessThan:
        matchToken(LessThan);
        break;
    case GreaterThan:
        matchToken(GreaterThan);
        break;
    case LessOrEqual:
        matchToken(LessOrEqual);
        break;
    case GreaterOrEqual:
        matchToken(GreaterOrEqual);
        break;
    default:
        printError();
        return;
    }
    printf("%s%s\n", STR_LANGNAME, ": Operand parsed");
}

/*
 ************************************************************
 * Argument List
 * BNF: <argument_list> -> <non_call_expression> <argument_tail> | ε
 * FIRST(<argument_list>) = { Identifier, IntLiteral, StringLiteral, DoubleLiteral, LeftParen, ε }.
 * FOLLOW(<argument_list>) = { SemiColon }.
 ***********************************************************
 */
flowcode_void argumentList()
{
    psData.parsHistogram[BNF_argument_list]++;
    switch (lookahead.code)
    {
    case Identifier:
    case IntLiteral:
    case DoubleLiteral:
    case StringLiteral:
    case LeftParen:
        nonCallExpression();
        argumentTail();
        break;
    case SemiColon:
        break;
    default:
        printError();
        return;
    }
    printf("%s%s\n", STR_LANGNAME, ": Argument List parsed");
}

/*
 ************************************************************
 * Argument Tail
 * BNF: <argument_tail> -> Comma <non_call_expression> <argument_tail> | ε
 * FIRST(<argument_tail>) = { Comma, ε }.
 * FOLLOW(<argument_tail>) = { SemiColon }.
 ***********************************************************
 */
flowcode_void argumentTail()
{
    psData.parsHistogram[BNF_argument_tail]++;
    switch (lookahead.code)
    {
    case Comma:
        matchToken(Comma);
        nonCallExpression();
        argumentTail();
        break;
    case SemiColon:
        break;
    default:
        printError();
        return;
    }
    printf("%s%s\n", STR_LANGNAME, ": Argument Tail parsed");
}

/*
 ************************************************************
 * Non Call Expression
 * BNF: <non_call_expression> -> <non_call_mul> <add_expre_tail>
 * FIRST(<non_call_expression>) = { Identifier, IntLiteral, StringLiteral, DoubleLiteral, LeftParen }.
 ***********************************************************
 */
flowcode_void nonCallExpression()
{
    psData.parsHistogram[BNF_non_call_expression]++;
    switch (lookahead.code)
    {
    case Identifier:
    case IntLiteral:
    case StringLiteral:
    case DoubleLiteral:
    case LeftParen:
        nonCallMul();
        addExpreTail();
        printf("%s%s\n", STR_LANGNAME, ": Non Call Expression parsed");
        break;
    default:
        printError();
    }
}

/*
 ************************************************************
 * Non Call Multiply
 * BNF: <non_call_mul> -> <non_call_pow> <mul_expre_tail>
 * FIRST(<non_call_mul>) = { Identifier, IntLiteral, StringLiteral, DoubleLiteral, LeftParen }.
 ***********************************************************
 */
flowcode_void nonCallMul()
{
    psData.parsHistogram[BNF_non_call_mul]++;
    switch (lookahead.code)
    {
    case Identifier:
    case IntLiteral:
    case StringLiteral:
    case DoubleLiteral:
    case LeftParen:
        nonCallPow();
        mulExpreTail();
        printf("%s%s\n", STR_LANGNAME, ": Non Call Multiply parsed");
        break;
    default:
        printError();
    }
}

/*
 ************************************************************
 * Non Call Power
 * BNF: <non_call_pow> -> <non_call_factor> Power <non_call_pow> | <non_call_factor>
 * FIRST(<non_call_pow>) = { Identifier, IntLiteral, StringLiteral, DoubleLiteral, LeftParen }.
 ***********************************************************
 */
flowcode_void nonCallPow()
{
    psData.parsHistogram[BNF_non_call_pow]++;
    switch (lookahead.code)
    {
    case Identifier:
    case IntLiteral:
    case StringLiteral:
    case DoubleLiteral:
    case LeftParen:
        nonCallFactor();
        if (lookahead.code == Power)
        {
            matchToken(Power);
            nonCallPow();
        }

        printf("%s%s\n", STR_LANGNAME, ": Non Call Power parsed");
        break;
    default:
        printError();
    }
}

/*
 ************************************************************
 * Non Call Factor
 * BNF: <non_call_factor> -> IntLiteral | StringLiteral | DoubleLiteral | LeftParen <non_call_expression> RightParen | Identifier
 * FIRST(<non_call_factor>) = { Identifier, IntLiteral, StringLiteral, DoubleLiteral, LeftParen }.
 ***********************************************************
 */
flowcode_void nonCallFactor()
{
    psData.parsHistogram[BNF_non_call_factor]++;
    switch (lookahead.code)
    {
    case Identifier:
        matchToken(Identifier);
        break;
    case IntLiteral:
        matchToken(IntLiteral);
        break;
    case StringLiteral:
        matchToken(StringLiteral);
        break;
    case DoubleLiteral:
        matchToken(DoubleLiteral);
        break;
    case LeftParen:
        matchToken(LeftParen);
        nonCallExpression();
        matchToken(RightParen);
        break;
    default:
        printError();
        return;
    }
    printf("%s%s\n", STR_LANGNAME, ": Non Call Power parsed");
}

/*
 ************************************************************
 * comment
 * BNF: comment
 * FIRST(<comment>)= {CMT_T}.
 ***********************************************************
 */

flowcode_void commentStatement(flowcode_void) {
   
    psData.parsHistogram[BNF_comment]++;
    matchToken(Comment);
}

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
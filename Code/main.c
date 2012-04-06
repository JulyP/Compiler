#include <stdio.h>
#include <stdlib.h>
#include "data structure.h"
#include "print errors.h"
#include "TableName.h"
#include "TableConstant.h"
#include "TableError.h"
#include "Scanner.h"
#include "parser.h"


int main()
{
    errorHead = NULL;
    //lex analizator
    Scanner();

    if (errorHead != NULL)
    {
        PrintErrors();
        return 0;
    }

    //sint analizator
    SA();

    if (errorHead != NULL)
    {
        PrintErrors();
        return 0;
    }

    printTree(Root);
    freeTree(&Root);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
//#include <stdafx.h>
#include "data structure.h"
#include "print errors.h"
#include "TableName.h"
#include "TableConstant.h"
#include "TableError.h"
#include "Scanner.h"
#include "parser.h"
#include "Semantic_analizer.h"

int main()
{
    int a;
	struct Table_Identificators *three_id = NULL;
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

    //printTree(Root);

    //semant analixator
    three_id = semantic_analizer(Root);
	if (errorHead != NULL)
    {
        PrintErrors();
        //return 0;
    }

    //printTree(Root);

    printTable(three_id);
	delete_Table_Identificators(&three_id);
    freeTree(&Root);
    return 0;
}

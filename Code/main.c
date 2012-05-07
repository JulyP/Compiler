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
    char input_f[9] = "input.txt";
    char output_f[10] = "output.txt";
    Scanner(input_f);

    if (errorHead != NULL)
    {
        PrintErrors(output_f);
        return 0;
    }

    //sint analizator
    SA();

    if (errorHead != NULL)
    {
        PrintErrors(output_f);
        return 0;
    }

    FILE *f;
    f = fopen("tree.txt", "w");
    printTree(Root,f);
    fclose(f);

    //semant analixator
    three_id = semantic_analizer(Root);
	if (errorHead != NULL)
    {
        PrintErrors(output_f);
        //return 0;
    }

    //printTree(Root);

    printTable(three_id);
	delete_Table_Identificators(&three_id);
    freeTree(&Root);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "data structure.h"
#include "TableName.h"
#include "TableConstant.h"
#include "TableError.h"
#include "Scanner.h"
#include "parser.h"


int main()
{
    errorHead = NULL;
    Scanner();

    if (errorHead != NULL)
    {

        return 0;
    }

    SA();
    return 0;
}

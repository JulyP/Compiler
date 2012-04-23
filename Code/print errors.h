#ifndef PRINT_ERRORS_H_INCLUDED
#define PRINT_ERRORS_H_INCLUDED

int freeTree(struct nodeTree **pp)
{
    if ((*pp) != NULL)
    {
        struct nodeTree *p0, *p1, *p2, *p3;
        p0 = (*pp) -> alpha[0];
        p1 = (*pp) -> alpha[1];
        p2 = (*pp) -> alpha[2];
        p3 = (*pp) -> alpha[3];
        if (p0 != NULL)
        {
            freeTree(&p0);
        }
        if (p1 != NULL)
        {
            freeTree(&p1);
        }
        if (p2 != NULL)
        {
            freeTree(&p2);
        }
        if (p3 != NULL)
        {
            freeTree(&p3);
        }
        free(*pp);
    }
    return 0;
}

int printTree(struct nodeTree *pp)
{
    struct nodeTree *p0, *p1, *p2, *p3;
	if (pp != NULL)
    {
        printf("\nt: %d\t%d ", pp->n.token, pp->n.numToken);

        p0 = pp -> alpha[0];
        p1 = pp -> alpha[1];
        p2 = pp -> alpha[2];
        p3 = pp -> alpha[3];
        if (p0 != NULL)
        {
            printTree(p0);
        }
        if (p1 != NULL)
        {
            printTree(p1);
        }
        if (p2 != NULL)
        {
            printTree(p2);
        }
        if (p3 != NULL)
        {
            printTree(p3);
        }
    }
    return 0;
}

int PrintErrors()
{
    struct nodeError *p = errorHead;
    FILE *f;
    f = fopen("errors.txt", "w");
    char *str = (char*)malloc(sizeof(char)*87);

	printf("\n\nThere are errors in errors.txt.\n");

    switch(p->typeOfError)
    {
        case 1: //lex mistakes
        {
            while(p != NULL)
            {
                switch(p->numOfError)
                {
                    case 0:
                    {
                        str = "Максимальная длина идентификатора больше 50 символов.";
                        break;
                    }
                    case 1:
                    {
                        str = "Максимальная длина числа больше 9 символов.";
                        break;
                    }
                    case 2:
                    {
                        str = "Пропуск символов закрывающих комментарий */.";
                        break;
                    }
                    case 3:
                    {
                        str = "Максимальная длина буфера больше 256 символов.";
                        break;
                    }
                    case 4:
                    {
                        str = "Неизвестный символ.";
                        break;
                    }
                    case 5:
                    {
                        str = "Неправильная запись числа, после точки не цифра.";
                        break;
                    }
                    case 6:
                    {
                        str = "Пропуск символа закрывающей кавычки.";
                        break;
                    }
                }
                fprintf(f, "%s", str);
                if (p->numOfError != 3)
                {
                    str = " Строка ";
                    fprintf(f, "%s", str);
                    fprintf(f, "%d", p->numOfString);
                    str = " позиция ";
                    fprintf(f, "%s", str);
                    fprintf(f, "%d.", p->position);
                }
                str = "\n";
                fprintf(f, "%s", str);
                p = p->next;
            }
            break;
        }
        case 2: //sintaxis mistakes
        {
            while(p != NULL)
            {
                switch(-1*(p->numOfError))
                {
                    case 1:
                    {
                        str = "Ожидается 'type'.";
                        break;
                    }
                    case 2:
                    {
                        str = "Ожидается идентификатор.";
                        break;
                    }
                    case 3:
                    {
                        str = "Ожидается 'else', 'type', идентификатор, 'cin', 'cout', 'if', 'for', 'while' или '}'.";
                        break;
                    }
                    case 4:
                    {
                        str = "Ожидается '&&', '||' или ')'.";
                        break;
                    }
                    case 5:
                    {
                        str = "Ожидается '{'.";
                        break;
                    }
                    case 6:
                    {
                        str = "Ожидается идентификатор или число.";
                        break;
                    }
                    case 7:
                    {
                        str = "Ожидается '+', '-' или ')'.";
                        break;
                    }
                    case 8:
                    {
                        str = "Ожидается 'cout'.";
                        break;
                    }
                    case 9:
                    {
                        str = "Ожидается '<<' или ';'.";
                        break;
                    }
                    case 10:
                    {
                        str = "Ожидается 'cin'.";
                        break;
                    }
                    case 11:
                    {
                        str = "Ожидается '*', '/' или ')'.";
                        break;
                    }
                    case 12:
                    {
                        str = "Ожидается '}'.";
                        break;
                    }
                    case 13:
                    {
                        str = "Ожидается ';'.";
                        break;
                    }
                    case 14:
                    {
                        str = "Ожидается число, идентификатор или '('.";
                        break;
                    }
                    case 15:
                    {
                        str = "Ожидается 'if'.";
                        break;
                    }
                    case 16:
                    {
                        str = "Ожидается строковая константа.";
                        break;
                    }
                    case 17:
                    {
                        str = "Ожидается 'for'.";
                        break;
                    }
                    case 18:
                    {
                        str = "Ожидается 'while'.";
                        break;
                    }
                    case 19:
                    {
                        str = "Ожидается 'main'.";
                        break;
                    }
                    case 20:
                    {
                        str = "Ожидается 'type', идентификатор, 'cin', 'cout', 'if', 'for', 'while' или '}'.";
                        break;
                    }
                    case 21:
                    {
                        str = "Ожидается '=' или ';'.";
                        break;
                    }
                    case 22:
                    {
                        str = "Ожидается константа, идентификатор или '('.";
                        break;
                    }
                    case 23:
                    {
                        str = "Ожидается число.";
                        break;
                    }
                    case 24:
                    {
                        str = "Ожидается '='.";
                        break;
                    }
                    case 25:
                    {
                        str = "Ожидается '>>'.";
                        break;
                    }
                    case 26:
                    {
                        str = "Ожидается '<<'.";
                        break;
                    }
                    case 27:
                    {
                        str = "Ожидается '('.";
                        break;
                    }
                    case 28:
                    {
                        str = "Ожидается ')'.";
                        break;
                    }
                    case 29:
                    {
                        str = "Ожидается 'else'.";
                        break;
                    }
                    case 30:
                    {
                        str = "Ожидается '&&' или '||'.";
                        break;
                    }
                    case 31:
                    {
                        str = "Ожидается '==', '<=', '>=', '!=', '>' или '<'.";
                        break;
                    }
                    case 32:
                    {
                        str = "Ожидается '+' или '-'.";
                        break;
                    }
                    case 33:
                    {
                        str = "Ожидается '*' или '/'.";
                        break;
                    }
                    case 34:
                    {
                        str = "Ожидается конец файла.";
                        break;
                    }
                }
                fprintf(f, "%s", str);
                str = " Строка ";
                fprintf(f, "%s", str);
                fprintf(f, "%d", p->numOfString);
                str = " позиция ";
                fprintf(f, "%s", str);
                fprintf(f, "%d.\n", p->position);
                p = p->next;
            }
            break;
        }
        case 3:
        {
            while(p != NULL)
            {
                switch(p->numOfError)
                {
                    case 0:
                    {
                        str = " ---=== *** ОШИБКА В ДЕРЕВЕ РАЗБОРА *** ===---";
                        break;
                    }
                    case 1:
                    {
                        str = "Превышен максимальный уровень вложенности блоков, равный ";
                        break;
                    }
                    case 2:
                    {
                        str = "В одном блоке не может быть более max_amount_podblocs вложенных блоков первого уровня.";
                        break;
                    }
					case 3:
                    {
                        str = "Повторное описание имени в блоке.";
                        break;
                    }
					case 4:
                    {
                        str = "Превышен лимит описания идентификаторов. максимальное количество имен в программе - ";
                        break;
                    }
					case 5:
                    {
                        str = "Несовпадение типов.";
                        break;
                    }
					case 6:
                    {
                        str = "Отсутствует описание идентификатора в программе.";
                        break;
                    }
					case 7:
                    {
                        str = "Превышен лимит выводимых выражений оператором вывода. предел - ";
                        break;
                    }
					case 8:
                    {
                        str = "Ошибка в арифметическом выражении.";
                        break;
                    }
					case 9:
                    {
                        str = "Данное выражение не является булевым.";
                        break;
                    }
                }
                fprintf(f, "%s", str);
                if(p->numOfError != 0)
                {
                    if (p->numOfError == 1)
                    {
                        fprintf(f, "%d.", max_level_blocks);
                    }
                    else
                    {
                        if (p->numOfError == 4)
                        {
                            fprintf(f, "%d.", max_amount_id);
                        }
                        else
                        {
                            if (p->numOfError == 7)
                            {
                                fprintf(f, "%d.", max_amount_print);
                            }
                        }
                    }
                    str = " Строка ";
                    fprintf(f, "%s", str);
                    fprintf(f, "%d", p->numOfString);
                    str = " позиция ";
                    fprintf(f, "%s", str);
                    fprintf(f, "%d.", p->position);
                }
                str = "\n";
                fprintf(f, "%s", str);
                p = p->next;
            }
            break;
        }
    }
    fclose(f);

    return 0;
}

#endif // PRINT_ERRORS_H_INCLUDED

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
	printf("\n\nОшибки:\n");

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
                        printf("Максимальная длина идентификатора больше 50 символов. Строка %d позиция %d\n", p->numOfString, p->position);
                        break;
                    }
                    case 1:
                    {
                        printf("Максимальная длина числа больше 9 символов. Строка %d позиция %d\n",p->numOfString, p->position);
                        break;
                    }
                    case 2:
                    {
                        printf("Пропуск символов закрывающих комментарий */. Строка %d позиция %d\n",p->numOfString, p->position);
                        break;
                    }
                    case 3:
                    {
                        printf("Максимальная длина буфера больше 256 символов\n");
                        break;
                    }
                    case 4:
                    {
                        printf("Неизвестный символ. Строка %d позиция %d\n",p->numOfString, p->position);
                        break;
                    }
                    case 5:
                    {
                        printf("Неправильная запись числа, после точки не цифра. Строка %d позиция %d\n",p->numOfString, p->position);
                        break;
                    }
                    case 6:
                    {
                        printf("Пропуск символа закрывающей кавычки. Строка %d позиция %d\n",p->numOfString, p->position);
                        break;
                    }
                }
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
                        printf("Ожидается 'type'.");
                        break;
                    }
                    case 2:
                    {
                        printf("Ожидается идентификатор.");
                        break;
                    }
                    case 3:
                    {
                        printf("Ожидается 'else', 'type', идентификатор, 'cin', 'cout', 'if', 'for', 'while' или '}'.");
                        break;
                    }
                    case 4:
                    {
                        printf("Ожидается '&&', '||' или ')'.");
                        break;
                    }
                    case 5:
                    {
                        printf("Ожидается '{'.");
                        break;
                    }
                    case 6:
                    {
                        printf("Ожидается идентификатор или число.");
                        break;
                    }
                    case 7:
                    {
                        printf("Ожидается '+', '-' или ')'.");
                        break;
                    }
                    case 8:
                    {
                        printf("Ожидается 'cout'.");
                        break;
                    }
                    case 9:
                    {
                        printf("Ожидается '<<' или ';'.");
                        break;
                    }
                    case 10:
                    {
                        printf("Ожидается 'cin'.");
                        break;
                    }
                    case 11:
                    {
                        printf("Ожидается '*', '/' или ')'.");
                        break;
                    }
                    case 12:
                    {
                        printf("Ожидается '}'.");
                        break;
                    }
                    case 13:
                    {
                        printf("Ожидается ';'.");
                        break;
                    }
                    case 14:
                    {
                        printf("Ожидается число, идентификатор или '('.");
                        break;
                    }
                    case 15:
                    {
                        printf("Ожидается 'if'.");
                        break;
                    }
                    case 16:
                    {
                        printf("Ожидается строковая константа.");
                        break;
                    }
                    case 17:
                    {
                        printf("Ожидается 'for'.");
                        break;
                    }
                    case 18:
                    {
                        printf("Ожидается 'while'.");
                        break;
                    }
                    case 19:
                    {
                        printf("Ожидается 'main'.");
                        break;
                    }
                    case 20:
                    {
                        printf("Ожидается 'type', идентификатор, 'cin', 'cout', 'if', 'for', 'while' или '}'.");
                        break;
                    }
                    case 21:
                    {
                        printf("Ожидается '=' или ';'.");
                        break;
                    }
                    case 22:
                    {
                        printf("Ожидается константа, идентификатор или '('.");
                        break;
                    }
                    case 23:
                    {
                        printf("Ожидается число.");
                        break;
                    }
                    case 24:
                    {
                        printf("Ожидается '='.");
                        break;
                    }
                    case 25:
                    {
                        printf("Ожидается '>>'.");
                        break;
                    }
                    case 26:
                    {
                        printf("Ожидается '<<'.");
                        break;
                    }
                    case 27:
                    {
                        printf("Ожидается '('.");
                        break;
                    }
                    case 28:
                    {
                        printf("Ожидается ')'.");
                        break;
                    }
                    case 29:
                    {
                        printf("Ожидается 'else'.");
                        break;
                    }
                    case 30:
                    {
                        printf("Ожидается '&&' или '||'.");
                        break;
                    }
                    case 31:
                    {
                        printf("Ожидается '==', '<=', '>=', '!=', '>' или '<'.");
                        break;
                    }
                    case 32:
                    {
                        printf("Ожидается '+' или '-'.");
                        break;
                    }
                    case 33:
                    {
                        printf("Ожидается '*' или '/'.");
                        break;
                    }
                    case 34:
                    {
                        printf("Ожидается конец файла.");
                        break;
                    }
                }
                printf(" Строка %d позиция %d\n", p->numOfString, p->position);
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
                        printf(" ---=== *** ОШИБКА В ДЕРЕВЕ РАЗБОРА *** ===---\n");
                        break;
                    }
                    case 1:
                    {
                        printf("Превышен максимальный уровень вложенности блоков, равный %d. Строка %d позиция %d\n", max_level_blocks, p->numOfString, p->position);
                        break;
                    }
                    case 2:
                    {
                        printf("В одном блоке не может быть более max_amount_podblocs вложенных блоков первого уровня. Строка %d позиция %d\n", p->numOfString, p->position);
                        break;
                    }
					case 3:
                    {
                        printf("Повторное описание имени в блоке. Строка %d позиция %d\n", p->numOfString, p->position);
                        break;
                    }
					case 4:
                    {
                        printf("Превышен лимит описания идентификаторов. максимальное количество имен в программе - %d. Строка %d позиция %d\n", max_amount_id, p->numOfString, p->position);
                        break;
                    }
					case 5:
                    {
                        printf("Несовпадение типов. Строка %d позиция %d\n", p->numOfString, p->position);
                        break;
                    }
					case 6:
                    {
                        printf("Отсутствует описание идентификатора в программе. Строка %d позиция %d\n", p->numOfString, p->position);
                        break;
                    }
					case 7:
                    {
                        printf("Превышен лимит выводимых выражений оператором вывода. предел - %d. Строка %d позиция %d\n", max_amount_print, p->numOfString, p->position);
                        break;
                    }
					case 8:
                    {
                        printf("Ошибка в арифметическом выражении. Строка %d позиция %d\n", p->numOfString, p->position);
                        break;
                    }
					case 9:
                    {
                        printf("Данное выражение не является булевым. Строка %d позиция %d\n", p->numOfString, p->position);
                        break;
                    }
                }
                p = p->next;
            }
            break;
        }
    }
    return 0;
}

#endif // PRINT_ERRORS_H_INCLUDED

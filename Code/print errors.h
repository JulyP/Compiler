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
                        str = "������������ ����� �������������� ������ 50 ��������.";
                        break;
                    }
                    case 1:
                    {
                        str = "������������ ����� ����� ������ 9 ��������.";
                        break;
                    }
                    case 2:
                    {
                        str = "������� �������� ����������� ����������� */.";
                        break;
                    }
                    case 3:
                    {
                        str = "������������ ����� ������ ������ 256 ��������.";
                        break;
                    }
                    case 4:
                    {
                        str = "����������� ������.";
                        break;
                    }
                    case 5:
                    {
                        str = "������������ ������ �����, ����� ����� �� �����.";
                        break;
                    }
                    case 6:
                    {
                        str = "������� ������� ����������� �������.";
                        break;
                    }
                }
                fprintf(f, "%s", str);
                if (p->numOfError != 3)
                {
                    str = " ������ ";
                    fprintf(f, "%s", str);
                    fprintf(f, "%d", p->numOfString);
                    str = " ������� ";
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
                        str = "��������� 'type'.";
                        break;
                    }
                    case 2:
                    {
                        str = "��������� �������������.";
                        break;
                    }
                    case 3:
                    {
                        str = "��������� 'else', 'type', �������������, 'cin', 'cout', 'if', 'for', 'while' ��� '}'.";
                        break;
                    }
                    case 4:
                    {
                        str = "��������� '&&', '||' ��� ')'.";
                        break;
                    }
                    case 5:
                    {
                        str = "��������� '{'.";
                        break;
                    }
                    case 6:
                    {
                        str = "��������� ������������� ��� �����.";
                        break;
                    }
                    case 7:
                    {
                        str = "��������� '+', '-' ��� ')'.";
                        break;
                    }
                    case 8:
                    {
                        str = "��������� 'cout'.";
                        break;
                    }
                    case 9:
                    {
                        str = "��������� '<<' ��� ';'.";
                        break;
                    }
                    case 10:
                    {
                        str = "��������� 'cin'.";
                        break;
                    }
                    case 11:
                    {
                        str = "��������� '*', '/' ��� ')'.";
                        break;
                    }
                    case 12:
                    {
                        str = "��������� '}'.";
                        break;
                    }
                    case 13:
                    {
                        str = "��������� ';'.";
                        break;
                    }
                    case 14:
                    {
                        str = "��������� �����, ������������� ��� '('.";
                        break;
                    }
                    case 15:
                    {
                        str = "��������� 'if'.";
                        break;
                    }
                    case 16:
                    {
                        str = "��������� ��������� ���������.";
                        break;
                    }
                    case 17:
                    {
                        str = "��������� 'for'.";
                        break;
                    }
                    case 18:
                    {
                        str = "��������� 'while'.";
                        break;
                    }
                    case 19:
                    {
                        str = "��������� 'main'.";
                        break;
                    }
                    case 20:
                    {
                        str = "��������� 'type', �������������, 'cin', 'cout', 'if', 'for', 'while' ��� '}'.";
                        break;
                    }
                    case 21:
                    {
                        str = "��������� '=' ��� ';'.";
                        break;
                    }
                    case 22:
                    {
                        str = "��������� ���������, ������������� ��� '('.";
                        break;
                    }
                    case 23:
                    {
                        str = "��������� �����.";
                        break;
                    }
                    case 24:
                    {
                        str = "��������� '='.";
                        break;
                    }
                    case 25:
                    {
                        str = "��������� '>>'.";
                        break;
                    }
                    case 26:
                    {
                        str = "��������� '<<'.";
                        break;
                    }
                    case 27:
                    {
                        str = "��������� '('.";
                        break;
                    }
                    case 28:
                    {
                        str = "��������� ')'.";
                        break;
                    }
                    case 29:
                    {
                        str = "��������� 'else'.";
                        break;
                    }
                    case 30:
                    {
                        str = "��������� '&&' ��� '||'.";
                        break;
                    }
                    case 31:
                    {
                        str = "��������� '==', '<=', '>=', '!=', '>' ��� '<'.";
                        break;
                    }
                    case 32:
                    {
                        str = "��������� '+' ��� '-'.";
                        break;
                    }
                    case 33:
                    {
                        str = "��������� '*' ��� '/'.";
                        break;
                    }
                    case 34:
                    {
                        str = "��������� ����� �����.";
                        break;
                    }
                }
                fprintf(f, "%s", str);
                str = " ������ ";
                fprintf(f, "%s", str);
                fprintf(f, "%d", p->numOfString);
                str = " ������� ";
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
                        str = " ---=== *** ������ � ������ ������� *** ===---";
                        break;
                    }
                    case 1:
                    {
                        str = "�������� ������������ ������� ����������� ������, ������ ";
                        break;
                    }
                    case 2:
                    {
                        str = "� ����� ����� �� ����� ���� ����� max_amount_podblocs ��������� ������ ������� ������.";
                        break;
                    }
					case 3:
                    {
                        str = "��������� �������� ����� � �����.";
                        break;
                    }
					case 4:
                    {
                        str = "�������� ����� �������� ���������������. ������������ ���������� ���� � ��������� - ";
                        break;
                    }
					case 5:
                    {
                        str = "������������ �����.";
                        break;
                    }
					case 6:
                    {
                        str = "����������� �������� �������������� � ���������.";
                        break;
                    }
					case 7:
                    {
                        str = "�������� ����� ��������� ��������� ���������� ������. ������ - ";
                        break;
                    }
					case 8:
                    {
                        str = "������ � �������������� ���������.";
                        break;
                    }
					case 9:
                    {
                        str = "������ ��������� �� �������� �������.";
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
                    str = " ������ ";
                    fprintf(f, "%s", str);
                    fprintf(f, "%d", p->numOfString);
                    str = " ������� ";
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

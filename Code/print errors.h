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
	printf("\n\n������:\n");

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
                        printf("������������ ����� �������������� ������ 50 ��������. ������ %d ������� %d\n", p->numOfString, p->position);
                        break;
                    }
                    case 1:
                    {
                        printf("������������ ����� ����� ������ 9 ��������. ������ %d ������� %d\n",p->numOfString, p->position);
                        break;
                    }
                    case 2:
                    {
                        printf("������� �������� ����������� ����������� */. ������ %d ������� %d\n",p->numOfString, p->position);
                        break;
                    }
                    case 3:
                    {
                        printf("������������ ����� ������ ������ 256 ��������\n");
                        break;
                    }
                    case 4:
                    {
                        printf("����������� ������. ������ %d ������� %d\n",p->numOfString, p->position);
                        break;
                    }
                    case 5:
                    {
                        printf("������������ ������ �����, ����� ����� �� �����. ������ %d ������� %d\n",p->numOfString, p->position);
                        break;
                    }
                    case 6:
                    {
                        printf("������� ������� ����������� �������. ������ %d ������� %d\n",p->numOfString, p->position);
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
                        printf("��������� 'type'.");
                        break;
                    }
                    case 2:
                    {
                        printf("��������� �������������.");
                        break;
                    }
                    case 3:
                    {
                        printf("��������� 'else', 'type', �������������, 'cin', 'cout', 'if', 'for', 'while' ��� '}'.");
                        break;
                    }
                    case 4:
                    {
                        printf("��������� '&&', '||' ��� ')'.");
                        break;
                    }
                    case 5:
                    {
                        printf("��������� '{'.");
                        break;
                    }
                    case 6:
                    {
                        printf("��������� ������������� ��� �����.");
                        break;
                    }
                    case 7:
                    {
                        printf("��������� '+', '-' ��� ')'.");
                        break;
                    }
                    case 8:
                    {
                        printf("��������� 'cout'.");
                        break;
                    }
                    case 9:
                    {
                        printf("��������� '<<' ��� ';'.");
                        break;
                    }
                    case 10:
                    {
                        printf("��������� 'cin'.");
                        break;
                    }
                    case 11:
                    {
                        printf("��������� '*', '/' ��� ')'.");
                        break;
                    }
                    case 12:
                    {
                        printf("��������� '}'.");
                        break;
                    }
                    case 13:
                    {
                        printf("��������� ';'.");
                        break;
                    }
                    case 14:
                    {
                        printf("��������� �����, ������������� ��� '('.");
                        break;
                    }
                    case 15:
                    {
                        printf("��������� 'if'.");
                        break;
                    }
                    case 16:
                    {
                        printf("��������� ��������� ���������.");
                        break;
                    }
                    case 17:
                    {
                        printf("��������� 'for'.");
                        break;
                    }
                    case 18:
                    {
                        printf("��������� 'while'.");
                        break;
                    }
                    case 19:
                    {
                        printf("��������� 'main'.");
                        break;
                    }
                    case 20:
                    {
                        printf("��������� 'type', �������������, 'cin', 'cout', 'if', 'for', 'while' ��� '}'.");
                        break;
                    }
                    case 21:
                    {
                        printf("��������� '=' ��� ';'.");
                        break;
                    }
                    case 22:
                    {
                        printf("��������� ���������, ������������� ��� '('.");
                        break;
                    }
                    case 23:
                    {
                        printf("��������� �����.");
                        break;
                    }
                    case 24:
                    {
                        printf("��������� '='.");
                        break;
                    }
                    case 25:
                    {
                        printf("��������� '>>'.");
                        break;
                    }
                    case 26:
                    {
                        printf("��������� '<<'.");
                        break;
                    }
                    case 27:
                    {
                        printf("��������� '('.");
                        break;
                    }
                    case 28:
                    {
                        printf("��������� ')'.");
                        break;
                    }
                    case 29:
                    {
                        printf("��������� 'else'.");
                        break;
                    }
                    case 30:
                    {
                        printf("��������� '&&' ��� '||'.");
                        break;
                    }
                    case 31:
                    {
                        printf("��������� '==', '<=', '>=', '!=', '>' ��� '<'.");
                        break;
                    }
                    case 32:
                    {
                        printf("��������� '+' ��� '-'.");
                        break;
                    }
                    case 33:
                    {
                        printf("��������� '*' ��� '/'.");
                        break;
                    }
                    case 34:
                    {
                        printf("��������� ����� �����.");
                        break;
                    }
                }
                printf(" ������ %d ������� %d\n", p->numOfString, p->position);
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
                        printf(" ---=== *** ������ � ������ ������� *** ===---\n");
                        break;
                    }
                    case 1:
                    {
                        printf("�������� ������������ ������� ����������� ������, ������ %d. ������ %d ������� %d\n", max_level_blocks, p->numOfString, p->position);
                        break;
                    }
                    case 2:
                    {
                        printf("� ����� ����� �� ����� ���� ����� max_amount_podblocs ��������� ������ ������� ������. ������ %d ������� %d\n", p->numOfString, p->position);
                        break;
                    }
					case 3:
                    {
                        printf("��������� �������� ����� � �����. ������ %d ������� %d\n", p->numOfString, p->position);
                        break;
                    }
					case 4:
                    {
                        printf("�������� ����� �������� ���������������. ������������ ���������� ���� � ��������� - %d. ������ %d ������� %d\n", max_amount_id, p->numOfString, p->position);
                        break;
                    }
					case 5:
                    {
                        printf("������������ �����. ������ %d ������� %d\n", p->numOfString, p->position);
                        break;
                    }
					case 6:
                    {
                        printf("����������� �������� �������������� � ���������. ������ %d ������� %d\n", p->numOfString, p->position);
                        break;
                    }
					case 7:
                    {
                        printf("�������� ����� ��������� ��������� ���������� ������. ������ - %d. ������ %d ������� %d\n", max_amount_print, p->numOfString, p->position);
                        break;
                    }
					case 8:
                    {
                        printf("������ � �������������� ���������. ������ %d ������� %d\n", p->numOfString, p->position);
                        break;
                    }
					case 9:
                    {
                        printf("������ ��������� �� �������� �������. ������ %d ������� %d\n", p->numOfString, p->position);
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

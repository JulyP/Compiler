#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

    // DATA
int Tab[47][24];				    //таблица, в ячейках которой хранятся номера ошибок и номера правил,
                                    //числа обозначающие выброс и допуск, таблица разбора
struct nodeToStack	                //узел стека
{
	int numOfRule;			        //номер правила (из грамматики)
	int token;			            //номер лексемы (терм. символа) и нетерм. символа
	int numToken;                   //номер атрибута (от 1 до 39)
	int value;                      //номер в таблице имен или констант
	int numString;                  //номер строки
	int position;                   //позиция в строке(в буфере)
	struct nodeToStack *next;	    //указатель на следующий элемент
};
struct nodeToStack *HeadSeqOfRule;  //Цепочка правил
struct nodeToStack *HeadOfStack;    //Стек для разбора (используется во время построения цепочки)

int numOfTokenOfChain;			    //номер текущего токена

    // FUNC
                                    //удаляем из стека вершину
int DelNodeFromStack(struct nodeToStack **p)
{
    struct nodeToStack *p1 = (*p);
    (*p) = (*p) -> next;
    free(p1);
    return 0;
}

                                    //удаляем лексему из потока лексем
int DelToken(struct node **p)
{
    struct node *p1 = (*p);
    (*p) = (*p) -> next;
    free(p1);
    return 0;
}

int NumFromStack(struct node **p)   //возвращает число, которое находится в верхушке стека (потока лексем)
{
    return (*p) -> n.numToken;
}

                                    //добавляет в посл-ть (в конец посл-ти) правил номер правила, атр.токена
int AddNodeToSeqOfRules(struct nodeToStack **HeadSeqOfRule, int rule, int token, int numToken, int position, int numString, int value)
{
    struct nodeToStack *p1, *p = (struct nodeToStack*)malloc(sizeof(struct nodeToStack));
    p -> numOfRule = rule;
    p -> numToken = numToken;
    p -> token = token;
    p -> next = NULL;
    p -> position = position;
    p -> numString = numString;
    p -> value = value;
    p1 = (*HeadSeqOfRule);
    if (p1 != NULL)
    {
        while (p1->next != NULL)
        {
            p1 = p1 -> next;
        }
        p1 -> next = p;
    }
    else
    {
        *HeadSeqOfRule = p;
    }
    return 0;
}

                                    //добавляет в стек номер нетерминала или лексемы
int AddNodeToStack (struct nodeToStack **HeadOfStack, int N_or_t)
{
    struct nodeToStack *p = (struct nodeToStack*)malloc(sizeof(struct nodeToStack));
    p -> numOfRule = 0;
    p -> token = N_or_t;
    p -> next = (*HeadOfStack);
    (*HeadOfStack) = p;

/*    if (p1 != NULL)
    {
        while (p1 -> next != NULL)
        {
            p1 = p1 -> next;
        }
        p1 -> next = p;
    }
    else
    {
        (*HeadOfStack) = p;
    }
*/
    return 0;
}

                                    //добавляем в дерево узел
struct nodeTree *addNodeToTree(struct nodeTree **p, int i, int j)
{
	struct nodeTree *p1 = (struct nodeTree*)malloc(sizeof(struct nodeTree));
	int k = 0;
	for (k = 0; k < 4; k++)
	{
		p1 -> alpha[k] = NULL;
	}
	p1 -> token = i;
	if (i == 23)
	{
		*p = p1;
	}
	else
	{
		(*p) -> alpha[j] = p1;
	}
	return p1;
}

void printTree()                    //печать синтаксического дерева
{
	printf("%d\n",Root->token);
	printf("%d\n",Root->alpha[1]->token);
	printf("%d\n",Root->alpha[2]->token);
	printf("%d\n",Root->alpha[2]->alpha[2]->token);
}

int Table()                         //заполняет таблицу разбора
{
    int i = 0;
	for (i = 0; i < 24; i++)
	{
		Tab[0][i] = -19;
		Tab[1][i] = -5;
		Tab[2][i] = -12;
		Tab[3][i] = -2;
		Tab[4][i] = -13;
		Tab[5][i] = -1;
		Tab[6][i] = -16;
		Tab[7][i] = -23;
		Tab[8][i] = -24;
		Tab[9][i] = -10;
		Tab[10][i] = -25;
		Tab[11][i] = -8;
		Tab[12][i] = -25;
		Tab[13][i] = -15;
		Tab[14][i] = -27;
		Tab[15][i] = -28;
		Tab[16][i] = -29;
		Tab[17][i] = -17;
		Tab[18][i] = -18;
		Tab[19][i] = -30;
		Tab[20][i] = -31;
		Tab[21][i] = -32;
		Tab[22][i] = -33;
		Tab[i][i] = 0;
		Tab[23][i] = -19;
		Tab[24][i] = -5;
		Tab[25][i] = -20;
		Tab[26][i] = -1;
		Tab[27][i] = -2;
		Tab[28][i] = -10;
		Tab[29][i] = -8;
		Tab[30][i] = -15;
		Tab[31][i] = -17;
		Tab[32][i] = -18;
		Tab[33][i] = -21;
		Tab[34][i] = -22;
		Tab[35][i] = -14;
		Tab[36][i] = -9;
		Tab[37][i] = -14;
		Tab[38][i] = -3;
		Tab[39][i] = -14;
		Tab[40][i] = -4;
		Tab[41][i] = -6;
		Tab[42][i] = -14;
		Tab[43][i] = -7;
		Tab[44][i] = -14;
		Tab[45][i] = -11;
		Tab[46][i] = -34;

	}
	Tab[23][0] = 101;
	Tab[24][1] = 102;
	//25
	Tab[25][2] = 110;
	Tab[25][3] = 104;
	Tab[25][5] = 103;
	Tab[25][9] = 105;
	Tab[25][11] = 106;
	Tab[25][13] = 107;
	Tab[25][17] = 108;
	Tab[25][18] = 109;
	Tab[25][23] = 110;
	//26-32
	Tab[26][5] = 111;
	Tab[27][3] = 116;
	Tab[28][9] = 117;
	Tab[29][11] = 118;
	Tab[30][13] = 121;
	Tab[31][17] = 124;
	Tab[32][18] = 125;
	//33
	Tab[33][4] = 113;
	Tab[33][8] = 112;
	Tab[33][23] = 113;
	//34
	Tab[34][3] = 114;
	Tab[34][6] = 115;
	Tab[34][7] = 114;
	Tab[34][14] = 114;
	//35
	Tab[35][3] = 133;
	Tab[35][7] = 133;
	Tab[35][14] = 133;
	//36
	Tab[36][4] = 119;
	Tab[36][12] = 120;
	Tab[36][23] = 119;
	//37
	Tab[37][3] = 126;
	Tab[37][7] = 126;
	Tab[37][14] = 126;
	//38
	Tab[38][2] = 123;
	Tab[38][3] = 123;
	Tab[38][5] = 123;
	Tab[38][9] = 123;
	Tab[38][11] = 123;
	Tab[38][13] = 123;
	Tab[38][15] = 103;//?????????????????
	Tab[38][16] = 122;
	Tab[38][17] = 123;
	Tab[38][18] = 123;
	Tab[38][23] = 123;
	//39
	Tab[39][3] = 130;
	Tab[39][7] = 130;
	Tab[39][14] = 129;
	//40
	Tab[40][15] = 128;
	Tab[40][19] = 127;
	Tab[40][23] = 128;
	//41
	Tab[41][3] = 131;
	Tab[41][7] = 132;
	Tab[41][3] = 131;
	//42
	Tab[42][3] = 136;
	Tab[42][7] = 136;
	Tab[42][14] = 136;
	//43
	Tab[43][15] = 135;
	Tab[43][21] = 134;
	Tab[43][23] = 135;
	//44
	Tab[44][3] = 121;
	Tab[44][7] = 140;
	Tab[44][14] = 139;
	//45
	Tab[45][15] = 138;
	Tab[45][21] = 138;
	Tab[45][22] = 137;
	Tab[45][23] = 138;
	//46
	Tab[46][23] = 100;
	return 0;
}

                                    //по потоку лексем строит цепочку правил
int TableOfTokensToSeqOfRules (int i)
{
	if (i >= 0)
	//нет ошибки
	{
		if (i == 0)
		//выброс
		{
		    //удаляем из стека вершину
			DelNodeFromStack(&HeadOfStack);
            //увеличиваем счетчик токенов входной цепочки, то есть будем считывать следующую вершину
			//numOfTokenOfChain++;
			DelToken(&Head);
		}
		//правила из грамматики
		else
		{
			//добавляем в цепочку правил правило
			AddNodeToSeqOfRules(&HeadSeqOfRule,i,Head->n.token,Head->n.numToken,Head->n.position,Head->n.numString,Head->n.value);
			switch(i)
			{
			    case 100:
			    {
			        //конец разбора, цепочка построена
			        printf("\n\nEND!\n\n");
			        return 0;
			    }
                case 101:
                {
                    //меняем Prog на main Block
                    DelNodeFromStack(&HeadOfStack);		    //удаляем из стека вершину Prog
                    AddNodeToStack(&HeadOfStack, 24);		//добавляем в стек вершину Block
                    AddNodeToStack(&HeadOfStack, 0);		//добавляем в стек вершину main
                    break;
                }
                case 102:
                {
                    //меняем Block на { Sent }
                    DelNodeFromStack(&HeadOfStack);		    //удаляем из стека вершину Block
                    AddNodeToStack(&HeadOfStack, 2);		//добавляем в стек вершину }
                    AddNodeToStack(&HeadOfStack, 25);		//добавляем в стек вершину Sent
                    AddNodeToStack(&HeadOfStack, 1);		//добавляем в стек вершину {
                    break;
                }
                case 103:
                {
                    //меняем Sent на DescrVar Sent
                    DelNodeFromStack(&HeadOfStack);		    //удаляем из стека вершину Sent
                    AddNodeToStack(&HeadOfStack, 25);		//добавляем в стек вершину Sent
                    AddNodeToStack(&HeadOfStack, 26);		//добавляем в стек вершину DescrVar
                    break;
                }
                case 104:
                {
                    //меняем Sent на OpEqu Sent
                    DelNodeFromStack(&HeadOfStack);		    //удаляем из стека вершину Sent
                    AddNodeToStack(&HeadOfStack, 25);		//добавляем в стек вершину Sent
                    AddNodeToStack(&HeadOfStack, 27);		//добавляем в стек вершину OpEqu
                    break;
                }
                case 105:
                {
                    //меняем Sent на OpIn Sent
                    DelNodeFromStack(&HeadOfStack);		    //удаляем из стека вершину Sent
                    AddNodeToStack(&HeadOfStack, 25);		//добавляем в стек вершину Sent
                    AddNodeToStack(&HeadOfStack, 28);		//добавляем в стек вершину OpIn
                    break;
                }
                case 106:
                {
                    //меняем Sent на OpOut Sent
                    DelNodeFromStack(&HeadOfStack);		    //удаляем из стека вершину Sent
                    AddNodeToStack(&HeadOfStack, 25);		//добавляем в стек вершину Sent
                    AddNodeToStack(&HeadOfStack, 29);		//добавляем в стек вершину OpOut
                    break;
                }
                case 107:
                {
                    //меняем Sent на OpIf Sent
                    DelNodeFromStack(&HeadOfStack);		    //удаляем из стека вершину Sent
                    AddNodeToStack(&HeadOfStack, 25);		//добавляем в стек вершину Sent
                    AddNodeToStack(&HeadOfStack, 30);		//добавляем в стек вершину OpIf
                    break;
                }
                case 108:
                {
                    //меняем Sent на OpFor Sent
                    DelNodeFromStack(&HeadOfStack);		    //удаляем из стека вершину Sent
                    AddNodeToStack(&HeadOfStack, 25);		//добавляем в стек вершину Sent
                    AddNodeToStack(&HeadOfStack, 31);		//добавляем в стек вершину OpFor
                    break;
                }
                case 109:
                {
                    //меняем Sent на OpWhile Sent
                    DelNodeFromStack(&HeadOfStack);		    //удаляем из стека вершину Sent
                    AddNodeToStack(&HeadOfStack, 25);		//добавляем в стек вершину Sent
                    AddNodeToStack(&HeadOfStack, 32);		//добавляем в стек вершину OpWhile
                    break;
                }
                case 110:
                {
                    //меняем Sent на пустой символ
                    DelNodeFromStack(&HeadOfStack);		    //удаляем из стека вершину Sent
                    break;
                }
                case 111:
                {
                    //меняем DescrVar на type id EquExpr
                    DelNodeFromStack(&HeadOfStack);		    //удаляем из стека вершину DescrVar
                    AddNodeToStack(&HeadOfStack, 33);		//добавляем в стек вершину EquExpr
                    AddNodeToStack(&HeadOfStack, 3);		//добавляем в стек вершину id
                    AddNodeToStack(&HeadOfStack, 5);		//добавляем в стек вершину type
                    break;
                }
                case 112:
                {
                    //EquExpr -> = Expr
                    DelNodeFromStack(&HeadOfStack);		    //удаляем из стека вершину EquExpr
                    AddNodeToStack(&HeadOfStack, 34);		//добавляем в стек вершину Expr
                    AddNodeToStack(&HeadOfStack, 8);		//добавляем в стек вершину =
                    break;
                }
                case 113:
                {
                    //EquExpr ->  Л
                    DelNodeFromStack(&HeadOfStack);		    //удаляем из стека вершину EquExpr
                    break;
                }
                case 114:
                {
                    //Expr -> ArExpr
                    DelNodeFromStack(&HeadOfStack);		    //удаляем из стека вершину Expr
                    AddNodeToStack(&HeadOfStack, 35);		//добавляем в стек вершину ArExpr
                    break;
                }
                case 115:
                {
                    //Expr -> conststr
                    DelNodeFromStack(&HeadOfStack);		    //удаляем из стека вершину Expr
                    AddNodeToStack(&HeadOfStack, 6);		//добавляем в стек вершину conststr
                    break;
                }
                case 116:
                {
                    // OpEqu -> id = Expr ;
                    DelNodeFromStack(&HeadOfStack);		    //удаляем из стека вершину OpEqu
                    AddNodeToStack(&HeadOfStack, 4);		//добавляем в стек вершину ;
                    AddNodeToStack(&HeadOfStack, 34);		//добавляем в стек вершину Expr
                    AddNodeToStack(&HeadOfStack, 8);		//добавляем в стек вершину =
                    AddNodeToStack(&HeadOfStack, 3);		//добавляем в стек вершину id
                    break;
                }
                case 117:
                {
                    // OpIn  ->  cin >> id ;
                    DelNodeFromStack(&HeadOfStack);		    //удаляем из стека вершину OpIn
                    AddNodeToStack(&HeadOfStack, 4);		//добавляем в стек вершину ;
                    AddNodeToStack(&HeadOfStack, 3);		//добавляем в стек вершину id
                    AddNodeToStack(&HeadOfStack, 10);		//добавляем в стек вершину >>
                    AddNodeToStack(&HeadOfStack, 9);		//добавляем в стек вершину cin
                    break;

                }
                case 118:
                {
                    // OpOut -> cout  Expr FuncOut ;
                    DelNodeFromStack(&HeadOfStack);		    //удаляем из стека вершину OpOut
                    AddNodeToStack(&HeadOfStack, 4);		//добавляем в стек вершину ;
                    AddNodeToStack(&HeadOfStack, 3);		//добавляем в стек вершину FuncOut
                    AddNodeToStack(&HeadOfStack, 10);		//добавляем в стек вершину Expr
                    AddNodeToStack(&HeadOfStack, 9);		//добавляем в стек вершину cout
                    break;
                }
                case 119:
                {
                    // FuncOut -> Л
                    DelNodeFromStack(&HeadOfStack);		    //удаляем из стека вершину FuncOut
                    break;
                }
                case 120:
                {
                    // FuncOut -> << Expr FuncOut
                    DelNodeFromStack(&HeadOfStack);		    //удаляем из стека вершину FuncOut
                    AddNodeToStack(&HeadOfStack, 3);		//добавляем в стек вершину FuncOut
                    AddNodeToStack(&HeadOfStack, 10);		//добавляем в стек вершину Expr
                    AddNodeToStack(&HeadOfStack, 12);		//добавляем в стек вершину <<
                    break;
                }
                case 121:
                {
                    // OpIf -> if  (CondExpr ) Block  Else
                    DelNodeFromStack(&HeadOfStack);		    //удаляем из стека вершину OpIf
                    AddNodeToStack(&HeadOfStack, 38);		//добавляем в стек вершину Else
                    AddNodeToStack(&HeadOfStack, 24);		//добавляем в стек вершину Block
                    AddNodeToStack(&HeadOfStack, 15);		//добавляем в стек вершину )
                    AddNodeToStack(&HeadOfStack, 37);		//добавляем в стек вершину CondExpr
                    AddNodeToStack(&HeadOfStack, 14);		//добавляем в стек вершину (
                    AddNodeToStack(&HeadOfStack, 13);		//добавляем в стек вершину if
                    break;
                }
                case 122:
                {
                    // Else -> else Block
                    DelNodeFromStack(&HeadOfStack);		    //удаляем из стека вершину Else
                    AddNodeToStack(&HeadOfStack, 24);		//добавляем в стек вершину Block
                    AddNodeToStack(&HeadOfStack, 16);		//добавляем в стек вершину else
                    break;
                }
                case 123:
                {
                    // Else -> Л
                    DelNodeFromStack(&HeadOfStack);		    //удаляем из стека вершину Else
                    break;
                }
                case 124:
                {
                    // OpFor -> for ( OpEqu ; CondExpr; ArExpr) Block
                    DelNodeFromStack(&HeadOfStack);		    //удаляем из стека вершину OpFor
                    AddNodeToStack(&HeadOfStack, 24);		//добавляем в стек вершину Block
                    AddNodeToStack(&HeadOfStack, 15);		//добавляем в стек вершину )
                    AddNodeToStack(&HeadOfStack, 35);		//добавляем в стек вершину ArExpr
                    AddNodeToStack(&HeadOfStack, 4);		//добавляем в стек вершину ;
                    AddNodeToStack(&HeadOfStack, 37);		//добавляем в стек вершину CondExpr
                    AddNodeToStack(&HeadOfStack, 4);		//добавляем в стек вершину ;
                    AddNodeToStack(&HeadOfStack, 27);		//добавляем в стек вершину OpEqu
                    AddNodeToStack(&HeadOfStack, 14);		//добавляем в стек вершину (
                    AddNodeToStack(&HeadOfStack, 17);		//добавляем в стек вершину for
                    break;
                }
                case 125:
                {
                    // OpWhile -> while (CondExpr) Block
                    DelNodeFromStack(&HeadOfStack);		    //удаляем из стека вершину OpWhile
                    AddNodeToStack(&HeadOfStack, 24);		//добавляем в стек вершину Block
                    AddNodeToStack(&HeadOfStack, 15);		//добавляем в стек вершину )
                    AddNodeToStack(&HeadOfStack, 37);		//добавляем в стек вершину CondExpr
                    AddNodeToStack(&HeadOfStack, 14);		//добавляем в стек вершину (
                    AddNodeToStack(&HeadOfStack, 18);		//добавляем в стек вершину while
                    break;
                }
                case 126:
                {
                    // CondExpr -> DiffCondExpr  SecDCE
                    DelNodeFromStack(&HeadOfStack);		    //удаляем из стека вершину CondExpr
                    AddNodeToStack(&HeadOfStack, 40);		//добавляем в стек вершину SecDCE
                    AddNodeToStack(&HeadOfStack, 39);		//добавляем в стек вершину DiffCondExpr
                    break;
                }
                case 127:
                case 128:
                case 129:
                case 130:
                case 131:
                case 132:
                case 133:
                case 134:
                case 135:
                case 136:
                case 137:
                case 138:
                case 139:
                case 140:
                case 141:
			}
		}
		//продолжаем разбор
		TableOfTokensToSeqOfRules(Tab[HeadOfStack -> token][Head -> n.token]);
		return 0;
	}
	//ошибка
	else
	{
		//Error(i);
		return 1;
	}
}

int SA()                             //вызываем СиА
{
	numOfTokenOfChain = 0;
	Table();
	int j = 0, i = 0;
/*	for (i = 0; i < 47; i++)
	{
		for (j = 0; j < 24; j++)
		{
			printf("%d ",Tab[i][j]);
		}
		printf("\n\n");
	}
*/
	HeadOfStack = NULL;
    //добавляем в стек Prog (23)
	AddNodeToStack(&HeadOfStack, 23);

    //строим цепочку, начинаем с первой лексемы
    HeadSeqOfRule = NULL;
	TableOfTokensToSeqOfRules(Tab[HeadOfStack -> token][Head -> n.token]);

	struct nodeToStack *p = HeadSeqOfRule;
	printf("\n\n~~~seq~~~\n\n");
	while(p != NULL)
	{
	    printf("%d - ", p->numOfRule);
	    p = p->next;
	}
	printf("\n\n");
	while(p != NULL)
	{
        p = HeadSeqOfRule;
        HeadSeqOfRule = p -> next;
	    free(p);
	}

	//BuildingOfTree(p,101,0);				//строим дерево
	addNodeToTree(&Root, 23, 1);
	addNodeToTree(&Root, 21, 1);
	struct nodeTree *pp = addNodeToTree(&Root, 0, 2);
	addNodeToTree(&pp, 4, 2);

	return 0;
}

#endif // PARSER_H_INCLUDED

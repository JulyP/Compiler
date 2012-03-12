#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

// ***DATA***
int Tab[47][24];				    //�������, � ������� ������� �������� ������ ������ � ������ ������,
                                    //����� ������������ ������ � ������, ������� �������
struct nodeToStack	                //���� �����
{
	int numOfRule;			        //����� ������� (�� ����������)
	int token;			            //����� ������� (����. �������) � ������. �������
	int numToken;                   //����� �������� (�� 1 �� 39)
	int value;                      //����� � ������� ���� ��� ��������
	int numString;                  //����� ������
	int position;                   //������� � ������(� ������)
	struct nodeToStack *next;	    //��������� �� ��������� �������
};
struct nodeToStack *HeadSeqOfRule;  //������� ������
struct nodeToStack *HeadOfStack;    //���� ��� ������� (������������ �� ����� ���������� �������)

int numOfTokenOfChain;			    //����� �������� ������


// ***FUNC***
//������� �� ����� �������
int DelNodeFromStack(struct nodeToStack **p)
{
    struct nodeToStack *p1 = (*p);
    (*p) = (*p) -> next;
    free(p1);
    return 0;
}

//������� ������� �� ������ ������
int DelToken(struct node **p)
{
    struct node *p1 = (*p);
    (*p) = (*p) -> next;
    free(p1);
    return 0;
}

//���������� �����, ������� ��������� � �������� ����� (������ ������)
int NumFromStack(struct node **p)
{
    return (*p) -> n.numToken;
}

//��������� � ����-�� (� ����� ����-��) ������ ����� �������, ���.������
int AddNodeToSeqOfRules(struct nodeToStack **pp, int rule, int token, int numToken, int position, int numString, int value)
{
    struct nodeToStack *p1, *p = (struct nodeToStack*)malloc(sizeof(struct nodeToStack));
    p -> numOfRule = rule;
    p -> numToken = numToken;
    p -> token = token;
    p -> next = NULL;
    p -> position = position;
    p -> numString = numString;
    p -> value = value;
    p1 = (*pp);
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
        *pp = p;
    }
    return 0;
}

//��������� � ���� ����� ����������� ��� �������
int AddNodeToStack (struct nodeToStack **pp, int N_or_t)
{
    struct nodeToStack *p = (struct nodeToStack*)malloc(sizeof(struct nodeToStack));
    p -> numOfRule = 0;
    p -> token = N_or_t;
    p -> next = (*pp);
    (*pp) = p;
    return 0;
}

//��������� � ������ ����
struct nodeTree *addNodeToTree(struct nodeTree **p, struct nodeToStack *p1, int neterminal, int j)
{
	struct nodeTree *p2 = (struct nodeTree*)malloc(sizeof(struct nodeTree));
	int k = 0;
	for (k = 0; k < 4; k++)
	{
		p2 -> alpha[k] = NULL;
	}
	p2 -> token = neterminal;                   //����� ������� (0 - 22), (23 - 46)
	p2 -> numToken = p1 -> numToken;            //����� �������� (�� 1 �� 39)
	p2 -> value = p1 -> value;                  //����� � ������� ���� ��� ��������
	p2 -> numString = p1 -> numString;          //����� ������
	p2 -> position = p1 -> position;            //������� � ������(� ������)
	if (neterminal == 23)
	{
		(*p) = p2;
	}
	else
	{
	    if (j == 0)
	    {
	        (*p) -> alpha[j] = p2;
	    }
	    else
	    {
            (*p) -> alpha[j-1] = p2;
	    }
	}
	return p2;
}

//��������� ������� �������
int Table()
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
	Tab[38][15] = 103;//??????
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

//�� ������ ������ ������ ������� ������
int TableOfTokensToSeqOfRules (int i)
{
	if (i >= 0)
	//��� ������
	{
		if (i == 0)
		//������
		{
		    //������� �� ����� �������
			DelNodeFromStack(&HeadOfStack);
            //����������� ������� ������� ������� �������, �� ���� ����� ��������� ��������� �������
			//numOfTokenOfChain++;
			DelToken(&Head);
		}
		//������� �� ����������
		else
		{
			//��������� � ������� ������ �������
			AddNodeToSeqOfRules(&HeadSeqOfRule,i,Head->n.token,Head->n.numToken,Head->n.position,Head->n.numString,Head->n.value);
			switch(i)
			{
			    case 100:
			    {
			        //����� �������, ������� ���������
			        printf("\n\nEND!\n\n");
			        return 0;
			    }
                case 101:
                {
                    //������ Prog �� main Block
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� Prog
                    AddNodeToStack(&HeadOfStack, 24);		//��������� � ���� ������� Block
                    AddNodeToStack(&HeadOfStack, 0);		//��������� � ���� ������� main
                    break;
                }
                case 102:
                {
                    //������ Block �� { Sent }
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� Block
                    AddNodeToStack(&HeadOfStack, 2);		//��������� � ���� ������� }
                    AddNodeToStack(&HeadOfStack, 25);		//��������� � ���� ������� Sent
                    AddNodeToStack(&HeadOfStack, 1);		//��������� � ���� ������� {
                    break;
                }
                case 103:
                {
                    //������ Sent �� DescrVar Sent
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� Sent
                    AddNodeToStack(&HeadOfStack, 25);		//��������� � ���� ������� Sent
                    AddNodeToStack(&HeadOfStack, 26);		//��������� � ���� ������� DescrVar
                    break;
                }
                case 104:
                {
                    //������ Sent �� OpEqu Sent
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� Sent
                    AddNodeToStack(&HeadOfStack, 25);		//��������� � ���� ������� Sent
                    AddNodeToStack(&HeadOfStack, 27);		//��������� � ���� ������� OpEqu
                    break;
                }
                case 105:
                {
                    //������ Sent �� OpIn Sent
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� Sent
                    AddNodeToStack(&HeadOfStack, 25);		//��������� � ���� ������� Sent
                    AddNodeToStack(&HeadOfStack, 28);		//��������� � ���� ������� OpIn
                    break;
                }
                case 106:
                {
                    //������ Sent �� OpOut Sent
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� Sent
                    AddNodeToStack(&HeadOfStack, 25);		//��������� � ���� ������� Sent
                    AddNodeToStack(&HeadOfStack, 29);		//��������� � ���� ������� OpOut
                    break;
                }
                case 107:
                {
                    //������ Sent �� OpIf Sent
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� Sent
                    AddNodeToStack(&HeadOfStack, 25);		//��������� � ���� ������� Sent
                    AddNodeToStack(&HeadOfStack, 30);		//��������� � ���� ������� OpIf
                    break;
                }
                case 108:
                {
                    //������ Sent �� OpFor Sent
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� Sent
                    AddNodeToStack(&HeadOfStack, 25);		//��������� � ���� ������� Sent
                    AddNodeToStack(&HeadOfStack, 31);		//��������� � ���� ������� OpFor
                    break;
                }
                case 109:
                {
                    //������ Sent �� OpWhile Sent
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� Sent
                    AddNodeToStack(&HeadOfStack, 25);		//��������� � ���� ������� Sent
                    AddNodeToStack(&HeadOfStack, 32);		//��������� � ���� ������� OpWhile
                    break;
                }
                case 110:
                {
                    //������ Sent �� ������ ������
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� Sent
                    break;
                }
                case 111:
                {
                    //������ DescrVar �� type id EquExpr
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� DescrVar
                    AddNodeToStack(&HeadOfStack, 33);		//��������� � ���� ������� EquExpr
                    AddNodeToStack(&HeadOfStack, 3);		//��������� � ���� ������� id
                    AddNodeToStack(&HeadOfStack, 5);		//��������� � ���� ������� type
                    break;
                }
                case 112:
                {
                    //EquExpr -> = Expr
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� EquExpr
                    AddNodeToStack(&HeadOfStack, 34);		//��������� � ���� ������� Expr
                    AddNodeToStack(&HeadOfStack, 8);		//��������� � ���� ������� =
                    break;
                }
                case 113:
                {
                    //EquExpr ->  �
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� EquExpr
                    break;
                }
                case 114:
                {
                    //Expr -> ArExpr
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� Expr
                    AddNodeToStack(&HeadOfStack, 35);		//��������� � ���� ������� ArExpr
                    break;
                }
                case 115:
                {
                    //Expr -> conststr
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� Expr
                    AddNodeToStack(&HeadOfStack, 6);		//��������� � ���� ������� conststr
                    break;
                }
                case 116:
                {
                    // OpEqu -> id = Expr ;
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� OpEqu
                    AddNodeToStack(&HeadOfStack, 4);		//��������� � ���� ������� ;
                    AddNodeToStack(&HeadOfStack, 34);		//��������� � ���� ������� Expr
                    AddNodeToStack(&HeadOfStack, 8);		//��������� � ���� ������� =
                    AddNodeToStack(&HeadOfStack, 3);		//��������� � ���� ������� id
                    break;
                }
                case 117:
                {
                    // OpIn  ->  cin >> id ;
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� OpIn
                    AddNodeToStack(&HeadOfStack, 4);		//��������� � ���� ������� ;
                    AddNodeToStack(&HeadOfStack, 3);		//��������� � ���� ������� id
                    AddNodeToStack(&HeadOfStack, 10);		//��������� � ���� ������� >>
                    AddNodeToStack(&HeadOfStack, 9);		//��������� � ���� ������� cin
                    break;

                }
                case 118:
                {
                    // OpOut -> cout  Expr FuncOut ;
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� OpOut
                    AddNodeToStack(&HeadOfStack, 4);		//��������� � ���� ������� ;
                    AddNodeToStack(&HeadOfStack, 3);		//��������� � ���� ������� FuncOut
                    AddNodeToStack(&HeadOfStack, 10);		//��������� � ���� ������� Expr
                    AddNodeToStack(&HeadOfStack, 9);		//��������� � ���� ������� cout
                    break;
                }
                case 119:
                {
                    // FuncOut -> �
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� FuncOut
                    break;
                }
                case 120:
                {
                    // FuncOut -> << Expr FuncOut
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� FuncOut
                    AddNodeToStack(&HeadOfStack, 3);		//��������� � ���� ������� FuncOut
                    AddNodeToStack(&HeadOfStack, 10);		//��������� � ���� ������� Expr
                    AddNodeToStack(&HeadOfStack, 12);		//��������� � ���� ������� <<
                    break;
                }
                case 121:
                {
                    // OpIf -> if  (CondExpr ) Block  Else
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� OpIf
                    AddNodeToStack(&HeadOfStack, 38);		//��������� � ���� ������� Else
                    AddNodeToStack(&HeadOfStack, 24);		//��������� � ���� ������� Block
                    AddNodeToStack(&HeadOfStack, 15);		//��������� � ���� ������� )
                    AddNodeToStack(&HeadOfStack, 37);		//��������� � ���� ������� CondExpr
                    AddNodeToStack(&HeadOfStack, 14);		//��������� � ���� ������� (
                    AddNodeToStack(&HeadOfStack, 13);		//��������� � ���� ������� if
                    break;
                }
                case 122:
                {
                    // Else -> else Block
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� Else
                    AddNodeToStack(&HeadOfStack, 24);		//��������� � ���� ������� Block
                    AddNodeToStack(&HeadOfStack, 16);		//��������� � ���� ������� else
                    break;
                }
                case 123:
                {
                    // Else -> �
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� Else
                    break;
                }
                case 124:
                {
                    // OpFor -> for ( OpEqu ; CondExpr; ArExpr) Block
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� OpFor
                    AddNodeToStack(&HeadOfStack, 24);		//��������� � ���� ������� Block
                    AddNodeToStack(&HeadOfStack, 15);		//��������� � ���� ������� )
                    AddNodeToStack(&HeadOfStack, 35);		//��������� � ���� ������� ArExpr
                    AddNodeToStack(&HeadOfStack, 4);		//��������� � ���� ������� ;
                    AddNodeToStack(&HeadOfStack, 37);		//��������� � ���� ������� CondExpr
                    AddNodeToStack(&HeadOfStack, 4);		//��������� � ���� ������� ;
                    AddNodeToStack(&HeadOfStack, 27);		//��������� � ���� ������� OpEqu
                    AddNodeToStack(&HeadOfStack, 14);		//��������� � ���� ������� (
                    AddNodeToStack(&HeadOfStack, 17);		//��������� � ���� ������� for
                    break;
                }
                case 125:
                {
                    // OpWhile -> while (CondExpr) Block
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� OpWhile
                    AddNodeToStack(&HeadOfStack, 24);		//��������� � ���� ������� Block
                    AddNodeToStack(&HeadOfStack, 15);		//��������� � ���� ������� )
                    AddNodeToStack(&HeadOfStack, 37);		//��������� � ���� ������� CondExpr
                    AddNodeToStack(&HeadOfStack, 14);		//��������� � ���� ������� (
                    AddNodeToStack(&HeadOfStack, 18);		//��������� � ���� ������� while
                    break;
                }
                case 126:
                {
                    // CondExpr -> DiffCondExpr  SecDCE
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� CondExpr
                    AddNodeToStack(&HeadOfStack, 40);		//��������� � ���� ������� SecDCE
                    AddNodeToStack(&HeadOfStack, 39);		//��������� � ���� ������� DiffCondExpr
                    break;
                }
                case 127:
                {
                    // SecDCE -> compop DiffCondExpr  SecDCE
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� SecDCE
                    AddNodeToStack(&HeadOfStack, 40);		//��������� � ���� ������� SecDCE
                    AddNodeToStack(&HeadOfStack, 39);		//��������� � ���� ������� DiffCondExpr
                    AddNodeToStack(&HeadOfStack, 19);		//��������� � ���� ������� compop
                    break;
                }
                case 128:
                {
                    // SecDCE -> �
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� SecDCE
                    break;
                }
                case 129:
                {
                    // DiffCondExpr -> (CondExpr)
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� DiffCondExpr
                    AddNodeToStack(&HeadOfStack, 15);		//��������� � ���� ������� )
                    AddNodeToStack(&HeadOfStack, 37);		//��������� � ���� ������� CondExpr
                    AddNodeToStack(&HeadOfStack, 14);		//��������� � ���� ������� (
                    break;
                }
                case 130:
                {
                    // DiffCondExpr -> SimpCondExpr
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� DiffCondExpr
                    AddNodeToStack(&HeadOfStack, 41);		//��������� � ���� ������� SimpCondExpr
                    break;
                }
                case 131:
                {
                    // SimpCondExpr -> id relop ArExpr
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� SimpCondExpr
                    AddNodeToStack(&HeadOfStack, 35);		//��������� � ���� ������� ArExpr
                    AddNodeToStack(&HeadOfStack, 20);		//��������� � ���� ������� relop
                    AddNodeToStack(&HeadOfStack, 3);		//��������� � ���� ������� id
                    break;
                }
                case 132:
                {
                    // SimpCondExpr -> constnum relop ArExpr
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� SimpCondExpr
                    AddNodeToStack(&HeadOfStack, 35);		//��������� � ���� ������� ArExpr
                    AddNodeToStack(&HeadOfStack, 20);		//��������� � ���� ������� relop
                    AddNodeToStack(&HeadOfStack, 7);		//��������� � ���� ������� constnum
                    break;
                }
                case 133:
                {
                    // ArExpr -> Addendum SecAddendum
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� ArExpr
                    AddNodeToStack(&HeadOfStack, 43);		//��������� � ���� ������� SecAddendum
                    AddNodeToStack(&HeadOfStack, 42);		//��������� � ���� ������� Addendum
                    break;
                }
                case 134:
                {
                    // SecAddendum -> addop Addendum SecAddendum
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� SecAddendum
                    AddNodeToStack(&HeadOfStack, 43);		//��������� � ���� ������� SecAddendum
                    AddNodeToStack(&HeadOfStack, 42);		//��������� � ���� ������� Addendum
                    AddNodeToStack(&HeadOfStack, 21);		//��������� � ���� ������� addop
                    break;
                }
                case 135:
                {
                    // SecAddendum -> �
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� SecAddendum
                    break;
                }
                case 136:
                {
                    // Addendum -> Multiplier SecMultiplier
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� Addendum
                    AddNodeToStack(&HeadOfStack, 45);		//��������� � ���� ������� SecMultiplier
                    AddNodeToStack(&HeadOfStack, 44);		//��������� � ���� ������� Multiplier
                    break;
                }
                case 137:
                {
                    // SecMultiplier -> multop Multiplier SecMultiplier
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� SecMultiplier
                    AddNodeToStack(&HeadOfStack, 45);		//��������� � ���� ������� SecMultiplier
                    AddNodeToStack(&HeadOfStack, 44);		//��������� � ���� ������� Multiplier
                    AddNodeToStack(&HeadOfStack, 22);		//��������� � ���� ������� multop
                    break;
                }
                case 138:
                {
                    // SecMultiplier -> �
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� SecMultiplier
                    break;
                }
                case 139:
                {
                    // Multiplier -> ( ArExpr)
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� Multiplier
                    AddNodeToStack(&HeadOfStack, 15);		//��������� � ���� ������� )
                    AddNodeToStack(&HeadOfStack, 35);		//��������� � ���� ������� ArExpr
                    AddNodeToStack(&HeadOfStack, 14);		//��������� � ���� ������� (
                    break;
                }
                case 140:
                {
                    // Multiplier -> constnum
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� Multiplier
                    AddNodeToStack(&HeadOfStack, 7);		//��������� � ���� ������� constnum
                    break;
                }
                case 141:
                {
                    // Multiplier -> id
                    DelNodeFromStack(&HeadOfStack);		    //������� �� ����� ������� Multiplier
                    AddNodeToStack(&HeadOfStack, 3);		//��������� � ���� ������� id
                    break;
                }
			}
		}
		//���������� ������
		TableOfTokensToSeqOfRules(Tab[HeadOfStack -> token][Head -> n.token]);
		return 0;
	}
	//������
	else
	{
		//Error(i);
		return 1;
	}
}

//���������� �����, ������� ��������� � �������� ����-�� (������� ������)
struct nodeToStack* DelNumFromSeqOfRule(struct nodeToStack **pp)
{
    if ((*pp) == NULL)
    {
        return NULL;
    }
    struct nodeToStack *p1, *p = (struct nodeToStack*)malloc(sizeof(struct nodeToStack));
    p -> numOfRule = (*pp) -> numOfRule;    //����� ������� (�� ����������)
	p -> token = (*pp) -> token;            //����� ������� (����. �������) � ������. �������
	p -> numToken = (*pp) -> numToken;      //����� �������� (�� 1 �� 39)
	p -> value = (*pp) -> value;            //����� � ������� ���� ��� ��������
	p -> numString = (*pp) -> numString;    //����� ������
	p -> position = (*pp) -> position;      //������� � ������(� ������)
	p -> next = NULL;

	p1 = (*pp);
	(*pp) = (*pp) -> next;
	free(p1);
	return p;
}

//�� ������������������ ������ ������ ������������� ������
int BuildingOfTree (struct nodeTree **p, struct nodeToStack *p1)
{
	struct nodeTree *newP;
	struct nodeToStack *fromHead;
	if(p1 == NULL)
	{
	    return 0;
	}
	switch(p1->numOfRule)
	{
        case 101:
		{
			newP = addNodeToTree(&(*p),p1,23,1);
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			break;
		}
        case 102:
		{
			newP = addNodeToTree(&(*p),p1,24,1);
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			break;
		}
        case 103:
		{
			newP = addNodeToTree(&(*p),p1,25,2);
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			//fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			break;
		}
        case 104:
		{
			newP = addNodeToTree(&(*p),p1,25,2);
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			//fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			break;
		}
        case 105:
		{
			newP = addNodeToTree(&(*p),p1,25,2);
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			//fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			break;
		}
        case 106:
		{
			newP = addNodeToTree(&(*p),p1,25,2);
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			//fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			break;
		}
        case 107:
		{
			newP = addNodeToTree(&(*p),p1,25,2);
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			//fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			break;
		}
        case 108:
		{
			newP = addNodeToTree(&(*p),p1,25,2);
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			//fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			break;
		}
        case 109:
		{
			newP = addNodeToTree(&(*p),p1,25,2);
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			//fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			break;
		}
        case 110:
		{
			addNodeToTree(&(*p),p1,25,1);
			break;
		}
        case 111:
		{
			newP = addNodeToTree(&(*p),p1,26,3);
			addNodeToTree(&newP,p1,5,0);
			addNodeToTree(&newP,p1,3,0);
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			break;
		}
        case 112:
		{
			newP = addNodeToTree(&(*p),p1,33,1);
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			break;
		}
        case 113:
		{
			addNodeToTree(&(*p),p1,33,0);
			break;
		}
        case 114:
		{
			newP = addNodeToTree(&(*p),p1,34,1);
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			break;
		}
        case 115:
		{
			newP = addNodeToTree(&(*p),p1,34,1);
			addNodeToTree(&newP,p1,6,0);
			break;
		}
        case 116:
		{
			newP = addNodeToTree(&(*p),p1,27,2);
			addNodeToTree(&newP,p1,3,0);
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			break;
		}
        case 117:
		{
			newP = addNodeToTree(&(*p),p1,28,1);
			addNodeToTree(&newP,p1,3,0);
			break;
		}
        case 118:
		{
			newP = addNodeToTree(&(*p),p1,29,2);
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			//fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			break;
		}
        case 119:
		{
			addNodeToTree(&(*p),p1,36,0);
			break;
		}
        case 120:
		{
			newP = addNodeToTree(&(*p),p1,36,2);
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			//fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			break;
		}
        case 121:
		{
			newP = addNodeToTree(&(*p),p1,30,3);
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			//fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			//fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			break;
		}
        case 122:
		{
			newP = addNodeToTree(&(*p),p1,38,1);
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			break;
		}
        case 123:
		{
			addNodeToTree(&(*p),p1,38,0);
			break;
		}
        case 124:
		{
			newP = addNodeToTree(&(*p),p1,31,4);
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			//fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			//fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			//fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			break;
		}
        case 125:
		{
			newP = addNodeToTree(&(*p),p1,32,2);
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			//fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			break;
		}
        case 126:
		{
			newP = addNodeToTree(&(*p),p1,37,2);
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			//fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			break;
		}
        case 127:
		{
			newP = addNodeToTree(&(*p),p1,40,3);
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			//fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			//fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			break;
		}
        case 128:
		{
			addNodeToTree(&(*p),p1,40,0);
			break;
		}
        case 129:
		{
			newP = addNodeToTree(&(*p),p1,39,1);
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			break;
		}
        case 130:
		{
			newP = addNodeToTree(&(*p),p1,39,1);
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			break;
		}
        case 131:
		{
			newP = addNodeToTree(&(*p),p1,41,3);
			addNodeToTree(&newP,p1,3,0);
			addNodeToTree(&newP,p1,20,0);
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			break;
		}
        case 132:
		{
			newP = addNodeToTree(&(*p),p1,41,3);
			addNodeToTree(&newP,p1,7,0);
			addNodeToTree(&newP,p1,20,0);
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			break;
		}
        case 133:
		{
			newP = addNodeToTree(&(*p),p1,35,2);
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			//fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			break;
		}
        case 134:
		{
			newP = addNodeToTree(&(*p),p1,43,3);
			addNodeToTree(&newP,p1,21,0);
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			//fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			break;
		}
        case 135:
		{
			addNodeToTree(&(*p),p1,43,0);
			break;
		}
        case 136:
		{
			newP = addNodeToTree(&(*p),p1,42,2);
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			//fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			break;
		}
        case 137:
		{
			newP = addNodeToTree(&(*p),p1,45,3);
			addNodeToTree(&newP,p1,22,0);
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			//fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			break;
		}
        case 138:
		{
			addNodeToTree(&(*p),p1,45,0);
			break;
		}
        case 139:
		{
			newP = addNodeToTree(&(*p),p1,44,1);
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule);
			BuildingOfTree (&newP,fromHead);
			break;
		}
        case 140:
		{
			newP = addNodeToTree(&(*p),p1,44,1);
			addNodeToTree(&newP,p1,7,0);
			break;
		}
        case 141:
		{
			newP = addNodeToTree(&(*p),p1,44,1);
			addNodeToTree(&newP,p1,3,0);
			break;
		}
	}
	return 0;
}

// �������������� ����������
int SA()
{
	Table();
	HeadOfStack = NULL;
    //��������� � ���� Prog (23)
	AddNodeToStack(&HeadOfStack, 23);

    //������ �������, �������� � ������ �������
    HeadSeqOfRule = NULL;
	TableOfTokensToSeqOfRules(Tab[HeadOfStack -> token][Head -> n.token]);

	struct nodeToStack *p = HeadSeqOfRule;
	/*
	printf("\n\n~~~seq~~~\n\n");
	while(p != NULL)
	{
	    printf("rule: %d    numToken: %d    token:%d\n", p->numOfRule, p->numToken, p -> token);
	    p = p->next;
	}
    */
    //������ ������
    p = DelNumFromSeqOfRule(&HeadSeqOfRule);
	BuildingOfTree(&Root,p);
	return 0;
}

#endif // PARSER_H_INCLUDED

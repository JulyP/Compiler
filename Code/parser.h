#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

// ***DATA***
struct node *Head1;                 //�������� ����� ������

int Tab[47][24];				    //�������, � ������� ������� �������� ������ ������ � ������ ������,
                                    //����� ������������ ������ � ������, ������� �������

struct nodeToStack	                //���� �����
{
	int numOfRule;			        //����� ������� (�� ����������)
	struct tokensFromScaner n;      //������� �� ����� � ����������
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
    if ((*p) != NULL)
    {
        (*p) = (*p) -> next;
        free(p1);
        return 0;
    }
    return 1;
}

//������� ������� �� ������ ������
int DelToken(struct node **p)
{
    if ((*p) != NULL)
    {
        struct node *p1 = (*p);
        (*p) = (*p) -> next;
        free(p1);
        return 0;
    }
    else
    {
        return 1;
    }
}

//���������� �����, ������� ��������� � �������� ����� (������ ������)
int NumFromStack()
{
    return Head -> n.token;
}

//��������� � ����-�� (� ����� ����-��) ������ ����� �������, ���.������
int AddNodeToSeqOfRules(struct nodeToStack **pp, int rule, struct tokensFromScaner token)
{
    struct nodeToStack *p1, *p = (struct nodeToStack*)malloc(sizeof(struct nodeToStack));
    p -> numOfRule = rule;
    p -> n = token;
    p -> n.numString = token.numString;
    p -> next = NULL;
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

//��������� � ���� (� �������) ����� ����������� ��� �������
int AddNodeToStack (struct nodeToStack **pp, int N_or_t)
{
    struct nodeToStack *p = (struct nodeToStack*)malloc(sizeof(struct nodeToStack));
    p -> numOfRule = 0;
    p -> n = Head->n;
    p -> n.token = N_or_t;
    //printf("%d ", N_or_t);
    p -> next = (*pp);
    (*pp) = p;
    return 0;
}

//��������� � ������ ����
struct nodeTree *addNodeToTree(struct nodeTree **p, struct nodeToStack *p1, int neterminal, int j)
{
	struct nodeTree *p2 = (struct nodeTree*)malloc(sizeof(struct nodeTree));
	p2->type = NULL;
	int k = 0;
	for (k = 0; k < 4; k++)
	{
		p2 -> alpha[k] = NULL;
	}
	p2 -> n = p1 -> n;                      //copy token from stek
	p2 -> n.token = neterminal;             //����� ������� (0 - 22), (23 - 46)
	if (neterminal == 23)
	{
		(*p) = p2;
	}
	else
	{
        (*p) -> alpha[j] = p2;
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
		Tab[12][i] = -26;
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
	Tab[40][4] = 128;
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
	Tab[43][4] = 135;//hhhhhhhhhh
	Tab[43][15] = 135;
	Tab[43][21] = 134;
	Tab[43][23] = 135;
	//44
	Tab[44][3] = 141;
	Tab[44][7] = 140;
	Tab[44][14] = 139;
	//45
	Tab[45][4] = 138; //HHHHHHH
	Tab[45][15] = 138;
	Tab[45][21] = 138;
	Tab[45][22] = 137;
	Tab[45][23] = 138;
	//46
	Tab[46][23] = 100;
	return 0;
}

//are adding node to errorHead (seq. of error)
int addSinError(int i)
{
    struct nodeError *p1, *p = (struct nodeError*)malloc(sizeof(struct nodeError));
    p -> numOfError = i;
    p -> typeOfError = 2;
    p -> numOfString = HeadOfStack->n.numString;
    p -> position = HeadOfStack->n.position;
    p -> next = NULL;

    if (errorHead == NULL)
    {
        errorHead = p;
    }
    else
    {
        p1 = errorHead;
        while (p1 -> next != NULL)
        {
            p1 = p1 -> next;
        }
        p1 -> next = p;
    }
    return 0;
}

//are adding node to Head (tokens from scanner)
int AddNodeToHead(int i, struct node **p)
{
    struct node *p1 = (struct node*)malloc(sizeof(struct node));
    p1 -> n.token = i;
    p1 -> next = (*p);
    //(*p) -> prev = p1;
    (*p) = p1;
    return 0;
}

//������ ��� �������
int Error (int i)
{
	addSinError (i);
	//printf("\n\nerror  %d\n\n",i);
	switch (i)
	{
	    case -1:    //'type' is expected
	    {
	        AddNodeToHead(5, &Head);                //token 'type' was added to Head
	        break;
        }
	    case -2:    //'id' is expected
	    {
	        if (NumFromStack() == 8)                //if '=' was met
	        {
	            AddNodeToHead(3,&Head);             //token 'id' was added to Head (sequence of tokens)
	        }
	        else
	        {
	            while (NumFromStack() != 4)         //while ';' will not be find
	            {
	                if (NumFromStack() == 23)               //'�'
                    {
                        while (HeadOfStack->n.token != 46)  //'#'
                        {
                            DelNodeFromStack(&HeadOfStack); //token "no_#" was deleted from Head
                        }
                        return 0;
                    }
	                DelToken(&Head);                //token "no_;" was deleted from Head
	            }
	            while (HeadOfStack->n.token != 4)   //while ';' will not be find
	            {
	                DelNodeFromStack(&HeadOfStack); //token "no_;" was deleted from Head
	            }
	        }
	        break;
	    }
	    case -3:    //'else', 'type', 'id', 'cin', 'cout', 'if', 'for', 'while' or '}' are expected
	    {
	        int j = NumFromStack();
	        if (j == 1)                         //if the next token is '{'
	        {
	            AddNodeToHead(16,&Head);        //token 'else' was added to Head
	        }
	        else
	        {
	            //while 'type', 'id', 'cin', 'cout', 'if', 'for' , 'while' or '}' will not be find
                while (j!=5 && j!=3 && j!=9 && j!=11 && j!=13 && j!=17 && j!=18 && j!=2)
                {
                    if (j == 23)                    //'�'
                    {
                        while (HeadOfStack->n.token != 46)  //'#'
                        {
                            DelNodeFromStack(&HeadOfStack); //token "no_#" was deleted from Head
                        }
                        return 0;
                    }
                    DelToken(&Head);                //token "no_;" was deleted from Head
                    j = NumFromStack();
                }
                while (HeadOfStack->n.token != 25)   //while 'Sent' will not be find
                {
                    DelNodeFromStack(&HeadOfStack); //token "no_Sent" was deleted from Head
                }
	        }
	        break;
        }
	    case -4:    //'&&', '||' or ')' are expected
	    {
	        int j = NumFromStack();
	        if (j==3 || j==7 || j==14)          //'id', 'constnum', '('
 	        {
	            AddNodeToHead(19, &Head);       //token 'compop' was added to Head
	        }
	        else
	        {
	            AddNodeToHead(15, &Head);       //token ')' was added to Head
	        }
	        break;
        }
	    case -5:    //'{' is expected
	    {
            AddNodeToHead(1,&Head);                 //token '{' was added to Head (sequence of tokens)
	        break;
        }
	    case -6:    //'id' or 'constnum' are expected
	    {
	        AddNodeToHead(3,&Head);                 //token 'id' was added to Head (sequence of tokens)
	        break;
	    }
	    case -7:    //'-', '+' or '(' are expected
        case -8:    //'cout' is expected
        case -10:   //'cin' is expected
        case -11:   //'*', '/' or ')' are expected
        case -16:   //'conststr' is expected
        case -22:   //'constnum', 'conststr', 'id' or '(' are expected
	    {
	        while (NumFromStack() != 4)         //while ';' will not be find
            {
                //printf("tok: %d   ", NumFromStack());
                if (NumFromStack() == 23)                    //'�'
                {
                    while (HeadOfStack->n.token != 46)  //'#'
                    {
                        DelNodeFromStack(&HeadOfStack); //token "no_#" was deleted from Head
                        //printf("Stack: %d   ", HeadOfStack->n.token);
                    }
                    return 0;
                }
                DelToken(&Head);                //token "no_;" was deleted from Head
	        }
            while (HeadOfStack->n.token != 4 && HeadOfStack->n.token != 46)   //while ';' will not be find
            {
                DelNodeFromStack(&HeadOfStack); //token "no_;" was deleted from Head
            }
	        break;
        }
	    case -9:    //'<<' or ';' are expected
        {
	        int j = NumFromStack();
	        if (j==3 || j==6 || j==7 || j==14)  //id, conststr, constnum, (
	        {
	            AddNodeToHead(12,&Head);         //token '<<' was added to Head
	        }
	        else
	        {
	            if (j==5 || j==3 || j==9 || j==11 || j==13 || j==17 || j==18 || j==2)
	            {
	                AddNodeToHead(4,&Head);     //token ';' was added to Head
	            }
	            else
	            {
	                while (NumFromStack() != 4 && NumFromStack() != 8)
	                {
	                    if (j == 23)                            //'�'
                        {
                            while (HeadOfStack->n.token != 46)  //'#'
                            {
                                DelNodeFromStack(&HeadOfStack); //token "no_#" was deleted from Head
                            }
                            return 0;
                        }
	                    DelToken(&Head);
	                    j = NumFromStack();
	                }
	            }
	        }
	        break;
        }
	    case -12:   //'}' is expected
	    {
	        AddNodeToHead(2,&Head);             //'}' is added
	        break;
        }
	    case -13:   //';' is expected
	    {
	        AddNodeToHead(4,&Head);             //';' is added
	        break;
	    }
	    case -14:   //'id', 'constnum' or '(' are expected
	    {
            while (NumFromStack() != 4 && NumFromStack() != 15) //while ';' will not be find
            {
                DelToken(&Head);                //token "no_;" was deleted from Head
	        }
            while (HeadOfStack->n.token != NumFromStack())      //while ';' will not be find
            {
                DelNodeFromStack(&HeadOfStack); //token "no_;" was deleted from Head
            }
	        break;
        }
	    case -15:   //'if' is expected
	    case -17:   //'for' is expected
	    case -18:   //'while' is expected
	    {
	        while (NumFromStack() != 1)         //while '{' will not be find
            {
                if (NumFromStack() == 23)                            //'�'
                {
                    while (HeadOfStack->n.token != 46)  //'#'
                    {
                        DelNodeFromStack(&HeadOfStack); //token "no_#" was deleted from Head
                    }
                    return 0;
                }
                DelToken(&Head);                //token "no_{" was deleted from Head
	        }
            while (HeadOfStack->n.token != 24)  //while 'Block' will not be find
            {
                DelNodeFromStack(&HeadOfStack); //token "no_{" was deleted from Head
            }
	        break;
        }
	    case -19:   //'main' is expected
	    {
	        //while '{' is not met
	        while (NumFromStack() != 1 && Head != NULL)
			{
			    if (NumFromStack() == 23)                            //'�'
                {
                    while (HeadOfStack->n.token != 46)  //'#'
                    {
                        DelNodeFromStack(&HeadOfStack); //token "no_#" was deleted from Head
                    }
                    return 0;
                }
				DelToken(&Head);            //token "no_main" was deleted from Head
			}
			AddNodeToHead(0,&Head);         //token "main" was added to Head (sequence of tokens)
	        break;
        }
	    case -20:   //'type', 'id', 'cin', 'cout', 'if', 'for' , 'while' or '}'
	    {
	        int j = NumFromStack();
	        //while 'type', 'id', 'cin', 'cout', 'if', 'for' , 'while' or '}' will not be find
	        while (j!=5 && j!=3 && j!=9 && j!=11 && j!=13 && j!=17 && j!=18 && j!=2)
            {
                printf("%d\n",j);
                if (j == 23)                            //'�'
                {
                    while (HeadOfStack->n.token != 46)  //'#'
                    {
                        DelNodeFromStack(&HeadOfStack); //token "no_#" was deleted from Head
                    }
                    return 0;
                }
                DelToken(&Head);                //token *** was deleted from Head
                j = NumFromStack();
	        }
	        //there is 'Sent' in HeadOfStack
	        break;
	    }
	    case -21:   //'=' or ';' are expected
	    {
	        int j = NumFromStack();
	        if (j==3 || j==6 || j==7 || j==14)  //id, conststr, constnum, (
	        {
	            AddNodeToHead(8,&Head);         //token '=' was added to Head
	        }
	        else
	        {
	            if (j==5 || j==3 || j==9 || j==11 || j==13 || j==17 || j==18 || j==2)
	            {
	                AddNodeToHead(4,&Head);     //token ';' was added to Head
	            }
	            else
	            {
	                while (NumFromStack() != 4 && NumFromStack() != 8)
	                {
	                    if (j == 23)                            //'�'
                        {
                            while (HeadOfStack->n.token != 46)  //'#'
                            {
                                DelNodeFromStack(&HeadOfStack); //token "no_#" was deleted from Head
                            }
                            return 0;
                        }
	                    DelToken(&Head);
	                    j = NumFromStack();
	                }
	            }
	        }
	        break;
        }
	    case -23:   //'constnum' is expected
	    {
	        AddNodeToHead(7,&Head);         //'constnum' is added
	        break;
        }
	    case -24:   //'=' is expected
	    {
	        AddNodeToHead(8,&Head);         //'=' is added
	        break;
        }
	    case -25:   //'>>' is expected
	    {
	        int j = NumFromStack();
	        if (j == 12) //<<
	        {
                DelToken(&Head);
                //printf ("\n\n%d", j);
	        }
            AddNodeToHead(10,&Head);         //'<<' is added
	        break;
	    }
	    case -26:   //'<<' is expected
	    {
	        int j = NumFromStack();
	        if (j == 10) //>>
	        {
                DelToken(&Head);
	        }
            AddNodeToHead(12,&Head);         //'<<' is added
	        break;
        }
	    case -27:   //'(' is expected
	    {
	        AddNodeToHead(14,&Head);         //'(' is added
	        break;
        }
	    case -28:   //')' is expected
	    {
	        AddNodeToHead(15,&Head);         //')' is added
	        break;
	    }
	    case -29:   //'else' is expected
	    {
	        AddNodeToHead(16,&Head);         //'else' is added
	        break;
        }
	    case -30:   //'&&' or '||' are expected
	    {
	        AddNodeToHead(19,&Head);         //'compop' is added
	        break;
        }
	    case -31:   //'==', '<=', '>=', '!=', '>' or '<' are expected
	    {
	        AddNodeToHead(20,&Head);         //'relop' is added
	        break;
        }
	    case -32:   //'+' or '-' are expected
	    {
	        AddNodeToHead(21,&Head);         //'addop' is added
	        break;
        }
	    case -33:   //'*' or '/' are expected
	    {
	        AddNodeToHead(22,&Head);         //'multop' is added
	        break;
        }
	    case -34:   //the end of sequence is expected
	    {
	        while (NumFromStack() != 23)         //while '�' will not be find
            {
                if (Head == NULL)
                {
                    return 0;
                }
                DelToken(&Head);                //token "no_{" was deleted from Head
	        }
            while (HeadOfStack->n.token != 46)  //while 'Block' will not be find
            {
                DelNodeFromStack(&HeadOfStack); //token "no_{" was deleted from Head
            }
	        break;
        }
	}
	return 0;
}

//�� ������ ������ ������ ������� ������
int TableOfTokensToSeqOfRules (int i)
{
    //printf("\ni: %d", i);
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
			AddNodeToSeqOfRules(&HeadSeqOfRule,i,Head -> n);
			switch(i)
			{
			    case 100:
			    {
			        //����� �������, ������� ���������
			        //printf("\n\nEND!\n\n");
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
                    AddNodeToStack(&HeadOfStack, 4);        //��������� � ���� ������� ;
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
                    AddNodeToStack(&HeadOfStack, 36);		//��������� � ���� ������� FuncOut
                    AddNodeToStack(&HeadOfStack, 34);		//��������� � ���� ������� Expr
                    AddNodeToStack(&HeadOfStack, 12);		//��������� � ���� ������� <<
                    AddNodeToStack(&HeadOfStack, 11);		//��������� � ���� ������� cout
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
                    AddNodeToStack(&HeadOfStack, 27);		//��������� � ���� ������� OpEqu
                    AddNodeToStack(&HeadOfStack, 4);		//��������� � ���� ������� ;
                    AddNodeToStack(&HeadOfStack, 37);		//��������� � ���� ������� CondExpr
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
		TableOfTokensToSeqOfRules(Tab[HeadOfStack -> n.token][Head -> n.token]);
		return 0;
	}
	//������
	else
	{
	    //printf("\ni: %d", i);
		Error(i);
		if (HeadOfStack -> n.token == 46)
        {
            return 0;
        }
        //printf("\nTab[HeadOfStack -> n.token][Head -> n.token]: %d", Tab[HeadOfStack -> n.token][Head -> n.token]);
		TableOfTokensToSeqOfRules(Tab[HeadOfStack -> n.token][Head -> n.token]);
		return 1;
	}
}

//���������� �����, ������� ��������� � �������� ����-�� (������� ������)
struct nodeToStack *DelNumFromSeqOfRule(struct nodeToStack **pp)
{
    if ((*pp) == NULL)
    {
        return NULL;
    }
    struct nodeToStack *p1, *p = (struct nodeToStack*)malloc(sizeof(struct nodeToStack));
    p -> numOfRule = (*pp) -> numOfRule;    //����� ������� (�� ����������)
	p -> n = (*pp) -> n;                    //token
	p -> next = NULL;
	p1 = (*pp);
	(*pp) = (*pp) -> next;
	free(p1);
	return p;
}

//����������
struct nodeToStack *returnToken(int number)
{
    struct node *p1 = Head1;
    struct nodeToStack *p = (struct nodeToStack*)malloc(sizeof(struct nodeToStack));
    int i = 0;

    for (i = 1; i <= number; i++)
    {
        p1 = p1 -> next;
    }

    p->n = p1->n;
    p->next = NULL;

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
		    newP = addNodeToTree(&(*p),p1,24,0);            //add Block
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //del rule
			BuildingOfTree (&newP,fromHead);                //build tree from Block
			break;
		}
        case 102:
		{
			newP = addNodeToTree(&(*p),p1,25,0);            //add Sent
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //del rule
			BuildingOfTree (&newP,fromHead);                //build tree from Sent
			break;
		}
        case 103:
		{
			newP = addNodeToTree(&(*p),p1,26,0);            //add DescrVar
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from DescrVar

			newP = addNodeToTree(&(*p),p1,25,1);            //add Sent
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from Sent
			break;
		}
        case 104:
		{
			newP = addNodeToTree(&(*p),p1,27,0);            //add OpEqu
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from OpEqu

			newP = addNodeToTree(&(*p),p1,25,1);            //add Sent
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from Sent

			break;
		}
        case 105:
		{
			newP = addNodeToTree(&(*p),p1,28,0);            //add OpIn
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from OpIn

			newP = addNodeToTree(&(*p),p1,25,1);            //add Sent
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from Sent
			break;
		}
        case 106:
		{
			newP = addNodeToTree(&(*p),p1,29,0);            //add OpOut
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from OpOut

			newP = addNodeToTree(&(*p),p1,25,1);            //add Sent
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from Sent
			break;
		}
        case 107:
		{
			newP = addNodeToTree(&(*p),p1,30,0);            //add OpIf
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from OpIf

			newP = addNodeToTree(&(*p),p1,25,1);            //add Sent
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from Sent
			break;
		}
        case 108:
		{
			newP = addNodeToTree(&(*p),p1,31,0);            //add OpFor
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from OpFor

			newP = addNodeToTree(&(*p),p1,25,1);            //add Sent
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from Sent
			break;
		}
        case 109:
		{
			newP = addNodeToTree(&(*p),p1,32,0);            //add OpWhile
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from OpWhile

			newP = addNodeToTree(&(*p),p1,25,1);            //add Sent
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from Sent
			break;
		}
        case 110:
		{
			addNodeToTree(&(*p),p1,50,0);                   //add lambda
			break;
		}
        case 111:
		{
			addNodeToTree(&(*p),p1,5,0);                    //add type
			addNodeToTree(&(*p),returnToken(p1->n.numLex),3,1); //add id
			newP = addNodeToTree(&(*p),p1,33,2);            //add EquExpr
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from EquExpr
			break;
		}
        case 112:
		{
			newP = addNodeToTree(&(*p),p1,34,0);            //add Expr
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from Expr
			break;
		}
        case 113:
		{
			addNodeToTree(&(*p),p1,50,0);                   //add lambda
			break;
		}
        case 114:
		{
			newP = addNodeToTree(&(*p),p1,35,0);            //add ArExpr
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from ArExpr
			break;
		}
        case 115:
		{
			addNodeToTree(&(*p),p1,6,0);                    //add conststr
			break;
		}
        case 116:
		{
		    addNodeToTree(&(*p),p1,3,0);                    //add id
			newP = addNodeToTree(&(*p),p1,34,1);            //add Expr
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from Expr
			break;
		}
        case 117:
		{
			addNodeToTree(&(*p),returnToken(1+p1->n.numLex),3,0);                   //add id
			break;
		}
        case 118:
		{
			newP = addNodeToTree(&(*p),p1,34,0);            //add Expr
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from Expr

			newP = addNodeToTree(&(*p),p1,36,1);            //add FuncOut
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from FuncOut
			break;
		}
        case 119:
		{
			addNodeToTree(&(*p),p1,50,0);                   //add lambda
			break;
		}
        case 120:
		{
			newP = addNodeToTree(&(*p),p1,34,0);            //add Expr
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from Expr

			newP = addNodeToTree(&(*p),p1,36,1);            //add FuncOut
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from FuncOut
			break;
		}
        case 121:
		{
			newP = addNodeToTree(&(*p),p1,37,0);            //add CondExpr
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from CondExpr

			newP = addNodeToTree(&(*p),p1,24,1);            //add Block
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from Block

			newP = addNodeToTree(&(*p),p1,38,2);            //add Else
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from Else
			break;
		}
        case 122:
		{
			newP = addNodeToTree(&(*p),p1,24,0);            //add Block
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from Block
			break;
		}
        case 123:
		{
			addNodeToTree(&(*p),p1,50,0);                   //add lambda
			break;
		}
        case 124:
		{
			newP = addNodeToTree(&(*p),p1,27,0);            //add OpEqu
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from OpEqu

			newP = addNodeToTree(&(*p),p1,37,1);            //add CondExpr
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from CondExpr

			newP = addNodeToTree(&(*p),p1,35,2);            //add ArExpr
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from ArExpr

			newP = addNodeToTree(&(*p),p1,24,3);            //add Block
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from Block
			break;
		}
        case 125:
		{
			newP = addNodeToTree(&(*p),p1,37,0);            //add CondExpr
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from CondExpr

			newP = addNodeToTree(&(*p),p1,24,1);            //add Block
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from Block
			break;
		}
        case 126:
		{
			newP = addNodeToTree(&(*p),p1,39,0);            //add DiffCondExpr
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from DiffCondExpr

			newP = addNodeToTree(&(*p),p1,40,1);            //add SecDCE
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree secDCE
			break;
		}
        case 127:
		{
		    addNodeToTree(&(*p),p1,19,0);                   //add compop
			newP = addNodeToTree(&(*p),p1,39,1);            //add DiffCondExpr
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from DiffCondExpr

			newP = addNodeToTree(&(*p),p1,40,2);            //add SecDCE
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);
			break;
		}
        case 128:
		{
			addNodeToTree(&(*p),p1,50,0);                   //add lambda
			break;
		}
        case 129:
		{
			newP = addNodeToTree(&(*p),p1,37,0);            //add CondExpr
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from CondExpr
			break;
		}
        case 130:
		{
			newP = addNodeToTree(&(*p),p1,41,0);            //add SimpCondExpr
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from SimpCondExpr
			break;
		}
        case 131:
		{
		    addNodeToTree(&(*p),p1,3,0);                    //add id
			addNodeToTree(&(*p),returnToken(p1->n.numLex),20,1);    //add relop
			newP = addNodeToTree(&(*p),p1,35,2);            //add ArExpr
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from ArExpr
			break;
		}
        case 132:
		{
		    addNodeToTree(&(*p),p1,7,0);                    //add constnum
			addNodeToTree(&(*p),returnToken(p1->n.numLex),20,1);    //add relop
			newP = addNodeToTree(&(*p),p1,35,2);            //add ArExpr
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from ArExpr
			break;
		}
        case 133:
		{
			newP = addNodeToTree(&(*p),p1,42,0);            //add Addendum
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from Addendum

			newP = addNodeToTree(&(*p),p1,43,1);            //add SecAddendum
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from SecAddendum
			break;
		}
        case 134:
		{
		    addNodeToTree(&(*p),p1,21,0);                   //add addop
			newP = addNodeToTree(&(*p),p1,42,1);            //add Addendum
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from Addendum

			newP = addNodeToTree(&(*p),p1,43,2);            //add SecAddendum
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from SecAddendum
			break;
		}
        case 135:
		{
			addNodeToTree(&(*p),p1,50,0);                   //add lambda
			break;
		}
        case 136:
		{
			newP = addNodeToTree(&(*p),p1,44,0);            //add Multiplier
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from Multiplier

			newP = addNodeToTree(&(*p),p1,45,1);            //add SecMultiplier
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from SecMultiplier
			break;
		}
        case 137:
		{
		    addNodeToTree(&(*p),p1,22,0);                   //add multop
			newP = addNodeToTree(&(*p),p1,44,1);            //add Multiplier
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from Multiplier

			newP = addNodeToTree(&(*p),p1,45,2);            //add SecMultiplier
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from SecMultiplier
			break;
		}
        case 138:
		{
			addNodeToTree(&(*p),p1,50,0);                   //add lambda
			break;
		}
        case 139:
		{
			newP = addNodeToTree(&(*p),p1,35,0);            //add ArExpr
			fromHead = DelNumFromSeqOfRule(&HeadSeqOfRule); //next rule
			BuildingOfTree (&newP,fromHead);                //build tree from ArExpr
			break;
		}
        case 140:
		{
			addNodeToTree(&(*p),p1,7,0);                    //add constnum
			break;
		}
        case 141:
		{
			addNodeToTree(&(*p),p1,3,0);                    //add id
			break;
		}
	}
	return 0;
}

// �������������� ����������
int SA()
{
    //*** �������� ����� ������
    struct node *p1 = Head, *p2;
    struct node *p3 = (struct node*)malloc(sizeof(struct node));
    while (p1->next != NULL)
    {
        p1 = p1 -> next;
    }
    //��������� � ����� ������ ������
    p3->n.token=23;
	p3->n.numToken=50;
	p3->n.numLex = 0;
	p3->next=NULL;
	p1->next=p3;

    p1 = Head;
    p3 = (struct node*)malloc(sizeof(struct node));
    p3 -> n = p1 -> n;
    p3 -> next = NULL;
    Head1 = p3;
    p2 = Head1;
    p1 = p1 -> next;
    while (p1 != NULL)
    {
        struct node *p3 = (struct node*)malloc(sizeof(struct node));
        p3 -> n = p1 -> n;
        p3 -> next = NULL;
        p2 -> next = p3;
        p2 = p2 -> next;
        p1 = p1 -> next;
    }

    // *** �������� ������� ������� **
    //��������� �������
	Table();
	HeadOfStack = NULL;
	//��������� � ���� (� �������) # (46)
	AddNodeToStack(&HeadOfStack, 46);
    //��������� � ���� (� �������) Prog (23)
	AddNodeToStack(&HeadOfStack, 23);
    //������ �������, �������� � ������ �������
    HeadSeqOfRule = NULL;
	TableOfTokensToSeqOfRules(Tab[HeadOfStack -> n.token][Head -> n.token]);

    //���� ������, ����������� ������
	if (errorHead != NULL)
	{
	    return 1;
	}

    // *** ������ ������            **
	struct nodeToStack *p;
    p = DelNumFromSeqOfRule(&HeadSeqOfRule);
    //��������� � ������ Prog
    addNodeToTree(&Root,p,23,0);
	BuildingOfTree(&Root,p);

	if (HeadSeqOfRule != NULL)
	{
	//    printf("\n\n%d\n\n", HeadSeqOfRule->numOfRule);
	    free(Head);
	}
	return 0;
}

#endif // PARSER_H_INCLUDED

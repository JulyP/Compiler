#ifndef DATA_STRUCTURE_H_INCLUDED
#define DATA_STRUCTURE_H_INCLUDED

// ����������� �����������
const int max_amount_id = 250;		//������������ ���������� ���������������
const int max_amount_skobka = 10;		//������������ ����������� ������
const int max_level_blocks = 8;		//������������ ����������� ������
const int max_amount_print = 5;		//������������ ���������� ��������� � ��������� ������
const int max_amount_podblocs = 20;	//������������ ���������� ��������� ��������� ������� ������ � ���� ����

//����� ������
struct error			        //���� �����, � ������� �������� ������
{
	int numOfError;	            //����� ������
	int typeOFError;	        //��� ������ (�����������, ��������������, �������������)
	int numOfString;	        //����� ������, � ������� ��������� ������
	int position;		        //������� ������ (� ����� ������� � ������ ��������� ������)
}*Errors;			            //��������� ��� ��� ������


//�� ������������ �����������
struct tokensFromScaner
{
	int token;                  //����� ������ (�� 0 �� 23)
	int numToken;               //����� �������� (�� 1 �� 39)
	int value;                  //����� � ������� ���� ��� ��������
	int numString;              //����� ������
	int position;               //������� � ������(� ������)
};

struct node
{
	struct tokensFromScaner n;
	struct node *next, *prev;
};
struct node *Head;

struct Name	                    //������� ����
{
	char name[1];               //���
    char kindtoken[1];	        //��� ������ (������������� ��� �������� �����)
    char kindid[1];             // ��� ��������������(int, string, float)
    int value;                  // ����� � ������� ��������� � �������� ��������
} *TableOfName;                 // ������� ����

struct Constant                 //������� ��������
{
	int num ;	                //����� ��������� ���������
	char str[1];	            //������
}* TableOfConst;                // ������� ��������� � �������� ���c����


//�� ��������������� �����������
struct nodeTree	                //���� ������
{
	int token;                  //����� ������ (�� 0 �� 23)
	int numToken;               //����� �������� (�� 1 �� 39)
	int value;                  //����� � ������� ���� ��� ��������
	int numString;              //����� ������
	int position;               //������� � ������(� ������)
	struct nodeTree *alpha[5];	//������ ���������� �� ������ ���� ������
};
struct nodeTree *Root;          //��������� �� ������ ��������������� ������


//�� �������������� �����������
struct Table_Id		            //������� Id
{
	struct Name  *Name;	        //������ �� ������� ����;
	struct Constant *Const;	    // ������ �� ������� ��������;
	char *type;			        // ��� ��������������
};

struct Table_Identificators 	//������� ���������������
{
	struct Table_Id  table[250];	            // � ����� <= 250 ���������������
	struct Table_Identificators  *Child[20];	// � ����� <= 20 ��������� ���������
	struct Table_Identificators  *Parent;	    // ��������� �� ������������ ����
	unsigned int level;	                        // ������� ����������� ������� �����
};

#endif // DATA_STRUCTURE_H_INCLUDED

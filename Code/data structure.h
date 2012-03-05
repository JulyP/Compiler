#ifndef DATA_STRUCTURE_H_INCLUDED
#define DATA_STRUCTURE_H_INCLUDED



#endif // DATA_STRUCTURE_H_INCLUDED
//����� ������
struct error			//���� �����, � ������� �������� ������
{
	int numOfError;	    //����� ������
	int typeOFError;	//��� ������ (�����������, ��������������, �������������)
	int numOfString;	//����� ������, � ������� ��������� ������
	int position;		//������� ������ (� ����� ������� � ������ ��������� ������)
}*Errors;			    //��������� �� ���� ������


//�� ������������ �����������
struct tokensFromScanner
{
	int token;		    //����� ������ (�� 0 �� 22)
	int numToken;		//����� �������� (�� 1 �� 39)
    int value;		    //����� � ������� ���� ��� ��������
	int numString;		//����� ������
	int position;  		//����� �������
	struct tokensFromScanner *next;	//��������� �� ��������� �������
};
struct tokensFromScanner *tokenHead, *tokenTail; //��������� �� ����� � �� ������ �������

struct Name	            //������� ����
{
	char name[];        //���
    char kindtoken[];	//��� ������ (������������� ��� �������� �����)
    char kindid[];      // ��� ��������������(int, string, float)
    int value;          // ����� � ������� ��������� � �������� ��������
} *TableOfName          // ������� ����

struct Constant		    //������� ��������
{
	int num ;	        //����� ��������� ���������
	char str[];	        //������
}* TableOfConst         // ������� ��������� � �������� ���c����

//�� ��������������� �����������
struct node		        //���� ������
{
	int token; 	        //����� ������� (��. ������� ������)
	int numToken;		//����� �������� (�� 1 �� 39)
	struct node *alpha[4];	//������ ���������� �� ������ ���� ������
};
struct node *Root;      //��������� �� ������ ��������������� ������

//�� �������������� �����������
struct Table_Identificators 	    //������� ���������������
{
	struct Table_Id  table[250];	// � ����� <= 250 ���������������
	struct Table_Identificators  *Child[20];	|| � ����� <= 20 ��������� ���������
	struct Table_Identificators  *Parent;	// ��������� �� ������������ ����
	unsigned int level;             // ������� ����������� ������� �����
}

struct Table_Id		    //������� Id
{
	struct Name  *Name;	//������ �� ������� ����;
	struct Constant *Const;	// ������ �� ������� ��������;
	char *type;			// ��� ��������������
}

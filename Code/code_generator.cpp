#include <iostream>
#include <stdio.h>

using namespace std;

struct node		//���� ������
{
    int data; 	//����� �������
    int nump;	//���������� ������ � ������ ����� �������
    node *alpha[];	//������ ���������� �� ������ ���� ������
    atr * m;		//��������� �� ��������
}
*Root;		//��������� �� ������ ��������������� ������

struct Name
{
  int id;
  char* name;
  char* kindtoken;
}
Name[] NamesTable;	// ������� ���� ������� ���������
Name[] PascalNameTable;	//������� ��� ��� �������� ���������

struct Table_Identificators
{
    Table_Id  table[250];	// � ����� <= 250 ���������������
    Table_Identificators  *Child[10];	// � ����� <= 10 ��������� ���������
    Table_Identificators  *Parent;	// ��������� �� ������������ ����
    unsigned int level;	// ������� ����������� ������� �����
}

void walk (node Root /*������ �������������� ������*/, node &NewRoot /*������ ������ ��� �������� ���������*/, Name NamesTable /*������� ��� ������� ���������*/, &PascalNamesTable /*������� ��� �������� ���������*/);
//������� ������ ������ ����� �������, ������� ����������� ��������� dfs; ������������� ������� � ������ ����. ������� ����� � �� �������� � ����� ������� ���. ���� ��������� ����, ������� ���������� ������������� � ��������� ��� Pascal, �� �������� ������� (����������� ����).


void dfs (node Root /*������ �������������� ������*/, node &NewRoot /*������ ������ ��� �������� ���������*/, Name NamesTable /*������� ��� ������� ���������*/, &PascalNamesTable /*������� ��� �������� ���������*/);

void generator (node Root, Name &Names_table);
void block_gen (node Root, Name &Names_table);
void convert_for (node CurrentToken, node &NewRoot);
void convert_output (node CurrentToken, node &NewRoot);
void convert_input (node CurrentToken, node &NewRoot);
void convert_note (node CurrentToken, node &NewRoot);
void convert_suffix (node CurrentToken, node &NewRoot);

#define COMMENT
#define FILE_OUTPUT

int main()
{
#ifdef COMMENT
    FILE *fi = fopen ("C:\\cplusplus_code.cpp", "r");
    FILE *fo = fopen ("C:\\pascal_code.cpp", "w");
    char *c = new char [500];

    fgets(c, 500, fi);
    for (int i = 0; c[i] != '\0'; i++)
    {
        cout << c[i];
    }

#ifdef FILE_OUTPUT
    fwrite (c, sizeof c, 10, fo);
#endif

    delete []c;
    fclose(fi);
    fclose(fo);
#endif
    return 0;
}

void Graph::walk (node Root /*������ �������������� ������*/, node &NewRoot /*������ ������ ��� �������� ���������*/, Name NamesTable /*������� ��� ������� ���������*/, &PascalNamesTable /*������� ��� �������� ���������*/)
{
    int pos = search(start);
    if (matrix[0][0] && search(start))	//�������� �� ������� ����� � ������� ��������� �������
    {
        bool *used = new bool [matrix[0][0]];	//������ ����������� ������������� ������ - false ��������, ��� �������
                                                //�� ��������������
        for (int i = 0; i < matrix[0][0]; i++)
        {
            used[i] = 0;
        }

        //���� �� ������, ������� ������ ������� ����, � ��� �� ������������
        //index - ��� ������� ��������� ���������������� ������� � used
        int index = 0;
        dfs (pos, used);
        delete [] used;
    }
}

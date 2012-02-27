#include <iostream>
#include <stdio.h>

using namespace std;

struct node		//узел дерева
{
    int data; 	//номер лексемы
    int nump;	//количество лексем в правой части правила
    node *alpha[];	//массив указателей на другие узлы дерева
    atr * m;		//указатель на атрибуты
}
*Root;		//указатель на корень синтаксического дерева

struct Name
{
  int id;
  char* name;
  char* kindtoken;
}
Name[] NamesTable;	// таблица имен входной программы
Name[] PascalNameTable;	//таблица имён для выходной программы

struct Table_Identificators
{
    Table_Id  table[250];	// В блоке <= 250 идентификаторов
    Table_Identificators  *Child[10];	// В блоке <= 10 вложенных подблоков
    Table_Identificators  *Parent;	// Указатель на родительский блок
    unsigned int level;	// Уровень вложенности данного блока
}

void walk (node Root /*корень семантического дерева*/, node &NewRoot /*корень дерева для выходной программы*/, Name NamesTable /*таблица имён входной программы*/, &PascalNamesTable /*таблица имён выходной программы*/);
//Обходит дерево вглубь слева направо, вызывая рекурсивную процедуру dfs; перекрашивает вершины в чёрный цвет. Заносит имена и их атрибуты в новую таблицу имён. Если встречает узлы, которые необходимо преобразовать в синтаксис для Pascal, то вызывает функции (перечислены ниже).


void dfs (node Root /*корень семантического дерева*/, node &NewRoot /*корень дерева для выходной программы*/, Name NamesTable /*таблица имён входной программы*/, &PascalNamesTable /*таблица имён выходной программы*/);

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

void Graph::walk (node Root /*корень семантического дерева*/, node &NewRoot /*корень дерева для выходной программы*/, Name NamesTable /*таблица имён входной программы*/, &PascalNamesTable /*таблица имён выходной программы*/)
{
    int pos = search(start);
    if (matrix[0][0] && search(start))	//проверка на пустоту графа и наличие начальной вершины
    {
        bool *used = new bool [matrix[0][0]];	//массив индикаторов использования вершин - false означает, что вершина
                                                //не использовалась
        for (int i = 0; i < matrix[0][0]; i++)
        {
            used[i] = 0;
        }

        //граф не пустой, поэтому первая вершина есть, и она не использована
        //index - это позиция ближайшей неиспользованной вершины в used
        int index = 0;
        dfs (pos, used);
        delete [] used;
    }
}

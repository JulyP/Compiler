#ifndef DATA_STRUCTURE_H_INCLUDED
#define DATA_STRUCTURE_H_INCLUDED

// КОНТЕКСТНЫЕ ОГРАНИЧЕНИЯ
const int max_amount_id = 250;		//максимальное количество идентификаторов
const int max_amount_skobka = 10;		//максимальная вложенность скобок
const int max_level_blocks = 8;		//максимальная вложенность блоков
const int max_amount_print = 5;		//максимальное количество выражений в операторе вывода
const int max_amount_podblocs = 20;	//максимальное количество вложенных подблоков первого уровня в один блок

//ОБЩИЕ ОШИБКИ
struct error			        //узел стека, в котором хранятся ошибки
{
	int numOfError;	            //номер ошибки
	int typeOFError;	        //тип ошибки (лексическая, синтаксическая, семантическая)
	int numOfString;	        //номер строки, в которой произошла ошибка
	int position;		        //позиция ошибки (в какой позиции в строке произошла ошибка)
}*Errors;			            //указатель нас тек ошибок


//ИЗ ЛЕКСИЧЕСКОГО АНАЛИЗАТОРА
struct tokensFromScaner
{
	int token;                  //номер токена (от 0 до 23)
	int numToken;               //номер атрибута (от 1 до 39)
	int value;                  //номер в таблице имен или констант
	int numString;              //номер строки
	int position;               //позиция в строке(в буфере)
};

struct node
{
	struct tokensFromScaner n;
	struct node *next, *prev;
};
struct node *Head;

struct Name	                    //таблица имен
{
	char name[1];               //имя
    char kindtoken[1];	        //тип токена (идентификатор или ключевое слово)
    char kindid[1];             // тип идентификатора(int, string, float)
    int value;                  // номер в таблице строковых и числовых констант
} *TableOfName;                 // таблица имен

struct Constant                 //таблица констант
{
	int num ;	                //длина строковой константы
	char str[1];	            //строка
}* TableOfConst;                // таблица строковых и числовых конcтант


//ИЗ СИТАНКСИЧЕСКОГО АНАЛИЗАТОРА
struct nodeTree	                //узел дерева
{
	int token;                  //номер токена (от 0 до 23)
	int numToken;               //номер атрибута (от 1 до 39)
	int value;                  //номер в таблице имен или констант
	int numString;              //номер строки
	int position;               //позиция в строке(в буфере)
	struct nodeTree *alpha[5];	//массив указателей на другие узлы дерева
};
struct nodeTree *Root;          //указатель на корень синтаксического дерева


//ИЗ СЕМАНТИЧЕСКОГО АНАЛИЗАТОРА
struct Table_Id		            //таблица Id
{
	struct Name  *Name;	        //Ссылка на таблицу имен;
	struct Constant *Const;	    // Ссылка на таблицу констант;
	char *type;			        // Тип идентификатора
};

struct Table_Identificators 	//таблица идентификаторов
{
	struct Table_Id  table[250];	            // В блоке <= 250 идентификаторов
	struct Table_Identificators  *Child[20];	// В блоке <= 20 вложенных подблоков
	struct Table_Identificators  *Parent;	    // Указатель на родительский блок
	unsigned int level;	                        // Уровень вложенности данного блока
};

#endif // DATA_STRUCTURE_H_INCLUDED

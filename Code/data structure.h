#ifndef DATA_STRUCTURE_H_INCLUDED
#define DATA_STRUCTURE_H_INCLUDED

// КОНТЕКСТНЫЕ ОГРАНИЧЕНИЯ
const int max_amount_id = 250;		//максимальное количество идентификаторов
const int max_amount_skobka = 10;	//максимальная вложенность скобок
const int max_level_blocks = 8;		//максимальная вложенность блоков
const int max_amount_print = 5;		//максимальное количество выражений в операторе вывода
const int max_amount_podblocs = 20;	//максимальное количество вложенных подблоков первого уровня в один блок

//ОБЩИЕ ОШИБКИ
struct nodeError			        //узел стека, в котором хранятся ошибки
{
	int numOfError;	            //номер ошибки
	int typeOfError;	        //тип ошибки (лексическая, синтаксическая, семантическая) 1 - лек 2 - син 3 - сем
	int numOfString;	        //номер строки, в которой произошла ошибка
	int position;		        //позиция ошибки (в какой позиции в строке произошла ошибка)
	struct nodeError* next;         //указатель на следующий элемент
}*errorHead = NULL;			    //указатель на стек ошибок

//ИЗ ЛЕКСИЧЕСКОГО АНАЛИЗАТОРА
struct tokensFromScaner
{
	unsigned short token;               //номер токена (от 0 до 23)
	unsigned short numToken;            //номер атрибута (от 1 до 39)
	struct nodeName* pointerName;       //указатель в таблицу имен
    struct nodeConst* pointerConst;     //указатель в таблицу констант
	unsigned int numString;             //номер строки
	unsigned int position;              //позиция в строке(в буфере)
	unsigned int numLex;                //порядковый номер лексемы
};

struct node
{
	struct tokensFromScaner n;
	struct node *next;
};
struct node *Head;

struct nodeName
{
	unsigned int n; //количество символов в name
    char *name; //название ключевого слова или идентификатора
    unsigned int token; //номер токена (от 0 до 23)
    unsigned int numToken; //номер атрибута (от 1 до 39)
	unsigned short kindToken;	//идентиф - 1 или ключевое слово - 0
	struct nodeName *next, *prev;
};
struct nodeName *nameHead;

struct nodeConst
{
	int num ;	//длина строковой константы
	char *str;	//строка
	struct nodeConst *next;
};
struct nodeConst *constHead;

//ИЗ СИТАНКСИЧЕСКОГО АНАЛИЗАТОРА
struct nodeTree	                //узел дерева
{
	struct tokensFromScaner n;  //лексема со всеми её атрибутами
	struct nodeTree *alpha[4];	//массив указателей на другие узлы дерева
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

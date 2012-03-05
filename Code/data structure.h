#ifndef DATA_STRUCTURE_H_INCLUDED
#define DATA_STRUCTURE_H_INCLUDED



#endif // DATA_STRUCTURE_H_INCLUDED
//ОБЩИЕ ОШИБКИ
struct error			//узел стека, в котором хранятся ошибки
{
	int numOfError;	    //номер ошибки
	int typeOFError;	//тип ошибки (лексическая, синтаксическая, семантическая)
	int numOfString;	//номер строки, в которой произошла ошибка
	int position;		//позиция ошибки (в какой позиции в строке произошла ошибка)
}*Errors;			    //указатель на стек ошибок


//ИЗ ЛЕКСИЧЕСКОГО АНАЛИЗАТОРА
struct tokensFromScanner
{
	int token;		    //номер токена (от 0 до 22)
	int numToken;		//номер атрибута (от 1 до 39)
    int value;		    //номер в таблице имен или констант
	int numString;		//номер строки
	int position;  		//номер позиции
	struct tokensFromScanner *next;	//указатель на следующий элемент
};
struct tokensFromScanner *tokenHead, *tokenTail; //Указатели на хвост и на голову очереди

struct Name	            //таблица имен
{
	char name[];        //имя
    char kindtoken[];	//тип токена (идентификатор или ключевое слово)
    char kindid[];      // тип идентификатора(int, string, float)
    int value;          // номер в таблице строковых и числовых констант
} *TableOfName          // таблица имен

struct Constant		    //таблица констант
{
	int num ;	        //длина строковой константы
	char str[];	        //строка
}* TableOfConst         // таблица строковых и числовых конcтант

//ИЗ СИТАНКСИЧЕСКОГО АНАЛИЗАТОРА
struct node		        //узел дерева
{
	int token; 	        //номер лексемы (см. таблицу лексем)
	int numToken;		//номер атрибута (от 1 до 39)
	struct node *alpha[4];	//массив указателей на другие узлы дерева
};
struct node *Root;      //указатель на корень синтаксического дерева

//ИЗ СЕМАНТИЧЕСКОГО АНАЛИЗАТОРА
struct Table_Identificators 	    //таблица идентификаторов
{
	struct Table_Id  table[250];	// В блоке <= 250 идентификаторов
	struct Table_Identificators  *Child[20];	|| В блоке <= 20 вложенных подблоков
	struct Table_Identificators  *Parent;	// Указатель на родительский блок
	unsigned int level;             // Уровень вложенности данного блока
}

struct Table_Id		    //таблица Id
{
	struct Name  *Name;	//Ссылка на таблицу имен;
	struct Constant *Const;	// Ссылка на таблицу констант;
	char *type;			// Тип идентификатора
}

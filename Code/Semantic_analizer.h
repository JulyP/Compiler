#ifndef SEMANTIC_ANALIZER_H_INCLUDED
#define SEMANTIC_ANALIZER_H_INCLUDED

#include "data structure.h"

unsigned short amount_id = 0;       //количество идентификаторов в программе
unsigned short numb_next_id = 1;    //номер следующего нового идентификатора

// добавление элемента к списку ошибок
void Add_semantic_error(int error_number, int string_nember, int position)
{
    struct nodeError *p1, *p = (struct nodeError*)malloc(sizeof(struct nodeError));
    p -> numOfError = error_number;
    p -> typeOfError = 3;
    p -> numOfString = string_nember;
    p -> position = position;
    p -> next = NULL;

    if (errorHead == NULL)
        errorHead = p;
    else
    {
        p1 = errorHead;
        while (p1 -> next)
            p1 = p1 -> next;
        
		p1 -> next = p;
    }
}

// создание нового блока. возвращает указатель на созданный блок
struct Table_Identificators *Create_block(struct Table_Identificators *Block, unsigned short string_number)
{
    struct Table_Identificators *p = NULL;
    short i;

    if (Block == NULL)
    {
        p = (struct Table_Identificators*) malloc(sizeof(struct Table_Identificators));
        p->level = 1;
        p->parent = NULL;
    }
    else
    {
        if (Block->level == max_level_blocks)
        {
            Add_semantic_error(1, Block->string_number, 0);
            return NULL;
        }

		if (Block->amount_blocks == max_amount_podblocs)
        {
            Add_semantic_error(2, Block->string_number, 0);
            return NULL;
        }

        p = (struct Table_Identificators*) malloc(sizeof(struct Table_Identificators));
        p->level = Block->level + 1;
        p->parent = Block;
		Block->child[Block->amount_blocks ++] = p;
    }

	p->string_number = string_number;
    p->amount_blocks = 0;
    p->table = NULL;
    for (i = 0; i <= max_amount_podblocs; i ++)
        p->child[i] = NULL;

    return p;
}

// проверка что идентификатор описан в текущем блоке.
short Check_new_id_descr(struct nodeName *id, struct Table_Identificators *Block)
{
	struct Table_Id *p = Block->table;
	for (; p; p = p->next)
		if (p->token->pointerName == id)
			return 1;
	return 0;
}

// поиск идентификатора во всей структуре (текущем блоке и всех вышестоящих)
// Если найден, вернется ссылка на него, если не найден – вернется NULL.
struct Table_Id *Search_id(struct tokensFromScaner *id, struct Table_Identificators *Block)
{
	struct Table_Id *p = NULL;
	
	if (!Block || !id)
		return NULL;
	
	for (p = Block->table; p; p = p->next)
		if (p->token->pointerName == id->pointerName)
			return p;

	return Search_id(id, Block->parent);
}

// добавляет идентификатор а таблицу, в указанный блок
struct Table_Id *Add_Id(short kind, struct tokensFromScaner *id, struct Table_Identificators *Block)
{
    struct Table_Id *p = NULL;

    if (Check_new_id_descr(id->pointerName, Block))
    {
		Add_semantic_error(3, id->numString, id->position);
		return NULL;
	}

    if (amount_id == max_amount_id)
    {
        Add_semantic_error(4, id->numString, id->position);
		return NULL;
    }

    p = (struct Table_Id*) malloc(sizeof(struct Table_Id));
    p->token = id;
    p->kind = kind;
    p->next = Block->table;
    Block->table = p;
    p->new_name = numb_next_id;
    numb_next_id ++;
	amount_id ++;

    return p;
}

// удаление дерева
void delete_Table_Identificators(struct Table_Identificators **table)
{
    struct Table_Id *p = NULL;
    short i;

    while ((*table)->table != NULL)
    {
        p = (*table)->table;
        (*table)->table = p->next;
        free(p);
    }

    for (i = 0; i < (*table)->amount_blocks; i ++)
        delete_Table_Identificators(&((*table)->child[i]));

    free((*table));
}

/* функция производит анализ текущей вершины дерева
    возвращаемые значения - тип текущей вершины:
    8 - int
    9 - float
    10 - char
    0 - ошибка, нет типа. ?на всякий случай?
    для оператора FuncOut: результат - уровень вложенности операторов
    для операторов CondExpr: результат:
    1 - булевский тип
    0 - иное
	для остальных вершин:
	0 - все хорошо :)
	666 - функция ещё не доделана, или неизвестная ошибка
	13 - ошибка в синтаксическом дереве*/
short Three_Analizer(struct nodeTree *root, struct Table_Identificators *table)
{
	int result1, result2, result3;	// в эту переменнтую сохраняем результат работы функции от потомков (тип вершины потомка)
	struct Table_Identificators *block = NULL;
	struct Table_Id *p = NULL;

	switch (root->n.token)
	{
	case 3:	//id
		// проверка что это id
		return (root->n.numToken != 28)? 13 : 0;

	case 5:	//type
		// проверка что это тип
		return (root->n.numToken < 8 || root->n.numToken > 10)? 13 : root->n.numToken;

	case 24:	//Block
		if (!root->alpha[0])
			return 13;

		// создаем новый блок + проверка на максимум блоков
		block = Create_block(table, root->n.numString);
		if (!block)
            return 0;

		return Three_Analizer(root->alpha[0], block);
	
	case 25:	//Sent
		if (!root->alpha[0])
			return 13;
		
		// идем дальше по дереву, проверок нет
		result1 = Three_Analizer(root->alpha[0], table);
		result2 = (!root->alpha[1])? 0: Three_Analizer(root->alpha[1], table);

		return (result1)? result1 : result2;
	
	case 26:	//DescrVar
		if (!root->alpha[0] || !root->alpha[1] || !root->alpha[2])
			return 13;

		// проверим что первый потомок - тип, второй - id
		result1 = Three_Analizer(root->alpha[0], table);
		result2 = Three_Analizer(root->alpha[1], table);
		if (result1 == 13 || result2)
			return 13;

		p = Add_Id(result1, &root->alpha[1]->n, table);
		result3 = Three_Analizer(root->alpha[2], table);

		// проверим что третий потомок имеет тип
		if (result3 < 8 || result3 > 10)
			return result3;
		
		// если id слишком много
		if (!p)
			return 0;

		// запомнили в id его тип
		root->alpha[1]->type = p;
		// проверим совпадение типов id и третьего потомка
		if (p->kind != result3 && !( p->kind == 9 && result3 == 8))
			Add_semantic_error(5, p->token->numString, p->token->position);

		return 0;
		
	case 27:	//OpEqu
		if (!root->alpha[0] || !root->alpha[1])
			return 13;

		// проверим что первый потомок - id
		result1 = Three_Analizer(root->alpha[0], table);
		if (result1)
			return result1;

		// если id не нашли в дереве - ошибка
		p = Search_id(&root->alpha[1]->n, table);
		if (!p)
			Add_semantic_error(6, root->alpha[1]->n.numString, root->alpha[1]->n.position);
		
		// проверим что второй потомок имеет тип
		result2 = Three_Analizer(root->alpha[1], table);
		if (result2 < 8 || result2 > 10)
			return result2;

		// проверим ещё раз. чтобы предыдущий код отработал
		if (!p)
			return 0;
		
		// запомнили в id его тип
		root->alpha[0]->type = p;
		// проверим совпадение типов id и второго потомка
		if (p->kind != result2 && !( p->kind == 9 && result2 == 8))
			Add_semantic_error(5, p->token->numString, p->token->position);

		return 0;
		/*
	case 28:	//OpIn
		return Three_Analizer(root->alpha[0], table);
	case 29:	//OpOut
		result_analisis = Three_Analizer(root->alpha[0], table);
		result1 = Three_Analizer(root->alpha[1], table);

		// определиться с дальнейшим выводом
		// выдать ошибку если уровень вывода больше чем в К.У.

		break;
	case 30:	//OpIf
        //result_analisis = Three_Analizer(&(root->alpha[0]), &table);  // условие. проверить тип условия???

        //проверить ещё что то?

        Three_Analizer(root->alpha[1], &table);
        Three_Analizer(root->alpha[2], &table);
		break;
	case 31:
	case 32:
	case 33:	//EquExpr
		if (root->alpha[0] == NULL)
			return 0;
		return Three_Analizer(root->alpha[0], table);
		break;
	case 34:	//Expr
		if (root->alpha[0]->n.token == 6)
		{
            //*(root)->alpha[0]->value	// ссылка на идентификатор в таблице констант/имен
		}
		else
			return Three_Analizer(root->alpha[0], table);
		//break;
	case 35:    //ArExpr

	case 36:	//FuncOut
		if (root->alpha[0] == NULL)
			return 0;
		result_analisis = Three_Analizer(root->alpha[0], table);
		return Three_Analizer(root->alpha[0], table);

		// что делать когда нет пива??? работать!!!

		break;
	case 37:    //CondExpr
        if (Three_Analizer(root->alpha[0], table) && Three_Analizer(root->alpha[1], table))
            return 1;
        else
            return 0;
	case 38:    //Else
        if (root->alpha[0] == NULL)
			return 0;
		return Three_Analizer(root->alpha[0], table);

		break;
	case 39:    //DiffCondExpr
        return Three_Analizer(root->alpha[0], table);
	case 40:    //SecDCE
        if (root->alpha[0] == NULL)
            return 1;
        //*(table)->alpha[0]    //операция И, ИЛИ. не надо(?)
        if (Three_Analizer(root->alpha[1], table) && Three_Analizer(root->alpha[2], table))
            return 1;
        else
            return 0;
	case 41:    //SimpCondExpr
        //*(table)->alpha[0]    //ссылка на идентификатор
        //*(table)->alpha[1]->numToken    //вид сравнения (не знаю зачем)
        result_analisis = Three_Analizer(root->alpha[2], table);    //тип выражения

        // вставить проверки типов для сравнения
        /*if ()   //вызов функции проверки?
            return 1;
        else
            return 0;*/
	/*case 42:
	case 43:
	case 44:
	case 45:*/
	case 50:	// L - конец программы
		return 0;
	default:
        return 666;
	}

	return 0;
}

// Функция производит анализ дерева разбора
struct Table_Identificators *semantic_analizer(struct nodeTree *root)
{
	struct Table_Identificators *table = Create_block(NULL, root->alpha[0]->n.numString);
	// инициализируем таблицу идентификаторов и пропускаем 2 вершины синтаксического дерева
	short code = Three_Analizer(root->alpha[0]->alpha[0], table);

	if (code == 13)
		Add_semantic_error(0, 0, 0);
	
	printf("\n -----====== ******* semantic analizer ******* ======-----\n");
	printf(" code = %d", code);
	printf("\n -----====== ******* semantic analizer ******* ======-----\n");

	return table;
}

void printTable(struct Table_Identificators *table)
{
    struct Table_Id *p = NULL;
    int i;
	char *type;

    if (!table)
        return;

    printf("\n---------------------------------\n");
    printf("string = %d\n", table->string_number);
	printf("level = %d\n", table->level);
    printf("amount blocks = %d\n", table->amount_blocks);

    p = table->table;
    while (p)
    {
        if (p->token->pointerName)
        {
			switch (p->kind)
			{
			case 8:
				type = "int\0";
				break;
			case 9:
				type = "float\0";
				break;
			case 10:
				type = "string\0";
				break;
			}
			printf(" -> id = %s  %s\n", type, p->token->pointerName->name);
		}
        else
            printf(" -> error\n");
        p = p->next;
    }

    for (i = 0; i <= max_amount_podblocs; i ++)
        printTable(table->child[i]);
}

#endif // SEMANTIC_ANALIZER_H_INCLUDED

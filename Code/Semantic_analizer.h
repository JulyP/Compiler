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
		// проверка уровня вложенности блоков
        if (Block->level == max_level_blocks)
        {
            Add_semantic_error(1, Block->string_number, 0);
            return NULL;
        }

		// проверка количества подблоков первого уровня
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

	// проверка на то что идентификатор не описан в текущем блоке
    if (Check_new_id_descr(id->pointerName, Block))
    {
		Add_semantic_error(3, id->numString, id->position);
		return NULL;
	}

	// проверка на количество идентификаторов в программе
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

// функция сравнивает типы двух арифметических выржений.
// если есть строка - возвращает 10, иначе общий тип для этих типов
short compare_types_arithmetic_expressions(short a, short b)
{
	if (a == 10 && b == 10)
		return 10;
	
	return (a == 9 || b == 9)? 9 : 8;
}

// функция сравнивает типы в выражении присваивания.
// усли типы совпадают - возвращает 1, иначе 0
short check_types_assign_expression(short a, short b)
{
	return (a == b || ( a == 9 && b == 8));
}

// функция сравнивает типы двух выржений в булевском выражении.
// усли типы совпадают - возвращает 1, иначе 0
short check_bool_expression(short a, short b)
{
	return !(a == 10 || b == 10);
}

/* функция производит анализ текущей вершины дерева
    возвращаемые значения:
	1)	тип текущей вершины для тегов Expr, ArExpr, Addendum, SecAddendum, Multiplier, SecMultiplier, constnum, id:
			8 - int
			9 - float
			10 - char
			0 - идентификатор не найден в дереве (для тега id)
	2)	для оператора FuncOut: 
			уровень вложенности операторов
    3)	для операторов CondExpr:
			8 - булевский тип
			10 - иное
	4)	для остальных вершин:
			0 - все хорошо :)
	5)	для всех вершин:
			-13 - ошибка в синтаксическом дереве*/
short Three_Analizer(struct nodeTree *root, struct Table_Identificators *table)
{
	int result1, result2, result3, result4;		// в эту переменнтую сохраняем результат работы функции от потомков
	struct Table_Identificators *block = NULL;	// при создании нового блока
	struct Table_Id *p = NULL;	//указатель на таблицу с id

	switch (root->n.token)
	{
	case 3:		//id
		// проверка что это id
		if (root->n.numToken != 28)
			return -13;

		// ищем id в таблице и возвращаем его тип
		p = Search_id(&root->n, table);
		if (!p)
		{
			Add_semantic_error(6, root->n.numString, root->n.position);
			return 0;
		}
		else
		{
			root->type = p;
			return p->kind;
		}

	case 5:		//type
		// проверка что это тип
		return (root->n.numToken < 8 || root->n.numToken > 10)? -13 : root->n.numToken;

	case 6:		//conststr
		// проверка что это строковая константа. возвращаем её тип, либо ошибку
		return (root->n.numToken == 27)? 10 : -13;

	case 7:		//constnum!
		// проверка что это числовая константа. возвращаем её тип, либо ошибку
		return (root->n.numToken == 8 || root->n.numToken == 9)? root->n.numToken : -13;

	case 19:	//compop
	case 20:	//relop
	case 21:	//addop
	case 22:	//multop
		return 0;

	case 24:	//Block
		if (!root->alpha[0])
			return -13;

		// создаем новый блок + проверка на максимум блоков
		block = Create_block(table, root->n.numString);
		if (!block)
            return 0;

		return Three_Analizer(root->alpha[0], block);
	
	case 25:	//Sent
		if (!root->alpha[0])
			return -13;
		
		// идем дальше по дереву, проверок нет
		result1 = Three_Analizer(root->alpha[0], table);
		result2 = (!root->alpha[1])? 0: Three_Analizer(root->alpha[1], table);

		return (result1)? result1 : result2;	//для отладки ищем: result1 == -13 || result2 == -13
	
	case 26:	//DescrVar
		if (!root->alpha[0] || !root->alpha[1] || !root->alpha[2])
			return -13;

		// проверим что первый потомок - тип, второй - id
		result1 = Three_Analizer(root->alpha[0], table);
		if (result1 < 8 || result1 > 10 || root->alpha[1]->n.numToken != 28)
			return -13;

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
		if (!check_types_assign_expression(p->kind, result3))
			Add_semantic_error(5, p->token->numString, p->token->position);

		return 0;
		
	case 27:	//OpEqu
		if (!root->alpha[0] || !root->alpha[1] || root->alpha[0]->n.numToken != 28)
			return -13;

		result1 = Three_Analizer(root->alpha[0], table);
		result2 = Three_Analizer(root->alpha[1], table);
		
		// проверим что первый потомок имеет тип
		if (result1 < 8 || result1 > 10)
			return result1;
		
		// проверим что второй потомок имеет тип
		if (result2 < 8 || result2 > 10)
			return result2;

		// проверим совпадение типов id и второго потомка
		if (!check_types_assign_expression(result1, result2))
			Add_semantic_error(5, root->n.numString, root->n.position);

		return 0;
		
	case 28:	//OpIn
		// в дереве ошибка. пропускаю эту вершину при разборе. ЗАМЕНИТЬ TBD
		return 666;

		if (!root->alpha[0] || root->alpha[0]->n.numToken != 28)
			return -13;

		// проверим что первый потомок - id
		result1 = Three_Analizer(root->alpha[0], table);
		return (result1 == -13)? -13 : 0;
		
	case 29:	//OpOut
		if (!root->alpha[0] || !root->alpha[1])
			return -13;
		
		// проверим что первый потомок имеет тип
		result1 = Three_Analizer(root->alpha[0], table);
		if (result1 < 8 || result1 > 10)
			return result1;
		
		
		result2 = Three_Analizer(root->alpha[1], table);
		if (result2 == -13)
			return -13;
		
		// проверим что не выводим недопустимое количество выражений
		if (result2 >= max_amount_print)
			Add_semantic_error(7, root->n.numString, root->n.position);
		
		return 0;
		
	case 30:	//OpIf
        if (!root->alpha[0] || !root->alpha[1] || !root->alpha[2])
			return -13;
		
		result1 = Three_Analizer(root->alpha[0], table);
		result2 = Three_Analizer(root->alpha[1], table);
		result3 = Three_Analizer(root->alpha[2], table);
		return (result1 == -13 || result2 == -13 || result3 == -13)? -13 : 0;
		
	case 31:	//OpFor
		if (!root->alpha[0] || !root->alpha[1] || !root->alpha[2] || !root->alpha[3])
			return -13;
		
		result1 = Three_Analizer(root->alpha[0], table);
		result2 = Three_Analizer(root->alpha[1], table);
		result3 = Three_Analizer(root->alpha[2], table);
		result4 = Three_Analizer(root->alpha[3], table);
		return (result1 == -13 || result2 == -13 || result3 == -13 || result4 == -13)? -13 : 0;

	case 32:	//OpWhile
		if (!root->alpha[0] || !root->alpha[1])
			return -13;
		
		result1 = Three_Analizer(root->alpha[0], table);
		result2 = Three_Analizer(root->alpha[1], table);
		return (result1 == -13 || result2 == -13)? -13 : 0;

	case 33:	//EquExpr
	case 34:	//Expr
	case 38:	//Else
	case 39:	//DiffCondExpr
		if (!root->alpha[0])
			return -13;
		
		// ничего не проверяем
		return Three_Analizer(root->alpha[0], table);
		
	case 35:    //ArExpr
	case 42:	//Addendum
		if (!root->alpha[0] || !root->alpha[1])
			return -13;
		
		// получаем типы первого и второго потомка
		result1 = Three_Analizer(root->alpha[0], table);
		result2 = Three_Analizer(root->alpha[1], table);
		if (result1 == -13 || result2 == -13)
			return -13;
		
		// получим результирующий тип для потомков
		result3 = compare_types_arithmetic_expressions(result1, result2);
		if (result3 == 10)
			Add_semantic_error(8, root->n.numString, root->n.position);
		
		return result3;
		
	case 36:	//FuncOut
		if (!root->alpha[0])
			return -13;
		
		// если потомок один, то это L => возвращаемое значение - 0
		if (!root->alpha[1])
			return (Three_Analizer(root->alpha[0], table))? -13 : 0;

		// если потомков 2:
		// проверим что первый потомок имеет тип
		result1 = Three_Analizer(root->alpha[0], table);
		if (result1 < 8 || result1 > 10)
			return result1;
		
		result2 = Three_Analizer(root->alpha[1], table);
		return (result2 == -13)? -13 : result2 + 1;
		
	case 37:    //CondExpr
        if (!root->alpha[0] || !root->alpha[1])
			return -13;
		
		// получаем типы первого и второго потомка
		result1 = Three_Analizer(root->alpha[0], table);
		result2 = Three_Analizer(root->alpha[1], table);
		if (result1 == -13 || result2 == -13)
			return -13;
		
		// проверим что результирующий тип для потомков булевый
		result3 = check_bool_expression(result1, result2);
		if (result3)
			return 8;
		else
		{
			Add_semantic_error(9, root->n.numString, root->n.position);
			return 10;
		}
		
	case 40:    //SecDCE
        if (!root->alpha[0])
			return -13;
		
		// если потомок один, то это L => возвращаемое значение - 0
		if (!root->alpha[1])
			return (Three_Analizer(root->alpha[0], table))? -13 : 0;

		// если потомков 3:
		if (!root->alpha[2])
			return -13;

		// первый потомок - compop, возвращаемое значение - 0
		result1 = Three_Analizer(root->alpha[0], table);
		// получаем типы второго и третьего потомка
		result2 = Three_Analizer(root->alpha[1], table);
		result3 = Three_Analizer(root->alpha[2], table);
		if (result1 || result2 == -13 || result3 == -13)
			return -13;
		
		// проверим что результирующий тип для потомков булевый
		result1 = check_bool_expression(result2, result3);
		if (result1)
			return 8;
		else
		{
			Add_semantic_error(9, root->n.numString, root->n.position);
			return 10;
		}
		
	case 41:    //SimpCondExpr
		if (!root->alpha[0] || !root->alpha[1] || !root->alpha[2])
			return -13;
		
		// второй потомок - relop, возвращаемое значение - 0
		result2 = Three_Analizer(root->alpha[1], table);
		// получаем типы первого и третьего потомка
		result1 = Three_Analizer(root->alpha[0], table);
		result3 = Three_Analizer(root->alpha[2], table);
		if (result1 == -13 || result2 || result3 == -13)
			return -13;

		// проверим что результирующий тип для потомков булевый
		result2 = compare_types_arithmetic_expressions(result1, result3);
		if (result2)
			return 8;
		else
		{
			Add_semantic_error(9, root->n.numString, root->n.position);
			return 10;
		}
		
	case 43:	//SecAddendum
	case 45:	//SecMultipler
		if (!root->alpha[0])
			return -13;
		
		// если потомок один, то это L => возвращаемое значение - 0
		if (!root->alpha[1])
			return (Three_Analizer(root->alpha[0], table))? -13 : 0;

		// если потомков 3:
		if (!root->alpha[2])
			return -13;

		// первый потомок - addop или multop, возвращаемое значение - 0
		result1 = Three_Analizer(root->alpha[0], table);
		if (result1)
			return -13;
		
		// получаем типы второго и третьего потомка
		result2 = Three_Analizer(root->alpha[1], table);
		result3 = Three_Analizer(root->alpha[2], table);
		if (result2 == -13 || result3 == -13)
			return -13;
		
		// получим результирующий тип для потомков
		result1 = compare_types_arithmetic_expressions(result2, result3);
		if (result1 == 10)
			Add_semantic_error(8, root->n.numString, root->n.position);
		
		return result1;
		
	case 44:	//Multiplier
		if (!root->alpha[0])
			return -13;
	
		// если идентификатор не найден - вернем 8 (тип int, дабы не было ошибок)
		result1 = Three_Analizer(root->alpha[0], table);
		return (root->alpha[0]->n.numToken == 28 && !result1)? 8 : result1;

	case 50:	// L - конец программы
		return 0;

	default:
        printf("\n *************************************");
		printf("\n*** Oops! Error 404: case not found ***");
		printf("\n *************************************\n");
		return 0;
	}

	return 0;
}

// Функция производит анализ дерева разбора
struct Table_Identificators *semantic_analizer(struct nodeTree *root)
{
	struct Table_Identificators *table = Create_block(NULL, root->alpha[0]->n.numString);
	// инициализируем таблицу идентификаторов и пропускаем 2 вершины синтаксического дерева
	short code = Three_Analizer(root->alpha[0]->alpha[0], table);

	if (code == -13)
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

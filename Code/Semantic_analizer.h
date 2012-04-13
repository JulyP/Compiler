#ifndef SEMANTIC_ANALIZER_H_INCLUDED
#define SEMANTIC_ANALIZER_H_INCLUDED

#include "data structure.h"

unsigned short amount_id = 0;       //количество идентификаторов в программе
unsigned short numb_next_id = 1;    //номер следующего нового идентификатора

// создание нового блока
struct Table_Identificators *Create_block(struct Table_Identificators *Block)
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
        if (Block->level == max_level_blocks || Block->amount_blocks == max_amount_podblocs)
        {
             // сгенерировать ошибку! -=TBD=-
             return NULL;
        }

        p = (struct Table_Identificators*) malloc(sizeof(struct Table_Identificators));
        p->level = Block->level + 1;
        p->parent = Block;
    }

    p->amount_blocks = 0;
    p->amount_id = 0;
    p->table = NULL;
    for (i = 0; i <= max_amount_podblocs; i ++)
        p->child[i] = NULL;

    return p;
}

// проверка что идентификатор описан в текущем, либо вышестоящих блоках
short Check_id_descr(struct tokensFromScaner *id, struct Table_Identificators *Block);

// проверка что идентификатор описан в текущем блоке.
short Check_new_id_descr(struct tokensFromScaner *id, struct Table_Identificators *Block)
{
	struct Table_Id *p = Block->table;
	for (; p != NULL; p = p->next)
		if (p->token == id)
			return 1;
	return 0;
}

// поиск идентификатора в данном блоке.??? или во всей структуре???
// Если найден, вернется ссылка на него, если не найден – вернется NULL.
struct Table_Id *Search_id(struct tokensFromScaner *id, struct Table_Identificators *Block);

// добавляет идентификатор а таблицу, в указанный блок
struct Table_Id *Add_Id(short kind, struct tokensFromScaner *id, struct Table_Identificators *Block)
{
    struct Table_Id *p = NULL;

    if (Check_new_id_descr(id, Block))
        return NULL;

    if (Block->amount_id == max_amount_id)
    {
        // что делать когда много идентификаторов?? надо ошибку генерить. добвлять или нет?
        // -=TBD=-
        return NULL;
    }

    p = (struct Table_Id*) malloc(sizeof(struct Table_Id));
    if (!p)
        return NULL;

    p->token = id;
    p->kind = kind;
    p->next = Block->table;
    Block->table = p;
    p->new_name = numb_next_id;
    numb_next_id ++;
    Block->amount_id ++;

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
    1 - int
    2 - float
    3 - char
    0 - нет типа
    для оператора FuncOut: результат - уровень вложенности операторов
    для операторов CondExpr: результат:
    1 - булевский тип
    0 - иное*/
short Three_Analizer(struct nodeTree *root, struct Table_Identificators *table)
{
	int result_analisis, result1;	// в эту переменнтую сохраняем результат работы функции от потомков (тип вершины потомка)
	struct Table_Identificators *block = NULL;

	switch (root->n.numToken)
	{
	case 24:	//Block
		block = Create_block(table);
		if (!block)
            return 666;

		return Three_Analizer(root->alpha[0], &block);
	case 25:	//Sent
		if (root->alpha[0] == NULL)
			return 0;
		Three_Analizer(root->alpha[0], table);
		Three_Analizer(root->alpha[1], table);
		return 0;
		//break;
	case 26:	//DescrVar
		//*(root)->alpha[0]->numToken	// равен 8/9/10 - тип данных
		//*(root)->alpha[1]->value	// ссылка на идентификатор в таблице констант/имен
		result_analisis = Three_Analizer(root->alpha[2], table);

		// вставить проверку типов

		break;
	case 27:	//OpEqu
		//*(root)->alpha[0]->value	// ссылка на идентификатор в таблице констант/имен
		result_analisis = Three_Analizer(root->alpha[1], table);

		// вставить проверку типов

		break;
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
	case 42:
	case 43:
	case 44:
	case 45:
	default:
        return 777;
	}

	return 0;
}

// Функция производит анализ дерева разбора
struct Table_Identificators *semantic_analizer(struct nodeTree *root)
{
	struct Table_Identificators *table = Create_block(NULL);

	// инициализируем таблицу идентификаторов и пропускаем 2 вершины синтаксического дерева
	Three_Analizer(root->alpha[0]->alpha[0], table);
}

void printTable(struct Table_Identificators *table)
{
    struct Table_Id *p = NULL;
    int i;

    printf("\n---------------------------------\n");
    printf("level = %d\n", table->level);
    printf("amount id = %d\n", table->amount_id);
    printf("amount blocks = %d\n", table->amount_blocks);

    p = table->table;
    while (p)
    {
        if (p->token->pointerName)
            printf(" -> id = %s\n", p->token->pointerName->name);
        else
            printf(" -> error\n");
        p = p->next;
    }

    for (i = 0; i <= max_amount_podblocs; i ++)
        printTable(table->child[i]);
}

#endif // SEMANTIC_ANALIZER_H_INCLUDED

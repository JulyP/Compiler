#ifndef SEMANTIC_ANALIZER_H_INCLUDED
#define SEMANTIC_ANALIZER_H_INCLUDED

#include "data structure.h"

unsigned short amount_id;       //количество идентификаторов в программе
unsigned short numb_next_id;    //номер следующего нового идентификатора

// Данная функция проверяет уровень вложенности блока.
//Если уровень вложенности максимальный, то вернётся 1, если нет, то вернется 0.
bool Check_Block(Table_Identificators *Block)
{
	if (Block.level = max_level_blocks)
		return true;
	else
		return false;
}

// проверка что идентификатор описан в текущем, либо вышестоящих блоках
bool Check_id_descr(Name *id, Table_Identificators *Block)
{
	//while ()
}

// проверка что идентификатор не описан в текущем блоке.
bool Check_new_id_descr(id, Table_Identificators *Block)
{
	for (int i = 0; i < i_max_amount_id; i++)
		if (Block.table[i] == id)
			return true;
	return false;
}

// поиск идентификатора в данном блоке.
// Если найден вернется позиция в массиве идентификаторов данного блока, если не найден – вернется -1.
int Search_id(id, *Block)
{

}

// добавляет идентификатор а таблицу, в указанный блок
bool Add_Id(id, *Block)
{

}

// Функция добавляет вложенный блок к текущему блоку
Create_Block(Block)
{

}

// функция производит анализ текущей вершины дерева
// возвращаемые значения - тип текущей вершины:
// 1 - int
// 2 - float
// 3 - char
// 0 - нет типа
// для оператора FuncOut: результат - уровень вложенности операторов
// для операторов CondExpr: результат:
// 1 - булевский тип
// 0 - иное
int Three_Analizer(nodeTree **root, Table_Identificators **table)
{
	int result_analisis;	// в эту переменнтую сохраняем результат работы функции от потомков (тип вершины потомка)
	switch (*(root)->token)
	{
	case 24:	//Block
		if((*table)->level == max_level_blocks)
            //сгенерировать ошибку. уровень вложенности максимальный
		Table_Identificators *block = (struct Table_Identificators*) malloc(sizeof(struct Table_Identificators));
		block->parent = *(table);
		block->level = *(table)->level + 1;
		block->table = NULL
		for (int i = 0; i < max_amount_podblocs; i++)
			block->child[i] = NULL;
		Three_Analizer(&(*root->alpha[0]), &block);
		return 0;
		//break;
	case 25:	//Sent
		if (*(table)->alpha[0] == NULL)
			return 0;
		Three_Analizer(&(root->alpha[0]), &table);
		Three_Analizer(&(root->alpha[1]), &table);
		return 0;
		//break;
	case 26:	//DescrVar
		//*(root)->alpha[0]->numToken	// равен 8/9/10 - тип данных
		//*(root)->alpha[1]->value	// ссылка на идентификатор в таблице констант/имен
		result_analisis = Three_Analizer(&(root->alpha[2]), &table);

		// вставить проверку типов

		break;
	case 27:	//OpEqu
		//*(root)->alpha[0]->value	// ссылка на идентификатор в таблице констант/имен
		result_analisis = Three_Analizer(&(root->alpha[1]), &table);

		// вставить проверку типов

		break;
	case 28:	//OpIn
		return Three_Analizer(&(root->alpha[0]), &table);
	case 29:	//OpOut
		result_analisis = Three_Analizer(&(root->alpha[0]), &table);
		int level_out = Three_Analizer(&(root->alpha[1]), &table);

		// определиться с дальнейшим выводом
		// выдать ошибку если уровень вывода больше чем в К.У.

		break;
	case 30:	//OpIf
        //result_analisis = Three_Analizer(&(root->alpha[0]), &table);  // условие. проверить тип условия???

        //проверить ещё что то?

        Three_Analizer(&(root->alpha[1]), &table);
        Three_Analizer(&(root->alpha[2]), &table);
		break;
	case 31:
	case 32:
	case 33:	//EquExpr
		if (*(table)->alpha[0] == NULL)
			return 0;
		return Three_Analizer(&(root->alpha[0]), &table);
		break;
	case 34:	//Expr
		if (*(table)->alpha[0]->token == 6)
			//*(root)->alpha[0]->value	// ссылка на идентификатор в таблице констант/имен
		else
			return Three_Analizer(&(root->alpha[0]), &table);
		//break;
	case 35:    //ArExpr

	case 36:	//FuncOut
		if (*(table)->alpha[0] == NULL)
			return 0;
		result_analisis = Three_Analizer(&(root->alpha[0]), &table);
		return Three_Analizer(&(root->alpha[0]), &table);

		// что делать когда нет пива??? работать!!!

		break;
	case 37:    //CondExpr
        if (Three_Analizer(&(root->alpha[0]), &table) && Three_Analizer(&(root->alpha[1]), &table))
            return 1;
        else
            return 0;
	case 38:    //Else
        if (*(table)->alpha[0] == NULL)
			return 0;
		return Three_Analizer(&(root->alpha[0]), &table);

		break;
	case 39:    //DiffCondExpr
        return Three_Analizer(&(root->alpha[0]), &table);
	case 40:    //SecDCE
        if (*(table)->alpha[0] == NULL)
            return 1;
        //*(table)->alpha[0]    //операция И, ИЛИ. не надо(?)
        if (Three_Analizer(&(root->alpha[1]), &table) && Three_Analizer(&(root->alpha[2]), &table))
            return 1;
        else
            return 0;
	case 41:    //SimpCondExpr
        //*(table)->alpha[0]    //ссылка на идентификатор
        //*(table)->alpha[1]->numToken    //вид сравнения (не знаю зачем)
        result_analisis = Three_Analizer(&(root->alpha[2]), &table);    //тип выражения

        // вставить проверки типов для сравнения
        if ()   //вызов функции проверки?
            return 1;
        else
            return 0;
	case 42:
	case 43:
	case 44:
	case 45:
	default:
	}

	return 0;
}

// Функция модуля, доступная извне. производит анализ дерева разбора
Table_Identificators *analizer(Constant *table_const, Name *table_name, nodeTree *root)
{
	Table_Identificators *table = (struct Table_Identificators*) malloc(sizeof(struct Table_Identificators));
	table->parent = NULL;
	table->level = 1;
	table->table = NULL
	for (int i = 0; i <= max_amount_podblocs; i++)
		table->child[i] = NULL;

	amount_id = 0;
	numb_next_id = 1;
	// инициализируем таблицу идентификаторов и пропускаем 2 вершины синтаксического дерева
	Three_Analizer(&(root->alpha[0]->alpha[0]), &table);
}

#endif // SEMANTIC_ANALIZER_H_INCLUDED

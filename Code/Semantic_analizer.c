//#include <>

// константы из контекстных условий
//***************************

const int i_max_amount_id = 250;
const int i_max_amount_skobka = 10;
const int i_max_level_blocks = 8;
const int i_max_amount_print = 5;
const int i_max_amount_podblocs = 20;

//***************************

unsigned int amount_id;	//количество идентификаторов в программе

struct Table_Id
{
	Table_Of_Name  *Tab_Name;	//Ссылка на таблицу имен;
	Table_Of_Const *Tab_Const;	// Ссылка на таблицу констант;
	char type;	// Тип идентификатора
}
// type == 'n' => Table_Of_Name
// type == 'c' => Table_Of_Const

struct Table_Identificators 
{
	Table_Id  table[i_max_amount_id];	// В блоке <= 250 идентификаторов
	Table_Identificators  *Child[i_max_amount_podblocs];	// В блоке <= 20 вложенных подблоков
	Table_Identificators  *Parent;	// Указатель на родительский блок
	unsigned int level;	// Уровень вложенности данного блока
}

// Данная функция проверяет уровень вложенности блока. 
//Если уровень вложенности максимальный, то вернётся 1, если нет, то вернется 0. 
bool Check_Block(Table_Identificators *Block)
{
	if (Block.level = i_max_level_blocks)
		return true;
	else
		return false;
} 

// проверка что идентификатор описан в текущем, либо вышестоящих блоках
bool Check_id_descr(id, *Block)
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

// Функция модуля, доступная извне. производит анализ дерева разбора
Table_Identificators *analizer(*table_code, *table_name, *root)
{

}


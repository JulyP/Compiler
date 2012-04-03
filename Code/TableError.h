#ifndef TABLEERROR_H_INCLUDED
#define TABLEERROR_H_INCLUDED

struct nodeError			        //узел стека, в котором хранятся ошибки
{
	int numOfError;	            //номер ошибки
	int typeOfError;	        //тип ошибки (лексическая, синтаксическая, семантическая) 1 - лек 2 - син 3 - сем
	int numOfString;	        //номер строки, в которой произошла ошибка
	int position;		        //позиция ошибки (в какой позиции в строке произошла ошибка)
	struct nodeError *next;         //указатель на следующий элемент
};

void InsertTableError(struct nodeError **errorHead, int numOfError, int typeOfError, int numOfString,int position)//Функция добавляет в таблицу ошибок запись, возвращает номер созданной записи в таблице
{
	struct nodeError *p = (struct nodeError*)malloc(sizeof(struct nodeError));
	struct nodeError *p1 = *errorHead;
	p->numOfError = numOfError;
	p->typeOfError = typeOfError;
	p->numOfString = numOfString;
	p->position = position;
	p -> next = NULL;
	if (*errorHead == NULL)
	    *errorHead = p;
	else
	{
		while (p1 -> next  != NULL)
			p1 = p1 -> next;
		p1 -> next = p;
	}
}
void printTableError(struct nodeError *errorHead)
{
	struct nodeError *p = errorHead;
	while(p != NULL)
	{
		if(p->typeOfError == 1)
		{
			switch(p->numOfError){
			case 0: printf("Максимальная длина идентификатора больше 50 символов. Строка %d позиция %d \n", p->numOfString, p->position);
			        break;
			case 1: printf("Максимальная длина числа больше 9 символов. Строка %d позиция %d \n", p->numOfString, p->position);
				    break;
			case 2: printf("Пропуск символов закрывающих комментарий */. Строка %d позиция %d \n", p->numOfString, p->position);
				    break;
			case 3: printf("Максимальная длина буфера больше 256 символов \n");
				    break;
			case 4: printf("Неизвестный символ. Строка %d позиция %d \n", p->numOfString, p->position);
				    break;
			case 5: printf("Неправильная запись числа, после точки не цифра. Строка %d позиция %d \n", p->numOfString, p->position);
				    break;
			case 6: printf("Пропуск символа закрывающей кавычки. Строка %d позиция %d \n", p->numOfString, p->position);
				    break;
			}
		}
		p = p->next;
	}
}

#endif // TABLEERROR_H_INCLUDED

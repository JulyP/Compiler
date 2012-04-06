#ifndef TABLECONSTANT_H_INCLUDED
#define TABLECONSTANT_H_INCLUDED

/*struct nodeConst
{
	unsigned int num ;	//длина строковой константы
	char *str;	//строка
	struct nodeConst *next;
};
*/
struct nodeConst* InsertTableConstString(struct nodeConst **constHead, unsigned int n, char *str) //Функция добавляет в таблицу строковых и числовых констант, возвращает номер созданной записи в таблице
{
	unsigned int i = 0;
	struct nodeConst *p = (struct nodeConst*)malloc(sizeof(struct nodeConst));
	struct nodeConst *p1 = *constHead;
	p->num = n;
	p->str = (char*)calloc(n+1,sizeof(char));
	for (i =0 ;i < n; i++)
	   p->str[i] = str[i];
	p->str[n] = '\0';
	p -> next = NULL;
	if (*constHead == NULL)
	    *constHead = p;
	else
	{
		while (p1 -> next  != NULL)
			p1 = p1 -> next;
		p1 -> next = p;
	}
	return p;
}
void printTableConst(struct nodeConst *constHead)
{
	struct nodeConst *p = constHead;
	while(p != NULL)
	{
		printf("%d %s \n", p->num, p->str);
		p = p->next;
	}
}

#endif // TABLECONSTANT_H_INCLUDED

#ifndef TABLENAME_H_INCLUDED
#define TABLENAME_H_INCLUDED

/*struct nodeName
{
    unsigned int n;
    char *name;
    unsigned int token;
    unsigned int numToken;
    unsigned short kindToken;	//идентиф - 1 или ключевое слово - 0
    struct nodeName *next, *prev;
};
*/
void addName(struct nodeName **nameHead, unsigned int n, char *name,unsigned int token, unsigned int numToken, unsigned short kindToken)
{
    int i = 0;
	struct nodeName *p = (struct nodeName*)malloc(sizeof(struct nodeName));
	struct nodeName *p1 = *nameHead;
	p->n = n;
	p->name = (char*)calloc(n+1, sizeof(char));
	for (i = 0 ;i < n; i++)
	    p->name[i] = name[i];
	p->name[n] ='\0';
	p->token = token;
	p->numToken = numToken;
	p->kindToken = kindToken;
	p -> next = NULL;
	p -> prev = NULL;
    if (*nameHead == NULL)
	    *nameHead = p;
	else
	{
		while (p1 -> next  != NULL)
			p1 = p1 -> next;
		p -> prev = p1;
		p1 -> next = p;
	}
}

void freeListName(struct nodeName **nameHead)
{
	struct nodeName *p = NULL;
    if (nameHead == NULL)
		return;
	while (nameHead != NULL)
	{
		p = *nameHead;
		*nameHead = p -> next;
		free(p);
	}
}
void InsertKeyWords(struct nodeName **nameHead)
{
	addName(nameHead, 4, "main", 0, 1, 0);
	addName(nameHead, 3, "cin", 9, 2, 0);
	addName(nameHead, 4, "cout", 11, 3, 0);
	addName(nameHead, 5, "while", 18, 4, 0);
	addName(nameHead, 3, "for", 17, 5, 0);
	addName(nameHead, 2, "if", 13, 6, 0);
	addName(nameHead, 4, "else", 16, 7, 0);
	addName(nameHead, 3, "int", 5, 8, 0);
	addName(nameHead, 5, "float", 5, 9, 0);
	addName(nameHead, 6, "string", 5, 10, 0);
}

struct nodeName* LookupTableName(struct nodeName *nameHead, char string[])
{
   struct nodeName *p = nameHead;
   while (p != NULL)
   {
	   if (strcmp(p->name, string) != 0)
	   {
		   p = p->next;
	   }
	   else
		   return p;
   }
   return NULL;
}

struct nodeName* InsertTableName(struct nodeName **nameHead, unsigned int n, char *string)
{
    addName(nameHead, n, string, 3, 28, 1);
    return LookupTableName(*nameHead, string);
}

void printTableName(struct nodeName *nameHead)
{
	struct nodeName *p = nameHead;
	while(p != NULL)
	{
		printf("%d %s %d %d %d \n", p->n, p->name, p->token, p->numToken, p->kindToken);
		p = p->next;
	}
}

#endif // TABLENAME_H_INCLUDED

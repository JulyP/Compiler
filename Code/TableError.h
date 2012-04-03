#ifndef TABLEERROR_H_INCLUDED
#define TABLEERROR_H_INCLUDED

struct nodeError			        //���� �����, � ������� �������� ������
{
	int numOfError;	            //����� ������
	int typeOfError;	        //��� ������ (�����������, ��������������, �������������) 1 - ��� 2 - ��� 3 - ���
	int numOfString;	        //����� ������, � ������� ��������� ������
	int position;		        //������� ������ (� ����� ������� � ������ ��������� ������)
	struct nodeError *next;         //��������� �� ��������� �������
};

void InsertTableError(struct nodeError **errorHead, int numOfError, int typeOfError, int numOfString,int position)//������� ��������� � ������� ������ ������, ���������� ����� ��������� ������ � �������
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
			case 0: printf("������������ ����� �������������� ������ 50 ��������. ������ %d ������� %d \n", p->numOfString, p->position);
			        break;
			case 1: printf("������������ ����� ����� ������ 9 ��������. ������ %d ������� %d \n", p->numOfString, p->position);
				    break;
			case 2: printf("������� �������� ����������� ����������� */. ������ %d ������� %d \n", p->numOfString, p->position);
				    break;
			case 3: printf("������������ ����� ������ ������ 256 �������� \n");
				    break;
			case 4: printf("����������� ������. ������ %d ������� %d \n", p->numOfString, p->position);
				    break;
			case 5: printf("������������ ������ �����, ����� ����� �� �����. ������ %d ������� %d \n", p->numOfString, p->position);
				    break;
			case 6: printf("������� ������� ����������� �������. ������ %d ������� %d \n", p->numOfString, p->position);
				    break;
			}
		}
		p = p->next;
	}
}

#endif // TABLEERROR_H_INCLUDED

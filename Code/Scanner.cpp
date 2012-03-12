#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

//Глобальные переменные
char *buf;    //буфер с считанной строкой
int numToken = 0; //номер атрибута (от 1 до 39)
int value = 0;    //номер в таблице имен или констант
int POS = 0;  //позиция в буфере
int position = 0;//позиция в строке
int state = 0;//текущее состояние
int start = 0;//начальное состояние

//Структуры
struct tokensFromScaner{
	int token;      //номер токена (от 0 до 23)
	int numToken;   //номер атрибута (от 1 до 39)
	int value;      //номер в таблице имен или констант
	int numString;  //номер строки
	int position; //позиция в строке(в буфере)
};

struct node
{
	tokensFromScaner n;
	node *next, *prev;
};
node *Head;

void addElem(tokensFromScaner n)
{
	node *p = (node*)malloc(sizeof(node));
	node *p1 = Head;
    p -> n = n;
	p -> next = NULL;
	p -> prev = NULL;
    if (Head == NULL)
		Head = p;
	else
	{
		while (p1 -> next  != NULL)
			p1 = p1 -> next;
		p -> prev = p1;
		p1 -> next = p;
	}
}

void freeList()
{
	node *p = NULL;
    if (Head == NULL)
		return;
	while (Head != NULL)
	{
		p = Head;
		Head = p -> next;
		//cout << p->n.token << " delete ";
		free(p);
	}
}

bool isLetter(char ch)     //проверка на дозволенные символы «A..Z», «a..z»
{
	if ((ch>='a' && ch<='z')||(ch>='A' && ch <= 'Z') ||(ch == '_'))
		return true;
	else
		return false;
}

bool isDigit(char ch)     //проверка «0..9»
{
	if (ch>='0' && ch<='9')
		return true;
	else
		return false;
}

char nextchar(){
   char symbol = buf[POS];
   POS++;
   return symbol;
}

int fail()
{
  POS--;
  switch (start){
      case 0: return 1;
      case 1:  return 5;
      case 2:  return 3;
      case 3:  return 4;
      case 5:  return 8;
      case 6:  return 7;
      case 8:  return 12;
      case 9:  return 10;
      case 10:  return 11;
      case 12:  return 15;
	  case 13:  return 14;
      case 15:  return 17;
      case 17:  return 23;
      case 18:  return 19;
      case 19:  return 20;
	  //case 21: error();break;// неправильная запись числа (после точки не цифра)
      case 23:  return 26;
	  case 24:  return 25;
	  //case 25: error();break;//отсутствует закрывающая "
      case 26:  return 27;
      case 27:  return 35;
      case 28:  return 30;
      case 30:  return 34;
	  case 31:  return 32;
	  //case 32: error();break;//нет закрывающей */
	  //case 33: error();break;//нет закрывающей */
	  case 35:  return 36;
      case 36:  return 37;
      case 37:  return 38;
      case 38:  return 39;
      case 39:  return 40;
      case 40:  return 41;
	  case 41:  return 42;
      case 42:  return 43;
	  case 43:  return 45;
      case 44:  return 45;
      //case 45:  error();break;//символ не распознан
	  case 46:  return 47;
	  //case 47:  error();break;//символ не распознан

  }
}

int nexttoken()
{
  char name[8];
  char c;
  int count;
  while(1){
  switch(state){
  case 0: c = nextchar();
          if (c == ' '){
             state = 0;
             POS++;
          }
          else
		  {
			  start = state;
			  state = fail();
		  }
          break;
  case 1: c = nextchar();
	      if (c == '<'){
          state = 2;
          }
          else
		  {
			  start = state;
			  state = fail();
		  }
          break;
  case 2: c = nextchar();
          if (c == '='){
          numToken = 17;//символ <=
          return 20;
          }
          else
          {
			  start = state;
			  state = fail();
		  }
          break;
  case 3: c = nextchar();
          if (c == '<'){
          numToken = 25;//символ <<
          return 12;
          }
          else
         {
			  start = state;
			  state = fail();
		  }
          break;
  case 4: c = nextchar();
	      if ((c != '<')||(c != '=')){
			  POS--;
              numToken = 14;//символ <
			  return 20;
          }
  case 5: c = nextchar();
          if (c == '='){
          state = 6;
          }
          else
         {
			  start = state;
			  state = fail();
		  }
          break;
  case 6: c = nextchar();
          if (c == '='){
		  numToken = 18;//символ ==
          return 20;
          }
          else
{
			  start = state;
			  state = fail();
		  }
          break;
  case 7: c = nextchar();
          if (c != '='){
		  POS--;
		  numToken = 26;//символ =
          return 8;
          }
  case 8: c = nextchar();
          if (c == '>'){
          state = 9;
          }
          else
         {
			  start = state;
			  state = fail();
		  }
          break;
  case 9: c = nextchar();
          if (c == '>'){
		  numToken = 24;//символ >>
          return 10;
          }
          else
          {
			  start = state;
			  state = fail();
		  }
          break;
  case 10: c = nextchar();
          if (c == '='){
          numToken = 16;
          return 20;//символ >=
          }
          else
          {
			  start = state;
			  state = fail();
		  }
          break;
  case 11: c = nextchar();
          if ((c != '=')||(c !='>'))
		  {
			  POS--;
			  numToken = 15;//символ <
			  return 20;
		  }
  case 12: c = nextchar();
          if (c == '!'){
          state = 13;
          }
          else
          {
			  start = state;
			  state = fail();
		  }
          break;
  case 13: c = nextchar();
          if (c == '='){
		  numToken = 19;
          return 20;//символ !=
          }
          else
		  {
			  start = state;
			  state = fail();
		  }
  case 14: c = nextchar();
	       if(c != '='){
			  POS--;
		      numToken = 13;
		      return 19;//символ !
	       }
   case 15:  c = nextchar();
	         if (isLetter(c)){
				 count = 0;
                 name[count] = c;
                 state = 16;
             }
			 else{

              start = state;
			  state = fail();
			 }
          break;
  case 16:  c = nextchar();
	        if (isLetter(c) || isDigit(c)){
				count++;
                name[count] = c;
                state = 16;
          }
          else
             {
			   POS--;
               //value = LookupTableName(name);
               //if (value == 0)
               //    value = InsertTableName(name, 3);
               //else  return token;
			   return 0;//идентификатор или ключевое слово
             }
 case 17: c = nextchar();
          if (isDigit(c)){
          state = 18;
          }
		  else{
		   start = state;
		   state = fail();
		  }
          break;
  case 18: c = nextchar();
          if (isDigit(c)){
          state = 18;
		  }
          else
		  {
			  start = state;
			  state = fail();
		  }
          break;
  case 19: c = nextchar();
          if (c == '.' ){
          state = 21;
          }
          else
		  {
			  start = state;
			  state = fail();
		  }
          break;
  case 20: c = nextchar();
          if (c != '.' ){
		  POS--;
		  numToken = 8;
          return 5;//целое исло
          }
  case 21: c = nextchar();
          if (isDigit(c)){
          state = 22;
          }
          else
		  {
			  start = state;
			  state = fail();
		  }
          break;
  case 22: c = nextchar();
          if (isDigit(c)){
          state = 22;
          }
		  else{
			  POS--;
              numToken = 9;
			  return 5;//вещ число
		  }
		  break;
  case 23: c = nextchar();
          if (c == '"'){
          state = 24;
          }
          else
		  {
			  start = state;
			  state = fail();
		  }
          break;
   case 24: c = nextchar();
          if (isLetter(c) || isDigit(c)){
          state = 24;
          }
          else
		  {
			  start = state;
			  state = fail();
		  }
		  break;
   case 25: c = nextchar();
            if (c =='"'){
			   //добавить в табл констант
			   numToken = 27;
               return 6;//строка
            }
			else
			{
			  start = state;
			  state = fail();
			}
			break;
	case 26: c = nextchar();
          if (c == '*'){
		  numToken = 22;
          return 22;//умножениее
          }
          else
		  {
			  start = state;
			  state = fail();
		  }
          break;
  case 27: c = nextchar();
          if (c == '/'){
          state = 28;
          }
          else
		  {
			  start = state;
			  state = fail();
		  }
          break;
  case 28: c = nextchar();
          if (c == '/'){
          state = 29;
          }
          else
		  {
			  start = state;
			  state = fail();
		  }
          break;
  case 29: c = nextchar();
          if (isLetter(c) || isDigit(c)){
          state = 29;
          }
          else
             return -1;
		  break;
  case 30: c = nextchar();
          if (c == '*'){
          state = 31;
          }
          else
         {
			  start = state;
			  state = fail();
		  }
          break;
  case 31: c = nextchar();
          if (isLetter(c) || isDigit(c)){
          state = 31;
          }
          else
          {
			  start = state;
			  state = fail();
		  }
		  break;
  case 32: c = nextchar();
          if (c == '*'){
          state = 33;
          }
          else
          {
			  start = state;
			  state = fail();
		  }
          break;
  case 33: c = nextchar();
          if (c == '/'){
          return -1;
          }
          else
          {
			  start = state;
			  state = fail();
		  }
          break;
  case 34: c = nextchar();
          if ((c != '/') || (c!='*')){
		  POS--;
		  numToken = 23;
          return 22; //деление
         }
		 break;
 case 35: c = nextchar();
          if (c == ';'){
			  numToken = 35;
			  return 4;//;
		  }
          else
          {
			  start = state;
			  state = fail();
		  }
          break;
  case 36: c = nextchar();
          if (c == ','){
			  numToken = 36;
			  return 23;//,
		  }
          else
          {
			  start = state;
			  state = fail();
		  }
          break;
  case 37: c = nextchar();
          if (c == '{'){
			  numToken = 31;
			  return 1;//{
		  }
          else
          {
			  start = state;
			  state = fail();
		  }
          break;
  case 38: c = nextchar();
          if (c == '}'){
			  numToken = 32;
			  return 2;//}
		  }
          else
          {
			  start = state;
			  state = fail();
		  }
          break;
  case 39: c = nextchar();
          if (c == '('){
			  numToken = 33;
			  return 14;//(
		  }
          else
          {
			  start = state;
			  state = fail();
		  }
          break;
  case 40: c = nextchar();
          if (c == ')'){
			  numToken = 34;
			  return 15;//)
		  }
          else
          {
			  start = state;
			  state = fail();
		  }
          break;
  case 41: c = nextchar();
          if (c == '+'){
			  numToken = 20;
			  return 21;//+
		  }
          else
          {
			  start = state;
			  state = fail();
		  }
          break;
  case 42: c = nextchar();
          if (c == '-'){
			  numToken = 21;
			  return 21;//-
		  }
          else
          {
			  start = state;
			  state = fail();
		  }
          break;
  case 43: c = nextchar();
          if (c == '|'){
			  state = 44;
		  }
          else
		  {
			  start = state;
			  state = fail();
		  }
          break;
  case 44: c = nextchar();
          if (c == '|'){
			  numToken = 12;
			  return 19;//||
		  }
          else
          {
			  start = state;
			  state = fail();
		  }
          break;
  case 45: c = nextchar();
          if (c == '&'){
			  state = 46;
		  }
          else
          {
			  start = state;
			  state = fail();
		  }
          break;
  case 46: c = nextchar();
          if (c == '&'){
			  numToken = 11;
			  return 19;//&&
		  }
          else
          {
			  start = state;
			  state = fail();
		  }
          break;
  case 47: c = nextchar();
          if (c != '&'){
			  start = state;
			  state = fail();
		  }
		  break;
  }
}
}

int main(){
	int numString = 0, n;
	tokensFromScaner  tokens;
	int m = 11;
	buf = new char[m];
	buf[0] = '"';
	buf[1] = 'h';
	buf[2] = 'e';
	buf[3] = '"';
	buf[4] = '|';
	buf[5] = '|';
	buf[6] = '}';
	buf[7] = '{';
	buf[8] = '&';
	buf[9] = '&';
	buf[10] = '=';
	//cout << buf[0];
	while (POS < m)
	{
			state = 0;
			start = 0;
			numToken = 0;
			position = 0;
			int t = nexttoken();
			cout << numToken <<" - "<< t << " ; " << endl;
			tokens.token = t;
			tokens.numToken = numToken;
			tokens.value = value;
	        tokens.numString = numString;
			tokens.position = position;
            addElem(tokens);
	}

	node *p = Head;
	while(p != NULL)
	{

		cout << p->n.token << " "<< p->n.numToken << " " << p->n.value << " " << p->n.numString << " "<< p->n.position << endl;
		p = p->next;
	}
    cout << "\n\nprint!\n";
	freeList();
	//cin>>n;
    return 0;
};

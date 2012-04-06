#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED

//Константы
const unsigned short max_length_id = 50;//максимальная длина идентификатора
const unsigned short max_length_num = 9;//	максимальная длина числа
const unsigned short max_length_string = 100;//максимальная длина строки
const unsigned short max_length_buf = 256;//максимальная длина буфера

//Глобальные переменные
char *buf;    //буфер с считанной строкой
unsigned short numToken = 0; //номер атрибута (от 1 до 39)
struct nodeName* pointerName = NULL;    //указатель в таблицу имен
struct nodeConst* pointerConst = NULL; //указатель в таблицу констант
unsigned int POS = 0;  //позиция в буфере
unsigned int numOfString = 1;
unsigned int position = 0;//позиция в строке
unsigned short state = 0;//текущее состояние
unsigned short start = 0;//начальное состояние
unsigned int numLex = 1;//порядковый номер лексемы
unsigned int counter = 0;//длина буфера

struct nodeName *nameHead;//указатель в таблицу имен
struct nodeConst *constHead;
struct nodeError *errorHead;

//Структуры
/*struct tokensFromScaner{
	unsigned short token;      //номер токена (от 0 до 23)
	unsigned short numToken;   //номер атрибута (от 1 до 39)
	struct nodeName* pointerName;    //указатель в таблицу имен
	struct nodeConst* pointerConst; //указатель в таблицу констант
	unsigned int numString;  //номер строки
	unsigned int position; //позиция в строке(в буфере)
	unsigned int numLex; //порядковый номер лексемы
};

struct node{
	struct tokensFromScaner n;
	struct node *next;
};

struct node *Head;
*/
void addElem(struct tokensFromScaner n){
	struct node *p = (struct node*)malloc(sizeof(struct node));
	struct node *p1 = Head;
        p -> n = n;
	p -> next = NULL;
        if (Head == NULL){
		Head = p;
	}
	else{
		while (p1 -> next  != NULL){
			p1 = p1 -> next;
		}
		p1 -> next = p;
	}
}

void freeList(){
	struct node *p = NULL;
    	if (Head == NULL){
		return;
	}
	while (Head != NULL){
		p = Head;
		Head = p -> next;
    		free(p);
	}
}

void printListTokens(){
	struct node *p = Head;
	while(p != NULL){

		printf("%d %d %p %p %d %d %d \n", p->n.token, p->n.numToken, p->n.pointerName, p->n.pointerConst, p->n.numString, p->n.position, p->n.numLex);
		p = p->next;
	}
}

unsigned short isLetter(char ch){     //проверка на дозволенные символы «A..Z», «a..z»
	if ((ch>='a' && ch<='z')||(ch>='A' && ch <= 'Z') ||(ch == '_')){
		return 1;
	}
	else{
		return 0;
	}
}

unsigned short isDigit(char ch){     //проверка «0..9»
	if (ch>='0' && ch<='9'){
		return 1;
	}
	else{
		return 0;
	}
}

char nextchar(){
   char symbol = buf[POS];
   POS++;
   return symbol;
}

void error (int error){
			switch(error){
			case 0: InsertTableError(&errorHead, 0, 1, numOfString, POS);
				    POS++;
			        break;
			case 1: InsertTableError(&errorHead, 1, 1, numOfString, POS);
				    POS++;
				    break;
			case 2: InsertTableError(&errorHead, 2, 1, numOfString, POS);
				    POS = counter;
				    break;
			case 3: InsertTableError(&errorHead, 3, 1, numOfString, POS);
				    break;
			case 4: InsertTableError(&errorHead, 4, 1, numOfString, POS);
				    POS++;
				    break;
			case 5: InsertTableError(&errorHead, 5, 1, numOfString, POS);
				    POS++;
				    break;
			case 6: InsertTableError(&errorHead, 6, 1, numOfString, POS);
					POS = counter;
				    break;
			}

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
      case 23:  return 26;
	  case 24:  return 25;
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
  char name[250];
  unsigned int i = 0;
  for (i = 0; i < 250; i++)
    	name[i] = '\0';
  char str[250];
  for (i = 0; i < 250; i++)
    	str[i] = '\0';
  int num =0;
  char c;
  int count=0;
  while(1){
  switch(state){
  case 0: c = nextchar();
          if (c == ' '){
             state = 0;
          }
          else
		  {   if(POS > counter)
				return -1;
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
		  break;
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
		  break;
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
		  break;
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
		  break;
  case 14: c = nextchar();
	       if(c != '='){
			  POS--;
		      numToken = 13;
		      return 19;//символ !
	       }
		   break;
   case 15:  c = nextchar();
	         if (isLetter(c)){
				 name[count++] = c;
                 state = 16;
             }
			 else{

              start = state;
			  state = fail();
			 }
          break;
  case 16:  c = nextchar();
	        if (isLetter(c) || isDigit(c)){
			    name[count++] = c;
                state = 16;
          }
          else
             {
			   POS--;
               struct nodeName *value = LookupTableName(nameHead, name);
			   if (value == NULL)
			   {
				   value = InsertTableName(&nameHead, count, name);
                   numToken = value->numToken;
				   pointerName = value;
				   return 3;
			   }
               else
			   {
				   numToken = value->numToken;
				   pointerName = value;
				   return value->token;
			   }; //идентификатор или ключевое слово
			}
			break;
 case 17: c = nextchar();
          if (isDigit(c)){
		  num = 0;
		  str[num++] = c;
          state = 18;
          }
		  else{
		   start = state;
		   state = fail();
		  }
          break;
  case 18: c = nextchar();
          if (isDigit(c)){
			   str[num++] = c;
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
			   str[num++] = c;
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
		  pointerConst = InsertTableConstString(&constHead, num, str);
          return 7;//целое число *** исправила юля п
          }
		  break;
  case 21: c = nextchar();
          if (isDigit(c)){
		  str[num++] = c;
          state = 22;
          }
          else
		  {
			  error(5);
			  return -1;
		  }
          break;
  case 22: c = nextchar();
          if (isDigit(c)){
		  str[num++] = c;
          state = 22;
          }
		  else{
			  POS--;
              numToken = 9;
			  pointerConst = InsertTableConstString(&constHead, num, str);
			  return 7;//вещ число  ***исправила юля п
		  }
		  break;
  case 23: c = nextchar();
          if (c == '"'){
		  num = 0;
          state = 24;
          }
          else
		  {
			  start = state;
			  state = fail();
		  }
          break;
   case 24: c = nextchar();
	      if (c != '"'){//(isLetter(c) || isDigit(c)){
		  str[num++] = c;
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
			   pointerConst = InsertTableConstString(&constHead, num, str);
			   numToken = 27;
               return 6;//строка
            }
			else
			{
			  //start = state;
			  //state = fail();
			  InsertTableError(&errorHead, 6, 1, numOfString, POS);//отсутствует закрывающая "
			  POS++;//как исправлять??
			  return -1;
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

void Scanner(){
	//structsetlocale(LC_ALL, "Russian");
	FILE*f;
	char q;
	unsigned int i = 0;
	struct tokensFromScaner  tokens;
	buf = (char*)calloc(max_length_buf + 1, sizeof(char));
   	InsertKeyWords(&nameHead);
	f = fopen("input.txt","rt");
	for (i = 0; i <= max_length_buf + 1; i++)
		buf[i]='\0';
    while (!(feof(f)))
    {
		fscanf(f,"%c",&q);
		if ((q != '\n') && !(feof(f)))
		{
			buf[counter++] = q;
		}
		else
		{
			while (POS < counter)
	       {
			state = 0;
			start = 0;
			numToken = 0;
			position = 0;
			pointerName = NULL;
			pointerConst = NULL;
			tokens.token = nexttoken();
			tokens.numToken = numToken;
			tokens.pointerName = pointerName;
			tokens.pointerConst = pointerConst;
	                tokens.numString = numOfString;
			tokens.position = position;
			tokens.numLex = numLex++;
                        addElem(tokens);
			}
			numOfString++;
			POS = 0;
			for (i = 0; i <= counter;i++)
		            buf[i]='\0';
			counter = 0;
		}
	}
	printListTokens();
	//printTableConst(constHead);
	printf("+++++++++++++++++++++++++ \n");
	printTableName(nameHead);
	//printTableError(errorHead);
};

#endif // SCANNER_H_INCLUDED

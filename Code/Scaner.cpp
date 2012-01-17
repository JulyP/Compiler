Struct Error
{
         int CodeError; // код ошибки
         int NumberOfString; //номер строки, где произошла ошибка   
}*TableOfError // таблица ошибок


Struct Name	
{
	char name[]; //имя
          char kindtoken[];	//тип токена (идентификатор или ключевое слово)
           char kindid[]; // тип идентификатора(int, string, float)
           int value; // номер в таблице строковых и числовых констант
} *TableOfName // таблица имен


Struct Constant	
{
	int num ;	//длина строковой константы
	char str[];	//строка
}* TableOfConst // таблица строковых и числовых конcтант


Struct tokensFromScanner
{
   Int token;        //номер токена (от 0 до 22)
   Int numToken;     //номер атрибута (от 1 до 39)
   Int  value;       //номер в таблице имен или констант
   Int numString;    //номер строки
}*tokens   //поток лексем

bool LengthString(string)    //проверка, что длина строки <=100
bool IsLetter(char)     //проверка на дозволенные символы «A..Z», «a..z»}
bool IsNumber(char)  //проверка «0..9»
bool LengthNumber(string) //проверка, что длина числа <=9
Функции таблиц имен:

Int InsertTableName(string, token)//Функция добавляет в таблицу имен запись. Возвращает номер созданной записи в таблице.
Int LookupTableName(string)//Функция поиска возвращает номер в таблице имен для string или 0, если строка не найдена.присваивает token номер токена
Int InsertKeyWords()//Функция добавление ключевых слов в таблицу имен.
Функции таблиц строковых  и числовых констант:
Int InsertTableConstString(string) //Функция добавляет в таблицу строковых и числовых констант, возвращает номер созданной записи в таблице;
Int InsertTableError(int, int) //Функция добавляет в таблицу ошибок запись, возвращает номер созданной записи в таблице;

int start;
char *buf;
int numToken;
int value;
int token;


int scanner()
{
  numString = 0;
  tokensFromScanner CurToken;
  пока не конец файла{
  numString++;
  считываем 1 строку из файла;
  помещаем в buf;
  пока конец buf не достигнут{
  start = 0;
  token =0;
  numToken =0;
  value=0;
  token = nexttoken();
  формируем токен;
  CurToken.token = token;
  CurToken.numToken = numToken;
  CurToken.value = value;
  CurToken.numString = numString;
  помещаем полученный токен в поток токенов;
  }
  }   
}

char nextchar(){
   char symbol = buf[POS];
   POS++;
   return symbol;
}

int fail()
{
  switch (start){
      POS--;
      case 0: start = 1; break;
      case 1: start = 5; break;
      case 2: start = 3; break;
      case 3: start = 4; break;
      case 5: start = 8; break;
      case 6: start = 7; break;
      case 8: start = 12; break;
      case 9: start = 10; break;
      case 10: start = 11; break;
      case 12: start = 14; break;
      case 14: start = 16; break;
      case 16: start = 22; break;
      case 17: start = 18; break;
      case 18: start = 19; break;
      case 22: start = 24; break;
      case 24: start = 25; break;
      case 25: start = 33; break;
      case 26: start = 28; break;
      case 28: start = 32; break;
  }

}


token nexttoken()
{
  char *name = '';
  while(1){
  switch(state){
  case 0: c = nextchar();
          if (c == ' '){
             state = 0;
             POS++;
          }
          else 
             state = fail();   
          break;
      }
  case 1: c = nextchar();
          if (c == '<'){
          state = 2;
          }
          else 
             state =fail();
          break;
  case 2: c = nextchar();
          if (c == '='){
          numToken = 17;
          return 20;
          }
          else 
             state = fail();
          break;
  case 3: c = nextchar();
          if (c == '<'){
          numToken = 25;
          return 12;
          }
          else 
             state = fail();
          break;
  case 4: c = nextchar();
          if (c != '<')||(c != '='){
          return;
          }
  case 5: c = nextchar();
          if (c == '='){
          state = 6;
          }
          else 
             state = fail();
          break;
  case 6: c = nextchar();
          if (c == '='){
          return;
          }
          else 
             state = fail();
          break;
  case 7: c = nextchar();
          if (c != '='){
          return;
          }
  case 8: c = nextchar();
          if (c == '>'){
          state = 9;
          }
          else
             state = fail();
          break;
  case 9: c = nextchar();
          if (c == '>'){
          return;
          }
          else
             state = fail();
          break;
  case 10: c = nextchar();
          if (c == '='){
          return;
          }
          else
             state = fail();
          break;
  case 11: c = nextchar();
          if (c != '=')||(c !='>'){
          return;
  case 12: c = nextchar();
          if (c == '!'){
          state = 13;
          }
          else
             state = fail();
          break;
  case 13: c = nextchar();
          if (c == '='){
          return;
          }
          else
             return;
  case 14:  c = nextchar();
          name[0] = c;
          if (isletter(c)){
          state = 15;
          }
          else
             state = fail();
          break; 
  case 15:  c = nextchar();
          if (isletter(c) or isdigit(c)){
          name[i] = c;
          state = 15;
          i++;
          }
          else
             {
               value = LookupTableName(name);
               if (value == 0)
                   value = InsertTableName(name, 3);
               else  return token; 
             }
  case 16: c = nextchar();
          if (isdigit(c)){
          state = 17;
          }
          else
             state = fail();
          break;
  case 17: c = nextchar();
          if (isdigit(c)){
          state = 18;
          }
          else
             state = fail();
          break;
  case 18: c = nextchar();
          if (c == '.' ){
          state = 20;
          }
          else
             state = fail();
          break;
  case 19: c = nextchar();
          if (c != '.' ){
          return;
          } 
  case 20: c = nextchar();
          if (isdigit(c)){
          state = 21;
          } 
          else
             state = fail();????
          break; 
  case 21: c = nextchar();
          if (isdigit(c)){
          state = 21;
          } 
          else
            return;
  case 22: c = nextchar();
          if (c == '"'){
          state = 23;
          } 
          else
             state = fail();
          break;
  case 23: c = nextchar();
          if (isletter(c) or isdigit(c)){
          state = 23;
          } 
          else
              return;
  case 24: c = nextchar();
          if (c == '*'){
          return;
          } 
          else
              state = fail();
          break;
  case 25: c = nextchar();
          if (c == '/'){
          state = 26;
          } 
          else
              state = fail();
          break;
  case 26: c = nextchar();
          if (c == '/'){
          state = 27;
          } 
          else
              state = fail();
          break;
  case 27: c = nextchar();
          if (isletter(c) or isdigit(c)){
          state = 27;
          } 
          else
             return;
  case 28: c = nextchar();
          if (c == '*'){
          state = 29;
          } 
          else
              state = fail();
          break;
  case 29: c = nextchar();
          if (isletter(c) or isdigit(c)){
          state = 29;
          } 
          else
              state = 30; 
  case 30: c = nextchar();
          if (c == '*'){
          state = 31;
          } 
          else
              state = fail();????
          break;
  case 31: c = nextchar();
          if (c == '/'){
          return;
          } 
          else
              state = fail();????
          break; 
  case 32: c = nextchar();
          if (c != '/') || (c!='*'){
          return;
  case 33: c = nextchar();
          if (c == ';'){
          return;
          else
              state = fail();????
          break; 

}

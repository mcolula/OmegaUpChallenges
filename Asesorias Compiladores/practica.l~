%{
  #include "practica.tab.h"
  #include <stdio.h>
  #include "list.h"

  extern list * table;
  char ans[1000];
%}




operator        [\+\-\*\%\^/]
digit           [0-9]+
char            [A-Za-z0-9" "]
letter          [A-Za-z]
integer         {digit}+
string          \"(\\.|[^\\"])*\"
double          ({digit}*"."{digit}+|{digit}+"."{digit}*)([eE][-+]?[0-9]+)?
identifier      ("_"|{letter})({letter}|{digit}|"_")*

%% 

{integer}       {
                  //printf("Integer Value: %s\n", yytext);
                  yylval.Integer = atoi(yytext);
                  return (integerValue);
                }

{double}        {
                  //printf("Double Value: %s\n", yytext);
                  yylval.Double = atof(yytext);
                  return (doubleValue);
                }

{operator}      {
                  //printf("Operator: %c\n", yytext[0]);
                  return (yytext[0]);
                }

"string"        {
                  //printf("Type String\n");
                  return (typeString);
                }

"double"        {
                  //printf("Type Double\n");
                  return (typeDouble);
                }

"int"           {
                  //printf("Type Integer\n");
                  return (typeInteger);
                }


"if"            {
                  return (IF);
                }

"!="            {
                  return (NEQ);
                }

"=="            {
                  return (EQ);
                }

">="            {
                  return (GREQ);
                }

"<="            {
                  return (LSEQ);
                }

"<"             {
                  return (LS);
                }

">"             {
                  return (GR);
                }

{identifier}    {
                  item * ans = search(table, yytext);
                  yylval.String = strdup(yytext);
                  if (!ans) {
                    //printf("Undeclared ID: %s\n", yytext);
                    return (undeclrID);
                  }
                  else if (strcmp(ans->type, "integer") == 0) {
                    //printf("Integer ID: %s\n", yytext);
                    return (integerID);
                  }
                  else if (strcmp(ans->type,  "double") == 0) {
                    //printf("double ID: %s\n", yytext);
                    return (doubleID);	
                  }
                  else if (strcmp(ans->type,  "string") == 0) {
                    //printf("string ID: %s\n", yytext);
                    return (stringID);	
                  }
                }

{string}        { 
	          int  i = 0;
	          for (i = 1; i + 1< strlen(yytext); i++)
                    ans[i - 1] = yytext[i];
                  ans[i - 1] = '\0';
                  yylval.String = strdup(ans);
                  return (stringValue);
                }

"\n"            {
                  return (yytext[0]);
                }

"("             {
                  return (yytext[0]);
                }

")"             {
                  return (yytext[0]);
                }

"="             {
                  return (yytext[0]);
                }

";"             {
                  return (yytext[0]);
                }

.               ;

%%

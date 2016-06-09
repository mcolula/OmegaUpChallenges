%{
  #include <math.h>
  #include "list.h"
%}
             

%{
  #define  MX 1000
  
  list * table;  
  char ans[MX];

  char * concat(char * a, char * b) {
    strcpy(ans, ""); 
    strcat(ans,  a); 
    strcat(ans,  b); 
    return strdup(ans);    
  }

%}

%union {
  int   Integer;
  double Double;
  char * String;
}

%token <Integer> integerValue
%token <Double>  doubleValue
%token <String>  stringValue
%type  <Integer> integerExp
%type  <Double>  doubleExp
%type  <String>  stringExp
%token <String>  integerID
%token <String>  undeclrID
%token <String>  doubleID
%token <String>  stringID
%type  <Integer> assign
%type  <Integer> declr
%type  <String>  invExp
%type  <Integer> redeclr
%type  <String>  typeError
%type  <String>  assignError

%token typeInteger
%token typeString
%token typeDouble

%left '+' '-'
%left '*' '/' '%'
%left umin
%left  '('     
%left  '^'
%left  '='

%%
             
input:  
                   | input line             
;

line:              '\n'
                   | integerExp   '\n'                       { printf("ans = %d\n",   $1);      } 
                   | doubleExp    '\n'                       { printf("ans = %f\n",   $1);      }
                   | stringExp    '\n'                       { printf("ans = '%s'\n", $1);      }                   
                   | declr        '\n'                       { printf("Definición  exitosa\n"); }
                   | assign       '\n'                       { printf("Asignación  exitosa\n"); }
                   | invExp       '\n'                       { printf("Expresión  inválida\n"); }
                   | typeError    '\n'                       { printf("Tipos   incorrectos\n"); }
                   | redeclr      '\n'                       { printf("Variable  existente\n"); }
                   | assignError  '\n'                       { printf("Error en asignación\n"); }
;                                                              


// Gramatica para expresiones tipo int
integerExp:          integerValue                              { $$ =  $1;          }
                   | integerExp '+' integerExp                 { $$ =  $1 + $3;     }
                   | '-' integerExp %prec umin                 { $$ = -$2;          }
                   | '('    integerExp     ')'                 { $$ =  $2;          }
                   | integerID                                 { $$ =  atoi(search(table, $1)->data); }
;                                                              
                                                              
// Gramatica para expresiones tipo double                                                             
doubleExp:           doubleValue                               { $$ =  $1;          }
                   | doubleExp  '+' doubleExp                  { $$ =  $1 + $3;     }
                   
                   | doubleExp  '+' integerExp                 { $$ =  $1 + $3;     }
                   
                   | integerExp '+' doubleExp                  { $$ =  $1 + $3;     }
                   
                   | '-' doubleExp %prec umin                  { $$ = -$2;          }
                   | '('    doubleExp     ')'                  { $$ =  $2;          }
                   | doubleID                                  { $$ =  atof(search(table, $1)->data); }
;                                                              

// Gramatica para expresiones tipo string
stringExp:           stringValue                               { $$ = $1;             }  
                   | stringExp '+' stringExp                   { $$ = concat($1, $3); }
                   | '('    stringExp     ')'                  { $$ = $2;             }
                   | stringID                                  { $$ = search(table,  $1)->data; }
;                                                              
                                                              
// Gramatica para expresiones con identificadores no definidos
invExp:              undeclrID                                 { printf("Variable '%s' no existe\n", $1);  } 
                   | integerExp '+' invExp                     {  }
                   
                   | invExp '+' integerExp                     {  }
                   
                   | doubleExp '+' invExp                      {  }
                   
                   | invExp '+' doubleExp                      {  }
                   
                   | stringExp '+' invExp                      {  }
                   
                   | invExp '+' stringExp                      {  }
                   
                   | invExp '+' invExp                         {  }
                   
                   | '-' invExp %prec umin                     {  }
                   | '('    invExp      ')'                    {  }
                   | typeInteger undeclrID '=' invExp          {  }
                   
                   | undeclrID '=' integerExp                  {  }
                   
                   | integerID '=' invExp                      {  }
                   | doubleID  '=' invExp                      {  }
                   | stringID  '=' invExp                      {  }
                   | undeclrID '=' invExp                      {  }                  
;                                               


// Gramatica para expresiones con errores de tipo                                                              
typeError:           stringExp  '+' integerExp                 {  }
                   
                   | integerExp '+' stringExp                  {  }
                   
                   | stringExp  '+' doubleExp                  {  }
                   
                   | doubleExp  '+' stringExp                  {  }
                   
                   | '-' stringExp %prec umin                  {  }
;                                                             

// Gramatica para expresiones con errores de redefinición
redeclr:             typeString stringID                       {  }
                   | typeString doubleID                       {  }
                   | typeString integerID                      {  }
                   | typeDouble stringID                       {  }
                   | typeDouble doubleID                       {  }
                   | typeDouble integerID                      {  }
                   | typeInteger stringID                      {  }
                   | typeInteger doubleID                      {  }
                   | typeInteger integerID                     {  }
                   | typeString stringID  '=' integerExp       {  }
                   | typeString stringID  '=' doubleExp        {  }
                   | typeString stringID  '=' stringExp        {  }
                   | typeString stringID  '=' invExp           {  }
                   
;                                                             
                                                              
// Gramatica para asignaciones
assign:              stringID  '=' stringExp                   { update(table, $1,  $3);                                 }
                   | integerID '=' integerExp                  { sprintf(ans, "%d", $3);         update(table, $1, ans); }
;           

// gramatica para asignaciones con tipos incorrectos
assignError:         stringID  '=' integerExp                  {  }
                   
                   | typeString  undeclrID '=' integerExp      {  }
                   
;
                                                                                                                 
// Gramatica para declaraciones
declr:               typeInteger  undeclrID '=' integerExp     { sprintf(ans,  "%d",            $4); insert(table, "integer", $2, ans); }
                   | typeString   undeclrID '=' stringExp      { insert(table, "string",  $2,   $4); }
                   | typeInteger  undeclrID                    { insert(table, "integer", $2,  "0"); }
;

%%

int yyerror(char * s) {
  printf("%s\n", s);
}

int main() {
  table = (list*) malloc(sizeof(list));
  if (yyparse())
     fprintf(stderr, "Successful parsing.\n");
  else
     fprintf(stderr, "error found.\n");
}

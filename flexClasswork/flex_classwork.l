%{
#include <stdio.h>
%}

%%
([0-9]+) {printf("INT");}
[0-9]+\.{1}[0-9]+|\.{1}[0-9]|[0-9]+\.{1} {printf("FLOAT");}
[mM]{1}(onday)|[tT]{1}(uesday|hursday)|[wW]{1}(ednesday)|[fF]{1}(riday)|[sS]{1}(aturday|unday) {printf("VALIDDAY");}
[[:alnum:]]+[\._-]?[[:alnum:]]+\@[[:alpha:]]+.com {printf("VALIDEMAIL");}
%%

int main(int argc, char ** argv) {
  yylex();
  return 0;
}
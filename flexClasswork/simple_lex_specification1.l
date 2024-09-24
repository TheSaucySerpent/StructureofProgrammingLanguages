%{
#include <stdio.h>
%}

%%
\$[A-Z] { printf("VARIABLE"); }
= { printf("EQUALS"); }
[0-9]+ { printf("NUMBER"); }
%%

int main(int argc, char** argv) {
  yylex();
  return 0;
}
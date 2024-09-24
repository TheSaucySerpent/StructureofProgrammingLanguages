%{
#include <stdio.h>
int a = 0;
int b = 0;
%}

%%
\n { ++a; ++b; }
. { ++a; }
%%

int main(int argc, char** argv) {
  yylex();
  printf("%d, %d\n", a, b);
}
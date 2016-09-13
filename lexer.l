%{
#include "shell.h"
vec_t * p_global_argv;
%}

%option noyywrap

%%
"<"               printf("LREDIR\n");
">"               printf("RREDIR\n");
"|"               printf("PIPE\n");
"&"               printf("BKGPROC\n");
[a-zA-Z0-9_/.-]+  {
                      printf("EXPRN\n");
                      /* char * tok = strdup(yytext); */
                      /* vec_push(p_global_argv, &tok); */
                  }
%%

YY_BUFFER_STATE global_buffer_state;

void lexer_set_argv(vec_t * p_argv) {
    p_global_argv = p_argv;
}

void lexer_parse_buffer(char * buffer) {
    yy_scan_buffer(buffer, read_buffer_size);
    yylex();
    yy_delete_buffer(YY_CURRENT_BUFFER);
}
%{
#include "shell.h"
vec_t * p_global_argv;
%}

%option noyywrap

%%

[a-zA-Z0-9]+   {
                   char * tok = strdup(yytext);
                   vec_push(p_global_argv, &tok);
               }
%%

YY_BUFFER_STATE global_buffer_state;

void lexer_set_argv(vec_t * p_argv) {
    p_global_argv = p_argv;
}

void lexer_parse_buffer(char * buffer) {
    yy_scan_buffer(buffer, read_buffer_size);
    yylex();
    /* TODO: Memory leak if return of yy_scan_buffer not handled!? */
}

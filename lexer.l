%{
vec_t * p_global_lexer_target;
%}

%option noyywrap
%option nounput
%option noinput

%%
"cd"                  {
                          char * tok = strdup(yytext);
                          vec_push(p_global_lexer_target, &tok);
                          global_builtin_idxs[CMD_CD] = global_num_commands - 1;
                          global_num_builtins += 1;
                      }
"exit"                {
                          char * tok = strdup(yytext);
                          vec_push(p_global_lexer_target, &tok);
                          global_builtin_idxs[CMD_EXIT] = global_num_commands - 1;
                          global_num_builtins += 1;
                      }
"|"                   {
                          char * tok = strdup(yytext);
                          vec_push(p_global_lexer_target, &tok);
                          global_num_commands += 1;
                      }
"<"|">"|"&"           {
                          char * tok = strdup(yytext);
                          vec_push(p_global_lexer_target, &tok);
                      }
\"(\\.|[^"])*\"       {
                          size_t len = strlen(yytext) - 2;
                          if (len > 0) {
                              char * tok = malloc(len + 1);
                              memcpy(tok, yytext + 1, len);
                              tok[len] = '\0';
                              vec_push(p_global_lexer_target, &tok);
                          }
                      }
[a-zA-Z0-9~@:_/\.-]+  {
                          char * tok = strdup(yytext);
                          vec_push(p_global_lexer_target, &tok);
                      }
[ \n\t]+ /* Ignore whitespace... */
%%

YY_BUFFER_STATE global_buffer_state;

void lexer_set_target(vec_t * p_target) {
    p_global_lexer_target = p_target;
}

void lexer_parse_buffer(char * buffer) {
    yy_scan_buffer(buffer, READ_BUFFER_SIZE);
    yylex();
    yy_delete_buffer(YY_CURRENT_BUFFER);
}

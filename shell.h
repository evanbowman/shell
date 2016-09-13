#pragma once
#include <sys/wait.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

typedef struct vec_t {
	char * data;
	size_t len;
	size_t insert_pos;
	size_t elem_size;
} vec_t;

/* CORE SHELL IMPLEMENTATION */
void shell_read(char *, vec_t *);
void shell_eval(vec_t *);
void launch_process(const char *, vec_t *, bool);

/* VECTOR DATA STRUCTURE IMPLEMENTATION */
int vec_init(vec_t *, const size_t);
int vec_push(vec_t *, const void *);
void vec_pop(vec_t *);
void vec_clear(vec_t *, void (*)(void *));
void vec_free(vec_t * p_vec, void (*)(void *));

/* VARIOUS CONSTANTS USED IN PROGRAM */
enum constants {
	read_buffer_size = 512,
	vec_growth_rate = 2
};

/* FOR THE LEXER */
void lexer_set_argv(vec_t *);
void lexer_parse_buffer(char *);

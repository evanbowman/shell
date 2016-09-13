#include "shell.h"

void vec_clear_policy(void * vec) {
	vec_t * p_vec = vec;
	char ** argv = (char **)p_vec->data;
	for (size_t i = 0; i < p_vec->insert_pos; i++) {
		if (argv[i]) free(argv[i]);
		argv[i] = NULL;
	}
}

int main(void) {
	char buffer[read_buffer_size];
	vec_t argv;
	vec_init(&argv, sizeof(char *));
	lexer_set_argv(&argv);
	puts("my_shell");
	while (true) {
		memset(buffer, '\0', read_buffer_size);
		shell_read(buffer, &argv);
		shell_eval(&argv);
		vec_clear(&argv, vec_clear_policy);
	}
	vec_free(&argv, vec_clear_policy);
	return 0;
}

void shell_read(char * buffer, vec_t * p_vec) {
	printf(">> ");
	fgets(buffer, read_buffer_size, stdin);
    lexer_parse_buffer(buffer);
}

void shell_eval(vec_t * p_vec) {
	/* eval the text... */
	/* TEMPORARY!! */
	/* char ** argv = (char **)p_vec->data; */
	/* for (size_t i = 0; i < p_vec->insert_pos; i++) { */
	/* 	printf("%s\n", argv[i]); */
	/* } */
}

void launch_process(const char * proc_name, vec_t * p_vec, bool wait) {
	enum pid_kind {
		child = 0,
		error = -1
	};
	pid_t pid = fork();
	int status;
    switch (pid) {
	case child:
		execve(proc_name, (char **)p_vec->data, NULL);
		perror("exec");
		break;
		
	case error:
		perror("fork");
		break;
		
	default:
		if (wait) waitpid(pid, &status, WUNTRACED | WCONTINUED);
		break;
	}
}

int vec_init(vec_t * p_vec, const size_t elem_size) {
	p_vec->data = malloc(elem_size);
	if (!p_vec->data) {
		return 0;
	}
	memset(p_vec->data, 0, p_vec->len);
	p_vec->len = elem_size;
	p_vec->insert_pos = 0;
	p_vec->elem_size = elem_size;
	return 1;
}

int vec_push(vec_t * p_vec, const void * p_element) {
	const size_t elem_size = p_vec->elem_size;
	if (p_vec->len >= (p_vec->insert_pos + 1) * elem_size) {
		memcpy(p_vec->data + p_vec->insert_pos * elem_size, p_element, elem_size);
		++p_vec->insert_pos;
	} else {
		char * new_data = malloc(p_vec->len * vec_growth_rate);
		if (!new_data) return 0;
		memcpy(new_data, p_vec->data, p_vec->len);
		free(p_vec->data);
		p_vec->data = new_data;
		memcpy(p_vec->data + p_vec->insert_pos * elem_size, p_element, elem_size);
		++p_vec->insert_pos;
		p_vec->len *= vec_growth_rate;
	}
	return 1;
}

void vec_pop(vec_t * p_vec) {
	memset(p_vec->data + (p_vec->insert_pos - 1) * p_vec->elem_size, 0, p_vec->elem_size);
}

void vec_clear(vec_t * p_vec, void (* policy)(void *)) {
    policy(p_vec);
	p_vec->insert_pos = 0;
}

void vec_free(vec_t * p_vec, void (* policy)(void *)) {
	policy(p_vec);
	free(p_vec->data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 01:26:25 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/22 00:03:09 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

void	token_list_print(t_token *head)
{
	t_token	*iter;
	char	*enum_names[6] = \
	{"STRING", "REDIR_TO", "APPEND_TO", "REDIR_FROM", "HERE_DOC", "PIPE"};	
	
	if (head == NULL)
	{
		printf("<null node>\n");
		return ;
	}
	iter = head;
	while (iter != NULL)
	{
		printf("type = %-12s, val = {%s}\n", enum_names[iter->type], iter->value);
		iter = iter->next;
	}
	printf("\n");
}

static char	*get_input(void)
{
	char	*prompt;
	char	*input;

	prompt = ft_strdup("test_parser $ ");
	if (prompt == NULL)
		exit_error("minishell: Error allocating memory: malloc", EXIT_FAILURE);
	input = readline(prompt);
	ft_free_n_null((void **)&prompt);
	return (input);
}

void interactive() {
	while (1) {
		char *line = get_input();
		t_token *token_list = parse(line);
		token_list_print(token_list);
		free(line);
	}
}

void test_ll_add_when_null() {
	printf("===============================================================\n");
	printf("                      Int Linked List                          \n");
	printf("===============================================================\n");
	t_list_int *head = NULL;
	list_add(&head, 42);
	printf("value of newly added node = %d\n", head->val);
	list_print(head);
}

void test_expansion_detection_variable() {
	printf("===============================================================\n");
	printf("              Variable Expansion Detection                     \n");
	printf("===============================================================\n");
	#define EXP_VAR_DET_TEST_COUNT 8
	char *var_expansion_detection_tests[EXP_VAR_DET_TEST_COUNT] = {
		" $$$ ",
		" $1 $2$$$ ",
		"$2$ ",
		" $? ",
		"$2$ $a x",
		"a$$b",
		"a$b$c123$$$$$a$2$ x",
		"a$$b \" a$$b \" a$$b \' a$$b \' a$$b"
	};

	for (int i = 0; i < EXP_VAR_DET_TEST_COUNT; ++i) {
		char *test_case = var_expansion_detection_tests[i];
		printf("test case %d = {%s}\n", i + 1, test_case);

		t_list_int *actual = NULL;
		detect_var_exp(test_case, &actual, 0, 0);
		
		list_print(actual);
		printf("\n");
	}
}

void test_expansion_detection_tilda() {
	printf("===============================================================\n");
	printf("              Tilda Expansion Detection                        \n");
	printf("===============================================================\n");
	#define EXP_TLD_DET_TEST_COUNT 8
	char *tilda_expansion_detection_tests[EXP_TLD_DET_TEST_COUNT] = {
		"~",
		" \" ~ \" ",
		" \' ~ \' ",
		" a~ ",
		" ~a ",
		" ~/ ",
		" ~/a ",
		" ~/a ~/ ~a a~ \' ~ \' \" ~ \" ~ ~"
	};

	for (int i = 0; i < EXP_TLD_DET_TEST_COUNT; ++i) {
		char *test_case = tilda_expansion_detection_tests[i];
		printf("test case %d = {%s}\n", i + 1, test_case);

		t_list_int *actual = NULL;
		detect_tld_exp(test_case, ft_strlen(test_case), &actual);
		
		list_print(actual);
		printf("\n");
	}
}

void test_str_append_appendc() {
	printf("===============================================================\n");
	printf("              str_append()   str_appendc()                     \n");
	printf("===============================================================\n");
	char *s1 = NULL;
	char *s2 = "hello world";
	printf("s1 initially         = %s\n", s1);
	str_append(&s1, s2);
	printf("s1 after str append  = %s\n", s1);
	str_appendc(&s1, 'x');
	printf("s1 after char append = %s\n", s1);
}

void test_token_list() {
	printf("===============================================================\n");
	printf("                           Token List                          \n");
	printf("===============================================================\n");
	t_token *head = NULL;
	add_token(&head, STRING, "hello there", NULL);
	token_list_print(head);
	add_token(&head, APPEND_TO, ">>", NULL);
	token_list_print(head);
}

void test_tokenizer() {
	printf("===============================================================\n");
	printf("                            Tokenizer                          \n");
	printf("===============================================================\n");
	#define TOKENIZER_TEST_COUNT 4
	char *tokenizer_tests[TOKENIZER_TEST_COUNT] = {
		"cat hello1>file2name 123>file1name123>world<<\" EOF\"",
		"export VAR=\"echo hi | cat\"",
		"echo asd << \"\" << file2",
		"echo hi | cat -e"
	};

	for (int i = 0; i < TOKENIZER_TEST_COUNT; ++i) {
		char *test_case = tokenizer_tests[i];
		printf("test case %d = {%s}\n", i + 1, test_case);

		t_token *token_list = tokenize(test_case, NULL);
		token_list_print(token_list);
		printf("\n");
	}
}

void test_parser() {
	printf("===============================================================\n");
	printf("                            Parser                             \n");
	printf("===============================================================\n");
	#define PARSER_TEST_COUNT 4
	char *tokenizer_tests[PARSER_TEST_COUNT] = {
		"cat hello1>file2name 123>file1name123>world<<\" EOF\"",
		"export VAR=\"echo hi | cat\"",
		"echo asd << \"\" << file2",
		"echo hi | cat -e"
	};

	for (int i = 0; i < PARSER_TEST_COUNT; ++i) {
		char *test_case = tokenizer_tests[i];
		printf("test case %d = {%s}\n", i + 1, test_case);

		t_token *token_list = parse(test_case);
		token_list_print(token_list);
		printf("\n");
	}
}

static int	init_minishell(void)
{
	extern char	**environ;
	extern int	errno;

	errno = 0;
	environ = dup_environ();
	if (environ == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
	init_minishell();
	
	if (argc == 2 && ft_strncmp(argv[1], "i", 1) == 0)
	{
		interactive();
	}
	else
	{
		test_ll_add_when_null();
		test_expansion_detection_tilda();
		test_expansion_detection_variable();
		test_str_append_appendc();
		test_token_list();
		test_tokenizer();
		test_parser();	
	}
}

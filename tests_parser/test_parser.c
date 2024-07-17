/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 01:26:25 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/17 07:41:11 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

void test_ll_add_when_null() {
	t_list_int *head = NULL;
	list_add(&head, 42);
	printf("value of newly added node = %d\n", head->val);
	list_print(head);
}

void test_expansion_detection_variable() {
	#define EXP_VAR_DET_TEST_COUNT 5
	char *var_expansion_detection_tests[EXP_VAR_DET_TEST_COUNT] = {
		"$2$ ",
		"$2$ $a x",
		"a$$b",
		"a$b$c123$$$$$a$2$ x",
		"a$$b \" a$$b \" a$$b \' a$$b \' a$$b"
	};

	for (int i = 0; i < EXP_VAR_DET_TEST_COUNT; ++i) {
		char *test_case = var_expansion_detection_tests[i];
		printf("test case = <%s>\n", test_case);

		t_list_int *actual = NULL;
		detect_var_expansions(test_case, &actual, 0);
		
		list_print(actual);
		printf("\n");
	}
}

void test_expansion_detection_tilda() {
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
		printf("test case = <%s>\n", test_case);

		t_list_int *actual = NULL;
		detect_tilda_expansions(test_case, &actual);
		
		list_print(actual);
		printf("\n");
	}
}

void test_str_append_appendc() {
	char *s1 = NULL;
	char *s2 = "hello world";
	printf("s1 initially         = %s\n", s1);
	str_append(&s1, s2);
	printf("s1 after str append  = %s\n", s1);
	str_appendc(&s1, 'x');
	printf("s1 after char append = %s\n", s1);
}

void test_token_list() {
	t_token *head;

	add_token(&head, STRING, "hello there");
	printf("added first\n");
	token_list_print(head);
	add_token(&head, APPEND_TO, ">>");
	token_list_print(head);
}

int main() {
	// test_ll_add_when_null();
	// test_expansion_detection_tilda();
	// test_expansion_detection_variable();
	// test_str_append_appendc();
	test_token_list();
}

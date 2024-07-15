/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 01:26:25 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/15 03:42:47 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void test_ll_add_when_null() {
	t_list_int *head = NULL;
	list_add(&head, 42);
	printf("value of newly added node = %d\n", head->val);
	list_print(head);
}

void test_expansion_tilda() {
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
		t_list_int *actual = NULL;
		detect_tilda_expansions(test_case, actual);
		list_print(actual);
		printf("\n");
	}
}

int main() {
	test_ll_add_when_null();
	// test_expansion_tilda();
}

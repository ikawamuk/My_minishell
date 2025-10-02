/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokurita <kokurita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 22:10:23 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/29 17:30:42 by kokurita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "define.h"
#include "token.h"
#include "parse_utils.h"

static bool	has_word(char *string);
static int	get_split_list(t_token_list *list, t_token_list **result_list_p);
int			split_string(char *str, t_token_list **sub_list_p);

int	split_token_list(t_token_list **list_p)
{
	t_token_list	*result_list;

	result_list = NULL;
	if (get_split_list(*list_p, &result_list) != NO_ERROR)
	{
		free_token_list(result_list);
		return (FATAL_ERROR);
	}
	free_token_list(*list_p);
	*list_p = result_list;
	return (NO_ERROR);
}

static int	get_split_list(t_token_list *list, t_token_list **result_list_p)
{
	t_token_list	**result_tail_p;
	t_token_list	*sub_list;

	result_tail_p = result_list_p;
	while (list)
	{
		if (has_word(list->data.word))
		{
			sub_list = NULL;
			if (split_string(list->data.word, &sub_list) != NO_ERROR)
				return (FATAL_ERROR);
			*result_tail_p = sub_list;
			while (sub_list->next)
				sub_list = sub_list->next;
			result_tail_p = &sub_list->next;
		}
		list = list ->next;
	}
	return (NO_ERROR);
}

static bool	has_word(char *string)
{
	while (is_space(*string))
		string++;
	if (!*string)
		return (false);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:20:41 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/23 17:08:57 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "define.h"
#include "token.h"
#include "parse_utils.h"
#include "libft.h"

static int	get_sub_list(char *str, t_token_list **list_p);
static char	*export_next_word(char *str, size_t *index_p);
static void	skip_word_index(char *str, size_t *ip);
static int	append_token(char *word, t_token_list **list_p);

int	split_string(char *str, t_token_list **sub_list_p)
{
	if (get_sub_list(str, sub_list_p) != NO_ERROR)
	{
		free(*sub_list_p);
		return (FATAL_ERROR);
	}
	return (NO_ERROR);
}

static int	get_sub_list(char *str, t_token_list **list_p)
{
	char			*word;
	size_t			index;

	index = 0;
	while (str[index])
	{
		if (!has_next_word(str, index))
			break ;
		word = export_next_word(str, &index);
		if (!word)
			return (FATAL_ERROR);
		if (append_token(word, list_p) != NO_ERROR)
			return (FATAL_ERROR);
	}
	return (NO_ERROR);
}

static char	*export_next_word(char *str, size_t *index_p)
{
	size_t	start;

	while (is_space(str[*index_p]))
		(*index_p)++;
	start = *index_p;
	skip_word_index(str, index_p);
	return (ft_substr(str, start, *index_p - start));
}

static void	skip_word_index(char *str, size_t *ip)
{
	char	quote;

	while (str[*ip] && !is_space(str[*ip]))
	{
		if (is_quote_marker(str[*ip]))
		{
			quote = str[*ip];
			(*ip)++;
			while (quote != str[*ip])
				(*ip)++;
			(*ip)++;
		}
		else
			(*ip)++;
	}
	return ;
}

static int	append_token(char *word, t_token_list **list_p)
{
	t_token_list	*new;

	new = malloc(sizeof(t_token_list));
	if (!new)
	{
		free(word);
		return (FATAL_ERROR);
	}
	new->data.type = T_WORD;
	new->data.word = word;
	new->next = NULL;
	push_token(list_p, new);
	return (NO_ERROR);
}

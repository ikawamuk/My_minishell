/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:49:47 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/23 17:36:46 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "parse_utils.h"

static void	mark_quote(char **str_p);
void		quote_string(char *str);

void	quote_token_list(t_token_list *list)
{
	while (list)
	{
		quote_string(list->data.word);
		list = list->next;
	}
	return ;
}

void	quote_string(char *str)
{
	while (*str)
	{
		if (is_quote(*str))
			mark_quote(&str);
		else
			str++;
	}
	return ;
}

static void	mark_quote(char **str_p)
{
	char	quote;

	quote = **str_p;
	if (quote == '\'')
		**str_p = (char)S_QUOTE_MARKER;
	else if (quote == '"')
		**str_p = (char)D_QUOTE_MARKER;
	(*str_p)++;
	while (quote != **str_p)
		(*str_p)++;
	if (quote == '\'')
		**str_p = (char)S_QUOTE_MARKER;
	else if (quote == '"')
		**str_p = (char)D_QUOTE_MARKER;
	(*str_p)++;
	return ;
}

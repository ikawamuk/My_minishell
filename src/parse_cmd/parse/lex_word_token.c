/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_word_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 21:27:48 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/10/02 20:20:34 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "token.h"
#include "libft.h"
#include "parse_utils.h"
#include "utils.h"

static int	skip_quoted_part(char quote, const char *str, size_t *ip);

int	lex_word_token(t_token *token, const char *str, size_t *ip)
{
	const char	*head;

	token->type = T_WORD;
	token->word = NULL;
	head = str + *ip;
	while (str[*ip] && !is_space(str[*ip]) && !is_metachar(str[*ip]))
	{
		if (is_quote(str[*ip]))
		{
			if (skip_quoted_part(str[*ip], str, ip) == UNCLOSED_QUOTE)
				return (PARSE_SYNTAX_ERROR);
		}
		else
			(*ip)++;
	}
	token->word = ft_strndup(head, &str[*ip] - head);
	if (!token->word)
		return (PARSE_FATAL_ERROR);
	return (PARSE_NO_ERROR);
}

static int	skip_quoted_part(char quote, const char *str, size_t *ip)
{
	(*ip)++;
	while (str[*ip] && str[*ip] != quote)
		(*ip)++;
	if (!str[*ip])
		return (UNCLOSED_QUOTE);
	(*ip)++;
	return (PARSE_NO_ERROR);
}

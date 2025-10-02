/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 21:03:51 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/18 23:20:57 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "parse.h"
#include "token.h"
#include "parse_utils.h"
#include "libft.h"

static int	lex_special_token(t_token *token, const char *str, size_t *ip);
static void	detect_special_token_type(const char *head, t_token_type *type);
int			lex_word_token(t_token *token, const char *str, size_t *ip);

int	lex(t_token *token, const char *str, size_t *ip)
{
	int	result;

	result = NO_ERROR;
	token->word = NULL;
	while (is_space(str[*ip]))
		(*ip)++;
	if (!str[*ip])
		token->type = T_NULL;
	else if (is_metachar(str[*ip]))
		result = lex_special_token(token, str, ip);
	else
		result = lex_word_token(token, str, ip);
	return (result);
}

static int	lex_special_token(t_token *token, const char *str, size_t *ip)
{
	const char	*head;

	head = str + *ip;
	if ((*head == '>' || *head == '<') && *head == *(head + 1))
		*ip += 2;
	else
		(*ip)++;
	token->word = NULL;
	detect_special_token_type(head, &token->type);
	return (PARSE_NO_ERROR);
}

static void	detect_special_token_type(const char *head, t_token_type *type_p)
{
	if (*head == '<')
	{
		if (*head == *(head + 1))
			*type_p = T_LESS_LESS;
		else
			*type_p = T_LESS;
	}
	else if (*head == '>')
	{
		if (*head == *(head + 1))
			*type_p = T_GREATER_GREATER;
		else
			*type_p = T_GREATER;
	}
	else if (*head == '|')
		*type_p = T_BAR;
	else
		*type_p = T_ERROR;
	return ;
}

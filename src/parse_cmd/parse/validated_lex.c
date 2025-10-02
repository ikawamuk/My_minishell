/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validated_lex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:54:01 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/17 21:34:41 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "token.h"
#include "libft.h"
#include "parse_utils.h"

int			lex(t_token *token, const char *str, size_t *ip);
static bool	is_valid_sequence(t_token_type token_type, t_parse_info *info);

int	vaidated_lex(t_token *token, t_parse_info *info)
{
	int	result;

	ft_bzero(token, sizeof(*token));
	result = lex(token, info->str, &info->str_i);
	if (is_parse_error(result))
		return (result);
	if (!is_valid_sequence(token->type, info))
		return (PARSE_SYNTAX_ERROR);
	info->last_token = token->type;
	return (PARSE_NO_ERROR);
}

static bool	is_valid_sequence(t_token_type token_type, t_parse_info *info)
{
	if (T_NULL == token_type)
	{
		if (info->last_token != T_WORD && info->last_token != T_NULL)
			return (false);
	}
	else if (is_command_connector(token_type))
	{
		if (info->last_token != T_WORD)
			return (false);
	}
	else if (is_redirect_operator(token_type))
	{
		if (is_redirect_operator(info->last_token))
			return (false);
	}
	return (true);
}

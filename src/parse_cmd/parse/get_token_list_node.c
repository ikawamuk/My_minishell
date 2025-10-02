/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_list_node.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:58:46 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/17 23:00:52 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "parse.h"
#include "parse_utils.h"
#include "token.h"
#include "libft.h"

int			vaidated_lex(t_token *token, t_parse_info *info);
static int	get_redirect_word(t_token *valid_token, t_parse_info *info);
static int	error_get_valid_token(int result, t_token tmp_token);
static bool	is_command_terminator(t_token_type type);

int	get_token_list_node(t_token *valid_token, t_parse_info *info)
{
	int		result;
	t_token	tmp_token;

	ft_bzero(valid_token, sizeof(*valid_token));
	result = vaidated_lex(&tmp_token, info);
	if (is_parse_error(result))
		return (error_get_valid_token(result, tmp_token));
	if (is_command_terminator(tmp_token.type))
		return (PARSE_CMD_FINISH);
	if (is_redirect_operator(tmp_token.type))
	{
		valid_token->type = tmp_token.type;
		return (get_redirect_word(valid_token, info));
	}
	if (tmp_token.type == T_WORD)
		*valid_token = tmp_token;
	return (PARSE_NO_ERROR);
}

static int	error_get_valid_token(int result, t_token tmp_token)
{
	free(tmp_token.word);
	return (result);
}

static int	get_redirect_word(t_token *valid_token, t_parse_info *info)
{
	int		result;
	t_token	tmp_token;

	result = vaidated_lex(&tmp_token, info);
	if (is_parse_error(result))
		return (error_get_valid_token(result, tmp_token));
	else if (tmp_token.type != T_WORD)
	{
		free(tmp_token.word);
		return (PARSE_SYNTAX_ERROR);
	}
	valid_token->word = tmp_token.word;
	return (PARSE_NO_ERROR);
}

static bool	is_command_terminator(t_token_type type)
{
	return (is_command_connector(type) || type == T_NULL);
}

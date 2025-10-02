/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:31:53 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/20 04:53:26 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "token.h"
#include "parse.h"
#include "libft.h"

bool	is_parse_error(int result)
{
	return (result == PARSE_FATAL_ERROR || result == PARSE_SYNTAX_ERROR);
}

bool	is_env_var(char *str)
{
	if (str[0] != '$')
		return (false);
	if (ft_isalpha(str[1]) || str[1] == '?' || str[1] == '_')
		return (true);
	return (false);
}

bool	is_command_connector(t_token_type type)
{
	if (type == T_BAR)
		return (true);
	if (type == T_BAR_BAR)
		return (true);
	if (type == T_AND_AND)
		return (true);
	return (false);
}

bool	is_redirect_operator(t_token_type type)
{
	if (type == T_GREATER)
		return (true);
	if (type == T_GREATER_GREATER)
		return (true);
	if (type == T_LESS)
		return (true);
	if (type == T_LESS_LESS)
		return (true);
	return (false);
}

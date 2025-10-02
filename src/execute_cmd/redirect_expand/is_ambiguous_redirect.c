/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_ambiguous_redirect.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:29:25 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/24 21:10:04 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "redirection.h"
#include "utils.h"

static bool	include_multi_word(char *string);
static bool	is_null_str(char *string);

bool	is_ambiguous_redirect(t_redir_list *redir_list)
{
	while (redir_list)
	{
		if (redir_list->data.type != R_HEREDOC)
		{
			if (is_null_str(redir_list->data.value.file_name))
				return (true);
			if (include_multi_word(redir_list->data.value.file_name))
				return (true);
		}
		redir_list = redir_list->next;
	}
	return (false);
}

static bool	include_multi_word(char *string)
{
	while (is_space(*string))
		string++;
	while (*string && !is_space(*string))
		string++;
	while (is_space(*string))
		string++;
	if (*string)
		return (true);
	return (false);
}

static bool	is_null_str(char *string)
{
	while (is_space(*string))
		string++;
	return (!*string);
}

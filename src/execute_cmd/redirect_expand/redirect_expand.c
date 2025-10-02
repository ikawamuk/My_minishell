/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:48:05 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/24 21:09:24 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "define.h"
#include "shell.h"
#include "command.h"
#include "exec.h"
#include "utils.h"

static int	expand_redir_list(t_redir_list *list, t_shell *shell);
static int	expand_redir_data(t_redir *redir, t_shell *shell);
void		quote_string(char *str);
int			expand_string(char *str, char **result_p, t_shell *shell);
int			dequote_string(char **str_p);

int	redirect_expand(t_redir_list *list, t_shell *shell)
{
	if (expand_redir_list(list, shell) != NO_ERROR)
	{
		free_redir_list(list);
		return (FATAL_ERROR);
	}
	return (NO_ERROR);
}

static int	expand_redir_list(t_redir_list *list, t_shell *shell)
{
	while (list)
	{
		if (list->data.type != R_HEREDOC)
			if (expand_redir_data(&list->data, shell) != NO_ERROR)
				return (FATAL_ERROR);
		list = list->next;
	}
	return (NO_ERROR);
}

static int	expand_redir_data(t_redir *redir, t_shell *shell)
{
	char	*result;

	quote_string(redir->value.file_name);
	if (expand_string(redir->value.file_name, &result, shell) != NO_ERROR)
		return (FATAL_ERROR);
	free(redir->value.file_name);
	redir->value.file_name = result;
	if (dequote_string(&redir->value.file_name) != NO_ERROR)
		return (FATAL_ERROR);
	return (NO_ERROR);
}

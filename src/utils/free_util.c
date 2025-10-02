/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokurita <kokurita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 22:50:53 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/29 21:41:39 by kokurita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "command.h"

void	*free_str_arr(char **str_arr)
{
	size_t	i;

	if (!str_arr)
		return (NULL);
	i = 0;
	while (str_arr[i])
		free(str_arr[i++]);
	free(str_arr);
	return (NULL);
}

void	*free_token_list(t_token_list *list)
{
	t_token_list	*next;

	while (list)
	{
		free(list->data.word);
		next = list->next;
		free(list);
		list = next;
	}
	return (NULL);
}

void	*free_redir_list(t_redir_list *list)
{
	t_redir_list	*next;

	while (list)
	{
		if (list->data.type != R_HEREDOC)
			free(list->data.value.file_name);
		else
			free(list->data.value.heredoc.eof);
		next = list->next;
		free(list);
		list = next;
	}
	return (NULL);
}

void	free_command(t_simple_cmd cmd)
{
	if (cmd.argv)
		cmd.argv = free_str_arr(cmd.argv);
	if (cmd.redir_list)
		cmd.redir_list = free_redir_list(cmd.redir_list);
	return ;
}

void	*free_command_list(t_cmd_list *list)
{
	t_cmd_list	*next;

	while (list)
	{
		free_command(list->cmd);
		next = list->next;
		free(list);
		list = next;
	}
	return (NULL);
}

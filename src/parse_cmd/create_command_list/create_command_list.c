/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 22:39:33 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/23 13:00:36 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "define.h"
#include "command.h"
#include "element.h"
#include "parse_utils.h"
#include "utils.h"
#include "libft.h"

static int	create_loop(t_cmd_list **cmd_list, t_element_list *element_list);
int			make_command(t_simple_cmd *cmd, t_element *element);
static int	append_command(t_cmd_list **cmd_list_p, t_simple_cmd cmd);
static void	push_command(t_cmd_list **list_p, t_cmd_list *new);

int	create_command_list(t_cmd_list **cmd_list, t_element_list *element_list)
{
	if (create_loop(cmd_list, element_list) != NO_ERROR)
	{
		free_command_list(*cmd_list);
		free_element_list(element_list);
		return (FATAL_ERROR);
	}
	free_element_list(element_list);
	return (NO_ERROR);
}

static int	create_loop(t_cmd_list **cmd_list, t_element_list *element_list)
{
	t_element_list	*next;
	t_simple_cmd	cmd;

	*cmd_list = NULL;
	while (element_list)
	{
		next = element_list->next;
		ft_bzero(&cmd, sizeof(cmd));
		if (make_command(&cmd, &element_list->data) != NO_ERROR)
			return (FATAL_ERROR);
		if (append_command(cmd_list, cmd) != NO_ERROR)
			return (FATAL_ERROR);
		element_list = next;
	}
	return (NO_ERROR);
}

static int	append_command(t_cmd_list **cmd_list_p, t_simple_cmd cmd)
{
	t_cmd_list	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (FATAL_ERROR);
	new->next = NULL;
	new->cmd = cmd;
	push_command(cmd_list_p, new);
	return (NO_ERROR);
}

static void	push_command(t_cmd_list **list_p, t_cmd_list *new)
{
	t_cmd_list	*tail;

	if (!*list_p)
		*list_p = new;
	else
	{
		tail = *list_p;
		while (tail->next)
			tail = tail->next;
		tail->next = new;
	}
	return ;
}

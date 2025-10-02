/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:31:53 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/23 16:47:54 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "define.h"
#include "command.h"
#include "libft.h"

static size_t	count_token_list_node(t_token_list *list);

int	create_argv(t_simple_cmd *cmd, t_token_list *list)
{
	t_token_list	*next;
	size_t			len;
	size_t			i;

	if (!list)
		return (NO_ERROR);
	len = count_token_list_node(list);
	cmd->argv = ft_calloc(len + 1, sizeof(char *));
	if (!cmd->argv)
		return (FATAL_ERROR);
	i = 0;
	while (i < len)
	{
		next = list->next;
		cmd->argv[i] = ft_strdup(list->data.word);
		if (!cmd->argv[i])
			return (FATAL_ERROR);
		list = next;
		i++;
	}
	return (NO_ERROR);
}

static size_t	count_token_list_node(t_token_list *list)
{
	size_t	count;

	count = 0;
	while (list)
	{
		list = list->next;
		count++;
	}
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redir_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokurita <kokurita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:34:46 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/29 16:57:59 by kokurita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "define.h"
#include "command.h"
#include "libft.h"

static int	make_new_redir_data(t_token *token, t_redir *new_data_p);
static int	append_redir_data(t_redir_list **list_p, t_redir new_data);
static int	assign_redir_type(t_token_type type);

int	create_redir_list(t_simple_cmd *cmd, t_token_list *rword_list)
{
	t_redir	new_data;

	while (rword_list)
	{
		if (make_new_redir_data(&rword_list->data, &new_data) != NO_ERROR)
			return (FATAL_ERROR);
		if (append_redir_data(&cmd->redir_list, new_data) != NO_ERROR)
			return (FATAL_ERROR);
		rword_list = rword_list->next;
	}
	return (NO_ERROR);
}

static int	make_new_redir_data(t_token *token, t_redir *new_data_p)
{
	new_data_p->type = assign_redir_type(token->type);
	if (new_data_p->type != R_HEREDOC)
	{
		new_data_p->value.file_name = token->word;
		token->word = NULL;
	}
	else
	{
		new_data_p->value.heredoc.eof = token->word;
		token->word = NULL;
	}
	return (NO_ERROR);
}

static int	assign_redir_type(t_token_type type)
{
	if (type == T_LESS)
		return (R_IN);
	if (type == T_GREATER)
		return (R_OUT);
	if (type == T_LESS_LESS)
		return (R_HEREDOC);
	if (type == T_GREATER_GREATER)
		return (R_APPEND);
	return (FATAL_ERROR);
}

static int	append_redir_data(t_redir_list **list_p, t_redir new_data)
{
	t_redir_list	*new;
	t_redir_list	*tail;

	new = ft_calloc(1, sizeof(*new));
	if (!new)
		return (FATAL_ERROR);
	new->next = NULL;
	new->data = new_data;
	if (!*list_p)
		*list_p = new;
	else
	{
		tail = *list_p;
		while (tail->next)
			tail = tail->next;
		tail->next = new;
	}
	return (NO_ERROR);
}

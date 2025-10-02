/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 21:37:28 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/23 17:35:22 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "define.h"
#include "parse_utils.h"
#include "element.h"

static int	shell_expand_element_list(t_element_list *list, t_shell *shell);
void		quote_token_list(t_token_list *list);
int			expand_token_list(t_token_list *list, t_shell *shell);
int			split_token_list(t_token_list **list_p);
int			dequote_token_list(t_token_list *list);

int	shell_expand(t_element_list *element_list, t_shell *shell)
{
	if (shell_expand_element_list(element_list, shell) != NO_ERROR)
	{
		free_element_list(element_list);
		return (FATAL_ERROR);
	}
	return (NO_ERROR);
}

static int	shell_expand_element_list(t_element_list *list, t_shell *shell)
{
	while (list)
	{
		quote_token_list(list->data.word_list);
		if (expand_token_list(list->data.word_list, shell) != NO_ERROR)
			return (FATAL_ERROR);
		if (split_token_list(&list->data.word_list) != NO_ERROR)
			return (FATAL_ERROR);
		if (dequote_token_list(list->data.word_list) != NO_ERROR)
			return (FATAL_ERROR);
		list = list->next;
	}
	return (NO_ERROR);
}

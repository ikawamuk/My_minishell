/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 22:18:19 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/18 22:18:42 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	push_token(t_token_list **list_p, t_token_list *new)
{
	t_token_list	*tail;

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

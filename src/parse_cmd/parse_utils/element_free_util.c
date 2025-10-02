/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:39:24 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/19 23:55:44 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "element.h"
#include "parse_utils.h"

void	free_element(t_element element)
{
	element.word_list = free_token_list(element.word_list);
	element.rword_list = free_token_list(element.rword_list);
	return ;
}

void	*free_element_list(t_element_list *list)
{
	t_element_list	*next;

	while (list)
	{
		next = list->next;
		free_element(list->data);
		free(list);
		list = next;
	}
	return (NULL);
}

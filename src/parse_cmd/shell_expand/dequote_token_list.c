/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequote_token_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 22:10:55 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/23 14:25:46 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "define.h"
#include "token.h"
#include "libft.h"
#include "parse_utils.h"

int	dequote_string(char **str_p);

int	dequote_token_list(t_token_list *list)
{
	while (list)
	{
		if (dequote_string(&list->data.word) != NO_ERROR)
			return (FATAL_ERROR);
		list = list->next;
	}
	return (NO_ERROR);
}

int	dequote_string(char **str_p)
{
	char	*str;
	char	*new_str;

	str = *str_p;
	new_str = ft_strdup("");
	if (!new_str)
		return (FATAL_ERROR);
	while (*str)
	{
		if (!is_quote_marker(*str))
		{
			if (append_char(&new_str, *str) != NO_ERROR)
				return (FATAL_ERROR);
		}
		str++;
	}
	free(*str_p);
	*str_p = new_str;
	return (NO_ERROR);
}

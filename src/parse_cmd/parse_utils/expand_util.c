/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 13:41:14 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/24 21:08:03 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include <stdlib.h>
#include "libft.h"
#include "parse_utils.h"

int	append_char(char **str_p, char c)
{
	char	*new_str;
	size_t	len;

	len = ft_strlen((*str_p)) + 1;
	new_str = ft_calloc(sizeof(char), len + 1);
	if (!new_str)
		return (FATAL_ERROR);
	ft_strlcpy(new_str, *str_p, len + 1);
	new_str[len - 1] = c;
	free(*str_p);
	*str_p = new_str;
	return (NO_ERROR);
}

bool	has_next_word(char *str, size_t i)
{
	while (is_space(str[i]))
		i++;
	if (!str[i])
		return (false);
	return (true);
}

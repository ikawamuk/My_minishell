/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 20:19:57 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/10/02 20:22:58 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*result;

	result = ft_calloc(n + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s, n + 1);
	return (result);
}

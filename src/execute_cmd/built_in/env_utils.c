/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:21:57 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/20 05:19:00 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "libft.h"

bool	match_key(char *env, char *key, size_t key_len)
{
	if (ft_strncmp(env, key, key_len) != 0)
		return (false);
	if (env[key_len] == '=' || env[key_len] == '\0')
		return (true);
	return (false);
}

bool	is_valid_key(const char *key)
{
	if (!key || !*key || !(ft_isalpha(*key) || *key == '_'))
		return (false);
	while (*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (false);
		key++;
	}
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_trimed_host_name.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 20:03:29 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/10/02 20:33:20 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "define.h"
#include "shell.h"
#include "utils.h"
#include "libft.h"

int			get_var_value(char *name, char **value_p, t_shell *shell);
int			safe_strdup(char *src, char **dst_p);
static int	trim_upto_the_first_dot(char *host_name, char **value_p);

int	get_trimed_host_name(char **value_p, t_shell *shell)
{
	int		result;
	char	*host_name;

	if (get_var_value(ft_strdup(ENVNAME_HOSTNAME), &host_name, shell))
		return (FATAL_ERROR);
	if (!host_name)
		return (safe_strdup("", value_p));
	result = trim_upto_the_first_dot(host_name, value_p);
	free(host_name);
	return (result);
}

static int	trim_upto_the_first_dot(char *host_name, char **value_p)
{
	char	*host;
	size_t	len;

	len = 0;
	while (host_name[len] && host_name[len] != '.')
		len++;
	host = ft_strndup(host_name, len);
	if (!host_name)
		return (FATAL_ERROR);
	*value_p = host;
	return (NO_ERROR);
}

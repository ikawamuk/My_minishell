/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:53:03 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/30 22:48:52 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "define.h"
#include "shell.h"
#include "libft.h"
#include "parse_utils.h"

static int	get_var(char *str, size_t *ip, char **value_p, t_shell *shell);
static int	get_var_name(char *str, size_t *ip, char **name_p);
int			get_var_value(char *name, char **value_p, t_shell *shell);
int			append_str(char **str1_p, char *str2);

int	expand_var(char *str, size_t *ip, char **result_p, t_shell *shell)
{
	char	*env_value;

	env_value = NULL;
	if (get_var(str, ip, &env_value, shell) != NO_ERROR)
		return (FATAL_ERROR);
	if (append_str(result_p, env_value) != NO_ERROR)
		return (FATAL_ERROR);
	return (NO_ERROR);
}

static int	get_var(char *str, size_t *ip, char **value_p, t_shell *shell)
{
	char	*var_name;

	var_name = ft_strdup("");
	if (!var_name)
		return (FATAL_ERROR);
	if (get_var_name(str, ip, &var_name) != NO_ERROR)
		return (FATAL_ERROR);
	if (get_var_value(var_name, value_p, shell) != NO_ERROR)
		return (FATAL_ERROR);
	return (NO_ERROR);
}

static int	get_var_name(char *str, size_t *ip, char **name_p)
{
	(*ip)++;
	if (str[*ip] == '?')
		return (append_char(name_p, str[(*ip)++]));
	if (append_char(name_p, str[(*ip)++]) != NO_ERROR)
		return (FATAL_ERROR);
	while (ft_isalnum(str[*ip]) || str[*ip] == '_')
	{
		if (append_char(name_p, str[(*ip)++]) != NO_ERROR)
		{
			free(*name_p);
			return (FATAL_ERROR);
		}
	}
	return (NO_ERROR);
}

int	append_str(char **str1_p, char *str2)
{
	char	*new_str;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(*str1_p);
	len2 = ft_strlen(str2);
	new_str = ft_calloc(sizeof(char), len1 + len2 + 1);
	if (!new_str)
	{
		free(str2);
		return (FATAL_ERROR);
	}
	ft_strlcpy(new_str, (const char *)*str1_p, len1 + 1);
	ft_strlcpy(new_str + len1, (const char *)str2, len2 + 1);
	free(*str1_p);
	free(str2);
	*str1_p = new_str;
	return (NO_ERROR);
}

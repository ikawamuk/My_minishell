/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_format_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:20:09 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/10/02 20:33:04 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "shell.h"
#include "utils.h"
#include "exec_util.h"
#include "libft.h"

int	get_var_value(char *name, char **value_p, t_shell *shell);
int	get_trimed_pwd(char **value_p, t_shell *shell);
int	get_trimed_host_name(char **value_p, t_shell *shell);
int	safe_strdup(char *src, char **dst_p);

int	get_format_value(char c, char **value_p, t_shell *shell)
{
	char	*uid;

	if (c == 'w')
		return (get_trimed_pwd(value_p, shell));
	if (c == 'n')
		return (safe_strdup("\n", value_p));
	if (c == 'u')
		return (get_var_value(ft_strdup(ENVNAME_USER), value_p, shell));
	if (c == 's')
		return (safe_strdup("minishell", value_p));
	if (c == 'h')
		return (get_trimed_host_name(value_p, shell));
	if (c == '$')
	{
		uid = ft_getenv(ENVNAME_UID, shell->envp);
		if (uid && !ft_strcmp("0", uid))
			return (safe_strdup("#", value_p));
		return (safe_strdup("$", value_p));
	}
	if (c == '\\')
		return (safe_strdup("\\", value_p));
	return (NO_ERROR);
}

int	safe_strdup(char *src, char **dst_p)
{
	*dst_p = ft_strdup(src);
	if (!*dst_p)
		return (FATAL_ERROR);
	return (NO_ERROR);
}

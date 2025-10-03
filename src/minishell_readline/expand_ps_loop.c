/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ps_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 22:39:01 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/10/02 20:32:35 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include "define.h"
#include "shell.h"
#include "libft.h"
#include "utils.h"
#include "exec_util.h"

static bool	is_to_expand(char *str);
int			append_str(char **str1_p, char *str2);
int			error_expand_string(char **result_p);
static int	expand_format(char c, char **prompt_p, t_shell *shell);
int			get_format_value(char c, char **prompt_p, t_shell *shell);

int	expand_ps_loop(char *ps, char **prompt_p, t_shell *shell)
{
	size_t	i;

	i = 0;
	while (ps[i])
	{
		if (is_to_expand(ps + i))
		{
			i++;
			if (expand_format(ps[i], prompt_p, shell) != NO_ERROR)
				return (error_expand_string(prompt_p));
			i++;
		}
		else
			if (append_char(prompt_p, ps[i++]) != NO_ERROR)
				return (error_expand_string(prompt_p));
	}
	return (NO_ERROR);
}

static int	expand_format(char c, char **prompt_p, t_shell *shell)
{
	char	*env_value;

	if (get_format_value(c, &env_value, shell) != NO_ERROR)
		return (FATAL_ERROR);
	if (append_str(prompt_p, env_value) != NO_ERROR)
		return (FATAL_ERROR);
	return (NO_ERROR);
}

static bool	is_to_expand(char *str)
{
	if (str[0] != '\\')
		return (false);
	if (!ft_strchr("wnush$\\", str[1]))
		return (false);
	return (true);
}

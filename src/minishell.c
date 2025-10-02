/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokurita <kokurita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:17:12 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/30 20:35:37 by kokurita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "shell.h"
#include "utils.h"
#include "libft.h"

static void	init_minishell(t_shell *shell, char **envp);
static char	**str_arr_dup(char **str_arr);
static void	clean_minishell(t_shell shell);
void		reader_loop(t_shell *shell);

int	minishell(char **envp)
{
	t_shell	shell;

	init_minishell(&shell, envp);
	reader_loop(&shell);
	clean_minishell(shell);
	return (shell.last_status);
}

static void	init_minishell(t_shell *shell, char **envp)
{
	shell->last_status = EXIT_SUCCESS;
	shell->cmd_list = NULL;
	shell->envp = str_arr_dup(envp);
	if (!shell->envp)
		perror("minishell");
	return ;
}

static char	**str_arr_dup(char **str_arr)
{
	char	**result;
	size_t	i;

	if (!str_arr)
		return (NULL);
	i = 0;
	while (str_arr[i])
		i++;
	result = ft_calloc(i + 1, sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (str_arr[i])
	{
		result[i] = ft_strdup(str_arr[i]);
		if (!result[i])
			return (free_str_arr(result));
		i++;
	}
	return (result);
}

static void	clean_minishell(t_shell shell)
{
	shell.envp = free_str_arr(shell.envp);
	return ;
}

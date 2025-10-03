/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_readline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 22:16:57 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/10/02 20:32:13 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdbool.h>
#include <unistd.h>
#include "define.h"
#include "shell.h"
#include "libft.h"
#include "exec_util.h"
#include "utils.h"

static char	*expand_ps(char *ps, t_shell *shell);
int			expand_ps_loop(char *ps, char **prompt_p, t_shell *shell);

char	*minishell_readline(char *prompt, t_shell *shell)
{
	char	*result;
	char	*ps;

	ps = NULL;
	if (ft_strcmp(prompt, PS1) == 0)
		ps = ft_getenv(ENVNAME_PS1, shell->envp);
	if (ft_strcmp(prompt, PS2) == 0)
		ps = ft_getenv(ENVNAME_PS2, shell->envp);
	if (!ps)
		return (readline(prompt));
	prompt = expand_ps(ps, shell);
	if (!prompt)
		return (readline(""));
	result = readline(prompt);
	free(prompt);
	return (result);
}

static char	*expand_ps(char *ps, t_shell *shell)
{
	char	*prompt;

	prompt = ft_strdup("");
	if (!prompt)
		return (NULL);
	if (expand_ps_loop(ps, &prompt, shell) != NO_ERROR)
		return (NULL);
	return (prompt);
}

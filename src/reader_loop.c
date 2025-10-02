/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:25:03 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/10/01 19:45:58 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <readline/readline.h>
#include <signal.h>
#include "define.h"
#include "shell.h"
#include "libft.h"

#include "sig.h"

void		set_signal_handler(t_shell *shell);
int			read_command(char *str, t_shell *shell);
static int	syntax_error(void);
int			do_heredoc(t_shell *shell);
void		exec_command(t_shell *shell);
static void	recieved_signal(t_shell *shell, char *str);
char		*minishell_readline(char *prompt, t_shell *shell);

void	reader_loop(t_shell *shell)
{
	char	*str;

	while (1)
	{
		set_signal_handler(shell);
		str = minishell_readline(PS1, shell);
		if (g_sig == SIGINT)
			recieved_signal(shell, str);
		else if (!str)
			break ;
		else if (!*str)
			free(str);
		else if (read_command(str, shell) == SYNTAX_ERROR)
			shell->last_status = syntax_error();
		else if (do_heredoc(shell) != SIG_INTERRUPTED)
			exec_command(shell);
	}
	ft_putstr_fd(EXIT_MESSAGE, STDERR_FILENO);
}

static void	recieved_signal(t_shell *shell, char *str)
{
	g_sig = -1;
	shell->last_status = 0x80 + SIGINT;
	free(str);
	return ;
}

static int	syntax_error(void)
{
	ft_putstr_fd(SYNTAX_ERROR_MESSAGE, STDERR_FILENO);
	return (EXIT_SYNTAX_ERROR);
}

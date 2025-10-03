/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 21:54:58 by kokurita          #+#    #+#             */
/*   Updated: 2025/10/03 09:52:41 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <readline/readline.h>
#include "define.h"
#include "libft.h"
#include "sig.h"
#include "shell.h"
#include "exec_util.h"

static char	*expand_line(char *line, t_shell *shell, int is_quoted);
static int	clean_heredoc(char *line, int write_fd, int result);
static int	sig_interrupted(char *line, int write_fd);
int			expand_string(char *str, char **result_p, t_shell *shell);
char		*minishell_readline(char *prompt, t_shell *shell);

int	heredoc_loop(char *eof, int write_fd, t_shell *shell, int quoted)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = minishell_readline(PS2, shell);
		if (g_sig == SIGINT)
			return (sig_interrupted(line, write_fd));
		if (!line)
		{
			ft_putstr_fd(HEREDOC_WANTED_EOF, STDERR_FILENO);
			return (clean_heredoc(line, write_fd, NO_ERROR));
		}
		if (!ft_strcmp(line, eof))
			return (clean_heredoc(line, write_fd, NO_ERROR));
		line = expand_line(line, shell, quoted);
		if (!line)
			return (clean_heredoc(line, write_fd, FATAL_ERROR));
		ft_putendl_fd(line, write_fd);
		free(line);
	}
	return (NO_ERROR);
}

static char	*expand_line(char *line, t_shell *shell, int is_quoted)
{
	char	*expanded_line;

	if (is_quoted)
		return (line);
	expanded_line = NULL;
	expand_string(line, &expanded_line, shell);
	free(line);
	return (expanded_line);
}

static int	sig_interrupted(char *line, int write_fd)
{
	g_sig = -1;
	return (clean_heredoc(line, write_fd, SIG_INTERRUPTED));
}

static int	clean_heredoc(char *line, int write_fd, int result)
{
	free(line);
	close(write_fd);
	return (result);
}

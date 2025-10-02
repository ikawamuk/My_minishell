/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_herdoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokurita <kokurita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:30:23 by kokurita          #+#    #+#             */
/*   Updated: 2025/09/30 21:55:19 by kokurita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "define.h"
#include "shell.h"
#include "libft.h"

int			heredoc_loop(char *eof, int write_fd, t_shell *shell, int quoted);
static bool	is_quoted(char *str);
bool		is_quote(char c);
void		quote_string(char *str);
int			dequote_string(char **str_p);

int	write_heredoc(char *eof, int write_fd, t_shell *shell)
{
	int		result;
	int		quoted;
	char	*eof_copy;

	eof_copy = ft_strdup(eof);
	if (!eof_copy)
		return (FATAL_ERROR);
	quoted = is_quoted(eof_copy);
	if (quoted)
	{
		quote_string(eof_copy);
		if (dequote_string(&eof_copy) != NO_ERROR)
			return (FATAL_ERROR);
	}
	result = heredoc_loop(eof_copy, write_fd, shell, quoted);
	free(eof_copy);
	return (result);
}

static bool	is_quoted(char *str)
{
	while (*str)
		if (is_quote(*str++))
			return (true);
	return (false);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 00:23:43 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/27 20:19:09 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "token.h"

# define PERM_MASK	0644

typedef struct s_redir_list	t_redir_list;
typedef struct s_redir		t_redir;

enum e_redir_type
{
	R_IN = T_LESS,
	R_OUT = T_GREATER,
	R_HEREDOC = T_LESS_LESS,
	R_APPEND = T_GREATER_GREATER
};

typedef struct s_heredoc
{
	char	*eof;
	int		pipefd;
}	t_heredoc;

union u_redir_value
{
	char		*file_name;
	t_heredoc	heredoc;
};

struct s_redir
{
	enum e_redir_type	type;
	union u_redir_value	value;
};

struct s_redir_list
{
	t_redir			data;
	t_redir_list	*next;
};

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:09:23 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/25 19:49:34 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <sys/types.h>
# include "command.h"

typedef struct s_exec
{
	t_cmd_list	*cmd_list;
	char		**envp;
	int			next_pipe_read;
	int			last_status;
}	t_exec;

typedef struct s_cmd_info
{
	pid_t			pid;
	int				in;
	int				out;
	char			**cleaned_envp;
	char			**paths_arr;
	t_cmd_list		*cmd_node;
	char			*cmd_path;
}	t_cmd_info;

#endif
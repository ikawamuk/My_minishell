/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:46:52 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/23 13:29:52 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "redirection.h"

typedef struct s_command		t_cmd_list;
typedef struct s_simple_cmd		t_simple_cmd;

struct s_simple_cmd
{
	char			**argv;
	t_redir_list	*redir_list;
};

struct s_command
{
	t_simple_cmd	cmd;
	t_cmd_list		*next;
};

#endif
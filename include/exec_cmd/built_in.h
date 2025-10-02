/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 11:37:46 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/24 23:39:06 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "shell.h"

# define ECHO_CMD		"echo"
# define CD_CMD			"cd"
# define PWD_CMD		"pwd"
# define EXPORT_CMD		"export"
# define UNSET_CMD		"unset"
# define ENVNAME_CMD	"env"
# define EXIT_CMD		"exit"

int	exec_echo(char **argv);
int	exec_cd(char **argv, t_shell *shell);
int	exec_pwd(void);
int	exec_export(char **argv, t_shell *shell);
int	exec_unset(char **argv, t_shell *shell);
int	exec_env(char **argv, t_shell *shell);
int	exec_exit(char **argv, t_shell *shell);

#endif
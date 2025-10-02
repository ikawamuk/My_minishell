/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 10:42:18 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/10/02 20:28:06 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

// exit status
# define EXIT_SUCCESS			0
# define EXIT_FAILURE			1
# define EXIT_SYNTAX_ERROR		2
# define EXIT_PERMISSION_DENIED	126
# define EXIT_COMMAND_NOT_FOUND	127

// intenal status
# define NO_ERROR			0
# define FATAL_ERROR		-1
# define SYNTAX_ERROR		-2
# define REDIRECT_FAILED	-3
# define SIG_INTERRUPTED	-4

// prompt
# define PS1	"$ "
# define PS2	"> "

// environment valiable name
# define ENVNAME_HOME		"HOME"
# define ENVNAME_USER		"USER"
# define ENVNAME_PWD		"PWD"
# define ENVNAME_OLDPWD		"OLDPWD"
# define ENVNAME_PATH		"PATH"
# define ENVNAME_PS1		"PS1"
# define ENVNAME_PS2		"PS2"
# define ENVNAME_HOSTNAME	"HOSTNAME"
# define ENVNAME_UID		"UID"

// message
# define EXIT_MESSAGE			"exit\n"
# define SYNTAX_ERROR_MESSAGE	"minishell: syntax error\n"
# define AMBIG_REDIR_MESSAGE	"minishell: ambiguous redirect\n"
# define CD_TOO_MANY_ARG		"minishell: cd: too many arguments\n"
# define CD_HOME_NOT_SET		"minishell: cd: HOME not set\n"
# define ENV_TOO_MANY_ARG		"minishell: env: too many arguments\n"
# define EXIT_NOT_NUMERIC_ARG	"minishell: exit: numeric argument required\n"
# define EXIT_TOO_MANY_ARG		"minishell: exit: too many arguments\n"
# define NO_SUCH_FILE_MESSAGE	"No such file or directory\n"
# define PERM_DENIED_MESSAGE	"Permission denied\n"
# define IS_A_DIR_MESSAGE		"is a directory\n"
# define CMD_NOT_FOUND_MESSAGE	"command not found\n"
# define HEREDOC_WANTED_EOF		"minishell: warning: here-document \
delimited by end-of-file\n"

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:34:36 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/10/01 19:51:27 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_UTIL_H
# define EXEC_UTIL_H

# include "exec.h"
# include "shell.h"
# include <stdbool.h>

int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin_sep(char *str1, char *str2, char *sep);
bool	match_key(char *env, char *key, size_t key_len);
int		update_env_var(t_shell *shell, char *key, char *value);
int		delete_env_var(t_shell *shell, char *key);
bool	is_valid_key(const char *key);
bool	is_built_in(char *cmd);
int		append_char(char **str_p, char c);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:56:41 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/10/02 20:22:46 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>
# include <stdlib.h>
# include "command.h"

void	*free_str_arr(char **str_arr);
void	*free_token_list(t_token_list *list);
void	*free_redir_list(t_redir_list *list);
void	free_command(t_simple_cmd cmd);
void	*free_command_list(t_cmd_list *list);
char	*ft_getenv(const char *name, char **envp);
int		count_str_arr(char **arr);
bool	is_space(char c);
void	set_default_sighandler(void);
void	set_ignore_sighandler(void);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strndup(const char *s, size_t n);

#endif
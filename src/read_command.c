/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:36:10 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/18 00:02:33 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <stdlib.h>
#include "shell.h"
#include "define.h"

int	parse_command(char *str, t_cmd_list **cmd_lst, t_shell *shell);

int	read_command(char *str, t_shell *shell)
{
	int	result;

	result = parse_command(str, &shell->cmd_list, shell);
	if (*str)
		add_history(str);
	free(str);
	if (result == FATAL_ERROR)
		perror("minishell");
	return (result);
}

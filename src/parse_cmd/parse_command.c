/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:42:34 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/27 20:02:33 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "define.h"
#include "shell.h"
#include "command.h"
#include "element.h"

int	parse(char *str, t_element_list **element_list);
int	shell_expand(t_element_list *element_list, t_shell *shell);
int	create_command_list(t_cmd_list **cmd_list, t_element_list *element_list);

int	parse_command(char *str, t_cmd_list **cmd_list, t_shell *shell)
{
	int				result;
	t_element_list	*element_list;

	element_list = NULL;
	*cmd_list = NULL;
	result = parse(str, &element_list);
	if (result != NO_ERROR)
		return (result);
	if (shell_expand(element_list, shell) != NO_ERROR)
		return (FATAL_ERROR);
	if (create_command_list(cmd_list, element_list) != NO_ERROR)
		return (FATAL_ERROR);
	return (NO_ERROR);
}

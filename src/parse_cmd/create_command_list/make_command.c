/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 00:22:08 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/23 13:35:07 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "define.h"
#include "command.h"
#include "element.h"
#include "libft.h"

int	create_argv(t_simple_cmd *cmd, t_token_list *list);
int	create_redir_list(t_simple_cmd *cmd, t_token_list *rword_list);

int	make_command(t_simple_cmd *cmd, t_element *element)
{
	if (create_argv(cmd, element->word_list) != NO_ERROR)
		return (FATAL_ERROR);
	if (create_redir_list(cmd, element->rword_list) != NO_ERROR)
		return (FATAL_ERROR);
	return (NO_ERROR);
}

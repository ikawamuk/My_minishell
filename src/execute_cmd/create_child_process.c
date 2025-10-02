/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_child_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:47:01 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/25 21:04:01 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "define.h"
#include "exec.h"

int	create_child_process(t_cmd_info *info)
{
	info->pid = fork();
	if (info->pid == -1)
		return (FATAL_ERROR);
	return (NO_ERROR);
}

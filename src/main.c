/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokurita <kokurita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:15:44 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/29 20:40:25 by kokurita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

volatile sig_atomic_t	g_sig = -1;

int	minishell(char **envp);

int	main(int ac, char *av[], char *envp[])
{
	(void)ac;
	(void)av;
	return (minishell(envp));
}

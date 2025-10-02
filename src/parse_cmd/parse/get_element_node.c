/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_element_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokurita <kokurita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:50:07 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/30 20:23:03 by kokurita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parse.h"
#include "parse_utils.h"
#include "element.h"
#include "libft.h"

int			get_token_list_node(t_token *valid_token, t_parse_info *info);
static int	error_get_element(int result, t_token token);
static int	append_token_to_element(t_element *element_p, t_token node);

int	get_element_node(t_element *element_p, t_parse_info *info)
{
	int		result;
	t_token	token;

	while (1)
	{
		ft_bzero(&token, sizeof(token));
		result = get_token_list_node(&token, info);
		if (is_parse_error(result))
			return (error_get_element(result, token));
		if (result == PARSE_CMD_FINISH)
			break ;
		result = append_token_to_element(element_p, token);
		if (result != PARSE_NO_ERROR)
			return (error_get_element(result, token));
	}
	return (PARSE_NO_ERROR);
}

static int	append_token_to_element(t_element *element_p, t_token node)
{
	t_token_list	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (PARSE_FATAL_ERROR);
	new->next = NULL;
	new->data = node;
	if (is_redirect_operator(node.type))
		push_token(&element_p->rword_list, new);
	else
		push_token(&element_p->word_list, new);
	return (PARSE_NO_ERROR);
}

static int	error_get_element(int result, t_token token)
{
	free(token.word);
	return (result);
}

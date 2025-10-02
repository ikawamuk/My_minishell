/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:46:16 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/26 20:02:59 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "element.h"
#include "parse.h"
#include "parse_utils.h"
#include "libft.h"

int			get_element_node(t_element *element, t_parse_info *info);
static void	init_parse_info(char *str, t_parse_info *info);
static int	append_element(t_element_list **element_list_p, t_element node);
static void	push_element(t_element_list **list_p, t_element_list *new);
static int	error_parse(int result, t_element element, t_element_list *list);

int	parse(char *str, t_element_list **element_list_p)
{
	int				result;
	t_parse_info	info;
	t_element		element;

	init_parse_info(str, &info);
	*element_list_p = NULL;
	while (1)
	{
		ft_bzero(&element, sizeof(element));
		result = get_element_node(&element, &info);
		if (result != PARSE_NO_ERROR)
			return (error_parse(result, element, *element_list_p));
		result = append_element(element_list_p, element);
		if (result != PARSE_NO_ERROR)
			return (error_parse(result, element, *element_list_p));
		if (info.last_token == T_NULL)
			break ;
	}
	return (NO_ERROR);
}

static int	append_element(t_element_list **element_list_p, t_element node)
{
	t_element_list	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (PARSE_FATAL_ERROR);
	new->next = NULL;
	new->data = node;
	push_element(element_list_p, new);
	return (PARSE_NO_ERROR);
}

static void	push_element(t_element_list **list_p, t_element_list *new)
{
	t_element_list	*tail;

	if (!*list_p)
		*list_p = new;
	else
	{
		tail = *list_p;
		while (tail->next)
			tail = tail->next;
		tail->next = new;
	}
	return ;
}

static int	error_parse(int result, t_element element, t_element_list *list)
{
	free_element(element);
	free_element_list(list);
	if (result == PARSE_FATAL_ERROR)
		return (FATAL_ERROR);
	if (result == PARSE_SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	return (NO_ERROR);
}

static void	init_parse_info(char *str, t_parse_info *info)
{
	info->str = str;
	info->str_i = 0;
	info->last_token = T_NULL;
	return ;
}

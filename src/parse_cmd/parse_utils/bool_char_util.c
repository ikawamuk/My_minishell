/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_char_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 21:09:55 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/20 06:31:45 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "parse_utils.h"

bool	is_metachar(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

bool	is_quote_marker(char c)
{
	return (c == (char)S_QUOTE_MARKER || c == (char)D_QUOTE_MARKER);
}

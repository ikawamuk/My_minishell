/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:30:49 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/24 21:07:27 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdlib.h>
# include "token.h"

enum e_parse_revturn_value
{
	PARSE_NO_ERROR = 0,
	PARSE_FATAL_ERROR = 1,
	PARSE_SYNTAX_ERROR = 2,
	PARSE_CMD_FINISH = 3
};

# define UNCLOSED_QUOTE	4

typedef struct s_parse_info
{
	const char		*str;
	size_t			str_i;
	t_token_type	last_token;
}	t_parse_info;

#endif
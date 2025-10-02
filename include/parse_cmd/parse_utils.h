/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:40:07 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/23 14:34:36 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_UTILS_H
# define PARSE_UTILS_H

# include <stdbool.h>
# include "utils.h"
# include "element.h"
# include "parse.h"

# define S_QUOTE_MARKER	-1
# define D_QUOTE_MARKER	-2

// free util
void	free_element(t_element element);
void	*free_element_list(t_element_list *list);

// bool util
bool	is_parse_error(int result);
bool	is_env_var(char *str);
bool	is_command_connector(t_token_type type);
bool	is_redirect_operator(t_token_type type);

// bool char util
bool	is_quote(char c);
bool	is_quote_marker(char c);
bool	is_metachar(char c);

// expand util
int		append_char(char **str_p, char c);
bool	has_next_word(char *str, size_t i);

// list util
void	push_token(t_token_list **list_p, t_token_list *new);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:47:30 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/17 20:33:45 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef struct s_token				t_token;
typedef struct s_token_list			t_token_list;

typedef enum e_token_type
{
	T_ERROR = -1,
	// null charactor
	T_NULL = 0,
	// word
	T_WORD = 1,
	// redirect oparator
	T_LESS = 2,
	T_GREATER = 3,
	T_LESS_LESS = 4,
	T_GREATER_GREATER = 5,
	// command connector
	T_BAR = 6,
	T_BAR_BAR = 7,
	T_AND_AND = 8,
}	t_token_type;

struct s_token
{
	t_token_type	type;
	char			*word;
};

struct s_token_list
{
	t_token			data;
	t_token_list	*next;
};

#endif
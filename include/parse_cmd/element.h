/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:35:39 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/17 20:48:46 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENT_H
# define ELEMENT_H

# include "token.h"

typedef struct s_element			t_element;
typedef struct s_element_list		t_element_list;

struct s_element
{
	t_token_list	*word_list;
	t_token_list	*rword_list;
};

struct s_element_list
{
	t_element		data;
	t_element_list	*next;
};

#endif
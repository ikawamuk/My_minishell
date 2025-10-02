/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_str_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 22:02:05 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/19 22:02:07 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	count_str_arr(char **arr)
{
	int	arr_len;

	arr_len = 0;
	while (arr[arr_len])
		arr_len++;
	return (arr_len);
}

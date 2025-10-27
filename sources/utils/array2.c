/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:07:25 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/27 17:14:15 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"
#include "libft.h"

void array_remove(t_array *arr, size_t ind)
{
	size_t const	start = ind * arr->elem_size;
	size_t const	end = (ind + 1) + arr->elem_size;
	size_t const	move_bytes = (arr->size - ind - 1) * arr->elem_size; 

	if (ind >= arr->size)
		return ;
	ft_memmove((char *)arr->data + start, (char *)arr->data + end, move_bytes);
	--arr->size;
}

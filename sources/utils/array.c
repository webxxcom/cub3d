/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 23:54:27 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/18 00:25:34 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"
#include "libft.h"

t_array	array_init(size_t elem_size)
{
	return ((t_array){
		.capacity = 8,
		.size = 0,
		.elem_size = elem_size,
		.data = malloc(8 * elem_size)
	});
}

void	array_push(t_array *arr, void *data)
{
	if (arr->size >= arr->capacity)
	{
		arr->capacity <<= 2;
		arr->data = ft_realloc(arr->data,
				arr->size * arr->elem_size,
				arr->capacity * arr->elem_size);
	}
	ft_memcpy(arr->data + arr->size * arr->elem_size, data, arr->elem_size);
	++arr->size;
}

size_t	array_size(t_array *arr)
{
	return (arr->size);
}

void	*array_get(t_array *arr, size_t idx)
{
	if (idx >= arr->size)
		return (NULL);
	return (arr->data + idx * arr->elem_size);
}

void	array_free(t_array *arr)
{
	free(arr->data);
	arr->data = NULL;
	arr->capacity = 0;
	arr->size = 0;
	arr->elem_size = 0;
}

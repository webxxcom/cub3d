/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 23:51:36 by webxxcom          #+#    #+#             */
/*   Updated: 2026/02/12 08:56:54 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_H
# define ARRAY_H

# include <stddef.h>

# define INIT_ARR_CAPACITY 8

typedef struct s_array
{
	void	*data;
	size_t	size;
	size_t	capacity;
	size_t	elem_size;
}			t_array;

t_array		array_init(size_t elem_size);

void		array_push(t_array *arr, void *data);

size_t		array_size(t_array *arr);

void		*array_get(t_array *arr, size_t idx);

void		array_free(t_array *arr);

void		array_remove(t_array *arr, size_t ind);

#endif
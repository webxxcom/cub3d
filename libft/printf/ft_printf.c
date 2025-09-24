/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:08:45 by phutran           #+#    #+#             */
/*   Updated: 2025/09/24 16:06:21 by phutran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_convert(char specifier, va_list args)
{
	if (specifier == 'c')
		return (ft_print_ch(va_arg(args, int)));
	else if (specifier == 's')
		return (ft_print_str(va_arg(args, const char *)));
	else if (specifier == 'p')
		return (ft_print_ptr(va_arg(args, void *)));
	else if (specifier == 'd')
		return (ft_print_int(va_arg(args, int)));
	else if (specifier == 'i')
		return (ft_print_int(va_arg(args, int)));
	else if (specifier == 'u')
		return (ft_print_uint(va_arg(args, unsigned int)));
	else if (specifier == 'x')
		return (ft_print_hex(va_arg(args, unsigned int), LOWERCASE));
	else if (specifier == 'X')
		return (ft_print_hex(va_arg(args, unsigned int), UPPERCASE));
	else if (specifier == '%')
		return (ft_print_ch('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;

	if (!format)
		return (0);
	len = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
			len += ft_convert(*(++format), args);
		else
			len += ft_print_ch(*format);
		++format;
	}
	va_end(args);
	return (len);
}

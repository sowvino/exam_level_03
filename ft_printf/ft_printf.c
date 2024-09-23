/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-18 14:56:36 by selango           #+#    #+#             */
/*   Updated: 2024-06-18 14:56:36 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
#include <stdio.h>

int	ft_print_char(char c)
{
	return (write(1, &c, 1));
}

int	ft_print_str(char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (ft_print_str("(null)"));
	while (*str)
	{
		ft_print_char(*str);
		count++;
		str++;
	}
	return (count);
}
int	ft_print_digit(long n, int base)
{
	int		count;
	char	*symbols;

	count = 0;
	symbols = "0123456789abcdef";
	if (n < 0)
	{
		write(1, "-", 1);
		return (ft_print_digit(-n, base) + 1);
	}
	else if (n < base)
		return (ft_print_char(symbols[n]));
	else
	{
		count = ft_print_digit(n / base, base);
		return (count + ft_print_digit(n % base, base));
	}
}
int	print_format(char specifier, va_list ap)
{
	int	count;

	count = 0;
	if (specifier == 's')
		count += ft_print_str(va_arg(ap, char *));
	else if (specifier == 'd')
		count += ft_print_digit((long)va_arg(ap, int), 10);
	else if (specifier == 'x')
		count += ft_print_digit((long)va_arg(ap, unsigned int), 16);
	else if (specifier == '%')
		count += ft_print_char('%');
	else
		return (0);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	count = 0;
	va_start(ap, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			count += print_format(*format, ap);
		}
		else
			count += ft_print_char(*format);
		format++;
	}
	va_end(ap);
	return (count);
}

int main()
{
    // Test cases:
    ft_printf("%%d: %d\n", 2147483647);  // Max int
    ft_printf("%%x: %x\n", 0);           // Zero in hex
    ft_printf("%%s: %s\n", NULL);        // NULL string
    ft_printf("%%d: %d\n", -2147483648); // Min int
    ft_printf("Mixed: %d %x %s\n", 42, 42, NULL); // Mixed case with spacing
}

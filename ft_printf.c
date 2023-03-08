/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaiti <jlaiti@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 09:21:14 by jlaiti            #+#    #+#             */
/*   Updated: 2023/03/08 11:12:21 by jlaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_count_number(int n)
{
	int	i;
	int	t;

	i = 0;
	if (n == 0)
		return (1);
	t = n;
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	if (t < 0)
		return (i + 1);
	else
		return (i);
}

void	ft_puthexa(unsigned int hexa)
{
	if (hexa >= 0 && hexa <= 9)
		ft_putchar(hexa + '0');
	else if (hexa >= 10 && hexa <= 15)
		ft_putchar(hexa - 10 + 'a');
	else
	{
		ft_puthexa(hexa / 16);
		ft_puthexa(hexa % 16);
	}	
}

int	ft_count_hexa(unsigned int hexa)
{
	int	i;

	i = 0;
	if (hexa == 0)
		return (1);
	while (hexa != 0)
	{
		i++;
		hexa /= 16;
	}
	return (i);
}

int	ft_hexa(va_list arg)
{
	unsigned int	hexa;

	hexa = va_arg(arg, unsigned int);
	ft_puthexa(hexa);
	return (ft_count_hexa(hexa));
}

void	ft_putnbr(int n)
{
	if (n >= 0 && n <= 9)
		ft_putchar(n + '0');
	else if (n < 0)
	{
		if (n == -2147483648)
			write(1, "-2147483648", 11);
		else
		{
			ft_putchar('-');
			ft_putnbr(n * (-1));
		}
	}
	else
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
}

int	ft_number(va_list arg)
{
	int	n;

	n = va_arg(arg, int);
	ft_putnbr(n);
	return (ft_count_number(n));
}

int	ft_string(va_list arg)
{
	char	*chaine;

	chaine = va_arg(arg, char *);
	if (chaine == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	ft_putstr(chaine);
	return (ft_strlen(chaine));
}

void	check_arg(va_list arg, const char *format, int *len)
{
	if (*format == 'd')
		*len += ft_number(arg);
	else if (*format == 's')
		*len += ft_string(arg);
	else if (*format == 'x')
		*len += ft_hexa(arg);
	else if (*format == '%')
	{
		write(1, "%", 1);
		len += 1;
	}
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		len;
	va_list	arg;

	i = 0;
	len = 0;
	va_start(arg, format);
	while (format[i])
	{
		if (format[i] == '%')
			check_arg(arg, &format[++i], &len);
		else
			len += write(1, &format[i], 1);
		i++;
	}
	va_end(arg);
	return (len);
}
/*
int	main(void)
{
	ft_printf("%s\n", "toto");
	ft_printf("Magic %s is %d", "number", 42);
	ft_printf("Hexadecimal for %d is %x\n", 42, 42);
	return(0);
}
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 00:09:39 by bchafi            #+#    #+#             */
/*   Updated: 2025/03/29 05:15:53 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_putchr(int c)
{
	char	ch;

	ch = (char)c;
	write(1, &ch, 1);
	return (1);
}

int	ft_putstr(const char *str)
{
	int	count;

	count = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (*str)
		count += ft_putchr(*str++);
	return (count);
}

int	ft_putnbr(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
		count++;
	}
	if (n > 9)
		count += ft_putnbr(n / 10);
	ft_putchr((n % 10) + '0');
	return (count + 1);
}

int	ft_hexadecimal(unsigned int num, char buffer)
{
	char	*base;
	char	hex;
	int		count;

	count = 0;
	if (buffer == 'x')
		base = "0123456789abcdef";
	else if (buffer == 'X')
		base = "0123456789ABCDEF";
	if (num == 0)
		return (ft_putchr('0'), 1);
	if (num >= 16)
		count += ft_hexadecimal(num / 16, buffer);
	hex = base[num % 16];
	count += ft_putchr(hex);
	return (count);
}

int	ft_hexa_address(unsigned long num)
{
	char	*base;
	char	hex;
	int		count;

	count = 0;
	base = "0123456789abcdef";
	if (num == 0)
		return (ft_putchr('0'), 1);
	if (num >= 16)
		count += ft_hexa_address(num / 16);
	hex = base[num % 16];
	count += ft_putchr(hex);
	return (count);
}

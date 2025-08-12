/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_function.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 00:13:17 by bchafi            #+#    #+#             */
/*   Updated: 2025/08/12 15:00:51 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isspace(int c)
{
	if (c == '\t' || c == '\r' || c == '\v' || c == '\f' || c == 32)
		return (1);
	return (0);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;
	unsigned char	set;
	size_t			i;

	str = (unsigned char *)b;
	set = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		str[i] = set;
		i++;
	}
	return (b);
}

void	ft_puterror_fd(char *s)
{
	if (!s)
		return ;
	write(2, s, ft_strlen(s));
}

char	*ft_strdup(const char *s1)
{
	int		lens1;
	int		i;
	char	*dup;

	lens1 = ft_strlen(s1);
	i = 0;
	dup = (char *)malloc(lens1 + 1);
	if (!dup)
		return (NULL);
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

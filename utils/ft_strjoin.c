/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bader <bader@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 00:17:25 by bchafi            #+#    #+#             */
/*   Updated: 2025/03/25 01:55:00 by bader            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*con;
	size_t	i;
	size_t	j;

	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && !s2)
		return (NULL);
	con = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!con)
		return (NULL);
	i = -1;
	while (++i < ft_strlen(s1))
		con[i] = s1[i];
	j = -1;
	while (++j < ft_strlen(s2))
		con[i + j] = s2[j];
	con[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	return (con);
}

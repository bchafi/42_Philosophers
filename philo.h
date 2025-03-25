/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bader <bader@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 02:09:29 by bader             #+#    #+#             */
/*   Updated: 2025/03/25 01:56:54 by bader            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <unistd.h>
# include <stdlib.h>

char	**ft_split(char const *s, char c);
void	ft_puterror_fd(char *s);
size_t	ft_strlen(const char *s);
int     ft_isspace(int c);
char    *ft_strjoin(char *s1, char *s2);
int     ft_isdigit(int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);




int     are_valid_argument(char *argv);
void    check_if_numbers(char **args_sp);
char    **parcing(char **argv);


#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 02:09:29 by bader             #+#    #+#             */
/*   Updated: 2025/03/29 05:11:39 by codespace        ###   ########.fr       */
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

# include <stdarg.h>
int     ft_printf(const char *format, ...);
int     ft_putchr(int c);
int     ft_putnbr(int n);
int     ft_putstr(const char *str);
int     ft_hexadecimal(unsigned int num, char buffer);
int     ft_hexa_address(unsigned long num);




int     are_valid_argument(char *argv);
void    check_if_numbers(char **args_sp);
char    **parcing(char **argv);


#endif
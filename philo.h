/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bader <bader@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 02:09:29 by bader             #+#    #+#             */
/*   Updated: 2025/04/08 10:20:33 by bader            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
#include <sys/time.h>

// #define long get_time_in_ms(void);


char	**ft_split(char const *s, char c);
void	ft_puterror_fd(char *s);
size_t	ft_strlen(const char *s);
int     ft_isspace(int c);
char    *ft_strjoin(char *s1, char *s2);
int     ft_isdigit(int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
int     ft_atoi(const char *str);

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


typedef struct philo t_philo;

typedef struct args {
    int num_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int meals_required;
    long start_time;
    int someone_died;                                                                                                                                                                                                                                                                                                                                                                                               
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
    t_philo *philos;
} t_data;

typedef struct philo {
    int id;
    int meals_eaten;
    long last_meal;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_data *data;
} t_philo;



long    get_time_in_ms();
t_data* init_data(t_data *data, char **args);
void    parc_init(int ac, char **av, t_data *d_dataP);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bader <bader@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 02:09:29 by bader             #+#    #+#             */
/*   Updated: 2025/04/09 12:01:00 by bader            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

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


void    free_args_philo(char **args_philo);
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
    pthread_mutex_t meal_lock;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_data *data;
} t_philo;



long    get_time_in_ms();
t_data* init_data(t_data *data, char **args);
t_data* init_philos(t_data *d_dataP);
char**  half_main(int ac, char **av, t_data *d_dataP);
void    free_to_exit(char **av, t_data *data);


// void think(t_philo *philo);
// void take_forks(t_philo *philo);
// void eat(t_philo *philo);
// void put_forks(t_philo *philo);
// void sleep_philo(t_philo *philo);
// void print_action(t_philo *philo, char *msg);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 11:44:55 by bchafi            #+#    #+#             */
/*   Updated: 2025/08/10 12:00:57 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <string.h>
# include <stdio.h>


void	*ft_memset(void *b, int c, size_t len);
// parcing.c
char    **parcing(char **argv);
int     are_valid_argument(char *argv);
int     ft_isspace(int c);
void	ft_puterror_fd(char *s);
size_t	ft_strlen(const char *s);
char    *ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
int     check_if_numbers(char **args_sp);
int     ft_isdigit(int c);

typedef struct philo t_philo;

typedef struct data
{
    int             num_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             meals_required;
    long            start_time;
    int             someone_died;
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
    pthread_mutex_t death_lock;
    t_philo         *philos;
}   t_data;

typedef struct philo
{
    int             id;
    int             meals_eaten;
    long            last_meal;
    pthread_t       thread;
    pthread_mutex_t meal_lock;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_data          *data;
}   t_philo;


t_data  *init_data(t_data *data, char **args);
int     ft_atoi(const char *str);


void    free_args_philo(char **args_philo);
int     free_to_exit(char **av, t_data *data);

// philo.c
t_data  *init_philos(t_data *d_dataP);
char    **initializer(int ac, char **av, t_data *d_dataP);



#endif
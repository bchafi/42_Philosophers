/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 11:44:55 by bchafi            #+#    #+#             */
/*   Updated: 2025/08/12 15:46:39 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <stdio.h>

int		ft_isspace(int c);
void	ft_puterror_fd(char *s);
void	*ft_memset(void *b, int c, size_t len);
char	**parcing(char **argv);
int		are_valid_argument(char *argv);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
int		check_if_numbers(char **args_sp);
int		ft_isdigit(int c);

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	long			start_time;
	int				someone_died;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
	t_philo			*philos;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

long	get_time_in_ms(void);
void	sleep_philo(t_philo *philo);
void	cpu_sleep(long duration_ms, t_philo *philo);

void	print_action(t_philo *philo, char *msg);
void	think(t_philo *philo);
void	take_forks(t_philo *philo);
void	eat(t_philo *philo);
void	put_forks(t_philo *philo);

int		check_monitor_philo(t_data *data, int i, int *all_full);
void	*monitor_routine(void *data_ptr);
void	routine_each_philo(t_philo *philo);
void	*philo_routine(void *arg);

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**initializer(char **av, t_data *d_dataP);
t_data	*init_data(t_data *data, char **args);
long	ft_atoi(const char *str);

void	free_args_philo(char **args_philo);
int		free_to_exit(char **av, t_data *data);

t_data	*init_philos(t_data *d_dataP);

#endif
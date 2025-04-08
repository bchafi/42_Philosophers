/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bader <bader@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 02:11:20 by bader             #+#    #+#             */
/*   Updated: 2025/04/08 10:43:10 by bader            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void think(t_philo *philo);
void take_forks(t_philo *philo);
void eat(t_philo *philo);
void put_forks(t_philo *philo);
void sleep_philo(t_philo *philo);
void print_action(t_philo *philo, char *msg);

void take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, "has taken a fork");
}
void eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_lock);
	philo->last_meal = get_time_in_ms();
	ft_printf("%ld %d is eating\n", philo->last_meal - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print_lock);

	usleep(philo->data->time_to_eat * 1000);
	philo->meals_eaten++;
}
void put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
void sleep_philo(t_philo *philo)
{
	print_action(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}
void think(t_philo *philo)
{
	print_action(philo, "is thinking");
}

void print_action(t_philo *philo, char *msg)
{
	long time = get_time_in_ms() - philo->data->start_time;

	pthread_mutex_lock(&philo->data->print_lock);
	if (!philo->data->someone_died)
		ft_printf("%ld %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_lock);
}

long get_time_in_ms()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

t_data *init_data(t_data *data, char **args)
{
	if (!args)
	{
		free(data);
		data = NULL;
		ft_puterror_fd("Has No Argument !!");
	}
	data->meals_required = -1;
	data->num_philos = ft_atoi(args[0]);
	data->time_to_die = ft_atoi(args[1]);
	data->time_to_eat = ft_atoi(args[2]);
	data->time_to_sleep = ft_atoi(args[3]);
	if (args[4])
		data->meals_required = ft_atoi(args[4]);
	return (data);
}

t_data *init_philos(t_data *d_dataP)
{
	int i;

	i = 0;
	while (i < d_dataP->num_philos)
	{
		d_dataP->philos[i].id = i + 1;
		d_dataP->philos[i].left_fork = &d_dataP->forks[i];
		d_dataP->philos[i].right_fork = &d_dataP->forks[(i + 1) % d_dataP->num_philos];
		d_dataP->philos[i].meals_eaten = 0;
		d_dataP->philos[i].last_meal = get_time_in_ms();
		d_dataP->philos[i++].data = d_dataP;
	}
	return (d_dataP);
}

void half_main(int ac, char **av, t_data *d_dataP)
{
	int i;

	if (ac < 2)
	{
		ft_printf("Argumenta Is Less Then Two Args!!");
		exit(1);
	}
	av = parcing(av);
	d_dataP = init_data(d_dataP, av);
	d_dataP->forks = malloc(sizeof(pthread_mutex_t) * d_dataP->num_philos);
	if (!d_dataP->forks)
	{
		free(d_dataP);
		exit(1);
	}
	i = 0;
	while (i < d_dataP->num_philos)
		pthread_mutex_init(&d_dataP->forks[i++], NULL);
	pthread_mutex_init(&d_dataP->print_lock, NULL);
	d_dataP->philos = malloc(sizeof(t_philo) * d_dataP->num_philos);
	if (!d_dataP->philos)
	{
		free(d_dataP);
		free(d_dataP->forks);
		exit(1);
	}
	d_dataP = init_philos(d_dataP);
}

void *philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	if (philo->id % 2 == 0)
		usleep(1000);

	while (!philo->data->someone_died)
	{
		think(philo);
		// take_forks(philo);
		// eat(philo);
		// put_forks(philo);
		// sleep_philo(philo);
	}
	return NULL;
}

#include <stdio.h>  // Use standard printf for testing

void create_threads(t_data *data)
{
    int i = 0;

    data->start_time = get_time_in_ms();
    while (i < data->num_philos)
    {
        if (pthread_create(&data->philos[i].thread, NULL,
				&philo_routine, &data->philos[i]) != 0)
            ft_printf("Failed to create thread for philosopher %d\n", i + 1);
        printf("Thread ID philo %d: %lu\n", i + 1, (unsigned long)data->philos[i].thread);
        i++;
    }
}

int main(int ac, char **av)
{
	// atexit(f);
	t_data *d_dataP;
	// int i;

	d_dataP = malloc(sizeof(t_data));
	if (!d_dataP)
		exit(1);
	half_main(ac, av, d_dataP);
	init_philos(d_dataP);
	create_threads(d_dataP);
	return (0);
}
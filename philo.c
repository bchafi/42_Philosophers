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
#include <stdio.h>

// void think(t_philo *philo);
// void take_forks(t_philo *philo);
// void eat(t_philo *philo);
// void put_forks(t_philo *philo);
// void sleep_philo(t_philo *philo);
// void print_action(t_philo *philo, char *msg);

void print_action(t_philo *philo, char *msg)
{
	long time = get_time_in_ms() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print_lock);
	if (!philo->data->someone_died)
		ft_printf("%ld %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void think(t_philo *philo)
{
	print_action(philo, "is thinking");
}

void take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken right fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken left fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken left fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken right fork");
	}
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
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
void sleep_philo(t_philo *philo)
{
	print_action(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->id % 2 == 0)
        usleep(500);

    while (1)
    {
        think(philo);
        take_forks(philo);
        eat(philo);
        put_forks(philo);
        sleep_philo(philo);
    }
    return NULL;
}


void create_threads(t_data *data)
{
    int i = 0;

    data->start_time = get_time_in_ms();
    while (i < data->num_philos)
    {
        if (pthread_create(&data->philos[i].thread, NULL,
				&philo_routine, &data->philos[i]) != 0)
            ft_printf("Failed to create thread for philosopher %d\n", i + 1);
        i++;
    }
}

int main(int ac, char **av)
{
	t_data *d_dataP;

	d_dataP = malloc(sizeof(t_data));
	if (!d_dataP)
		exit(1);
	parc_init(ac, av, d_dataP);
	create_threads(d_dataP);
	return (0);
}
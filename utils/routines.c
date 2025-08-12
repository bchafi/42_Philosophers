/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:22:56 by bchafi            #+#    #+#             */
/*   Updated: 2025/08/11 18:46:56 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_monitor_philo(t_data *data, int i, int *all_full)
{
	long	time_meal;
	int		meals;

	pthread_mutex_lock(&data->philos[i].meal_lock);
	time_meal = get_time_in_ms() - data->philos[i].last_meal;
	meals = data->philos[i].meals_eaten;
	pthread_mutex_unlock(&data->philos[i].meal_lock);
	pthread_mutex_lock(&data->death_lock);
	if (data->someone_died)
	{
		pthread_mutex_unlock(&data->death_lock);
		print_action(&data->philos[i], "died");
		return (1);
	}
	if (time_meal > data->time_to_die)
	{
		data->someone_died = 1;
		pthread_mutex_unlock(&data->death_lock);
		print_action(&data->philos[i], "died");
		return (1);
	}
	pthread_mutex_unlock(&data->death_lock);
	if (data->meals_required != -1 && meals < data->meals_required)
		*all_full = 0;
	return (0);
}

void	*monitor_routine(void *data_ptr)
{
	t_data	*data;
	int		i;
	int		all_full;

	data = (t_data *)data_ptr;
	while (1)
	{
		i = -1;
		all_full = 1;
		while (++i < data->num_philos)
		{
			if (check_monitor_philo(data, i, &all_full))
				return (NULL);
		}
		if (data->meals_required != -1 && all_full)
		{
			pthread_mutex_lock(&data->death_lock);
			data->someone_died = 1;
			pthread_mutex_unlock(&data->death_lock);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

void	routine_each_philo(t_philo *philo)
{
	take_forks(philo);
	eat(philo);
	put_forks(philo);
	sleep_philo(philo);
	think(philo);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		died;

	philo = (t_philo *)arg;
	if (philo->data->num_philos == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		cpu_sleep(philo->data->time_to_die, philo);
		return (pthread_mutex_unlock(philo->right_fork), NULL);
	}
	if (philo->id % 2 != 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_lock);
		died = philo->data->someone_died;
		pthread_mutex_unlock(&philo->data->death_lock);
		if (died)
			break ;
		routine_each_philo(philo);
	}
	return (NULL);
}

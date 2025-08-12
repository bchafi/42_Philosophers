/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:20:45 by bchafi            #+#    #+#             */
/*   Updated: 2025/08/11 18:43:59 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_action(t_philo *philo, char *msg)
{
	long	time;
	int		died;

	if (!msg)
	{
		write(2, "Warning: NULL message passed to print_action!\n", 47);
		return ;
	}
	time = get_time_in_ms() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->death_lock);
	died = philo->data->someone_died;
	pthread_mutex_lock(&philo->data->print_lock);
	if (!died || (msg[0] == 'd' && !ft_strncmp(msg, "died", 4)))
		printf("%ld %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_lock);
	pthread_mutex_unlock(&philo->data->death_lock);
}

void	think(t_philo *philo)
{
	print_action(philo, "is thinking");
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_lock);
	print_action(philo, "is eating");
	cpu_sleep(philo->data->time_to_eat, philo);
	pthread_mutex_lock(&philo->meal_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

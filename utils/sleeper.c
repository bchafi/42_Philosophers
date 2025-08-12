/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:17:42 by bchafi            #+#    #+#             */
/*   Updated: 2025/08/12 10:11:48 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	get_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	sleep_philo(t_philo *philo)
{
	print_action(philo, "is sleeping");
	cpu_sleep(philo->data->time_to_sleep, philo);
}

void	cpu_sleep(long duration_ms, t_philo *philo)
{
	long	start;
	int		died;

	start = get_time_in_ms();
	while ((get_time_in_ms() - start) < duration_ms)
	{
		pthread_mutex_lock(&philo->data->death_lock);
		died = philo->data->someone_died;
		pthread_mutex_unlock(&philo->data->death_lock);
		if (died)
			return ;
		usleep(100);
	}
}

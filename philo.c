/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 23:03:54 by bchafi            #+#    #+#             */
/*   Updated: 2025/08/12 15:35:48 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, \
			NULL, &philo_routine, &data->philos[i]))
		{
			write(2, "-Failed to create thread for philosopher-\n", 43);
			pthread_mutex_lock(&data->death_lock);
			data->someone_died = 1;
			pthread_mutex_unlock(&data->death_lock);
			while (--i >= 0)
				pthread_join(data->philos[i].thread, NULL);
			return (0);
		}
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data		*data_f;
	int			i;
	pthread_t	monitor;

	if (ac < 5 || ac > 6)
		return (ft_puterror_fd("Error Args!!\n"), 1);
	data_f = malloc(sizeof(t_data));
	if (!data_f)
		return (0);
	ft_memset(data_f, 0, sizeof(t_data));
	av = initializer(av, data_f);
	if (!av)
		return (free_to_exit(av, data_f), 1);
	data_f->start_time = get_time_in_ms();
	i = -1;
	while (++i < data_f->num_philos)
		data_f->philos[i].last_meal = data_f->start_time;
	if (!create_threads(data_f))
		return (free_to_exit(av, data_f), 0);
	if (pthread_create(&monitor, NULL, monitor_routine, data_f))
		return (pthread_join(monitor, NULL), free_to_exit(av, data_f), 0);
	i = -1;
	while (++i < data_f->num_philos)
		pthread_join(data_f->philos[i].thread, NULL);
	return (pthread_join(monitor, NULL), free_to_exit(av, data_f), 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 23:04:10 by bchafi            #+#    #+#             */
/*   Updated: 2025/08/12 15:59:22 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_data	*init_data(t_data *data, char **args)
{
	if (!args)
		return (free(data), data = NULL, ft_puterror_fd("No Argument!!"), NULL);
	data->meals_required = -2;
	data->num_philos = ft_atoi(args[0]);
	if (data->num_philos == 0 || data->num_philos > 200
		|| ft_atoi(args[0]) > INT_MAX || ft_atoi(args[0]) < 0)
		return (ft_puterror_fd("No Philosopher or more then 200!!\n"), NULL);
	data->time_to_die = ft_atoi(args[1]);
	data->time_to_eat = ft_atoi(args[2]);
	data->time_to_sleep = ft_atoi(args[3]);
	if (data->time_to_die < 60 || data->time_to_eat < 60
		|| data->time_to_sleep < 60 || data->time_to_die > INT_MAX
		|| data->time_to_eat > INT_MAX || data->time_to_sleep > INT_MAX
		|| (args[4] && ft_atoi(args[4]) > INT_MAX))
		return (ft_puterror_fd("An Args less Or More then??`60 or INT_MAX`\n")
			, NULL);
	if (args[4])
		data->meals_required = ft_atoi(args[4]);
	if (data->meals_required == 0 || data->meals_required == -1)
		return (ft_puterror_fd("An Args Under the bridge??`Meals Eating!!`\n")
			, NULL);
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->death_lock, NULL);
	return (data->someone_died = 0, data);
}

t_data	*init_philos(t_data *d_dataP)
{
	int	i;

	i = 0;
	while (i < d_dataP->num_philos)
	{
		d_dataP->philos[i].id = i + 1;
		d_dataP->philos[i].right_fork = &d_dataP->forks[i];
		d_dataP->philos[i].left_fork = &d_dataP->forks[(i + 1) \
		% d_dataP->num_philos];
		d_dataP->philos[i].meals_eaten = 0;
		d_dataP->philos[i].last_meal = 0;
		d_dataP->philos[i].data = d_dataP;
		pthread_mutex_init(&d_dataP->philos[i].meal_lock, NULL);
		i++;
	}
	return (d_dataP);
}

char	**initializer(char **av, t_data *d_dataP)
{
	int	i;

	av = parcing(av);
	if (!av)
		return (NULL);
	d_dataP = init_data(d_dataP, av);
	if (!d_dataP)
		return (free(d_dataP), free_args_philo(av), NULL);
	d_dataP->forks = malloc(sizeof(pthread_mutex_t) * d_dataP->num_philos);
	if (!d_dataP->forks)
		return (NULL);
	i = -1;
	while (++i < d_dataP->num_philos)
	{
		if (pthread_mutex_init(&d_dataP->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&d_dataP->forks[i]);
			return (NULL);
		}
	}
	d_dataP->philos = malloc(sizeof(t_philo) * d_dataP->num_philos);
	if (!d_dataP->philos)
		return (NULL);
	return (d_dataP = init_philos(d_dataP), av);
}

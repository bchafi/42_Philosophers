/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bader <bader@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:19:05 by bader             #+#    #+#             */
/*   Updated: 2025/04/08 10:19:10 by bader            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long get_time_in_ms()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

void new_data(t_data *data, char **args)
{
    data->meals_required = -1;
    data->num_philos = ft_atoi(args[0]);
    data->time_to_die = ft_atoi(args[1]);
    data->time_to_eat = ft_atoi(args[2]);
    data->time_to_sleep = ft_atoi(args[3]);
    if (args[4])
        data->meals_required = ft_atoi(args[4]);
    data->someone_died = 0;
    data->start_time = 0;
}

t_philo *init_philo(t_philo *philo, t_data *data)
{
	int i;

	i = 0;
	if (!philo)
	{
		free(data);
		free(data->forks);
		exit(1);
	}
	while (i < data->num_philos)
	{
		philo[i].id = i + 1;
		philo[i].left_fork = &data->forks[i];
		philo[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		philo[i].meals_eaten = 0;
		philo[i].last_meal = get_time_in_ms();
		philo[i++].data = data;
	}
	return (philo);
}

t_data *init_data(t_data *data, char **args)
{
    int i;

    if (!args || !args[1])
    {
        ft_puterror_fd("Arguments are missing!\n");
        exit(1);
    }
    new_data(data, args);
    if (data->num_philos == 0)
    {
        ft_puterror_fd("The number of philosophers is 0!!\n");
        free(data);
        exit(1);
    }
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
    if (!data->forks)
    {
        free(data);
        exit(1);
    }
    while (i < data->num_philos)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->print_lock, NULL);
    data->philos = malloc(sizeof(t_philo) * data->num_philos);
    if (!data->philos)
    {
        free(data->forks);
        free(data);
        exit(1);
    }
    return init_philo(data->philos, data);
}


void parc_init(int ac, char **av, t_data *d_dataP)
{
	int i;

	if (ac < 2)
	{
		ft_printf("Argumenta Is Less Then Two Args!!");
		exit(1);
	}
	av = parcing(av);
	d_dataP = init_data(d_dataP, av);
}

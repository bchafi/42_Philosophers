/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bader <bader@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 02:11:20 by bader             #+#    #+#             */
/*   Updated: 2025/04/07 13:15:31 by bader            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	// ft_printf("%d\n", t_args->meals_required);
	// ft_printf("%d\n", t_args->num_philos);
	// ft_printf("%d\n", t_args->time_to_die);
	// ft_printf("%d\n", t_args->time_to_eat);
	// ft_printf("%d\n", t_args->time_to_sleep);
	return (data);
}

int main(int ac, char **av)
{
	// atexit(f);
	t_data *d_dataP;
	t_philo *d_philo;
	if (ac < 2)
	{
		ft_printf("Argumenta Is Less Then Two Args!!");
		exit(1);
	}

	av = parcing(av);
	d_dataP = malloc(sizeof(t_data));
	if (!d_dataP)
		exit(1);
	d_dataP = init_data(d_dataP, av);
	d_philo = malloc(sizeof(t_philo));
	if (!d_philo)
	{
		free(d_dataP);
		exit(1);
	}
	d_dataP->forks = malloc(sizeof(pthread_mutex_t) * d_dataP->num_philos);
	if (!d_dataP->forks)
	{
		free(d_dataP);
		free(d_philo);
		free(d_dataP->forks);
		exit(1);
	}
	int i;
	i = 0;
	while (i < d_dataP->num_philos)
		pthread_mutex_init(&d_dataP->forks[i++], NULL);

	(void)d_philo;
	return (0);
}
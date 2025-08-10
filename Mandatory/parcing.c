/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 11:55:25 by bchafi            #+#    #+#             */
/*   Updated: 2025/08/10 11:58:47 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	are_valid_argument(char *argv)
{
	while (*argv && ft_isspace((unsigned char)*argv))
		argv++;
	if (*argv == '\0')
		return (ft_puterror_fd("An Argument Is Empty!!\n"), 0);
	while (*argv)
	{
		if (ft_isspace((unsigned char)*argv) && *(argv + 1) == '\0'
			&& ft_isspace((unsigned char)*(argv + 1)))
			return (ft_puterror_fd("An Argument Is Empty!!\n"), 0);
		argv++;
	}
	return (1);
}

int	check_if_numbers(char **args_sp)
{
	char	*args;
	int		i;

	i = 0;
	while (*args_sp)
	{
		i = 0;
		args = *args_sp;
		while (args[i])
		{
			if (ft_isdigit(args[i]))
				i++;
			else if (i == 0 && args[i] == '-')
				return (ft_puterror_fd("The Argument Is Negative!!\n"), 0);
			else if ((i == 0 && args[i] == '+') && ft_isdigit(args[i + 1]))
				i++;
			else
				return (ft_puterror_fd("The Argument Is Not A Digit!!\n"), 0);
		}
		args_sp++;
	}
	return (1);
}

char	**parcing(char **argv)
{
	char	*string;
	int		counter;
	char	**temp_args;

	temp_args = NULL;
	argv++;
	counter = 0;
	string = NULL;
	while (*argv)
	{
		if (!are_valid_argument(*argv))
			return (NULL);
		string = ft_strjoin(string, *argv);
		string = ft_strjoin(string, " ");
		argv++;
	}
	argv = ft_split(string, ' ');
	free(string);
	if (!check_if_numbers(argv))
		return (free_args_philo(argv), argv = NULL, NULL);
	temp_args = argv;
	while (*argv++)
		counter++;
	return (temp_args);
}

void	free_args_philo(char **args_philo)
{
	char	**start;

	start = args_philo;
	if (!args_philo)
		return ;
	while (*args_philo)
	{
		free(*args_philo);
		args_philo++;
	}
	free(start);
}

int	free_to_exit(char **av, t_data *data)
{
	int	i;

	i = -1;
	free_args_philo(av);
	if (data->philos)
		while (++i < data->num_philos)
			pthread_mutex_destroy(&data->philos[i].meal_lock);
	i = -1;
	if (data->forks)
		while (++i < data->num_philos)
			pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->death_lock);
	free(data->forks);
	free(data->philos);
	free(data);
	return (0);
}

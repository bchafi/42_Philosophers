/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bader <bader@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:07:07 by bader             #+#    #+#             */
/*   Updated: 2025/04/04 15:36:01 by bader            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// void free_args_philo(char **args_philo)
// {
// 	char **strc = args_philo;
// 	while (*args_philo)
// 	{
// 		free(*args_philo);
// 		args_philo++;
// 	}
// 	free(strc);
//  strc = NULL;
// 	return;
// }

int are_valid_argument(char *argv)
{
	while (*argv && ft_isspace((unsigned char)*argv))
		argv++;
	if (*argv == '\0')
		ft_puterror_fd("An Argument Is Empty!!\n");
	while (*argv)
	{
		if (ft_isspace((unsigned char)*argv) && *(argv + 1) == '\0' && ft_isspace((unsigned char)*(argv + 1)))
			ft_puterror_fd("An Argument Is Empty!!\n");
		argv++;
	}
	return (1);
}

void check_if_numbers(char **args_sp)
{
	char *args;
	int i;

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
				ft_puterror_fd("The Argument Is Negative!!\n");
			else if ((i == 0 && args[i] == '+') && ft_isdigit(args[i + 1]))
				i++;
			else
				ft_puterror_fd("The Argument Is Not A Digit!!\n");
		}
		args_sp++;
	}
}

char **parcing(char **argv)
{
	char    *string;
	int     counter;
    char    **temp_args;

	(1) && (temp_args = NULL, counter = 0, argv++, string = NULL);
	while (*argv)
	{
		are_valid_argument(*argv);
		string = ft_strjoin(string, *argv);
		string = ft_strjoin(string, " ");
		argv++;
	}
	argv = ft_split(string, ' ');
	check_if_numbers(argv);
	free(string);
    temp_args = argv;
	while (*argv++)
		counter++;
	if (counter <= 3 || counter >= 6)
		ft_puterror_fd("Error The args is not 4 or 5\n");
	return (temp_args);
}

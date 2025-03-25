/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bader <bader@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 02:11:20 by bader             #+#    #+#             */
/*   Updated: 2025/03/25 01:54:23 by bader            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
# include <stdlib.h>

int	are_valid_argument(char *argv)
{
	while (*argv && ft_isspace((unsigned char)*argv))
		argv++;
	if (*argv == '\0')
		ft_puterror_fd("An Argument Is Empty!!\n");
	while (*argv)
	{
		if (ft_isspace((unsigned char)*argv) && *(argv + 1) == '\0'
			&& ft_isspace((unsigned char)*(argv + 1)))
			ft_puterror_fd("An Argument Is Empty!!\n");
		argv++;
	}
	return (1);
}

void	check_if_numbers(char **args_sp)
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
				ft_puterror_fd("The Argument Is Negative!!\n");
			else if ((i == 0 && args[i] == '+') && ft_isdigit(args[i + 1]))
				i++;
			else
				ft_puterror_fd("The Argument Is Not A Digit!!\n");
		}
		args_sp++;
	}
}

char	**parcing(char **argv)
{
	char	*string;
	char	**args_philo;

	argv++;
	string = NULL;
	while (*argv)
	{
		are_valid_argument(*argv);
		string = ft_strjoin(string, *argv);
		string = ft_strjoin(string, " ");
		argv++;
	}
	args_philo = ft_split(string, ' ');
	check_if_numbers(args_philo);
	free(string);
	return (args_philo);
}

int main(int ac, char **av)
{
	(void)ac;
	parcing(av);

	return (0);
}
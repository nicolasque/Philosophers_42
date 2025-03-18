/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verify_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nquecedo <nquecedo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 01:35:37 by nquecedo          #+#    #+#             */
/*   Updated: 2025/03/18 11:43:26 by nquecedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Philosophers.h"

bool	ft_check_nbr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && (str[i] != '-' && str[i] != '+'))
			return (false);
		i++;
	}
	return (true);
}

bool	ft_chek_individual_arg(char **argv)
{
	if (ft_atoi(argv[0]) <= 0 || ft_atoi(argv[0]) >= PHILO_MAX)
		return (printf("%sBad Philosofer number %s\n", RED, RESET), false);
	if (ft_atoi(argv[1]) <= 60)
		return (printf("%sBad time_to_die %s\n", RED, RESET), false);
	if (ft_atoi(argv[2]) <= 60)
		return (printf("%sBad time_to_eat %s\n", RED, RESET), false);
	if (ft_atoi(argv[3]) <= 60)
		return (printf("%sBad time_to_sleep %s\n", RED, RESET), false);
	if (argv[4])
		if (ft_atoi(argv[4]) < 1)
			return (printf("%sBad numbe_times_to_eat %s\n", RED, RESET), false);
	return (true);
}

bool	ft_check_args(int argc, char **argv)
{
	int	i;

	argc--;
	if (argc != 4 && argc != 5)
	{
		printf("%sBad argument number %s\n", RED, RESET);
		return (false);
	}
	i = 0;
	while (i < argc)
	{
		if (ft_check_nbr(argv[i]) == false)
		{
			printf("%sBad argument type (only numbers) %s\n", RED, RESET);
			return (false);
		}
		i++;
	}
	if (ft_chek_individual_arg(argv) == false)
		return (false);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nquecedo <nquecedo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:22:01 by nquecedo          #+#    #+#             */
/*   Updated: 2025/03/03 17:57:03 by nquecedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Philosophers.h"

void ft_print_args(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
	{
		ft_printf("ARGV: %s\n", argv[i]);
		i++;
	}
}

void ft_print_shared(t_shared *t_shared)
{
	printf("=================\n");
	printf("nbr_filos: %d\n", t_shared->nbr_filo);
	printf("time_to_die: %ld\n", t_shared->time_to_die);
	printf("time_to_eat: %ld\n", t_shared->time_to_eat);
	printf("time_to_sleep: %ld\n", t_shared->time_to_sleep);
	if (t_shared->nbr_times_to_eat)
		printf("nbr_times_to_eat: %d\n", t_shared->nbr_times_to_eat);
	printf("=================\n");
}

void ft_print_philos(t_philo *t_philos)
{
	int i;

	i = 0;
	while (t_philos[i].id_philo != PHILO_LAST)
	{
		printf("=================\n");
		printf("Philo_id: %d\n", t_philos[i].id_philo);
		printf("Philo_fork: %d\n", t_philos[i].fork);
		if (t_philos[i].live == ALIVE)
			printf("Philo_live: %sALIVE%s\n", GREEN, RESET);
		else
			printf("Philo_live: %sDEAD%s\n", RED, RESET);
		printf("Philo_time_eaten: %d\n", t_philos[i].times_eaten);
		printf("Philo_time_start: %ld\n", t_philos[i].time_star);
		printf("Philo_time_end: %ld\n", t_philos[i].time_end);
		printf("=================\n\n");
		i++;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_shared.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nquecedo <nquecedo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 02:44:13 by nquecedo          #+#    #+#             */
/*   Updated: 2025/03/03 17:27:37 by nquecedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Philosophers.h"

void ft_init_shared(char **argv, t_shared *t_shared)
{
	int i;

	i = 0;
	t_shared->nbr_filo = ft_atoi(argv[0]);
	t_shared->time_to_die = ft_atoi(argv[1]);
	t_shared->time_to_eat = ft_atoi(argv[2]);
	t_shared->time_to_sleep = ft_atoi(argv[3]);
	if (argv[4])
		t_shared->nbr_times_to_eat = ft_atoi(argv[4]);
	else
		t_shared->nbr_times_to_eat = false;
	pthread_mutex_init(&t_shared->print_mutex, NULL);
	pthread_mutex_init(&t_shared->death_mutex, NULL);
	t_shared->forks = malloc(sizeof(pthread_mutex_t) * t_shared->nbr_filo);
	while (i < t_shared->nbr_filo)
	{
        pthread_mutex_init(&t_shared->forks[i], NULL);
		i++;
	}

}

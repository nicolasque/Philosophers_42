/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_const.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nquecedo <nquecedo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:46:16 by nquecedo          #+#    #+#             */
/*   Updated: 2025/03/18 12:00:50 by nquecedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Philosophers.h"

void	ft_init_shared(char **argv, t_shared *t_shared)
{
	int	i;

	i = 0;
	t_shared->nbr_filo = ft_atol(argv[0]);
	t_shared->time_to_die = ft_atol(argv[1]);
	t_shared->time_to_eat = ft_atol(argv[2]);
	t_shared->time_to_sleep = ft_atol(argv[3]);
	t_shared->program_star_time = get_time_mls();
	t_shared->philos_live = ALIVE;
	if (argv[4])
		t_shared->nbr_times_to_eat = ft_atoi(argv[4]);
	else
		t_shared->nbr_times_to_eat = 0;
	pthread_mutex_init(&t_shared->print_mutex, NULL);
	pthread_mutex_init(&t_shared->death_mutex, NULL);
	t_shared->forks = malloc(sizeof(pthread_mutex_t) * t_shared->nbr_filo);
	while (i < t_shared->nbr_filo)
	{
		pthread_mutex_init(&t_shared->forks[i], NULL);
		i++;
	}
}

void	ft_init_philos(t_shared *t_shared, t_philo *t_philo)
{
	int	i;

	i = 0;
	while (i < (*t_shared).nbr_filo && i < PHILO_MAX)
	{
		t_philo[i].id_philo = i + 1;
		t_philo[i].live = ALIVE;
		t_philo[i].times_eaten = 0;
		t_philo[i].last_time_eaten = get_time_mls();
		t_philo[i].time_end = 0;
		t_philo[i].left_fork = i;
		t_philo[i].right_fork = (i + 1) % t_shared->nbr_filo;
		t_philo[i].t_shared = t_shared;
		i++;
	}
	t_shared->t_philos = t_philo;
	t_philo[i].id_philo = PHILO_LAST;
}
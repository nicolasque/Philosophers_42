/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nquecedo <nquecedo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:22:01 by nquecedo          #+#    #+#             */
/*   Updated: 2025/03/17 22:15:50 by nquecedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Philosophers.h"

void	ft_print_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		ft_printf("ARGV: %s\n", argv[i]);
		i++;
	}
}

void	ft_print_shared(t_shared *t_shared)
{
	printf("=================\n");
	printf("nbr_filos: %d\n", t_shared->nbr_filo);
	printf("time_to_die: %ld\n", t_shared->time_to_die);
	printf("time_to_eat: %ld\n", t_shared->time_to_eat);
	printf("time_to_sleep: %ld\n", t_shared->time_to_sleep);
	printf("nbr_times_to_eat: %d\n", t_shared->nbr_times_to_eat);
	printf("=================\n");
}

void	ft_print_philos(t_philo *t_philos)
{
	int	i;

	i = 0;
	while (t_philos[i].id_philo != PHILO_LAST)
	{
		printf("=================\n");
		printf("Philo_id: %d\n", t_philos[i].id_philo);
		printf("Philo_left_fork: %d\n", t_philos[i].left_fork);
		printf("Philo_right_fork: %d\n", t_philos[i].right_fork);
		if (t_philos[i].live == ALIVE)
			printf("Philo_live: %sALIVE%s\n", GREEN, RESET);
		else
			printf("Philo_live: %sDEAD%s\n", RED, RESET);
		printf("Philo_time_eaten: %d\n", t_philos[i].times_eaten);
		printf("Philo_time_start: %ld\n", t_philos[i].last_time_eaten);
		printf("Philo_time_end: %ld\n", t_philos[i].time_end);
		printf("=================\n\n");
		i++;
	}
}

void	ft_print_mutex(t_philo *t_philo, char action)
{
	pthread_mutex_lock(&t_philo->t_shared->print_mutex);
	pthread_mutex_lock(&t_philo->t_shared->death_mutex);
	if (t_philo->t_shared->philos_live == DEAD)
		return (pthread_mutex_unlock(&t_philo->t_shared->death_mutex), pthread_mutex_unlock(&t_philo->t_shared->print_mutex), (void)0);
	pthread_mutex_unlock(&t_philo->t_shared->death_mutex);
	if (action == TAKE_FORK)
		printf("%s%lld %d has taken a fork%s\n", YELLOW, (get_time_mls()
				- t_philo->t_shared->program_star_time), t_philo->id_philo,
			RESET);
	else if (action == EAT)
		printf("%s%lld %d has eaten%s\n", CYAN, (get_time_mls()
				- t_philo->t_shared->program_star_time), t_philo->id_philo,
			RESET);
	else if (action == SLEEP)
		printf("%s%lld %d is sleeping%s\n", PURPLE, (get_time_mls()
				- t_philo->t_shared->program_star_time), t_philo->id_philo,
			RESET);
	else if (action == THINK)
		printf("%s%lld %d is thinking%s\n", GREEN, (get_time_mls()
				- t_philo->t_shared->program_star_time), t_philo->id_philo,
			RESET);
	pthread_mutex_unlock(&t_philo->t_shared->print_mutex);
}

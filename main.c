/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nquecedo <nquecedo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:26:00 by nquecedo          #+#    #+#             */
/*   Updated: 2025/06/10 03:10:09 by nquecedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/includes/Philosophers.h"

void	*ft_proces(void *arg)
{
	t_philo	*t_philo;

	t_philo = arg;
	if (t_philo->id_philo % 2 == 0)
		custom_sleep_ms(5, t_philo->t_shared);
	while (!ft_is_philos_dead(t_philo->t_shared))
	{
		ft_eat(t_philo);
		if (ft_is_philos_dead(t_philo->t_shared))
			break;
		ft_sleep(t_philo);
		if (ft_is_philos_dead(t_philo->t_shared))
			break;
		ft_think(t_philo);
		usleep(100);
	}
	return (NULL);
}

void	ft_init_theads(t_philo *t_philos, t_shared *t_shared)
{
	int			i;
	pthread_t	t_monitor[2];

	i = 0;
	pthread_create(&t_monitor[0], NULL, &ft_monitor_dead, t_shared);
	if (t_shared->nbr_times_to_eat && t_shared->nbr_filo > 1)
		pthread_create(&t_monitor[1], NULL, &ft_monitor_eat, t_shared);
	while (t_philos[i].id_philo != PHILO_LAST)
	{
		pthread_create(&t_philos[i].philo_thread, NULL, &ft_proces,
			&t_philos[i]);
		i++;
	}
	i = 0;
	pthread_join(t_monitor[0], NULL);
	if (t_shared->nbr_times_to_eat && t_shared->nbr_filo > 1)
		pthread_join(t_monitor[1], NULL);
	while (t_philos[i].id_philo != PHILO_LAST)
	{
		pthread_join(t_philos[i].philo_thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_shared	t_shared;
	t_philo		t_philos[PHILO_MAX];

	(void)t_shared;
	argv++;
	if (ft_check_args(argc, argv) == false)
		return (1);
	ft_init_shared(argv, &t_shared);
	ft_print_shared(&t_shared);
	ft_init_philos(&t_shared, t_philos);
	ft_print_philos(t_philos);
	ft_init_theads(t_philos, &t_shared);
	return (0);
}

// ft_print_philos(t_philos);
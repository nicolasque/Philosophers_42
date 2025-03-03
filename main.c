/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nquecedo <nquecedo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:26:00 by nquecedo          #+#    #+#             */
/*   Updated: 2025/03/03 18:02:03 by nquecedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/includes/Philosophers.h"

void	ft_init_philos(t_shared *t_shared, t_philo *t_philo)
{
	int i;

	i = 0;
	
	while (i < (*t_shared).nbr_filo && i < PHILO_MAX)
	{
		t_philo[i].id_philo = i;
		t_philo[i].fork = 1;
		t_philo[i].live = ALIVE;
		t_philo[i].times_eaten = 0;
		t_philo[i].time_star = 0;
		t_philo[i].time_end = 0;
		pthread_mutex_init(&t_philo[i].fork_mutex, NULL);
		pthread_mutex_init(&t_philo[i].sleep_mutex, NULL);
		pthread_mutex_init(&t_philo[i].think_mutex, NULL);
		t_philo[i].t_shared = t_shared;
		i++;
	}
	t_philo[i].id_philo = PHILO_LAST;
}

void	ft_init_theads(t_philo *t_philos)
{
	int i;

	i = 0;
	while (t_philos[i].id_philo != PHILO_LAST)
	{
		
	}
	
}

int	main(int argc, char **argv)
{
	struct s_shared t_shared;
	struct s_philo t_philos[PHILO_MAX];

	(void)t_shared;
	argv ++; // Para saltar el nombre del porgrama
	if (ft_check_args(argc, argv) == false)
		return (1);
	ft_init_shared(argv, &t_shared);
	ft_print_shared(&t_shared);
	ft_init_philos(&t_shared, t_philos);
	ft_print_philos(t_philos);
	

	return (0);
}

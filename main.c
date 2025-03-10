/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nquecedo <nquecedo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:26:00 by nquecedo          #+#    #+#             */
/*   Updated: 2025/03/10 17:55:25 by nquecedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/includes/Philosophers.h"

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

void	*ft_proces(void *arg)
{
	int		i;
	t_philo	*t_philo;

	t_philo = arg;
	i = 0;
	if (t_philo->id_philo % 2 == 0)
		custom_sleep_ms(50);
	while (1)
	{
		if (t_philo->t_shared->philos_live == DEAD)
			return (NULL);
		ft_eat(t_philo);
		ft_sleep(t_philo);
		ft_think(t_philo);
		i++;
	}
	return (NULL);
}

void	*ft_monitor(void *arg)
{
	t_shared *t_shared;
	t_philo *t_philos;
	int i;

	i = 0;
	t_shared = arg;
	t_philos = t_shared->t_philos;
	while (1)
	{
		if (t_philos[i].live == DEAD)
		{
			t_shared->philos_live = DEAD;
			printf("%sTime: %lld Id_Philo: %d Has died%s\n", RED, (get_time_mls()
					- t_shared->program_star_time), t_philos[i].id_philo,
				RESET);
			break;
		}
		if (t_philos[i].times_eaten < t_shared->nbr_times_to_eat && t_philos[i].id_philo != PHILO_LAST)
		{
			i++;
			continue ;
		}
		if (t_philos[i].id_philo == PHILO_LAST)
			i = 0;
		i++;
	}
	return (NULL);
}

void	ft_init_theads(t_philo *t_philos, t_shared *t_shared)
{
	int	i;
	pthread_t		t_monitor;

	i = 0;
	pthread_create(&t_monitor, NULL, &ft_monitor, t_shared);
	while (t_philos[i].id_philo != PHILO_LAST)
	{
		pthread_create(&t_philos[i].philo_thread, NULL, &ft_proces,
			&t_philos[i]);
		i++;
	}
	i = 0;
	pthread_join(t_monitor, NULL);
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
	argv++; // Para saltar el nombre del porgrama
	if (ft_check_args(argc, argv) == false)
		return (1);
	ft_init_shared(argv, &t_shared);
	ft_print_shared(&t_shared);
	ft_init_philos(&t_shared, t_philos);
	ft_print_philos(t_philos);
	ft_init_theads(t_philos, &t_shared);
	printf("Despues de los hilos \n");
	ft_print_philos(t_philos);

	return (0);
}

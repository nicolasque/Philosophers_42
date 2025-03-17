/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nquecedo <nquecedo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:26:00 by nquecedo          #+#    #+#             */
/*   Updated: 2025/03/17 21:16:06 by nquecedo         ###   ########.fr       */
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
	t_philo	*t_philo;

	t_philo = arg;
	if (t_philo->id_philo % 2 == 0)
		custom_sleep_ms(50, t_philo->t_shared);
	while (1)
	{
		if (t_philo->t_shared->philos_live == DEAD)
			return (NULL);
		ft_eat(t_philo);
		if (t_philo->t_shared->philos_live == DEAD)
			return (NULL);
		ft_sleep(t_philo);
		if (t_philo->t_shared->philos_live == DEAD)
			return (NULL);
		ft_think(t_philo);
	}
	return (NULL);
}

void	*ft_monitor_dead(void *arg)
{
	t_shared	*t_shared;
	t_philo		*t_philos;
	int			i;

	i = 0;
	t_shared = arg;
	t_philos = t_shared->t_philos;
	while (1)
	{
		if (t_philos[i].id_philo == PHILO_LAST)
			i = 0;
		pthread_mutex_lock(&t_shared->death_mutex);
		if (t_philos[i].live == DEAD)
		{
			t_shared->philos_live = DEAD;
			pthread_mutex_lock(&t_philos->t_shared->print_mutex);
			printf("%s%lld %d Has died%s\n", RED, (get_time_mls()
					- t_shared->program_star_time), t_philos[i].id_philo,
				RESET);
			pthread_mutex_unlock(&t_philos->t_shared->print_mutex);
			pthread_mutex_unlock(&t_shared->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&t_shared->death_mutex);

		i++;
		usleep(100);
	}
	return (NULL);
}

void	*ft_monitor_eat(void *arg)
{
	t_shared	*t_shared;
	t_philo		*t_philos;
	int			i;

	i = 0;
	t_shared = arg;
	t_philos = t_shared->t_philos;
	if (t_shared->nbr_times_to_eat == 0)
		return (NULL);
	while (1)
	{
		if (t_philos[i].id_philo == PHILO_LAST)
		{
			t_shared->philos_live = DEAD;
			pthread_mutex_lock(&t_philos->t_shared->print_mutex);
			printf("%sAll Philosofers have finised eating %s\n", BOLD_GREEN,
				RESET);
			pthread_mutex_unlock(&t_philos->t_shared->print_mutex);
			break ;
		}
		if (t_philos[i].times_eaten < t_shared->nbr_times_to_eat)
			i = 0;
		i++;
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
	if (t_shared->nbr_times_to_eat)
		pthread_create(&t_monitor[1], NULL, &ft_monitor_eat, t_shared);
	while (t_philos[i].id_philo != PHILO_LAST)
	{
		pthread_create(&t_philos[i].philo_thread, NULL, &ft_proces,
			&t_philos[i]);
		i++;
	}
	i = 0;
	pthread_join(t_monitor[0], NULL);
	if (t_shared->nbr_times_to_eat)
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
	argv++; // Para saltar el nombre del porgrama
	if (ft_check_args(argc, argv) == false)
		return (1);
	ft_init_shared(argv, &t_shared);
	ft_print_shared(&t_shared);
	ft_init_philos(&t_shared, t_philos);
	ft_print_philos(t_philos);
	ft_init_theads(t_philos, &t_shared);
	ft_print_philos(t_philos);
	return (0);
}

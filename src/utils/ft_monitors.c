/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nquecedo <nquecedo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:45:32 by nquecedo          #+#    #+#             */
/*   Updated: 2025/03/18 20:27:15 by nquecedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Philosophers.h"

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
		{
			i = 0;
		}
		ft_check_dead_time(&t_philos[i]);
		pthread_mutex_lock(&t_shared->death_mutex);
		if (t_shared->all_finish_eating == true)
		{
			pthread_mutex_unlock(&t_shared->death_mutex);
			break;
		}
		if (t_philos[i].live == DEAD)
		{
			t_shared->philos_live = DEAD;
			pthread_mutex_unlock(&t_shared->death_mutex);
			pthread_mutex_lock(&t_shared->print_mutex);
			printf("%s%lld %d Has died%s\n", RED, (get_time_mls()
					- t_shared->program_star_time), t_philos[i].id_philo,
				RESET);
			pthread_mutex_unlock(&t_shared->print_mutex);
			break ;
		}
		pthread_mutex_unlock(&t_shared->death_mutex);
		i++;
		usleep(10);
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
		pthread_mutex_lock(&t_shared->death_mutex);
		if (t_shared->philos_live == DEAD)
		{
			pthread_mutex_unlock(&t_shared->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&t_shared->death_mutex);
		if (t_philos[i].id_philo == PHILO_LAST)
		{
			pthread_mutex_lock(&t_shared->death_mutex);
			t_shared->philos_live = DEAD;
			t_shared->all_finish_eating = true;
			pthread_mutex_unlock(&t_shared->death_mutex);
			pthread_mutex_lock(&t_philos->t_shared->print_mutex);
			printf("%sAll Philosofers have finised eating %s\n", BOLD_GREEN,
				RESET);
			pthread_mutex_unlock(&t_philos->t_shared->print_mutex);
			break ;
		}
		if (t_philos[i].times_eaten < t_shared->nbr_times_to_eat)
			i = 0;
		i++;
		usleep(10);
	}
	return (NULL);
}

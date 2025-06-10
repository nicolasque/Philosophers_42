/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nquecedo <nquecedo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:45:32 by nquecedo          #+#    #+#             */
/*   Updated: 2025/06/10 03:08:39 by nquecedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Philosophers.h"

static void	ft_print_monitors(t_philo *t_philo, t_shared *t_shared, int action)
{
	pthread_mutex_lock(&t_shared->print_mutex);
	if (action == ALL_EAT)
	{
		printf("%sAll Philosofers have finised eating %s\n", BOLD_GREEN, RESET);
	}
	else if (action == DIE_MSG)
	{
		printf("%s%lld %d Has died%s\n", RED, (get_time_mls()
				- t_shared->program_star_time), t_philo->id_philo, RESET);
	}
	pthread_mutex_unlock(&t_shared->print_mutex);
}

static void	ft_set_dead_state(t_philo *t_philo, t_shared *t_shared, int action)
{
	if (action == ALL_EAT)
	{
		pthread_mutex_lock(&t_shared->death_mutex);
		t_shared->philos_live = DEAD;
		t_shared->all_finish_eating = true;
		ft_print_monitors(t_philo, t_shared, ALL_EAT);
	}
	else if (action == DIE_MSG)
	{
		t_shared->philos_live = DEAD;
		ft_print_monitors(t_philo, t_shared, DIE_MSG);
	}
}

static void	ft_init_args(void *arg, t_shared **t_shared, t_philo **t_philos,
		int *i)
{
	i = 0;
	*t_shared = arg;
	*t_philos = (*t_shared)->t_philos;
	(void)i;
}

void	*ft_monitor_dead(void *arg)
{
	t_shared	*t_shared;
	t_philo		*t_philos;
	int			i;

	ft_init_args(arg, &t_shared, &t_philos, &i);
	while (1)
	{
		if (t_philos[i].id_philo == PHILO_LAST)
			i = 0;
		ft_check_dead_time(&t_philos[i]);
		pthread_mutex_lock(&t_shared->death_mutex);
		if (t_shared->all_finish_eating == true)
			break ;
		if (t_philos[i].live == DEAD)
		{
			ft_set_dead_state(&t_philos[i], t_shared, DIE_MSG);
			break ;
		}
		i++;
		pthread_mutex_unlock(&t_shared->death_mutex);
		usleep(10);
	}
	pthread_mutex_unlock(&t_shared->death_mutex);
	return (NULL);
}

void	*ft_monitor_eat(void *arg)
{
	t_shared	*t_shared;
	t_philo		*t_philos;
	int			i;

	ft_init_args(arg, &t_shared, &t_philos, &i);
	while (1)
	{
		pthread_mutex_lock(&t_shared->death_mutex);
		if (t_shared->philos_live == DEAD)
			break ;
		pthread_mutex_unlock(&t_shared->death_mutex);
		if (t_philos[i].id_philo == PHILO_LAST)
		{
			ft_set_dead_state(&t_philos[i], t_shared, ALL_EAT);
			break ;
		}
		if (t_philos[i].times_eaten < t_shared->nbr_times_to_eat)
			i = 0;
		i++;
		usleep(10);
	}
	pthread_mutex_unlock(&t_shared->death_mutex);
	return (NULL);
}

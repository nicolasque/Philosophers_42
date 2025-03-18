/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_dead_time.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nquecedo <nquecedo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 01:11:20 by nquecedo          #+#    #+#             */
/*   Updated: 2025/03/18 14:51:15 by nquecedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Philosophers.h"

int	ft_check_dead_time(t_philo *t_philo)
{
	long int	actual_time;
	long int	time_since_last_meal;
	int			is_dead;

	pthread_mutex_lock(&t_philo->t_shared->death_mutex);
	if (t_philo->t_shared->philos_live == DEAD)
	{
		pthread_mutex_unlock(&t_philo->t_shared->death_mutex);
		return (DEAD);
	}
	actual_time = get_time_mls();
	time_since_last_meal = actual_time - t_philo->last_time_eaten;
	if (t_philo->live == ALIVE
		&& time_since_last_meal >= t_philo->t_shared->time_to_die)
	{
		t_philo->live = DEAD;
		t_philo->t_shared->philos_live = DEAD;
		is_dead = DEAD;
	}
	else
		is_dead = ALIVE;
	pthread_mutex_unlock(&t_philo->t_shared->death_mutex);
	return (is_dead);
}

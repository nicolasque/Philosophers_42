/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_dead_time.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nquecedo <nquecedo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 01:11:20 by nquecedo          #+#    #+#             */
/*   Updated: 2025/03/18 11:42:32 by nquecedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Philosophers.h"

int	ft_check_dead_time(t_philo *t_philo)
{
	long int	actual_time;
	int			is_dead;

	is_dead = ALIVE;
	pthread_mutex_lock(&t_philo->t_shared->death_mutex);
	actual_time = get_time_mls();
	if (t_philo->live == ALIVE && (actual_time
			- t_philo->last_time_eaten) >= t_philo->t_shared->time_to_die)
	{
		t_philo->live = DEAD;
		is_dead = DEAD;
	}
	pthread_mutex_unlock(&t_philo->t_shared->death_mutex);
	return (is_dead);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_acctions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nquecedo <nquecedo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 00:41:04 by nquecedo          #+#    #+#             */
/*   Updated: 2025/03/17 17:40:05 by nquecedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Philosophers.h"

static int	ft_handle_single_philo(t_philo *t_philo)
{
	if (t_philo->t_shared->nbr_filo != 1)
		return (0);
	pthread_mutex_lock(&t_philo->t_shared->forks[t_philo->left_fork]);
	ft_print_mutex(t_philo, TAKE_FORK);
	while (t_philo->t_shared->philos_live != DEAD)
	{
		ft_check_dead_time(t_philo);
		custom_sleep_ms(1, t_philo->t_shared);
	}
	pthread_mutex_unlock(&t_philo->t_shared->forks[t_philo->left_fork]);
	return (1);
}

void	ft_eat(t_philo *t_philo)
{
	if (ft_handle_single_philo(t_philo))
		return ;
	pthread_mutex_lock(&t_philo->t_shared->forks[t_philo->left_fork]);
	ft_check_dead_time(t_philo);
	if (t_philo->t_shared->philos_live == DEAD)
		return (pthread_mutex_unlock(&t_philo->t_shared->forks[t_philo->left_fork]),
			(void)0);
	ft_print_mutex(t_philo, TAKE_FORK);
	pthread_mutex_lock(&t_philo->t_shared->forks[t_philo->right_fork]);
	ft_check_dead_time(t_philo);
	if (t_philo->t_shared->philos_live == DEAD)
		return (pthread_mutex_unlock(&t_philo->t_shared->forks[t_philo->left_fork]),
			pthread_mutex_unlock(&t_philo->t_shared->forks[t_philo->right_fork]),
			(void)0);
	ft_print_mutex(t_philo, TAKE_FORK);
	if (t_philo->t_shared->philos_live == DEAD)
		return (pthread_mutex_unlock(&t_philo->t_shared->forks[t_philo->left_fork]),
			pthread_mutex_unlock(&t_philo->t_shared->forks[t_philo->right_fork]),
			(void)0);
	ft_print_mutex(t_philo, EAT);
	t_philo->times_eaten++;
	t_philo->last_time_eaten = get_time_mls();
	custom_sleep_ms(t_philo->t_shared->time_to_eat, t_philo->t_shared);
	pthread_mutex_unlock(&t_philo->t_shared->forks[t_philo->right_fork]);
	pthread_mutex_unlock(&t_philo->t_shared->forks[t_philo->left_fork]);
}

void	ft_sleep(t_philo *t_philo)
{
	ft_check_dead_time(t_philo);
	if (t_philo->t_shared->philos_live == DEAD)
		return ((void)0);
	ft_print_mutex(t_philo, SLEEP);
	custom_sleep_ms(t_philo->t_shared->time_to_sleep, t_philo->t_shared);
}

void	ft_think(t_philo *t_philo)
{
	if (t_philo->t_shared->philos_live == DEAD)
		return ((void)0);
	ft_print_mutex(t_philo, THINK);
}

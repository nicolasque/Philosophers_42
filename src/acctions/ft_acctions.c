/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_acctions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nquecedo <nquecedo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 00:41:04 by nquecedo          #+#    #+#             */
/*   Updated: 2025/03/04 03:31:45 by nquecedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Philosophers.h"

void	ft_eat(t_philo *t_philo)
{
	pthread_mutex_lock(&t_philo->t_shared->forks[t_philo->left_fork]);
	if (ft_check_dead_time(t_philo))
		return ;
	pthread_mutex_lock(&t_philo->t_shared->print_mutex);
	printf("%sTime: %lld Id_Philo: %d has taken a fork%s\n", YELLOW,
		(get_time_s() - t_philo->t_shared->program_star_time),
		t_philo->id_philo, RESET);
	pthread_mutex_unlock(&t_philo->t_shared->print_mutex);
	pthread_mutex_lock(&t_philo->t_shared->forks[t_philo->right_fork]);
	pthread_mutex_lock(&t_philo->t_shared->print_mutex);
	printf("%sTime: %lld Id_Philo: %d has eaten%s\n", CYAN, (get_time_s()
			- t_philo->t_shared->program_star_time), t_philo->id_philo, RESET);
	pthread_mutex_unlock(&t_philo->t_shared->print_mutex);
	custom_sleep_ms(t_philo->t_shared->time_to_eat);
	pthread_mutex_lock(&t_philo->t_shared->death_mutex);
	t_philo->times_eaten++;
	t_philo->last_time_eaten = get_time_ms();
	pthread_mutex_unlock(&t_philo->t_shared->death_mutex);
	pthread_mutex_unlock(&t_philo->t_shared->forks[t_philo->right_fork]);
	pthread_mutex_unlock(&t_philo->t_shared->forks[t_philo->left_fork]);
}

void	ft_sleep(t_philo *t_philo)
{
	pthread_mutex_lock(&t_philo->t_shared->print_mutex);
	printf("%sTime: %lld Id_Philo: %d is sleeping%s\n", PURPLE, (get_time_s()
	- t_philo->t_shared->program_star_time), t_philo->id_philo, RESET);
	pthread_mutex_unlock(&t_philo->t_shared->print_mutex);
	custom_sleep_ms(t_philo->t_shared->time_to_sleep);
	if (t_philo->last_time_eaten)
		ft_check_dead_time(t_philo);
	if (t_philo->live == DEAD)
		return ;
}

void	ft_think(t_philo *t_philo)
{
	pthread_mutex_lock(&t_philo->t_shared->print_mutex);
	printf("%sTime: %lld Id_Philo: %d is thinking%s\n", GREEN, (get_time_s()
	- t_philo->t_shared->program_star_time), t_philo->id_philo, RESET);
	pthread_mutex_unlock(&t_philo->t_shared->print_mutex);
	if (t_philo->last_time_eaten)
		ft_check_dead_time(t_philo);
	if (t_philo->live == DEAD)
		return ;
}

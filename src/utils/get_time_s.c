/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nquecedo <nquecedo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:23:31 by nquecedo          #+#    #+#             */
/*   Updated: 2025/06/10 02:57:52 by nquecedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Philosophers.h"

long get_time_micros(void)
{
	struct timeval time;
	long milliseconds;

	gettimeofday(&time, NULL);
	milliseconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (milliseconds);
}

long int get_time_s(void)
{
	struct timeval time;
	long seconds;

	gettimeofday(&time, NULL);
	seconds = time.tv_sec;
	return (seconds);
}

long int get_time_mls(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long int diff_time(long int time)
{
	return (get_time_mls() - time);
}

void custom_sleep_ms(long int time, t_shared *t_shared)
{
	long int start_time;
	long int current_time;

	start_time = get_time_mls();
	while (!ft_is_philos_dead(t_shared))
	{
		current_time = get_time_mls();
		if (current_time - start_time >= time)
			break;
		usleep(500); // Sleep más corto para mejor precisión pero menos overhead
	}
}

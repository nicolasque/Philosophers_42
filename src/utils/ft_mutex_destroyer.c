/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex_destroyer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nquecedo <nquecedo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:03:37 by nquecedo          #+#    #+#             */
/*   Updated: 2025/03/18 11:44:30 by nquecedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Philosophers.h"

void	ft_mutex_destroyer(t_shared *t_shared)
{
	int	i;

	i = 0;
	while (i < t_shared->nbr_filo)
	{
		pthread_mutex_destroy(&t_shared->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&t_shared->death_mutex);
	pthread_mutex_destroy(&t_shared->print_mutex);
}

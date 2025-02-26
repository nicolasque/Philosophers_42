/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_const.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nquecedo <nquecedo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 02:44:13 by nquecedo          #+#    #+#             */
/*   Updated: 2025/02/26 02:53:44 by nquecedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Philosophers.h"

void ft_init_const(char **argv, t_const *t_const)
{
	t_const->nbr_filo = ft_atoi(argv[0]);
	t_const->time_to_die = ft_atoi(argv[1]);
	t_const->time_to_eat = ft_atoi(argv[2]);
	t_const->time_to_sleep = ft_atoi(argv[3]);
	if (argv[4])
		t_const->nbr_times_to_eat = ft_atoi(argv[4]);
	else
		t_const->nbr_times_to_eat = false;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nquecedo <nquecedo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:26:00 by nquecedo          #+#    #+#             */
/*   Updated: 2025/02/26 03:02:27 by nquecedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/includes/Philosophers.h"

void ft_print_args(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
	{
		ft_printf("ARGV: %s\n", argv[i]);
		i++;
	}
}

void ft_print_const(t_const *t_const)
{
	printf("=================\n");
	printf("nbr_filos: %d\n", t_const->nbr_filo);
	printf("time_to_die: %d\n", t_const->time_to_die);
	printf("time_to_eat: %d\n", t_const->time_to_eat);
	printf("time_to_sleep: %d\n", t_const->time_to_sleep);
	if (t_const->nbr_times_to_eat)
		printf("nbr_times_to_eat: %d\n", t_const->nbr_times_to_eat);
	printf("=================\n");
}

int	main(int argc, char **argv)
{
	struct s_const t_const;

	(void)t_const;
	argv ++; // Para saltar el nombre del porgrama
	if (ft_check_args(argc, argv) == false)
		return (1);
	ft_init_const(argv, &t_const);
	ft_print_const(&t_const);
	return (0);
}

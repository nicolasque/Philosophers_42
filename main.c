/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nquecedo <nquecedo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:26:00 by nquecedo          #+#    #+#             */
/*   Updated: 2025/02/26 01:23:41 by nquecedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/includes/Philosophers.h"
#include <pthread.h>
#include <sys/time.h>

int	main(int argc, char **argv)
{
	int i = 0;
	if (argc < 4)
	{
		return (1);
	}
	while (i < argc)
	{
		ft_printf("ARGV: %s\n", argv[i]);
		i++;
	}
	return (0);
}

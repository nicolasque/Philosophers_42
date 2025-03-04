/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nquecedo <nquecedo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:23:31 by nquecedo          #+#    #+#             */
/*   Updated: 2025/03/04 03:33:22 by nquecedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Philosophers.h"

long	get_time_ms(void)
{
    struct timeval	time;
    long			milliseconds;

    gettimeofday(&time, NULL);
    milliseconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    return (milliseconds);
}

long int get_time_s(void)
{
	struct timeval	time;
	long	seconds;

	gettimeofday(&time, NULL);
    seconds = time.tv_sec;
	return (seconds);
}

void custom_sleep_ms(long ms)
{
    long time;
    
    // Convertir ms a microsegundos y dividir por 500 para obtener iteraciones
    time = (ms * 1000) / 500;
    
    // Si ms es muy pequeño, al menos ejecutar una vez
    if (time == 0 && ms > 0)
        time = 1;
        
    while (time)
    {
        usleep(500);
        time--;
    }
}
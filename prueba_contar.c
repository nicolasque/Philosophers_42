/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba_contar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nquecedo <nquecedo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:26:00 by nquecedo          #+#    #+#             */
/*   Updated: 2025/02/26 01:21:02 by nquecedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/includes/Philosophers.h"
#include <pthread.h>
#include <sys/time.h>

pthread_mutex_t	mutex;
int				contador = 0;

void	*hilo_funcion(void *arg)
{
	long long int		j;
	double	elapsed;

	j = 0;
	long long sum = 0; // Usamos operaciones matemáticas en lugar de memoria
	struct timeval start, end;
	long seconds, microseconds;
	(void)arg;
	gettimeofday(&start, NULL);
	// Cálculo intensivo sin operaciones de memoria
	for (long long i = 0; i < 9000000000; i++)
	{
		sum += j * j; // Operación matemática simple
		j++;
	}
	gettimeofday(&end, NULL);
	seconds = end.tv_sec - start.tv_sec;
	microseconds = end.tv_usec - start.tv_usec;
	elapsed = seconds + microseconds / 1000000.0;
	pthread_mutex_lock(&mutex);
	printf("Hilo %lu completó el cálculo en %.2f segundos (suma: %lld)\n",
		(unsigned long)pthread_self(), elapsed, sum);
	pthread_mutex_unlock(&mutex);
	return (NULL);
}

int	main(void)
{
	int				nbr_hilos;
	nbr_hilos = 8;
	pthread_t		hilos[nbr_hilos];
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	for (int i = 0; i < nbr_hilos; i++)
		hilos[i] = (pthread_t)NULL;
	printf("Segundos: %ld, Microsegundos: %ld\n", tv.tv_sec, tv.tv_usec);
	pthread_mutex_init(&mutex, NULL);
	for (int i = 0; i < nbr_hilos; i++)
		pthread_create(&hilos[i], NULL, hilo_funcion, NULL);
	for (int i = 0; i < nbr_hilos; i++)
		pthread_join(hilos[i], NULL);
	pthread_mutex_destroy(&mutex);
	return (0);
}

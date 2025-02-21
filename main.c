/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nquecedo <nquecedo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:26:00 by nquecedo          #+#    #+#             */
/*   Updated: 2025/02/21 19:13:03 by nquecedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/includes/Philosophers.h"
#include <pthread.h>
#include <sys/time.h>


pthread_mutex_t mutex;
int contador = 0;

void *hilo_funcion(void *arg) {
	(void)arg;
    pthread_mutex_lock(&mutex);
    contador++;
	usleep(1000000);  // 1 segundo
    printf("Contador: %d\n", contador);
    pthread_mutex_unlock(&mutex);
    return NULL;
}



int main() {
    pthread_t hilos[5];
	struct timeval tv;

    gettimeofday(&tv, NULL);
    for (int i = 0; i < 5; i++)
		hilos[i] = (pthread_t)NULL;
    printf("Segundos: %ld, Microsegundos: %ld\n", tv.tv_sec, tv.tv_usec);


    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < 5; i++)
        pthread_create(&hilos[i], NULL, hilo_funcion, NULL);
    
    for (int i = 0; i < 5; i++)
        pthread_join(hilos[i], NULL);

    pthread_mutex_destroy(&mutex);
    return 0;
}

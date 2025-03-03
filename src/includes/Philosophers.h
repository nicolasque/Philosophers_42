/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nquecedo <nquecedo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:02:04 by nquecedo          #+#    #+#             */
/*   Updated: 2025/03/03 17:34:52 by nquecedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEWMINI_H
# define NEWMINI_H

# include "colors.h"
# include "libft/libft.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

#define PHILO_MAX 300
#define PHILO_LAST -33
#define ALIVE 22
#define DEAD -23

typedef struct s_shared
{
	int				nbr_filo;
	long int				time_to_die;
	long int				time_to_eat;
	long int				time_to_sleep;
	int				nbr_times_to_eat;
	pthread_mutex_t print_mutex;    // Para imprimir mensajes
    pthread_mutex_t death_mutex;
}					t_shared;

typedef struct s_philo
{
	int				id_philo;
	int				fork;
	int				live;
	int				times_eaten;
	size_t			time_star;
	size_t			time_end;
	pthread_t		philo_thread;
	pthread_mutex_t	fork_mutex;
	pthread_mutex_t	sleep_mutex;
	pthread_mutex_t	think_mutex;
	t_shared		*t_shared;
}					t_philo;



// PARSEO

bool				ft_check_nbr(char *str);
bool				ft_chek_individual_arg(char **argv);
bool				ft_check_args(int argc, char **argv);

// INIT
void				ft_init_shared(char **argv, t_shared *t_shared);


//UTILS
	//Prints.c
	void ft_print_shared(t_shared *t_shared);
	void ft_print_args(char **argv);
	void ft_print_philos(t_philo *t_philos);




#endif

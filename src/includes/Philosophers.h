/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nquecedo <nquecedo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:02:04 by nquecedo          #+#    #+#             */
/*   Updated: 2025/03/18 11:48:13 by nquecedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

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

# define PHILO_MAX 800
# define PHILO_LAST -33
# define ALIVE 22
# define DEAD -23
# define TAKE_FORK 50
# define EAT 51
# define SLEEP 52
# define THINK 53
# define DIE_MSG 54
# define ALL_EAT 55

typedef struct s_philo	t_philo;

typedef struct s_shared
{
	int					nbr_filo;
	long int			time_to_die;
	long int			time_to_eat;
	long int			time_to_sleep;
	int					nbr_times_to_eat;
	long long int		program_star_time;
	int					philos_live;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		*forks;
	t_philo				*t_philos;
}						t_shared;

typedef struct s_philo
{
	int					id_philo;
	int					left_fork;
	int					right_fork;
	int					live;
	int					times_eaten;
	long int			last_time_eaten;
	long int			time_end;
	pthread_t			philo_thread;
	t_shared			*t_shared;
}						t_philo;

// PARSEO

bool					ft_check_nbr(char *str);
bool					ft_chek_individual_arg(char **argv);
bool					ft_check_args(int argc, char **argv);

// INIT
void					ft_init_shared(char **argv, t_shared *t_shared);

// UTILS
// Prints.c
void					ft_print_shared(t_shared *t_shared);
void					ft_print_args(char **argv);
void					ft_print_philos(t_philo *t_philos);
void					ft_print_mutex(t_philo *t_philo, char action);

// ft_mutex_destroy.c
void					ft_mutex_destroyer(t_shared *t_shared);
// ft_chak_dead_time.c
int						ft_check_dead_time(t_philo *t_philo);

// get_time.c
long					get_time_micros(void);
long int				get_time_s(void);
long int				get_time_mls(void);
void					custom_sleep_ms(long int time, t_shared *t_shared);

// ACCTIONS
void					ft_eat(t_philo *t_philo);
void					ft_sleep(t_philo *t_philo);
void					ft_think(t_philo *t_philo);
int						ft_is_philos_dead(t_shared *t_shared);

#endif // PHILOSOPHERS_H
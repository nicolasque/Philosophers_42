/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nquecedo <nquecedo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:02:04 by nquecedo          #+#    #+#             */
/*   Updated: 2025/02/26 02:51:49 by nquecedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEWMINI_H
# define NEWMINI_H

# include "libft/libft.h"
# include "colors.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_const
{
	int		nbr_filo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nbr_times_to_eat;
}						t_const;

//PARSEO
bool ft_check_nbr(char *str);
bool	ft_chek_individual_arg(char **argv);
bool	ft_check_args(int argc, char **argv);


//INIT
void ft_init_const(char **argv, t_const *t_const);


#endif

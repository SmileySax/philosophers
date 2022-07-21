/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:37:27 by keaton            #+#    #+#             */
/*   Updated: 2022/07/21 23:15:59 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <signal.h>

typedef struct s_pinfo{
	int				*info;
	int				full;
	sem_t			*sem_fork;
	sem_t			*sem_possible;
	sem_t			**sem_mt;
	sem_t			*sem_full;
	sem_t			*sem_report;
	int				ph_nbr;
	int				meals;
	int				*pid;
	struct timeval	last_meal;
	struct timeval	start_time;
}				t_pinfo;

int		ft_close_sems(t_pinfo *pinfo);
int		ft_free_ip(int *i, t_pinfo *p);
int		ft_usleep(int delay);
int		ft_atoi(const char *str);
int		ft_check_info(int *info, int flag);
int		**ft_fill_info(char **argv, int **info);
void	ft_pinfo_init(t_pinfo *pinfo, int *info);
t_pinfo	ft_init_values(t_pinfo *pinfo, char **argv);
void	ft_report(const char *words, t_pinfo *pinfo, int stop);
void	ft_eat(t_pinfo *pinfo);
int		ft_check_death(t_pinfo *pinfo);
void	*monitoring(void *arg);
int		ft_philo(t_pinfo pinfo, int i);
void	ft_lets_eat(t_pinfo pinfo);
int		main(int argc, char **argv);
int		ft_deccount(int n);
char	*ft_itoa(int n, char *num);
char	*ft_set_sem_name(t_pinfo pinfo, int i);
void	ft_kill_n_finish(t_pinfo *pinfo, int i);
int		ft_sleep_n_think(t_pinfo *pinfo);

#endif

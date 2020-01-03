/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 21:14:07 by toliver           #+#    #+#             */
/*   Updated: 2019/12/18 01:02:31 by jates-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_usage(void)
{
	ft_dprintf(2, "usage: ./asm [-%s] file[.s] ...\n", FLAGS);
	exit(0);
}

void		ft_wrong_flag(t_env *env, char c)
{
	ft_dprintf(2, "%s: illegal option -- %c\n", env->prog_name, c);
	ft_usage();
}

void		ft_crash(int error)
{
	t_env		*env;
	t_program	*prog;

	env = ft_get_env();
	prog = ft_get_prog();
	ft_dprintf(2, "%s: ", env->prog_name);
	if (error == MALLOC_FAIL)
		ft_dprintf(2, "malloc failed: %s\n", strerror(errno));
	ft_free_env(env);
	ft_free_prog(prog);
	exit(0);
}

int		ft_error(t_env *env, t_file *file, int error)
{
	(void)error;
	ft_dprintf(2, "%s: %s: %s\n", env->prog_name, file->filename, strerror(errno));
	file->mode = CRASH;
	return (0);
}



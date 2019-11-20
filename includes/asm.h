/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:18:38 by toliver           #+#    #+#             */
/*   Updated: 2019/11/20 23:03:18 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/errno.h>
#include <fcntl.h>
#include "libft.h"
#include "libftprintf.h"


#define FLAGS "a"


enum mode 
{
	CRASH,
	PARSING_ARGS,
	PARSING_FLAGS,
	PARSING_FILES
};

enum error
{
	NO_PARAMS,
	WRONG_FLAGS,
};

typedef struct		s_error
{
	int				value;
	char			flag_error;
}					t_error;

typedef struct		s_env
{
	char			*prog_name;
	int				mode;
	t_error			error;
	int				flags;
}					t_env;
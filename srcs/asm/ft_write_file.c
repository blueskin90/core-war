/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jates- <jates-@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 03:10:28 by jates-            #+#    #+#             */
/*   Updated: 2019/12/20 01:03:13 by jates-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*ft_cor_filename(t_file *file)
{
	const int	len = ft_strlen(file->filename);
	char		*corname;

	corname = NULL;
	if (len > 2 && file->filename[len - 2] == '.'
	&& file->filename[len - 1] == 's' && file->filename[len] == 0)
	{
		if ((corname = ft_strnew(len + 2)) 
		&& ft_strncpy(corname, file->filename, len - 1))
			return(ft_strcat(corname, "cor"));
	}
	else
	{
		if ((corname = ft_strnew(len + 4)) 
		&& ft_strncpy(corname, file->filename, len))
			return (ft_strcat(corname, ".cor"));
	}
	ft_crash(MALLOC_FAIL);
	return (corname);
}

void	write_hexlen(int fd, size_t size, int len)
{
	unsigned char	*tmp;
	int				i;

	i = len;
	if (!(tmp = (unsigned char*)ft_memalloc(i * sizeof(unsigned char))))
		return ;
	while (size && i > 0)
	{
		tmp[--i] = size % 256;
		size /= 256;
	}
	write(fd, tmp, len);
	ft_memdel((void**)&tmp);
}

void	ft_write_head(t_program *prog)
{
	write_hexlen(prog->fd, COREWAR_EXEC_MAGIC, 4);
	write(prog->fd, prog->header.prog_name, PROG_NAME_LENGTH);
	write_hexlen(prog->fd, prog->header.prog_size, 8);
	write(prog->fd, prog->header.comment, COMMENT_LENGTH);
	write(prog->fd, "\0\0\0\0", 4);
}

int	ft_pass_newline(t_file *file, t_token **token)
{
	t_token		*tmp;

	if (!*token)
		return(ft_syntax_error(file, *token));
	if ((*token)->type != NEWLINE)
		return (1);
	tmp = (*token)->next;
	while (tmp)
	{
		*token = tmp;
		if (tmp->type != NEWLINE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_pass_comm(t_file *file, t_token **token)
{
	t_token		*tmp;

	if (!*token)
		return(ft_syntax_error(file, *token));
	if ((*token)->type != COMMENT)
		return (1);
	tmp = (*token)->next;
	while (tmp)
	{
		*token = tmp;
		if (tmp->type != COMMENT)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_pass_newline_comm(t_file *file, t_token **token)
{
	t_token		*tmp;

	if (!*token)
		return(ft_syntax_error(file, *token));
	if ((*token)->type != NEWLINE && (*token)->type != COMMENT)
		return (1);
	tmp = (*token)->next;
	while (tmp)
	{
		*token = tmp;
		if (tmp->type != NEWLINE && tmp->type != COMMENT)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_init_prog(t_env *env, t_file *file)
{
	t_program	champ;
	int		ret;

	ft_bzero(&champ, sizeof(t_program));
	ret = 0;
	if (!(champ.filename = ft_cor_filename(file)) || !ft_check_header(file)\
		|| !ft_check_body(file, &champ) || !ft_check_labels(file, &champ, file->tokens))
	{
		free(champ.filename);
		return (0);
	}
	return (0); //stop for now
	if ((champ.fd = open(champ.filename, O_WRONLY | O_CREAT, 0755) < 0))
	{	
		free(champ.filename);
		return (ft_error(env, file, OPEN_ERROR));
	}
	close(champ.fd);
	return (1);
}


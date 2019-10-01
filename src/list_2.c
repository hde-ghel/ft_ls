/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 20:35:53 by hde-ghel          #+#    #+#             */
/*   Updated: 2019/09/19 13:57:07 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_list_ls	*malloc_error(t_arg_ls *arg)
{
	arg->malloc_error = 1;
	return (NULL);
}

t_list_ls	*check_sort(t_list_ls *mylist, t_arg_ls *arg)
{
	mylist = sort_ascii(mylist);
	if (arg->is_t == 1)
		mylist = sort_time(mylist);
	if (arg->is_r == 1)
		mylist = reverse_list(mylist);
	return (mylist);
}

t_list_ls	*add_no_file(t_list_ls *mylist, char *str)
{
	t_list_ls	*tmp;

	if (!(tmp = ft_memalloc(sizeof(t_list_ls))))
		return (NULL);
	if (!(tmp->file_name = ft_strdup(str)))
		return (NULL);
	tmp->next = mylist;
	return (tmp);
}

void		print_delete(t_list_ls *mylistfile)
{
	t_list_ls	*tmp;

	mylistfile = sort_ascii(mylistfile);
	tmp = mylistfile;
	while (tmp != NULL)
	{
		ft_putstr_fd("./ft_ls: ", 2);
		ft_putstr_fd(tmp->file_name, 2);
		ft_putstr_fd(":no such file or directory\n", 2);
		tmp = tmp->next;
	}
	while (mylistfile)
	{
		tmp = mylistfile->next;
		ft_strdel(&mylistfile->file_name);
		free(mylistfile);
		mylistfile = tmp;
	}
}

int			no_file(char **argv, int i, int argc, t_arg_ls *arg)
{
	t_list_ls	*mylistfile;
	struct stat	fs;

	mylistfile = NULL;
	while (i < argc)
	{
		if (lstat(argv[i], &fs) < 0)
		{
			if (!(mylistfile = add_no_file(mylistfile, argv[i])))
				return (-1);
			arg->count++;
		}
		i++;
	}
	print_delete(mylistfile);
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_base.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:57:16 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/12 16:57:58 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_BASE_H
# define MINI_BASE_H

# include <stdlib.h>
# include <stdio.h>
# include <libft.h>
# include <readline/readline.h>
# include <signal.h>
# include <readline/history.h>
# include <unistd.h>
# include <utils.h>

typedef enum s_bool
{
	false,
	true
}	t_bool;

void	signals_setup(void);

#endif
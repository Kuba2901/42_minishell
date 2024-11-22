/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:56:48 by jnenczak          #+#    #+#             */
/*   Updated: 2024/11/14 18:09:44 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

static void log_message(t_log_level level, const char *msg) {
	const char	*color_code;
	
	if (level == LOG_DEBUG)
		color_code = COLOR_DEBUG;
	else if (level == LOG_WARNING)
		color_code = COLOR_WARNING;
	else if (level == LOG_ERROR)
		color_code = COLOR_ERROR;
	else if (level == LOG_SUCCESS)
		color_code = COLOR_SUCCESS;
	else
		color_code = COLOR_RESET;
	printf("%s", color_code);
	printf("%s", msg);
	printf("%s\n", COLOR_RESET);
}

void	log_error(const char *msg)
{
	log_message(LOG_ERROR, msg);
}

void	log_success(const char *msg)
{
	log_message(LOG_SUCCESS, msg);
}

void	log_warning(const char *msg)
{
	log_message(LOG_WARNING, msg);
}

void	log_debug(const char *msg)
{
	log_message(LOG_DEBUG, msg);
}
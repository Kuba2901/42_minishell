#ifndef UTILS_H
# define UTILS_H

# define COLOR_RESET "\033[0m"
# define COLOR_DEBUG "\033[36m"   // Cyan
# define COLOR_WARNING "\033[35m" // Yellow
# define COLOR_ERROR "\033[31m"   // Red
# define COLOR_SUCCESS "\033[32m" // Green


# include <stdio.h>
# include <stdarg.h>

typedef enum	s_log_level {
	LOG_DEBUG,
	LOG_WARNING,
	LOG_ERROR,
	LOG_SUCCESS
}	t_log_level;

void	log_debug(const char *msg);
void	log_warning(const char *msg);
void	log_success(const char *msg);
void	log_error(const char *msg);

#endif
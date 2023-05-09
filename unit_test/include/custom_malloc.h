/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   custom_malloc.h                                 |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 13:35:49 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 13:35:49 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUSTOM_MALLOC_H
# define CUSTOM_MALLOC_H
# ifdef __linux__
# define _GNU_SOURCE
# endif

# include <stddef.h>
# include <dlfcn.h>
// Custom malloc function
void *custom_malloc(size_t size);

// Set malloc failure condition
void set_malloc_failure_condition(int condition);

void activate_malloc_hook(void);
void deactivate_malloc_hook(void);

int get_malloc_failure_condition(void);
#endif // CUSTOM_MALLOC_H

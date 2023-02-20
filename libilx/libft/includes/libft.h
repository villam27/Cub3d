/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:08:45 by lcrimet           #+#    #+#             */
/*   Updated: 2022/12/09 13:20:22 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include <stdint.h>
# if defined(_WIN32)
#  include <io.h>
# else
#  include <unistd.h>
# endif
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
size_t			ft_strlen(const char *s);
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
size_t			ft_strlcat(char *dst, char *src, size_t size);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
char			*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
int				ft_atoi(const char *str);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strdup(const char *s1);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char *c);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
void			ft_putchar_fd(char c, int fd);
int				ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
void			ft_count(char *str, int *i, int *cmpt, char *c);
void			ft_freeall(char **tab);
char			*ft_convert_base(char *nbr, char *base_from, char *base_to);
void			ft_rverse_str(char *str, int size);
int				ft_bad_base_atoi(char *base);
int				ft_in_base(char *base, char c);
int				ft_num_from_base(char *str, char *base, int i);
char			*ft_dec2hex_ul(unsigned long n, char *str);
char			*ft_dec2hex_u(unsigned int n, char *str);
void			ft_putnbr_u(unsigned int n, int *i);
int				ft_print_c(va_list *lst);
int				ft_print_str(va_list *lst);
int				ft_print_ptr(va_list *lst);
int				ft_print_signed_i(va_list *lst);
int				ft_printf(const char *str, ...);
void			ft_putnbr(int n, int *i);
void			ft_rverse_str(char *str, int size);
char			ft_is_newline(const char *str);
void			ft_init_buffer(char *buffer, int j);
char			*get_next_line(int fd);
uint32_t		ft_atoui_base(char *str, char *base, char *base2);
int				ft_is_in_str(char c, char *str);
char			*ft_strcpy(char *dest, char *src);
char			*ft_strcat(char *dest, char *src);

#endif

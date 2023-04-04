/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:22:17 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/10/03 14:22:19 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H

int		ft_isalnum(int ch);
int		ft_isascii(int ch);
int		ft_isalpha(int ch);
int		ft_isdigit(int ch);
int		ft_isprint(int ch);
int		ft_strlen(const char *str);
int		ft_strlcpy(char *dest, const char *src, unsigned int size);
int		ft_strlcat(char *dest, const char *src, unsigned int size);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
int		ft_tolower(int ch);
int		ft_toupper(int ch);
int		ft_atoi(char *str);
long	ft_int_atoi(char *str);
char	*ft_itoa(int n);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, unsigned int len);
void	ft_bzero(void *s, unsigned int n);
void	*ft_calloc(unsigned int nmemb, unsigned int size);
void	*ft_memchr(const void *s, int c, unsigned int n);
int		ft_memcmp(const void *s1, const void *s2, unsigned int n);
void	*ft_memcpy(void *dest, const void *src, unsigned int n);
void	*ft_memmove(void *dest, const void *src, unsigned int n);
void	*ft_memset(void *s, int c, unsigned int n);
char	*ft_substr(char const *s, unsigned int start, unsigned int len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(const char *s1, const char *set);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_printf(const char *str, ...);
char	*get_next_line(int fd);

typedef struct s_stack
{
	int		x;
	void	*next;
}	t_stack;

int		ft_lstsize(t_stack *lst);
t_stack	*ft_lstnew(int content);
t_stack	*ft_lstlast(t_stack *lst);
void	ft_lstadd_front(t_stack **lst, t_stack *new);
void	ft_lstadd_back(t_stack **lst, t_stack *new);
void	ft_lstdelone(t_stack *lst, void (*del)(int));
void	ft_lstclear(t_stack **lst, void (*del)(int));
void	ft_lstiter(t_stack *lst, void (*f)(int));
t_stack	*ft_lstmap(t_stack *lst, int (*f)(int), void (*del)(int));

#endif

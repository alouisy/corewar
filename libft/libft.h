/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 09:52:18 by zcugni            #+#    #+#             */
/*   Updated: 2017/11/20 09:42:28 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFF_SIZE 320
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <inttypes.h>

/*
**struct for libft
*/
typedef	struct				s_trim
{
	int start;
	int end;
}							t_trim;

typedef struct				s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}							t_list;

typedef struct				s_char_arr
{
	char	**arr;
	int		len;
}							t_char_arr;

typedef struct				s_bubble_sort
{
	t_list	*first_el;
	t_list	*second_el;
	t_list	*prev_el;
	int		sorted;
}							t_bubble_sort;

/*
**struct for printf
*/
typedef struct				s_conv_info
{
	int		rest;
	int		is_neg;
	char	current_value;
}							t_conv_info;

typedef struct				s_result
{
	char	**str;
	size_t	size;
}							t_result;

typedef struct				s_detail
{
	int			width;
	int			pre;
	t_result	*conv;
	t_list		*info;
	char		*ori_str;
}							t_detail;

typedef struct				s_pos
{
	int	start;
	int	mid;
	int i;
}							t_pos;

/*
**struct for tree
*/
typedef struct				s_tree_index
{
	int		nb;
	char	*str;
	int		is_nb;
}							t_tree_index;

typedef struct				s_rbt_node
{
	void				*content;
	int					red;
	t_tree_index		index;
	struct s_rbt_node	*parent;
	struct s_rbt_node	*left_child;
	struct s_rbt_node	*right_child;
}							t_rbt_node;

typedef unsigned char		t_u_char;
typedef unsigned int		t_u_int;
typedef	unsigned long long	t_ull;

/*
**Str
*/
char						*ft_strcat(char *s1, const char *s2);
char						*ft_strchr(const char *s, int c);
int							ft_strchri(const char *s, int c);
void						ft_strclr(char *s);
char						*ft_strcpy(char *dst, const char *src);
int							ft_strcmp(const char *s1, const char *s2);
void						ft_strdel(char **as);
void						free_str_arr(t_char_arr *str_arr);
char						*ft_strdup(const char *s1);
int							ft_strequ(char const *s1, char const *s2);
void						ft_striter(char *s, void (*f)(char *));
void						ft_striteri(char *s, void (*f)(t_u_int, char *));
char						*ft_strjoin(char const *s1, char const *s2);
char						*ft_strjoin_free(char *s1, char *s2,
	int side_to_free);
size_t						ft_strlcat(char *dst, const char *src, size_t size);
size_t						ft_strlen(const char *s);
char						*ft_strmap(char const *s, char (*f)(char));
char						*ft_strmapi(char const *s,
	char (*f)(t_u_int, char));
char						*ft_strncat(char *s1, const char *s2, size_t n);
int							ft_strncmp(const char *s1, const char *s2,
	size_t n);
char						*ft_strncpy(char *dst, const char *src, size_t len);
char						*ft_strndup(const char *s1, size_t n);
int							ft_strnequ(char const *s1, char const *s2,
	size_t n);
char						*ft_strnew(size_t size);
char						*ft_strnstr(const char *haystack,
	const char *needle, size_t len);
char						*ft_strrchr(const char *s, int c);
char						**ft_strsplit(char const *s, char c);
char						*ft_strstr(const char *haystack,
	const char *needle);
char						*ft_strsub(const char *s, t_u_int start,
	size_t len);
char						*ft_strsub_free(char *s, t_u_int start, size_t len);
char						*ft_strtrim(char const *s);
int							ft_toupper(int c);
int							ft_tolower(int c);
int							is_strdigit(char *str, int accept_neg);
char						*join_parts(t_char_arr *str_parts,
													char *sep, int limit);
char						**ft_strsplit_white(char const *s);
/*
**Lst
*/
void						ft_lstadd(t_list **alst, t_list *new);
void						ft_lstappend(t_list **alst, t_list *new);
t_list						*ft_lstcpy(t_list *ori);
void						ft_lstdel(t_list **alst,
												void (*del)(void *, size_t));
void						ft_lstdelone(t_list **alst,
												void (*del)(void *, size_t));
t_list						*ft_lstfind(t_list *list, void *content,
															size_t size);
int							lst_findi(t_list *list, void *content, size_t size);
void						ft_lstiter(t_list *lst, void (*f)(t_list *elem));
int							ft_lstlength(t_list *lst);
t_list						*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list						*ft_lstnew(void const *content,
														size_t content_size);
t_list						*ft_lstnew_pointer(void *content,
														size_t content_size);
void						lst_clr(t_list **lst);
char						*lst_to_str(t_list *lst);
t_list						*ft_pop(t_list **lst);
int							ft_pop_value(t_list **lst);
t_list						*lst_pop_pointer(t_list **lst);
t_list						*lstp_pop_at(t_list **lst, void *p);
void						bubble_sort_lst(t_list **lst,
												int (*get_nb)(t_list *lst));
void						remove_first_elem(t_list **lst);
void						lst_partial_clr(t_list **lst);
/*
**Tree
*/
t_rbt_node					*find_in_tree(t_rbt_node *rbt,
												t_tree_index searched_index);
void						rotate(t_rbt_node *node, int rotate_right);
t_rbt_node					*new_rbt_node(void *content, t_tree_index index);
void						insert_rbt(t_rbt_node **rbt, t_rbt_node *current,
															t_rbt_node *new);
int							is_inf(t_tree_index rbt_index_1,
													t_tree_index rbt_index_2);
t_rbt_node					*rearrange(t_rbt_node *node);
void						display_tree_id(t_rbt_node *rbt);
void						rbt_clear(t_rbt_node **rbt,
									void (*free_content)(void *content));
/*
**IO
*/
void						ft_putchar(char c);
void						ft_putchar_fd(char c, int fd);
void						ft_putendl(char const *s);
void						ft_putendl_fd(char const *s, int fd);
void						ft_putnbr(int n);
void						ft_putnbr_fd(int n, int fd);
void						ft_putstr(const char *str);
void						ft_putstr_fd(char const *s, int fd);
int							get_next_line(const int fd, char **line,
	char separator);
void						exit_error(char *msg, int code);
/*
**Mem
*/
void						ft_bzero(void *s, size_t n);
void						*ft_memalloc(size_t size);
int							ft_memcmp(const void *s1, const void *s2, size_t n);
void						*ft_memccpy(void *dst, const void *src, int c,
	size_t n);
void						*ft_memchr(const void *s, int c, size_t n);
void						*ft_memcpy(void *dst, const void *src, size_t n);
void						ft_memdel(void **ap);
void						*ft_memmove(void *dst, const void *src, size_t len);
void						*ft_memset(void *b, int c, size_t len);
void						get_leaks(char *msg);
/*
**Ft_printf
*/
int							ft_printf(const char *str, ...);
void						convert(va_list ap, t_detail *conv_detail);
char						*convert_s(char *str, int precision);
t_result					*convert_ls(wchar_t *nb_arr);
char						*convert_signed(long long nb);
char						*convert_unsigned(t_ull nb);
char						*convert_lc(wchar_t nb);
char						*convert_c(char c);
void						get_info(t_pos *p, t_detail *conv_detail,
	va_list ap);
int							get_nb(const char *str, int *i);
int							get_precision(const char *str, int *i);
void						get_width_modifier(const char **str,
	t_list **info, int *i);
void						add(t_detail *det, t_list **fin_lst, int add_null);
void						act_on_flag(t_detail *conv_detail);
void						pad_width(t_detail *conv_detail, char chara,
	int right);
void						pad_precision(t_detail conv_detail, char type);
char						*ft_itoa_base_long(unsigned long nb,
	int base, int upper);
char						*ft_itoa_base_2_long(t_ull nb, int base, int upper);
char						*ft_itoa_base_uintmax(uintmax_t nb, int base,
	int upper);
long						ft_atoi_long(char *str);
long long					ft_atoi_2_long(char *str);
int							display(t_list *final_lst, int error);
/*
**Misc
*/
long long					ft_atoi(char *str);
long long					ft_atoi_harsh(char *str, int accept_neg);
int							ft_isascii(int c);
int							ft_isalnum(int c);
int							ft_isalpha(int c);
int							ft_isdigit(int c);
int							ft_isprint(int c);
int							ft_iswhitespace(int c);
char						*ft_itoa(long long nb);
char						*ft_itoa_base(unsigned int nb, int base, int upper);
long long					ft_pow(int nb, int power);
int							is_neg(char *str);

#endif

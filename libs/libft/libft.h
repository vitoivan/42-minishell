/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 15:21:11 by victor            #+#    #+#             */
/*   Updated: 2022/08/07 08:32:48 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/* Check for an alphabetic character */
int					ft_isalpha(int n);

/* Check for a digit */
int					ft_isdigit(int ch);

/* Check for an alphanumeric character */
int					ft_isalnum(int ch);

/* Check if a character is between 0 and 127 */
int					ft_isascii(int c);

/* Checks for any printable character */
int					ft_isprint(int c);

/* Get a length of the passed string */
size_t				ft_strlen(const char *s);

/* Fill the first N bytes of the memory area with a passed character */
void				*ft_memset(void *str, int c, size_t n);

/* Fill ne first N bytes of the memory area with a null character */
void				ft_bzero(void *s, size_t n);

/* Copy N bytes from the src to dst, the memory areas may NOT overlap */
void				*ft_memcpy(void *dst, const void *src, size_t n);

/* Copy N bytes from the src to dst, the memory areas can or not overlap */
void				*ft_memmove(void *dst, const void *src, size_t n);

/*
   Copy N characters from src to dst string
   guaranteeing the null byte at the end
*/
size_t				ft_strlcpy(char *dst, const char *src, size_t size);

/* 
   Concatenate the src to dst, size is the buffer (like an sizeof(dst))
   if dst_len >= size, the buffer is full so do nothing
*/
size_t				ft_strlcat(char *dst, const char *src, size_t size);

/* Put some char to uppercase */
int					ft_toupper(int c);

/* Put some char to lowercase */
int					ft_tolower(int c);

/* Return a pointer to a first ocurrence of a char in a string */
char				*ft_strchr(const char *s, int c);

/* 
   Return a pointer to a last ocurrence of a char in a string or
   return a first ocurrence (back to front)
*/
char				*ft_strrchr(const char *s, int c);

/* 
   Compare the first N characters of two strings
   if are equal, return 0
   if first > second, return 1
   if second > first, return -1
*/
int					ft_strncmp(const char *s1, const char *s2, size_t n);

int					ft_strcmp(const char *s1, const char *s2);

/* Return a first ocurrence of a number C in N bytes */
void				*ft_memchr(const void *s, int c, size_t n);

/*
   Compare the first N bytes of two memory areas
   if are equal, return 0
   if first > second, return 1
   if second > first, return -1
*/
int					ft_memcmp(const void *s1, const void *s2, size_t n);

/*
   Return a pointer to the first ocurrence of a substring
   in a bigger string. If there's not, return NULL
*/
char				*ft_strnstr(const char *big, const char *little,
						size_t len);

/* Convert a number string to an integer */
int					ft_atoi(const char *nptr);

/* Alocate memory and fills it with null characters */
void				*ft_calloc(size_t nmemb, size_t size);

/* Duplicate a string */
char				*ft_strdup(const char *s);

/* Create a substring of other string */
char				*ft_substr(const char *s, unsigned int start, size_t len);

/* Join two strings */
char				*ft_strjoin(const char *s1, const char *s2);

/* Create a substring without a set of values at the ends of the string */
char				*ft_strtrim(const char *s1, const char *set);

/* Return an array with the splitted str */
char				**ft_split(char const *s, char c);

/* Transform a integer to an char array */
char				*ft_itoa(int n);

/* 
 * Apply a function in every character of an string, 
 * and return the new string with the callback modifications */
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/* Apply a function to every character of an string array,
 * but do not return anything */
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

/* Write an char in a File Descriptior */
void				ft_putchar_fd(char c, int fd);

/* Write an string in a file descriptor */
void				ft_putstr_fd(char *s, int fd);

/* Write an string + \n in a file descriptor */
void				ft_putendl_fd(char *s, int fd);

/* Write an number in a file descriptor */
void				ft_putnbr_fd(int n, int fd);

/* Create an list (structure) and return a pointer to it */
t_list				*ft_lstnew(void *content);

/* Add a new list (structure) to the begin of that linked list */
void				ft_lstadd_front(t_list **lst, t_list *new);

/* Return the size of an linked list */
int					ft_lstsize(t_list *lst);

/* Return a pointer to the last element of an linked list */
t_list				*ft_lstlast(t_list *lst);

/* Add a new list (structure) to the end of an linked list */
void				ft_lstadd_back(t_list **lst, t_list *new);

/* Delete a content of an node of the linked list */
void				ft_lstdelone(t_list *lst, void (*del)(void *));

/* Delete the content and the node of an linked
 * list from the passed node to the end */
void				ft_lstclear(t_list **lst, void (*del)(void *));

/* Apply a function in every node content of an linked list */
void				ft_lstiter(t_list *lst, void (*f)(void *));

/* Apply a function to every single node content of an linked list,
 * and return a new list with the modifications */
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

int					ft_printf(const char *str, ...);
#endif

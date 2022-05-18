/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vectors.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 13:47:30 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/18 13:40:58 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

typedef struct s_vector_double
{
	double	x;
	double	y;
}				t_vector_double;

typedef struct s_vector_int
{
	int	x;
	int	y;
}				t_vector_int;

typedef struct s_segment
{
	t_vector_double	p_0;
	t_vector_double	p_1;
}		t_segment;

typedef struct s_line
{
	double	a;
	double	b;
	double	c;
}	t_line;

typedef struct s_segment_intersect
{
	t_segment	s1;
	t_segment	s2;
	t_segment	s3;
	t_segment	ray;
	t_line		l1;
	t_line		l2;
}			t_intersect;

#endif
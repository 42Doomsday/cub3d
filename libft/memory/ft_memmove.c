/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: clouden <clouden@student.42madrid.com	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/04/14 13:05:33 by clouden		   #+#	#+#			 */
/*   Updated: 2025/10/15 14:13:29 by clouden          ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <libft.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (n == 0 || d == s)
		return (dest);
	if (s < d)
	{
		i = n;
		while (i--)
			d[i] = s[i];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void test_memmove(const char *label, char *buffer1, char *buffer2, void *src,\
				 size_t n, size_t offset_dest, size_t print_len)
{
	char *dest1 = buffer1 + offset_dest;
	char *dest2 = buffer2 + offset_dest;

	void *ret1 = ft_memmove(dest1, src, n);
	void *ret2 = memmove(dest2, src, n);

	printf("--- %s ---\n", label);

	// Check returned pointer
	if (ret1 != dest1)
		printf("ft_memmove returned wrong pointer\n");
	if (ret2 != dest2)
		printf("memmove returned wrong pointer (this should not happen!)\n");

	// Compare memory content
	if (memcmp(buffer1, buffer2, print_len) == 0)
		printf("PASS: Memory content matches.\n");
	else {
		printf("FAIL: Memory content differs.\n");
		printf("Expected: \"%.*s\"\n", (int)print_len, buffer2);
		printf("Got	 : \"%.*s\"\n", (int)print_len, buffer1);
	}
	printf("\n");
}

int main(void)
{
	char src[] = "lorem ipsum dolor sit amet";

	// buffers for comparison
	char buf1[64];
	char buf2[64];

	// Test 1: Overwrite with literal "consectetur" (5 bytes)
	strcpy(buf1, src);
	strcpy(buf2, src);
	test_memmove("Test 1: overwrite with \"consectetur\" (5 bytes)",\
			 buf1, buf2, "consectetur", 5, 1, 22);

	// Test 2: Copy with embedded nulls "con\0sec\0\0te\0tur" (10 bytes)
	strcpy(buf1, src);
	strcpy(buf2, src);
	test_memmove("Test 2: copy with null bytes", buf1, buf2, \
				"con\0sec\0\0te\0tur", 10, 1, 22);

	// Test 3: Overlapping src < dest
	strcpy(buf1, src);
	strcpy(buf2, src);
	test_memmove("Test 3: overlapping src < dest", buf1, buf2, src, 8, 1, 22);

	// Test 4: Overlapping src > dest
	strcpy(buf1, src);
	strcpy(buf2, src);
	test_memmove("Test 4: overlapping src > dest", buf1, buf2, buf1 + 1,\
				 8, 0, 22);

	// Test 5: Zero-length move
	strcpy(buf1, src);
	strcpy(buf2, src);
	test_memmove("Test 5: zero-length move", buf1, buf2, buf1 + 1, 0, 0, 22);

	return 0;
}

int	main(void)
{
	int ft_src[7] = {1,20,300,4000,50000,600000,7000000};
	int *ft_dest = ft_src + 2;
	int src[7] = {1,20,300,4000,50000,600000,7000000};
	int *dest = src + 2;
	int i;

	ft_memmove(ft_dest, ft_src, sizeof(int) * 7);
	memmove(dest, src, sizeof(int) * 7);
	for (i = 0; i < 7; i++)
	{
		printf("ft_dest[%d]: %d\n", i, ft_dest[i]);
		printf("dest[%d]:	%d\n", i, dest[i]);
	}
	
	char src[] = "lorem upsum dolor sit amet";
	char *dest;	

	write(1, ft_memmove(dest, "consectetur", 5) , 22);
	write(1, memmove(dest, "consectetur", 5), 22);
	write(1, "\n", 1);

	write(1, ft_memmove(dest, "con\0sec\0\0te\0tur", 10), 22);	
	write(1, memmove(dest, "con\0sec\0\0te\0tur", 10), 22);
	write(1, "\n", 1);
	
		

	return (0);
}
*/

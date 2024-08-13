#include "libft.h"

void *ft_realloc(void *ptr, size_t newSize)
{
	void	*newPtr;

	newPtr = malloc(newSize);
	if (!newPtr)
	{
		return (NULL); // Allocation failed
	}
	if (newSize > 0 && ptr != NULL) {
		size_t minSize = newSize < sizeof(*ptr) ? newSize : sizeof(*ptr);
		ft_memcpy(newPtr, ptr, minSize);
	}
	free(ptr); // Free the old block
	return (newPtr);
}
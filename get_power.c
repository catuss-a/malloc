
#include <math.h>
#include <stdlib.h>

int                     get_power(size_t size)
{
  int                   p;

  p = 0;
  while (p < 32)
    {
      if (size < (size_t)pow(2, p))
        return (p);
      ++p;
    }
  return (-1);
}

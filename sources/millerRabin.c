#include "millerRabin.h"
#include "error.h"


int witness(__uint64_t a, __uint64_t n)
{
	__uint64_t m = n-1;
	__uint64_t y = 1;
	__uint64_t b;

	while (m != 0)
	{
		if (m%2 == 1)
		{
			y = (a*y) % n;
			m = m-1;
		}
		else
		{
			b = a;
			a = (a*a) % n;
			if (a==1 && b!=1 && b!=n-1) {
			// b est une racine carre non triviale de 1
			return 1;		// n est composé
			}
			m = m/2;
		}
	}
	if (y != 1)
		return 1;			// n est composé
	else
		return 0;
}

int millerWitness(__uint64_t base, __uint64_t number)
{
	__uint64_t s;
	__uint64_t d;
	__uint64_t x;

	d = number - 1;
	s = 0;
	while (d % 2 == 0)
	{
		s++;
		d /= 2;
	}
//	ft_printf("2 ^ %llu * %llu = %llu\n", s, d, number);
	x = modularPow(base, d, number);
//	ft_printf("%llu ^ %llu %% %llu = %llu\n", base, d, number, x);
	if (x == base || x == number-1)
	{
		return 0;
	}
	while (s > 1)
	{
		x = modularPow(x, 2, number);
		if (x == (number - 1))
		{
			return 0;
		}
		s = s - 1;
	}
//	ft_printf("find witness\n");
	return 1;
}

int millerRabin(__uint64_t number, __uint64_t k)
{
	__uint64_t base;
	int first;

	if (number < 3)
		return 0;
	if (number % 2  == 0)
		return 0;
	first = 1;
	while (k > 0)
	{
		base = randomInt64(2, number - 2);
		if (witness(base, number))
			return 0;
		if (first)
		{
			first = 0;
			ft_printf(".");
		}
		k--;
		ft_printf("+");
	}
	ft_printf("\n");
	return 1;
}

int kByAccuracy(float accuracy)
{
	int k;
	float errorProb;

	k = 1;
	errorProb = 0.25;
	while (errorProb > (1 - accuracy))
	{
		errorProb /= 4;
		k++;
	}
	return k;
}

int ft_ssl_is_primary(__uint64_t number, float probability)
{
	int k;

	k = kByAccuracy(probability);
	//ft_printf("test miller-rabin with k = %d (prob = %f)\n", k, probability);
	return millerRabin(number, k);
}

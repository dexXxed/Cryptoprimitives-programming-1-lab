#include "PolynomUtilities.h"

int degree(M_LONG a)
{
	for (int i = 32 * a[0] - 1; i >= 0; i--)
		if ((a[i / 32 + 1] >> (i % 32)) & 1)
			return i;
	return -1;
}

void printPolynom(M_LONG a)
{
	int maximum = degree(a);
	if (maximum < 0) {
		cout << "0" << endl;
		return;
	}
	if (maximum)
		cout << "t^" << maximum;
	for (int i = maximum - 1; i > 0; i--)
	{
		if ((a[i / 32 + 1] >> (i % 32)) & 1)
		{
			cout << " + " << "t^" << i;
		}
	}
	if (maximum && (a[1] & 1))
		cout << " + 1";
	else if (a[1] & 1)
		cout << "1";
	cout << endl;
}

/*void printPolynomBin(M_LONG a)
{
int firstNotZerro = a[0];
while (firstNotZerro > 0 && a[firstNotZerro] == 0)
firstNotZerro--;
if (!firstNotZerro)
{
cout << '0' << endl;
return;
}

int j = 31;
for (; ((a[firstNotZerro] >> j) & 1) == 0; j--);

for (int i = a[0]; i > 0; i--)
{
for (; j >= 0; j--)
cout << ((a[i] >> j) & 1);
cout << ' ';
j = 31;
}
cout << endl;
}*/

void printPolynomBin(M_LONG a)
{
	int i = a[0], j;
	bool flag = true;
	for (; i > 0 && flag; i--)
	{
		for (j = 31; j >= 0; j--)
			if ((a[i] >> j) & 1)
			{
				flag = true;
				break;
			}
	}

	i++;

	for (; i > 0; i--)
	{
		for (; j >= 0; j--)
		{
			cout << ((a[i] >> j) & 1);
			if (j % 4 == 3)
				cout << ' ';
		}
		j = 31;
	}
	/*int m = degree(a);
	if (m < 0)
	cout << "0" << endl;
	for (; m >= 0; m--)
	{
	cout << ((a[m / 32 + 1] >> (m % 32)) & 1);
	if (m % 4)
	cout << ' ';
	}*/
	cout << endl;
}

void printPolynomHex(ostream &out, M_LONG a)
{
	int firstNotZerro = a[0];
	while (firstNotZerro > 0 && a[firstNotZerro] == 0)
		firstNotZerro--;
	if (!firstNotZerro)
	{
		out << '0';
		return;
	}
	out << hex << a[firstNotZerro];
	for (int i = firstNotZerro - 1; i > 0; i--)
		out << std::setw(8) << std::setfill('0') << a[i];
	out << dec << std::setw(0);
}

void setBits(M_LONG a, std::vector<unsigned int> degries)
{
	if (degries.size() != 2 && degries.size() != 4)
	{
		cout << "Incorrect polynom" << endl;
		return;
	}
	for (int i = 0; i < degries.size() - 1; i++)
	{
		if (degries[i] <= degries[i + 1])
		{
			cout << "Incorrect polynom" << endl;
			return;
		}
	}
	a[0] = degries[0] / 32 + 1;
	a[1] = 1;
	for (int i = 2; i <= a[0]; i++)
		a[i] = 0;
	for (int i = 0; i < degries.size(); i++)
		a[degries[i] / 32 + 1] |= 1 << (degries[i] % 32);
}

unsigned int myRand()
{
	return ((rand() << 17) | (rand() << 2) | (rand() & 3));
}

bool randElement(M_LONG a, unsigned int n)
{
	int bl = n / 32 + 1;
	int sd = n % 32;
	for (int i = 1; i < bl; i++)
		a[i] = myRand();
	a[bl] = myRand() & ((1 << sd) - 1);
	a[0] = bl;
	while (a[a[0]] == 0 && a[0] > 1)
		a[0]--;
	if (a[1] == 0 && a[0] == 1)
		return true;
	return false;
}

int genElem(M_LONG f, M_LONG g)
{
	int deg = degree(f);

	while (randElement(g, deg));
	return 0;
}
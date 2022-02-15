#include <iostream>
#include <fstream>      // std::ifstream
using namespace std;
void main()
{
	ifstream   f5("Debug\\CompresedTestCase.txt", ifstream::binary);
	ofstream   f6("Debug\\decompresedTestCase.bmp", ofstream::binary);
	f5.seekg(0, f5.end);//make ct =0
	char ch;
	int N = f5.tellg(); //N=the ct
	cout << N << endl;
	f5.seekg(0, f5.beg);
	int ct = 0;
	char x[257][1000];
	int m = 0, b = 1;
	int z = 0;
	int k, ct2 = 0;

	for (int i = 0; i < N; i++)
	{
		f5.read(&ch, 1);
		ct2++;
		x[m][0] = ch;
		if (ch == '.')
		{
			ct++;
		}
		b = 1;
		for (k = 0;; k++)
		{
			f5.read(&ch, 1);
			ct2++;
			if (ch == '.' && k == 0)
			{
				z = 1;
				m--;
				break;
			}
			x[m][b] = ch;
			b++;
			if (ch == '.')
			{
				break;
			}
		}
		if (z == 1)
		{
			f5.read(&ch, 1);
			ct2++;
			break;
		}
		m++;
	}
	int ib2;
	f5.read(&ch, 1);
	unsigned char c[200000];
	int a = 0;
	ib2 = ch - 48;

	for (int i = ct2 + 1; i < N; i++)
	{
		f5.read(&ch, 1);
		c[a] = ch;
		a++;
	}

	unsigned char t = 0, mask = 1, r, r2;
	int  ib = 7;
	char d[200000], decode[200000];
	int a2 = 0, d2 = 0;
	int i;
	for (i = 0; i < a; )
	{
		mask = 1;
		r2 = (mask << ib) & c[i];
		if (r2 != 0)
		{
			//1
			decode[a2] = '1';
		}
		else
		{
			//0
			decode[a2] = '0';
		}
		decode[a2 + 1] = 46;
		a2++;
		for (int z = 0; z <= m + 1; z++)
		{
			ct = 0;
			for (k = 0; k <= a2; k++)
			{
				if (decode[k] == x[z][k + 1])
				{
					ct++;
				}
				else
				{
					break;
				}
			}
			if (ct == a2 + 1)
			{
				d[d2] = x[z][0];
				d2++;

				//delete decode 
				for (int h = 0; h < k; h++)
				{
					decode[h] = ' ';
				}


				a2 = 0;
				break;
			}
		}
		ib--;
		if (ib == -1)
		{
			ib = 7;
			i++;
		}
		if (i == a - 1 && ib == ib2)
		{
			break;
		}

	}


	for (i = 0; i < d2; i++)
	{
		//cout << d[i];
		//char q = d[i];
		f6.write(&d[i], 1);

	}
	cout << "Done";

}
#include<iostream>
using namespace std;

int main()
{

	unsigned char output[20000] = { 0 }, mul_p[2000] = { 0 };
	int N, A;
	int max_out = 1, max_mul = 1, real_mul=max_mul;
	cin >> N >> A;

	for (int i = 0; i < 1000; i++)
		output[i] = mul_p[i] = 0;
	mul_p[0] = 1;
	
	for (int i = 1; i <= N; i++)
	{
		for (int tem_mul = real_mul-1; tem_mul >=0; tem_mul--)
		{
			mul_p[tem_mul] *= A;
			int t_2_mul;
			if (mul_p[tem_mul] >= 10)
			{
				t_2_mul = tem_mul;
				while (1)
				{
					mul_p[t_2_mul + 1] += mul_p[t_2_mul] / 10;
					mul_p[t_2_mul] = mul_p[t_2_mul] % 10;
					t_2_mul++;
					if (mul_p[t_2_mul] < 10)
						break;
				}
				max_mul = max(max_mul, t_2_mul+1);
				max_out = max(max_out, max_mul);
			}

		}
		real_mul = max_mul;

		for (int tem_out = 0; tem_out < max_mul; tem_out++)
		{
			int tem = mul_p[tem_out] * i;
			int t_2_out = tem_out;

			while (tem)
			{
				int ttt;
				output[t_2_out++] += tem % 10;
				tem /= 10;

				if (output[t_2_out - 1] >= 10)
				{
					ttt = t_2_out - 1;
					while (1)
					{
						output[ttt + 1] += output[ttt] / 10;
						output[ttt] = output[ttt] % 10;
						ttt++;
						if (output[ttt] < 10)
							break;
					}
					max_out = max(max_out, ttt + 1);
				}

			}


		}
	}

	int out = 0;
	if (output[max_out+5] != 0)
		cout << char(output[max_out] + '0');
	if (output[max_out+4] != 0)
		cout << char(output[max_out] + '0');
	if (output[max_out+3] != 0)
		cout << char(output[max_out] + '0');
	if (output[max_out+2] != 0)
		cout << char(output[max_out+2] + '0');
	if (output[max_out+1] != 0)
		cout << char(output[max_out+1] + '0');
	if (output[max_out] != 0)
		cout << char(output[max_out] + '0');

	for (int i = max_out - 1; i >= 0; i--)
		cout << char(output[i] + '0');
	/*for (max_out = 5000; max_out >= 0; max_out--)
	{
		if (output[max_out] != 0)
		{
			for (int i = max_out; i >= 0; i--)
				cout << char(output[i] + '0');
			break;
		}
	}*/


	/*	int add=0,ttii;
	if (max_out <= 10)
	{
		int outt = 0;
		for (outt = 0; outt < 20; outt++)
			if (output[outt] != 0)
				max_out = outt;

	}
	if(max_out>=10)
	{
		for (ttii = max_out - 10; ttii < max_out+20; ttii++)
			if (output[ttii] != 0)
				max_out=ttii;

	}
	for (int i = max_out; i >= 0; i--)
		cout << char(output[i] + '0');*/
	return 0;
}
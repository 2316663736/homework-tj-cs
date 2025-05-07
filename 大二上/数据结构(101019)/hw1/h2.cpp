#include<iostream>
using namespace std;

int main()
{
	long long output[10000]={0}, times = 0, place, num, out = 0;
	char input;
	while (out!=2)
	{
		times++;
		place = 1;

		while(1)
		{
			input = getchar();
			if (input == '#')
			{
					out = 2;
					break;
		
			}
			else if (input == 10)
				break;
			else
			{
				 if(input<='Z'&&input>='A')
					output[times] += (input - 'A' + 1) * place;						
				place++;
			}
		}
	}
	for (long long i = 1; i < times; i++)
		cout << output[i] << endl;

	return 0;
}
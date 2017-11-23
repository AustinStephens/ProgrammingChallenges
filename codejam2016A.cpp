/* Google Code Jam 2016 Qualifying problem.
Bleatrix Trotter the sheep has devised a strategy that helps her fall asleep faster. First, she picks a number N. Then she starts naming N, 2 × N, 3 × N, and so on. Whenever she names a number, she thinks about all of the digits in that number. She keeps track of which digits (0, 1, 2, 3, 4, 5, 6, 7, 8, and 9) she has seen at least once so far as part of any number she has named. Once she has seen each of the ten digits at least once, she will fall asleep.

Bleatrix must start with N and must always name (i + 1) × N directly after i × N. For example, suppose that Bleatrix picks N = 1692. She would count as follows:

N = 1692. Now she has seen the digits 1, 2, 6, and 9.
2N = 3384. Now she has seen the digits 1, 2, 3, 4, 6, 8, and 9.
3N = 5076. Now she has seen all ten digits, and falls asleep.
What is the last number that she will name before falling asleep? If she will count forever, print INSOMNIA instead.

Input

The first line of the input gives the number of test cases, T. T test cases follow. Each consists of one line with a single integer N, the number Bleatrix has chosen.

Output

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the last number that Bleatrix will name before falling asleep, according to the rules described in the statement.

Limits

1 = T = 100.
Small dataset

0 = N = 200.*/

#include <iostream>
#include <string>
#include <unordered_set>

using std::cin;
using std::cout;
using std::endl;
using std::unordered_set;
using std::string;
using std::to_string;

int main()
{
	int t;
	bool flag;
	unordered_set<int> digits;
	int n;
	
	do{
		cout << "Enter amount of tests you want to perform ";
		cin >> t; // amount of tests
	} while (t < 1 || t > 100);

	for (int i = 1; i <= t; i++)  
	{
		digits.clear();
		
		cin >> n;
		if (n < 0 || n > 200) continue; // if its invalid, just skip this iteration
		
		cout << "Case #" << i << ": ";
		
		if (n == 0) cout << "IMSOMNIA" << endl;
		else
		{
			int num = 0;
			flag = true;
			for(int j = 1;flag;j++)
			{
				flag = false;
				int newNum = n * j;
				while (newNum >= 1)
				{
					digits.insert(newNum % 10); // gets the last digit
					newNum /= 10;
				}
				for (int k = 0; k < 10; k++)
				{
					//   for some reason digits.count(k) doesnt work
					if (digits.find(k) == digits.end())  // if there is a digit missing, keep going
					{
						flag = true;
						break;
					}
				}
				num = n * j;
			}
			cout << num << endl;
		}
	}
	return 0;
}

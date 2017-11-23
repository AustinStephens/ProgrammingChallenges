// In c++
// This is a version of the FizzBuzz challenge. If its divisible by 3 output "cats", if divisible by 5 output "dogs", if both then output "cats&dogs".
#include <iostream>

using std::cout;
using std::endl;

int main() 
{
	for (int i = 1; i <= 1000; i++)
	{
		
	    if (i % 3 == 0)
	    {
	    	cout << "Cats";
	    	if (i % 5 == 0) // might look like im checking the same condition twice but this is never checked twice. If this is checked then ill never actually check the else if.
	    	{
	    		cout << "&Dogs";
			}
	    }
	    else if (i % 5 == 0)
	    {
	   		cout << "Dogs";
	    }
	    else
	    {
	      cout << i;
		}
	    cout << endl;
	}
	return 0;
}

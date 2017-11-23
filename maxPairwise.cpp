/* Used to test the maxPairwiseProduct function*/

#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;
using std::endl;

int MaxPairwiseProduct(int numbers[], int size) {
  int largest, second;
  largest = numbers[0];
  second = 0;
  
  for (int i = 1; i < size; ++i)
  {
  	if (numbers[i] >= largest)
  	{
  		second = largest;
  		largest = numbers[i];
	}
  }
  
  return largest * second;
}

int main() {
	int n;
    cout << "Enter the length of the array" << endl;
    cin >> n;
    if(n > 0) 
	{
	    int numbers[n];
	    for (int i = 0; i < n; ++i) {
	    	cout << "Enter element " << i << endl;
	        cin >> numbers[i];
	    }
	
	    int result = MaxPairwiseProduct(numbers, n);
	    cout << endl << result << endl;
	}
    return 0;
}

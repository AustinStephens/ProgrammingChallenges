// Collection of many programming challenge functions.

#include <iostream>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <unordered_set>
#include <string>

#include "LinkedList.h"
#include "LinkedList.cpp"
#include "Node.h"

using std::vector;
using std::cout;
using std::unordered_set;
using std::string;

//RNG with a given range, just doing this to save space
int randInt(int min, int max)          
{
	int num;                                                                                    //for example, randInt(50,60)
	time_t timer;																			    
	srand(time(&timer));															  
	num = rand() % (max - min + 1) + min;//rand() % range + 1   then add the minimum to it.          //num = (rand() % 11) + 50
	return num;																   //should be between 0 and 10  ^^^^^    so add 50 then its 50 to 60
}

int power(int a, int b)
{
	/*if (b < 0)   guess this doesnt work right now
	{
		return 1 / power(a, abs(b));
	}
	else*/ if (b <= 0) return 1;   
	else if (b == 1) return a;
	else
	{
		return a *= power(a, b-1);
	}
}

//from Google Software Engineer Interview      saw the idea on the board and coded it
bool findPairWithSum(const vector<int> &data, int sum) //sees if a vector contains two elements that add up to the given sum, assuming its sorted
{
	int min = 0;                     //min index
	int max = data.size() - 1;       //max
	
	while (min < max)                //if they equal or somehow they cross it exits
	{
		int obsSum = data[min] + data[max];     //temp value for the sum of the two elements being added
		if (obsSum == sum)                     //asks if the sum of the two elements
			return true;
		else if (obsSum > sum)
			--max;
		else
			++min;
	}
	
	return false;
}

//Also from the Google Video
bool findPairUnordered(const vector<int> &data, int sum)  //sees if a vector contains two elements that add up to the given sum, the vector is not garunteed to be sorted
{
	unordered_set<int> comp; //set of compliments
	
	for (int value : data)
	{
		if (comp.count(value))  //looks if there is a element with that value in it
			return true;				   //So essentially it asks if the value returned from find(value) is undefined, if not return true.
		comp.insert(sum - value);    //If it is undefined add the compliment to the set, goes back to the beginning.
	}
	return false;  //if it finishes the vector and never returns true, return false
}

char findFirstRecurringChar(string str) //finds the first duplicate character in a string, if not returns null, very similar to the above challenge
{
	unordered_set<char> prevChars; // set of previous characters in the string
	
	for (char letter : str) // loops through the string
	{
		if(prevChars.count(letter)) //if there is 1 of those letters in the prevchar set, thats the first recurring character
			return letter;
		prevChars.insert(letter); //otherwise add it to the character set
	}
	
	return NULL; //shouldnt have null, bad practice in c++, could make a custom object/struct
	//struct CustomReturnType { bool ifCharIsFound; char foundChar } , would just leave foundChar undefined if not found, check ifCharIsFound before using it.
}

int factorial(int num) //uses for loop instead of recursion
{
	int returnNum = 1;          //starts the temp at 1
    for (num; num > 1; num--)   //keeps going down to 1 (unneccesary to add 1 because it doesn't change the product
    {
        returnNum *= num;
    }
    
  	return returnNum; 
}

int factorialRecursive(int num)  //uses factorial instead of for loops
{   //could do it if(num <= 1) since both cases are same
	if (num < 1) return 1;            //if its 0! it should be 1
	else if (num == 1) return 1;    //if its 1! it should be 1
	else
	{
		num *= factorialRecursive(num - 1);  //Ends of num * num-1 * num - 2 * num - 3 ....
		return num;      //returns the product
	}
}

//Almost like a quick sort, each iteration we have to check 1 less element
void replaceWithProduct(vector<int> &data)  //replaces every element in a vector with the product of all the other elements WITHOUT USING DIVISON
{
	int previousProduct = 1;					//The product of all the elements to the left
	for (int i = 0; i < data.size(); ++i)
	{
		int temp = data[i];           //temp value for the existing element so it can multiply it to the previousProduct
		data[i] = 1;                  //sets the element to one (essentially wipes it) because we dont include itself
		for (int j = i + 1; j < data.size(); j++)  //iterates throught the elements on the right side and multiplies them to data[i]
		{
			data[i] *= data[j];
		}
		data[i] *= previousProduct;        //multiplies the new value of the product of the elements to the right to the elements to the left
		previousProduct *= temp;  //multiplies the old value of the element to the product of the elements to the left
	}
}

int largestArea(const vector<int> &data) //finds the largest rectangular area in a given histogram
{ //So what this does is it goes through every y = 1 increment and adds continuous columns to the width then times it by the height or current y level
	bool flag = true;               //Flag to check if the histogram goes to that y level , if it iterates through a row and finds x's go that high, it stops the for loop
	int largestRectangle = 0;       //If no values are in vector, returns 0
	for (int i = 1; flag; i++) //starts at 1 because we dont care if it equals zero
	{
		int tempRectangle = 0;   //temp rectangle gets reset after each iteration
		flag = false;   // for each row it makes sure there are values in it
		for (int j = 0; j < data.size(); j++) 
		{
			if (data[j] >= i)   //if the value of x is greater or equal to the than current height were looking for
			{
				tempRectangle++; //add 1 to the temp rectangle "width"
				flag = true;  //means there was a x value that has a height this high, doesnt exit for loop
			}
			else  //if we find an x values that doesn't go that high
			{
				tempRectangle *= i;   //takes the rectangle we made so far then times it by the height for the total area
				if (tempRectangle > largestRectangle) largestRectangle = tempRectangle;  //if its greater than the largest one we've found so far, then it is the new max
				tempRectangle = 0;  //resets the width to 0
			}
		}
	}
	
	return largestRectangle;
}


//From Google programming challenge: Find the Volume of Each Lake Created by Rainwater
//A lot like the biggest rectangle in a histogram challenge
//Might be O(n^2), but other solutions are assuming a lot of things about the array.
int volumeOfRainwater(const vector<int> &island) //returns the amount of rainwater a given island could hold (basically how many gaps are there where there the island is on both sides)
{  
	//assuming there are no 0's or negative numbers in the array, or that a 0 doesn't affect how much rainwater could be held
	bool flag = true; //becomes false when we iterate through a new y level and tehre aren't any heights that high
	int rainwater = 0;
	for(int y = 1; flag; y++) //the height of the space (y coord)
	{
		int rightIndex, leftIndex = 0; //the index of the right and left most points where land is, water cannot form outside of them
		
		flag = false;
		
		for(int i = 0; i < island.size(); i++) // finds the right most index that is <= y
		{
			if (island[i] >= y)
			{
				leftIndex = i;
				flag = true; 
				break;    //should add this to the top condition
			}
		}
		
		for (int j = island.size() - 1; j >= 0; j--)   // finds the right most index that is >= y
		{
			if (island[j] >= y)
			{
				rightIndex = j;
				flag = true;
				break;  //should add this to the top condition
			}
		}
		
		if(flag || rightIndex == leftIndex) //makes sure there is any land on this y level and that the indexes arent the same
		{   // checks between the two indexes for white space
			for (int x = leftIndex + 1; x < rightIndex; x++)
			{
				if (island[x] < y) //if there is white space increment the rainwater
				{
					rainwater++;
				}
			}
		}
	}
	
	return rainwater;
}

//finds the sub array of a vector with the largest sum
int maxSubArray(const vector<int> &data)
{
	int maxSubArray = 0;           //inializes the max and sum to 0
	int sum = 0;               
	for (int element : data)
	{
		sum += element;       //gets the sum of the whole vector
	}
	maxSubArray = sum;       //sets max equal to the sum
	
	int lo = 0; //low index
	int hi = data.size() - 1; //high index
	
	while (lo < hi)   //while they dont equal essentially, but in case the cross for some reason
	{
		if (data[lo] > data[hi]) //if the high index is the lower value, subtract it from the sum of the previous subArray
		{
			sum -= data[hi];
			hi--;
		}
		else //else if the lo index is <=, subtract it from the sum of the previous subArray
		{
			sum -= data[lo];
			lo++;
		}	
		
		if (sum > maxSubArray) //if the sum of the subArray is greater than the largest one we've found, set it to the largest
			maxSubArray = sum;
	}
	
	return maxSubArray;
	
}

void selectionSort(vector<int> &data)
{
	for (int i = 0; i < data.size(); i++)
	{
		int minElement = i; //index of the min element
		int temp; //temp value holder
		for(int j = i; j < data.size(); j++)  
		{
			if(data[j] < data[minElement]) minElement = j;  //if element is smaller, min index is the index of the value
		}
		temp = data[i]; 
		data[i] = data[minElement]; //element is replaced with min element value
		data[minElement] = temp;  //swaps the value of min element with the old element
	}
}

//using a linked list, not double, but its too late to change it.                                                            This is how it works: you have the list of denoms and the sum, i make a vector that physicall represents the coins that make of the sum
int changeOptionsDblLinked(int sum, const vector<int> &denominations) //denoms must be in ascending order                    I put the denoms into a linked list in descending order, then I do the order that uses the largest denoms first, and each time i decrement
{ // returns the the number of ways the sum can be split up by the different denominations                                   the denoms by one 
	LinkedList<int> denoms; //will be in descending order                                                                    Should go:   sum = 5   denoms = {1, 2, 5}   5 , 2 + 2 + 1, 2 + 1 + 1 + 1, 1 + 1 + 1 + 1
	vector<Node<int> *> change;
	int total = 0;
	int i;
	int numOfWays = 0; //number of ways, the int returned by the function
	bool flag = true; //for figuring out when to exit the while loop when its at the lower denom
	bool forFlag; //need this to get over the dilema of the smallest denom problem
	
	//entering vector data into linked list, in descending order
	for(i = denominations.size() - 1; i >= 0; i--)//also removing any denoms that are larger than sum
	{	
		if(denominations[i] <= sum && denominations[i] > 0) //figured i'd put that here since 0 or negatives would break this	//was more efficient but need to be descending so i cant put this condition in for statement
			denoms.append(denominations[i]);
	}
	
	Node<int> *currentDenom = denoms.head;  //start it at the highest denom
	
	while(currentDenom) //finds the combination that uses that largest amounts of coins
	{
		for (total; total + currentDenom->value <= sum; total += currentDenom->value)
		{
			change.push_back(currentDenom);
		}
		
		currentDenom = currentDenom->nextNode;
	}
	if(total == sum) numOfWays++; //if it equals the sum, incremenet num of ways
	
	while(change.front()->nextNode)
	{
		flag = true; //reset flag
		currentDenom = change.back(); //find what denom the last element has
		
		if(currentDenom->nextNode) //making sure the lowest denom isnt in the first arrangement of numbers
		{
			total -= currentDenom->value;	
			change.back() = currentDenom->nextNode; //change it to the next lowest
			total += change.back()->value;
			
			while(flag)
			{	
				forFlag=false; //reset flag
				if(currentDenom->nextNode) currentDenom = currentDenom->nextNode;  //while there are lower denoms, its like this because i only want to take away the lower value from the vector
				else flag = false; // having a hard time finding a way to make it so if theres no next node before it enters the while loop, execute once, but if nextnode becomes null in the loop exit.
				
				for (total; total + currentDenom->value <= sum; total += currentDenom->value)
				{
					forFlag = true; //tells the if statement for numofways that it was been through the for loop so i dont get duplicates adding to the numofways
					change.push_back(currentDenom);
					//if (total == sum) numOfWays++;
				}
				
				if(total == sum && forFlag) numOfWays++;//couldnt put it in for loop because it exits before ever incrementing it to where it would be equal
			}
		}
		
		for (i = change.size() - 1; i >= 0 && change[i]->value == currentDenom->value; i--, total -= currentDenom->value)
		{
			change.pop_back();  //these should be the lowest denom, they are removed from the end
		}
	}
	return numOfWays;
}


int fibbonaciN(int n) //finds the nth number in the fibbonaci sequence
{
	if(n <= 2) return n-1; //if its 0 or negative this wont work
	
	int first = 0;
	int second = 1;
	int temp;
	
	for(int i = 3; i <= n; i++)
	{
		temp = first;
		first = second;
		second += temp;
	}
	return second;
}



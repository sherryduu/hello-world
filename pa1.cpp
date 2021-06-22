/*
 * COMP2011 (Fall 2020) Assignment 1: Binary Numbers
 *
 * Student name: DU XIAWEI
 * Student ID: 20697770
 * Student email: xduam@connect.ust.hk
 *
 * Note:
 * 1. You CANNOT define and use any arrays.
 * 2. You CANNOT define and use any global variables.
 * 3. You CANNOT use the static keyword.
 * 4. You CANNOT include any extra libraries other than iostream.
 * 5. You CANNOT use any bitwise operators: ~, ^, |, & (since they are not taught in this course).
 * 6. You CANNOT change the function headers of the functions given in the tasks.
 * 7. You CANNOT use any string operations.
 * 8. You can add helper functions.
 */

#include <iostream>

using namespace std;

int get_power_result(int y,int z)
{
    int power_result=1;
    for(int i=0; i<y; i++)
        power_result *= z;
    return power_result;
}

// Task 1
int get_min_bits_length(int x)
{
    int min_bits_length=0;
    int difference;
    if (x>=0)
    {
        difference = x-1;
        if (difference<=0)
            min_bits_length = 2;
        else
        {           
            while(difference>=0)
            {
                min_bits_length += 1;
                difference = x-get_power_result(min_bits_length,2);
            }
            min_bits_length += 1;       
        }
    } 
    else
    {
        x=abs(x);
        difference = x;
        if (x==1||x==2)
            min_bits_length = 2;
        else
        {           
            while(difference>0)
            {
                min_bits_length += 1;
                difference = x-get_power_result(min_bits_length,2);
            }
            min_bits_length += 1;       
        }
    }
    
    return min_bits_length;
}

int remainder(int y)
{
    do
    {
        y=y%2;
    }while(y>1);
    return y;
}

// Task 2
int get_bit_positive(int x, int n)
{
	int bit_positive;
	if(x<0||n<0)
        bit_positive = -1;
    else
    {
        if (n==0)
            bit_positive = x%2;
        else if (n>=(get_min_bits_length(x)-1))
            bit_positive = 0;
        else
        {
            bit_positive = remainder(x/get_power_result(n,2));
        }          
    }
    return bit_positive;
}

int find_remain_v2(int x)
{
    int remain_v2=-1;
    int n=0;
    while(remain_v2<0)
    {
        n += 1;
        remain_v2 = get_power_result(n,2)-abs(x);
    }
    return remain_v2;
}

// Task 3
int get_bit_negative(int x, int n)
{
	int bit_negative;
    if(x>0||n<0)
        bit_negative = -1;
    else
    {
        if (n==0)
            bit_negative = abs(x)%2;
        else if (n>=(get_min_bits_length(x)-1))
            bit_negative = 1;
        else
        {
            bit_negative = remainder(find_remain_v2(x)/get_power_result(n,2));
        }          
    }
    return bit_negative;
}

// Task 4
void print_2s_complement_representation(int x)
{	
	if(x>=0)
    {
        for(int i=get_min_bits_length(x);i>0;i--)
        {
            cout << get_bit_positive(x,(i-1));
        }
        cout << endl;
    }
    else
    {
        for(int i=get_min_bits_length(x);i>0;i--)
        {
            cout << get_bit_negative(x,(i-1));
        }
        cout << endl;
    }
      
    return ;
}

// Task 5
void print_addition_carry_out(int a, int b)
{
	int a_x,b_x,c=0,n=0;
    long long addition_carry_out=0;
    int total_length;
 	
	while( n<=get_min_bits_length(a) && n<=get_min_bits_length(b) )
    {
        if (a>=0)
        {
            a_x=get_bit_positive(a,n);
        }
        else
        {
            a_x=get_bit_negative(a,n);
        }
        if (b>=0)
        {
            b_x=get_bit_positive(b,n);
        }
        else
        {
            b_x=get_bit_negative(b,n);
        }
        if ( (a_x==1 && b_x==1) || ((a_x||b_x) && c==1 ) )
        {
            addition_carry_out=addition_carry_out+get_power_result(n,2);
            c=1;
        } 
        else
        {
            c=0;
        }
        n++;
    }  
    total_length = get_min_bits_length(a+b);
    for(int i=total_length;(i<=get_min_bits_length(addition_carry_out));i++) 
    {
        cout << 0;
    }
    print_2s_complement_representation(addition_carry_out);
    return;
}

// DO NOT WRITE ANYTHING AFTER THIS LINE. ANYTHING AFTER THIS LINE WILL BE REPLACED

int main()
{
	while (true) {
		int option = 0;

		do {
			cout << "1. Task 1" << endl;
			cout << "2. Task 2" << endl;
			cout << "3. Task 3" << endl;
			cout << "4. Task 4" << endl;
			cout << "5. Task 5" << endl;
			cout << "0. Exit" << endl;
			cout << "Enter an option (0-5): ";
			cin >> option;
		} while (option < 0 || option > 5);
		
		if (option == 0)
			break;
		else if (option == 1) {
			int number;
			cout << "Enter a number: ";
			cin >> number;
			cout << number << " needs " << get_min_bits_length(number) << " bits." << endl;
		}
		else if (option == 2) {
			int number;
			int bit;

			cout << "Enter a number: ";
			cin >> number;

			cout << "Which bit? ";
			cin >> bit;
			
			cout << "The number " << bit << " bit of " << number << " is " << get_bit_positive(number, bit) << endl;
		}
		else if (option == 3) {
			int number;
			int bit;

			cout << "Enter a number: ";
			cin >> number;

			cout << "Which bit? ";
			cin >> bit;
			
			cout << "The number " << bit << " bit of " << number << " is " << get_bit_negative(number, bit) << endl;
		}
		else if (option == 4) {
			int number;
			cout << "Enter a number: ";
			cin >> number;
			cout << "The 2's complement representation of " << number << " is:" << endl;
			print_2s_complement_representation(number);
		}
		else if (option == 5) {
			int a, b;
			cout << "Enter number A: ";
			cin >> a;
			cout << "Enter number B: ";
			cin >> b;
			cout << "The sum of " << a << " and " << b << " is " << a + b << ". The carry bits are:" << endl;
			print_addition_carry_out(a, b);
		}

		cout << endl;
	}

	return 0;
}
#include<iostream>
#include<ctime>
#include<vector>
#include<iomanip>
using namespace std;

//test if the three numbers are able to form a right triangle
//assert i < j < k
bool is_right_triangle(int i, int j, int k)
{
	if (i * i + j * j == k * k)
		return true;
	else
		return false;
}

//store the data
class database
{
	vector<int*> db;
public:
	//insert a new triangle into the db
	void INSERT(int i, int j, int k)
	{
		int* temp = new int[3];
		temp[0] = i; temp[1] = j; temp[2] = k;
		db.push_back(temp);
	}
	void print()
	{
		int len = db.size();
		for (int i = 0; i < len; i++) {
			cout << db[i][0] << " "
				<< db[i][1] << " "
				<< db[i][2] << " "
				<< endl;
		}
		cout << "Total counts: " << len << endl;
	}
	int size()
	{
		return db.size();
	}
};

void main()
{
	for (int n = 100; n <= 1000; n += 100)
	{
		database sql;
		clock_t start, end; //set start and end indicator to 
		start = clock();	//caculate the time consumed
		for (int i = 1; i < n; i++) {
			for (int j = i; j < n; j++) {
				for (int k = j; k < i+j; k++) {
					if (is_right_triangle(i, j, k))
						sql.INSERT(i, j, k);
				}
			}
		}
		end = clock();
		//sql.print();
		/*if you wanna print all the solutions
		please uncomment the line above*/

		cout << "n: " << setw(4) << n					
			<< "  time: " << setprecision(5)
			<< (double)(end - start) / CLOCKS_PER_SEC
			<< endl;
	}
}
/* Output:
n :  100  time : 0.005
n :  200  time : 0.031
n :  300  time : 0.107
n :  400  time : 0.241
n :  500  time : 0.491
n :  600  time : 0.866
n :  700  time : 1.361
n :  800  time : 2.049
n :  900  time : 2.871
n : 1000  time : 3.893
*/
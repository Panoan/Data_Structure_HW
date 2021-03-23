#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//Merge sort
void Sort(int* A, int l, int r, int* T) {
	if (r - l > 1) {
 		int m = (l + r) / 2;
		int p = l, q = m, i = l;
		Sort(A, l, m, T);
		Sort(A, m, r, T);
		while (p < m || q < r) {
			if (q >= r || (p < m && A[p] <= A[q]))
				T[i++] = A[p++];
			else T[i++] = A[q++];
		}
		for (int i = l; i < r; i++) A[i] = T[i];
	}
}

int main()
{
	const int a = 10, b = 5;					//set the size of La & Lb
	int* La = new int[a]; int* Lb = new int[b];

	//generate a non-repeatable array
	int* arr = new int[a + b];					//temporarily put La and Lb together
	for (int i = 0; i < a + b; i++)				//arr:{1, 2, 3, 4, ..., a + b}
		arr[i] = i;
	for (int i = 0; i < a + b; i++) {			//randomly swap these numbers to make the whole array 
		int indicator;
		if (i == 0) indicator = 1;
		else indicator = rand() % i;
		swap(arr[i], arr[indicator]);			//a non-repeatable integer array
	}

	//divide the arr into La and Lb
	for (int i = 0; i < a; i++)
		La[i] = arr[i];
	for (int i = a; i < a + b; i++)
		Lb[i - a] = arr[i];

	int* tempa = new int[a];
	int* tempb = new int[b];
	Sort(La, 0, a , tempa);
	Sort(Lb, 0, b , tempb);
	delete[] tempa; delete[]tempb;

	//merge this two
	int p = 0, q = 0;
	int* temp = new int[a + b];
	int* Lc = new int[a + b];
	while (p <= a && q <= b) {
		if (p == a || (q < b && La[p] >= Lb[q]))
			temp[p + q] = Lb[q++];
		else
			temp[p + q] = La[p++];
	}

	for (int i = 0; i < a + b; i++) {
		Lc[i] = temp[i];
		cout << Lc[i] << endl;
	}
}

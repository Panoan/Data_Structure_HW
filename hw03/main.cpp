#include <iostream>
#include<algorithm>
using namespace std;

/* set the length of a and b */
int a = 20, b = 10;  

template<typename T>
class node {
public:
	T data;
	node<T>* next = nullptr;
};

//class chain 
template<typename T>
class chain {
public:
	node<T> *start;
	int size = 1;
	
	/* funcs */
	//init
	chain(){ 
		start = new node<T>;
	}
	chain(int n){
		start = new node<T>;
		extend(n-1);
	}
	chain(node<T>* start, int size) {
		this->start = start;
	}

	//set start node (useless)
	void setstart(node<T>* start) {
		this->start = start;
	}

	/* //return the address of the last node (useless)
	node<T>* last() {
		node* curr = start;
		while (curr.next) { curr = curr.next; }
		return curr;
	} */

	//extend the chain by l node(s)
	void extend(int l = 1) {
		node<T>* curr = start;
		for (int i = 0; i < l; i++) {
			node<T> *New = new node<T>;
			curr->next = New;
			curr = curr->next;
			size++;
		}
	}

	/* //return size of the chain (useless)
	size(){
		int count = 1; curr = start;
		while(curr.next){ count++; }
		return count;
	} */

	//locate the the address of the ith element of the chain
	node<T>* loc(int i){
		if (i < 0 || i > size) return nullptr;
		node<T>* curr = start;
		for(int j = 0; j < i; j++){
			curr = curr->next;
		}
		return curr;
	}

	/* //Overload []
	operator[](int i){
		if(i > size) 
			return &nullptr;
		else {
			Node<T>& ref = loc(i).data
			return ref;
		} 
	} */
	
	/* //Overload =
	template <typename U>
	node<T>* operator&= (const node<U>& ref) {
		data = ref.data;
	} */
};

//overload print()
template <typename T>
void print(chain<T>& arr) {
	for (node<int>* curr = arr.start; curr; curr = curr->next) {
		cout << curr->data << " ";
		if (!curr->next)
			break;
	}
	cout << endl;
}
template <typename T>
void Go_on(node<T>* &somenode) {
	somenode = somenode->next;
}
//Overload swap()
template <typename T>
bool swap(chain<T>& somechain, int a, int b){
	if (a > b) swap(a, b); //assert a <= b
	
	node<T>* ath = somechain.loc(a);
	node<T>* bth = somechain.loc(b);

	if (a == b) {
		return 0;
	} else if (a == 0) {		
		if (b == 1) {
			ath->next = bth->next;
			bth->next = ath;
		} else {
			node<T>* preb = somechain.loc(b-1);
			node<T>* bnext = bth->next;
			bth->next = ath->next;
			preb->next = ath;
			ath->next = bnext;
		}
		somechain.setstart(bth);
	} else if (a == b-1) {
		node<T>* prea = somechain.loc(a-1);
		prea->next = bth;
		ath->next = bth->next;
		bth->next = ath;
	} else {
		node<T>* prea = somechain.loc(a-1);
		node<T>* preb = somechain.loc(b-1);
		node<T>* athnext = ath->next;
		prea->next = bth;
		preb->next = ath;
		ath->next = bth->next;
		bth->next = athnext;
	}
	return 1;
}

/* //Merge sort
template<typename U> 
void Sort(node<U>* A, int l, int r, node<U>* T) {
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
} */

//locate the previous element with the curr one's addr
template<typename T>
node<T>* pre(chain<T>& somechain, node<T>* somenode) {
	node<T>* curr;
	for (curr = somechain.start; curr->next != somenode; curr = curr->next) {
		continue;
	}
	return curr;
}

//bubble sort
template <typename T>
void bubble_sort(chain<T>& somechain) {
	for(int i = 0; i < a+b; i++) {
		for(node<T>* curr = somechain.start; curr && curr->next; curr = curr->next) {
			if (!curr) break;
			if (curr->data > curr->next->data) {
				if (curr == somechain.start) {
					node<T>* second_node = curr->next;
					curr->next = second_node->next;
					second_node->next = curr;
					somechain.setstart(second_node);
				} else {
					node<T>* precurr = pre(somechain, curr);
					precurr->next = curr->next;
					curr->next = precurr->next->next;
					precurr->next -> next = curr;
				}
			}
			//print(somechain);
		}
	}
}

int main()
{
	
	chain<int> arr(a+b);

	//assign the ith element with integer i
	int i = 0;
	for(node<int>* curr = arr.start; curr; curr = curr->next) {
		curr->data = i;
		i++;
	}
	//print(arr);

	//randomly swap two elements
	for(int i = 0; i < a+b; i++) {
		int indicator;
		if (i == 0) indicator = 1;
		else indicator = rand() % i;
		swap(arr, i, indicator);
		//print(arr);
	}

	//separate La and Lb
	node<int>* mid = arr.loc(a-1);
	chain<int> La(arr.start, a);
	chain<int> Lb(mid->next, b);
	mid->next = nullptr;
	
	//rearrange using bubble sort
	bubble_sort(La);
	bubble_sort(Lb);
	cout << "La: "; print(La);
	cout << "Lb: "; print(Lb);

	//combine La & Lb
	node<int> *ptr_a = La.start, *ptr_b = Lb.start;
	chain<int> result;
	delete result.start;									//save memory
	if (La.start->data < Lb.start->data) {
		result.start = La.start;
		ptr_a = ptr_a->next;
	} else {
		result.start = Lb.start;
		ptr_b = ptr_b->next;
	}
	node<int>* curr_step = result.start; 					//pointing to the current element of the result
	for (int i = 1; i < a+b; i++) {				
	//the first comparison has been done above so we start i from 1
		while (ptr_a->next && ptr_b->next) {
			if (ptr_a->data < ptr_b->data) {
				curr_step->next = ptr_a;
				result.size++; Go_on(ptr_a);
			} else {
				curr_step->next = ptr_b;
				result.size++; Go_on(ptr_b);
			}
			Go_on(curr_step);
		}
	}
	cout << "Lc: "; print(result);
	return 0; 
}

/* output sample */
/* 
La: 1 4 6 9 10 11 12 14 15 16 17 18 19 20 22 23 24 25 27 28
Lb: 0 2 3 5 7 8 13 21 26 29
Lc: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 29 
*/
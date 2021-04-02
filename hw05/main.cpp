#include <iostream>
#include <string>
#include <iomanip>
using namespace std;


/* generate the 'next' array of KMP */
int* NEXT (const string& W) {
    int lenW = W.length();
    int* Next = new int[lenW];
    int i = 1, 
        now = 0, //now 
        curr_indicator = 0;

    while(i < lenW) {
        if(W[i] == W[now]) {
            Next[i] = ++curr_indicator;
            i++; now++;
        } else if(curr_indicator) {
            curr_indicator = Next[curr_indicator - 1];
            now = 0;
        } else {
            Next[i] = 0; 
            i++; 
            now = 0;
        }
    }

    //IF YOU WANT TO PRINT THE NEXT ARRAY 
    //PLEASE UNCOMMENT THE CODE BELOW
    /*     
    for(int i = 0; i < lenW ;i++) {
        cout << Next[i] << ' ';
    } cout << endl;

    for(int i = 0; i < lenW ;i++) {
        cout <<"- ";
    } cout << endl;

    for(int i = 0; i < lenW ;i++) {
        cout << W[i] << " ";
    } cout << endl;
    */

    return Next;
}

int KMP(const string& S, const string& W) {
    int lenS = S.length(), lenW = W.length();
    int j = 0;
    int* Next = NEXT(W);
    for(int i = 0; i < lenS; i++) {
        if(S[i] != W[j]) {
            j = Next[j] + 1;
        } else {
            if(j == lenW - 1)
                return i - lenW + 1;
            else
                j++;
        }
    }
    return -1;
}



int main() 
{
    string S = "abcabcdabcde";
    string W = "abcdabcde";

    /*  //IF YOU WANT MANNUALLY SET THE TWO STRINGS, 
        //UNCOMMENT THE CODE BELOW
    cout << "Input the main string: "; cin >> S;
    cout << "Input the string you want to search: "; cin >> W;
    */

    int Index = KMP(S, W); //start from 0

    if(Index == -1) {
        cout << "unmatch" << endl;
        return 0;
    }

    
    //PRINT THE RESULT
    int lenS = S.length(), lenW = W.length();
    for(int i = 0; i < lenS; i++) {
        cout << S[i] << " ";
    } cout << endl;
    for(int i = 0; i < lenS; i++) {
        if(i < Index || i >= lenW + Index)
            cout << " ";
        else
            cout << "-";
        cout << " ";
    } cout << endl;
    for(int i = 0; i < lenS; i++) {
        if(i < Index)
            cout << "  ";
    } 
    for(int i = 0; i < lenW; i++) {
        cout << W[i] << " ";
    } cout << endl;

    return 0;
}

/* 
SAMPLE OUTPUT:
a b c a b c d a b c d e 
      - - - - - - - - - 
      a b c d a b c d e 
 */

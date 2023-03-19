#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

bool isSorted(vector<int>& v) {
    for (int i = 1; i < v.size(); i++) {
        if (v[i] < v[i-1]) {
            return false;
        }
    }
    return true;
}

vector<int> generateRandomVector(int n, int max) {
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        v[i] = rand() % (max+1);
    }
    return v;
}

int getMax(int v[], int n) {
    int Max=0;
    for(int i=0; i<n; i++)
        if(v[i]>Max) Max=v[i];
    return Max;
}

void CountSort(int v[], int n, int nrcif) {
    int output[n];
    int count[10]={0};
    for(int i=0; i<n; i++)
        count[(v[i]/nrcif)%10]++;
    for(int i=1; i<10; i++)
        count[i]+=count[i-1];
    for(int i=n-1; i>=0; i--)
    {
        output[count[(v[i]/nrcif)%10]-1]=v[i];
        count[(v[i]/nrcif)%10]--;
    }
    for(int i=0; i<n; i++)
        v[i]=output[i];
}

void RadixSort(int v[], int n) {
    int m;
    m=getMax(v,n);
    for(int nrcif=1; m/nrcif>0; nrcif=nrcif*10)
        CountSort(v,n,nrcif);
}

int main() {
    srand(time(NULL));

    vector<int> test_sizes = {1000, 100000, 1000000};
    vector<int> max_values = {1000, 10000, 100000};

    for (int N : test_sizes) {
        for (int max_val : max_values) {
            vector<int> v = generateRandomVector(N, max_val);
            cout << "N = " << N << ", Max = " << max_val << endl;

            // Test RadixSort algorithm
            int* v_arr = v.data();
            clock_t start_time = clock();
            RadixSort(v_arr, N);
            clock_t end_time = clock();
            double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
            cout << "RadixSort: " << elapsed_time << " seconds." << endl;
            if (!isSorted(v)) {
                cout << "Vectorul nu e sortat" << endl;
            }

            // Test std::sort algorithm
            start_time = clock();
            sort(v.begin(), v.end());
            end_time = clock();
            elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
            cout << "std::sort: " << elapsed_time << " seconds." << endl;
            if (!isSorted(v)) {
                cout << "Vectorul nu e sortat" << endl;
            }

            cout << endl;
        }
    }

    return 0;
}


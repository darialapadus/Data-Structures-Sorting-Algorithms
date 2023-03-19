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


void interclasare(vector <int> &v,int st,int dr)
{
    vector <int> a(v.size());
    int m=(st+dr)/2;
    int i=st,j=m+1,k=st;
    while(i<=m && j<=dr)
        if(v[i]<=v[j])
            a[k++]=v[i++];
        else
            a[k++]=v[j++];
    while(i<=m)
        a[k++]=v[i++];
    while(j<=dr)
        a[k++]=v[j++];
    for(k=st;k<=dr;k++)
        v[k]=a[k];
}

void MergeSort(vector <int> &v,int st,int dr)
{
    if(st < dr) {
        int m=(st+dr)/2;
        MergeSort(v,st,m);
        MergeSort(v,m+1,dr);
        interclasare(v,st,dr);
    }
}

int main() {
    srand(time(NULL));

    vector<int> test_sizes = {1000, 10000, 10000};
    vector<int> max_values = {1000, 10000, 100000};

    for (int N : test_sizes) {
        for (int max_val : max_values) {
            vector<int> v = generateRandomVector(N, max_val);
            cout << "N = " << N << ", Max = " << max_val << endl;

            // Test MergeSort algorithm
            clock_t start_time = clock();
            MergeSort(v, 0, N-1);
            clock_t end_time = clock();
            double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
            cout << "MergeSort: " << elapsed_time << " seconds." << endl;
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


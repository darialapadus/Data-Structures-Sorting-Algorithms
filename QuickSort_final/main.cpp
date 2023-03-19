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

void QuickSort(int v[], int lo, int hi)
{
    int j=lo, i=lo-1,pivot=v[hi];
    if(lo<hi)
    {
        while(j<hi)
        {
            if(v[j]<pivot)
            {
                i++;
                swap(v[j],v[i]);
            }
            j++;
        }
        swap(v[i+1],v[hi]);
        QuickSort(v,lo,i);
        QuickSort(v,i+2,hi);
    }

}
int main() {
    srand(time(NULL));

    vector<int> test_sizes = {1000, 100000, 1000000};
    vector<int> max_values = {1000, 100000, 1000000};

    for (int N : test_sizes) {
        for (int max_val : max_values) {
            vector<int> v = generateRandomVector(N, max_val);
            cout << "N = " << N << ", Max = " << max_val << endl;

            // Test QuickSort algorithm
            int* v_arr = v.data();
            clock_t start_time = clock();
            QuickSort(v_arr, 0, N - 1);
            clock_t end_time = clock();
            double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
            cout << "QuickSort: " << elapsed_time << " seconds." << endl;
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


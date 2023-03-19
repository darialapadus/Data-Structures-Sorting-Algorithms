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

void ShellSort(int v[], int n) {
    for (int interval=n/2; interval>0; interval/=2) {
        for (int i=interval; i<n; i++)
            for (int j = i; j >= interval && v[j - interval] > v[j]; j = j - interval)
                swap(v[j], v[j - interval]);
    }
}

int main() {
    srand(time(NULL));

    vector<int> test_sizes = {1000, 100000, 1000000};
    vector<int> max_values = {1000, 10000, 100000};

    for (int N : test_sizes) {
        for (int max_val : max_values) {
            vector<int> v = generateRandomVector(N, max_val);
            cout << "N = " << N << ", Max = " << max_val << endl;

            // Test ShellSort algorithm
            int* v_arr = v.data();
            clock_t start_time = clock();
            ShellSort(v_arr, N);
            clock_t end_time = clock();
            double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
            cout << "ShellSort: " << elapsed_time << " seconds." << endl;
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


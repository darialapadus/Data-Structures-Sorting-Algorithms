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

void CountingSort(vector<int>& v) {
    int maxVal = v[0];
    for (int i = 1; i < v.size(); i++) {
        if (v[i] > maxVal) {
            maxVal = v[i];
        }
    }
    vector<int> count(maxVal + 1, 0);
    vector<int> output(v.size());
    for (int i = 0; i < v.size(); i++)
        count[v[i]]++;
    for (int i = 1; i <= maxVal; i++)
        count[i] += count[i-1];
    for (int i = v.size() - 1; i >= 0; i--) {
        output[count[v[i]] - 1] = v[i];
        count[v[i]]--;
    }
    for (int i = 0; i < v.size(); i++) 
        v[i] = output[i];
}

int main() {
    srand(time(NULL));

    vector<int> test_sizes = {10000, 100000, 1000000};
    vector<int> max_values = {1000, 10000, 100000};

    for (int N : test_sizes) {
        for (int max_val : max_values) {
            vector<int> v = generateRandomVector(N, max_val);
            cout << "N = " << N << ", Max = " << max_val << endl;

            // Test CountingSort algorithm
            clock_t start_time = clock();
            CountingSort(v);
            clock_t end_time = clock();
            double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
            cout << "CountingSort: " << elapsed_time << " seconds." << endl;
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


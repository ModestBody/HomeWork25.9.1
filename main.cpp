#include <iostream>
#include <vector>
#include <thread>
#include <numeric>
#include <random>
using namespace std;

void sum_part(const vector<int>& arr, int start, int end, int& result) {
    result = accumulate(arr.begin() + start, arr.begin() + end, 0);
}

int main() {
    int N;
    int M;
    cout << "Enter N:" << endl;
    cin >> N;
    cout << "Enter M:" << endl;
    cin >> M;

    vector<int> arr(N);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10);
    for (int& x : arr) {
        x = dis(gen);
    }

    vector<thread> threads;
    vector<int> results(M, 0);
    int part_size = N / M;

    for (int i = 0; i < M; ++i) {
        int start = i * part_size;
        int end = (i == M - 1) ? N : start + part_size;
        threads.emplace_back(sum_part, cref(arr), start, end, ref(results[i]));
    }

    for (auto& t : threads) {
        t.join();
    }

    int total_sum = accumulate(results.begin(), results.end(), 0);

    cout << "Sum of array elements: " << total_sum << endl;

    return 0;
}
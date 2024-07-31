#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>

std::vector<int> generateRandomVector(int N) 
{
    std::vector<int> vec(N);
    srand(time(0));
    for (int i = 0; i < N; ++i)
    {
        vec[i] = rand() % (N + 1);
    }
    return vec;
}

bool isSorted(const std::vector<int> &vec)
{
    for (size_t i = 1; i < vec.size(); ++i)
    {
        if (vec[i - 1] > vec[i])
        {
            return false;
        }
    }
    return true;
}

void insertionSort(std::vector<int> &vec)
{
    for (size_t i = 1; i < vec.size(); ++i)
    {
        int key = vec[i];
        int j = i - 1;
        while (j >= 0 && vec[j] > key)
        {
            vec[j + 1] = vec[j];
            --j;
        }
        vec[j + 1] = key;
    }
}

void merge(std::vector<int> &vec, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = vec[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = vec[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            vec[k++] = L[i++];
        }
        else
        {
            vec[k++] = R[j++];
        }
    }

    while (i < n1)
        vec[k++] = L[i++];
    while (j < n2)
        vec[k++] = R[j++];
}

void mergeSort(std::vector<int> &vec, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);
        merge(vec, left, mid, right);
    }
}

void countingSort(std::vector<int>& vec) {
    int max = *max_element(vec.begin(), vec.end());
    int min = *min_element(vec.begin(), vec.end());
    size_t range = max - min + 1;

    std::vector<int> count(range), output(vec.size());
    for (size_t i = 0; i < vec.size(); i++) count[vec[i] - min]++;
    for (size_t i = 1; i < range; i++) count[i] += count[i - 1];
    for (int i = vec.size() - 1; i >= 0; i--) {
        output[count[vec[i] - min] - 1] = vec[i];
        count[vec[i] - min]--;
    }
    for (size_t i = 0; i < vec.size(); i++) vec[i] = output[i];
}

int main() {
    int N = 1000;
    std::vector<int> vec = generateRandomVector(N);

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    insertionSort(vec);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cout << "Execution time (Insertion Sort): " << duration.count() << " seconds\n";

    std::cout << "Vector sorted: " << (isSorted(vec) ? "Yes" : "No") << "\n";

    return 0;
}

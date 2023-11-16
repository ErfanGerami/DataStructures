#include <iostream>
#include <chrono>
#include <iomanip> 

using namespace std;
//insertion sort-----------------------------------------------------------------------

template<typename T>
void insertionSort(T* arr, int size) {
	for (int i = 1; i < size; i++) {
		T key = arr[i];
		int comparing_index = i - 1;
		while (key < arr[comparing_index] && comparing_index >= 0) {
			arr[comparing_index + 1] = arr[comparing_index];
			comparing_index--;

		}
		arr[comparing_index + 1] = key;
	}


}

//merge sort---------------------------------------------------------------------------
template <typename T>
void merge(T* arr, int start, int middle, int end, T max) {
	T* temp1 = new T[middle - start + 2];
	T* temp2 = new T[end - middle + 1];
	int size1 = middle - start;
	int size2 = end - middle;
	for (int i = 0; i < middle - start + 1; i++) {
		temp1[i] = arr[i + start];
	}
	for (int i = 0; i < end - middle; i++) {
		temp2[i] = arr[i + middle + 1];
	}
	temp1[middle - start + 1] = max + 1;
	temp2[end - middle] = max + 1;

	int cnt1 = 0, cnt2 = 0;
	for (int i = start; i <= end; i++) {
		if (temp1[cnt1] < temp2[cnt2]) {
			arr[i] = temp1[cnt1];
			cnt1++;
		}
		else {
			arr[i] = temp2[cnt2];
			cnt2++;
		}
	}


}
template<typename T>
void mainMergeSort(T* arr, int start, int end, T max) {
	if (start >= end)
		return;
	mainMergeSort(arr, start, (start + end) / 2, max);
	mainMergeSort(arr, (start + end) / 2 + 1, end, max);
	merge(arr, start, (start + end) / 2, end, max);

}
template<typename T>
void mergeSort(T* arr, int size) {
	T max = arr[0];
	for (int i = 0; i < size; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	mainMergeSort(arr, 0, size - 1, max);
}

int main() {
	srand(time(NULL));
	const int size = 300000;

	int* arr = new int[size];
	for (int i = 0; i < size; i++) {
		arr[i] = rand() % 20001 - 10000;
	}


	int* arr2 = new int[size];
	for (int i = 0; i < size; i++) {
		arr2[i] = rand() % 20001 - 1000;
	}


	
	//-------
	auto beg = chrono::high_resolution_clock::now();
	insertionSort(arr, size);
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(end - beg);
	cout << "insertion sort timer:" <<fixed<< setprecision(2) <<duration.count()/1000.0<<" s"<<endl;
	//--------	
	beg = chrono::high_resolution_clock::now();
	mergeSort(arr2, size);
	
	end = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::milliseconds>(end - beg);
	cout << "merge sort timer:" << fixed << setprecision(2) << duration.count() / 1000.0 << " s" << endl;
	//--------
}
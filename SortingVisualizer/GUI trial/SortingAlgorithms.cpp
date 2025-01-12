#include <iostream>
#include <vector>
#include <string>
#include <Header1.h>
using namespace std;



template <typename T>
class SortingAlgorithms {
public:


	template <typename T>
	void Swap(T& a, T& b) {


		T temp = a;
		a = b;
		b = temp;


	}


	template <class T>
	int getmax(vector<T>& v) {
		int  max = v[0];
		for (int i = 0; i < v.size()-1;i++) {
			if (v[i] > max) max = v[i];
		}
		return max;
	}
	template <class T>
	void count_sort(vector<T>& v, int exp) {
		int count[10] = { 0 };
		int output[v.size()];
		for (auto it : v) {
			count[(it / exp) % 10]++;
		}
		for (int i = 1; i < v.size(); i++) {
			v[i] += v[i - 1];
		}
		for (int j = v.size() - 1; j >= 0; j--) {
			output[count[(v[i] / exp) % 10]] = v[i];
		}
		for (int k = v.size() - 1; k >= 0; k--) {
			v[k] = output[k];
		}

	}
	template <class T>
	void radix_sort(vector<T>& v) {
		int m = getmax(v);
		int exp = 1;
		while (m != 0) {
			count_sort(v, i);
			m /= 10;
			exp *= 10;
		}
	}

	template <typename T>
	void insertionSort(vector<T>& vec) {
		for (size_t i = 1; i < vec.size(); ++i) {
			T key = vec[i];
			size_t j = i;

			while (j > 0 && vec[j - 1] > key) {
				vec[j] = vec[j - 1];
				--j;
			}

			vec[j] = key;
		}
	}
	template <typename type>
	void Heapify(vector<type>& v, int n, int i) {

		int largest = i;
		int left = i * 2 + 1;
		int right = i * 2 + 2;

		if (left<n && v[left]>v[largest]) {
			largest = left;
		}
		if (right<n && v[right]>v[largest]) {
			largest = right;
		}

		if (largest != i) {
			type temp = v[largest];
			v[largest] = v[i];
			v[i] = temp;

			Heapify(v, n, largest);

		}





	}

	template <typename type>
	void HeapSort(vector<type>& v, int n) {

		for (int i = (n / 2) - 1; i >= 0; i--) {
			Heapify(v, n, i);
		}

		for (int i = n - 1; i >= 0; i--) {

			type temp = v[i];
			v[i] = v[0];
			v[0] = temp;

			Heapify(v, i, 0);

		}


	}
	template <typename t>
	void merge(vector<t>& v, int left, int right, int mid) {

		int leftSize = mid - left + 1;
		int rightSize = right - mid;

		vector<int> leftSide(leftSize), rightSide(rightSize);

		for (int i = 0; i < leftSize; i++) {
			leftSide[i] = v[left + i];
		}
		for (int i = 0; i < rightSize; i++) {
			rightSide[i] = v[mid + 1 + i];
		}

		int i = 0, j = 0;
		int k = left;
		while (i < leftSize && j < rightSize) {
			if (leftSide[i] <= rightSide[j]) {
				v[k] = leftSide[i];
				i++;

			}
			else {
				v[k] = rightSide[j];
				j++;

			}
			k++;

		}
		while (i < leftSize) {
			v[k] = leftSide[i];
			i++;
			k++;
		}
		while (j < rightSize) {
			v[k] = rightSide[j];
			j++;
			k++;
		}




	}









	template <typename t>
	void mergeSort(vector<t>& v, int left, int right) {

		if (left >= right) { return; }

		else {
			int mid = (right + left) / 2;
			mergeSort(v, left, mid);
			mergeSort(v, mid + 1, right);
			merge(v, left, right, mid);

		}

	}
	template<typename Type>
	void QuickSort(vector<Type>& array, int length, bool ascending) {
		srand(time(NULL));
		QuickSort_recursion(array, 0, length - 1, ascending);
	}

	template<typename Type>
	void QuickSort_recursion(vector<Type>& array, int low, int high, bool ascending) {
		if (low < high) {
			int pivot_index = partition(array, low, high, ascending);
			QuickSort_recursion(array, low, pivot_index - 1, ascending);
			QuickSort_recursion(array, pivot_index + 1, high, ascending);
		}
	}

	template<typename Type>
	int partition(vector<Type>& array, int low, int high, bool ascending) {
		int pivot_index = low + (rand() % (high - low + 1));

		Swap(array[pivot_index], array[high]);

		Type pivot_value = array[high];
		int i = low;

		for (int j = low; j < high; j++) {

			if ((ascending && array[j] <= pivot_value) || (!ascending && array[j] >= pivot_value)) {
				Swap(array[i], array[j]);
				i++;
			}
		}
		Swap(array[i], array[high]);
		return i;
	}
	template <typename Type>
	void selectionSort(vector<Type>& arr, int n) {
		for (int i = 0; i < n - 1; i++) {
			int minIndex = i;
			for (int j = i + 1; j < n; j++) {
				if (arr[j] < arr[minIndex]) {
					minIndex = j;
				}
			}

			int temp = arr[minIndex];
			arr[minIndex] = arr[i];
			arr[i] = temp;
		}
	}

	template <typename T>
	void bubbleSort(vector<T>& arr, const int n) {


		bool sorted = true;
		for (int i = 0; i < n - 1; i++) {


			for (int j = 0; j < n - i - 1; j++) {
				if (arr[j] > arr[j + 1]) {
		
					Swap(arr[j], arr[j + 1]);
					sorted = false;
				}
			}

			
			if (sorted)
				break;
		}
	}
	template <typename T>
	void displayArray(vector<T>& arr, int n) {
		for (int i = 0; i < n; i++) {
			cout << arr[i] << " ";
		}
		cout << std::endl;
	}

};



int main() {



	vector<int> v;
	int n, element, choice;
	bool ascending;
	SortingAlgorithms<int> SA;

	cout << "Enter the number of elements in the array: ";
	cin >> n;
	cout << "Enter the elements of the array: ";
	for (int i = 0; i < n; i++) {
		cin >> element;
		v.push_back(element);
	}

	cout << "Choose Sorting Algorithm:\n"
		<< "1. Quick Sort\n"
		<< "2. Merge Sort\n"
		<< "3. Heap Sort\n"
		<< "4. Bubble Sort\n"
		<< "5. Insertion Sort\n"
		<< "6. Selection Sort\n"
		<< "7. Radix Sort (Only for integers)\n";
	cin >> choice;

	if (choice != 7) {
		cout << "Ascending (1) or Descending (0)? ";
		cin >> ascending;
	}

	switch (choice) {
	case 1: SA.QuickSort(v, n, ascending); break;
	case 2: SA.mergeSort(v, 0, n-1); break;
	case 3: SA.HeapSort(v, n); break;
	case 4: SA.bubbleSort(v, n); break;
	case 5: SA.insertionSort(v);  break;
	case 6: SA.selectionSort(v, n);  break;
	case 7: SA.radix_sort(v);  break;
	default: cout << "Invalid choice!"; return 1;
	}



	cout << "Sorted Array:" << endl;
	SA.displayArray(v,n);









	return 0;

}
#pragma once
#include <iostream>
#include <Vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <iostream>
#include <sstream>
#include <algorithm> 
#include "CustomVector.h"

using namespace std;

template <typename t>
class SortingAlgorithms {
private:
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;
	const sf::Color BAR_COLOR = sf::Color(255, 0, 0);

public:

	// Swap function
	void Swap(t& a, t& b);

	;

	// Counting sort helper function

	void count_sort(Vector<t>& v, int exp, sf::RenderWindow& window, sf::Font& font, int maxValue, int animationSpeed,bool ascending, Vector<t>& sortedArr);

	// Radix sort function
	void radix_sort(Vector<t>& v, int maxValue, sf::RenderWindow& window, sf::Font& font, sf::Sound& swapSound, int animationSpeed, bool ascending, Vector<t>& sortedArr);


	// Insertion sort

	void insertionSort(Vector<t>& vec, int maxValue, sf::RenderWindow& window, sf::Font& font, sf::Sound& swapSound, int animationSpeed, bool ascending, Vector<t>& sortedArr);

	// Heapify function for HeapSort
	void Heapify(Vector<t>& v, int n, int i, sf::RenderWindow& window, sf::Font& font, int maxValue, sf::Sound& swapSound, int animationSpeed, bool ascending, Vector<t>& sortedArr);

	// HeapSort function
	void HeapSort(Vector<t>& v, int n, sf::RenderWindow& window, sf::Font& font, int maxValue, sf::Sound& swapSound, int animationSpeed, bool ascending, Vector<t>& sortedArr);

	// Merge function for MergeSort
	void merge(sf::RenderWindow& window, Vector<t>& arr, sf::Font& font, int maxValue, int left, int mid, int right, sf::Sound& swapSound, int animationSpeed, bool ascending, Vector<t>& sortedArr);

	// MergeSort function
	void mergeSort(sf::RenderWindow& window, Vector<t>& arr, sf::Font& font, int maxValue, int left, int right, sf::Sound& swapSound, int animationSpeed, bool ascending, Vector<t>& sortedArr);

	// QuickSort function
	/*
	void QuickSort(Vector<T>& array, int length, bool ascending, sf::RenderWindow& window, sf::Font& font, sf::Sound& swapSound, sf::Sound& finishSound, bool ascending);
	*/
	// Recursive QuickSort function
	void QuickSort_recursion(Vector<t>& arr, int low, int high, int maxValue, sf::RenderWindow& window, sf::Font& font, sf::Sound& swapSound, int animationSpeed, bool ascending, Vector<t>& sortedArr);
	// Partition function for QuickSort
	int partition(Vector<t>& arr, int low, int high, int maxValue, sf::RenderWindow& window, sf::Font& font, sf::Sound& swapSound, int animationSpeed, bool ascending, Vector<t>& sortedArr);

	void QuickSort_recursion_aux(Vector<t>& arr, int low, int high, bool ascending);
	// Partition function for QuickSort
	int partition_aux(Vector<t>& arr, int low, int high,  bool ascending);

	// SelectionSort function
	void selectionSort(Vector<t>& arr, int n, int maxValue, sf::RenderWindow& window, sf::Font& font, sf::Sound& swapSound, int animationSpeed, bool ascending, Vector<t>& sortedArr);

	// BubbleSort function
	void bubbleSort(Vector<t>& arr, int n, int maxValue, sf::RenderWindow& window, sf::Font& font, sf::Sound& swapSound, int animationSpeed, bool ascending, Vector<t>& sortedArr);
	void drawBars(sf::RenderWindow& window,  Vector<t>& arr, sf::Font& font, int maxValue, Vector<t>& sortedArr,int current = -1, int minIndex = -1, float offsetX1 = 0, float offsetY1 = 0, float offsetX2 = 0, float offsetY2 = 0);
	void animateSwap(sf::RenderWindow& window, Vector<t>& arr, sf::Font& font, int maxValue, int index1, int index2, int animationSpeed, Vector<t>& sortedArr);
};



template <typename t>
void SortingAlgorithms<t>::Swap(t& a, t& b) {


	t temp = a;
	a = b;
	b = temp;


}




template<typename t>
void SortingAlgorithms<t>::drawBars(sf::RenderWindow& window,  Vector<t>& arr, sf::Font& font, int maxValue, Vector<t>& sortedArr,
	int current, int minIndex, float offsetX1, float offsetY1,
	float offsetX2, float offsetY2)
{
	window.clear();
	int numBars = arr.getSize();
	if (numBars == 0) {
		window.display();
		return;
	}

	int barWidth = (WINDOW_WIDTH / numBars) - 10;
	float scaleFactor = static_cast<float>(WINDOW_HEIGHT - 50) / maxValue;

	for (size_t i = 0; i < arr.getSize(); i++) {
		float barHeight = arr[i] * scaleFactor;
		sf::RectangleShape bar(sf::Vector2f(barWidth, barHeight));

		float xPosition = i * (barWidth + 10);
		float yPosition = WINDOW_HEIGHT - barHeight - 25;

		if (i == current) {
			bar.setPosition(xPosition + offsetX1, yPosition + offsetY1);
			bar.setFillColor(sf::Color::Blue);
		}
		else if (i == minIndex) {
			bar.setPosition(xPosition + offsetX2, yPosition + offsetY2);
			bar.setFillColor(sf::Color::Blue);
		}
		else if (arr[i] == sortedArr[i]) {
			bar.setPosition(xPosition, yPosition);
			bar.setFillColor(sf::Color::Green);

		}
		else {
			bar.setPosition(xPosition, yPosition);
			bar.setFillColor(BAR_COLOR);
		}

		window.draw(bar);

		sf::Text label(to_string(arr[i]), font, 15);
		float labelX = bar.getPosition().x + barWidth / 2 - label.getGlobalBounds().width / 2;
		float labelY = bar.getPosition().y - label.getGlobalBounds().height - 5;
		label.setPosition(labelX, labelY);
		label.setFillColor(sf::Color::White);
		window.draw(label);
	}
	window.display();
}



// Function to animate the swapping of two bars
template<typename t>
void SortingAlgorithms<t>::animateSwap(sf::RenderWindow& window, Vector<t>& arr, sf::Font& font, int maxValue, int index1, int index2, int animationSpeed, Vector<t>& sortedArr)
{
	float totalFrames = 50.0;
	int barWidth = (WINDOW_WIDTH / arr.getSize()) - 10;

	for (float frame = 0; frame <= totalFrames; frame++) {
		float progress = frame / totalFrames;
		float offsetX1 = (index2 - index1) * barWidth * progress;
		float offsetX2 = (index1 - index2) * barWidth * progress;

		float offsetY = -4 * 100 * progress * (1 - progress);

		drawBars(window, arr, font, maxValue, sortedArr,index1, index2, offsetX1, offsetY, offsetX2, offsetY);



		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(animationSpeed / 50.0f)));
	}

	swap(arr[index1], arr[index2]);
	drawBars(window, arr, font, maxValue, sortedArr);
}



template <typename t>
void SortingAlgorithms<t>::count_sort(Vector<t>& v, int exp, sf::RenderWindow& window, sf::Font& font, int maxValue, int animationSpeed, bool ascending, Vector<t>& sortedArr) {
	Vector<t> count(10, 0); 
	Vector<t> output(v.getSize());


	for (int num : v) {
		count[(num / exp) % 10]++;
	}

	if (ascending) {

		for (int i = 1; i < 10; i++) {
			count[i] += count[i - 1];
		}
	}
	else {
		for (int i = 8; i >= 0; i--) {
			count[i] += count[i + 1];
		}
	}

	for (int j = v.getSize() - 1; j >= 0; j--) {
		int digit = (v[j] / exp) % 10;
		output[count[digit] - 1] = v[j];
		count[digit]--;
	}

	for (int k = 0; k < v.getSize(); k++) {
		v[k] = output[k];
	}
	drawBars(window, v, font, maxValue,sortedArr);
}


template <typename t>
void SortingAlgorithms<t>::radix_sort(Vector<t>& v, int maxValue, sf::RenderWindow& window, sf::Font& font, sf::Sound& swapSound, int animationSpeed, bool ascending, Vector<t>& sortedArr) {
	int m = maxValue;
	for (int exp = 1; m / exp > 0; exp *= 10) {
		count_sort(v, exp, window, font, maxValue, animationSpeed, ascending, sortedArr);
		drawBars(window, v, font, maxValue,  sortedArr);

		std::this_thread::sleep_for(std::chrono::milliseconds(animationSpeed));

	}
	drawBars(window, v, font, maxValue, sortedArr);


}

template <typename t>
void SortingAlgorithms<t>::insertionSort(Vector<t>& vec, int maxValue, sf::RenderWindow& window, sf::Font& font, sf::Sound& swapSound, int animationSpeed, bool ascending, Vector<t>& sortedArr) {
	for (size_t i = 1; i < vec.getSize(); ++i) {
		t key = vec[i];
		size_t j = i;

		if (ascending) {
			while (j > 0 && vec[j - 1] > key) {
				vec[j] = vec[j - 1];
				--j;
				drawBars(window, vec, font, maxValue, sortedArr);
				std::this_thread::sleep_for(std::chrono::milliseconds(animationSpeed));
			}
		}
		else{
			while (j > 0 && vec[j - 1] < key) {
				vec[j] = vec[j - 1];
				--j;
				drawBars(window, vec, font, maxValue,sortedArr);
				std::this_thread::sleep_for(std::chrono::milliseconds(animationSpeed));
			}

		}

		vec[j] = key;
		drawBars(window, vec, font, maxValue,  sortedArr);
		std::this_thread::sleep_for(std::chrono::milliseconds(animationSpeed));
	}
	drawBars(window, vec, font, maxValue,  sortedArr);

}

template <typename t>
void SortingAlgorithms<t>::Heapify(Vector<t>& v, int n, int i, sf::RenderWindow& window, sf::Font& font, int maxValue, sf::Sound& swapSound, int animationSpeed, bool ascending, Vector<t>& sortedArr) {
	if (ascending) {
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
			swapSound.play();
			animateSwap(window, v, font, maxValue, i, largest, animationSpeed, sortedArr);

			Heapify(v, n, largest, window, font, maxValue, swapSound, animationSpeed, ascending, sortedArr);

		}
	}
	else {
		int smallest = i;
		int left = i * 2 + 1;
		int right = i * 2 + 2;

		if (left<n && v[left]<v[smallest]) {
			smallest = left;
		}
		if (right<n && v[right]<v[smallest]) {
			smallest = right;
		}

		if (smallest != i) {

			swapSound.play();
			animateSwap(window, v, font, maxValue, i, smallest, animationSpeed, sortedArr);

			Heapify(v, n, smallest, window, font, maxValue, swapSound, animationSpeed, ascending, sortedArr);

		}
	}





}

template <typename t>
void SortingAlgorithms<t>::HeapSort(Vector<t>& v, int n, sf::RenderWindow& window, sf::Font& font, int maxValue, sf::Sound& swapSound, int animationSpeed, bool ascending, Vector<t>& sortedArr)
{

	for (int i = (n / 2) - 1; i >= 0; i--) {
		Heapify(v, n, i, window, font, maxValue, swapSound, animationSpeed, ascending,sortedArr);
	}

	

	for (int i = n - 1; i >= 0; i--) {

		swapSound.play();
		animateSwap(window, v, font, maxValue, i, 0, animationSpeed, sortedArr);

		Heapify(v, i, 0, window, font, maxValue, swapSound, animationSpeed, ascending, sortedArr);

	}

	drawBars(window, v, font, maxValue, sortedArr);



}

template <typename t>
void SortingAlgorithms<t>::merge(sf::RenderWindow& window, Vector<t>& arr, sf::Font& font, int maxValue, int left, int mid, int right, sf::Sound& swapSound, int animationSpeed, bool ascending, Vector<t>& sortedArr)
{
	int leftgetSize = mid - left + 1;
	int rightgetSize = right - mid;


	vector<int> leftSide(leftgetSize), rightSide(rightgetSize);

	for (int i = 0; i < leftgetSize; i++) {
		leftSide[i] = arr[left + i];
	}
	for (int i = 0; i < rightgetSize; i++) {
		rightSide[i] = arr[mid + 1 + i];
	}

	int i = 0, j = 0;
	int k = left;
	while (i < leftgetSize && j < rightgetSize) {
		if ((ascending && leftSide[i] <= rightSide[j])||(!ascending&& leftSide[i] >= rightSide[j])) {
			arr[k] = leftSide[i];
			i++;
		}
		else {
			arr[k] = rightSide[j];
			j++;
		}
		k++;
		drawBars(window, arr, font, maxValue, sortedArr);
		std::this_thread::sleep_for(std::chrono::milliseconds(animationSpeed));

	}

	while (i < leftgetSize) {
		arr[k] = leftSide[i];
		i++;
		k++;
		drawBars(window, arr, font, maxValue,  sortedArr);
		std::this_thread::sleep_for(std::chrono::milliseconds(animationSpeed));

	}

	while (j < rightgetSize) {
		arr[k] = rightSide[j];
		j++;
		k++;
		drawBars(window, arr, font, maxValue, sortedArr);
		std::this_thread::sleep_for(std::chrono::milliseconds(animationSpeed));

	}

	drawBars(window, arr, font, maxValue, sortedArr);


}

template <typename t>
void SortingAlgorithms<t>::mergeSort(sf::RenderWindow& window, Vector<t>& arr, sf::Font& font, int maxValue, int left, int right, sf::Sound& swapSound, int animationSpeed, bool ascending, Vector<t>& sortedArr)
{
	if (left >= right) {
		return;
	}

	int mid = (right + left) / 2;
	mergeSort(window, arr, font, maxValue, left, mid, swapSound, animationSpeed, ascending, sortedArr);
	mergeSort(window, arr, font, maxValue, mid + 1, right, swapSound, animationSpeed, ascending, sortedArr);
	merge(window, arr, font, maxValue, left, mid, right, swapSound, animationSpeed, ascending, sortedArr);




}

template<typename t>
void QuickSort(Vector<t>& array, int length, bool ascending) {
	srand(time(NULL));
	QuickSort_recursion(array, 0, length - 1, ascending);
}



template<typename t>
void SortingAlgorithms<t>::QuickSort_recursion(Vector<t>& arr, int low, int high, int maxValue, sf::RenderWindow& window, sf::Font& font, sf::Sound& swapSound, int animationSpeed, bool ascending, Vector<t>& sortedArr) {
	if (low < high) {
		int pivot_index = partition(arr, low, high, maxValue, window, font, swapSound, animationSpeed, ascending,sortedArr);
		QuickSort_recursion(arr, low, pivot_index - 1, maxValue, window, font, swapSound, animationSpeed, ascending,sortedArr);
		QuickSort_recursion(arr, pivot_index + 1, high, maxValue, window, font, swapSound, animationSpeed, ascending, sortedArr);
	}
}

template<typename t>
int SortingAlgorithms<t>::partition(Vector<t>& arr, int low, int high, int maxValue, sf::RenderWindow& window, sf::Font& font, sf::Sound& swapSound, int animationSpeed, bool ascending, Vector<t>& sortedArr) {
	int pivot_index = low + (rand() % (high - low + 1));
	swapSound.play();
	animateSwap(window, arr, font, maxValue, pivot_index, high, animationSpeed/3, sortedArr);
	t pivot_value = arr[high];
	int i = low;
	for (int j = low; j < high; ++j) {
		if ((ascending && arr[j] <= pivot_value) || (!ascending && arr[j] >= pivot_value)) {
			swapSound.play();
			animateSwap(window, arr, font, maxValue, i, j, animationSpeed/3, sortedArr);
			++i;
		}
	}
	swapSound.play();
	animateSwap(window, arr, font, maxValue, i, high, animationSpeed/3, sortedArr);

	return i; 
}

template<typename t>
void SortingAlgorithms<t>::QuickSort_recursion_aux(Vector<t>& arr, int low, int high,bool ascending) {
	if (low < high) {
		int pivot_index = partition_aux(arr, low, high,ascending);
		QuickSort_recursion_aux(arr, low, pivot_index - 1, ascending);
		QuickSort_recursion_aux(arr, pivot_index + 1, high, ascending);
	}
}

template<typename t>
int SortingAlgorithms<t>::partition_aux(Vector<t>& arr, int low, int high,bool ascending) {
	int pivot_index = low + (rand() % (high - low + 1));
	swap(arr[pivot_index], arr[high]);
	t pivot_value = arr[high];
	int i = low;
	for (int j = low; j < high; ++j) {
		if ((ascending && arr[j] <= pivot_value) || (!ascending && arr[j] >= pivot_value)) {
			swap(arr[j], arr[i]);
			++i;
		}
	}
	swap(arr[i], arr[high]);

	return i;
}


template <typename t>
void SortingAlgorithms<t>::selectionSort(Vector<t>& arr, int n, int maxValue, sf::RenderWindow& window, sf::Font& font, sf::Sound& swapSound, int animationSpeed, bool ascending, Vector<t>& sortedArr) {
	
	for (int i = 0; i < n - 1; i++) {
		int Index = i;
		for (int j = i + 1; j < n; j++) {
			if (ascending) {
				if (arr[j] < arr[Index]) {
					Index = j;
				}
			}
			else{
				if (arr[j] > arr[Index]) {
					Index = j;
				}

			}
		}
		swapSound.play();
		animateSwap(window, arr, font, maxValue, Index, i, animationSpeed/3, sortedArr);

	}

	drawBars(window, arr, font, maxValue,  sortedArr);



}

template <typename t>
void SortingAlgorithms<t>::bubbleSort(Vector<t>& arr, int n, int maxValue, sf::RenderWindow& window, sf::Font& font, sf::Sound& swapSound, int animationSpeed, bool ascending, Vector<t>& sortedArr) {

	for (int i = 0; i < n - 1; i++) {


		for (int j = 0; j < n - i - 1; j++) {
			if (ascending) {
				if (arr[j] > arr[j + 1]) {
					swapSound.play();
					animateSwap(window, arr, font, maxValue, j, j + 1, animationSpeed/3, sortedArr);
				}
			}
			else {
				if (arr[j] < arr[j + 1]) {
					swapSound.play();
					animateSwap(window, arr, font, maxValue, j, j + 1, animationSpeed/3, sortedArr);
				}

			}


		}

	}


	drawBars(window, arr, font, maxValue, sortedArr); // Draw the final sorted array

}
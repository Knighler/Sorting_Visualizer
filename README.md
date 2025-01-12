# Sorting Algorithm Visualizer

This project is a graphical application that visualizes sorting algorithms using the SFML library. It allows users to interactively input data, choose a sorting algorithm, and observe the sorting process step by step.

## Features
- **User Input:** Enter up to 15 numbers for sorting.
- **Sorting Algorithms:** Supports multiple algorithms including Bubble Sort, Selection Sort, Insertion Sort, Merge Sort, Quick Sort, Radix Sort, and Heap Sort.
- **Customization:** Choose sorting order (ascending/descending) and animation speed (slow, normal, fast).
- **Graphical Interface:** Visualize sorting in real-time with a user-friendly interface.
- **Sound Effects:** Plays sound effects during swaps and upon sorting completion.
- **Restart Option:** Restart the sorting process after completion.

---

## Requirements
- **SFML Library:** Install SFML for rendering graphics, handling events, and playing sounds.
- **C++ Compiler:** A modern C++ compiler supporting C++11 or later.

---

## Setup and Installation
1. **Install SFML:** Follow the installation guide for SFML specific to your platform (Windows/Linux/Mac).
2. **Clone Repository:** Download or clone the project to your local machine.
3. **File Paths:** Ensure the file paths for sound and texture assets match your system:
    - `E:/VS projects/SortingVisualizer/maro-jump-sound-effect_1.wav`
    - `E:/VS projects/SortingVisualizer/untitled_3.wav`
    - `E:/VS projects/SortingVisualizer/brown-brick-wall-texture-wall-bricks_146714-3037.png`
    - Adjust these paths in the source code if needed.
4. **Compile:** Use your preferred compiler or IDE to compile the project.

---

## How to Use
### Input Data
1. Launch the application.
2. Enter up to 15 numbers separated by spaces in the input prompt.
3. Press **Enter** to confirm input.

### Choose Sorting Algorithm
1. Select one of the sorting algorithms displayed on the menu.
2. Options include Bubble Sort, Selection Sort, Insertion Sort, Merge Sort, Quick Sort, Radix Sort, and Heap Sort.

### Choose Sorting Order
1. Choose between **Ascending** or **Descending** order.

### Choose Animation Speed
1. Select one of the three animation speeds: Slow, Normal, or Fast.

### Visualization
1. Watch the sorting process visualized with graphical bars and sound effects.
2. Once sorting completes, an end screen appears.

### Restart or Exit
1. Choose to restart the sorting process or close the application.

---

## Code Overview
### Key Components
- **`handleUserInput`:** Captures user input and populates the array.
- **`displaySortMenu`:** Displays the sorting algorithm selection menu.
- **`displayOrderMenu`:** Allows users to choose sorting order.
- **`displaySpeedMenu`:** Lets users select animation speed.
- **`displayEndScreen`:** Shows the end screen with the option to restart.
- **`SortingAlgorithms`:** A class encapsulating various sorting algorithm implementations.

### Dependencies
- **SFML Graphics and Audio Modules**: Used for rendering and sound.
- **CustomVector**: A custom vector implementation.
- **AlgosHeader**: Contains sorting algorithm definitions.

---

## Sound and Visual Assets
- **Sound Effects:**
  - `maro-jump-sound-effect_1.wav`: Played during element swaps.
  - `untitled_3.wav`: Played upon sorting completion.
- **Background Texture:**
  - `brown-brick-wall-texture-wall-bricks_146714-3037.png`: Used as the application's background image.

---

## Possible Improvements
1. **Dynamic Input Size:** Allow larger inputs dynamically adjusted to fit the screen.
2. **More Algorithms:** Add support for additional sorting algorithms like Shell Sort or Counting Sort.
3. **Improved UI:** Enhance the graphical design for better user experience.
4. **Cross-Platform Support:** Make file paths relative and package assets for easier portability.

---

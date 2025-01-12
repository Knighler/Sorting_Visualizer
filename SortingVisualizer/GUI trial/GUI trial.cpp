

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <iostream>

#include <sstream>
#include <algorithm> 
#include<iostream>
#include "AlgosHeader.h"
#include "CustomVector.h"

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const sf::Color BAR_COLOR = sf::Color(255, 0, 0);

template<typename t>
void handleUserInput(sf::RenderWindow& window, Vector<t>& arr, sf::Font& font, const sf::RectangleShape& background) {
    sf::Text prompt("Enter up to 15 numbers separated by spaces\nPress Enter to finish:", font, 20);
    prompt.setFillColor(sf::Color::White);
    prompt.setPosition(10, 10);

    sf::Text userInput("", font, 20);
    userInput.setFillColor(sf::Color::Yellow);
    userInput.setPosition(10, 100);

    string input = "";
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b' && !input.empty()) {
                    input.pop_back();
                }
                else if (event.text.unicode == '\r') {
                    
                    stringstream ss(input);
                    string token;
                    while (ss >> token) {
                        try {
                            double number = stod(token); 
                            arr.push_back(number);      
                        }
                        catch (const invalid_argument&) {
                            cout << "Invalid input: " << token << endl;
                          
                        }
                        if (arr.getSize() >= 15) break; 
                    }
                    return;
                }
                else if (event.text.unicode >= 32 && event.text.unicode < 128) {
                    input += static_cast<char>(event.text.unicode);
                }
            }
        }

        userInput.setString(input);

        window.clear();
        window.draw(background);
        window.draw(prompt);
        window.draw(userInput);
        window.display();

    }
}


struct SortChoice {
    int algorithmIndex;
    bool ascending;
};


SortChoice displaySortMenu(sf::RenderWindow& window, sf::Font& font, const sf::RectangleShape& background) {
    sf::Text title("Choose Sorting Algorithm", font, 40);
    title.setFillColor(sf::Color::Yellow);
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(2);
    title.setPosition(WINDOW_WIDTH / 2 - title.getGlobalBounds().width / 2, 50);

    Vector<string> sortNames; 
    sortNames.push_back("Bubble Sort");
    sortNames.push_back("Selection Sort");
    sortNames.push_back("Insertion Sort");
    sortNames.push_back("Merge Sort");
    sortNames.push_back("Quick Sort");
    sortNames.push_back("Radix Sort");
    sortNames.push_back("Heap Sort");

    Vector<sf::RectangleShape> buttons;
    Vector<sf::Text> buttonTexts;

    for (size_t i = 0; i < sortNames.getSize(); ++i) {
        sf::RectangleShape button(sf::Vector2f(200, 40));
        button.setPosition(WINDOW_WIDTH / 2 - 100, 150 + i * 50);
        button.setFillColor(sf::Color(50, 150, 50));
        buttons.push_back(button);

        sf::Text buttonText(sortNames[i], font, 20);
        buttonText.setFillColor(sf::Color::White);
        buttonText.setPosition(button.getPosition().x + 10, button.getPosition().y + 5);
        buttonTexts.push_back(buttonText);
    }

    SortChoice choice;
    choice.algorithmIndex = -1;
    choice.ascending = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return choice;
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                for (size_t i = 0; i < buttons.getSize(); ++i) {
                    if (buttons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        choice.algorithmIndex = static_cast<int>(i);
                        return choice;
                    }
                }
            }
        }

        window.clear();
        window.draw(background);
        window.draw(title);
        for (size_t i = 0; i < buttons.getSize(); ++i) {
            window.draw(buttons[i]);
            window.draw(buttonTexts[i]);
        }
        window.display();
    }

    return choice;
}


bool displayOrderMenu(sf::RenderWindow& window, sf::Font& font, const sf::RectangleShape& background) {
    sf::Text title("Choose Sorting Order", font, 40);
    title.setFillColor(sf::Color::Yellow);
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(2);
    title.setPosition(WINDOW_WIDTH / 2 - title.getGlobalBounds().width / 2, 50);

    sf::RectangleShape ascendingButton(sf::Vector2f(150, 40));
    ascendingButton.setPosition(WINDOW_WIDTH / 2 - 200, 200);
    ascendingButton.setFillColor(sf::Color(50, 150, 50));

    sf::RectangleShape descendingButton(sf::Vector2f(150, 40));
    descendingButton.setPosition(WINDOW_WIDTH / 2 + 50, 200);
    descendingButton.setFillColor(sf::Color(150, 50, 50));

    sf::Text ascendingText("Ascending", font, 20);
    ascendingText.setFillColor(sf::Color::White);
    ascendingText.setPosition(ascendingButton.getPosition().x + 10, ascendingButton.getPosition().y + 5);

    sf::Text descendingText("Descending", font, 20);
    descendingText.setFillColor(sf::Color::White);
    descendingText.setPosition(descendingButton.getPosition().x + 10, descendingButton.getPosition().y + 5);

    bool ascending = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return ascending;
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (ascendingButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    return true;
                }
                else if (descendingButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    return false;
                }
            }
        }

        window.clear();
        window.draw(background);
        window.draw(title);
        window.draw(ascendingButton);
        window.draw(descendingButton);
        window.draw(ascendingText);
        window.draw(descendingText);
        window.display();
    }

    return ascending;
}

int displaySpeedMenu(sf::RenderWindow& window, sf::Font& font, const sf::RectangleShape& background) {
    sf::Text title("Choose Animation Speed", font, 40);
    title.setFillColor(sf::Color::Yellow);
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(2);
    title.setPosition(WINDOW_WIDTH / 2 - title.getGlobalBounds().width / 2, 50);

    Vector<string> speedLabels;
    speedLabels.push_back("Slow");
    speedLabels.push_back("Normal");
    speedLabels.push_back("Fast");

    Vector<int> speedValues;
    speedValues.push_back(650);
    speedValues.push_back(350);
    speedValues.push_back(120);

  
    Vector<sf::RectangleShape> buttons;
    Vector<sf::Text> buttonTexts;

    for (size_t i = 0; i < speedLabels.getSize(); ++i) {
        sf::RectangleShape button(sf::Vector2f(200, 50));
        button.setPosition(WINDOW_WIDTH / 2 - 100, 150 + i * 70);
        button.setFillColor(sf::Color(50, 150, 50));
        buttons.push_back(button);

        sf::Text buttonText(speedLabels[i], font, 25);
        buttonText.setFillColor(sf::Color::White);
        buttonText.setPosition(button.getPosition().x + 50, button.getPosition().y + 10);
        buttonTexts.push_back(buttonText);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return speedValues[1]; 
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                for (size_t i = 0; i < buttons.getSize(); ++i) {
                    if (buttons[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        return speedValues[i];
                    }
                }
            }
        }

        window.clear();
        window.draw(background);
        window.draw(title);
        for (size_t i = 0; i < buttons.getSize(); ++i) {
            window.draw(buttons[i]);
            window.draw(buttonTexts[i]);
        }
        window.display();
    }

    return speedValues[1]; 
}

bool displayEndScreen(sf::RenderWindow& window, sf::Font& font, const sf::RectangleShape& background) {
    sf::Text title("Sorting Completed!", font, 40);
    title.setFillColor(sf::Color::Yellow);
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(2);
    title.setPosition(WINDOW_WIDTH / 2 - title.getGlobalBounds().width / 2, 100);

    sf::RectangleShape restartButton(sf::Vector2f(200, 50));
    restartButton.setPosition(WINDOW_WIDTH / 2 - 100, 300);
    restartButton.setFillColor(sf::Color(50, 150, 50));

    sf::Text restartText("Restart", font, 25);
    restartText.setFillColor(sf::Color::White);
    restartText.setPosition(restartButton.getPosition().x + 50, restartButton.getPosition().y + 10);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return false;
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (restartButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    return true; 
                }
            }
        }

        window.clear();
        window.draw(background);
        window.draw(title);
        window.draw(restartButton);
        window.draw(restartText);
        window.display();
    }
}



int main() {
 
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Sorting Algorithm Visualization");


    sf::SoundBuffer swapBuffer, finishBuffer;
    if (!swapBuffer.loadFromFile("E:/VS projects/SortingVisualizer/maro-jump-sound-effect_1.wav") || !finishBuffer.loadFromFile("E:/VS projects/SortingVisualizer/untitled_3.wav")) {
        cout << "Error loading sound files!" << endl;
        return -1;
    }
    sf::Sound swapSound(swapBuffer), finishSound(finishBuffer);


    sf::Font font;
    if (!font.loadFromFile("E:/VS projects/SortingVisualizer/SuperMario256.ttf")) {
        cout << "Error loading font!" << endl;
        return -1;
    }

    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("E:/VS projects/SortingVisualizer/brown-brick-wall-texture-wall-bricks_146714-3037.png")) {
        cout << "Error loading background image!" << endl;
        return -1;
    }
    sf::RectangleShape background(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    background.setTexture(&bgTexture);


    Vector<int> arr;
    Vector<int> sortedArr;
;
    
    do{
   
    handleUserInput(window, arr, font, background);
    sortedArr = arr;


    SortingAlgorithms<int> sorting;

    if (!arr.empty()) {
 
        int animationSpeed = displaySpeedMenu(window, font, background);
        SortChoice sortChoice = displaySortMenu(window, font, background);

        int maxValue = *max_element(arr.begin(), arr.end());




        if (sortChoice.algorithmIndex != -1) { 
            bool ascending = displayOrderMenu(window, font, background);
            sorting.QuickSort_recursion_aux(sortedArr, 0, arr.getSize() - 1, ascending);

            switch (sortChoice.algorithmIndex) {
            case 0:
                sorting.bubbleSort(arr, arr.getSize(), maxValue, window, font, swapSound, animationSpeed, ascending, sortedArr);

                break;
            case 1:
                sorting.selectionSort(arr, arr.getSize(), maxValue, window, font, swapSound, animationSpeed, ascending, sortedArr);

                break;
            case 2:
                sorting.insertionSort(arr, maxValue, window, font, swapSound, animationSpeed, ascending, sortedArr);

                break;
            case 3:
                sorting.mergeSort(window, arr, font, maxValue, 0, arr.getSize() - 1, swapSound, animationSpeed, ascending, sortedArr);

                break;
            case 4:
                sorting.QuickSort_recursion(arr, 0, arr.getSize() - 1, maxValue, window, font, swapSound, animationSpeed, ascending, sortedArr);

                break;
            case 5:

                sorting.radix_sort(arr, maxValue, window, font, swapSound, animationSpeed, ascending, sortedArr);

                break;
            case 6:
                sorting.HeapSort(arr, arr.getSize(), window, font, maxValue, swapSound, animationSpeed, ascending, sortedArr);

                break;
            default:
                cout << "Invalid algorithm selection." << endl;
                break;
            }
            finishSound.play();
            std::this_thread::sleep_for(std::chrono::seconds(4));
            displayEndScreen(window, font, background);
        }
        else {
            cout << "No algorithm selected or window closed." << endl;
        }
        arr.clear();
    }
    } while (displayEndScreen(window, font, background));

    cout << "Press Enter to exit..." << endl;

    return 0;

}


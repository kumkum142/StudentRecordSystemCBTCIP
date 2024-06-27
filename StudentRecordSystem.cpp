//#include <iostream>
//#include <limits>
//
//using namespace std;
//
//// Function to validate numerical input
//double getValidatedInput() {
//    double num;
//    while (true) {
//        cin >> num;
//        if (cin.fail()) {
//            cin.clear(); // Clear the error flag
//            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
//            cout << "Invalid input. Please enter a numerical value: ";
//        } else {
//            return num;
//        }
//    }
//}
//
//// Function to display the menu and get the user's choice
//int displayMenu() {
//    int choice;
//    cout << "\nDigital Calculator Menu:\n";
//    cout << "1. Addition\n";
//    cout << "2. Subtraction\n";
//    cout << "3. Multiplication\n";
//    cout << "4. Division\n";
//    cout << "5. Exit\n";
//    cout << "Enter your choice (1-5): ";
//    cin >> choice;
//    return choice;
//}
//
//// Function to perform the chosen operation
//void performOperation(int choice) {
//    double num1, num2;
//    cout << "Enter the first number: ";
//    num1 = getValidatedInput();
//    cout << "Enter the second number: ";
//    num2 = getValidatedInput();
//
//    switch (choice) {
//        case 1:
//            cout << "Result: " << num1 + num2 << endl;
//            break;
//        case 2:
//            cout << "Result: " << num1 - num2 << endl;
//            break;
//        case 3:
//            cout << "Result: " << num1 * num2 << endl;
//            break;
//        case 4:
//            if (num2 != 0) {
//                cout << "Result: " << num1 / num2 << endl;
//            } else {
//                cout << "Error: Division by zero is not allowed.\n";
//            }
//            break;
//        default:
//            cout << "Invalid choice.\n";
//            break;
//    }
//}
//
//int main() {
//    int choice;
//    while (true) {
//        choice = displayMenu();
//        if (choice == 5) {
//            cout << "Exiting the calculator. Goodbye!\n";
//            break;
//        }
//        performOperation(choice);
//    }
//    return 0;
//}

//#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>

// Function to check if a string is a number
bool isNumber(const std::string& str) {
    std::istringstream iss(str);
    double d;
    return iss >> d >> std::ws && iss.eof();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 600), "SFML Calculator");
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return EXIT_FAILURE;
    }

    sf::Text display("", font, 30);
    display.setFillColor(sf::Color::Black);
    display.setPosition(10, 10);

    std::string currentInput = "";
    std::string previousInput = "";
    char operation = '\0';

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                    currentInput += static_cast<char>(event.text.unicode);
                } else if (event.text.unicode == '.') {
                    if (currentInput.find('.') == std::string::npos) {
                        currentInput += '.';
                    }
                } else if (event.text.unicode == '+' || event.text.unicode == '-' || 
                           event.text.unicode == '*' || event.text.unicode == '/') {
                    if (isNumber(currentInput)) {
                        previousInput = currentInput;
                        currentInput = "";
                        operation = static_cast<char>(event.text.unicode);
                    }
                } else if (event.text.unicode == 13) { // Enter key
                    if (isNumber(currentInput) && isNumber(previousInput)) {
                        double num1 = std::stod(previousInput);
                        double num2 = std::stod(currentInput);
                        double result = 0;

                        if (operation == '+') result = num1 + num2;
                        else if (operation == '-') result = num1 - num2;
                        else if (operation == '*') result = num1 * num2;
                        else if (operation == '/') result = num1 / num2;

                        currentInput = std::to_string(result);
                        previousInput = "";
                        operation = '\0';
                    }
                } else if (event.text.unicode == 8) { // Backspace key
                    if (!currentInput.empty()) {
                        currentInput.pop_back();
                    }
                } else if (event.text.unicode == 'c' || event.text.unicode == 'C') {
                    currentInput = "";
                    previousInput = "";
                    operation = '\0';
                }
            }
        }

        display.setString(currentInput);

        window.clear(sf::Color::White);
        window.draw(display);
        window.display();
    }

    return 0;
}

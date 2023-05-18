#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

using namespace std;
int main() {

    sf::Image image;
    if (!image.loadFromFile("images/gkejrghet.png")) { // завантаження зображення
        return 1;
    }

    int imageWidth = image.getSize().x; // отримуємо ширину зображення
    int imageHeight = image.getSize().y; // отримуємо довготу зображення

    int charWidth = 2; // на яку ширину буде один знак
    int charHeight = 4; // на яку висоту буде один знак

    int textWidth = imageWidth / charWidth; // скільки буде символів у кінцевому результаті 
    int textHeight = imageHeight / charHeight;

    char asciiMap[] = " .:-=+*#%@"; // з яких символів буде створений малюнок
    
    std::ofstream outputFile("txtFiles/modification2x4-28.txt");   // Відкриття текстового файлу для запису
    if (!outputFile) {
        return 1;
    }

    for (int y = 0; y < textHeight; ++y) {  
        for (int x = 0; x < textWidth; ++x) {
            int startX = x * charWidth;
            int startY = y * charHeight;

            int sum = 0;
            for (int dy = 0; dy < charHeight; ++dy) {
                for (int dx = 0; dx < charWidth; ++dx) {
                    sf::Color pixelColor = image.getPixel(startX + dx, startY + dy); // отримує заданий піксель
                    int pixelValue = (pixelColor.r + pixelColor.g + pixelColor.b) / 3; // отримує середнє значення яскравості пікселя
                    sum += pixelValue;
                }
            }
            int average = sum / (charWidth * charHeight); // сума яскаравості усіх пікселей ділеться на їхню кількість

            int asciiIndex = average * (sizeof(asciiMap) - 1) / 255; // отримуємо значення для масиву знаків де в сайзоф ми отримуємо розмір масива і віднімаємо один тому що масив почниається з 0 і ділимо на 255 щоб отримати знак з масиву
            char asciiChar = asciiMap[asciiIndex];

            outputFile << asciiChar;
        }
        outputFile << '\n';
    }
    outputFile.close(); // закриття файлу

    return 0;
}

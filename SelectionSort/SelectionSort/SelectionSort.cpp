#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <algorithm>

//Die Texte werden mit einem bestimmten abstand untereinander Positioniert
void renderList(sf::RenderWindow& window, sf::Font font, std::vector<int>& numbersList, int gap, int xPos)
{
    auto yPos = 50;

    for (int e : numbersList)
    {
        sf::Text unsortedT(font, std::to_string(e), 30);
        unsortedT.setPosition(sf::Vector2f(xPos, yPos));
        yPos = yPos + gap;
        window.draw(unsortedT);
    }
}

void addRandomNumToList(std::vector<int>& unsortedList)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(-50, 50);

    for (int i = 0; i < 20; ++i)
    {
        int num = dist(rng);
        unsortedList.push_back(num);
    }
}

// Es wird gecheckt ob der vector leer ist da es sonst einen error gibt falls er leer ist
// Sucht die kleinste Nummer in der Liste
// Wenn die kleinste Nummer gefunden wurde wird sie an die erste Stelle gesetzt und danach rausgelöscht
// Die kleinste nummer wird dann mit einem push back in die sortierte Liste hinzugefügt
void SelectionSort(std::vector<int>& unsortedList, std::vector<int>& sortedList)
{
    if (!unsortedList.empty())
    {
        int smallestNum = 0;

        for (int j = 0 + 1; j < unsortedList.size(); j++)
        {
            if (unsortedList[j] < unsortedList[smallestNum])
            {
                smallestNum = j;
            }
        }

        sortedList.push_back(unsortedList[smallestNum]);
        std::swap(unsortedList[0], unsortedList[smallestNum]);
        unsortedList.erase(unsortedList.begin());
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1000, 900 }), "Selection Sort");

    std::vector<int> unsortedList;
    std::vector<int> sortedList;

    addRandomNumToList(unsortedList);
        
    const sf::Font font("fonts/ariblk.ttf");
    sf::Clock clock;

    sf::Text sortedT(font, "Sortiert", 30);
    sortedT.setPosition(sf::Vector2f(200, 10));

    sf::Text unsortedT(font, "Unsortiert", 30);
    unsortedT.setPosition(sf::Vector2f(600, 10));

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
        {
            sf::Time elapsed1 = clock.getElapsedTime();
            // Wenn man die Taste drückt wird die Function sehr oft ausgeführt deshalb dieser cooldown
            if (elapsed1.asSeconds() > 1.6)
            {
                clock.restart();
                SelectionSort(unsortedList, sortedList);
            }
        }

        window.clear();

        window.draw(sortedT);
        window.draw(unsortedT);

        renderList(window, font, unsortedList, 40, 670);
        renderList(window, font, sortedList, 40, 230);
        window.display();
    }
}
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <algorithm>

// Zeichnet für jede Zahl einen Balken, jegrößer die Zahl desto größer der Balken (5 mal die Zahl)
// Über jedem Balken steht die Zahl als Text
// Größe, Position und Farbe vom Balken werden gesetzt
void drawListBar(sf::RenderWindow& window, const sf::Font& font, std::vector<int>& numbersList, float gap)
{
    float yPos = 900.0f;
    float xPos = 10.0f;

    for (int e : numbersList)
    {
        float barWidth = 20.0f;
        float barHeight = e * 5.0f;

        sf::RectangleShape bar;
        sf::Text barText(font, std::to_string(e), 10);

        xPos = xPos + gap;

        bar.setSize(sf::Vector2f(barWidth, barHeight));
        bar.setPosition(sf::Vector2f(xPos, yPos - barHeight));
        bar.setFillColor(sf::Color::White);
        barText.setPosition(sf::Vector2f(xPos + 2.0f, yPos - barHeight - 20.0f));

        window.draw(bar);
        window.draw(barText);
    }
}

//Die Texte werden mit einem bestimmten abstand untereinander Positioniert
void renderList(sf::RenderWindow& window, sf::Font font, std::vector<int>& numbersList, float gap, float xPos)
{
    float yPos = 50.0f;

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
    std::uniform_int_distribution<int> dist(1, 50);

    for (int i = 0; i < 20; ++i)
    {
        int num = dist(rng);
        unsortedList.push_back(num);
    }  
}

// Es wird gecheckt ob der vector leer ist da es sonst einen error gibt falls er leer ist
// Sucht die kleinste Nummer in der Liste
// Wenn die kleinste nummer gefunden wurde wird sie mit dem selectedInt getauscht
void SelectionSort(sf::RenderWindow& window, std::vector<int>& unsortedList, int& selectedNumber)
{
    if (unsortedList.empty() || selectedNumber < unsortedList.size() - 1)
    {
        int smallestNumber = selectedNumber;

        for (int j = selectedNumber + 1; j < unsortedList.size(); j++)
        {
            if (unsortedList[j] < unsortedList[smallestNumber])
            {
                smallestNumber = j;
            }
        }

        std::swap(unsortedList[selectedNumber], unsortedList[smallestNumber]);
        selectedNumber++;
    }
    else 
    {
        window.close();
    }
}


int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1000, 900 }), "Selection Sort 2");

    std::vector<int> unsortedList;
    int selectedNumber = 0;

    addRandomNumToList(unsortedList);
        
    const sf::Font font("assets/fonts/ariblk.ttf");
    sf::Clock clock;

    sf::Text unsortedT(font, "Nummern", 30);
    unsortedT.setPosition(sf::Vector2f(800, 10));

    sf::Text infoText(font, "Druecke ENTER um die Liste zu Sortieren", 10);
    infoText.setPosition(sf::Vector2f(50, 7.0f));

    sf::Texture texture("assets/img/info.png");
    sf::Sprite infoSprite(texture);
    infoSprite.setScale(sf::Vector2f(0.2f, 0.2f)); 

    sf::Text finishedT(font, "", 20);
    finishedT.setPosition(sf::Vector2f(10, 45));

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            // Key Released ohne Clock-Object
            if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
            {
                SelectionSort(window, unsortedList, selectedNumber);
            }
        }

        finishedT.setString("Abgeschlossen: " + std::to_string(selectedNumber + 1) + "/" + std::to_string(unsortedList.size()));

        window.clear();

        window.draw(unsortedT);
        window.draw(infoSprite);
        window.draw(infoText);
        window.draw(finishedT);

        renderList(window, font, unsortedList, 40.0f, 870.0f);
        drawListBar(window, font, unsortedList, 40.0f);
        window.display();
    }
}
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
        sf::Text unsortedT(font, std::to_string(e), 20);
        unsortedT.setPosition(sf::Vector2f(xPos, yPos));
        yPos = yPos + gap;
        window.draw(unsortedT);
    }
}

void addRandomNumToList(std::vector<int>& unsortedList, int maximumNum, int highestNum)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(1, highestNum);

    for (int i = 0; i < maximumNum; ++i)
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
    bool startingScreen = true;
    bool sortScreen = false;

    bool uMaximum = true;
    bool uHighest = false;
    int maximumNum = 20; // Maximale Zahlen die Sortiert werden
    int highestNum = 50; // Höchste random Nummer

    sf::RenderWindow window(sf::VideoMode({ 1000, 900 }), "Selection Sort 2");

    std::vector<int> unsortedList;
    int selectedNumber = 0;

    const sf::Font font("assets/fonts/ariblk.ttf");

    //Starting Screen 
    sf::Text sctT(font, "SORTING SYSTEM", 40);
    sctT.setPosition(sf::Vector2f(300, 10));

    sf::Text uMaximumT(font, "Maximale Sortier Zahlen: 20", 20);
    uMaximumT.setPosition(sf::Vector2f(350, 100));

    sf::Text uHighestT(font, "Hoechste Sortier Zahl: 50", 20);
    uHighestT.setPosition(sf::Vector2f(350, 200));

    sf::Text startScreenInfoT(font, "Mit den Pfeiltasten hoch und runter wird die zahl kleiner oder groesser.\n Mit der Enter Taste kannst du einen Schritt weiter gehen und dann auch Starten.", 12);
    startScreenInfoT.setPosition(sf::Vector2f(245, 260));
    startScreenInfoT.setFillColor(sf::Color::Red);

    //Sorting Screen 
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
                //Enter
                if (static_cast<int>(keyReleased->code) == 58)
                {
                    if (startingScreen)
                    {
                        if (uMaximum)
                        {
                            uMaximum = false;
                            uHighest = true;
                        }
                        else if (!uMaximum && uHighest)
                        {
                            startingScreen = false;
                            sortScreen = true;
                            uHighest = false;
                            addRandomNumToList(unsortedList, maximumNum, highestNum);
                        }
                    }
                    else if (sortScreen)
                    {
                        SelectionSort(window, unsortedList, selectedNumber);
                    }
                }

                //Arrow Key up 
                if (static_cast<int>(keyReleased->code) == 73)
                {
                    if (uMaximum && maximumNum < 26)
                    {
                        maximumNum++;
                        uMaximumT.setString("Maximale Sortier Zahlen: " + std::to_string(maximumNum));
                    }
                    else if (!uMaximum && uHighest && highestNum < 100)
                    {
                        highestNum++;
                        uHighestT.setString("Hoechste Sortier Zahl: " + std::to_string(highestNum));
                    }
                }

                //Arrow Key down
                if (static_cast<int>(keyReleased->code) == 74)
                {
                    if (uMaximum && maximumNum > 1)
                    {
                        maximumNum--;
                        uMaximumT.setString("Maximale Sortier Zahlen: " + std::to_string(maximumNum));
                    }
                    else if (!uMaximum && uHighest && highestNum > 2)
                    {
                        highestNum--;
                        uHighestT.setString("Hoechste Sortier Zahl: " + std::to_string(highestNum));
                    }
                }
            }
        }

        finishedT.setString("Abgeschlossen: " + std::to_string(selectedNumber + 1) + "/" + std::to_string(unsortedList.size()));

        window.clear();

        if (startingScreen)
        {
            window.draw(sctT);
            window.draw(uHighestT);
            window.draw(uMaximumT);
            window.draw(startScreenInfoT);
        }

        if (sortScreen)
        {
            window.draw(unsortedT);
            window.draw(infoSprite);
            window.draw(infoText);
            window.draw(finishedT);

            renderList(window, font, unsortedList, 32.0f, 870.0f);
            drawListBar(window, font, unsortedList, 30.0f);
        }

        window.display();
    }
}
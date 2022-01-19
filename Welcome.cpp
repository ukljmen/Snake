
#include <cstring>
#include <iostream>
#include <fstream>
#include "sstream"
#include "Welcome.h"


Welcome::Welcome(SnakeBoard &o) : wbrd(o) {

    tile.setPointCount(4);
    tile.setPoint(0, sf::Vector2f(0.f, 0.f));
    tile.setPoint(1, sf::Vector2f(150.f, 0.f));
    tile.setPoint(2, sf::Vector2f(150.f, 100.f));
    tile.setPoint(3, sf::Vector2f(0.f, 100.f));
    tile.setFillColor(sf::Color::Magenta);

    if (!fontey.loadFromFile("arial.ttf")) {
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    title.setFont(fontey);
    title.setString("Snake");
    choose.setFont(fontey);
    choose.setString("Choose difficulty level: ");
    d1.setFont(fontey);
    d1.setString("EASY");
    d2.setFont(fontey);
    d2.setString("MEDIUM");
    d3.setFont(fontey);
    d3.setString("HARD");

    finalScore.setFont(fontey);
}

void Welcome::display_setup(sf::RenderWindow &win) {
    win.draw(tile);
    tile.setPosition(100, 250);
    win.draw(tile);
    tile.setPosition(300, 250);
    win.draw(tile);
    tile.setPosition(500, 250);

    win.draw(title);
    title.setPosition(325, 50);
    win.draw(choose);
    choose.setPosition(200, 200);
    win.draw(d1);
    d1.setPosition(140, 270);
    win.draw(d2);
    d2.setPosition(315, 270);
    win.draw(d3);
    d3.setPosition(530, 270);
}

void Welcome::display_gameover(sf::RenderWindow &win) {
    win.clear(sf::Color(80, 0, 80));
    std::vector<int> scores;
    int c;
    std::fstream file;
    file.open("scores.txt", std::ios::in);
    while (!file.eof()) {
        file >> c;
        scores.push_back(c);
    }

    for (int i = 0; i < scores.size(); ++i) {
        for (int j = 1; j < scores.size(); ++j) {
            if (scores.at(j - 1) < scores.at(j)) {
                c = scores[j];
                scores[j] = scores[j - 1];
                scores[j - 1] = c;
            }
        }
    }
    std::stringstream ss1, ss2;
    ss1 << wbrd.getScore();
    std::string s1 = ss1.str(), s2;
    finalScore.setString("Your score: " + s1);
    win.draw(finalScore);
    finalScore.setPosition(300, 15);
    choose.setString("Highscores: ");
    win.draw(choose);
    choose.setPosition(60, 40);

    ss1.str("");
    ss2.str("");
    ss1 << scores.at(0);
    s1 = ss1.str();
    ss2 << 1;
    s2 = ss2.str();
    title.setString(s2 + ".  " + s1);
    win.draw(title);
    title.setPosition(60, 95);
    for (int i = 0; i < 10; ++i) {
        if (i == scores.size() - 1) { break; }
        ss1.str("");
        ss2.str("");
        ss1 << scores.at(i);
        s1 = ss1.str();
        ss2 << i + 1;
        s2 = ss2.str();
        title.setString(s2 + ".  " + s1);
        win.draw(title);

        if (i == 8) {
            title.setPosition(43, 120 + 25 * i);
            continue;
        }
        if (i == 9 || (i == scores.size() - 2 && scores.size() - 2 < 9)) {
            title.setPosition(60, 95);
            break;
        }

        title.setPosition(60, 120 + 25 * i);
    }

    file.close();
}




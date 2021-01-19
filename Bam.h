#ifndef BAM_H
#define BAM_H

#include <SFML/Graphics.hpp>
#include <random>
#include <sstream>
#include <chrono>

class Bam {
public:
    sf::RectangleShape m_square;
    sf::Text         m_hudScore;
    int                 m_score;
public:    
    Bam();
    void          cursorSpeed();
    void          resetSquare();
    sf::Text            score();
    sf::Text           coords();
private:
    std::random_device               m_rd;
    std::mt19937                    m_gen;
    std::uniform_int_distribution<> m_cod;    
    sf::Font                       m_font;
};

#endif
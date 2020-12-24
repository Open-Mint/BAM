#include "Bam.h"

Bam::Bam()
: m_gen(m_rd()), m_cod(40, 560)
{
    m_square.setSize(sf::Vector2f(20, 20));
    m_square.setFillColor(sf::Color::Red);
    m_square.setPosition(m_cod(m_gen), m_cod(m_gen));

    m_font.loadFromFile("DS-DIGI.TTF");    

    m_hudScore.setFont(m_font);
    m_hudScore.setFillColor(sf::Color::White);

    m_score = 0;
}

void Bam::resetSquare(){
    m_square.setPosition(m_cod(m_gen), m_cod(m_gen));
    ++m_score;
}

void Bam::cursorSpeed(){
    
}

sf::Text Bam::score(){

    std::stringstream ss;
 
    ss << "Score: " << m_score;
    m_hudScore.setString(ss.str());
 
    return m_hudScore;    
}
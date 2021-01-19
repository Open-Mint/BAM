#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <SFML/Window/Window.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Bam.h"

#define WWIDTH  800
#define WHEIGHT 600

class MainWindow
{
    public:
        MainWindow();
        ~MainWindow();
        int run();
    private:        
        void            update(float dt);
        void              handleEvents();
        void                    render();
        void                     reset();
        void                   restart();
        void                      quit();
        void          updateHoverColor(sf::RectangleShape &button, 
                                       sf::Text &text, sf::Color &buttonNormalColor, 
                                       sf::Color &buttonHoverColor, 
                                       sf::Color &normalTextColor, 
                                       sf::Color &hoverTextColor);
    private:
        Bam player;
    private:
        sf::RectangleShape m_restartButton;
        sf::RectangleShape    m_quitButton;
        
        sf::RenderWindow      m_MainWindow;
        
        sf::Font                    m_font;
        
        sf::Text                   m_timer;
        sf::Text             m_restartText;
        sf::Text                m_quitText;
        sf::Text              m_theEndText;

        sf::Image                  m_image;  
        
        sf::Color            R_normalColor;
        sf::Color             R_hoverColor;
        sf::Color            Q_normalColor;
        sf::Color             Q_hoverColor;
        sf::Color        m_normalTextColor;
        sf::Color         m_hoverTextColor;

        float             m_finalCountdown;

        bool                    m_winState;
        bool                 m_buttonState;
};

#endif // MAINWINDOW_H
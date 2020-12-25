#include "MainWindow.h"
#include <SFML/Graphics.hpp>

MainWindow::MainWindow()
  : m_MainWindow( sf::VideoMode(WWIDTH, WHEIGHT), "Bam!!", sf::Style::Close | sf::Style::Titlebar),
    Q_normalColor(202, 11, 0),      Q_hoverColor(162, 9, 0),
    R_normalColor(175, 234, 220),   R_hoverColor(140, 188, 176),
    m_normalTextColor(4, 30, 66),     m_hoverTextColor(3, 24, 53)
{

    /*SETTING THE MAXIMUM TIMER LIMIT*/

    m_finalCountdown = 10.f;

    /* ICON SETTING */
    
    unsigned int imageWidth;
    unsigned int imageHeight;

    imageWidth  =  60;
    imageHeight =  50;

    sf::Image image;
    image.loadFromFile("BamIcon.png");
    m_MainWindow.setIcon(imageWidth, imageHeight, image.getPixelsPtr());
    
    /* SET WINDOW STATE TO TRUE */

    m_winState  =  1;

    /* LOADING FONT FOR EVERYTHING */

    m_font.loadFromFile("DS-DIGI.TTF");
    
    /* SETTING OF A TIMER TEXT */

    m_timer.setFont(m_font);
    m_timer.setCharacterSize(25);
    m_timer.setFillColor(sf::Color::White);    
    m_timer.setPosition(770, 0);    
    
    /* RESTART BUTTON SETTING */

    m_restartButton.setSize(sf::Vector2f(180, 100));
    m_restartButton.setPosition(WHEIGHT / 2, (WWIDTH / 2) - 110);
    
    m_restartText.setCharacterSize(50);
    m_restartText.setFont(m_font);
    m_restartText.setPosition((WHEIGHT / 2) + 5, ((WWIDTH / 2) - 110) + 15);

    /* QUIT BUTTON SETTING */

    m_quitButton.setSize(sf::Vector2f(180, 100));
    m_quitButton.setPosition(WHEIGHT / 2, WWIDTH / 2);
    
    m_quitText.setCharacterSize(50);
    m_quitText.setFont(m_font);
    m_quitText.setPosition((WHEIGHT / 2) + 45, ((WWIDTH / 2) + 15));

    /* THE ENDING TEXT */
    
    m_theEndText.setCharacterSize(75);
    m_theEndText.setFont(m_font);
    m_theEndText.setPosition((WHEIGHT / 2) - 200, ((WWIDTH / 2) - 345));
}

MainWindow::~MainWindow()
{
    
}

int MainWindow::run()
{
    const sf::Time FrameRate = sf::seconds( 1.f/60.f );
    const float frameRate = FrameRate.asSeconds();
    sf::Time frameTime;

    sf::Clock frameClock;
    while( m_MainWindow.isOpen() )
    {
        
        for( ; frameTime > FrameRate; frameTime -= FrameRate)
        {
            handleEvents();
            update( frameRate );
        }
               
        render();
        frameTime += frameClock.restart();
    }

    return 0;
}

void MainWindow::handleEvents()
{
    sf::Event evnt;
    while( m_MainWindow.pollEvent( evnt ) )
    {
        /*
            =---------------------=
            Main window events here
            =---------------------=
        */
        switch( evnt.type )
        {
            case sf::Event::Closed:
            {
                m_MainWindow.close();
                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                if(evnt.mouseButton.button == sf::Mouse::Left && m_winState){ // What happens if someone presses the object?
                    reset();
                    break;
                }
                else
                    if(evnt.mouseButton.button == sf::Mouse::Left && !m_winState && !m_buttonState){ // What happens if someone presses restart button?
                        restart();
                        break;
                    }
                    else
                        if(evnt.mouseButton.button == sf::Mouse::Left && !m_winState && m_buttonState){ // What happens if someone presses quit button?
                            quit();
                            break;
                        }
            }    
        }
    }
}

void MainWindow::update(float dt)
{
    /*
        =----------------------=
        Main window updates here
        =----------------------=
    */

    std::stringstream countdown;
    std::stringstream restartButtonText;
    std::stringstream quitButtonText;
    std::stringstream areYouSureText;
    std::stringstream theEndText;

    if(m_finalCountdown >= 1.f){
        
        /* DANGER COLOR */
        
        if(m_finalCountdown < 6.f && ((int)m_finalCountdown % 2) == 1)
            m_timer.setFillColor(sf::Color(202, 11, 0));
        else
            m_timer.setFillColor(sf::Color::White);
        
        /* CLOCK STARTS TICKING */

        m_finalCountdown -= dt;

        /* SCORE SETTINGS */

        player.m_hudScore.setCharacterSize(25);    
        player.m_hudScore.setPosition(0,0);     
    }
    else 
    {
        m_winState = 0;
        
        /* CHECKING FOR BUTTON STATES */

        if(m_quitButton.getGlobalBounds().contains(sf::Mouse::getPosition(m_MainWindow).x, sf::Mouse::getPosition(m_MainWindow).y))
            m_buttonState = 1;
        else
            m_buttonState = 0;
        
        /* SCORE RE-SETTINGS FOR ENDING WINDOW */

        player.m_hudScore.setCharacterSize(45);
        player.m_hudScore.setPosition((WHEIGHT / 2) + 5, (WWIDTH / 2) - 200);        
    }
    
    /* UPDATE HOVER COLOR FOR BUTTON AND TEXT */

    updateHoverColor(m_restartButton, m_restartText, R_normalColor, R_hoverColor, m_normalTextColor, m_hoverTextColor); 
    updateHoverColor(m_quitButton, m_quitText, Q_normalColor, Q_hoverColor, m_normalTextColor, m_hoverTextColor);    

    countdown << (int)m_finalCountdown; 
    restartButtonText << "Restart";
    quitButtonText << "Quit";
    theEndText << "Thanks for playing!";

    m_theEndText.setString(theEndText.str());
    m_timer.setString(countdown.str());
    m_restartText.setString(restartButtonText.str());
    m_quitText.setString(quitButtonText.str());    
}

void MainWindow::render()
{
    m_MainWindow.clear(sf::Color(4, 30, 66));

    /*
        =----------------------=
        Main window renders here
        =----------------------=
    */
    
    if(m_winState == 0){
        m_MainWindow.draw(player.score());
        m_MainWindow.draw(m_restartButton);
        m_MainWindow.draw(m_restartText);
        m_MainWindow.draw(m_quitButton);
        m_MainWindow.draw(m_quitText);
        m_MainWindow.draw(m_theEndText);
    }
    else
    {
        m_MainWindow.draw(player.m_square);
        m_MainWindow.draw(player.score());
        m_MainWindow.draw(m_timer);
    }
    m_MainWindow.display();
}

void MainWindow::reset(){
    if(player.m_square.getGlobalBounds().contains(sf::Mouse::getPosition(m_MainWindow).x, sf::Mouse::getPosition(m_MainWindow).y))
    {
        player.resetSquare(); // Call the function for moving the object to random position
    
        m_finalCountdown ++; // Increment time by one
    }
}

void MainWindow::restart(){
    if(m_restartButton.getGlobalBounds().contains(sf::Mouse::getPosition(m_MainWindow).x, sf::Mouse::getPosition(m_MainWindow).y))
    {
       m_winState = 1; // Reset the windows' state to 1 (working state)
       
       m_finalCountdown = 10; // Reset countdown back to maximum value
       
       player.m_score = 0; // Reset the player's score
    }
}

/* QUIT IF PLAYER INTERSECTS QUIT BUTTON */

void MainWindow::quit()
{
    if(m_quitButton.getGlobalBounds().contains(sf::Mouse::getPosition(m_MainWindow).x, sf::Mouse::getPosition(m_MainWindow).y))
       m_MainWindow.close();
}

/* UPDATE HOVER COLOR FOR BUTTONS AND TEXT */

void MainWindow::updateHoverColor(sf::RectangleShape &button, sf::Text &text, sf::Color &buttonNormalColor, sf::Color &buttonHoverColor, sf::Color &normalTextColor, sf::Color &hoverTextColor)
{
    if(button.getGlobalBounds().contains(sf::Mouse::getPosition(m_MainWindow).x, sf::Mouse::getPosition(m_MainWindow).y))
    {
        button.setFillColor(buttonHoverColor);
        text.setFillColor(normalTextColor);
    }
    else
    {
        button.setFillColor(buttonNormalColor);
        text.setFillColor(hoverTextColor);
    }
}
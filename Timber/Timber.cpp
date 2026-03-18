#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cmath>


using namespace sf;
using namespace std;

void updateBranches(int seed);
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];
enum class side
{
    LEFT,
    RIGHT,
    NONE
};

side branchPositions[NUM_BRANCHES];


int main()
{
    srand(time(0));
    int h;

    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "TIMBER");
    View view(FloatRect(0, 0, 1920, 1080));
    window.setView(view);

    bool paused = true;

    Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");
    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);

    Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810, 0);

    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 800);

    bool beeActive = false;
    float beeSpeed = 0.0f;

    Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");

    Sprite spriteCloud1;
    spriteCloud1.setTexture(textureCloud);
    spriteCloud1.setScale(0.5f, 0.5f);
    bool cloud1Active = false;
    float cloud1Speed = 0.0f;

    Sprite spriteCloud2;
    spriteCloud2.setTexture(textureCloud);
    spriteCloud2.setScale(0.4f, 0.4f);
    bool cloud2Active = false;
    float cloud2Speed = 0.0f;

    Sprite spriteCloud3;
    spriteCloud3.setTexture(textureCloud);
    spriteCloud3.setScale(0.3f, 0.3f);
    bool cloud3Active = false;
    float cloud3Speed = 0.0f;

    Texture texturePlayer;
    texturePlayer.loadFromFile("graphics/player.png");
    Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setPosition(580, 720);

    bool acceptInput = false;


    side playerSide = side::LEFT;

    Texture textureRIP;
    textureRIP.loadFromFile("graphics/rip.png");
    Sprite spriteRIP;
    spriteRIP.setTexture(textureRIP);
    spriteRIP.setPosition(600, 860);

    Texture textureAxe;
    textureAxe.loadFromFile("graphics/axe.png");
    Sprite spriteAxe;
    spriteAxe.setTexture(textureAxe);
    spriteAxe.setPosition(700, 830);

    const float AXE_POSITION_LEFT = 700;
    const float AXE_POSITION_RIGHT = 1075;

    Texture textureLog;
    textureLog.loadFromFile("graphics/log.png");
    Sprite spriteLog;
    spriteLog.setTexture(textureLog);
    spriteLog.setPosition(810, 720);

    bool logActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;

    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    int score = 0;
    Text messageText;
    Text scoreText;
    Font font;
    font.loadFromFile("font/KOMIKAP_.ttf");

    messageText.setFont(font);
    scoreText.setFont(font);

    messageText.setString("Press ENTER to start");
    scoreText.setString("Score = 0");

    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(75);

    messageText.setFillColor(Color::Green);
    scoreText.setFillColor(Color::Red);

    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(
        (textRect.left + textRect.width) / 2.0f,
        (textRect.top + textRect.height) / 2.0f
    );

    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
    scoreText.setPosition(20, 20);

    Texture textureBranch;
    textureBranch.loadFromFile("graphics/branch.png");
    for(int i=0; i < NUM_BRANCHES; i++){
        branches[i].setTexture(textureBranch);
        branches[i].setPosition(-2000, -2000);
        branches[i].setOrigin(220, 40);
    }

    Clock clock;
    Time dt;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
                window.close();

            if(event.type == Event::KeyReleased && !paused)
                acceptInput = true;
            
            spriteAxe.setPosition(2000, spriteAxe.getPosition().y);

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Return)
            {
                paused = false;
                score = 0;
                timeRemaining = 6.0f;

                acceptInput = true;

                for(int i=1; i<NUM_BRANCHES; i++){
                    branchPositions[i] = side::NONE;
                }

                spriteRIP.setPosition(675,2000);
                spritePlayer.setPosition(580,720);

                scoreText.setString("Score = 0");
            }

            if (acceptInput)
            {
                if (Keyboard::isKeyPressed(Keyboard::Right))
                {

                    playerSide = side::RIGHT;
                    score++;
                    

                    timeRemaining += (2.0f / score) + 0.15f;
                    if (timeRemaining >= 6.0f)
                        timeRemaining = 6.0f;

                    spritePlayer.setPosition(1200, 720);
                    spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);

                    spriteLog.setPosition(810, 720);
                    logSpeedX = -5000;
                    logActive = true;

                    updateBranches(score);


                    acceptInput = false;

                }

                if (Keyboard::isKeyPressed(Keyboard::Left))
                {
                    score++;


                    playerSide = side::LEFT;
                    

                    timeRemaining += (2.0f / score) + 0.15f;
                    if (timeRemaining >= 6.0f)
                        timeRemaining = 6.0f;

                    spritePlayer.setPosition(580, 720);
                    spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);
                    spriteLog.setPosition(810, 720);
                    logSpeedX = 5000;
                    logActive = true;

                    updateBranches(score);


                    acceptInput = false;
                }
            }
        }

        dt = clock.restart();

        if (!paused)
        {
            timeRemaining -= dt.asSeconds();
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

            if (timeRemaining <= 0.0f)
            {
                paused = true;
            }
            
            

            if (!beeActive)
            {
                beeSpeed = (rand() % 200) + 200;
                float height = (rand() % 500) + 500;
                spriteBee.setPosition(2000, height);
                beeActive = true;
                h = 100;
            }
            else
            {
                spriteBee.setPosition(
                    spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()),
                    spriteBee.getPosition().y + sin(int(h++/100)));

                if (spriteBee.getPosition().x < -100)
                    beeActive = false;
            }

            if (!cloud1Active)
            {
                cloud1Speed = (rand() % 50) + 50;
                float height = rand() % 200;
                spriteCloud1.setPosition(-200, height);
                cloud1Active = true;
            }
            else
            {
                spriteCloud1.setPosition(
                    spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()),
                    spriteCloud1.getPosition().y);

                if (spriteCloud1.getPosition().x > 1920)
                    cloud1Active = false;
            }

            if (!cloud2Active)
            {
                cloud2Speed = (rand() % 50) + 50;
                float height = rand() % 300;
                spriteCloud2.setPosition(-200, height);
                cloud2Active = true;
            }
            else
            {
                spriteCloud2.setPosition(
                    spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()),
                    spriteCloud2.getPosition().y);

                if (spriteCloud2.getPosition().x > 1920)
                    cloud2Active = false;
            }

            if (!cloud3Active)
            {
                cloud3Speed = (rand() % 50) + 50;
                float height = rand() % 400;
                spriteCloud3.setPosition(-200, height);
                cloud3Active = true;
            }
            else
            {
                spriteCloud3.setPosition(
                    spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()),
                    spriteCloud3.getPosition().y);

                if (spriteCloud3.getPosition().x > 1920)
                    cloud3Active = false;

                std::stringstream ss;
                ss << "score =" << score;
                scoreText.setString(ss.str());


                if(logActive){
                    spriteLog.setPosition(spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()), spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));
                }

                if(spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > 2000){
                    logActive = false;
                    spriteLog.setPosition(810, 720);
                }


                for(int i=0; i< NUM_BRANCHES; i++){
                    float height = i*150;

                    if(branchPositions[i] == side::LEFT){
                        branches[i].setPosition(610,height);
                        branches[i].setRotation(180);
                    }
                    else if(branchPositions[i]==side::RIGHT){
                        branches[i].setPosition(1330, height);
                        branches[i].setRotation(0);
                    }
                    else{
                        branches[i].setPosition(3000, height);
                    }
                }


                    
            }
        }

        window.clear();
        window.draw(spriteBackground);
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        window.draw(spriteTree);
        for(int i=0; i<NUM_BRANCHES; i++){
            window.draw(branches[i]);
        }
        window.draw(spritePlayer);
        window.draw(spriteRIP);
        window.draw(spriteAxe);
        window.draw(spriteLog);
        window.draw(spriteBee);
        window.draw(timeBar);

        if (paused)
            window.draw(messageText);

        window.draw(scoreText);
        window.display();
    }

    return 0;
}


void updateBranches(int seed){
    for(int j  = NUM_BRANCHES-1; j>0; j--){
        branchPositions[j] = branchPositions[j-1];
    }
    srand((int)time(0) +seed);
    int r = (rand() % 5);

    switch(r){
        case 0:
            branchPositions[0] = side::LEFT;
            break;
        case 1:
            branchPositions[0] = side::RIGHT;
            break;
        default:
            branchPositions[0] = side::NONE;
    }
}
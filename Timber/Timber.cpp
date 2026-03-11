#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace sf;

int main()
{
    srand(time(0));

    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "TIMBER");
    View view(FloatRect(0, 0, 1920, 1080));
    window.setView(view);

    bool paused = true;

    // ================= BACKGROUND =================
    Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");
    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);

    // ================= TREE =================
    Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810, 0);

    // ================= BEE =================
    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 800);

    bool beeActive = false;
    float beeSpeed = 0.0f;

    // ================= CLOUD TEXTURE =================
    Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");

    // Cloud 1
    Sprite spriteCloud1;
    spriteCloud1.setTexture(textureCloud);
    spriteCloud1.setScale(0.5f, 0.5f);
    bool cloud1Active = false;
    float cloud1Speed = 0.0f;

    // Cloud 2
    Sprite spriteCloud2;
    spriteCloud2.setTexture(textureCloud);
    spriteCloud2.setScale(0.4f, 0.4f);
    bool cloud2Active = false;
    float cloud2Speed = 0.0f;

    // Cloud 3
    Sprite spriteCloud3;
    spriteCloud3.setTexture(textureCloud);
    spriteCloud3.setScale(0.3f, 0.3f);
    bool cloud3Active = false;
    float cloud3Speed = 0.0f;

    // ================= PLAYER =================
    Texture texturePlayer;
    texturePlayer.loadFromFile("graphics/player.png");
    Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setPosition(580, 720);

    bool acceptInput = false;

    // ================= RIP =================
    Texture textureRIP;
    textureRIP.loadFromFile("graphics/rip.png");
    Sprite spriteRIP;
    spriteRIP.setTexture(textureRIP);
    spriteRIP.setPosition(600, 860);

    // ================= AXE =================
    Texture textureAxe;
    textureAxe.loadFromFile("graphics/axe.png");
    Sprite spriteAxe;
    spriteAxe.setTexture(textureAxe);
    spriteAxe.setPosition(700, 830);

    const float AXE_POSITION_LEFT = 700;
    const float AXE_POSITION_RIGHT = 1075;

    // ================= LOG =================
    Texture textureLog;
    textureLog.loadFromFile("graphics/log.png");
    Sprite spriteLog;
    spriteLog.setTexture(textureLog);
    spriteLog.setPosition(810, 720);

    // ================= TIME BAR =================
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

    Clock clock;
    Time dt;

    // ================= GAME LOOP =================
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {

            if (event.type == Event::Closed)
                window.close();

            if(event.type == Event::KeyReleased)
                acceptInput = true;
            
            spriteAxe.setPosition(2000, spriteAxe.getPosition().y);

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Return)
            {
                paused = false;
                score = 0;
                timeRemaining = 6.0f;

                acceptInput = true;

                scoreText.setString("Score = 0");
            }

            if (acceptInput)
            {
                if (Keyboard::isKeyPressed(Keyboard::Right))
                {
                    score++;
                    acceptInput = false;

                    timeRemaining += (2.0f / score) + 0.15f;
                    if (timeRemaining >= 6.0f)
                        timeRemaining = 6.0f;

                    spritePlayer.setPosition(1200, 720);
                    spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);


                }

                if (Keyboard::isKeyPressed(Keyboard::Left))
                {
                    score++;
                    acceptInput = false;

                    timeRemaining += (2.0f / score) + 0.15f;
                    if (timeRemaining >= 6.0f)
                        timeRemaining = 6.0f;

                    spritePlayer.setPosition(580, 720);
                    spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);


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
            
            std::stringstream ss;
            ss << "score =" << score;
            scoreText.setString(ss.str());

            // ================= BEE =================
            if (!beeActive)
            {
                beeSpeed = (rand() % 200) + 200;
                float height = (rand() % 500) + 500;
                spriteBee.setPosition(2000, height);
                beeActive = true;
            }
            else
            {
                spriteBee.setPosition(
                    spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()),
                    spriteBee.getPosition().y);

                if (spriteBee.getPosition().x < -100)
                    beeActive = false;
            }

            // ================= CLOUD 1 =================
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

            // ================= CLOUD 2 =================
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

            // ================= CLOUD 3 =================
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
            }
        }

        // ================= DRAW =================
        window.clear();
        window.draw(spriteBackground);
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        window.draw(spriteTree);
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
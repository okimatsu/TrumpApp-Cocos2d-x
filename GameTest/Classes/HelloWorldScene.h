#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"


enum CardType
{
    Clubs = 0,
    Diamonds,
    Hearts,
    Spades
};

struct Card
{
    int number;
    CardType type;
};

struct PosIndex
{
    int x;
    int y;
};

class CardSprite : public cocos2d::Sprite
{
protected:
    std::string getFileName(CardType cardType);
    void showNumber();
    
public:
    virtual bool init();
    void onEnter() override;
    
    CREATE_FUNC(CardSprite);
    
    CC_SYNTHESIZE(Card, _card, Card);
    CC_SYNTHESIZE(PosIndex, _posIndex, PosIndex)
    
};

class HelloWorld : public cocos2d::Scene
{
protected:
    std::vector<Card> _cards;
    
    void initCards();
    Card getCard();
    void createCard(PosIndex);
    void showInitCards();
    void initGame();
    
    
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(HelloWorld);
};

#endif

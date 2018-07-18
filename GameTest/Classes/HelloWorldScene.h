#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

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
    void onEnter();
    
    CREATE_FUNC(CardSprite);
    
    CC_SYNTHESIZE(Card, _card, Card);
    CC_SYNTHESIZE(PosIndex, _posIndex, PosIndex)
    
    void moveBackToInitPos();
    void moveToTrash();
    void moveToInitPos();
};

class HelloWorld : public cocos2d::Scene
{
protected:
    std::vector<Card> _cards;
    CardSprite* _firstCard;
    float _timer;
    
    
    void initCards();
    Card getCard();
    void createCard(PosIndex);
    void showInitCards();
    void initGame();
    CardSprite* getTouchCard(cocos2d::Touch *touch);
    void showButton();
    void initTrash();
    void onTapButton(cocos2d::Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void showBackCards();
    void showTimerLabel();
    
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(HelloWorld);
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    void update(float dt) override;
};

#endif

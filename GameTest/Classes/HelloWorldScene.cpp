#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <random>

#define CARD_NUM 13
#define CARD_TYPE_NUM 4

#define CARD_1_POS_X 50
#define CARD_1_POS_Y 100 //7plusJust
#define CARD_DISTANCE_X 95 //7plusJust
#define CARD_DISTANCE_Y 120

#define ZORDER_SHOW_CARD 1

#define ZORDER_MOVING_CARD 2

USING_NS_CC;

std::string CardSprite::getFileName(CardType cardType)
{
    std::string filename;
    switch (cardType) {
        case Clubs: filename = "CB.png"; break;
        case Diamonds: filename = "DA.png"; break;
        case Hearts: filename = "HT.png"; break;
        default: filename = "SP.png"; break;
    }
    return filename;
}

void CardSprite::showNumber()
{
    std::string numberString;
    switch (_card.number) {
        case 1: numberString = "A"; break;
        case 11: numberString = "J"; break;
        case 12:numberString = "Q"; break;
        case 13: numberString = "K"; break;
        default: numberString = StringUtils::format("%d", _card.number); break;
    }
 
    auto number = Label::createWithSystemFont(numberString, "Arial", 96);
    number->setPosition(Point(getContentSize() / 2));
    number->setTextColor(Color4B::WHITE);
    number->setSystemFontSize(40);
    addChild(number);
}

bool CardSprite::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    return true;
}

void CardSprite::onEnter()
{
    Sprite::onEnter();
    
    setTexture(getFileName(_card.type));
    showNumber();
    
    float posX = CARD_1_POS_X + CARD_DISTANCE_X * _posIndex.x;
    float posY = CARD_1_POS_Y + CARD_DISTANCE_X * _posIndex.y;
    setPosition(posX, posY);
    setTag(_posIndex.x + _posIndex.y * 5 + 1);
}

CardSprite* HelloWorld::getTouchCard(Touch *touch)
{
    for (int tag = 1; tag <= 10; tag++)
    {
        auto card = (CardSprite*)getChildByTag(tag);
        if (card && card->getBoundingBox().containsPoint(touch->getLocation()))
        {
            return card;
        }
    }
    return nullptr;
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
    _firstCard = getTouchCard(touch);
    if (_firstCard)
    {
        _firstCard->setLocalZOrder(ZORDER_MOVING_CARD);
        return true;
    }
    return false;
}

void HelloWorld::onTouchMoved(Touch *touch, Event *unused_event)
{
    _firstCard->setPosition(_firstCard->getPosition() + touch->getDelta());
}

void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event)
{
    _firstCard = nullptr;
}

void HelloWorld::onTouchCancelled(Touch *touch, Event *unused_event)
{
    onTouchEnded(touch, unused_event);
}

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto Layer = HelloWorld::create();
    scene->addChild(Layer);
    
    return scene;
    
    return HelloWorld::create();
}

bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    Size winSize = Director::getInstance()->getVisibleSize();
    //縦のサイズがなぜか合わないので+100
    auto backGround = LayerColor::create(Color4B::WHITE, winSize.width + 100, winSize.height + 100);
    this->addChild(backGround);
    
    initGame();
    
    return true;
}

void HelloWorld::createCard(PosIndex posIndex)
{
    
    auto card = CardSprite::create();
    card->setCard(getCard());
    card->setPosIndex(posIndex);
    addChild(card, ZORDER_SHOW_CARD);
}



void HelloWorld::showInitCards()
{
    for (int tag = 1; tag <=10; tag++)
    {
        auto card = getChildByTag(tag);
        if (card)
        {
            card->removeFromParent();
        }
    }
    
    for (int x = 0; x < 5; x++)
    {
        for (int y = 0; y < 2; y++)
        {
            PosIndex posIndex;
            posIndex.x = x;
            posIndex.y = y;
            
            createCard(posIndex);
        }
    }
}

void HelloWorld::initGame()
{
    initCards();
    
    showInitCards();
}

void HelloWorld::initCards() //？
{
    _cards.clear();
    
    for (int type = 0; type < CARD_TYPE_NUM; type++)
    {
        for (int number = 1; number <= CARD_NUM; number++)
        {
            Card card;
            card.number = number;
            card.type = (CardType)type;
            
            _cards.push_back(card);
        }
    }
}

Card HelloWorld::getCard()
{
    std::random_device rd;
    std::mt19937 rand = std::mt19937(rd());
    
    int index = std::uniform_int_distribution<int>(0, (int)_cards.size() - 1)(rand);
    
    auto card = _cards[index];
    
    _cards.erase(_cards.begin() + index);
    
    return card;
}

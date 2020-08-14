/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include <time.h>
#include "WheelScene.h"

///
#include <iostream>

Scene* Wheel::createScene()
{
    auto scene = Scene::createWithPhysics();
    auto layer = Wheel::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);

    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Wheel::init()
{
    if ( !Scene::init() )
        return false;

    srand(time(NULL));
    int numitems = 8;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 wheelposition = Vec2(visibleSize.width / 2.f + origin.x , visibleSize.height / 2.f + origin.y +50.f);
    std::string itemspath[5] = { "Assets/heart.png", "Assets/brush.png" , "Assets/gem.png",
                                "Assets/hammer.png", "Assets/coin.png" };
    std::string itemnumbers[8] = {"30\nmin", "X3", "X35", "X3", "X750", "X1", "X75", "X1"};

    //wheel
    wheelsprite = Sprite::create("Assets/wheel_sections_8.png");
    if (wheelsprite == nullptr)
    {
        problemLoading("'Assets/wheel_sections_8.png'");
    }
    else
    {
        // position the sprite on the center of the screen

        wheelsprite->setScale(0.5);
        wheelsprite->setAnchorPoint(Vec2(0.5f, 0.5f));
        wheelsprite->setPosition(wheelposition);
        
        PhysicsBody* wheelphysics = PhysicsBody::createBox(wheelsprite->getContentSize(), PhysicsMaterial(0, 1, 0));
        wheelphysics->setGravityEnable(false);
        wheelsprite->setPhysicsBody(wheelphysics);
        wheelsprite->setTag(1);
        // add the sprite as a child to this layer
        this->addChild(wheelsprite, 0);
    }


    //wheelborder
    auto bordersprite = Sprite::create("Assets/wheel_border.png");
    if (bordersprite == nullptr)
    {
        problemLoading("'Assets/wheel_sections_8.png'");
    }
    else
    {

        bordersprite->setAnchorPoint(Vec2(0.5f, 0.5f));
        bordersprite->setScale(0.5f);
        // position the sprite on the center of the screen
        bordersprite->setPosition(wheelposition);
        bordersprite->setTag(1);
        

        // add the sprite as a child to this layer
        this->addChild(bordersprite, 1);
        
    }

    items.resize(8);
    //items
    items[0].ItemSet(Sprite::create("Assets/heart.png") ,"heart30", 0.2f , 0, Label::createWithTTF("30\nmin", "fonts/Marker Felt.ttf", 50.f));
    items[1].ItemSet(Sprite::create("Assets/brush.png") ,"brush3" , 0.1f , 1, Label::createWithTTF("X3"     , "fonts/Marker Felt.ttf", 50.f));
    items[2].ItemSet(Sprite::create("Assets/gem.png")   ,"gem35"  , 0.1f , 2, Label::createWithTTF("X35"    , "fonts/Marker Felt.ttf", 50.f));
    items[3].ItemSet(Sprite::create("Assets/hammer.png"),"hammer3", 0.1f , 3, Label::createWithTTF("X3"     , "fonts/Marker Felt.ttf", 50.f));
    items[4].ItemSet(Sprite::create("Assets/coin.png")  ,"coin750", 0.05f, 4, Label::createWithTTF("x750"   , "fonts/Marker Felt.ttf", 50.f));
    items[5].ItemSet(Sprite::create("Assets/brush.png") ,"brush1" , 0.2f , 5, Label::createWithTTF("X1"     , "fonts/Marker Felt.ttf", 50.f));
    items[6].ItemSet(Sprite::create("Assets/gem.png")   ,"gem75"  , 0.05f, 6, Label::createWithTTF("x75"    , "fonts/Marker Felt.ttf", 50.f));
    items[7].ItemSet(Sprite::create("Assets/hammer.png"),"hammer1", 0.2f , 7, Label::createWithTTF("X1"     , "fonts/Marker Felt.ttf", 50.f));
    iteminit();

    //arrow
    arrowsprite = Sprite::create("Assets/wheel_arrow.png");
    if (arrowsprite == nullptr)
    {
        problemLoading("'Assets/wheel_arrow.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        arrowsprite->setScale(0.5f,0.6f);
        arrowsprite->setAnchorPoint(Vec2(0.5f,0.7f));
        arrowsprite->setPosition(Vec2(wheelposition.x, wheelposition.y + wheelsprite->getBoundingBox().size.height/2.f));
        arrowsprite->setTag(1);

        // add the sprite as a child to this layer
        this->addChild(arrowsprite, 2);
    }

    spinbutton = MenuItemImage::create("Assets/spin_button.png", "Assets/spin_button.png", CC_CALLBACK_0(Wheel::menuSpinCallback, this));

    if (spinbutton == nullptr ||
        spinbutton->getContentSize().width <= 0 ||
        spinbutton->getContentSize().height <= 0)
    {
        problemLoading("'Assets/spin_button.png'");
    }
    else
    {
        spinbutton->setScale(0.5f);
        spinbutton->setAnchorPoint(Vec2(0.5f, 1.f));
        spinbutton->setPosition(Vec2(wheelposition.x,wheelposition.y - wheelsprite->getBoundingBox().size.height/2.f));
        spinbutton->setTag(1);
        //spinbutton->setTitleText("Button Text");
        auto Spinlabel = Label::createWithTTF("Spin", "fonts/Marker Felt.ttf", 62);
        Spinlabel->setAnchorPoint(Vec2(0.5f, 0.5f));
        spinbutton->addChild(Spinlabel);
        Spinlabel->setPosition(Vec2(spinbutton->getBoundingBox().size.width, spinbutton->getBoundingBox().size.height));
        //this->addChild(spinbutton);
    }

     //create menu, it's an autorelease object
    auto menu = Menu::create(spinbutton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    ///event
    /// prepare
    listener_prepare = EventListenerCustom::create("prepare", [=](EventCustom* event) {
        wheelsprite->getPhysicsBody()->setAngularVelocity(2.f);
        });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener_prepare, this);
    /// spin
    listener_spin = EventListenerCustom::create("spin", [=](EventCustom* event) {
        resitem = CalculateProb();

        wheelsprite->getPhysicsBody()->setAngularVelocity(-32.f + resitem);
        wheelsprite->getPhysicsBody()->setAngularDamping(0.64f);
        });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener_spin, this);
    /// finish spin
    listener_finish = EventListenerCustom::create("finish", [=](EventCustom* event) {
        this->unscheduleUpdate();
        auto move = RotateTo::create(0.3f, items[resitem].angle);
        wheelsprite->runAction(move);
        _eventDispatcher->dispatchCustomEvent("result");
        });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener_finish, this);
    //show result
    listener_result = EventListenerCustom::create("result", [=](EventCustom* event) {
        std::string path = items[resitem].m_sprite->getResourceName();
        Sprite* res = Sprite::createWithTexture(items[resitem].m_sprite->getTexture());
        Label* name = Label::createWithTTF(items[resitem].m_label->getString(),
                                            items[resitem].m_label->getTTFConfig().fontFilePath,
                                            items[resitem].m_label->getTTFConfig().fontSize, Size::ZERO, TextHAlignment::RIGHT);
        name->setWidth(res->getBoundingBox().size.width*2);
        //name->setAnchorPoint(Vec2(0.0f, 1.0f));
        res->addChild(name);
        this->removeAllChildren();
        
        this->addChild(res);
        res->setPosition(wheelposition);
        res->setScale(0.1f);
        auto scaleby = ScaleBy::create(0.5f, 15.0f);
        res->runAction(scaleby);
        });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener_result, this);


    this->scheduleUpdate();

    return true;
}

void Wheel::update(float dt)
{

    int numspin = wheelsprite->getRotation() / 360.f;
    curr_rotation = wheelsprite->getRotation()-360.f * numspin;


    float v = wheelsprite->getPhysicsBody()->getAngularVelocity();
    float r = wheelsprite->getRotation();
    if (wheelsprite->getPhysicsBody()->getAngularVelocity() > 0.0f && wheelsprite->getRotation() <= -22.5f)
    {
        _eventDispatcher->removeEventListener(listener_prepare);
        _eventDispatcher->dispatchCustomEvent("spin");
    }

    if (wheelsprite->getPhysicsBody()->getAngularVelocity() < 0.0f && wheelsprite->getPhysicsBody()->getAngularVelocity() >= -0.1f
        && curr_rotation > items[resitem].angle - half_degree && curr_rotation < items[resitem].angle + half_degree)
    {
        _eventDispatcher->removeEventListener(listener_spin);
        _eventDispatcher->dispatchCustomEvent("finish");
    }
    

}


void Wheel::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);

}

void Wheel::menuSpinCallback()
{
    auto shrink = ScaleBy::create(0.3f, 0.0f);
    auto fadeout = FadeOut::create(0.3f);
    spinbutton->runAction(fadeout);
    spinbutton->runAction(shrink);
    _eventDispatcher->dispatchCustomEvent("prepare");
}

int Wheel::CalculateProb()
{

    int random = rand() % 100;
    
    int curritem = 0;
    int rangestart = 0;
    int rangeend = items[curritem].m_dropchance;

    while (true)
    {
        if (random >= rangestart && random < rangeend)
        {
            items[curritem].m_sprite->setTag(2);
            return curritem;
        }
        
        
        rangestart = rangeend;
        ++curritem;
        rangeend = rangestart + items[curritem].m_dropchance;
    }

    return -1;
}

void Wheel::iteminit()
{
    float radius = wheelsprite->getBoundingBox().size.width * 0.7f;
    for (int i = 0; i < numsection; ++i)
    {
        // position the sprite on the center of the screen
        if (wheelsprite)
        {
            items[i].m_sprite->setAnchorPoint(Vec2(0.5f, 0.5f));
            items[i].m_sprite->setScale(0.8f);
            items[i].m_sprite->setRotation(half_degree + degree_section * i);
            items[i].m_sprite->setPosition(Vec2(wheelsprite->getBoundingBox().size.width + radius * cos(CC_DEGREES_TO_RADIANS(90.f - half_degree - degree_section * i)),
                                                wheelsprite->getBoundingBox().size.height + radius * sin(CC_DEGREES_TO_RADIANS(90.f - half_degree - degree_section * i))));
            items[i].m_sprite->setTag(1);
            items[i].m_label->setAnchorPoint(Vec2(0.0f, 1.0f));
            items[i].m_sprite->addChild(items[i].m_label);
            items[i].m_label->setHorizontalAlignment(TextHAlignment::RIGHT);
            items[i].m_label->enableOutline(Color4B::BLACK, 3);
            items[i].m_label->setWidth(items[i].m_sprite->getBoundingBox().size.width);
            items[i].m_label->setPosition(Vec2(0.0f, 0.0f));
            items[i].angle = 360.f - half_degree - degree_section * i;
            wheelsprite->addChild(items[i].m_sprite, 0);
        }

    }

}

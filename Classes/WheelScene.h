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

#ifndef __WHEEL_SCENE_H__
#define __WHEEL_SCENE_H__

#include "cocos2d.h"
#include <vector>
USING_NS_CC;

struct Item 
{
    Sprite* m_sprite;
    std::string m_name;
    int m_dropchance;
    int m_id;
    Label* m_label;
    float angle;
    void ItemSet(Sprite* _sprite, std::string _name, float _drop, int _id, Label* _label)
    {
        m_sprite = _sprite;
        m_name = _name;
        m_dropchance = _drop * 100.f;
        m_id = _id;
        m_label = _label;
        
    }
};

class Wheel : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuSpinCallback();

    // implement the "static create()" method manually
    CREATE_FUNC(Wheel);

    void update(float dt);

private:
    PhysicsWorld* sceneWorld;
    void SetPhysicsWorld(PhysicsWorld* world) { sceneWorld = world; }
    int CalculateProb();
    void iteminit();
    //bool spin = false;
    EventListenerCustom* listener_prepare;
    EventListenerCustom* listener_spin;
    EventListenerCustom* listener_finish;
    EventListenerCustom* listener_result;

    Sprite* wheelsprite;
    //PhysicsBody* wheelphysics;
    std::vector<Item> items;
    Sprite* arrowsprite;
    MenuItem* spinbutton;
    int resitem;
    float curr_rotation;
   
    //scene
    int numsection = 8;
    float degree_section = 360.f/numsection;
    float half_degree = degree_section / 2.f;

    
};

#endif // __HELLOWORLD_SCENE_H__

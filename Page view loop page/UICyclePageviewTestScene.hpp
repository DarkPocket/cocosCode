//
//  UICyclePageviewTestScene.hpp
//  cocosTest
//
//  Created by 7cgames on 2018/3/27.
//
//

#ifndef UICyclePageviewTestScene_hpp
#define UICyclePageviewTestScene_hpp

#include <iostream>
#include "CCyclePageView.hpp"

#include "define.h"

USING_NS_CC;
using namespace cocos2d::ui;

class CCyclePageViewTestScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback

    void menuCloseCallback(cocos2d::Ref* pSender);
    

    void update2Callback(float dt);
    
    void updateSubPage(Layout **layout,int id);
    Layout*  addSubPage(int id);
    void addMainPageview();
    void pageViewEvent(cocos2d::Ref* sender, cocos2d::ui::PageView::EventType type);
    
    void menuBackCallback(Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(CCyclePageViewTestScene);
    
private:
    
    static int pageId;
    Size visibleSize;
    Vec2 origin;
    float w, h;
    CCyclePageView *m_pageView;
    ui::Button *addBtn, *removeBtn;
    
    int midPos;
    int pageAllCount;
    int pageShowCount;
};



#endif /* UICyclePageviewTestScene_hpp */

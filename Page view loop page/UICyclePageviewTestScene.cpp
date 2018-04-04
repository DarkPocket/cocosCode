//
//  UICyclePageviewTestScene.cpp
//  cocosTest
//
//  Created by 7cgames on 2018/3/27.
//
//

#include "UICyclePageviewTestScene.hpp"


int CCyclePageViewTestScene::pageId = 0;

Scene* CCyclePageViewTestScene::createScene()
{
    auto scene = Scene::create();
    auto layer = CCyclePageViewTestScene::create();
    scene->addChild(layer);
    return scene;
}
bool CCyclePageViewTestScene::init()
{

    if (!Layer::init())
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    origin = Director::getInstance()->getVisibleOrigin();
    w = visibleSize.width;
    h = visibleSize.height;
    
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(CCyclePageViewTestScene::menuCloseCallback, this));
    
    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        //problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }
    
    //// create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 2);
    
    pageId = 0;
    auto label = Label::createWithTTF("CCyclePageViewTestScene", "fonts/Marker Felt.ttf", 48);//Marker Felt
    label->setColor(Color3B::WHITE);
    
    if (label == nullptr)
    {
        //problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                origin.y + visibleSize.height - label->getContentSize().height));
        this->addChild(label, 1);
    }
    
    //// add "HelloWorld" splash screen"
    auto sprite = Sprite::create("backgroundB12.jpeg");
    if (sprite == nullptr)
    {
        //problemLoading("'next_3.jpg'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        
        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    
    m_pageView=nullptr;
    addMainPageview();
    
    this->schedule(schedule_selector(CCyclePageViewTestScene::update2Callback),0.1);
    
    
    
    auto backItem = MenuItemImage::create(
                                          "restart.png",
                                          "restart.png",
                                          CC_CALLBACK_1(CCyclePageViewTestScene::menuBackCallback, this));
    
    backItem->setPosition(Vec2(origin.x  + backItem->getContentSize().width/2 ,
                               visibleSize.height+ origin.y - backItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu2 = Menu::create(backItem, NULL);
    menu2->setPosition(Vec2::ZERO);
    this->addChild(menu2);
    
    return true;
}



void CCyclePageViewTestScene::addMainPageview()
{//
    
    pageShowCount=5;
    pageAllCount=8;
    midPos=3;
    
    m_pageView = CCyclePageView::create();
    m_pageView->setDirection(PageView::Direction::HORIZONTAL);
    m_pageView->setContentSize(visibleSize);
    m_pageView->setPosition(Vec2(0.0*w + origin.x, 0.0*h + origin.y));
    m_pageView->addEventListenerPageView(this, pagevieweventselector(CCyclePageViewTestScene::pageViewEvent));
    m_pageView->addPageChangedListener(std::bind(&CCyclePageViewTestScene::updateSubPage, this, std::placeholders::_1, std::placeholders::_2));
    m_pageView->setPageMount(pageAllCount);
    
    //posDot2.png posDot.png
    m_pageView->addPageViewIndicator("btn_checkmarkY.png", "btn_crossX.png");
    
    int pageNum = 5;
    for (int i = 0; i < pageNum; ++i)
    {
        m_pageView->addPage(addSubPage(i));
    }
    
    for (auto& IndexNodes :m_pageView->m_PageViewIndexNodes)
    {
        this->addChild(IndexNodes);
    }
    
    m_pageView->setCurrentPageIndex(midPos);
    m_pageView->setCurShowPagePos(midPos);
    this->addChild(m_pageView);
}

void CCyclePageViewTestScene::updateSubPage(Layout **layout,int id)
{
    *layout = Layout::create();
    (*layout)->setContentSize(visibleSize);
    
    std::string str = "win" + std::to_string((id + 1)%8) + ".png";
    ImageView* imageView = ImageView::create(str);
    imageView->setContentSize(visibleSize);
    imageView->setPosition(Vec2((*layout)->getContentSize().width / 2.0f, (*layout)->getContentSize().height / 2.0f));
    (*layout)->addChild(imageView);
    
    
    Text* label = Text::create(StringUtils::format("%d page %d",id, (id)), "fonts/Marker Felt.ttf", 40);
    label->setColor(Color3B(122, 192, 192));
    label->setPosition(imageView->getPosition());
    (*layout)->addChild(label);
    
}

Layout* CCyclePageViewTestScene::addSubPage(int id)
{
    //
    Layout* layout ;
    updateSubPage(&layout,id);
    return layout;
}

void CCyclePageViewTestScene::update2Callback(float dt)
{
    if(m_pageView!=nullptr)
    {
        m_pageView->checkToChangePage();
    }
}

void CCyclePageViewTestScene::pageViewEvent(cocos2d::Ref* sender, cocos2d::ui::PageView::EventType type)
{
    switch (type)
    {
        case cocos2d::ui::PageView::EventType::TURNING:
        {
            //PageView* pageView = dynamic_cast<PageView*>(pSender);
            int pos = m_pageView->getCurPageIndex();
            int pos2 = m_pageView->getCurrentPageIndex();
            CCLOG("getCurPageIndex  %d  %d  pageId=%d ", pos, pos2, pageId);
        }
            break;
        default:
            break;
    }
}



void CCyclePageViewTestScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    
}

void CCyclePageViewTestScene::menuBackCallback(Ref* pSender)
{
    auto scene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(scene);
}


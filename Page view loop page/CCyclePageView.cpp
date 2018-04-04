//
//  CCyclePageView.cpp
//  cocosTest
//
//  Created by 7cgames on 2018/3/27.
//
//

#include "CCyclePageView.hpp"



CCyclePageView* CCyclePageView::create()
{
    CCyclePageView* widget = new (std::nothrow) CCyclePageView();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

CCyclePageView::CCyclePageView() : m_updatePageCallback(nullptr), pageAllCount(0)
{
    
    auto  visibleSize = Director::getInstance()->getVisibleSize();
    
    IndicatorSpaceBetweenIndex=visibleSize.width*0.1;
    IndicatorPosition.x=visibleSize.width*0.5;
    IndicatorPosition.y=visibleSize.height*0.3;
    curMidPos=0;
    
}
CCyclePageView::~CCyclePageView()
{
}

void CCyclePageView::moveToLeftPages()
{
    /*
     pageShowCount=5;
   
     midPos=2;
     */
    //删尾
    int removeId=pageShowCount-1;
    removePageAtIndex(removeId);
    
    //插头
    int pageId=(curMidPos-3+pageAllCount)%pageAllCount;
    int inserId=0;
    insertPage(addUpdatePage(pageId),inserId);
    
    setCurrentPageIndex(pageShowCount/2);
    //    m_pageView->ListView::scrollToItem(2, Vec2::ANCHOR_MIDDLE, Vec2::ANCHOR_MIDDLE,0.111);
    
    curMidPos=(curMidPos-1+pageAllCount)%pageAllCount;
    
}
void CCyclePageView::moveToRightPages()
{
    /*
     pageShowCount=5;
     midPos=2;
     */
    //删头
    int removeId=0;
    removePageAtIndex(removeId);
    
    //插尾
    int pageId=(curMidPos+3+pageAllCount)%pageAllCount;
    int  inserId=pageShowCount-1;
    insertPage(addUpdatePage(pageId),inserId);
    
    setCurrentPageIndex(pageShowCount/2);
    curMidPos=(curMidPos+1+pageAllCount)%pageAllCount;
    
}

void CCyclePageView::checkToChangePage()
{
    
    int nextGamePagePos=static_cast<int>(getCurrentPageIndex());
    static int lastGamePagePos=static_cast<int>(getCurrentPageIndex());
    
    //int nextGamePagePos=curPagePos;
    
    if(lastGamePagePos!=nextGamePagePos)
    {
        CCLOG(" PagePos %d =>%d",lastGamePagePos,nextGamePagePos);
    }
    
    //right
    if(nextGamePagePos>lastGamePagePos)
    {
        if(nextGamePagePos>=pageAllCount-1)
        {
            nextGamePagePos=0;
        }
        lastGamePagePos=nextGamePagePos;
        CCLOG(" right  cur pos=%d",nextGamePagePos);
        moveToRightPages();
        lastGamePagePos=static_cast<int>( getCurrentPageIndex());
        
        CCLOG(" right  cmidPos =%d",curMidPos);
        setPageViewCurSelectedPageViewIndicator(curMidPos);
    }
    //left
    if(nextGamePagePos<lastGamePagePos)
    {
        if(nextGamePagePos<=0)
        {
            nextGamePagePos=pageAllCount-1;
        }
        lastGamePagePos=nextGamePagePos;
        CCLOG(" left  cur pos=%d",nextGamePagePos);
        moveToLeftPages();
        lastGamePagePos=static_cast<int>(getCurrentPageIndex());
        CCLOG(" left  cmidPos =%d",curMidPos);
         setPageViewCurSelectedPageViewIndicator(curMidPos);
    }
}


Layout* CCyclePageView::addUpdatePage(int id)
{
    Layout* layout;
    m_updatePageCallback(&layout,id);
    return layout;
}

void CCyclePageView::setPageMount(int count)
{
    pageAllCount=count;
}

void CCyclePageView::setCurShowPagePos(int pos)
{
    if(pos<pageAllCount&&pos>=0)
    {
        setCurrentPageIndex(pos);
        curMidPos=pos;
        setPageViewCurSelectedPageViewIndicator(pos);
    }
}

int CCyclePageView::getCurShowPagePos()
{
    return curMidPos;
}

void CCyclePageView::addPageViewIndicator(const std::string& texName,const std::string& untexName)
{
    if(m_PageViewIndexNodes.size()==0)
    {
        //close cocos Indicator
        //use diy Indicator
        setIndicatorEnabled(false);
        SelectedTexturePath=texName;
        UnselectedTexturePath=untexName;
        for (int i=0; i<pageAllCount; ++i)
        {
            Sprite* pageViewIndexNodes=Sprite::create( untexName );
            
            if(i==curMidPos)
            {
                pageViewIndexNodes->setTexture(texName);
            }
            m_PageViewIndexNodes.pushBack(pageViewIndexNodes);
        }
        updatePageViewIndicatorPosition();
    }
}

void CCyclePageView::updatePageViewIndicatorPosition()
{
    Vec2  StartPos;
    StartPos=IndicatorPosition;
    
    if(pageAllCount%2==0)
    {
        StartPos.x=IndicatorPosition.x-IndicatorSpaceBetweenIndex*(pageAllCount/2-0.5);
    }else
    {
        StartPos.x=IndicatorPosition.x-IndicatorSpaceBetweenIndex*(pageAllCount/2);
    }
    for (int i=0; i<m_PageViewIndexNodes.size(); ++i)
    {
        Vec2  curPos;
        curPos.y= StartPos.y;
        curPos.x=StartPos.x+IndicatorSpaceBetweenIndex*i;
        
        m_PageViewIndexNodes.at(i)->setPosition(curPos);
    }
}
void CCyclePageView::setPageViewIndicatorPosition(const Vec2& position)
{
    IndicatorPosition=position;
    updatePageViewIndicatorPosition();
}

void CCyclePageView::setPageViewCurSelectedPageViewIndicator(int pos)
{
    for (int i=0; i<m_PageViewIndexNodes.size(); ++i)
    {
        if(i==curMidPos)
        {
            m_PageViewIndexNodes.at(i)->setTexture(SelectedTexturePath);
        }else
        {
            m_PageViewIndexNodes.at(i)->setTexture(UnselectedTexturePath);
        }
    }
}

void CCyclePageView::setPageViewIndicatorSpaceBetweenIndex(float space)
{
    if(space>0)
    {
        IndicatorSpaceBetweenIndex=space;
    }else
    {
        IndicatorSpaceBetweenIndex=20;
    }
    updatePageViewIndicatorPosition();
}

float CCyclePageView::getPageViewIndicatorSpaceBetweenIndex()
{
    return IndicatorSpaceBetweenIndex;
}

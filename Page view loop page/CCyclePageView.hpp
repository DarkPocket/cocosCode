//
//  CCyclePageView.hpp
//  cocosTest
//
//  Created by 7cgames on 2018/3/27.
//
//
/*
 设置setPageMount（）
 设置 addPageChangedListener
 重写 void(Layout*,size_t)函数 返回  id 对应的layout
 父类    添加update函数 调用checkToChangePage  //  this->schedule(schedule_selector(MyPageviewScene::updateCallback),0.1);
 
 */
#ifndef CCyclePageView_hpp
#define CCyclePageView_hpp
#include "cocos2d.h"
#include "ui//CocosGUI.h"
USING_NS_CC;
using namespace cocos2d::ui;


class CCyclePageView : public PageView
{
public:
    static CCyclePageView* create();
    void moveToLeftPages();
    void moveToRightPages();
    void checkToChangePage();
    
    void addPageChangedListener(const std::function<void(Layout**, size_t)> callback){ m_updatePageCallback = callback; }
    
    void setPageMount(int count);
    
    void setCurShowPagePos(int pos);
    int getCurShowPagePos();
    
    Layout* addUpdatePage(int id);
    void addPageViewIndicator(const std::string& texName,const std::string& untexName);
    //    void setPageViewIndicatorIndexSelectedTexture(const std::string& texName);
    //    void setPageViewIndicatorIndexUnselectedTexture(const std::string& texName);
    void updatePageViewIndicatorPosition();
    void setPageViewIndicatorPosition(const Vec2& position);
    void setPageViewCurSelectedPageViewIndicator(int pos);
    void setPageViewIndicatorSpaceBetweenIndex(float space);
    float getPageViewIndicatorSpaceBetweenIndex();
    
    
    Vector<Sprite*> m_PageViewIndexNodes;
protected:
    CCyclePageView();
    ~CCyclePageView();
private:
    
    const int pageShowCount=5;
    int pageAllCount;
    //中间页面 的下标 与页面内容保持一致
    int curMidPos;
    std::function<void(Layout**,size_t)> m_updatePageCallback;
    
    
    Vec2 IndicatorPosition;
    float IndicatorSpaceBetweenIndex;
    std::string SelectedTexturePath,UnselectedTexturePath;
};

#endif /* CCyclePageView_hpp */

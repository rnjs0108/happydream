#ifndef __ITEM_SCENE_H__
#define __ITEM_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CustomTableViewCell.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ItemScene : public cocos2d::LayerColor,
	public cocos2d::extension::TableViewDataSource,
	public cocos2d::extension::TableViewDelegate
{
private:
	std::ostringstream textString;
	
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(ItemScene);
	virtual bool init();

	void setText();
	void setGageScale();
	void setButtonVisible();
	void setButtonHide();
	void setEquipImage();

	void useItemClicked(cocos2d::Ref* pSender);
	void dropItemClicked(cocos2d::Ref* pSender);
	void quitClicked(cocos2d::Ref* pSender);
	void leftClicked(cocos2d::Ref* pSender);
	void rightClicked(cocos2d::Ref* pSender);
	void equipItem1Clicked(cocos2d::Ref* pSender);
	void equipItem2Clicked(cocos2d::Ref* pSender);
	void viewAllItemClicked(cocos2d::Ref* pSender);
	void viewEquipItemClicked(cocos2d::Ref* pSender);
	void viewFoodItemClicked(cocos2d::Ref* pSender);
	void viewMaterialItemClicked(cocos2d::Ref* pSender);
	
	virtual void scrollViewDidScroll(ScrollView* view) {};
	virtual void scrollViewDidZoom(ScrollView* view) {};
	virtual Size tableCellSizeForIndex(TableView* table, ssize_t idx);
	virtual void tableCellTouched(TableView * table, TableViewCell * cell);
	virtual TableViewCell * tableCellAtIndex(TableView * table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(TableView * table);


};

#endif //__ITEM_SCENE_H__

#include "CPTFriendUnit.h"


CPTFriendUnit::CPTFriendUnit(Sprite* node)
{
	this->_unitType = UnitType::Friend;
	this->node = node;
}


CPTFriendUnit::~CPTFriendUnit(void)
{
}

Sprite* CPTFriendUnit::GetNode()
{
	return this->node;
}

CPTBOOL CPTFriendUnit::IsHit(CPTFLOAT x, CPTFLOAT y)
{
	auto height = this->node->getContentSize().height;
	auto width = this->node->getContentSize().width;
	auto postionX = this->node->getPosition().x;
	auto postionY = this->node->getPosition().y;
	auto anchorX = this->node->getAnchorPoint().x;
	auto anchorY = this->node->getAnchorPoint().y;
	auto actualX = postionX + width*(0.5 - anchorX);
	auto actualY = postionY + height*(0.5 - anchorY);
	auto maxX = actualX + 0.5 * width;
	auto minX = actualX - 0.5 * width;
	auto maxY = actualY + 0.5 * height;
	auto minY = actualY - 0.5 * height;
	if (x >= minX &&
		x <= maxX &&
		y >= minY &&
		y <= maxY)
	{
		return true;
	}
	else
	{
		return false;
	}
}
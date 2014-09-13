#include "CPTEnemyUnit.h"


CPTEnemyUnit::CPTEnemyUnit(Sprite* node)
{
	this->_unitType = UnitType::Enemy;
	this->node = node;
}


CPTEnemyUnit::~CPTEnemyUnit(void)
{

}

Sprite* CPTEnemyUnit::GetNode()
{
	return this->node;
}

CPTBOOL CPTEnemyUnit::IsHit(CPTFLOAT x, CPTFLOAT y)
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


void CPTEnemyUnit::AddAbility(CPTAbility* ability)
{
	this->abilities->push_back(ability);
}

void CPTEnemyUnit::RunAbilities()
{
	this->node->stopAllActions();
	// this->node->getActionManager()->removeAllActions();
	for (auto iter = this->abilities->begin(); iter != this->abilities->end(); iter++)
	{
		if ((*iter)->IsEnable == true)
		{
			this->node->runAction((*iter)->GetAction());
		}
	}
}
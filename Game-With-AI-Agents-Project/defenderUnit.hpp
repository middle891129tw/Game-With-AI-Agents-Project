/*
* defenfderUnit.hpp
*/

#include "enemyUnit.hpp"

class DefenderUnit : public EnemyUnit
{
public:
	DefenderUnit(Unit* target);
	~DefenderUnit();

	void defend();

protected:
	Unit* _target;
};
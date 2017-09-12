#ifndef UIOBJECTBASE_H
#define UIOBJECTBASE_H
#include "ObjectBase\ObjectBase.h"
#include "TaskManager\TaskManager.h"


class UIObjectBase : public Lib::ObjectBase
{
public:
	UIObjectBase() = default;
	virtual ~UIObjectBase() = default;

	virtual void Update() = 0;
	virtual void Draw() = 0;

private:

};

#endif

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ミッションリスト
//
// Created by Ryusei Kajiya on 20151204
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重定義防止
#pragma once

//*****************************************************************************
// include
#include "Mission/mission.h"

//*****************************************************************************
// クラス設計
class MissionList
{
public:
	MissionList(){}
	virtual ~MissionList(){}

	void AddObserver(Mission* observer)
	{
		observer->_next = _head;
		_head = observer;
	}

	void RemoveObserver(Mission* observer)
	{
		if( _head == observer)
		{
			_head = observer->_next;
			observer->_next = nullptr;
			return;
		}

		Mission *current = _head;

		while( current != nullptr )
		{
			if( current->_next == observer )
			{
				current->_next = observer->_next;
				observer->_next = nullptr;
				return;
			}
			current = current->_next;
		}
	}

protected:

	void Notify(MISSION_EVENT mission_event)
	{
		Mission* observer = _head;

		while( observer  != nullptr)
		{
			observer->OnNotify(mission_event);
			observer = observer->_next;
		}
	}

private:
	Mission* _head;
};
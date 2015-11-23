//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���\�[�X�{�b�N�X
//
// Created by Ryusei Kajiya on 20151102
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �N���X�݌v
template<class T>
class ResourceBox
{
private:

	using ResourceMap = std::map< s32, T>;
	ResourceMap _map;

public:
	//ResourceBox():{}
	//virtual ~ResourceBox(){}

	// �ǉ�
	// true : �ǉ�����
	// false : �ǉ����s
	bool Add(T resource,s32 id)
	{
		if( _map.find(id) == _map.end())
		{
			// ���\�[�X�̒ǉ�
			_map.insert(ResourceMap::value_type(id, resource)).first->second = resource;
			return true;
		}
		return false;
	}

	// �擾
	const T Get(const int id)
	{
		if( _map.find(id) == _map.end() )
		{// �����ꍇ
			return T();
		}

		return _map[id];
	}

	// �v�f�̍폜
	bool Delete(const int id)
	{
		if( _map.find(id) == _map.end() )
		{// �����ꍇ
			return false;
		}

		// �v�f�̍폜 : �f�X�g���N�^����
		_map.erase(id);

		return true;
	}

	// �v�f�̑S�폜
	void Clear()
	{
		for( auto it = _map.begin(); it != _map.end(); ++it )
		{
			_map.erase(it);
		}
		_map.clear();

		_current_id = 0;
	}

	// Begin
	typename ResourceMap::iterator Begin(){ return _map.begin(); }

	// End
	typename ResourceMap::iterator End(){ return _map.end(); }



};

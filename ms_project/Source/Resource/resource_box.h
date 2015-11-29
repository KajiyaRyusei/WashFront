//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���\�[�X�{�b�N�X
// 
// Created by Ryusei Kajiya on 20151029
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
public:
	ResourceBox() : _current_id{ 0 }{}
	virtual ~ResourceBox(){}

	// �ǉ�
	s32 Add(T resource)
	{
		// ���\�[�X�̒ǉ�
		_map.insert(ResourceMap::value_type(_current_id, resource)).first->second = resource;
		return _current_id++;
	}

	// �擾
	const T Get(const int id)
	{
		if( _map.find(id) == _map.end() )
		{// �����ꍇ
			return nullptr;
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
			SafeDelete(it->second);
		}
		_map.clear();

		_current_id = 0;
	}

private:

	using ResourceMap = std::map<int, T>;
	ResourceMap _map;
	s32 _current_id;
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// リソースボックス
// 
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// クラス設計
template<class T>
class ResourceBox
{
public:
	ResourceBox() : _current_id{ 0 }{}
	virtual ~ResourceBox(){}

	// 追加
	s32 Add(T resource)
	{
		// リソースの追加
		_map.insert(ResourceMap::value_type(_current_id, resource)).first->second = resource;
		return _current_id++;
	}

	// 取得
	const T Get(const int id)
	{
		if( _map.find(id) == _map.end() )
		{// 無い場合
			return nullptr;
		}

		return _map[id];
	}

	// 要素の削除
	bool Delete(const int id)
	{
		if( _map.find(id) == _map.end() )
		{// 無い場合
			return false;
		}

		// 要素の削除 : デストラクタ発動
		_map.erase(id);

		return true;
	}

	// 要素の全削除
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

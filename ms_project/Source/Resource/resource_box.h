//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// リソースボックス
//
// Created by Ryusei Kajiya on 20151102
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
private:

	using ResourceMap = std::map< s32, T>;
	ResourceMap _map;

public:
	//ResourceBox():{}
	//virtual ~ResourceBox(){}

	// 追加
	// true : 追加成功
	// false : 追加失敗
	bool Add(T resource,s32 id)
	{
		if( _map.find(id) == _map.end())
		{
			// リソースの追加
			_map.insert(ResourceMap::value_type(id, resource)).first->second = resource;
			return true;
		}
		return false;
	}

	// 取得
	const T Get(const int id)
	{
		if( _map.find(id) == _map.end() )
		{// 無い場合
			return T();
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

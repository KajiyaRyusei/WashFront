////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////
//// �����Ԃ�
//// 
//// Created by Ryusei Kajiya on 20151125
////
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
////*****************************************************************************
//// ���d�C���N���[�h�h�~
//#pragma once
//
////*****************************************************************************
//// �N���X�݌v
//class WaterSpray
//{
//public:
//	WaterSpray* GetNext() const { return _state._next; }
//	void SetNext(WaterSpray* next){ _state._next = next; }
//	// ������
//	void Initialize(
//		const D3DXVECTOR3& position,
//		const D3DXQUATERNION& quaternion);
//	// �A�j���[�V����
//	bool Animate();
//	// �g�p���Ă��邩
//	bool IsUse()const { return _frame_left > 0; }
//
//private:
//	u32 _frame_left;
//
//	union
//	{
//		struct
//		{
//			D3DXVECTOR3 _position;
//			D3DXQUATERNION _quaternion;
//			D3DXVECTOR3 _scale;
//		};
//
//		WaterSpray* _next;
//	}_state;
//};
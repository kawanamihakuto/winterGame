#include "Input.h"
#include<DxLib.h>

Input::Input():
	inputData_{},
	lastInputData_{},
	inputTable_{}
{
	//イベント名を添え字にして、
	// 右辺に実際の入力種別と入力コードの配列を置く
	inputTable_["ok"] = { {PeripheralType::keyboard,KEY_INPUT_RETURN},
							{PeripheralType::pad1,PAD_INPUT_START} };

	inputTable_["left"] = { {PeripheralType::keyboard,KEY_INPUT_LEFT},
							{PeripheralType::pad1,PAD_INPUT_LEFT} };
	inputTable_["up"] = { {PeripheralType::keyboard,KEY_INPUT_UP},
							{PeripheralType::pad1,PAD_INPUT_UP} };
	inputTable_["right"] = { {PeripheralType::keyboard,KEY_INPUT_RIGHT},
							{PeripheralType::pad1,PAD_INPUT_RIGHT} };
	inputTable_["down"] = { {PeripheralType::keyboard,KEY_INPUT_DOWN},
							{PeripheralType::pad1,PAD_INPUT_DOWN} };

	inputTable_["jump"] = { {PeripheralType::keyboard,KEY_INPUT_SPACE},
							{PeripheralType::pad1,PAD_INPUT_A} };

	inputTable_["inhale"] = { {PeripheralType::keyboard,KEY_INPUT_Z},
							{PeripheralType::pad1,PAD_INPUT_B} };



	//あらかじめ入力データの枠を開けておく
	//ここで枠を開けておかないと、
	//チェックの際にAt関数でクラッシュする可能性がある
	for (const auto& inputInfo : inputTable_)
	{
		inputData_[inputInfo.first] = false;
		lastInputData_[inputInfo.first] = false;
	}
}

void Input::Update()
{
	char keyState[256];
	GetHitKeyStateAll(keyState);//生のキーボード情報
	int padState = GetJoypadInputState(DX_INPUT_PAD1);//生のパッド情報
	lastInputData_ = inputData_;//直前のフレームを更新(前のフレーム情報をコピー)
	//すべての入力イベントをチェック
	//ここでinputData_が更新される
	//inputTable_を回して各イベントの入力をチェック
	for (const auto inputInfo : inputTable_)
	{
		auto& input = inputData_[inputInfo.first];//inputInfo.firstには"ok"等が入っている
		//InputStateのベクタを回す
		for (const auto& state : inputInfo.second)
		{
			//入力種別をチェック
			switch (state.type)
			{
			case PeripheralType::keyboard://キーボードの場合
				input = keyState[state.id];
				break;
			case PeripheralType::pad1:
				input = (padState & state.id);
				break;
			}
			//ここでbreakしないと最後のチェックで押されていないとfalseになる
			if (input)
			{
				break;
			}
		}
		
	}
}

bool Input::IsPressed(const char* name) const
{
	return inputData_.at(name);
}

bool Input::IsTriggered(const char* name) const
{
	return inputData_.at(name) && !lastInputData_.at(name);
}

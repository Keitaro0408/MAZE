/**
 * @file   KeyDevice.h
 * @brief  KeyDeviceクラスのヘッダファイル
 * @author kotani
 */
#ifndef KEYDEVICE_H
#define KEYDEVICE_H
#include <dinput.h>	
#include <map>
#include <string>
#include <list>
#include "..\..\Singleton.h"

namespace Lib
{
	/**
	 * キーの状態を表したenum
	 */
	enum KEYSTATE
	{
		KEY_PUSH,	//!< キーが押された瞬間の状態
		KEY_RELEASE,//!< キーが離された瞬間の状態
		KEY_ON,		//!< キーが押され続けている状態
		KEY_OFF		//!< キーが押されていない状態
	};

	struct KEYDATA
	{
		KEYSTATE KeyData;
		int		 DIKeyState;
	};

	class KeyDevice
	{
		friend Singleton<KeyDevice>;
	public:
		/**
		 * KeyDeviceの初期化関数
		 * @param[in] _pDInput8 DirectInputオブジェクト
		 * @param[in] _hWnd KeyDeviceに対応させるウィンドウハンドル
		 * @return デバイスの初期化に成功したらtrueが返る
		 */
		bool Initialize(LPDIRECTINPUT8 _pDInput8, HWND _hWnd);

		/**
		 * KeyDeviceの解放関数
		 */
		void Finalize();

		/**
		 * KeyDeviceの状態を更新する
		 */
		void Update();

		/**
		 * 更新するキーに名前をつけて登録する
		 * @param[in] _dik チェックしたいキーのDIK
		 * @param[in] _keyName 登録するキーの名前
		 */
		void KeyCheckEntry(std::string _keyName, int _dik);

		/**
		 * 登録したキーの全ての状態をチェック(すべて一致)
		 * @param[in] _keyName チェックするキーの名前
		 * @param[in] _keyState チェックする状態
		 * @return 全ての登録されたキーの状態が同じならtrueを返す
		 */
		bool AllMatchKeyCheck(std::string _keyName, KEYSTATE _keyState);

		/**
		 * 登録したキーの全ての状態をチェック(一つでも一致)
		 * @param[in] _keyName チェックするキーの名前
		 * @param[in] _keyState チェックする状態
		 * @return 一つでも登録されたキーの状態が同じならtrueを返す
		 */
		bool AnyMatchKeyCheck(std::string _keyName, KEYSTATE _keyState);

	private:
		/**
		 * KeyDeviceクラスのコンストラクタ
		 */
		KeyDevice();

		/**
		 * KeyDeviceクラスのデストラクタ
		 */
		~KeyDevice(){};

		LPDIRECTINPUT8							   m_pDInput8;
		HWND									   m_hWnd;
		LPDIRECTINPUTDEVICE8					   m_pDInputDevice8;
		BYTE									   m_pDIKeyState[256];
		BYTE									   m_pOldDIKeyState[256];
		std::map<std::string, std::list<KEYDATA> > m_SetKeyState;

	};
}


#endif

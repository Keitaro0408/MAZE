/**
 * @file   ApplicationBase.h
 * @brief  ApplicationBaseクラスのヘッダファイル
 * @author kotani
 */
#ifndef APPLICATIONBASE_H
#define APPLICATIONBASE_H
/**
 * @mainpage Library使い方
 * エントリーポイントはApplicationBaseに内蔵されており
 * 実装し、グローバルで宣言する事でウィンドウが表示される。 \n\n
 * GitHub url : https://github.com/Keitaro0408/Library
 */

#include <Windows.h>
#ifdef _MSC_VER
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"d3dx10.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dsound.lib")
#pragma comment(lib,"strmiids.lib")
#pragma comment(lib,"xinput.lib")
//#pragma comment(lib,"libfbxsdk-mt.lib")
#endif

namespace Lib
{
	/**
	 * このクラスがメイン
	 * この抽象クラスを実装し、グローバルで宣言する事でウィンドウが表示される
	 */
	class ApplicationBase
	{
	public:
		ApplicationBase(LPCTSTR _appName,int _windowWidth, int _windowHeight);
		virtual ~ApplicationBase();

		static inline ApplicationBase* GetInstance()
		{
			return m_pInstance;
		}


		/**
		 * 初期化処理
		 *
		 * ライブラリで自動に呼ばれる
		 */
		virtual void Initialize() = 0;

		/**
		 * 開放処理
		 *
		 * ライブラリで自動に呼ばれる
		 */
		virtual void Finalize() = 0;

		/**
		 * この関数が毎フレーム呼ばれる
		 * @return trueになると終了する
		 */
		bool MainLoop();

		int Boot();

	private:
		/**
		 * ライブラリの初期化
		 */
		void InitLib();

		/**
		 * ライブラリの解放
		 */
		void ReleaseLib();

		static ApplicationBase* m_pInstance;
		int m_WindowWidth;
		int m_WindowHeight;
		LPCTSTR m_AppName;

	};

	inline int Boot()
	{
		return ApplicationBase::GetInstance()->Boot();
	};
}


#endif

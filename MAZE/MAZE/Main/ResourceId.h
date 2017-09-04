#ifndef RESOUCEID_H
#define RESOUCEID_H

namespace ResourceId
{
	namespace Title
	{
		enum Sound
		{
		};

		enum Texture
		{
			BACKGROUND_TEX,
			TEX_MAX
		};
	}

	namespace Game
	{
		enum Sound
		{
			//!< BGM
			MAIN_BGM,
			//!< SE
			START_SE,
			LANDING_SE,
			COIN_SE,
			SOUND_MAX
		};

		enum Texture
		{
			BACKGROUND_TEX, //!< �w�i
			UNITY_TEX,		//!< �����e�N�X�`��
			TEX_MAX
		};
	}
}


#endif

#pragma once

using   pcmEncodeHandle = void*;

enum Law
{
    Law_ULaw = 0, 		/**< U law */
    Law_ALaw = 1, 		/**< A law */
    Law_PCM16 = 2, 		/**< 16 bit uniform PCM values. 原始 pcm 数据 */
    Law_PCM8 = 3,
    Law_G726 = 4		/**< G726 */
};

enum Rate
{
    Rate16kBits = 2,	/**< 16k bits per second (2 bits per ADPCM sample) */
    Rate24kBits = 3,	/**< 24k bits per second (3 bits per ADPCM sample) */
    Rate32kBits = 4,	/**< 32k bits per second (4 bits per ADPCM sample) */
    Rate40kBits = 5	/**< 40k bits per second (5 bits per ADPCM sample) */
};

enum G711Type
{
    G711U,G711A
};
typedef struct _g711param
{
    ;
}G711Param;

typedef struct _g726param
{
    unsigned char ucRateBits;//Rate16kBits Rate24kBits Rate32kBits Rate40kBits
}G726Param;

typedef struct _initParam
{
    unsigned char	ucAudioCodec;			// Law_uLaw  Law_ALaw Law_PCM16 Law_G726
    unsigned char	ucAudioChannel;			//1
    unsigned int	u32AudioSamplerate;		//8000
    unsigned int	u32PCMBitSize;			//16
    union
    {
        G711Param g711param;
        G726Param g726param;
    };

}InitParam;
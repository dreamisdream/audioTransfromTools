#pragma once

/*
    
*/
#include "common.h"

#define USE_SHOUT_G711PACK 1

#if USE_SHOUT_G711PACK
#define G711_ONE_LEN 160
#define G711_ONE_OFFSET 0

#else
#define G711_ONE_LEN 164
#define G711_ONE_OFFSET 4
#endif

const int CON_PCM_SIZE = 320;

class AudioBuffer;

/*
    输入源数据流信息
*/
class InputAudioInfo
{
public:
    InputAudioInfo()
    {
        m_initParam.u32AudioSamplerate = 8000;
        m_initParam.ucAudioChannel = 1;
        m_initParam.u32PCMBitSize = 16;
        m_initParam.ucAudioCodec = Law_ALaw;
    }

    InputAudioInfo(InitParam param) 
    {
        m_initParam = param;
    }

    ~InputAudioInfo()
    {
        ;
    }
    
    unsigned int codecType() 
    {
        return m_initParam.ucAudioCodec;
    }

    unsigned int samplerate()
    {
        return m_initParam.u32AudioSamplerate;
    }
    
    unsigned int channel() 
    {
        return m_initParam.ucAudioChannel;
    }

    unsigned int pcmBitsize()
    {
        return m_initParam.u32PCMBitSize;
    }

    unsigned char g726RateBits()
    {
        return m_initParam.g726param.ucRateBits;
    }
private:
    InitParam m_initParam;
};

/*
    音频编解码基类
    * 目前支持 encode pcm->g711a pcm->g711u pcm->g726
               decode g711a->pcm g711u->pcm g726->pcm
*/

class DecodeToPcm
{
public:
    DecodeToPcm();
    virtual ~DecodeToPcm();

    virtual void init(InputAudioInfo info) = 0;
    // other -> pcm
    virtual int decode(unsigned char *outBuffer, unsigned int *outLen, unsigned char*inputBuffer, unsigned int inBufferLen) = 0;
    // pcm -> other
    virtual int encode(unsigned char *outBuffer, unsigned int *outLen, unsigned char*inputBuffer, unsigned int inBufferLen) = 0;
    virtual int pcmSize() = 0;
    virtual int g7FrameSize() = 0;
};

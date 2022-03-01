#pragma once

#include "G711ToPcm.h"
#include "G726ToPcm.h"
#include "AudioBuffer.h"

/*
    G7 -> pcm
*/
class G7ToPcm
{
public:
    G7ToPcm();
    ~G7ToPcm();

    bool init(InputAudioInfo info);
    // g7 -> pcm
    int pcmEncode(unsigned char* inbuf, unsigned int inlen, unsigned char* outbuf, unsigned int* outlen);
    // pcm -> g7
    int pcmDecode(unsigned char* inbuf, unsigned int inlen, unsigned char* outbuf, unsigned int* outlen);
private:
    int pcmEncodeObject(unsigned char* inbuf, unsigned int inlen, unsigned char* outbuf, unsigned int* outlen);
    int pcmDecodeObject(unsigned char* inbuf, unsigned int inlen, unsigned char* outbuf, unsigned int* outlen);
    bool createEncodePcm();
    bool createBuffer();

private:

    // pcm 缓存
    unsigned int m_pcmTmpSize;
    unsigned char *m_pcmTmpBuffer;

    // g7 缓存
    unsigned char *m_g7FrameBuffer;
    unsigned long m_g7FrameBufferSize;

    // 数据缓存对象
    AudioBuffer *m_audioBuffer;
    // 源数据参数信息
    InputAudioInfo m_inAudioInfo;
    // 编码器
    DecodeToPcm* m_pDecodeToPcm;
};


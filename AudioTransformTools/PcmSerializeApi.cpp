#include "PcmSerializeApi.h"
#include "G7ToPcm.h"

Audio_API pcmEncodeHandle Audio_APICALL pcmCodeInit(InitParam initparam)
{
    G7ToPcm *handle = new G7ToPcm();
    
    InputAudioInfo inputParam(initparam);
    handle->init(inputParam);

    return handle;
}

Audio_API int Audio_APICALL pcmEncode(pcmEncodeHandle handle, unsigned char* inbuf, unsigned int inlen, unsigned char* outbuf, unsigned int* outlen)
{
    if (handle)
        return reinterpret_cast<G7ToPcm*>(handle)->pcmEncode(inbuf, inlen, outbuf, outlen);
    return -1;
}

Audio_API int Audio_APICALL pcmDecode(pcmEncodeHandle handle, unsigned char * inbuf, unsigned int inlen, unsigned char * outbuf, unsigned int * outlen)
{
    if (handle)
        return reinterpret_cast<G7ToPcm*>(handle)->pcmDecode(inbuf, inlen, outbuf, outlen);
    return -1;
}

Audio_API void Audio_APICALL pcmRelease(pcmEncodeHandle handle)
{
    if (handle)
        delete reinterpret_cast<G7ToPcm*>(handle);
    return;
}

Audio_API int Audio_APICALL pcm16Topcm8(char* inBuffer, int inLen, char*outBuffer, int *outLen)
{
    char *out = (char *)outBuffer;
    short *in = (short *)inBuffer;

    if (inBuffer == nullptr || inLen <= 0)
        return -1;

    for (int i = 0; i < inLen / 2; i++) {
        out[i] = unsigned char(char(in[i] >> 8) + 128);
    }

    *outLen = inLen / 2;
    return inLen / 2;
};


Audio_API int Audio_APICALL pcm8Topcm16(char* inBuffer, int inLen, char*outBuffer, int *outLen)
{
    short *out = (short *)outBuffer;
    char *in = (char *)inBuffer;

    if (inBuffer == nullptr || inLen <= 0)
        return -1;

    for (int i = 0; i < inLen; i++) {
        out[i] = (short)(in[i] - 128) << 8;
    }

    *outLen = inLen * 2;
    return inLen * 2;
};
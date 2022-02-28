#include "pcmEncode.h"
#include "G7ToPcm.h"

Audio_API pcmEncodeHandle Audio_APICALL pcmEncodeInit(InitParam initparam)
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

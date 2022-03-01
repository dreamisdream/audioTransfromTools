#include "decodeToPcm.h"

#include <cstdint>
#include <cstdio>

DecodeToPcm::DecodeToPcm()
{
    printf("%s %d\n", __FUNCTION__, __LINE__);
    ;
}

DecodeToPcm::~DecodeToPcm()
{
    printf("%s %d\n", __FUNCTION__, __LINE__);
    ;
}



/*

*/
//DecodeToPcmBase::DecodeToPcmBase()
//{
//    ;
//}
//
//DecodeToPcmBase::~DecodeToPcmBase()
//{
//    ;
//}
//
//void DecodeToPcmBase::init(InputAudioInfo info)
//{
//    m_g7FrameSize = G711_ONE_LEN;
//
//}
//
//int DecodeToPcmBase::pcmSize()
//{
//    return CON_PCM_SIZE;
//}
//
//int DecodeToPcmBase::g7FrameSize()
//{
//    return m_g7FrameSize;
//}
//
//int DecodeToPcmBase::decode(unsigned char *outBuffer, unsigned int *outLen, unsigned char*inputBuffer, unsigned int inBufferLen)
//{
//    if (outBuffer == nullptr ||
//        inputBuffer == nullptr ||
//        outLen == nullptr || inBufferLen == 0)
//        return -1;
//    int16_t *dst = (int16_t*)outBuffer;
//    uint8_t *src = (uint8_t*)inputBuffer;
//    
//    if (*outLen < 2 * inBufferLen) {
//        printf("outLen is too short\n");
//        return -2;
//    }
//    
//    for (int i = 0; i < inBufferLen; ++i) {
//        *(dst++) = (int16_t)DecodeOneChar(*(src++));
//    }
//    *outLen = 2 * inBufferLen;
//
//    return 2 * inBufferLen;
//}
//
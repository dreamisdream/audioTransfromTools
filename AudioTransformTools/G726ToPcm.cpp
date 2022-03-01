#include "G726ToPcm.h"
#include "condef.h"
#include <cstdio>

G726ToPcm::G726ToPcm() 
{
    printf("%s %d\n", __FUNCTION__, __LINE__);
    ;
}

G726ToPcm::~G726ToPcm()
{
    printf("%s %d\n", __FUNCTION__, __LINE__);
    SAFE_FREE_BUF(m_state726);
}

void  G726ToPcm::init(InputAudioInfo info)
{
    m_g7FrameSize = G711_ONE_LEN;
    m_state726 = (g726_state_t *)malloc(sizeof(g726_state_t));

    int rateBits = info.g726RateBits();
    switch (rateBits) {
    case Rate16kBits:
        m_bitRate = 8000 * 2;
        m_pcmSize = (2 * m_g7FrameSize * 120 + 30) / 30;
        break;
    case Rate24kBits:
        m_bitRate = 8000 * 3;
        m_pcmSize = (2 * m_g7FrameSize * 80 + 30) / 30;
        break;
    case Rate32kBits:
        m_bitRate = 8000 * 4;
        m_pcmSize = (2 * m_g7FrameSize * 60 + 30) / 30;
        break;
    case Rate40kBits:
        m_bitRate = 8000 * 5;
        m_pcmSize = (2 * m_g7FrameSize * 48 + 30) / 30;
        break;
    default:
        break;
    }
    m_state726 = g726_init(m_state726, m_bitRate);

}

int G726ToPcm::decode(unsigned char *outBuffer, unsigned int *outLen, unsigned char*inputBuffer, unsigned int inBufferLen)
{
    int result = g726_decode(m_state726, (short*)outBuffer, inputBuffer, inBufferLen);

    *outLen = result * 2;

    return result * 2;

}

int G726ToPcm::encode(unsigned char * outBuffer, unsigned int * outLen, unsigned char * inputBuffer, unsigned int inBufferLen)
{
    int result = g726_encode(m_state726, inputBuffer, (short*)outBuffer, inBufferLen);
    
    *outLen = result * 2;

    return result * 2;
}

int G726ToPcm::pcmSize()
{
    return m_pcmSize;
}

int G726ToPcm::g7FrameSize()
{
    return m_g7FrameSize;
}



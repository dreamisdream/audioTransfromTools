#include "G711ToPcm.h"
#include "g711.h"
#include <cstdio>

G711ToPcm::G711ToPcm()
{
    printf("%s %d\n", __FUNCTION__, __LINE__);
    ;
}

G711ToPcm::~G711ToPcm()
{
    printf("%s %d\n", __FUNCTION__, __LINE__);
    ;
}

void G711ToPcm::setOriginType(G711Type type)
{
    m_type = type;
}

int G711ToPcm::decode(unsigned char *outBuffer, unsigned int *outLen, unsigned char*inputBuffer, unsigned int inBufferLen)
{
    auto result = g711Decode((char *)outBuffer, (char *)inputBuffer, inBufferLen, m_type);
    
    *outLen = result;

    return  result;
}

int G711ToPcm::encode(unsigned char * outBuffer, unsigned int * outLen, unsigned char * inputBuffer, unsigned int inBufferLen)
{
    auto result = g711EnCode((char *)outBuffer, (char *)inputBuffer, inBufferLen, m_type);

    *outLen = result;

    return  result;
}

int G711ToPcm::pcmSize()
{
    return CON_PCM_SIZE;
}

void G711ToPcm::init(InputAudioInfo info)  
{
    if (info.codecType() == 1)
        this->setOriginType(G711Type::G711A);
    else
        this->setOriginType(G711Type::G711U);
    m_g7FrameSize = G711_ONE_LEN;
}

int G711ToPcm::g7FrameSize()
{
    return m_g7FrameSize;
}

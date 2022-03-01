#pragma once
#include "decodeToPcm.h"
#include "g726.h"

class G726ToPcm :public DecodeToPcm
{
public:
    G726ToPcm();
    virtual ~G726ToPcm();

    virtual void init(InputAudioInfo info) override;
    virtual int decode(unsigned char *outBuffer, unsigned int *outLen, unsigned char*inputBuffer, unsigned int inBufferLen)override;
    virtual int encode(unsigned char *outBuffer, unsigned int *outLen, unsigned char*inputBuffer, unsigned int inBufferLen)override;
    virtual int pcmSize();
    virtual int g7FrameSize();
private:
    g726_state_t *m_state726;

    int m_bitRate;
    int m_g7FrameSize;
    int m_pcmSize;
};


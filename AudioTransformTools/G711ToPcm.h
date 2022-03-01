#pragma once
#include "DecodeToPcm.h"
#include "common.h"
/*
    G711->pcm 
*/
class G711ToPcm :public DecodeToPcm
{
public:
    G711ToPcm();
    virtual ~G711ToPcm();
    
    virtual void init(InputAudioInfo info) override;
    virtual int decode(unsigned char *outBuffer, unsigned int *outLen, unsigned char*inputBuffer, unsigned int inBufferLen) override;
    virtual int encode(unsigned char *outBuffer, unsigned int *outLen, unsigned char*inputBuffer, unsigned int inBufferLen) override;
    virtual int pcmSize() override;
    virtual int g7FrameSize()override ;

private:
    void setOriginType(G711Type type);
private:
    // 数据源的类型 a1 u0
    G711Type m_type;
    int m_g7FrameSize;
};


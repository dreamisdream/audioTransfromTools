#include "G7ToPcm.h"
#include "condef.h"

#include <cstring>
#include <cstdio>
#include <cstdlib>

G7ToPcm::G7ToPcm()
{
    m_pcmTmpBuffer = nullptr;
    m_g7FrameBuffer = nullptr;
    m_audioBuffer = nullptr;
    m_pDecodeToPcm = nullptr;

    m_pcmTmpSize = 0;
    printf("%s %d\n", __FUNCTION__, __LINE__);
}

G7ToPcm::~G7ToPcm()
{
    SAFE_DELETE_OBJ(m_audioBuffer);
    SAFE_DELETE_OBJ(m_pDecodeToPcm);
    SAFE_FREE_BUF(m_g7FrameBuffer);
    SAFE_FREE_BUF(m_pcmTmpBuffer);
    printf("%s %d\n", __FUNCTION__, __LINE__);
}


bool G7ToPcm::init(InputAudioInfo info)
{
 
    m_inAudioInfo = info;
    if (!createEncodePcm())
        return false;
    
    return createBuffer();
}

bool G7ToPcm::createEncodePcm()
{
    auto type = m_inAudioInfo.codecType();
    if (type == Law_ALaw || type == Law_ULaw) {
        m_pDecodeToPcm = new G711ToPcm();
 
    }  else if (type == Law_G726){
        m_pDecodeToPcm = new G726ToPcm();
    } else {
        return false;
    }

    m_pDecodeToPcm->init(m_inAudioInfo);

    return true;
}

bool G7ToPcm::createBuffer()
{
    m_g7FrameBufferSize = m_pDecodeToPcm->g7FrameSize();
    m_g7FrameBuffer = (unsigned char *)malloc(m_g7FrameBufferSize * sizeof(unsigned char));
    memset(m_g7FrameBuffer, 0, m_g7FrameBufferSize);

    m_pcmTmpSize = m_pDecodeToPcm->pcmSize();
    m_pcmTmpBuffer = (unsigned char *)malloc(m_pcmTmpSize * sizeof(unsigned char));
    memset(m_pcmTmpBuffer, 0, m_pcmTmpSize);

    m_audioBuffer = new AudioBuffer();
    return true;
}

int G7ToPcm::pcmEncode(unsigned char* inbuf, unsigned int inlen, unsigned char* outbuf, unsigned int* outlen)
{
    int result = 0;

    if (m_pDecodeToPcm != nullptr)
        result = this->pcmEncodeObject(inbuf, inlen, outbuf, outlen);

    return result;
}

int G7ToPcm::pcmDecode(unsigned char * inbuf, unsigned int inlen, unsigned char * outbuf, unsigned int * outlen)
{
    int result = 0;

    if (m_pDecodeToPcm != nullptr)
        result = this->pcmDecodeObject(inbuf, inlen, outbuf, outlen);

    return result;
}

int G7ToPcm::pcmEncodeObject(unsigned char* inbuf, unsigned int inlen, unsigned char* outbuf, unsigned int* outlen)
{
    int g7bufferLen = 0;
    int pcmReadLength = 0;
    // pcm 已经读取数据长度
    int count = 0;
    // 已经读取g7 数据的长度
    int hasReadSize = 0;

    // 1.从缓存中读取数据 
    // 2.使用encode编码成pcm
    // 2.拷贝数据到out
    m_audioBuffer->wirteData(inbuf, inlen);

    while ((g7bufferLen = m_audioBuffer->getData(m_g7FrameBuffer, m_g7FrameBufferSize)) > 0) {
        if (g7bufferLen <= 0) {
            printf("%s:[%d] G711A -> PCM  no G711 data !\n", __FUNCTION__, __LINE__);
            return -1;
        }
        hasReadSize += g7bufferLen;

        //printf("g711: %s\n", m_g7FrameBuffer);
        memset(m_pcmTmpBuffer, 0, m_pcmTmpSize);
        if ((pcmReadLength = m_pDecodeToPcm->decode(m_pcmTmpBuffer, &m_pcmTmpSize, m_g7FrameBuffer, g7bufferLen)) < 0) {
            printf("%s:[%d] G711A -> PCM  failed buffer_len = %d !\n", __FUNCTION__, __LINE__, g7bufferLen);
            return -1;
        }
        //printf("pcm: %s\n", m_pcmTmpBuffer);
        printf("origin length:%d  outLen:%d\n", g7bufferLen, pcmReadLength);
        if (pcmReadLength > 0) {
            
            memcpy(outbuf + count, m_pcmTmpBuffer, pcmReadLength);
            count += pcmReadLength;

        }
    }

    *outlen = count;

    return *outlen;
}

int G7ToPcm::pcmDecodeObject(unsigned char *inbuf, unsigned int inlen, unsigned char *outbuf, unsigned int *outlen)
{
    int pcmTempBufferLen = 0;
    int g7ReadLength = 0;
    int count = 0;

    m_audioBuffer->wirteData(inbuf, inlen);

    while ((pcmTempBufferLen = m_audioBuffer->getData(m_pcmTmpBuffer, m_pcmTmpSize)) > 0) {
        if (pcmTempBufferLen <= 0) {
            printf("%s:[%d] pcm -> g7 data !\n", __FUNCTION__, __LINE__);
            return -1;
        }

        // 清除缓存数据
        memset(m_g7FrameBuffer, 0, m_g7FrameBufferSize);
        if ((g7ReadLength = m_pDecodeToPcm->encode(m_g7FrameBuffer, (unsigned int*)&m_g7FrameBufferSize, m_pcmTmpBuffer, pcmTempBufferLen)) < 0) {
            printf("%s:[%d] pcm -> g7  failed buffer_len = %d !\n", __FUNCTION__, __LINE__, pcmTempBufferLen);
            return -1;
        }
        //printf("origin length:%d  outLen:%d\n", m_pcmTmpSize, g7ReadLength);
        if (g7ReadLength > 0) {

            memcpy(outbuf + count, m_g7FrameBuffer, g7ReadLength);
            count += g7ReadLength;

        }
    }

    *outlen = count;

    return *outlen;
}


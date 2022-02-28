#include "AudioBuffer.h"
#include <iostream>

const int g_BufferLen = 1024 * 128;

AudioBuffer::AudioBuffer() 
{
    printf("%s %d\n", __FUNCTION__, __LINE__);
    m_data = new unsigned char[g_BufferLen];
    m_len = 0;
}

AudioBuffer::~AudioBuffer() 
{
    printf("%s %d\n", __FUNCTION__, __LINE__);
    delete []m_data;
    m_data = nullptr;
}

int AudioBuffer::wirteData(void *data, int len)
{
    if (g_BufferLen - m_len < len) {
        printf("audio buffer full m_len:%d len:%d\n", m_len, len);
        return -1;
    }

    if (len > 0) {
        memcpy(m_data + m_len, data, len);
        m_len += len;
        return len;
    }
    return 0;
}

// 获取走的数据清除
int AudioBuffer::getData(unsigned char *dest, int howYouWant) 
{
    if (m_len == 0 )
        return 0;
    if (m_len < howYouWant) {
        memcpy(dest, m_data, m_len);
        memset(m_data, 0, m_len);
        int result = m_len;
        m_len = 0;
        return result;

    }
    memcpy(dest, m_data, howYouWant);
    memmove(m_data, m_data + howYouWant, m_len - howYouWant);
    m_len -= howYouWant;
    return howYouWant;
}

unsigned char *AudioBuffer::getWritablePtr() 
{
    return m_data + m_len;
}

void AudioBuffer::updateDataLen(int len) 
{
    m_len += len;
}
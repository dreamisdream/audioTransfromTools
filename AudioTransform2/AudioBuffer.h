#pragma once

class AudioBuffer
{
public:
    AudioBuffer();
    ~AudioBuffer();
    
    int wirteData(void *data, int len);
    int getData(unsigned char *dest, int howYouWant);
    void updateDataLen(int len);
    unsigned char *getWritablePtr();
private:
    unsigned char *m_data;
    int m_len;
};


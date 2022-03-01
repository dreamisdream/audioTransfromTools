// testAudioDll.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>

#include "../../../AudioSerialize/include/common.h"
#include "../../../AudioSerialize/include/PcmSerializeApi.h"

using namespace std;

string pcmName("d://pcm_8000_16_1");
void pcm2G711a()
{
    InitParam initParam;
    initParam.u32AudioSamplerate = 8000;
    initParam.ucAudioChannel = 1;
    initParam.u32PCMBitSize = 16;
    initParam.ucAudioCodec = Law_ALaw;
    auto handle = pcmCodeInit(initParam);
    FILE *fpIn = nullptr;
    auto result = fopen_s(&fpIn,pcmName.append(".pcm").c_str(), "rb");
    if (result < 0) {
        printf("%s:[%d] open %s file failed\n", __FUNCTION__, __LINE__, pcmName.c_str());
        return;
    }
    FILE *fpOut = nullptr;
    result = fopen_s(&fpOut,pcmName.append(".g711a").c_str(), "wb");
    if (result < 0) {
        printf("%s:[%d] open %s file failed\n", __FUNCTION__, __LINE__, pcmName.c_str());
        return;
    }

    int gBytesRead = 0;
    int bG711ABufferSize = 500;
    int bAACBufferSize = 4 * bG711ABufferSize; //提供足够大的缓冲区
    unsigned char *pbG711ABuffer = new unsigned char[bG711ABufferSize];
    unsigned char *pbAACBuffer = new unsigned char[bAACBufferSize];

    unsigned int out_len = 0;
    int count = 0;
    while ((gBytesRead = fread(pbG711ABuffer, 1, bG711ABufferSize, fpIn)) > 0) {
        if (pcmDecode(handle, pbG711ABuffer, gBytesRead, pbAACBuffer, &out_len) > 0) {
            fwrite(pbAACBuffer, 1, out_len, fpOut);
            count += out_len;
            //printf("%s:[%d] pbAACBuffer(%d) inputLen:%d len=%d \n", __FUNCTION__, __LINE__,
            //    bAACBufferSize, gBytesRead, out_len);
        }
    }

    printf("success %d\n", count);
    delete[]pbG711ABuffer;
    delete[]pbAACBuffer;
    fclose(fpIn);
    fclose(fpOut);

    pcmRelease(handle);
}

void testPcm8To16(string filename)
{
    FILE *fpIn = nullptr;
    auto result = fopen_s(&fpIn, filename.c_str(), "rb");
    if (result < 0) {
        printf("%s:[%d] open %s file failed\n", __FUNCTION__, __LINE__, filename.c_str());
        return;
    }
    FILE *fpOut = nullptr;
    result = fopen_s(&fpOut, filename.append(".pcm16").c_str(), "wb");
    if (result < 0) {
        printf("%s:[%d] open %s file failed\n", __FUNCTION__, __LINE__, filename.c_str());
        return;
    }

    int gBytesRead = 0;
    int bG711ABufferSize = 500;
    int bAACBufferSize = 8 * bG711ABufferSize; //提供足够大的缓冲区
    char *pbG711ABuffer = new  char[bG711ABufferSize];
    char *pbAACBuffer = new  char[bAACBufferSize];

    int out_len = 0;
    int count = 0;
    while ((gBytesRead = fread(pbG711ABuffer, 1, bG711ABufferSize, fpIn)) > 0) {
        if (pcm8Topcm16(pbG711ABuffer, gBytesRead, pbAACBuffer, &out_len) > 0) {
            fwrite(pbAACBuffer, 1, out_len, fpOut);
            count += out_len;
            printf("%s:[%d] pbAACBuffer(%d) inputLen:%d len=%d \n", __FUNCTION__, __LINE__,
                bAACBufferSize, gBytesRead, out_len);
        }
    }

    printf("success %d\n", count);
    delete[]pbG711ABuffer;
    delete[]pbAACBuffer;
    fclose(fpIn);
    fclose(fpOut);
}

int main()
{
    //pcm2G711a();
    testPcm8To16("d://pcm_8000_8_1.pcm");
    std::cout << "Hello World!\n";
    getchar();
}


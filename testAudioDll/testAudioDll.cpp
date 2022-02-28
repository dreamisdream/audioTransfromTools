// testAudioDll.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>

#include "common.h"
#include "pcmEncode.h"

using namespace std;

#pragma comment(lib,"AudioTransform.lib")

string pcmName("d://16k_1_16");
void pcm2G711a()
{
    InitParam initParam;
    initParam.u32AudioSamplerate = 8000;
    initParam.ucAudioChannel = 1;
    initParam.u32PCMBitSize = 16;
    initParam.ucAudioCodec = Law_ALaw;
    auto handle = pcmEncodeInit(initParam);
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
    int bAACBufferSize = 8 * bG711ABufferSize; //提供足够大的缓冲区
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

int main()
{
    pcm2G711a();
    std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

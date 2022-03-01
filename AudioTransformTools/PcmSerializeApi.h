#pragma once
/*
    ����ӿ�
*/

#ifdef _WIN32
#define Audio_API  __declspec(dllexport)
#define Audio_APICALL  __stdcall
#else
#define Audio_API
#define Audio_APICALL 
#endif


#include "common.h"


// pcm���л����� ��ʼ��
Audio_API pcmEncodeHandle Audio_APICALL pcmCodeInit(InitParam initparam);

// other(g711a g711u g726) -> pcm 
Audio_API int Audio_APICALL pcmEncode(pcmEncodeHandle handle, unsigned char* inbuf, unsigned int inlen, unsigned char* outbuf, unsigned int* outlen);

//  pcm -> other(g711a g711u g726)
Audio_API int Audio_APICALL pcmDecode(pcmEncodeHandle handle, unsigned char* inbuf, unsigned int inlen, unsigned char* outbuf, unsigned int* outlen);

// release ���л�����
Audio_API void Audio_APICALL pcmRelease(pcmEncodeHandle handle);

Audio_API int Audio_APICALL pcm16Topcm8(char* inBuffer, int inLen, char*outBuffer, int *outLen);

Audio_API int Audio_APICALL pcm8Topcm16(char* inBuffer, int inLen, char*outBuffer, int *outLen);


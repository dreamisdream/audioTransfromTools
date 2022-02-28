#pragma once

#ifdef _WIN32
#define Audio_API  __declspec(dllexport)
#define Audio_APICALL  __stdcall
#else
#define Audio_API
#define Audio_APICALL 
#endif
/*
    对外接口
*/
#include "common.h"

Audio_API pcmEncodeHandle Audio_APICALL pcmEncodeInit(InitParam initparam);

Audio_API int Audio_APICALL pcmEncode(pcmEncodeHandle handle, unsigned char* inbuf, unsigned int inlen, unsigned char* outbuf, unsigned int* outlen);

Audio_API int Audio_APICALL pcmDecode(pcmEncodeHandle handle, unsigned char* inbuf, unsigned int inlen, unsigned char* outbuf, unsigned int* outlen);

Audio_API void Audio_APICALL pcmRelease(pcmEncodeHandle handle);
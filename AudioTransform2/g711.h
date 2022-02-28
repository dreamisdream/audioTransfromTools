#pragma once

enum g711type { G711ULAW, G711ALAW };

/**
 * @brief pcm data encode to g711 data
 *
 *  user should be responsible for pCodecbit memmory
 *
 * @param pCodecBits store g711 encoded data
 * @param pBuffer pcm raw data
 * @param BufferSize pcm data len
 * @param type g711 data type
 * @return int encode data length
 */
 int g711EnCode(char *pCodecBits, char *pBuffer,int BufferSize,int gtype);

/**
 * @brief g711 data decode to pcm data
 *
 * user should be responsible for pRawData memmory
 *
 * @param pRawData store uncoded pcm data
 * @param pBuffer g711 encoded data
 * @param BufferSize g711 data len
 * @param type g711 data type
 * @return int pcm data len
 */
int  g711Decode(char *pRawData, char *pBuffer,
                                               int BufferSize, int gtype);

/**
 * @brief g711 u-law data and a-law data convert
 *
 * @param alawdata g711 a-law data
 * @param ulawdata g711 u-lwa data
 * @param datasize input data length
 * @param type target g711 data type
 * @return int sucess:1; failed:0
 */
int g711TypeChange(unsigned char *alawdata,unsigned char *ulawdata,int datasize, int gtype);


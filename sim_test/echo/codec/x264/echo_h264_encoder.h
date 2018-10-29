/*-
* Copyright (c) 2017-2018 wenba, Inc.
*	All rights reserved.
*
* See the file LICENSE for redistribution information.
*/

#ifndef __h264_encoder_h__
#define __h264_encoder_h__

#ifdef _MSC_VER	/* MSVC */
#pragma warning(disable: 4996)
#define snprintf	_snprintf
#define vsnprintf	_vsnprintf
#define strcasecmp	stricmp
#define strncasecmp strnicmp
#endif

#include <stdint.h>

extern "C"
{
#include "x264.h"
#include "libavcodec/avcodec.h"
#include "libavutil/avutil.h"
#include "libswscale/swscale.h"
#include "libavutil/pixfmt.h"
};

#include "codec_common.h"

/*h264��������֧���Զ����ű���,֧�ֶ�̬�޸����ʣ���̬�޸ķֱ��ʡ�Ϊ�˸��õĺ�razor������ϴ��䣬�����������ó�inter-refreshģʽ*/
class H264Encoder : public VideoEncoder
{
public:
	H264Encoder();
	~H264Encoder();

	bool encode(uint8_t *in, int in_size, enum PixelFormat pix_fmt, uint8_t *out, int *out_size, int *frame_type, bool request_keyframe = false);

	int get_bitrate() const;

	int get_codec_width() const;
	int get_codec_height() const;

protected:
	void config_param();
	void reconfig_encoder(uint32_t bitrate);
	bool open_encoder();
	void close_encoder();

private:
	//RGB -> YUVת������
	SwsContext*		sws_context_;
	//X264�������
	x264_picture_t	pic_out_;
	x264_picture_t	en_picture_;
	x264_t *		en_h_;
	x264_param_t	en_param_;

};

#endif



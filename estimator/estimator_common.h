#ifndef __estimator_common_h_
#define __estimator_common_h_
#include <stdint.h>
#include "cf_stream.h"

enum {
	kBwNormal = 0,
	kBwUnderusing = 1,
	kBwOverusing = 2,
};

enum {
	kRcHold, 
	kRcIncrease, 
	kRcDecrease
};

enum { 
	kRcNearMax, 
	kRcAboveMax, 
	kRcMaxUnknown 
};

typedef struct
{
	int			state;
	uint32_t	incoming_bitrate;
	double		noise_var;
}rate_control_input_t;

#define DEFAULT_RTT 200


typedef struct
{
	int64_t			create_ts;			/*����ʱ���*/
	int64_t			arrival_ts;			/*����ʱ���*/
	int64_t			send_ts;			/*����ʱ���*/

	uint16_t		sequence_number;	/*����ͨ���ı������*/
	size_t			payload_size;		/*�����ݴ�С*/
}packet_feedback_t;

#define init_packet_feedback(p)	\
	do{							\
		(p).create_ts = -1;		\
		(p).arrival_ts = -1;		\
		(p).send_ts = -1;		\
		(p).sequence_number = 0;\
		(p).payload_size = 0;	\
		} while (0)


typedef struct
{
	uint16_t		seq;
	int64_t			ts;
}feedback_sample_t;

#define MAX_FEELBACK_COUNT 128
typedef struct
{
	uint16_t				base_seq;
	int64_t					min_ts;

	uint8_t				samples_num;
	feedback_sample_t	samples[MAX_FEELBACK_COUNT];
}feedback_msg_t;

void	feedback_msg_encode(bin_stream_t* strm, feedback_msg_t* msg);
void	feedback_msg_decode(bin_stream_t* strm, feedback_msg_t* msg);

#endif



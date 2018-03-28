#ifndef __estimator_common_h_
#define __estimator_common_h_
#include <stdint.h>

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

#endif




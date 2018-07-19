#ifndef __bbr_receive_controller_h_
#define __bbr_receive_controller_h_

#include "cf_platform.h"
#include "cc_loss_stat.h"
#include "razor_api.h"
#include "cf_stream.h"

typedef struct
{
	cc_loss_statistics_t		loss_stat;

	/*��Ϣ��������*/
	void*						handler;
	send_feedback_func			send_cb;

	/*�հ���Ϣ*/
	int64_t						feedback_ts;		/*feedbakʱ�����UNIX����ʱ�䣬����Ϊ��λ*/

	int64_t						base_seq;			/*���ڷ�������ʼID*/
	int64_t						min_seq;			/*�����б�������СID*/
	int64_t						max_seq;			/*����������ID*/

	size_t						array_size;
	int64_t*					array;				/*�洢���Ǳ��ĵ����ʱ�䣬���δ�յ�������ģ���-1*/

	cf_unwrapper_t				unwrapper;			/*ID�ָ���*/
	bin_stream_t				strm;
}bbr_receiver_t;

bbr_receiver_t*					bbr_receive_create(void* handler, send_feedback_func cb);
void							bbr_receive_destroy(bbr_receiver_t* cc);

void							bbr_receive_check_acked(bbr_receiver_t* cc);
void							bbr_receive_on_received(bbr_receiver_t* cc, uint16_t seq, uint32_t timestamp, size_t size, int remb);

/*��ʱ����ʵ�ֵĽӿڣ���ΪBBRֻ��Ҫ�������ն˱�����Ϣ�Ϳ��Խ���ӵ������*/
void							bbr_receive_update_rtt(bbr_receiver_t* cc, int32_t rtt);
void							bbr_receive_set_min_bitrate(bbr_receiver_t* cc, int min_bitrate);
void							bbr_receive_set_max_bitrate(bbr_receiver_t* cc, int max_bitrate);

#endif




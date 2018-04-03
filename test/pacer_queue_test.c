#include "pacer_queue.h"
#include "common_test.h"

#define k_packet_size 1000
#define k_packet_num 5

static void test_pacer_queue_push()
{
	pacer_queue_t que;
	packet_event_t packet;
	int i;
	int64_t now_ts, oldest_ts;

	pacer_queue_init(&que);

	oldest_ts = now_ts = GET_SYS_MS();

	for (i = 0; i < k_packet_num; i++){
		packet.retrans = 0;
		packet.que_ts = now_ts;
		packet.sent = 0;
		packet.seq = i;
		packet.size = k_packet_size;

		pacer_queue_push(&que, &packet);

		now_ts += 100;
	}

	EXPECT_EQ(oldest_ts, pacer_queue_oldest(&que));
	EXPECT_EQ(k_packet_num * k_packet_size, pacer_queue_bytes(&que));
	EXPECT_EQ(80, pacer_queue_target_bitrate_kbps(&que, now_ts));

	pacer_queue_destroy(&que);
}

static void test_pacer_queue_sent()
{
	pacer_queue_t que;
	packet_event_t packet;
	int i;
	int64_t now_ts, oldest_ts;

	pacer_queue_init(&que);

	oldest_ts = now_ts = GET_SYS_MS();

	for (i = 0; i < k_packet_num; i++){
		packet.retrans = 0;
		packet.que_ts = now_ts;
		packet.sent = 0;
		packet.seq = i;
		packet.size = k_packet_size;

		pacer_queue_push(&que, &packet);

		now_ts += 100;
	}

	/*ȷ�Ϸ����м����������*/
	pacer_queue_sent(&que, 1);
	pacer_queue_sent(&que, 2);
	EXPECT_EQ(oldest_ts, pacer_queue_oldest(&que));
	EXPECT_EQ((k_packet_num - 2) * k_packet_size, pacer_queue_bytes(&que));
	EXPECT_EQ(48, pacer_queue_target_bitrate_kbps(&que, now_ts));
	assert(pacer_queue_empty(&que) != 0);

	/*ȷ�Ϸ����˵�һ����,����������ǰ�ƶ�������Ĵ���ص���ʼ�������ٶ�*/
	pacer_queue_sent(&que, 0);

	EXPECT_EQ(oldest_ts + 300, pacer_queue_oldest(&que));
	EXPECT_EQ((k_packet_num - 3) * k_packet_size, pacer_queue_bytes(&que));
	EXPECT_EQ(80, pacer_queue_target_bitrate_kbps(&que, now_ts));
	assert(pacer_queue_empty(&que) != 0);

	/*ȷ�Ϸ��������������������Ϊ��*/
	pacer_queue_sent(&que, 3);
	pacer_queue_sent(&que, 4);

	EXPECT_EQ(-1, pacer_queue_oldest(&que));
	EXPECT_EQ(0, pacer_queue_bytes(&que));
	EXPECT_EQ(0, pacer_queue_target_bitrate_kbps(&que, now_ts));
	assert(pacer_queue_empty(&que) == 0);

	pacer_queue_destroy(&que);
}

void test_pacer_queue_front()
{
	pacer_queue_t que;
	packet_event_t packet, *p;
	int i;
	int64_t now_ts, oldest_ts;

	pacer_queue_init(&que);

	oldest_ts = now_ts = GET_SYS_MS();

	for (i = 0; i < k_packet_num; i++){
		packet.retrans = 0;
		packet.que_ts = now_ts;
		packet.sent = 0;
		packet.seq = i;
		packet.size = k_packet_size;

		pacer_queue_push(&que, &packet);

		now_ts += 100;
	}

	for (i = 0; i < k_packet_num; i++){
		p = pacer_queue_front(&que);
		EXPECT_EQ(i, p->seq);

		pacer_queue_sent(&que, i);
	}

	assert(pacer_queue_empty(&que) == 0);

	pacer_queue_destroy(&que);
}

void test_pacer_queue()
{
	test_pacer_queue_push();
	test_pacer_queue_sent();

	test_pacer_queue_front();
}







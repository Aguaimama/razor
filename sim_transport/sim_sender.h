struct __sim_sender
{
	int							actived;
	uint32_t					base_packet_id;			/*���ܶ˱����Ѿ����յ������������ID*/

	uint32_t					packet_id_seed;
	uint32_t					frame_id_seed;
	uint32_t					transport_seq_seed;

	int64_t						first_ts;			/*��һ֡��ʼʱ���*/

	skiplist_t*					cache;				/*���ʹ���*/

	razor_sender_t*				cc;					/*ӵ�����ƶ���*/

	sim_session_t*				s;
};



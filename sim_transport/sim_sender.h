struct __sim_sender
{
	int							state;
	uint32_t					base;				/*���ܶ˱�����Ѿ������seq*/
	uint32_t					base_ts;			/*ȷ���յ���֡��ʱ���*/

	uint32_t					frame_ts;			/*��ǰ���͵�ts���Ǹ����ֵ*/
	uint64_t					start_ts;			/*��һ֡�ľ���ʱ���*/

	skiplist_t*					cache;				/*���ʹ���*/

	uint64_t					tick_ts;
	uint64_t					rtt_ts;

	int							actived;

	razor_sender_t*				cc;					/*ӵ�����ƶ���*/
};




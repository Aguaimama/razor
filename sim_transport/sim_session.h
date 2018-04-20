
struct __sim_session
{
	su_socket		s;
	su_addr			peer;

	uint32_t		cid;
	uint32_t		uid;				/*�����û�ID*/

	uint32_t		rtt;				/*rttֵ*/
	uint32_t		rtt_var;			/*rtt�������ֵ*/

	int				state;				/*״̬*/
	volatile int	run;				/*run�̱߳�ʾ */
	su_mutex		mutex;				/*������*/

	sim_sender_t*	sender;				/*��Ƶ������*/
	sim_receiver_t*	receiver;			/*��Ƶ������*/

	int				resend;				/*�ط�����*/
	uint64_t		commad_ts;			/*����ʱ���*/
	uint64_t		stat_ts;

	uint32_t		rbandwidth;			/*���մ���*/
	uint32_t		sbandwidth;			/*���ʹ���*/
	uint32_t		rcount;
	uint32_t		scount;

	bin_stream_t	sstrm;

	su_thread		thr;				/*�߳�ID*/

	vch_notify_fn	notify_cb;
	vch_adjust_fn	adjust_cb;
	vch_state_fn	state_cb;
};


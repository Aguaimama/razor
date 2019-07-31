
AllDirs := common/platform/posix bbr cc common estimator pacing sim_transport 
Sources := $(foreach n,$(AllDirs) , $(wildcard $(n)/*.c))
Objs := $(patsubst %.c,%.o, $(Sources))
Deps := $(patsubst %.c,%.d, $(Sources)) 

StaticLib := librazor.a

CC = gcc
CXX = g++
RM = rm -f
#CFLAG = -g -O2 -fPIC -Wall
CFLAG = -Wall -std=c99 -g -O2 -fPIC
CPPFLAGS = $(foreach n,$(AllDirs) , -I$(n)) 
CPPFLAGS+=-Isim_test/win_log/
LDFLAGS += -lpthread

SenderApp = sim_sender_test
ReceiverApp = sim_receiver_test
RelayApp = sim_relay

#以下是编译test目录下的文件
RazorTest = razortest
test_c_file = $(wildcard ./test/*.c)
test_o_file	= $(patsubst %.c,%.o,$(test_c_file))
test_d_file	= $(patsubst %.c,%.d,$(test_c_file))

all : $(SenderApp) $(ReceiverApp) $(RazorTest)
$(RazorTest):  $(Objs)	$(test_o_file)
	$(CC) $(Objs) $(test_o_file) -o $(RazorTest) $(CPPFLAGS) $(LDFLAGS) -lm

$(SenderApp):$(Objs)
	$(CXX) sim_test/sim_sender/sim_sender_test.cpp sim_test/win_log/audio_log.cpp $(Objs) -o $(SenderApp) $(CPPFLAGS) $(LDFLAGS)

$(ReceiverApp):$(Objs)
	$(CXX) sim_test/sim_receiver/sim_receiver_test.cpp sim_test/win_log/audio_log.cpp $(Objs) -o $(ReceiverApp) $(CPPFLAGS) $(LDFLAGS)

$(StaticLib): $(Objs)
	ar rcs $@ $^
	
%.d : %.c
	$(CC) -MT"$(<:.c=.o) $@" -MM $(CFLAG) $(CPPFLAGS) $< > $@
	

	
sinclude $(Deps)	

.PHONY : clean

clean: 
	$(RM) $(Objs) $(Deps) $(SenderApp) $(ReceiverApp) $(test_o_file) $(test_d_file) $(RazorTest) 
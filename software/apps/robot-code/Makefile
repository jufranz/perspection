CONTIKI = ../../contiki
CONTIKI_PROJECT = controller headset 

TARGETDIRS += ../../platform

all: $(CONTIKI_PROJECT)


CONTIKI_WITH_RIME = 1
include $(CONTIKI)/Makefile.include
LDFLAGS+=-lm
CFLAGS+=-lm
TARGET_LIBFILES+=-lm

TARGET:= libldds.a
SOURCE:= $(wildcard *.cc)
OBJECT:= $(patsubst %.cc, %.o, ${SOURCE})
CFLAGS:= -c
CC:= g++
AR:= ar

all: ${TARGET}
	ls -lh $+
${TARGET}: ${OBJECT}
	$(AR) cr $@ $+
%.o:%.cc
	$(CC) $< -c
clean:
	rm *.o *.a -rf

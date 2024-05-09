LIB:= build/libldds.a
LIBSRC:= $(wildcard ../*.cc)
LIBOBJ:= $(patsubst %.cc, build/.d/%.o, ${LIBSRC})
CFLAGS:= -I.. #-lpthread #-O2 
CC:= g++
AR:= ar

all: adc.exe
	ls

${LIB}:${LIBOBJ}
	${AR} cr $@ $+
build/.d/%.o: %.cc
	$(shell mkdir build/.d/ -p)
	${CC} -g -c $< -o $@

hex.exe: hex_demo.cxx 
	${CC} $+ -o $@ ${CFLAGS}
	mv $@ build
rtti.exe: rtti_demo.cxx 
	${CC} $+ -o $@ ${CFLAGS}
	mv $@ build
mutex.exe: mutex_demo.cxx 
	${CC} $+ -o $@ ${CFLAGS}
	mv $@ build
ldds.exe: ldds_demo.cxx ${LIB}
	${CC} $+ -o $@ ${CFLAGS}
	mv $@ build
platform.exe: platform_demo.cxx ${LIB}
	${CC} $+ -o $@ ${CFLAGS}
	mv $@ build
bus.exe: bus_demo.cxx ${LIB}
	${CC} $+ -o $@ ${CFLAGS}
	mv $@ build
node.exe: node_demo.cxx ${LIB}
	${CC} $+ -o $@ ${CFLAGS}
	mv $@ build
msg.exe: msg_demo.cxx ${LIB}
	${CC} $+ -o $@ ${CFLAGS}
	mv $@ build
payload.exe: payload_demo.cxx
	${CC} $+ -o $@ ${CFLAGS}
	mv $@ build
duration.exe: duration_demo.cxx 
	${CC} $+ -o $@ ${CFLAGS}
	mv $@ build
queue.exe: syncq_demo.cxx
	${CC} $+ -o $@ ${CFLAGS}
	mv $@ build
map.exe: syncm_demo.cxx
	${CC} $+ -o $@ ${CFLAGS}
	mv $@ build
time.exe: time_demo.cxx
	${CC} $+ -o $@ ${CFLAGS}
	mv $@ build
adc.exe: adc_demo.cxx ${LIB}
	${CC} $+ -o $@ ${CFLAGS}
	mv $@ build

cloc:
	cloc ..

clean:
	rm ${LIB} ${LIBOBJ} *.a *.o *.exe -rf build/* 

LIBS = -ldl	# On Linux
#LIBS = -lc	# On BSD
LOCAL_CPPFLAGS += -I.
AM_V_P := :

all: demo lttng-ust-provider-ust-tests-demo.so lttng-ust-provider-ust-tests-demo3.so

tp.o: tp.c ust_tests_demo.h
	@if $(AM_V_P); then set -x; else echo "  CC       $@"; fi; \
		$(CC) $(CPPFLAGS) $(LOCAL_CPPFLAGS) $(AM_CFLAGS) $(AM_CPPFLAGS) \
		$(CFLAGS) -fpic -c -o $@ $<

tp2.o: tp2.c ust_tests_demo2.h
	@if $(AM_V_P); then set -x; else echo "  CC       $@"; fi; \
		$(CC) $(CPPFLAGS) $(LOCAL_CPPFLAGS) $(AM_CFLAGS) $(AM_CPPFLAGS) \
		$(CFLAGS) -fpic -c -o $@ $<

lttng-ust-provider-ust-tests-demo.so: tp.o tp2.o
	@if $(AM_V_P); then set -x; else echo "  CCLD     $@"; fi; \
		$(CC) -Wl,--no-as-needed -o $@ $(LDFLAGS) $(AM_CFLAGS) \
		$(AM_LDFLAGS) $(CFLAGS) -shared -fpic tp.o tp2.o $(LIBS) -llttng-ust

tp3.o: tp3.c ust_tests_demo3.h
	@if $(AM_V_P); then set -x; else echo "  CC       $@"; fi; \
		$(CC) $(CPPFLAGS) $(LOCAL_CPPFLAGS) $(AM_CFLAGS) $(AM_CPPFLAGS) \
		$(CFLAGS) -fpic -c -o $@ $<

lttng-ust-provider-ust-tests-demo3.so: tp3.o
	@if $(AM_V_P); then set -x; else echo "  CCLD     $@"; fi; \
		$(CC) -Wl,--no-as-needed -o $@ $(LDFLAGS) $(AM_CFLAGS) \
		$(AM_LDFLAGS) $(CFLAGS) -shared -fpic tp3.o $(LIBS) -llttng-ust

demo.o: demo.c
	@if $(AM_V_P); then set -x; else echo "  CC       $@"; fi; \
		$(CC) $(CPPFLAGS) $(LOCAL_CPPFLAGS) $(AM_CFLAGS) $(AM_CPPFLAGS) \
		$(CFLAGS) -c -o $@ $<

demo: demo.o
	@if $(AM_V_P); then set -x; else echo "  CCLD     $@"; fi; \
		$(CC) $(LDFLAGS) $(AM_CFLAGS) $(AM_LDFLAGS) $(CFLAGS) \
		-o $@ demo.o $(LIBS)

.PHONY: clean
clean:
	rm -f *.o *.so demo


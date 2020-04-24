ifndef TUXDIR
$(error TUXDIR is not set)
endif

export PATH:=$(TUXDIR)/bin:$(PATH)
export LD_LIBRARY_PATH:=$(TUXDIR)/lib:$(LD_LIBRARY_PATH)
export TUXCONFIG:=$(CURDIR)/tuxconfig

default: server tuxconfig
	strace -T -ttt -f -oservers.txt tmboot -y &
	sleep 20
	strace -T -ttt -f -otmshutdown.txt tmshutdown -i 3
	tmshutdown -k KILL -y
	tmipcrm -y

ubbconfig: ubbconfig.in
	cat $< \
          | sed s:@TUXDIR@:$(TUXDIR):g \
          | sed s:@UNAME@:`uname -n`:g \
          | sed s:@CURDIR@:$(CURDIR):g > $@

tuxconfig: ubbconfig
	tmloadcf -y $<

server: server.c
	buildserver -o $@ -f $< -s TOUPPER -v

clean:
	-tmipcrm -y
	-rm -f *.o ubbconfig tuxconfig server ULOG.* access.* stderr stdout

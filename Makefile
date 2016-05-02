PRG=gnu.exe
OSTYPE := $(shell uname)
#ifeq ($(OSTYPE),Linux)
ifeq ($(OSTYPE),$(filter $(OSTYPE),Linux Darwin))
CYGWIN=
else
CYGWIN=-Wl,--enable-auto-import
endif

VALGRIND_OPTIONS=-q --leak-check=full
DIFF_OPTIONS_ENC=--strip-trailing-cr
DIFF_OPTIONS_DEC=

#with arguments
#GNU
gcc0:
	echo Compile with C and C++
	g++ -c uucode.cpp -Wall -Wextra -ansi -pedantic
	g++ -c driver-args.cpp -Wall -Wextra  -ansi -pedantic
	g++ -o $(PRG) uucode.o driver-args.o 

0 1:
	echo "running test$@"
	@echo "should run in less than 500 ms"
	./$(PRG) 1 input-$@.txt input-remote-$@.txt >studentout$@
	diff input-$@.uue studentout$@ $(DIFF_OPTIONS_ENC) >difference$@ 2>difference$@
2:
	echo "running test$@"
	@echo "should run in less than 500 ms"
	./$(PRG) 2 icon1.uue >/dev/null
	diff icon-1-remote.ico icon1.ico $(DIFF_OPTIONS_DEC) > difference$@ 2>difference$@
mem0:
	echo "running memory test $@"
	@echo "should run in less than 5000 ms"
	valgrind $(VALGRIND_OPTIONS) ./$(PRG) 1 input-$@.txt input-remote-$@.txt 1>/dev/null 2>difference$@
	@echo "lines after this are memory errors"; cat difference$@
	
#clean
clean:
	rm -f *.o *.obj *.exe


######################################################
# Compiler                                           #
######################################################
CC = gcc

######################################################
# Target                                             #
######################################################
TARGET = build/simulator.exe

######################################################
# Option                                             #
######################################################
CFLAGS = -Wall -Wextra

######################################################
# Source Files                                       #
######################################################
SRCS = \
    src/bsw/bbsw2ios/bbsw2ios.c \
    src/bsw/bcyclemng/bcyclemng.c \
    src/bsw/bios2bsw/bios2bsw.c \
    src/bsw/bschedule/bschedule.c \
    src/sac/sacaramng/sacaramng.c \
    src/sac/sacelcrt/sacelcrt.c \
    src/sac/sbrkcrt/sbrkcrt.c \
    src/sac/sclthcrt/sclthcrt.c \
    src/sac/sgearcrt/sgearcrt.c \
    src/sac/sigswcrt/sigswcrt.c \
    src/sac/avehsts/avehsts.c \
    src/apl/pprtct/pprtct.c \
    src/apl/pperm/pperm.c \
    src/apl/psimbrdg/psimbrdg.c \
    src/apl/pvehstsjdg/pvehstsjdg.c \
    src/apl/pwarn/pwarn.c \
    env/swift_env/swift_env.c \
    debug/kensa_1/dmy_def.c \
    debug/kensa_1/main.c \
    debug/log/print_log/print_log.c

######################################################
# Object Files                                       #
######################################################
OBJS = \
    build/bbsw2ios.o \
    build/bcyclemng.o \
    build/bios2bsw.o \
    build/bschedule.o \
    build/sacaramng.o \
    build/sacelcrt.o \
    build/sbrkcrt.o \
    build/sclthcrt.o \
    build/sgearcrt.o \
    build/sigswcrt.o \
    build/avehsts.o \
    build/pprtct.o \
    build/pperm.o \
    build/psimbrdg.o \
    build/pvehstsjdg.o \
    build/pwarn.o \
    build/swift_env.o \
    build/dmy_def.o \
    build/main.o \
    build/print_log.o

######################################################
# Default Target                                     #
######################################################
all: build
	if exist build\error.log del build\error.log
	$(MAKE) $(TARGET)

######################################################
# Build Directory                                    #
######################################################
build:
	if not exist build mkdir build

######################################################
# Link                                               #
######################################################
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) 2>> build/error.log

######################################################
# Compile                                            #
######################################################
build/bbsw2ios.o: src/bsw/bbsw2ios/bbsw2ios.c
	$(CC) $(CFLAGS) -c $< -o $@ 2>> build/error.log

build/bcyclemng.o: src/bsw/bcyclemng/bcyclemng.c
	$(CC) $(CFLAGS) -c $< -o $@ 2>> build/error.log

build/bios2bsw.o: src/bsw/bios2bsw/bios2bsw.c
	$(CC) $(CFLAGS) -c $< -o $@ 2>> build/error.log

build/bschedule.o: src/bsw/bschedule/bschedule.c
	$(CC) $(CFLAGS) -c $< -o $@ 2>> build/error.log

build/sacaramng.o: src/sac/sacaramng/sacaramng.c
	$(CC) $(CFLAGS) -c $< -o $@ 2>> build/error.log

build/sacelcrt.o: src/sac/sacelcrt/sacelcrt.c
	$(CC) $(CFLAGS) -c $< -o $@ 2>> build/error.log

build/sbrkcrt.o: src/sac/sbrkcrt/sbrkcrt.c
	$(CC) $(CFLAGS) -c $< -o $@ 2>> build/error.log

build/sclthcrt.o: src/sac/sclthcrt/sclthcrt.c
	$(CC) $(CFLAGS) -c $< -o $@ 2>> build/error.log

build/sgearcrt.o: src/sac/sgearcrt/sgearcrt.c
	$(CC) $(CFLAGS) -c $< -o $@ 2>> build/error.log

build/sigswcrt.o: src/sac/sigswcrt/sigswcrt.c
	$(CC) $(CFLAGS) -c $< -o $@ 2>> build/error.log

build/avehsts.o: src/sac/avehsts/avehsts.c
	$(CC) $(CFLAGS) -c $< -o $@ 2>> build/error.log

build/pprtct.o: src/apl/pprtct/pprtct.c
	$(CC) $(CFLAGS) -c $< -o $@ 2>> build/error.log

build/pperm.o: src/apl/pperm/pperm.c
	$(CC) $(CFLAGS) -c $< -o $@ 2>> build/error.log

build/psimbrdg.o: src/apl/psimbrdg/psimbrdg.c
	$(CC) $(CFLAGS) -c $< -o $@ 2>> build/error.log

build/pvehstsjdg.o: src/apl/pvehstsjdg/pvehstsjdg.c
	$(CC) $(CFLAGS) -c $< -o $@ 2>> build/error.log

build/pwarn.o: src/apl/pwarn/pwarn.c
	$(CC) $(CFLAGS) -c $< -o $@ 2>> build/error.log

build/swift_env.o: env/swift_env/swift_env.c
	$(CC) $(CFLAGS) -c $< -o $@ 2>> build/error.log

build/dmy_def.o: debug/kensa_1/dmy_def.c
	$(CC) $(CFLAGS) -c $< -o $@ 2>> build/error.log

build/main.o: debug/kensa_1/main.c
	$(CC) $(CFLAGS) -c $< -o $@ 2>> build/error.log

build/print_log.o: debug/log/print_log/print_log.c
	$(CC) $(CFLAGS) -c $< -o $@ 2>> build/error.log

######################################################
# Clean                                              #
######################################################
clean:
	if exist build rmdir /S /Q build

######################################################
# Rebuild                                            #
######################################################
rebuild: clean all
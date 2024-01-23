
CC = gcc

c_sources = \
	common.c \
	dyn_cross.c \
	encode.c \
	audio_read.c \
	lfe.c \
	lingual.c \
	musicin.c \
	predisto.c \
	psycho_1.c \
	psycho_2.c \
	alloc_tables.c \
	crc.c \
	subband.c \
	config.c \
	fft.c 


OBJ = $(c_sources:.c=.o)

#Uncomment this if you want to do some profiling
#PG = -g -pg

# Optimize flag. 3 is about as high as you can sanely go with GCC3.2.
OPTIM = -O1 -g -Wpedantic -Wall -std=c99

# These flags are pretty much mandatory
REQUIRED = -DINLINE=inline

#pick your architecture
ARCH = -march=native
#ARCH = -march=athlon-tbird
#Possible x86 architectures
#gcc3.2 => i386, i486, i586, i686, pentium, pentium-mmx
#          pentiumpro, pentium2, pentium3, pentium4, k6, k6-2, k6-3,
#          athlon, athlon-tbird, athlon-4, athlon-xp and athlon-mp.

#TWEAK the hell out of the compile. Some of these are real dodgy
#TWEAKS = -finline-functions -fexpensive-optimizations -ffast-math -malign-double \
#	-mfancy-math-387 -funroll-loops -funroll-all-loops -pipe \
#	-fschedule-insns2 -fno-strength-reduce

#Set a stack of warnings to overcome my atrocious coding style . MFC.
WARNINGS = -Wall -Wno-unused-but-set-variable
WARNINGS2 = -Wstrict-prototypes -Wmissing-prototypes -Wunused -Wunused-function -Wunused-label -Wunused-parameter -Wunused-variable -Wunused-value -Wredundant-decls

CC_SWITCHES = $(OPTIM) $(REQUIRED) $(ARCH) $(PG) $(TWEAKS) $(WARNINGS) -DUNIX -DNEWSUBBAND -DNEWP1TABLES

PGM = mctoolame

LIBS =  -lm

#nick burch's OS/2 fix  gagravarr@SoftHome.net
UNAME = $(shell uname)
ifeq ($(UNAME),OS/2)
   SHELL=sh     
   PGM = toolame.exe
   PG = -Zcrtdll -Zexe
   LIBS =
endif

%.o: %.c Makefile
	$(CC) $(CC_SWITCHES) -c $< -o $@

$(PGM):	$(OBJ) Makefile
	$(CC) $(PG) -o $(PGM) $(OBJ) $(LIBS)

clean:
	-rm $(OBJ) $(DEP)

megaclean:
	-rm $(OBJ) $(DEP) $(PGM) \#*\# *~

distclean:
	-rm *.o $(PGM) \#* *~ gmon.out gprof* core *shit* *.wav *.mp2 *.c.* *.mp2.* *.da *.h.* *.d *.mp3 *.pcm *.wav logfile

tags: TAGS

TAGS: ${c_sources}
	etags -T ${c_sources}


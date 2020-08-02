# Build mode
# 0: development (max safety, no optimisation)
# 1: release (min safety, optimisation)
# 2: fast and furious (no safety, optimisation)
BUILD_MODE?=0

all: pbmake_wget main
	
# Automatic installation of the repository PBMake in the parent folder
pbmake_wget:
	if [ ! -d ../PBMake ]; then wget https://github.com/BayashiPascal/PBMake/archive/master.zip; unzip master.zip; rm -f master.zip; sed -i '' 's@ROOT_DIR=.*@ROOT_DIR='"`pwd | gawk -F/ 'NF{NF-=1};1' | sed -e 's@ @/@g'`"'@' PBMake-master/Makefile.inc; mv PBMake-master ../PBMake; fi

# Check code style
style:
	cbo *.h *.c

# Makefile definitions
MAKEFILE_INC=../PBMake/Makefile.inc
include $(MAKEFILE_INC)

# Rules to make the executable
repo=buzzy
$($(repo)_EXENAME): \
		$($(repo)_EXENAME).o \
		$($(repo)_EXE_DEP) \
		$($(repo)_DEP)
	$(COMPILER) `echo "$($(repo)_EXE_DEP) $($(repo)_EXENAME).o" | tr ' ' '\n' | sort -u` $(LINK_ARG) $($(repo)_LINK_ARG) -o $($(repo)_EXENAME) 
	
$($(repo)_EXENAME).o: \
		$($(repo)_DIR)/$($(repo)_EXENAME).c \
		$($(repo)_INC_H_EXE) \
		$($(repo)_EXE_DEP)
	$(COMPILER) $(BUILD_ARG) $($(repo)_BUILD_ARG) `echo "$($(repo)_INC_DIR)" | tr ' ' '\n' | sort -u` -c $($(repo)_DIR)/$($(repo)_EXENAME).c
	
install_libao:
	cd ~/ ; wget http://downloads.xiph.org/releases/ao/libao-1.2.0.tar.gz ; tar xvf libao-1.2.0.tar.gz ; cd libao-1.2.0 ; ./configure ; make ; sudo make install; sudo cp /usr/lib/x86_64-linux-gnu/ao/plugins-4/* /usr/local/lib/ao/plugins-4/

install_sox:
	sudo apt install sox

wav2raw:
	echo "sox test.wav --bits 16 --rate 44100 --channels 2  test.raw"

reset_device:
	pulseaudio -k && sudo alsa force-reload

edit_libao_conf:
	sudo gedit /etc/libao.conf


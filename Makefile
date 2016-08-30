TITLE_ID 	= 	VITAUDIO1
TARGET   	= 	VitaAudio
TITLE		= 	vitaAudio Example
OBJS     	= 	src/main.o resources/sprites/img_bg.o resources/sprites/img_btn.o resources/sprites/img_btnp.o \
				\
				src/vitaAudio/ogg/util/memory.o 			\
				src/vitaAudio/ogg/util/float-to-int16.o 	\
				src/vitaAudio/ogg/util/decode-frame.o 		\
				src/vitaAudio/ogg/decode/stb_vorbis.o 		\
				src/vitaAudio/ogg/decode/setup.o 			\
				src/vitaAudio/ogg/decode/seek.o 			\
				src/vitaAudio/ogg/decode/packet.o 			\
				src/vitaAudio/ogg/decode/io.o 				\
				src/vitaAudio/ogg/decode/decode.o 			\
				src/vitaAudio/ogg/decode/crc32.o 			\
				src/vitaAudio/ogg/api/version.o 			\
				src/vitaAudio/ogg/api/seek-tell.o 			\
				src/vitaAudio/ogg/api/read-int16.o 			\
				src/vitaAudio/ogg/api/read-float.o 			\
				src/vitaAudio/ogg/api/open-file.o 			\
				src/vitaAudio/ogg/api/open-callbacks.o 		\
				src/vitaAudio/ogg/api/open-buffer.o 		\
				src/vitaAudio/ogg/api/info.o 				\
				src/vitaAudio/ogg/api/close.o 				\
				src/vitaAudio/wav/wav.o 				 	\
				src/vitaAudio/buffer/buffer.o 			 	\
				src/vitaAudio/vitaAudio.o

LIBS 		= 	-lvita2d								\
				-lSceKernel_stub 						\
				-lSceGxm_stub 							\
				-lSceSysmodule_stub						\
				-lSceCtrl_stub							\
				-lScePgf_stub 							\
				-lSceCommonDialog_stub					\
				-lfreetype								\
				-lpng									\
				-ljpeg									\
				-lz										\
				-lm										\
				-lc										\
				-lSceDisplay_stub						\
				-lSceTouch_stub							\
				-lSceAudio_stub -lSceAudiodec_stub

	



	
BIN 		= bin
PREFIX  	= arm-vita-eabi
CC      	= $(PREFIX)-gcc
CXX      	= $(PREFIX)-g++
CFLAGS  	= -Wl,-q -Wall -O3 -std=c99 -Wno-unused-variable -Wno-unused-but-set-variable
CXXFLAGS 	= $(CFLAGS) -std=c++11 -fno-rtti -fno-exceptions
ASFLAGS 	= $(CFLAGS)
PSVITAIP 	= 10.0.63

all: $(BIN)/$(TARGET).vpk



%.vpk: $(BIN)/eboot.bin
	vita-mksfoex -d PARENTAL_LEVEL=1 -s APP_VER=00.40 -s TITLE_ID=$(TITLE_ID) "$(TITLE)" $(BIN)/param.sfo
	vita-pack-vpk -s $(BIN)/param.sfo -b $(BIN)/eboot.bin \
		--add sce_sys/icon0.png=sce_sys/icon0.png \
		--add sce_sys/livearea/contents/bg.png=sce_sys/livearea/contents/bg.png \
		--add sce_sys/livearea/contents/startup.png=sce_sys/livearea/contents/startup.png \
		--add sce_sys/livearea/contents/template.xml=sce_sys/livearea/contents/template.xml \
		\
		--add resources/sounds/snd_button1.wav=files/snd_button1.wav \
		--add resources/sounds/snd_button2.wav=files/snd_button2.wav \
		\
		--add resources/fonts/MyriadPro.otf=files/MyriadPro.otf \
	$(BIN)/$(TARGET).vpk



$(BIN)/eboot.bin: $(BIN)/$(TARGET).velf
	vita-make-fself $< $@



%.velf: %.elf
	vita-elf-create $< $@



$(BIN)/$(TARGET).elf: binfolder $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@	



%.o: %.png
	$(PREFIX)-ld -r -b binary -o $@ $^



clean:
	@rm -rf $(BIN) $(OBJS)



vpksend: $(BIN)/$(TARGET).vpk
	curl -T $(BIN)/$(TARGET).vpk ftp://$(PSVITAIP):1337/ux0:/
	@echo "Sent."



send: $(BIN)/eboot.bin
	curl -T $(BIN)/eboot.bin ftp://$(PSVITAIP):1337/ux0:/app/$(TITLE_ID)/
	@echo "Sent."



binfolder:
	@mkdir $(BIN) || true

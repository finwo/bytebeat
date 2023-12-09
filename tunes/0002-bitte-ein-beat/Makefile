0001-beat.wav: main.c
	rm -f $@
	tcc -lm -run main.c | ffmpeg -f u8 -ar 8k -ac 1 -i - $@


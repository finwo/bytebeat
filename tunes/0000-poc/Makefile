0000-poc.wav: main.c
	tcc -run main.c | ffmpeg -f u8 -ar 8k -ac 1 -i - $@


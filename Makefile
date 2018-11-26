all:
	g++ -o wav_2_mp3 Wav_2_MP3.cpp con.cpp -lmp3lame -lpthread

compile:

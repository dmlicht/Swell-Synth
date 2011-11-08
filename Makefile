CXXFLAGS=-I/Users/David/IS/portaudio/include -Wall
LIBS=-L/Users/David/IS/portaudio/lib/.libs -lportaudio -framework CoreAudio -framework AudioToolbox -framework AudioUnit -framework Carbon

test3: Player5.o wavetable.o sine_table.o square_table.o saw_table.o tri_table.o rand_table.o envelope.o sound_block.o generator.o mixer.o mixee.o processor.o synth.o note.o
	g++ -Wall $(CFLAGS) $(LIBS) Player5.o wavetable.o sine_table.o square_table.o saw_table.o tri_table.o rand_table.o envelope.o mixer.o mixee.o sound_block.o generator.o processor.o synth.o note.o -o test3

test2: Player4.o wavetable.o sine_table.o square_table.o saw_table.o tri_table.o rand_table.o envelope.o sound_block.o generator.o mixer.o mixee.o processor.o synth.o note.o
	g++ -Wall $(CFLAGS) $(LIBS) Player4.o wavetable.o sine_table.o square_table.o saw_table.o tri_table.o rand_table.o envelope.o mixer.o mixee.o sound_block.o generator.o processor.o synth.o note.o -o test2

Player4.o: Player4.cpp wavetable.h sine_table.h square_table.h saw_table.h tri_table.h rand_table.h envelope.h sound_block.h generator.h processor.h synth.h
#	g++ -Wall -c $(CFLAGS) Player2.cpp

Player5.o: Player5.cpp wavetable.h sine_table.h square_table.h saw_table.h tri_table.h rand_table.h envelope.h sound_block.h generator.h processor.h synth.h
#	g++ -Wall -c $(CFLAGS) Player3.cpp

wavetable.o: wavetable.cpp wavetable.h generator.h sound_block.h

sine_table.o: sine_table.cpp sine_table.h wavetable.h
square_table.o: square_table.cpp square_table.h wavetable.h
saw_table.o: saw_table.cpp saw_table.h wavetable.h
tri_table.o: tri_table.cpp tri_table.h wavetable.h
rand_table.o: rand_table.cpp rand_table.h wavetable.h
envelope.o: envelope.cpp envelope.h processor.h note.h

mixer.o: mixer.cpp mixer.h sound_block.h mixee.h note.h
mixee.o: mixee.cpp mixee.h mixer.h
sound_block.o: sound_block.cpp sound_block.h note.h
generator.o: generator.cpp generator.h sound_block.h note.h
processor.o: processor.cpp processor.h sound_block.h note.h
synth.o: synth.cpp synth.h sound_block.h generator.h wavetable.h note.h
note.o: note.cpp note.h synth.h

clean:
	rm *.o test2 test3
#outputGenerator.o: outputGenerator.cpp outputGenerator.h
#	g++ -Wall -c $(CFLAGS) outputGenerator.cpp

#waveform_processor.o: waveform_processor.cpp waveform_processor.h
#	g++ -Wall -c $(CFLAGS) waveform_processor.cpp

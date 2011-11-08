#include <cmath>
#include <iostream>
#include <string>
#include "portaudio.h"
#include "wavetable.h"
#include "sine_table.h"
#include "square_table.h"
#include "saw_table.h"
#include "tri_table.h"
#include "rand_table.h"
#include "envelope.h"
#include "mixer.h"
#include "mixee.h"
#include "processor.h"
#include "generator.h"
#include "sound_block.h"
#include "synth.h"

#define PLAY_TIME 4

using namespace std;

static int paCallBack( const void *inputBuffer, void *outputBuffer,
                         unsigned long framesPerBuffer,
			 const PaStreamCallbackTimeInfo* timeInfo,
			 PaStreamCallbackFlags statusFlags,
			 void *userData )
  {
    synth *data = (synth *) userData;
    float *out = (float *) outputBuffer;
    (void) inputBuffer;
    data->get_samps(out, framesPerBuffer);
    return 0;
  }

  int main()
  {
    string table_type;
    wavetable *wave;
//		wavetable *wave2;
//		wavetable *wave3;
//		envelope *env;
		synth *mysynth;
//		mixer *mix;
		synth::initialize();
		wave = new sine_table();
//		env = new envelope(.1, 0.5, .5, 0.5);
//		wave2 = new tri_table();
//		wave3 = new saw_table();

    PaStream *stream;

		mysynth = new synth(wave);
//		wave->add_after(env);
//		mix = new mixer();
//		wave->add_after(mix);
//		mix->add_mixee(wave2);
		mysynth->add_note(new note(45));
		mysynth->add_note(new note(52));
//		mix->add_mixee(wave3, .2);

    /* Set up PortAudio */
    PaError error;
    error = Pa_Initialize();
    if (error != paNoError) goto handle_portaudio_error;

    error = Pa_OpenDefaultStream(&stream,
  			        0,
			          synth::get_nchan(), 
			          paFloat32,
			          synth::get_sample_rate(),
			          synth::get_ksmps(),
			          paCallBack,
			          mysynth
                                );
    if (error != paNoError) goto handle_portaudio_error;

    error = Pa_StartStream(stream);
    if (error != paNoError) goto handle_portaudio_error;

    Pa_Sleep(4000);
/*
		mysynth->add_note(new note(76));
		mysynth->add_note(new note(57));
    Pa_Sleep(1000);
		mysynth->add_note(new note(73));
    Pa_Sleep(500);
		mysynth->add_note(new note(71));
    Pa_Sleep(500);
		mysynth->add_note(new note(57));
    Pa_Sleep(2000);
*/
		error = Pa_StopStream(stream);
    if (error != paNoError) goto handle_portaudio_error;

    error = Pa_CloseStream(stream);
    if (error != paNoError) goto handle_portaudio_error;

    error = Pa_Terminate();
    if (error !=paNoError){
      cout << "PortAudio error: " << Pa_GetErrorText(error);
    }
    return EXIT_SUCCESS;

handle_portaudio_error:
    Pa_Terminate();
    cout << "PortAudio error: " << Pa_GetErrorText(error) << endl;
    return EXIT_FAILURE;
  }

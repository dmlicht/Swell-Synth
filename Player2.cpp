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
//#include "mixer.h"
//#include "mixee.h"
#include "processor.h"
#include "generator.h"
#include "sound_block.h"
#include "synth.h"

#define SAMPLE_RATE 44100
#define KSMPS 128
#define TEST_FREQ 880
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
    int frequency;
    wavetable *wave;
		synth *mysynth;
		synth::initialize();

    cout << "Please enter desired frequency: ";
    cin >> frequency;
    cout << "Please enter desired wavetype(sine, saw, tri, square, noise): ";
    cin >> table_type;

    PaStream *stream;

    /* Set Sample Table */
    if (table_type.compare("sine") == 0){
      wave = new sine_table();
    }
    else if (table_type.compare("square") == 0){
      wave = new square_table;
    }
    else if (table_type.compare("saw") == 0){
      wave = new saw_table;
    }
    else if (table_type.compare("tri") == 0){
      wave = new tri_table;
    }
    else if (table_type.compare("noise") == 0){
      wave = new rand_table;
    }
    else {
      cout << "Error choosing wavetype" << endl;
    }
    wave->set_frequency(frequency);

		mysynth = new synth(wave);

    /* Set up PortAudio */
    PaError error;
    error = Pa_Initialize();
    if (error != paNoError) goto handle_portaudio_error;

    error = Pa_OpenDefaultStream(&stream,
  			        0,
			          1, 
			          paFloat32,
			          SAMPLE_RATE,
			          synth::get_ksmps(),
			          paCallBack,
			          mysynth
                                );
    if (error != paNoError) goto handle_portaudio_error;

    error = Pa_StartStream(stream);
    if (error != paNoError) goto handle_portaudio_error;

    Pa_Sleep(PLAY_TIME * 1000);
  
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

#include <cmath>
#include <iostream>
#include "portaudio.h"

#define SAMPLE_RATE 44100
#define TEST_FREQ 880
#define PLAY_TIME 3


typedef struct{
  float table[SAMPLE_RATE * PLAY_TIME];
  int index;
  float incr;
  float curphase;
  int osc_count;
} sinwave;

using namespace std;

/*
int sr;
int frequency;
int current_sample;
*/

static int paCallBack( const void *inputBuffer, void *outputBuffer,
                         unsigned long framesPerBuffer,
			 const PaStreamCallbackTimeInfo* timeInfo,
			 PaStreamCallbackFlags statusFlags,
			 void *userData )
  {
    sinwave *data = (sinwave *) userData;
    float *out = (float *) outputBuffer;
    (void) inputBuffer;

    for (unsigned long i = 0; i < framesPerBuffer; i++){
//      out = &(data->table[data->index]);
      *out = data->table[data->index];
//      *out = data->table[data->index];
//      cout << data->table[data->index] << endl;
      out++;
      data->index += 1;
    }
    return 0;
  }

  int main()
  {

    int frequency;
    /* Get user specifications */
/*    cout << "Please enter desired sample rate: ";
    cin >> sr; */
    cout << "Please enter desired frequency: ";
    cin >> frequency;
/*    cout << "Please enter desired play time in second: ";
    cin >> play_time_in_seconds;
*/

    PaStream *stream;
    sinwave wave;
    wave.index = 0;
    wave.osc_count = 0;
    wave.incr = frequency * (2 * M_PI) / SAMPLE_RATE;
    for (int i = 0; i < SAMPLE_RATE * PLAY_TIME; ++i){
      if (wave.curphase < M_PI){
        wave.table[i] = 1;
      } else { 
        wave.table[i] = -1;
      }
      wave.curphase += wave.incr;
      if (wave.curphase >= (2 * M_PI)){
//        cout <<  ++wave.osc_count << endl;
        wave.curphase -= 2 * M_PI;
      }
    }

    
    /* Set up PortAudio */
    PaError error;
    error = Pa_Initialize();
    if (error != paNoError) goto handle_portaudio_error;

    error = Pa_OpenDefaultStream(&stream,
  			          0,
			          1, 
			          paFloat32,
			          SAMPLE_RATE,
			          paFramesPerBufferUnspecified,
			          paCallBack,
			          &wave
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

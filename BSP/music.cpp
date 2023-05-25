//
// Created by bleppe on 25/5/2023.
//

#include "music.h"
#include "debug_bsp.h"
#include <SDL2/SDL.h>
#include <cmath>
#include "task.h"
#include "queue.h"

struct AudioData{
    MuscialNote note;
    bool play;
};

static const int SAMPLE_RATE = 44100;
static const int BUFFER_SIZE = 2048;
static const int CHANNELS = 2;
static const int BYTES_PER_SAMPLE = sizeof(float);
static float angle = 0.0;
static AudioData data;
static TaskHandle_t thread;
static QueueHandle_t queue;
static bool running;

// <editor-fold defaultstate="collapsed" desc="notes">
static float notes[] = {
        261.626,
        277.183,
        293.665,
        311.127,
        329.628,
        349.228,
        369.994,
        391.995,
        415.305,
        440,
        466.164,
        493.883,
        523.251,
        554.365,
        587.33,
        622.254,
        659.225,
        698.456,
        739.989,
        783.991,
        830.609,
        880,
        932.328,
        987.767,
        1046.5,
        1108.73,
        1174.66,
        1244.51,
        1318.51,
        1396.91,
        1479.98,
        1567.98,
        1661.22,
        1760,
        1864.66,
        1975.53,
        0,
};
// </editor-fold>
static AudioElement jingle_notes[] = {
        {Mi5, Negra},
        {Mi5, Negra},
        {Mi5, Blanca},
        {Mi5, Negra},
        {Mi5, Negra},
        {Mi5, Blanca},
        {Mi5, Negra},
        {Sol5, Negra},
        {Do5, Negra},
        {Re5, Negra},
        {Mi5, Redonda},
};
static AudioElement OSInit[] = {//A4,C5,E5,G5,A5
        {La4, Negra},
        {Do5, Negra},
        {Mi5, Negra},
        {Sol5, Negra},
        {La5, Negra},
};
static AudioElement OSInit2[] = {//A4,C5,E5,G5,A5
        {Do5, Negra},
        {Mi5, Negra},
        {Sol5, Negra},
        {Fas5, Negra},
        {Re5, Negra},
        {Do5, Negra},
};
static Song jingle_bells = {
        .noteArray = jingle_notes,
        .len = (int)sizeof(jingle_notes)/sizeof(AudioElement),
        .bpm = 60,
};
static Song os_song = {
        .noteArray = OSInit,
        .len = (int)sizeof(OSInit)/sizeof(AudioElement),
        .bpm = 22,
};

static void audioCallback(void* userdata, Uint8* stream, int len);
static void generateAudioSamples(float frequency, float* stream, int length);
static void task(void*);



void music_initialize()
{
    SDL_AudioSpec desiredSpec, obtainedSpec;
    desiredSpec.freq = SAMPLE_RATE;
    desiredSpec.format = AUDIO_S16;
    desiredSpec.channels = CHANNELS;
    desiredSpec.samples = BUFFER_SIZE;
    desiredSpec.callback = audioCallback;
    desiredSpec.userdata = &data;

    data.play = false;

    /* Open the audio device, forcing the desired format */
    if ( SDL_OpenAudio(&desiredSpec, &obtainedSpec) < 0 ) {
        DEBUG_PRINT("Error\n");
        return;
    }

    SDL_PauseAudio(0);  // Unpause audio playback
    running = true;
    queue = xQueueCreate(1,sizeof(Song));
    xTaskCreate(task,"MusicTask",1024, nullptr,2,&thread);
    music_play_song(&os_song);
}
void music_deinit()
{
    running = false;
    vTaskDelete(thread);
    SDL_PauseAudio(1);  // Unpause audio playback
    SDL_CloseAudio();   // Close the audio device
}
void music_play_note(enum MuscialNote note, int ticks)
{
    data.play = true;
    data.note = note;
    SDL_Delay(ticks-10);
    data.note = silence;
    SDL_Delay(10);
    data.play = false;
}
void music_play_song(Song *song)
{
    xQueueSend(queue, song, 0);
}

// Function to generate audio samples for the C5 note
static void generateAudioSamples(float frequency, float* stream, int length) {
    const float amplitude = 0.2;  // Amplitude of the audio signal
    float increment = 2.0f * M_PI * frequency / SAMPLE_RATE;

    for (int i = 0; i < length; i+=2) {
        float sample = amplitude * sinf(angle);
        stream[i] = sample;
        stream[i+1] = sample;
        angle += increment;
    }
}
// Audio callback function
void audioCallback(void* userdata, Uint8* stream, int len) {
    if(!data.play)
        return;
    float* samples = (float*)stream;
    int numSamples = len / BYTES_PER_SAMPLE;
    generateAudioSamples(notes[data.note] ,samples, numSamples);
}

void task(void *params){
    Song song;
    while(running)
    {
        if(xQueueReceive(queue,&song,10) == 1){
            for(int i = 0; i < song.len; i++){
                music_play_note(song.noteArray[i].note, song.bpm * song.noteArray[i].ticks);
            }
        }
    }
}
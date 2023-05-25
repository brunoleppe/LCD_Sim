//
// Created by bleppe on 03/04/23.
//

#ifndef MUSIC_H
#define MUSIC_H

enum MuscialNote{
    Do4     = 0 ,
    Dos4        ,
    Re4         ,
    Res4        ,
    Mi4         ,
    Fa4         ,
    Fas4        ,
    Sol4        ,
    Sols4       ,
    La4         ,
    Las4        ,
    Si4         ,
    Do5         ,
    Dos5        ,
    Re5         ,
    Res5        ,
    Mi5         ,
    Fa5         ,
    Fas5        ,
    Sol5        ,
    Sols5       ,
    La5         ,
    Las5        ,
    Si5         ,
    Do6         ,
    Dos6        ,
    Re6         ,
    Res6        ,
    Mi6         ,
    Fa6         ,
    Fas6        ,
    Sol6        ,
    Sols6       ,
    La6         ,
    Las6        ,
    Si6         ,
    silence     ,
};
enum NoteDuration{
    Semicorchea = 1,
    Corchea = 2,
    Corchea_punto = 3,
    Negra = 4,
    Negra_punto = 6,
    Blanca = 8,
    Blanca_punto= 12,
    Redonda = 16,
    Redonda_punto = 24,
};


typedef struct AudioElement{
    enum MuscialNote note;
    int ticks;
}AudioElement;

typedef struct Song{
    AudioElement *noteArray;
    int len;
    int bpm;
}Song;

void music_initialize();
void music_deinit();
void music_play_note(enum MuscialNote note, int ticks);
void music_play_song(Song *song);

#endif //MUSIC_H
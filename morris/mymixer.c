#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<unistd.h>
#include<SDL2/SDL_audio.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL.h>


int main()
{
    printf("this sdl_mixer test~\n");

    // 初始化 SDL_mixer 失敗的話，會報錯
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) 
    {
        fprintf(stderr, "Failed to initialize SDL_mixer: %s\n", Mix_GetError());
        SDL_Quit();
        return 1;
    }

    // 這個chunk是拿來播音效的
    // Mix_LoadWAV 是拿來載入.wav檔的函式
    Mix_Chunk* soundEffect = Mix_LoadWAV("soundeffect-gameover.wav");
    // 載入失敗的報錯
    if (soundEffect == NULL) {
        fprintf(stderr, "Failed to load sound effect: %s\n", Mix_GetError());
    }

    // 這個music是拿來播音樂的(長的音樂)
    // Mix_LoadMUS 是拿來載入.mp3檔的函式
    Mix_Music* music = Mix_LoadMUS("bgm_flow.mp3");
    if (music == NULL) 
    {
        fprintf(stderr, "Failed to load music: %s\n", Mix_GetError());
    }

    // 播音樂 後面數字指的是次數，-1就是無限循環
    Mix_PlayMusic(music, -1);  // Play indefinitely

    sleep(1);

    

    
    // 暫停/重播 音樂
    // Pause/Resume music
    Mix_PauseMusic();
    sleep(1);
    Mix_ResumeMusic();
    sleep(1);

    // Stop music
    Mix_HaltMusic();

    sleep(1);

    // 找一個空的頻道播放音效 
    int channel = Mix_PlayChannel(-1, soundEffect, 0);  // Play on any free channel
    if (channel == -1) {
        fprintf(stderr, "Failed to play sound effect: %s\n", Mix_GetError());
    }
    
    sleep(1);

    
    Mix_FreeChunk(soundEffect);
    Mix_FreeMusic(music);
    Mix_CloseAudio();  // Close SDL_mixer



}
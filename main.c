#include "sdl_func.h"
#include "story.h"

int main(int argc, char** argv){
    SDL_Window     *window;
    SDL_Renderer   *renderer;
    SDL_Surface    *screen;
    SDL_Event       ev;

    SDL_Color       white = {255, 255, 255};
    SDL_Color       black = {0, 0, 0};

    SDL_Texture    *scene;
    SDL_Texture    *main_character;
    SDL_Texture    *other_character;
    SDL_Texture    *text;

    init_sdl(&window, &renderer);

    //path buffer
    char *scene_path = get_scene(line);
    char *speaker = get_speaker(line);
    char *dialogue = get_dialogue(line);


    FILE *fp = fopen("test.txt", "r");
    if(fp == NULL){
        printf("File not found\n");
        return 1;
    }

    while (1) {
        SDL_PollEvent(&ev);
        if (ev.type == SDL_QUIT) {
            break;
        } // break the loop

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);

        //main loop
        char *buff = readline(fp);
        sline *line = parse_line(buff, strlen(buff));
        switch(line -> kind){
            case SCENE:
                // printf("scene: %s\n", scene_path);
                scene = load_png(scene_path, renderer);
                free(scene_path);
                break;
            case DIALOGUE:
                if(strcmp(line -> speaker, "肌肉超人") == 0){
                    main_character = load_png(speaker, renderer);
                }else{
                    other_character = load_png(speaker, renderer);
                }

                printf("%s\n", dialogue);
                text = load_png(dialogue, renderer);
                // free(speaker);
                // free(dialogue);
                break;
            case CHOICE:
                break;
            case EVENT:
                break;
        }

        renderTexture(scene, renderer, 0, 0, 900, 600);
        renderTexture(other_character, renderer, 300, 100, 100, 100);
        renderTexture(main_character, renderer, 100, 100, 100, 100);
        renderTexture(text, renderer, 100, 300, 600, 200);

        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
        free(buff);
        free_sline(line);
    } // window loop



    SDL_DestroyTexture(scene);
    SDL_FreeSurface(screen);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
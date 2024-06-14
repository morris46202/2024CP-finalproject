#include "sdl_func.h"
#include "story.h"

int main(int argc, char** argv){
    SDL_Window     *window;
    SDL_Renderer   *renderer;
    SDL_Surface    *screen;
    SDL_Event       ev;

    SDL_Color       white = {255, 255, 255, 255};
    SDL_Color       black = {0, 0, 0};

    SDL_Texture    *scene;
    SDL_Texture    *main_character;
    SDL_Texture    *other_character;
    SDL_Texture    *text;
    TTF_Font       *Sans = NULL;
    SDL_Texture    *message;
    int             message_width = 0;
    int             in_choice = 0;
    FILE           *fp;

    initSDL(&window, &renderer, &fp, &Sans);

    while (1) {
        SDL_PollEvent(&ev);
        if (ev.type == SDL_QUIT) {
            break;
        }else if(ev.type == SDL_MOUSEBUTTONDOWN){
            continue;
        }

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);

        //main loop
        char *buff = readline(fp);
        sline *line = parse_line(buff, strlen(buff));
        if(buff == NULL){
            printf("End of file\n");
            break;
        }
        switch(line -> kind){
            case SCENE:
                char *scene_path = get_scene(line);
                // printf("scene: %s\n", scene_path);
                scene = load_png(scene_path, renderer);
                free(scene_path);
                break;
            case DIALOGUE:
                char *speaker = get_speaker(line);
                printf("speaker: %s\n", speaker);
                char *dialogue = get_dialogue(line, &message_width);
                printf("dialogue: %s\n", dialogue);
                if(strcmp(line -> speaker, "肌肉超人") == 0){
                    main_character = load_png(speaker, renderer);
                }else{
                    other_character = load_png(speaker, renderer);
                }

                // printf("%s\n", dialogue);
                // text = load_png(dialogue, renderer);
                message = load_text(dialogue, Sans, white, renderer);

                free(speaker);
                free(dialogue);
                break;
            case CHOICE:
                in_choice = 1;
                break;
            case EVENT:
                break;
        }

        //x, y, w, h
        renderTexture(scene, renderer, 0, 0, 900, 600);
        renderTexture(other_character, renderer, 0, 350, 250, 250);
        renderTexture(main_character, renderer, 650, 350, 250, 250);
        // renderTexture(text, renderer, 100, 600, 600, 200);
        renderTexture(message, renderer, 0, 600, message_width * 8, 25);


        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
        free(buff);
        free_sline(line);
    } // window loop

    SDL_DestroyTexture(message);

    SDL_DestroyTexture(scene);
    SDL_FreeSurface(screen);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_CloseFont(Sans);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
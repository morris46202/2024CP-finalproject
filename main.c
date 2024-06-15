#include "sdl_func.h"
#include "story.h"

int main(int argc, char** argv){
    SDL_Window     *window;
    SDL_Renderer   *renderer;
    SDL_Surface    *screen;
    SDL_Event       ev;

    SDL_Color       white = {255, 255, 255, 255};
    SDL_Color       yellow = {255, 255, 0};
    SDL_Color       black = {0, 0, 0};

    SDL_Texture    *scene;
    SDL_Texture    *main_character;
    SDL_Texture    *other_character;
    SDL_Texture    *text;
    TTF_Font       *Sans = NULL;
    SDL_Texture    *message;
    SDL_Texture    *opt_tmp;
    int             message_width = 0;
    int             in_choice = 0;
    FILE           *fp;
    Option         *opt[10];
    int             opt_count = 0;
    int             end = 0;

    initSDL(&window, &renderer, &fp, &Sans);
    GameData *game_data = load_game("game_data.txt");

    while (1) {
        SDL_PollEvent(&ev);
        if (ev.type == SDL_QUIT) {
            break;
        }

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);

        //main loop
        char *buff = readline(fp);
        sline *line = parse_line(buff, strlen(buff));
        if(buff == NULL || line == NULL){
            printf("End of file\n");
            break;
        }
        switch(line -> kind){
            case PARA:
                game_data -> para = line -> para;
                save_game(game_data, "game_data.txt");
                break;
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

                opt_count = 0;
                while(line -> kind == CHOICE){
                    opt[opt_count] = get_choice(line);
                    // printf("choice: %s\n", item_path[item_count]);
                    opt_count++;
                    free_sline(line);
                    buff = readline(fp);
                    line = parse_line(buff, strlen(buff));
                }

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

        SDL_Rect *opt_rect = (SDL_Rect *)calloc(opt_count, sizeof(SDL_Rect));
        for(int i = 0; i < opt_count; i++){
            opt_tmp = load_text(opt[i] -> text, Sans, white, renderer);
            opt_rect[i].x = 1150 - (8 * opt[i]->text_len) - 10;
            opt_rect[i].y = 600 + 25 * (i + 1);
            opt_rect[i].w = 8 * opt[i]->text_len;
            opt_rect[i].h = 25;
            renderTexture(opt_tmp, renderer, opt_rect[i].x, opt_rect[i].y, opt_rect[i].w, opt_rect[i].h);
        }

        SDL_RenderPresent(renderer);
        if(line -> kind == DIALOGUE || line -> kind == END || in_choice == 1){
            SDL_Texture *cursor = load_text("<", Sans, yellow, renderer);
            int selected_option = 0;
            while(ev.type != SDL_MOUSEBUTTONDOWN){ //等待滑鼠按下
                SDL_PollEvent(&ev);
                SDL_Delay(10);
                if(ev.type == SDL_QUIT){
                    end = 1;
                    break;
                }

                if(in_choice == 1){
                    SDL_Point mouse;
                    SDL_GetMouseState(&mouse.x, &mouse.y);
                    // SDL_Texture *cursor = load_text("<", Sans, yellow, renderer);
                    for(int i = 0; i < opt_count; i++){
                        if(SDL_PointInRect(&mouse, &opt_rect[i]) && ev.type == SDL_MOUSEBUTTONDOWN){
                            selected_option = i;
                            printf("selected_option: %d\n", selected_option);
                            in_choice = 0;
                            jump(fp, opt[selected_option] -> jump);
                            for(int j = 0; j < opt_count; j++){
                                free(opt[j] -> text);
                                free(opt[j] -> filepath);
                                free(opt[j]);
                            }
                            opt_count = 0;
                            break;
                        }
                    }
                }

            }
        }
        if(end == 1){
            break;
        }
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
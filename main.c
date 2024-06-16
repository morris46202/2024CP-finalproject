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
    int             narrator = 0;

    initSDL(&window, &renderer, &fp, &Sans);
    GameData *game_data = load_game("game_data.txt");
    if(game_data->para != 0){
        jump(fp, game_data->para);
    }

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
            exit(0);
        }
        switch(line -> kind){
            case PARA:
                // printf("para: %d\n", line -> para);
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
                char *speaker = (char *)calloc(10, sizeof(char));
                char *speaker_path = get_speaker(line, speaker);
                // printf("speaker: %s\n", speaker);
                char *dialogue = get_dialogue(line, &message_width);
                // printf("dialogue: %s\n", dialogue);
                
                char *sentence = (char *)calloc(strlen(speaker)+strlen(dialogue)+3, sizeof(char));
                if(strcmp(line -> speaker, "大頭") == 0){
                    main_character = load_png(speaker_path, renderer);
                }else{
                    other_character = load_png(speaker_path, renderer);
                }
                if(strlen(speaker) != 0){
                    message_width += strlen(speaker) + 2;
                    strncat(sentence, speaker, strlen(speaker));
                    strncat(sentence, ": ", 3);
                }else{
                    narrator = 1;
                }
                strncat(sentence, dialogue, strlen(dialogue));
                // printf("%s\n", dialogue);
                // text = load_png(dialogue, renderer);
                message = load_text(sentence, Sans, white, renderer);

                free(speaker);
                free(speaker_path);
                free(dialogue);
                free(sentence);
                break;
            case CHOICE:
                in_choice = 1;

                opt_count = 0;
                while(line -> kind == CHOICE){
                    opt[opt_count] = get_choice(line);
                    // printf("choice: %s\n", opt[opt_count] -> text);
                    opt_count++;
                    free_sline(line);
                    buff = readline(fp);
                    line = parse_line(buff, strlen(buff));
                }

                break;
            case EVENT:
                mod_data(game_data, line);
                save_game(game_data, "game_data.txt");
                break;

            case CONDITION:
                int c = check_condition(game_data, line);
                // printf("condition: %d\n", c);
                if(c == 0){
                    printf("jump!\n");
                    readline(fp);
                }
                break;

            default:
                break;
        }
        // display_data(game_data, Sans, white, renderer);
        display_data_graph(game_data, Sans, white, renderer);
        display_item(game_data, Sans, white, renderer);
        save_game(game_data, "game_data.txt");
        // show_stats(game_data);
        // printf("opt_count: %d\n", opt_count);

        //x, y, w, h
        renderTexture(scene, renderer, 0, 0, 900, 600);
        // printf("narrator: %d\n", narrator);
        renderTexture(other_character, renderer, 0, 350, 250, 250);
        // narrator = 0;
        renderTexture(main_character, renderer, 650, 350, 250, 250);
        // renderTexture(text, renderer, 100, 600, 600, 200);
        renderTexture(message, renderer, 0, 600, message_width * 8, 25);

        SDL_Rect exit_rect = {900, 800, 100, 50};
        draw_exit_button(Sans, white, renderer, exit_rect);

        SDL_Rect *opt_rect = (SDL_Rect *)calloc(opt_count, sizeof(SDL_Rect));
        SDL_Texture **opt_text = (SDL_Texture **)calloc(opt_count, sizeof(SDL_Texture *));
        if(game_data->para == 31 && in_choice == 1){
            opt_count = 5;
        }
        for(int i = 0; i < opt_count; i++){
            if(game_data->para == 31 && in_choice == 1){
                // printf("recent opt_count: %d\n", opt_count);
                // printf("recent i: %d\n", i);
                if(game_data->love[LOVE_HOWARD] < 20 && i == LOVE_HOWARD){
                    // i++;
                    continue;
                }
                if(game_data->backpack[ITEM_TICKET] == 0 && i == ITEM_TICKET){
                    // i++;
                    continue;
                }
            }
            opt_text[i] = load_text(opt[i] -> text, Sans, white, renderer);
            opt_rect[i].x = 1150 - (8 * opt[i]->text_len) - 10;
            opt_rect[i].y = 600 + 25 * (i + 1);
            opt_rect[i].w = 8 * opt[i]->text_len;
            opt_rect[i].h = 25;
            renderTexture(opt_text[i], renderer, opt_rect[i].x, opt_rect[i].y, opt_rect[i].w, opt_rect[i].h);
            SDL_DestroyTexture(opt_text[i]);
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
            SDL_Point mouse;
            SDL_GetMouseState(&mouse.x, &mouse.y);
                if(in_choice == 1){
                    // SDL_Texture *cursor = load_text("<", Sans, yellow, renderer);
                    for(int i = 0; i < opt_count; i++){
                        if(SDL_PointInRect(&mouse, &opt_rect[i]) && ev.type == SDL_MOUSEBUTTONDOWN){
                            selected_option = i;
                            printf("selected_option: %d\n", selected_option);
                            if(game_data->para == 10){
                                if(selected_option == 0){
                                    game_data -> love[LOVE_TIKILI] += 10;
                                }else if(selected_option == 1){
                                    game_data -> love[LOVE_SHINRAY] += 10;
                                    game_data -> love[LOVE_JCUP] += 10;
                                }else if(selected_option == 2){
                                    game_data -> love[LOVE_JCUP] += 10;
                                }else if(selected_option == 3){
                                    game_data -> love[LOVE_SUKI] += 10;
                                }else if(selected_option == 4){
                                    game_data -> love[LOVE_SHINRAY] += 10;
                                }
                                save_game(game_data, "game_data.txt");
                            }
                            in_choice = 0;
                            jump(fp, opt[selected_option] -> jump);
                            sline *line = parse_line(buff, strlen(buff));
                            game_data->para = opt[selected_option] -> jump;
                            save_game(game_data, "game_data.txt");
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

                if(SDL_PointInRect(&mouse, &exit_rect) && ev.type == SDL_MOUSEBUTTONDOWN){
                    printf("exit\n");
                    end = 1;
                    break;
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
    SDL_DestroyTexture(main_character);
    SDL_DestroyTexture(other_character);
    SDL_DestroyTexture(scene);
    SDL_FreeSurface(screen);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_CloseFont(Sans);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
#include "keylist.hpp"
#include "everything.hpp"

void do_command(int what) {
    command_par(1,what);
}

int sub_load_maze=0;

void command_par(int num, ...) {
    va_list args;
    va_start(args, num);
    int font_size;
    sf::Color color;
    int decimal;
    int what=va_arg(args,int);
    switch (what) {
        case GO_DOWNLOAD:
            go_download=0;
            start_get_videos_thread();
            break;
        case GO_LIST:
            combine=1;
            start_burning=1;
            go_burn=1;
            go_list=0;
            break;
        case -1:
            CLEANBITMAPS();
            cleanupbitmaps_mazes();
            ReadBitmaps2();
            ReadBitmaps4();
            go_burn=0;
            plot_back=0;
            plot_front=1;
            F4=1;
            difficulty=4;
            skipclear=1;
            force_game=1;
            F2=0;
            eatmode=1;
            insert_event(sf::Keyboard::Add,0);
            flippo=0;
            break;
        case GO_BURN:
////            force_game=0;
////            insert_event(sf::Keyboard::F,EVENT_CONTROL);
            handler[INTERNET_SELECT].plot_front=-1;
            selector=INTERNET_SELECT;
            burn_next_sub_ready=1;
            break;
        case TEXT_FILES:        //SHIFT-F1
//            insert_event(sf::Keyboard::T,EVENT_ALT);
            font_size=atoi(va_arg(args,char *));
            decimal = (int)strtol((va_arg(args,char *)), NULL, 16);
            color=sf::Color( decimal );
            textfiles_to_screen(font_size  , color);
//            textfiles_to_screen();
            break;
        case MACRO_LIST:        //SHIFT-F1
//            insert_event(sf::Keyboard::F1,EVENT_SHIFT);
            read_keylist_hpp();
            parse_command("TEXT_FILES 30 0xFF00FFFF");
            break;
        case MACRO1:
            insert_event(sf::Keyboard::F6,EVENT_ALT);
            insert_event(sf::Keyboard::F6,EVENT_ALT);
            insert_event(sf::Keyboard::F12,0);
            insert_event(sf::Keyboard::F12,EVENT_CONTROL);
            insert_event(sf::Keyboard::F10,0);
            insert_event(sf::Keyboard::F10,EVENT_CONTROL);
            insert_event(sf::Keyboard::Y,EVENT_CONTROL);
            insert_event(sf::Keyboard::Down,EVENT_ALT);
            for (int x=0; x<40; x++) insert_event(sf::Keyboard::PageDown,EVENT_SHIFT);
            break;
        case GRAPHICS_MODE:
            decimal=atoi(va_arg(args,char *));
            formula=decimal;
            break;
        case BACKGROUND:
            if (drawmazes==1) insert_event(sf::Keyboard::D,EVENT_SHIFT);
            break;
        case FOREGROUND:
            if (drawmazes==0) insert_event(sf::Keyboard::D,EVENT_SHIFT);
            break;
        case PLOT_ALL:
            insert_event(sf::Keyboard::F6,EVENT_SHIFT);
            break;
        case MACRO2:
            insert_key('x');
            insert_event(sf::Keyboard::F9,EVENT_SHIFT);
            insert_key('g');
            insert_event(sf::Keyboard::Y,EVENT_CONTROL);
            insert_event(sf::Keyboard::Down,EVENT_ALT);
            for (int x=0; x<40; x++) insert_event(sf::Keyboard::PageDown,EVENT_SHIFT);
            break;
        case ZOOM_OUT:
            DO_ADAPT=1;
            if (zoom_off==1) {
                hold=(double)(sprite_from_canvas.getScale().x)*pow(2.0,level);
                hold_level=level;
                zoom_off=0;
                scale_slow=sprite_from_canvas.getScale().x;
                speed_slowx=0.0;
                speed_slowy=0.0;
                ddp_loop=0.0;
//                printf("command(ZOOM_OUT): hold=%f hold_level=%d\n",hold,hold_level);
            }
            if ((double)scale_slow<scale_jump && level>0) {
//            if ((double)sprite_from_canvas.getScale().x<scale_jump && level>0) {
                playsound=playsound|3;
                double rel_x=rel_pos_in_map_x;
                double rel_y=rel_pos_in_map_y;
//                printf("command(ZOOM_OUT): insert_key('[')\n");
                insert_key('[');
                rel_pos_in_map_x=rel_x;
                rel_pos_in_map_y=rel_y;
                rel_pos_to_pacman();
            } else if (level==0 && scale_slow<0.01) {
//            } else if (level==0 && sprite_from_canvas.getScale().x<0.01) {
//                printf("command(ZOOM_OUT): DO_ZOOM_OUT=0\n");
                DO_ZOOM_OUT=0;
            }
            break;
        case ZOOM_IN:
            DO_ADAPT=1;
            if ( (double)(scale_slow)*pow(2.0,level)>hold || (double)(scale_slow)>=5.0)  {
//            if ( (double)(sprite_from_canvas.getScale().x)*pow(2.0,level)>hold || (double)(sprite_from_canvas.getScale().x)>=10.0)  {
                DO_ZOOM_IN=0;
//                printf("command(ZOOM_IN): DO_ZOOM_IN=0\n");
            } else if ((double)(scale_slow/2.0)>=scale_jump && level<SAS_MAX_ZOOM && level<hold_level) {
//            } else if ((double)(sprite_from_canvas.getScale().x/2.0)>=scale_jump && level<SAS_MAX_ZOOM && level<hold_level) {
                playsound=playsound|3;
                double rel_x=rel_pos_in_map_x;
                double rel_y=rel_pos_in_map_y;
//                printf("command(ZOOM_IN): insert_key(']')\n");
                insert_key(']');
                rel_pos_in_map_x=rel_x;
                rel_pos_in_map_y=rel_y;
                rel_pos_to_pacman();
            }
            break;
        case ADAPT_SPEED:
            adapt_speed();
            break;
        default:
            printf("UNKNOWN COMMAND: %d\n",what);
            break;
    }
    va_end(args);
}


void insert_key(WPARAM key) {
    HANDLECHAR((WPARAM)key);
}


void insert_event(sf::Keyboard::Key code,int MODE) {
    sf::Event my_event;
    my_event.type=sf::Event::KeyPressed;
    my_event.key.code=code;
    my_event.key.alt=false;
    my_event.key.control=false;
    my_event.key.shift=false;
    my_event.key.system=false;
    if ((MODE&EVENT_ALT)==EVENT_ALT) my_event.key.alt=true;
    if ((MODE&EVENT_SHIFT)==EVENT_SHIFT) my_event.key.shift=true;
    if ((MODE&EVENT_CONTROL)==EVENT_CONTROL) my_event.key.control=true;
    if ((MODE&EVENT_SYSTEM)==EVENT_SYSTEM) my_event.key.system=true;
    HANDLEKEY((WPARAM)my_event.key.code,my_event);
}

void print_event(sf::Event event) {
    char type[100];
    char code_char[50];
    WPARAM unicode;
    WPARAM code;
    switch (event.type) {
//        case sf::Event::Closed:
//            strcpy(type,"Closed");
//            printf("Type: %s\n",type);
//            break;
        case sf::Event::TextEntered:
            strcpy(type,"TextEntered");
            unicode=event.text.unicode;
//            printf("Type: %s unicode: %d\n",type,unicode);
            break;
        case sf::Event::KeyPressed:
            strcpy(type,"KeyPressed");
            code=event.key.code;
            switch (code) {
                case sf::Keyboard::PageDown:
                    strcpy(code_char,"PageDown");
                    break;
                case sf::Keyboard::PageUp:
                    strcpy(code_char,"PageUp");
                    break;
                case sf::Keyboard::RBracket:
                    strcpy(code_char,"']'");
                    break;
                case sf::Keyboard::LBracket:
                    strcpy(code_char,"'['");
                    break;
                default:
                    sprintf(code_char,"#%d",code);
                    break;
            }
//            printf("Type: %s code: %s ALT=%d CONTROL=%d SHIFT=%d SYSTEM=%d\n",type,code_char,event.key.alt,event.key.control,event.key.shift, event.key.system);
            break;
//        case sf::Event::MouseMoved:
//            strcpy(type,"MouseMoved");
//            printf("Type: %s x: %d y: %d\n",type,event.mouseMove.x,event.mouseMove.y);
//            break;
//        case sf::Event::MouseButtonPressed:
//            strcpy(type,"MouseButtonPressed");
//            printf("Type: %s x: %d y: %d\n",type,event.mouseMove.x,event.mouseMove.y);
//            break;
        default:
            strcpy(type,"Other");
            code=event.key.code;
//            printf("Type: %s code: %d ALT=%d CONTROL=%d SHIFT=%d SYSTEM=%d\n",type,code,event.key.alt,event.key.control,event.key.shift, event.key.system);
            break;
    }
}

inline int wordlen(const char * str){
   int tempindex=0;
   while(str[tempindex]!=' ' && str[tempindex]!=0 && str[tempindex]!='\n'){
      ++tempindex;
   }
   return(tempindex);
}

void wrap(char * s, const int wrapline){
    int start=0;
    int index=0;
    int curlinelen = 0;
    while(s[index] != '\0'){
      if(s[index] == '\n'){
         curlinelen=0;
      }
      else if(s[index] == ' '){
         if(curlinelen+wordlen(&s[index+1]) >= wrapline){
            s[index] = '\n';
            curlinelen = 0;
         }
      }
      curlinelen++;
      index++;
    }
}

struct keylist_struct {
    char name[16]="";
    int code;
    char key[22]="";
    char desc[101]="";
};

struct keylist_struct keylist[1000];
int trim(char * text);
int num=0;

void read_keylist_hpp() {
    FILE * file;
    char line[10000]="";
    char test[15]="";
    int line_count=0;
    bool record=false;
    bool stop=false;
    bool skip=true;
    num=0;
    if (file=fopen("src/keylist.hpp","r")) {
        while ( fgets (line,10000, file)!=NULL && stop==false) {
//            printf("line[%d]=%s",line_count,line);
            line_count++;
            if (record==false) {
                strcpy(test,"              ");
                strncpy(test,(line+8),10);
                trim(test);
//                printf("test=\"%s\"\n",test);
                if (strcmp(test,(char*)"LIST_START")==0) {
                    record=true;
                }
            } else {
                skip=false;
                strcpy(test,"              ");
                strncpy(test,(line+8),8);
                trim(test);
                if (strcmp(test,(char*)"LIST_END")==0) {
//                    printf("test=\"%s\"\n",test);
                    record=false;
                    stop=true;
                }
            }
            if (record==true && skip==false) {
                if (strlen(line)>=8) {
                    strncpy(keylist[num].name,line+8,15);
                    trim(keylist[num].name);
                } else strcpy(keylist[num].name,(char*)"");

                if (strlen(line)>=24) {
                    strcpy(test,"              ");
                    strncpy(test,line+24,7);
                    trim(test);
                    keylist[num].code=atoi(test);
                } else {
                    keylist[num].code=0;
                }
                if (strlen(line)>=38) {
                    strncpy(keylist[num].key,line+38,21);
                    trim(keylist[num].key);
                } else strcpy(keylist[num].key,(char*)"");

                if (strlen(line)>=60) {
                    strncpy(keylist[num].desc,line+60,100);
                    if (strlen(line)<=160 && strlen(line)>60) keylist[num].desc[strlen(line)-61]='\0';
                } else strcpy(keylist[num].desc,(char*)"");
                num++;
                int add=160;
                while (strlen(line)>add) {
                    strcpy(keylist[num].name,keylist[num-1].name);
                    keylist[num].code=keylist[num-1].code;
                    strcpy(keylist[num].key,keylist[num-1].key);
                    strncpy(keylist[num].desc,line+add,100);
                    if (strlen(line)<=add+100 && strlen(line)>add) keylist[num].desc[strlen(line)-add-1]='\0';
//                    printf("desc=%s\n",keylist[num].desc);
                    add+=100;
                    num++;
                }
            }
        }
        fclose(file);
        if (!(file=fopen("MACRO.TXT","w"))) {
            printf("Can not open MACRO.TXT FOR WRITING.\n");
            strcpy(error_msg4,"CAN NOT OPEN MACRO.TXT FOR WRITING"); error_flag4=1;
        }
//        printf("RESULTS(%d)\n",num);
//        printf("  # NAME            CODE    KEY                  DESCRIPTION\n");
        if (file) fprintf(file,"\n");
        if (file) fprintf(file,"  # NAME            CODE    KEY                  DESCRIPTION\n");
        strcpy(line,"");
        int x=0;
        int str_clear=1;
        for (x=0; x<num-1; x++) {
            if (x>0) {
                if (keylist[x].code==keylist[x-1].code || keylist[x].code==0) {
//                    if (strlen(keylist[x-1].desc)>0) {
//                        if (keylist[x-1].desc[strlen(keylist[x-1].desc)-1]!=' ') {
//                            printf(" ");
//                            if (file) fprintf(file," ");
//                            strcat(line," ");
//                        }
//                    }
//                    printf("%s",keylist[x].desc);
                    strcat(line,keylist[x].desc);
                } else {
                    wrap(line,60);
                    char dummy[5];
                    sprintf(dummy,"\n");
                    while (replace_str(line,dummy,"[NEWLINE]                                                 "));
                    while (replace_str(line,"[NEWLINE]",dummy));
                    if (file) {
                        fprintf(file,"%s",line);
                        fprintf(file,"\n");
                    }
//                    printf("%s",line);
//                    printf("\n");
                    str_clear=1;
                }
            }
            if (num==0 || (num>0 && keylist[x].code!=keylist[x-1].code && keylist[x].code!=0)) {
//                printf("Here 4 x=%d num=%d\n",x,num);
//                printf("%3d %-15s",x,keylist[x].name);
//                printf(" %7d",keylist[x].code);
//                printf(" %-21s",keylist[x].key);
//                    printf(" %s",keylist[x].desc);
                strcpy(line,keylist[x].desc);
                str_clear=0;
//                    strcat(line," ");
//                if (file) fprintf(file,"\n");
                if (file) fprintf(file,"%3d %-15s",x,keylist[x].name);
                if (file) fprintf(file," %7d",keylist[x].code);
                if (file) fprintf(file," %-21s",keylist[x].key);
//                    if (file) fprintf(file," %s",keylist[x].desc);
            }
        }

        if (str_clear==0) {
            wrap(line,60);
            char dummy[2];
            sprintf(dummy,"\n");
            while (replace_str(line,dummy,"[NEWLINE]                                                 "));
            while (replace_str(line,"[NEWLINE]",dummy));
            if (file) {
//                fprintf(file,"\n");
                fprintf(file,"%s",line);
//                fprintf(file,"\n");
            }
//            printf("%s",line);
//            printf("\n");
//            printf("\n");
        }


//        printf("\n");
        if (file) fprintf(file,"\n");
        if (file) {
            fclose(file);
            if (!(file=fopen("LIST.TXT","w"))) {
                printf("Can not open LIST.TXT FOR WRITING.\n");
                strcpy(error_msg4,"CAN NOT OPEN LIST.TXT FOR WRITING"); error_flag4=1;
            } else {
                fprintf(file,"MACRO.TXT\n");
                fclose(file);
                mytext.setFont(myfont2);
                mytext.setCharacterSize(16.0);
                ffmpegfile=0;
                sprite_from_ffmpeg.setScale(16.0,16.0);
//                parse_command("TEXT_FILES 30 0xFF00FFFF");
//                parse_command("SCRIPT \"../scripts/fun.chai\"");
//                parse_command("SCRIPT \"..\\scripts\\fun.chai\"");
//                parse_command("SCRIPT ..\\scripts\\fun.chai");
//                parse_command("SCRIPT ../scripts/fun.chai InPuT1 InPuT2");
//                parse_command("SCRIPT ../scripts/fun.chai");
//                char exe_string[200]=R"(EXECUTE print("Hello World\n");)";
//                parse_command(exe_string);
//                command(TEXT_FILES,"30","0xFF00FFFF");
                ffmpegfile=1;
                pen=1;
                pen_mode=2;
            }
        }
    } else {
        sprintf(error_msg4,"CANNOT LOAD KEYLIST.HPP"); error_flag4=1;
        printf("Can not load keylist.hpp (read_keylist_hpp() in commando.cpp\n");
        return;
    }

    return;
}

int trim(char * text)
{
   char blank[1000];
   int c = 0, d = 0;

   while (text[c] != '\0') {
      if (text[c] == ' ') {
         int temp = c + 1;
         if (text[temp] != '\0') {
            while (text[temp] == ' ' && text[temp] != '\0') {
               if (text[temp] == ' ') {
                  c++;
               }
               temp++;
            }
         }
      }
      if (text[c]!=' ') {
        blank[d] = text[c];
        d++;
      }
      c++;
   }

   blank[d] = '\0';

   strcpy(text,blank);

   return 0;
}

void parse_command(char * text) {
    char comlist[10][2000]={"","","","","","","","","",""};
    int found=0;
    int x;
    int counter;
    counter=sscanf(text, "%s %s %s %s %s %s %s %s %s %s", comlist[0],comlist[1],comlist[2],comlist[3],comlist[4],comlist[5],comlist[6],comlist[7],comlist[8],comlist[9]);
    for (x=0; x<num-1; x++) {
        char com[20];
        strcpy(com,keylist[x].name);
//        printf("comparing(\"%s\",\"%s\"\n",comlist[0],com);
        if ( strcmp(comlist[0],com)==0 ) {
            found=1;
            break;
        }
    }
    if (found) {
        if (keylist[x].code==EXECUTE) {
            char execute_string[10000]="";
//            std::string execute_string = (char*)comlist[1];
            sprintf(execute_string,"%s",&text[8]);
//            sprintf(execute_string, "%s",
  //                 R"(printf("hi\n");)" );

//            printf("execute_string=%s\n",execute_string);
//            printf("Executing command code %07d: %s\n",keylist[x].code,&text[8]);

//            chaiscript::ChaiScript chai;
//            chai.add(chaiscript::fun(&helloWorld), "helloWorld");
//  chai.eval(
//              R"(
//    puts("Hello World\n");
//  )"
//);
            run_chai(execute_string);
//            scripting();
//            chai.eval(execute_string);
        } else if (keylist[x].code==SCRIPT) {
            counter=0;
            std::string cmd = (char*)text;
            std::istringstream ss(cmd);
            std::string arg;
            std::list<std::string> ls;
            std::vector<char*> v;
            while (ss >> arg)
            {
               ls.push_back(arg);
               char * between=const_cast<char*>(ls.back().c_str());
               while (replace_str(between,"\"",""));
               v.push_back(const_cast<char*>(between));
                counter++;
            }
            v.push_back(0);  // need terminating null pointer
//            printf("counter=%d\n",counter);
            if (counter<1) {
                printf("No filename specified: %s\n",text);
            } else {
//                printf("Executing command code %07d: %s\n",keylist[x].code,text);
                scripting_file(v,counter);
            }
//            scripting_file(v[1]);
//            doscript(counter, &v[0]);
        } else {
/*
            for (x=1; x<counter; x++) {
               if (comlist[x][0]=='"') comlist[x][0]=' ';
               if (strlen(comlist[x])>0) {
                    if (comlist[x][strlen(comlist[x])-1]=='"') comlist[x][strlen(comlist[x])-1]=' ';
               }
            }
*/
            printf("counter=%d\n",counter);
            printf("Executing command code %07d: %s %s %s %s %s %s %s %s %s %s\n",keylist[x].code,comlist[0],comlist[1],comlist[2],comlist[3],comlist[4],comlist[5],comlist[6],comlist[7],comlist[8],comlist[9]);
            command_par(counter,keylist[x].code,comlist[1],comlist[2],comlist[3],comlist[4],comlist[5],comlist[6],comlist[7],comlist[8],comlist[9]);
        }
    } else {
        strcpy(error_msg4,"COMMAND NOT FOUND..."); error_flag4=1;
        printf("COMMAND NOT FOUND: %s\n",text);
    }
}

int stay_active=true;
int active_loaders=0;
int loader_index=0;
int loader_signal[150000];
void LOAD_ONE_IMAGE(size_t index);
extern bool burn;
extern int F2;

int count_ready_global=0;

struct image_loader {
    std::string filename;
    sf::Image* image;
    bool ready=false;
    bool ok=true;
    size_t index;
    sf::Thread *thread_pointer;
    std::string previous="";
//    sf::Thread image_thread;
};

std::vector<struct image_loader*> image_buffer;


int resize_image(sf::Image *imagebuffer, std::string &filename) {
    sf::Texture texture_buffer;
    int ret=imagebuffer->loadFromFile(filename.c_str());
    texture_buffer.loadFromImage(*imagebuffer);
    sf::RenderTexture rendertexture_buffer;
    rendertexture_buffer.create(texture_buffer.getSize().x/2.0,texture_buffer.getSize().y/2.0);
    sf::Sprite sprite_buffer;
    sprite_buffer.setTexture(texture_buffer,true);
    sprite_buffer.setScale(sf::Vector2f(0.5,0.5));
    sprite_buffer.setPosition(sf::Vector2f(0.0,0.0));
    sprite_buffer.setOrigin(sf::Vector2f(0.0,0.0));
    texture_buffer.setSmooth(true);
    rendertexture_buffer.setSmooth(true);
    rendertexture_buffer.draw(sprite_buffer);
    rendertexture_buffer.display();
    *imagebuffer=rendertexture_buffer.getTexture().copyToImage();
    return ret;
}


int wait_for_all_loaded() {
    bool all_ready=1;
    int count_ready=0;
    int count_not_exist=0;
    int count_error_loading=0;
//    printf("\r");
//    for (auto u : image_buffer) {
    for (int m=0; m<loader_index; m++) {
        if (image_buffer[m]->ready) {
//        if (u->ready) {
            count_ready++;
            if (image_buffer[m]->ok) {
//            if (u->ok) {
//                    printf("!"); //ready and loaded and ok
            } else {
                all_ready=-1;
                printf("E"); //ready and error loading
                count_error_loading++;
            }
        } else {
            if (image_buffer[m]->ok) {
//            if (u->ok) {
//                printf("L"); //not ready-loading
                if (all_ready==1) all_ready=0;
            } else {
                static int hop=0;
                hop++;
                count_not_exist++;
                all_ready=-2;
                if (hop>50) {
                    printf("X");//file does not exists/not ready (should not occur often...)
                }
            }
        }
    }
//    if (all_ready==0)
//        if (!burn && F2==1) printf("#ready=%d/%d ",count_ready,loader_index);
//    else
//        if (!burn && F2==1) printf("#ready=%d/%d ",count_ready,loader_index);
    if (count_not_exist) {
        printf("                                              #not exist=%d",count_not_exist);
        return 1;//just fok it. Bill Gates corrupts everything through his updates, motherfokking bastard insane psyco....

    }
    if (count_error_loading) {
        printf("                                              #error loading=%d",count_error_loading);
        return 1;//just fok it.
    }
    count_ready_global=count_ready;
    return all_ready;
//    return all_ready;
};

int sharp=false;
extern bool file_exists(const char * filename);
extern bool file_exists3(const char * filename);

void LOAD_ONE_IMAGE(size_t index) {
//    printf("index=%d Thread started. filename=%s\n",index,image_buffer[index].filename.c_str());
    int first=1;
    while (stay_active==true) {
        char fn[2000];

        strcpy(fn,image_buffer[index]->filename.c_str());

        replace_string(fn,"png","jpg");
        replace_string(fn,"bmp","jpg");

        image_buffer[index]->filename=std::string() + fn;

        if (!file_exists(image_buffer[index]->filename.c_str())) {
            bool f_ok=false;
//            strcpy(fn,image_buffer[index]->filename.c_str());
//            printf("\nfn[strlen(fn)-3]=%c",fn[strlen(fn)-3]);
//            printf("\nfn[strlen(fn)-2]=%c",fn[strlen(fn)-2]);
//            printf("\nfn[strlen(fn)-1]=%c\n",fn[strlen(fn)-1]);
            sleep(sf::seconds(10));
            if (strlen(fn)>4) {
                fn[strlen(fn)-3]='b';
                fn[strlen(fn)-2]='m';
                fn[strlen(fn)-1]='p';
                if (!file_exists(fn)) {
                    fn[strlen(fn)-3]='p';
                    fn[strlen(fn)-2]='n';
                    fn[strlen(fn)-1]='g';
                    if (!file_exists(fn)) {
                        fn[strlen(fn)-3]='j';
                        fn[strlen(fn)-2]='p';
                        fn[strlen(fn)-1]='g';
                        if (file_exists(fn)) f_ok=true;
                    } else f_ok=true;
                } else f_ok=true;
            }
            if (f_ok) image_buffer[index]->filename=fn;
        }

        if (image_buffer[index]->previous==image_buffer[index]->filename) {
//            printf("\rSAME FILE!!! NOT LOADING -> %s\n",image_buffer[index]->previous.c_str());
            image_buffer[index]->ready=true;
        } else if (!file_exists(image_buffer[index]->filename.c_str())) {
            printf("\nindex=%d Cannot find file on disk: %s\n",index,image_buffer[index]->filename.c_str());
            image_buffer[index]->ok=false;
        } else {
            if (first==1) {
//                printf("index=%d File exists / first run Sleeping for 30 seconds before loading %s\n",index,image_buffer[index]->filename.c_str());
                while (batch_load==0) sf::sleep(sf::milliseconds(10));
//                printf("index=%d Waking up after first run. Now loading filename=%s\n",index,image_buffer[index]->filename.c_str());
            } else {
//                printf("index=%d File exists / loading now: s%s\n",index,image_buffer[index]->filename.c_str());
                while (batch_load==0) sf::sleep(sf::milliseconds(10));
            }
            if (index>=NUMBER_OF_SIMULTANIOUS_ACTIVE_THREADS) {
                while (!image_buffer[index-NUMBER_OF_SIMULTANIOUS_ACTIVE_THREADS]->ready && stay_active==true) sf::sleep(sf::milliseconds(30));
            }
            if (stay_active==true) {
//                image_buffer[index]->ok=image_buffer[index]->image.loadFromFile(image_buffer[index]->filename.c_str());
                image_buffer[index]->ok=image_buffer[index]->image->loadFromFile(image_buffer[index]->filename.c_str());
//                image_buffer[index]->ok=resize_image(image_buffer[index]->image,image_buffer[index]->filename);
                if (!image_buffer[index]->ok)
                    printf("\nindex=%d Error loading file: %s\n",index,image_buffer[index]->filename.c_str());
                else
                image_buffer[index]->previous = image_buffer[index]->filename;
                image_buffer[index]->ready=true;
            }
        }
        first=0;
//        printf("index=%d Ready. Staying active, waiting for signal\n");
        while (loader_signal[index]==0 && stay_active==true) {
                if (!sharp) sf::sleep(sf::seconds(1.0));
                else sf::sleep(sf::seconds(0.1));
        }
        loader_signal[index]=0;
        if (stay_active==true) {
//            printf("index=%d signal->NEW JOB!!! Got signal..... New file:%s\n",index,image_buffer[index]->filename.c_str());
        } else if (stay_active==false) {
//            printf("index=%d stay_active->Unloading...bye\n",index);
        }
    }
}

void push_image_file(std::string filename) {
    size_t index=image_buffer.size();
    sharp=true;
//    struct image_loader* image_loader_struct_pointer = new image_loader;
//    sf::Thread* thread_pointer = new sf::Thread(&LOAD_ONE_IMAGE,index);

    if (loader_index>=index) {
        struct image_loader* image_loader_struct_pointer = new image_loader;

//        sf::Thread* thread_pointer = new sf::Thread(&LOAD_ONE_IMAGE,index);
//        image_loader_struct_pointer->thread_pointer=thread_pointer;
        image_loader_struct_pointer->image = new sf::Image;
        image_loader_struct_pointer->thread_pointer = new sf::Thread(&LOAD_ONE_IMAGE,index);

        image_loader_struct_pointer->filename=filename;
        image_loader_struct_pointer->ready=false;
        image_loader_struct_pointer->ok=true;
        loader_signal[loader_index]=0;
        image_buffer.push_back(image_loader_struct_pointer);
//        printf("index=%d loaderindex=%d index=%d First launching: filename=%s\n",loader_index,index,image_buffer.size()-1,filename.c_str());
        image_buffer[image_buffer.size()-1]->thread_pointer->launch();
//        thread_pointer->launch();
//        printf("index=%d First launched: size=%d filename=%s\n",index,image_buffer.size(),filename.c_str());
    } else {
//        printf("index=%d re-Launching: filename=%s\n",loader_index,filename.c_str());
        if (image_buffer[loader_index]->image == NULL)
            image_buffer[loader_index]->image = new sf::Image;
        image_buffer[loader_index]->filename=filename;
        image_buffer[loader_index]->ready=false;
        image_buffer[loader_index]->ok=true;
//        loader_signal[loader_index]=0;
//        image_buffer[loader_index]->previous="";
//        image_buffer[loader_index]->thread_pointer->launch();
//        printf("index=%d re-Launched: size=%d filename=%s\n",index,image_buffer.size(),filename.c_str());
        loader_signal[loader_index]=1;
    }
    loader_index++;
//    printf("index=%d loader_index=%d First launched: image_buffer.size=%d filename=%s\n",index,loader_index,image_buffer.size(),filename.c_str());
}

void clear_image_buffer() {
//    printf("Clearing image buffer\n");
    loader_index=0;
    sharp=false;
    batch_load=0;
//    stay_active=false;
    for (int m=0; m<image_buffer.size(); m++) {
//        image_buffer[m]->thread_pointer->wait();
//        printf("deleting thread=%u\n",image_buffer[m]->thread_pointer);
//        printf("deleting image_loader=%u\n",image_buffer[m]);
//        delete image_buffer[m]->thread_pointer;
//        image_buffer[m]->image->~Image();
        delete image_buffer[m]->image;
        image_buffer[m]->image = NULL;
        image_buffer[m]->previous="";
        image_buffer[m]->filename="";
//        delete image_buffer[m];
    }
//    image_buffer.clear();
//    for (auto u : image_buffer) {
//        u->ok=true;
//        u->ready=false;
//            u->filename="";
//    }
//    image_buffer.clear();
//    printf("\nimage_buffer.size()=%d\n",image_buffer.size());
    active_loaders=0;
//    image_buffer.clear();
//    sf::sleep(sf::seconds(0.25));
}

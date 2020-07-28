
void do_the_recording_stuff_window(sf::RenderWindow& window, int win_num)
{
    blocked_by_window=1;

    if (record_screen==1)
    {
        fpstime=fpstime_factor*(float)record_screen_num*(float)rate/60.0;
    }

    if (record_screen==1)
    {
        if (record_pause==0)
        {
            flop++;
            if (flop==rate)
                flop=0;
            /*
                        if (flop==0)
                            flop=1;
                        else
                            flop=0;
            */
            if (flop==0)
            {
                if (recording_type==0)
                {
                    Screenshot3_window(window);
                    record_screen_num++;
                }
            }
        }
    }
}
extern int reload_init();
extern int end_on_record;
extern int sound_counter;
extern sf::Clock clock_ghost;
extern int burn_subs;
extern int texture_ready;
extern int isrecording;
extern int recording_start(int x, int y);
extern int error_msg;
extern void recording_end();
sf::Mutex window_recording;


void handle_key_window(sf::Event event, int win_num, sf::RenderWindow& window) {
    window_recording.lock();
    recording_type=0;
    switch(event.key.code)
    {
    case sf::Keyboard::R:
        if (event.key.shift) {
            if (record_window) {
                if (record_pause==1) record_pause=0;
                else record_pause=0;
            } else {
                printf("Not recording...\n");
                blocked_by_window=1;
                reload_init();
                record_screen=1;
                record_window=1;
                play_rate=1;
                end_on_record=0;
                sound_counter=0;
                record_screen_num=0;
                if (recording_start(window.getSize().x,window.getSize().y)!=0)
                {
                    printf("RECORDING_START() FAILED");
                    record_screen=0;
                    record_window=0;
                }
                else
                {
                    flop=0;
                    rate_count=play_rate-1;
//                    record_pause=1;
                    window.setVerticalSyncEnabled(false);
                }
                record_pause=1;
            }
        } else {
            if (record_screen==0)
            {
                blocked_by_window=1;
                reload_init();
                record_screen=1;
                record_window=1;
                play_rate=1;
                end_on_record=0;
                sound_counter=0;
            }
            else
            {
                blocked_by_window=0;
                record_screen=0;
                record_window=0;
                play_rate=1;
                record_pause=0;
                clock_ghost.restart();
                burn_subs=0;
                texture_ready=0;
                isrecording=0;
    //            the_time=0.0;
            }

            if (record_screen==1)
            {
                if (recording_type==0)
                {
                    record_screen_num=0;
                    if (recording_start(window.getSize().x,window.getSize().y)!=0)
                    {
                        printf("RECORDING_START() FAILED");
                        record_screen=0;
                        record_window=0;
                    }
                    else
                    {
                        flop=0;
                        rate_count=play_rate-1;
    //                    record_pause=1;
                        window.setVerticalSyncEnabled(false);
                    }
                }
                else if (recording_type==1)
                {
                    printf("Recording type not available. Press 'R' to select.");
                }
            }
            else
            {
                if (sync_window[win_num]==1)
                    window.setVerticalSyncEnabled(true);
                else
                    window.setVerticalSyncEnabled(false);
                record_screen=0;
                record_window=0;
                record_pause=0;
                sf::sleep(sf::microseconds(100));
                Screenshot3_window(window);
                printf("FLUSHING RECORD PIPE...");
    //            window.display();

                if (recording_type==0)
                    recording_end();
            }
            break;
        }
    }
    window_recording.unlock();
}


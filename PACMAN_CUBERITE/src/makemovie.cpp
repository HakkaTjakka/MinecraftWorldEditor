#define SFML_STATIC
#undef UNICODE
#include <SFML/Graphics/Image.hpp>
#include <stdint.h>


#define __STDC_CONSTANT_MACROS
#define __STDC_LIMIT_MACROS

extern "C"{
//#include <x264.h>
#include <libswscale/swscale.h>
#include <libavcodec/avcodec.h>
#include <libavutil/mathematics.h>
#include <libavformat/avformat.h>
#include <libavutil/opt.h>
}

extern void savedata(char *naam, int data);


char *fmtext="mp4";
char filename[200];

AVOutputFormat * fmt;
AVFormatContext *oc;

AVStream * stream;
AVCodec *codec;
AVCodecContext *c;
int ret;
AVFrame *rgbpic, *yuvpic;
AVDictionary* opt;


struct SwsContext* convertCtx=nullptr;


int makemovie_init() {
    printf("start\n");
    av_register_all(); // Loads the whole database of available codecs and formats.
    avcodec_register_all();
//    avdevice_register_all();


    convertCtx = sws_getCachedContext(convertCtx,1920, 1080, (::PixelFormat) AV_PIX_FMT_RGB24, 1920, 1080, (::PixelFormat) AV_PIX_FMT_YUV420P, SWS_FAST_BILINEAR, nullptr, nullptr, nullptr); // Preparing to convert my generated RGB images to YUV frames.

    sprintf(filename, "GeneratedVideo.%s", fmtext);

    fmt = av_guess_format(fmtext, NULL, NULL);
    oc = NULL;

    avformat_alloc_output_context2(&oc, NULL, NULL, filename);


    stream = avformat_new_stream(oc, 0);
    codec=NULL;
    c= NULL;

    printf("avcodec_find_encoder_by_name\n");
//    codec = avcodec_find_encoder(CODEC_ID_H264);
//    codec = avcodec_find_encoder(AV_CODEC_ID_H264);
//    codec = avcodec_find_encoder(AV_CODEC_ID_MP4ALS);
    codec = avcodec_find_encoder(AV_CODEC_ID_MPEG4);

//    codec = avcodec_find_encoder_by_name("h.264");

    if (codec==nullptr) return -1;
//    codec = avcodec_find_encoder_by_name("libx264");

    printf("hier 1\n");

    // Setting up the codec:
    opt = NULL;
    av_dict_set( &opt, "preset", "slow", 0 );
    av_dict_set( &opt, "crf", "20", 0 );
    av_dict_set( &opt,"framerate","60",0 );
    avcodec_get_context_defaults3(stream->codec, codec);
    c=avcodec_alloc_context3(codec);
    c->width = 1920;
    c->height = 1080;
    c->pix_fmt = AV_PIX_FMT_YUV420P;

    printf("hier 2\n");

    // Setting up the format, its stream(s), linking with the codec(s) and write the header:
    if (oc->oformat->flags & AVFMT_GLOBALHEADER) // Some formats require a global header.
        c->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
    avcodec_open2( c, codec, &opt );
    av_dict_free(&opt);
    stream->time_base=(AVRational){1, 25};
    stream->codec=c; // Once the codec is set up, we need to let the container know which codec are the streams using, in this case the only (video) stream.
    av_dump_format(oc, 0, filename, 1);
    avio_open(&oc->pb, filename, AVIO_FLAG_WRITE);
    ret=avformat_write_header(oc, &opt);
    av_dict_free(&opt);

    printf("hier 3\n");

    // Preparing the containers of the frame data:

    // Allocating memory for each RGB frame, which will be lately converted to YUV:
    rgbpic=av_frame_alloc();
    rgbpic->format=AV_PIX_FMT_RGB24;
    rgbpic->width=1920;
    rgbpic->height=1080;
    ret=av_frame_get_buffer(rgbpic, 1);

    printf("hier 4\n");

    // Allocating memory for each conversion output YUV frame:
    yuvpic=av_frame_alloc();
    yuvpic->format=AV_PIX_FMT_YUV420P;
    yuvpic->width=1920;
    yuvpic->height=1080;
    ret=av_frame_get_buffer(yuvpic, 1);

    // After the format, code and general frame data is set, we write the video in the frame generation loop:
    // std::vector<uint8_t> B(width*height*3);
    printf("hier 5\n");
    return 0;
}

int got_output;
AVPacket pkt;
int i,N;
int x,y;

void makemovie_frame(sf::Image image,int i) {
        savedata("makemovie_frame() start",0);

//        generateframe(B, i); // This one is the function that generates a different frame for each i.
        // The AVFrame data will be stored as RGBRGBRGB... row-wise, from left to right and from top to bottom, hence we have to proceed as follows:
        sf::Color color;
        for (y=0; y<1080; y++)
        {
            for (x=0; x<1920; x++)
            {
                color=image.getPixel(x,y);
                // rgbpic->linesize[0] is equal to width.
                rgbpic->data[0][y*rgbpic->linesize[0]+3*x]=color.r;
                rgbpic->data[0][y*rgbpic->linesize[0]+3*x+1]=color.g;
                rgbpic->data[0][y*rgbpic->linesize[0]+3*x+2]=color.b;
            }
        }

        savedata("makemovie_frame()",1);

        sws_scale(convertCtx, rgbpic->data, rgbpic->linesize, 0, 1080, yuvpic->data, yuvpic->linesize); // Not actually scaling anything, but just converting the RGB data to YUV and store it in yuvpic.
        savedata("makemovie_frame()",2);
        av_init_packet(&pkt);
        pkt.data = NULL;
        pkt.size = 0;
        yuvpic->pts = i; // The PTS of the frame are just in a reference unit, unrelated to the format we are using. We set them, for instance, as the corresponding frame number.
        savedata("makemovie_frame() 2.1 ",2);
        ret=avcodec_encode_video2(c, &pkt, yuvpic, &got_output);
        savedata("makemovie_frame()",3);
        if (got_output)
        {
            savedata("makemovie_frame()",4);
            fflush(stdout);
            av_packet_rescale_ts(&pkt, (AVRational){1, 25}, stream->time_base); // We set the packet PTS and DTS taking in the account our FPS (second argument) and the time base that our selected format uses (third argument).
            savedata("makemovie_frame()",5);
            pkt.stream_index = stream->index;
            printf("Write frame %6d (size=%6d)\n", i, pkt.size);
            savedata("makemovie_frame()",6);
            av_interleaved_write_frame(oc, &pkt); // Write the encoded frame to the mp4 file.
            savedata("makemovie_frame()",7);
            av_packet_unref(&pkt);
        }

        savedata("makemovie_frame() end",0);
}

// Writing the delayed frames:
void makemovie_end(int i) {
     savedata("makemovie_end() start",0);
    for (got_output = 1; got_output; i++) {
        ret = avcodec_encode_video2(c, &pkt, NULL, &got_output);
        if (got_output) {
            fflush(stdout);
            av_packet_rescale_ts(&pkt, (AVRational){1, 25}, stream->time_base);
            pkt.stream_index = stream->index;
            printf("Write frame %6d (size=%6d)\n", i, pkt.size);
            av_interleaved_write_frame(oc, &pkt);
            av_packet_unref(&pkt);
        }
    }
    av_write_trailer(oc); // Writing the end of the file.
    if (!(fmt->flags & AVFMT_NOFILE))
        avio_closep(&oc->pb); // Closing the file.
    avcodec_close(stream->codec);
    // Freeing all the allocated memory:
    sws_freeContext(convertCtx);
    av_frame_free(&rgbpic);
    av_frame_free(&yuvpic);
    avformat_free_context(oc);
    savedata("makemovie_end() end",0);
}

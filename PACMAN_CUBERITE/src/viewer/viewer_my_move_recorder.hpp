
float playbackspeed=0.015;

FILE* movement_file=NULL;
extern int extra_octants;
//extern bool show_text;
extern int GET_LAT_LON_FROM_FILE_LIST(char *naam);

extern bool MAKE_NBT;

void start_view(FILE* file, char* filename) {
//    fclose(file);
    if (file_exists("playbackspeed.txt")) {
        FILE* pbs=fopen("playbackspeed.txt","r");
        char line[100];
        fgets(line,100,pbs);
        fclose(pbs);
        while (replace_str(line,",","."));
        sscanf(line,"%f",&playbackspeed);
        printf("playbackspeed set to %f\n",playbackspeed);
    }

    splines_loaded=false;
    char command[2000];
    sprintf(command,"del %s","markers_copy.txt");
    system(command);
    sprintf(command,"copy %s %s",filename,"markers_copy.txt");
    printf(command); printf("\n");
    system(command);
    if (movement_file==NULL) movement_file = fopen ("markers_copy.txt", "r"); //otherwise continue...???
//    file = fopen (filename, "a"); //reopen, continue marking...
    interpolate_spline(0); //start
}


void stop_view() {
//    fclose(movement_file);
    movement_file=NULL;
    interpolate_on=false;
    set_end_of_movement=false;
}

float int_q[4];
float int_e[3];
float int_l[3];
float int_t[3];
float int_p[4];
float int_bmin[3];
float int_bmax[3];
float int_arr[19];
int int_frustum_toggle;

extern int mirror;

void get_view(float &rotate_object_x, float &rotate_object_y, float &rotate_object_z, float curr_quat2[4],float eye2[3],float lookat2[3],float translation[3],float perspective[4],float bmin[3],float bmax[3], int& frustum_toggle) {
    curr_quat2[0]=int_q[0]; eye2[0]=int_e[0]; lookat2[0]=int_l[0]; translation[0]=int_t[0]; perspective[0]=(float)int_p[0];    //angle.
    curr_quat2[1]=int_q[1]; eye2[1]=int_e[1]; lookat2[1]=int_l[1]; translation[1]=int_t[1]; //perspective[1]=(float)int_l[1]; don't use...
    curr_quat2[2]=int_q[2]; eye2[2]=int_e[2]; lookat2[2]=int_l[2]; translation[2]=int_t[2]; //perspective[2]=(float)int_l[2]; don't use...
    curr_quat2[3]=int_q[3];                                                                 //perspective[3]=(float)int_l[3]; don't use...
//kloten
    if (area!="Models") {
//        RECALC_BMIN_BMAX(buffers, bmin,bmax, 0.0, 0.0);
        bmin[0]=int_bmin[0]; bmin[1]=int_bmin[1]; bmin[2]=int_bmin[2];
        bmax[0]=int_bmax[0]; bmax[1]=int_bmax[1]; bmax[2]=int_bmax[2];
    }
    frustum_toggle=int_frustum_toggle;
    rotate_object_x=int_arr[16];
    rotate_object_y=int_arr[17];
    rotate_object_z=int_arr[18];
//    if (set_end_of_movement) {
//        interpolate_on=false;
//        movement_file=NULL;
//        set_end_of_movement=false;
//    }
}

int getnext_movement(char *naam);


/*
This work by Ryan Muller released under the Creative Commons CC0 License
http://creativecommons.org/publicdomain/zero/1.0/
*/

/*
  Spline interpolation of a parametric function.
  INPUT: std::vector<double> x
        A list of double values that represent sampled
        points. The array index of each point will be
        taken as the parameter t by which x will be
        represented as a function.
  OUTPUT: std::vector<cv::Vec4d> P
        A list of cv::Vec4d representing polynomials. To
        interpret segment [i]:
        x(t) =  P0*a + P1*b + P2*(a^3-a)/6 + P3*(b^3-b)/6
        where a = t-i
              b = i-t+1
  */

void splinterp(std::vector<cv::Vec4d>& out,std::vector<double> x){

//    std::vector<cv::Vec4d> out;

    // spline size
    int n=x.size();

    // loop counter
    int i;

    // working variables
    double p;
    std::vector<double> u;

    // second derivative
    std::vector<double> z;

    u.resize(n+1);
    z.resize(n+1);

    // set the second derivative to 0 at the ends
    z[0] = u[0] = 0;
    z[n] = 0;
    u[n] = 0;
//    z[n-1] = 0;
//    u[n-1] = 0;

    // decomposition loop
    for(i=1;i<n-1;i++){
//    for(i=1;i<n;i++){
        p = 0.5*z[i-1] + 2.0;
        z[i] = -0.5/p;
        u[i] = x[i+1]+x[i-1]-2*x[i];
        u[i] = (3*u[i]-0.5*u[i-1])/p;
    }

    // back-substitution loop
//    for(i=n-2;i>0;i--){
//    z[n-1] = u[n-1];
    for(i=n-1;i>0;i--){
        z[i] = z[i] * z[i+1] + u[i];
    }

//    for(i=n-1;i>0;i--){
//        z[i] = z[i] * z[i+1] + u[i];
//    }

    for(i=0;i<n-1;i++){
        out.push_back(cv::Vec4d(
                          x[i+1],
                          x[i],
                          z[i+1],
                          z[i]
                          ));
    }

//    return out;

}

double splinterpEval( std::vector<cv::Vec4d> spline, double t );

/**
  A demo of Splinterp's capabilities.
  Modify the function in the for loop to change
  the sample points. When you run the program
  it will generate a polynomial for each segment
  and output it in text format. Copy and paste
  the output into WxMaxima (andrejv.github.com/wxmaxima/)
  to see a plot of your interpolated curves!
  */
void splinterpDemo(){

    std::vector<double> samples;
    std::vector<cv::Vec4d> spline;
    cv::Vec4d p;
    double x;
    unsigned int i, imax=12;

    for(i=0;i<imax;i++){
        // modify this function
        x = (cos(2*M_PI*i/(imax-1)));
        samples.push_back(x);
    }

    splinterp(spline , samples);

    for( double t=0 ; t<=(imax-1) ; t+=0.2 ) {
        printf( "x_%f = %f\n", t, splinterpEval( spline, t ) );
    }

    for(i=0;i<spline.size();i++){
        p = spline.at(i);
        printf("x%d(t):= if t>= %d and t<=%d then %.8f * (t-%d) + %.8f * (%d-t) + "
               "%.8f * ((t-%d)^3-(t-%d))/6 + %.8f * ((%d-t)^3-(%d-t))/6 $\n",
               i,i,i+1,p[0],i,p[1],i+1,p[2],i,i,p[3],i+1,i+1);
    }
    printf("wxplot2d([");
    for(i=0;i<spline.size();i++){
        if(i>0) std::cout << ",";
        printf("x%d(t)",i);
    }
    printf("],[t,0,%d],[gnuplot_preamble,\"set nokey;\"])$\n",spline.size());
}




//x(t) = P0_a + P1_b + P2_(a^3-a)/6 + P3_(b^3-b)/6
//where a = t-i
// b = i-t+1



double splinterpEval( std::vector<cv::Vec4d> spline, double t ) {
    int i = (int) floor(t);
    if (i>=spline.size() ) { //&& t==(double)i
//        t=t-t/1000000000.0;
        i=i-1-(i-spline.size());
    }
    if( i>=0 && i<spline.size() ) {
        double a = t - i;
        double b = i - t + 1;
        cv::Vec4d p = spline.at(i);
        double x_t = p[0]*a + p[1]*b + p[2]*(a*a*a-a)/6.0 + p[3]*(b*b*b-b)/6.0;
        return x_t;
    }
    else
    {
        printf( "Cannot Eval Spline out of range at t=%f\n",t );
    }
}




void interpolate_spline(int what) {
    static bool loop_end=false;
    static int cnt;
    static double starting=0.0;
    static char line[4096];
    static int c=0;
    static char calc[4096];
    static char store[4096];
//    static char fline[4096];
//    static char fline2[4096];

    //static keep data for ...
    static std::vector<double> s_q0; static std::vector<double> s_e0; static std::vector<double> s_l0; static std::vector<double> s_t0; static std::vector<double> s_p0;
    static std::vector<double> s_q1; static std::vector<double> s_e1; static std::vector<double> s_l1; static std::vector<double> s_t1;
    static std::vector<double> s_q2; static std::vector<double> s_e2; static std::vector<double> s_l2; static std::vector<double> s_t2;
    static std::vector<double> s_q3;
    static std::vector<double> s_bmin0; static std::vector<double> s_bmax0;
    static std::vector<double> s_bmin1; static std::vector<double> s_bmax1;
    static std::vector<double> s_bmin2; static std::vector<double> s_bmax2;
    static std::vector<double> s_r0; static std::vector<double> s_r1; static std::vector<double> s_r2; static std::vector<double> s_r3;
    static std::vector<double> s_r4; static std::vector<double> s_r5; static std::vector<double> s_r6; static std::vector<double> s_r7;
    static std::vector<double> s_r8; static std::vector<double> s_r9; static std::vector<double> s_r10; static std::vector<double> s_r11;
    static std::vector<double> s_r12; static std::vector<double> s_r13; static std::vector<double> s_r14; static std::vector<double> s_r15;
    static std::vector<double> s_r16; static std::vector<double> s_r17; static std::vector<double> s_r18;
    static std::vector<int> s_frustum_toggle;

    static std::vector<cv::Vec4d> sp_q0; static std::vector<cv::Vec4d> sp_e0; static std::vector<cv::Vec4d> sp_l0; static std::vector<cv::Vec4d> sp_t0; static std::vector<cv::Vec4d> sp_p0;
    static std::vector<cv::Vec4d> sp_q1; static std::vector<cv::Vec4d> sp_e1; static std::vector<cv::Vec4d> sp_l1; static std::vector<cv::Vec4d> sp_t1;
    static std::vector<cv::Vec4d> sp_q2; static std::vector<cv::Vec4d> sp_e2; static std::vector<cv::Vec4d> sp_l2; static std::vector<cv::Vec4d> sp_t2;
    static std::vector<cv::Vec4d> sp_q3;
    static std::vector<cv::Vec4d> sp_bmin0; static std::vector<cv::Vec4d> sp_bmax0;
    static std::vector<cv::Vec4d> sp_bmin1; static std::vector<cv::Vec4d> sp_bmax1;
    static std::vector<cv::Vec4d> sp_bmin2; static std::vector<cv::Vec4d> sp_bmax2;
    static std::vector<cv::Vec4d> sp_r0; static std::vector<cv::Vec4d> sp_r1; static std::vector<cv::Vec4d> sp_r2; static std::vector<cv::Vec4d> sp_r3;
    static std::vector<cv::Vec4d> sp_r4; static std::vector<cv::Vec4d> sp_r5; static std::vector<cv::Vec4d> sp_r6; static std::vector<cv::Vec4d> sp_r7;
    static std::vector<cv::Vec4d> sp_r8; static std::vector<cv::Vec4d> sp_r9; static std::vector<cv::Vec4d> sp_r10; static std::vector<cv::Vec4d> sp_r11;
    static std::vector<cv::Vec4d> sp_r12; static std::vector<cv::Vec4d> sp_r13; static std::vector<cv::Vec4d> sp_r14; static std::vector<cv::Vec4d> sp_r15;
    static std::vector<cv::Vec4d> sp_r16; static std::vector<cv::Vec4d> sp_r17; static std::vector<cv::Vec4d> sp_r18;


    if (what==0) {
        loop_end=false;
        s_q0.clear(); s_e0.clear(); s_l0.clear(); s_t0.clear(); s_p0.clear();
        s_q1.clear(); s_e1.clear(); s_l1.clear(); s_t1.clear();
        s_q2.clear(); s_e2.clear(); s_l2.clear(); s_t2.clear();
        s_q3.clear();
        s_bmin0.clear(); s_bmax0.clear();
        s_bmin1.clear(); s_bmax1.clear();
        s_bmin2.clear(); s_bmax2.clear();
        s_frustum_toggle.clear();
        s_r0.clear(); s_r1.clear(); s_r2.clear(); s_r3.clear();
        s_r4.clear(); s_r5.clear(); s_r6.clear(); s_r7.clear();
        s_r8.clear(); s_r9.clear(); s_r10.clear(); s_r11.clear();
        s_r12.clear(); s_r13.clear(); s_r14.clear(); s_r15.clear();
        s_r16.clear(); s_r17.clear(); s_r18.clear();

        sp_q0.clear(); sp_e0.clear(); sp_l0.clear(); sp_t0.clear(); sp_p0.clear();
        sp_q1.clear(); sp_e1.clear(); sp_l1.clear(); sp_t1.clear();
        sp_q2.clear(); sp_e2.clear(); sp_l2.clear(); sp_t2.clear();
        sp_q3.clear();
        sp_bmin0.clear(); sp_bmax0.clear();
        sp_bmin1.clear(); sp_bmax1.clear();
        sp_bmin2.clear(); sp_bmax2.clear();
        sp_r0.clear(); sp_r1.clear(); sp_r2.clear(); sp_r3.clear();
        sp_r4.clear(); sp_r5.clear(); sp_r6.clear(); sp_r7.clear();
        sp_r8.clear(); sp_r9.clear(); sp_r10.clear(); sp_r11.clear();
        sp_r12.clear(); sp_r13.clear(); sp_r14.clear(); sp_r15.clear();
        sp_r16.clear(); sp_r17.clear(); sp_r18.clear();

        c=0;
        bool first=true;
        bool second=false;
        while (fgets (line,4096, movement_file)!=NULL ) {
            while (replace_str(line,",","."));
            sscanf(line,"QUATS=%e %e %e %e EYE=%e %e %e LOOKAT=%e %e %e TRANSLATION=%e %e %e PERSPECTIVE=%e %e %e %e BMIN=%e %e %e BMAX=%e %e %e FRUSTUM=%d MATRIX=%e %e %e %e %e %e %e %e %e %e %e %e %e %e %e %e ROTATION=%e %e %e\n",
                &int_q[0], &int_q[1], &int_q[2], &int_q[3],
                &int_e[0], &int_e[1], &int_e[2],
                &int_l[0], &int_l[1], &int_l[2],
                &int_t[0], &int_t[1], &int_t[2],
                &int_p[0], &int_p[1], &int_p[2], &int_p[3],
                &int_bmin[0], &int_bmin[1], &int_bmin[2],
                &int_bmax[0], &int_bmax[1], &int_bmax[2], &int_frustum_toggle,
                &int_arr[0], &int_arr[1], &int_arr[2], &int_arr[3],
                &int_arr[4], &int_arr[5], &int_arr[6], &int_arr[7],
                &int_arr[8], &int_arr[9], &int_arr[10], &int_arr[11],
                &int_arr[12], &int_arr[13], &int_arr[14], &int_arr[15],
                &int_arr[16],&int_arr[17],&int_arr[18]);

            printf("LOAD:c=%d t=%-+f q0=%-+f q1=%-+f q2=%-+f q3=%-+f  e0=%-+f e1=%-+f e2=%-+f  l0=%-+f l1=%-+f l2=%-+f  t0=%-+f t1=%-+f t2=%-+f  p0=%-+f  bmin=%-+f %-+f %-+f  bmax=%-+f %-+f %-+f  frustum=%d r0=%-+f r1=%-+f r2=%-+f r3=%-+f r4=%-+f r5=%-+f r6=%-+f r7=%-+f r8=%-+f r9=%-+f r10=%-+f r11=%-+f r12=%-+f r13=%-+f r14=%-+f r15=%-+f ROTATION=%-+f %-+f %-+f\n",c,starting,
                    int_q[0],int_q[1],int_q[2],int_q[3],
                    int_e[0],int_e[1],int_e[2],
                    int_l[0],int_l[1],int_l[2],
                    int_t[0],int_t[1],int_t[2],
                    int_p[0],
                    int_bmin[0], int_bmin[1], int_bmin[2],
                    int_bmax[0], int_bmax[1], int_bmax[2], int_frustum_toggle,
                    (float)int_arr[0],(float)int_arr[1],(float)int_arr[2],(float)int_arr[3],
                    (float)int_arr[4],(float)int_arr[5],(float)int_arr[6],(float)int_arr[7],
                    (float)int_arr[8],(float)int_arr[9],(float)int_arr[10],(float)int_arr[11],
                    (float)int_arr[12],(float)int_arr[13],(float)int_arr[14],(float)int_arr[15],
                    (float)int_arr[16],(float)int_arr[17],(float)int_arr[18]);

/*
            if (second) {
                strcpy(fline2,line);
                second=false;
            }
            if (first) {
                strcpy(fline,line);
                first=false;
                second=true;
            }
*/

/*
            fgets (line,2000, movement_file);
            while (replace_str(line,",","."));
            sscanf(line,"MATRIX=%e %e %e %e %e %e %e %e %e %e %e %e %e %e %e %e %e\n",
                &int_arr[0], &int_arr[1], &int_arr[2], &int_arr[3],
                &int_arr[4], &int_arr[5], &int_arr[6], &int_arr[7],
                &int_arr[8], &int_arr[9], &int_arr[10], &int_arr[11],
                &int_arr[12], &int_arr[13], &int_arr[14], &int_arr[15], &int_arr[16]);
            printf("LOAD:c=%d t=%-+f r0=%-+f r1=%-+f r2=%-+f r3=%-+f r4=%-+f r5=%-+f r6=%-+f r7=%-+f r8=%-+f r9=%-+f r10=%-+f r11=%-+f r12=%-+f r13=%-+f r14=%-+f r15=%-+f ROTATION_Z=%-+f\n",c,starting,
                    (float)int_arr[0],(float)int_arr[1],(float)int_arr[2],(float)int_arr[3],
                    (float)int_arr[4],(float)int_arr[5],(float)int_arr[6],(float)int_arr[7],
                    (float)int_arr[8],(float)int_arr[9],(float)int_arr[10],(float)int_arr[11],
                    (float)int_arr[12],(float)int_arr[13],(float)int_arr[14],(float)int_arr[15],(float)int_arr[16]);
*/

            s_q0.push_back((double)int_q[0]); s_e0.push_back((double)int_e[0]);  s_l0.push_back((double)int_l[0]); s_t0.push_back((double)int_t[0]); s_p0.push_back((double)int_p[0]);
            s_q1.push_back((double)int_q[1]); s_e1.push_back((double)int_e[1]);  s_l1.push_back((double)int_l[1]); s_t1.push_back((double)int_t[1]);
            s_q2.push_back((double)int_q[2]); s_e2.push_back((double)int_e[2]);  s_l2.push_back((double)int_l[2]); s_t2.push_back((double)int_t[2]);
            s_q3.push_back((double)int_q[3]);
            s_bmin0.push_back((double)int_bmin[0]); s_bmax0.push_back((double)int_bmax[0]);
            s_bmin1.push_back((double)int_bmin[1]); s_bmax1.push_back((double)int_bmax[1]);
            s_bmin2.push_back((double)int_bmin[2]); s_bmax2.push_back((double)int_bmax[2]);
            s_frustum_toggle.push_back(int_frustum_toggle);

            s_r0.push_back((double)int_arr[0]);     s_r1.push_back((double)int_arr[1]);     s_r2.push_back((double)int_arr[2]);     s_r3.push_back((double)int_arr[3]);
            s_r4.push_back((double)int_arr[4]);     s_r5.push_back((double)int_arr[5]);     s_r6.push_back((double)int_arr[6]);     s_r7.push_back((double)int_arr[7]);
            s_r8.push_back((double)int_arr[8]);     s_r9.push_back((double)int_arr[9]);     s_r10.push_back((double)int_arr[10]);  s_r11.push_back((double)int_arr[11]);
            s_r12.push_back((double)int_arr[12]);   s_r13.push_back((double)int_arr[13]);   s_r14.push_back((double)int_arr[14]);  s_r15.push_back((double)int_arr[15]);
            s_r16.push_back((double)int_arr[16]);   s_r17.push_back((double)int_arr[17]);   s_r18.push_back((double)int_arr[18]);

            c++;
            if (first) {
                first=false;
//                strcpy(fline2,line);
            }
        }
        fclose(movement_file);

        if (!first) {
            s_q0.push_back((double)s_q0[0]); s_e0.push_back((double)s_e0[0]);  s_l0.push_back((double)s_l0[0]); s_t0.push_back((double)s_t0[0]); s_p0.push_back((double)s_p0[0]);
            s_q1.push_back((double)s_q1[0]); s_e1.push_back((double)s_e1[0]);  s_l1.push_back((double)s_l1[0]); s_t1.push_back((double)s_t1[0]);
            s_q2.push_back((double)s_q2[0]); s_e2.push_back((double)s_e2[0]);  s_l2.push_back((double)s_l2[0]); s_t2.push_back((double)s_t2[0]);
            s_q3.push_back((double)s_q3[0]);
            s_bmin0.push_back((double)s_bmin0[0]); s_bmax0.push_back((double)s_bmax0[0]);
            s_bmin1.push_back((double)s_bmin1[0]); s_bmax1.push_back((double)s_bmax1[0]);
            s_bmin2.push_back((double)s_bmin2[0]); s_bmax2.push_back((double)s_bmax2[0]);
            s_frustum_toggle.push_back(s_frustum_toggle[0]);
            s_r0.push_back((double)s_r0[0]);    s_r4.push_back((double)s_r4[0]);    s_r8.push_back((double)s_r8[0]);   s_r12.push_back((double)s_r12[0]);
            s_r1.push_back((double)s_r1[0]);    s_r5.push_back((double)s_r5[0]);    s_r9.push_back((double)s_r9[0]);   s_r13.push_back((double)s_r13[0]);
            s_r2.push_back((double)s_r2[0]);    s_r6.push_back((double)s_r6[0]);    s_r10.push_back((double)s_r10[0]); s_r14.push_back((double)s_r14[0]);
            s_r3.push_back((double)s_r3[0]);    s_r7.push_back((double)s_r7[0]);    s_r11.push_back((double)s_r11[0]); s_r15.push_back((double)s_r15[0]);
            s_r16.push_back((double)s_r16[0]);  s_r17.push_back((double)s_r17[0]);  s_r18.push_back((double)s_r18[0]);
//            s_r16.push_back((double)   s_r16[s_r16.size()-1] +  (s_r16[s_r16.size()-1] - s_r16[s_r16.size()-2] ) );
            c++;
            s_q0.push_back((double)s_q0[1]); s_e0.push_back((double)s_e0[1]);  s_l0.push_back((double)s_l0[1]); s_t0.push_back((double)s_t0[1]); s_p0.push_back((double)s_p0[1]);
            s_q1.push_back((double)s_q1[1]); s_e1.push_back((double)s_e1[1]);  s_l1.push_back((double)s_l1[1]); s_t1.push_back((double)s_t1[1]);
            s_q2.push_back((double)s_q2[1]); s_e2.push_back((double)s_e2[1]);  s_l2.push_back((double)s_l2[1]); s_t2.push_back((double)s_t2[1]);
            s_q3.push_back((double)s_q3[1]);
            s_bmin0.push_back((double)s_bmin0[1]); s_bmax0.push_back((double)s_bmax0[1]);
            s_bmin1.push_back((double)s_bmin1[1]); s_bmax1.push_back((double)s_bmax1[1]);
            s_bmin2.push_back((double)s_bmin2[1]); s_bmax2.push_back((double)s_bmax2[1]);
            s_frustum_toggle.push_back(s_frustum_toggle[1]);
            s_r0.push_back((double)s_r0[1]);    s_r4.push_back((double)s_r4[1]);    s_r8.push_back((double)s_r8[1]);   s_r12.push_back((double)s_r12[1]);
            s_r1.push_back((double)s_r1[1]);    s_r5.push_back((double)s_r5[1]);    s_r9.push_back((double)s_r9[1]);   s_r13.push_back((double)s_r13[1]);
            s_r2.push_back((double)s_r2[1]);    s_r6.push_back((double)s_r6[1]);    s_r10.push_back((double)s_r10[1]); s_r14.push_back((double)s_r14[1]);
            s_r3.push_back((double)s_r3[1]);    s_r7.push_back((double)s_r7[1]);    s_r11.push_back((double)s_r11[1]); s_r15.push_back((double)s_r15[1]);
            s_r16.push_back((double)s_r16[1]);  s_r17.push_back((double)s_r17[1]);  s_r18.push_back((double)s_r18[1]);
//            s_r16.push_back((double)   s_r16[s_r16.size()-1] +  (s_r16[s_r16.size()-1] - s_r16[s_r16.size()-2] ) );
        }

        printf("size=%d\n",s_q0.size());
        printf("Loaded movement data line(s): %d\n", c);
        movement_file=NULL;
        if (c==0) {
            printf(" No data in file %s\n",marker_filename);
            interpolate_on=false;
            return;
        }
        printf("\nReady. Creating splines...");
        splinterp(sp_q0,s_q0); splinterp(sp_e0,s_e0); splinterp(sp_l0,s_l0); splinterp(sp_t0,s_t0); splinterp(sp_p0,s_p0);
        splinterp(sp_q1,s_q1); splinterp(sp_e1,s_e1); splinterp(sp_l1,s_l1); splinterp(sp_t1,s_t1);
        splinterp(sp_q2,s_q2); splinterp(sp_e2,s_e2); splinterp(sp_l2,s_l2); splinterp(sp_t2,s_t2);
        splinterp(sp_q3,s_q3);
        splinterp(sp_bmin0,s_bmin0); splinterp(sp_bmax0,s_bmax0);
        splinterp(sp_bmin1,s_bmin1); splinterp(sp_bmax1,s_bmax1);
        splinterp(sp_bmin2,s_bmin2); splinterp(sp_bmax2,s_bmax2);

        splinterp(sp_r0,s_r0);      splinterp(sp_r4,s_r4);      splinterp(sp_r8,s_r8); splinterp(sp_r12,s_r12);
        splinterp(sp_r1,s_r1);      splinterp(sp_r5,s_r5);      splinterp(sp_r9,s_r9); splinterp(sp_r13,s_r13);
        splinterp(sp_r2,s_r2);      splinterp(sp_r6,s_r6);      splinterp(sp_r10,s_r10); splinterp(sp_r14,s_r14);
        splinterp(sp_r3,s_r3);      splinterp(sp_r7,s_r7);      splinterp(sp_r11,s_r11); splinterp(sp_r15,s_r15);
        splinterp(sp_r16,s_r16);    splinterp(sp_r17,s_r17);    splinterp(sp_r18,s_r18);

        printf("...loaded and ready\n");
        splines_loaded=true;
        starting=0.0;
        if (c==1) {
            printf(" Only one line, jumping to it and quiting\n");
            set_end_of_movement=true;
            return;
        } else printf("\n");
        what=2;
//        if (record_window) {
//            record_pause=0;
//        }
    }
    if (!interpolate_on && what!=2) {  //step
        if (!splines_loaded) {
            printf("No movement data in movement file. Press m to create markers, shift-P to load them.\n");
            return;
        }
        if (c==0) {
            printf("No data in movement file. Press m to create markers, shift-P to load them.\n");
            return;
        }
        if (what!=2) starting=(double)((int)(starting+1.0));
        int tt=(int)starting;
        if (tt>c-1) {
            tt=0;
            starting=0.0;
            printf("Setting start to 0.0\n");
        }
        int_q[0]=(float)splinterpEval(sp_q0, starting); int_q[1]=(float)splinterpEval(sp_q1, starting); int_q[2]=(float)splinterpEval(sp_q2, starting); int_q[3]=(float)splinterpEval(sp_q3, starting);
        int_e[0]=(float)splinterpEval(sp_e0, starting); int_e[1]=(float)splinterpEval(sp_e1, starting); int_e[2]=(float)splinterpEval(sp_e2, starting);
        int_l[0]=(float)splinterpEval(sp_l0, starting); int_l[1]=(float)splinterpEval(sp_l1, starting); int_l[2]=(float)splinterpEval(sp_l2, starting);
        int_t[0]=(float)splinterpEval(sp_t0, starting); int_t[1]=(float)splinterpEval(sp_t1, starting); int_t[2]=(float)splinterpEval(sp_t2, starting);
        int_p[0]=(float)splinterpEval(sp_p0, starting);
        int_bmin[0]=(float)splinterpEval(sp_bmin0, starting); int_bmin[1]=(float)splinterpEval(sp_bmin1, starting); int_bmin[2]=(float)splinterpEval(sp_bmin2, starting);
        int_bmax[0]=(float)splinterpEval(sp_bmax0, starting); int_bmax[1]=(float)splinterpEval(sp_bmax1, starting); int_bmax[2]=(float)splinterpEval(sp_bmax2, starting);
        int_frustum_toggle=s_frustum_toggle[tt];
//        if (area!="Models") {
            rot_arr[0]=(float)splinterpEval(sp_r0, starting);   rot_arr[4]=(float)splinterpEval(sp_r4, starting);   rot_arr[8]=(float)splinterpEval(sp_r8, starting); rot_arr[12]=(float)splinterpEval(sp_r12, starting);
            rot_arr[1]=(float)splinterpEval(sp_r1, starting);   rot_arr[5]=(float)splinterpEval(sp_r5, starting);   rot_arr[9]=(float)splinterpEval(sp_r9, starting); rot_arr[13]=(float)splinterpEval(sp_r13, starting);
            rot_arr[2]=(float)splinterpEval(sp_r2, starting);   rot_arr[6]=(float)splinterpEval(sp_r6, starting);   rot_arr[10]=(float)splinterpEval(sp_r10, starting); rot_arr[14]=(float)splinterpEval(sp_r14, starting);
            rot_arr[3]=(float)splinterpEval(sp_r3, starting);   rot_arr[7]=(float)splinterpEval(sp_r7, starting);   rot_arr[11]=(float)splinterpEval(sp_r11, starting); rot_arr[15]=(float)splinterpEval(sp_r15, starting);
            int_arr[16]=(float)splinterpEval(sp_r16, starting); int_arr[17]=(float)splinterpEval(sp_r17, starting); int_arr[18]=(float)splinterpEval(sp_r18, starting);
//        } else {
//            rot_mat=glm::mat4(1.0);
//        }

        sprintf(calc,"c=%d t=%-+f q0=%-+f q1=%-+f q2=%-+f q3=%-+f  e0=%-+f e1=%-+f e2=%-+f  l0=%-+f l1=%-+f l2=%-+f  t0=%-+f t1=%-+f t2=%-+f  p0=%-+f  bmin=%-+f %-+f %-+f  bmax=%-+f %-+f %-+f  frustum=%d",c,starting,
                int_q[0],int_q[1],int_q[2],int_q[3],
                int_e[0],int_e[1],int_e[2],
                int_l[0],int_l[1],int_l[2],
                int_t[0],int_t[1],int_t[2],
                int_p[0],
                int_bmin[0], int_bmin[1], int_bmin[2],
                int_bmax[0], int_bmax[1], int_bmax[2],int_frustum_toggle
               );

        int_q[0]    = (float)s_q0[tt]; int_e[0] = (float)s_e0[tt]; int_l[0] = (float)s_l0[tt]; int_t[0] = (float)s_t0[tt]; int_p[0] = (float)s_p0[tt];
        int_q[1]    = (float)s_q1[tt]; int_e[1] = (float)s_e1[tt]; int_l[1] = (float)s_l1[tt]; int_t[1] = (float)s_t1[tt];
        int_q[2]    = (float)s_q2[tt]; int_e[2] = (float)s_e2[tt]; int_l[2] = (float)s_l2[tt]; int_t[2] = (float)s_t2[tt];
        int_q[3]    = (float)s_q3[tt];
        int_bmin[0] = (float)s_bmin0[tt]; int_bmax[0] = (float)s_bmax0[tt];
        int_bmin[1] = (float)s_bmin1[tt]; int_bmax[1] = (float)s_bmax1[tt];
        int_bmin[2] = (float)s_bmin2[tt]; int_bmax[2] = (float)s_bmax2[tt];
        int_arr[0]  = (float)s_r0[tt]; int_arr[1]  = (float)s_r1[tt]; int_arr[2]  = (float)s_r2[tt]; int_arr[3]  = (float)s_r3[tt];
        int_arr[4]  = (float)s_r4[tt]; int_arr[5]  = (float)s_r5[tt]; int_arr[6]  = (float)s_r6[tt]; int_arr[7]  = (float)s_r7[tt];
        int_arr[8]  = (float)s_r8[tt]; int_arr[9]  = (float)s_r9[tt]; int_arr[10] = (float)s_r10[tt];int_arr[11] = (float)s_r11[tt];
        int_arr[12] = (float)s_r12[tt];int_arr[13] = (float)s_r13[tt];int_arr[14] = (float)s_r14[tt];int_arr[15] = (float)s_r15[tt];
        int_arr[16] = (float)s_r16[tt];int_arr[17] = (float)s_r17[tt];int_arr[18] = (float)s_r18[tt];

        sprintf(store,"c=%d t=%-+f q0=%-+f q1=%-+f q2=%-+f q3=%-+f  e0=%-+f e1=%-+f e2=%-+f  l0=%-+f l1=%-+f l2=%-+f  t0=%-+f t1=%-+f t2=%-+f  p0=%-+f  bmin=%-+f %-+f %-+f  bmax=%-+f %-+f %-+f  frustum=%d",c,starting,
                int_q[0],int_q[1],int_q[2],int_q[3],
                int_e[0],int_e[1],int_e[2],
                int_l[0],int_l[1],int_l[2],
                int_t[0],int_t[1],int_t[2],
                int_p[0],
                int_bmin[0], int_bmin[1], int_bmin[2],
                int_bmax[0], int_bmax[1], int_bmax[2],int_frustum_toggle
               );

        printf("CALC:%s\n",calc);
        printf("STOR:%s\n",store);
        if (strcmp(calc,store)!=0) printf("DIFFERENT!!! THIS SUCKS!!!!\n");
        printf("\n");
        if (tt>c) {
            printf("Reached end point...\n");
        }

        return;
    }
    if (what==1 || what==3) {

        if (!splines_loaded) {
            printf("No movement data in movement file. Press m to create markers, shift-P to load them.\n");
            return;
        }
        if (c==0) {
            printf("No data in movement file. Press m to create markers, shift-P to load them.\n");
            return;
        }
        int tt=(int)starting;

        int_q[0]=(float)splinterpEval(sp_q0, starting); int_q[1]=(float)splinterpEval(sp_q1, starting); int_q[2]=(float)splinterpEval(sp_q2, starting); int_q[3]=(float)splinterpEval(sp_q3, starting);
        int_e[0]=(float)splinterpEval(sp_e0, starting); int_e[1]=(float)splinterpEval(sp_e1, starting); int_e[2]=(float)splinterpEval(sp_e2, starting);
        int_l[0]=(float)splinterpEval(sp_l0, starting); int_l[1]=(float)splinterpEval(sp_l1, starting); int_l[2]=(float)splinterpEval(sp_l2, starting);
        int_t[0]=(float)splinterpEval(sp_t0, starting); int_t[1]=(float)splinterpEval(sp_t1, starting); int_t[2]=(float)splinterpEval(sp_t2, starting);
        int_p[0]=(float)splinterpEval(sp_p0, starting);
        int_bmin[0]=(float)splinterpEval(sp_bmin0, starting); int_bmin[1]=(float)splinterpEval(sp_bmin1, starting); int_bmin[2]=(float)splinterpEval(sp_bmin2, starting);
        int_bmax[0]=(float)splinterpEval(sp_bmax0, starting); int_bmax[1]=(float)splinterpEval(sp_bmax1, starting); int_bmax[2]=(float)splinterpEval(sp_bmax2, starting);
        int_frustum_toggle=s_frustum_toggle[tt];
//        if (area!="Models") {
            rot_arr[0]=(float)splinterpEval(sp_r0, starting); rot_arr[4]=(float)splinterpEval(sp_r4, starting); rot_arr[8]=(float)splinterpEval(sp_r8, starting); rot_arr[12]=(float)splinterpEval(sp_r12, starting);
            rot_arr[1]=(float)splinterpEval(sp_r1, starting); rot_arr[5]=(float)splinterpEval(sp_r5, starting); rot_arr[9]=(float)splinterpEval(sp_r9, starting); rot_arr[13]=(float)splinterpEval(sp_r13, starting);
            rot_arr[2]=(float)splinterpEval(sp_r2, starting); rot_arr[6]=(float)splinterpEval(sp_r6, starting); rot_arr[10]=(float)splinterpEval(sp_r10, starting); rot_arr[14]=(float)splinterpEval(sp_r14, starting);
            rot_arr[3]=(float)splinterpEval(sp_r3, starting); rot_arr[7]=(float)splinterpEval(sp_r7, starting); rot_arr[11]=(float)splinterpEval(sp_r11, starting); rot_arr[15]=(float)splinterpEval(sp_r15, starting);
            int_arr[16]=(float)splinterpEval(sp_r16, starting);
            int_arr[17]=(float)splinterpEval(sp_r17, starting);
            int_arr[18]=(float)splinterpEval(sp_r18, starting);
//        } else {
//            rot_mat=glm::mat4(1.0);
//        }
//        if (tt==starting) {
/*
        if ((int)(starting-0.01)!=(int)(starting)) {
            sprintf(calc,"c=%d t=%-+f q0=%-+f q1=%-+f q2=%-+f q3=%-+f  e0=%-+f e1=%-+f e2=%-+f  l0=%-+f l1=%-+f l2=%-+f\n  t0=%-+f t1=%-+f t2=%-+f  p0=%-+f  bmin=%-+f %-+f %-+f  bmax=%-+f %-+f %-+f\n  frustum=%d",c,starting,
                    int_q[0],int_q[1],int_q[2],int_q[3],
                    int_e[0],int_e[1],int_e[2],
                    int_l[0],int_l[1],int_l[2],
                    int_t[0],int_t[1],int_t[2],
                    int_p[0],
                    int_bmin[0], int_bmin[1], int_bmin[2],
                    int_bmax[0], int_bmax[1], int_bmax[2],int_frustum_toggle
                   );
            printf("CALC:%s\n",calc);
//            printf("STOR:%s\n",store);
//            if (strcmp(calc,store)!=0) printf("DIFFERENT!!! THIS SUCKS!!!!\n");
            printf("\n");
        }
*/
        if (c>0) {
            float perc=starting/(float)c;
            printf("\rtime=%7.2f %5.2f%%",starting,100.0*perc);
        }


        if (record_window && starting>0.0 && !loop_end) {
            record_pause=0;
            show_text=false;
        }

        starting=starting+playbackspeed;
        if ((int)starting>c-2) {
            printf("\n");
            tt=0;
            starting=0.0;
            if (record_window) {
                loop_end=true;
                printf("Recording paused. Press shift-R to continue recording, r to stop\n");
                record_pause=1;
            }
            printf("Setting start to 0.0\n");
//            stop_view();
        }

/*        if (tt>c-1) {
            printf("Reached end point...\n");
            set_end_of_movement=true;
            if (record_window) {
                printf("Recording paused. Press shift-R to continue recording, r to stop\n");
                record_pause=1;
            }
        }
*/
        return;
    }
}

int center_x=0;
int center_y=0;

double center_lat=0;
double center_lon=0;

bool sort_lat_lon=false;

std::vector<glm::dvec2> lat_lon_center;

struct info_3d_struct {
    glm::ivec2 pos;
    glm::ivec2 pos2;
    std::string filename;
//utrecht
    glm::vec3 min_x=glm::vec3(0,0,0);
    glm::vec3 min_y=glm::vec3(0,0,0);
    glm::vec3 min_z=glm::vec3(0,0,0);
    glm::vec3 max_x=glm::vec3(0,0,0);
    glm::vec3 max_y=glm::vec3(0,0,0);
    glm::vec3 max_z=glm::vec3(0,0,0);
    double lat=0.0;
    double lon=0.0;
    double n=0.0;
    double s=0.0;
    double e=0.0;
    double w=0.0;
    bool ok=true;

    bool operator < (const info_3d_struct &B) const
    {
        if (sort_lat_lon) {
            double angle;
            double Bangle;
            int center_pos2_y_lowest=9999.9;
            int center_pos2_x_lowest=9999.9;
            int Bcenter_pos2_y_lowest=9999.9;
            int Bcenter_pos2_x_lowest=9999.9;

            double dist;
            double Bdist;
            double dist_lowest=9999.9;
            double Bdist_lowest=9999.9;
            int n=0;
            int Bn=0;
            int cnt=99;
            for (auto v : lat_lon_center) {
                cnt--;
                glm::dvec2 one_lat_lon_center=v;
                int center_x=one_lat_lon_center.x;
                int center_y=one_lat_lon_center.y;

                dist=sqrt( (pos2.y-center_y)*(pos2.y-center_y) + (pos2.x-center_x)*(pos2.x-center_x)*1.23 );
                if (dist<dist_lowest) {
                    dist_lowest=dist;
                    center_pos2_x_lowest=center_x;
                    center_pos2_y_lowest=center_y;
                    n=cnt;
                }

                Bdist=sqrt( (B.pos2.y-center_y)*(B.pos2.y-center_y) + (B.pos2.x-center_x)*(B.pos2.x-center_x)*1.23 );
                if (Bdist<Bdist_lowest) {
                    Bdist_lowest=Bdist;
                    Bcenter_pos2_x_lowest=center_x;
                    Bcenter_pos2_y_lowest=center_y;
                    Bn=cnt;
                }
            }

            if (int(dist_lowest/3)!=int(Bdist_lowest/3)) return ( dist_lowest < Bdist_lowest );

            if (n!=Bn) return ( n<Bn );

            angle=atan2(pos2.x-center_pos2_x_lowest,pos2.y-center_pos2_y_lowest);
            Bangle=atan2(B.pos2.x-Bcenter_pos2_x_lowest,B.pos2.y-Bcenter_pos2_y_lowest);

            return( angle < Bangle );

/*
            double angle;
            double Bangle;
            double center_lat_lowest=9999.9;
            double center_lon_lowest=9999.9;
            double Bcenter_lat_lowest=9999.9;
            double Bcenter_lon_lowest=9999.9;

            double dist;
            double Bdist;
            double dist_lowest=9999.9;
            double Bdist_lowest=9999.9;
            int n=0;
            int Bn=0;
            int cnt=99;
            for (auto v : lat_lon_center) {
                cnt--;
                glm::dvec2 one_lat_lon_center=v;
                center_lat=one_lat_lon_center.x;
                center_lon=one_lat_lon_center.y;

                dist=sqrt( (float)((lat-center_lat)*(lat-center_lat) + (lon-center_lon)*(lon-center_lon)) );
                if (dist<dist_lowest) {
                    dist_lowest=dist;
                    center_lat_lowest=lat;
                    center_lon_lowest=lon;
                    n=cnt;
                }

                Bdist=sqrt( (float)((B.lat-center_lat)*(B.lat-center_lat) + (B.lon-center_lon)*(B.lon-center_lon)) );
                if (Bdist<Bdist_lowest) {
                    Bdist_lowest=Bdist;
                    Bcenter_lat_lowest=B.lat;
                    Bcenter_lon_lowest=B.lon;
                    Bn=cnt;
                }
            }

            if (int(dist_lowest/4)!=int(Bdist_lowest/4)) return ( dist_lowest < Bdist_lowest );

            if (n!=Bn) return ( n<Bn );

            angle=atan2(lon-center_lon_lowest,lat-center_lat_lowest);
            Bangle=atan2(B.lon-Bcenter_lon_lowest,B.lat-Bcenter_lat_lowest);

            return( angle < Bangle );
*/

        } else {

            double dist=sqrt( (pos2.x-center_x)*(pos2.x-center_x)*1.23 +(pos2.y-center_y)*(pos2.y-center_y) );
            double Bdist=sqrt( (B.pos2.x-center_x)*(B.pos2.x-center_x)*1.23 + (B.pos2.y-center_y)*(B.pos2.y-center_y) );

            if (int(dist/4)!=int(Bdist/4)) return ( dist < Bdist);


            double angle=atan2(pos2.x-center_x,pos2.y-center_y);
            double Bangle=atan2(B.pos2.x-center_x,B.pos2.y-center_y);

            return( angle < Bangle );
        }
    }
};

static bool MakeObj(std::vector<struct info_3d_struct>& info_3d, std::string my_area);

std::vector<struct info_3d_struct> info_3d;

bool create_boundaries(std::string my_area, sf::RenderWindow& window) {
    shut_up=1;
    ShowTaskBar(true);
    info_3d.clear();
    info_3d_struct info_3d_elem;
    sf::Event event;

    int x=0,y=0;

    double bmin[3], bmax[3];
    bmin[0] = bmin[1] = bmin[2] = std::numeric_limits<double>::max();
    bmax[0] = bmax[1] = bmax[2] = -std::numeric_limits<double>::max();


    int max_x =-std::numeric_limits<int>::max();
    int max_y =-std::numeric_limits<int>::max();;

    int min_x = std::numeric_limits<int>::max();
    int min_y = std::numeric_limits<int>::max();;


    std::string str;

    FILE *file_arr;
    char line[500];
    int cnt=0;
    printf("Area=%s\n",my_area.c_str());
    if ((file_arr = fopen ("OBJECT_ARRAY.TXT", "r"))!=NULL) {
        printf("OBJECT_ARRAY.TXT detected. Loading object array data...\n");
        while (fgets (line,200, file_arr)!=NULL ) {
            x=-1;y=-1;
            int num=sscanf(line,"X=%d Y=%d\n", &x, &y);
            cnt++;
            if (num==2 && line[0]=='X' && x!=-1 && y!=-1) {
                window.pollEvent(event);
                str=get_area_data(my_area,x,y);
                if (str!="") {
                    printf("FOUND: X=%4d Y=%4d %s          \r",x,y,GetFileName(str).c_str());
//                    printf("lat/lon   : \"%s\"\n",latitude_longditude);
                    bool ERR=false;
                    for (auto v : info_3d) {
                        if (v.pos.x==x && v.pos.y==y) {
                            ERR=true;
                            printf("DOUBLE X=%4d Y=%4d %s          \n",x,y,GetFileName(str).c_str());
                        }
                    }
                    if (ERR) continue;
                    if (x<min_x) min_x=x;
                    if (y<min_y) min_y=y;
                    if (x>max_x) max_x=x;
                    if (y>max_y) max_y=y;
                    info_3d_elem.filename=str;
                    info_3d_elem.pos=glm::ivec2(x,y);

                    lat_north=0.0;
                    lat_south=0.0;
                    lon_west=0.0;
                    lon_east=0.0;
                    if (latitude_longditude!="") {
                        char line[2000];
                        strcpy(line,latitude_longditude.c_str());
//decimal_point
                        while (replace_str(line,",","."));
//                        while (replace_str(line,".",","));
                        int num=sscanf(line,"N=%lf S=%lf W=%lf E=%lf", &lat_north, &lat_south, &lon_west, &lon_east);

//                        if (num==4) {
//                        }
                    }
                    info_3d_elem.lat=(lat_north+lat_south)/2.0;
                    info_3d_elem.lon=(lon_east+lon_west)/2.0;
                    info_3d_elem.n=lat_north;
                    info_3d_elem.s=lat_south;
                    info_3d_elem.e=lon_east;
                    info_3d_elem.w=lon_west;
                    info_3d.push_back(info_3d_elem);
                } else {
                    printf("NOT FOUND: X=%4d Y=%4d                                                                                                               \n",x,y);
                }
            } else {
//                printf("Skipping line %d: %s\n",cnt,line);
            }
        }
        fclose(file_arr);
    } else {
//        printf("No OBJECT_ARRAY.TXT found, using corner octants...\n");
        max_x=-1;max_y=-1;
        get_area_data(my_area,max_x,max_y);
        min_x=0;min_y=0;

        for (y=0; y<max_y; y++) {
            for (x=0; x<max_x; x++) {
                window.pollEvent(event);
                if (my_area=="Models" || my_area=="Canvas") {
                } else if (!(x>1 && x<max_x-1 && y>1 && y<max_y-1)) {
                    if (my_area=="NewYork" || my_area=="Amsterdam") continue; //outline
                }
//                if (x!=0 && x!=max_x-1 && y!=0 && y!=max_y-1) continue; //outline
//                if (!(  (x==0 && (y==0 || y==max_y-1)) || (x==max_x-1 && (y==0 || y==max_y-1))  )) continue; //corners

                str=get_area_data(my_area,x,y);
                if (str!="") {
                    printf("#%3d FOUND: X=%3d Y=%3d %s\n",cnt,x,y,str.c_str());
                    info_3d_elem.filename=str;
                    info_3d_elem.pos=glm::ivec2(x,y);
                    lat_north=0.0;
                    lat_south=0.0;
                    lon_west=0.0;
                    lon_east=0.0;

                    if (latitude_longditude!="") {
                        char line[2000];
                        strcpy(line,latitude_longditude.c_str());
//decimal_point
                                            while (replace_str(line,",","."));
//                        while (replace_str(line,".",","));
                        int num=sscanf(line,"N=%lf S=%lf W=%lf E=%lf", &lat_north, &lat_south, &lon_west, &lon_east);
//                        "N=52.0916748046875 S=52.08892822265625 W=5.0811767578125 E=5.086669921875"
//                        if (num==4) {
//                        }
                    }
                    info_3d_elem.lat=(lat_north+lat_south)/2.0;
                    info_3d_elem.lon=(lon_east+lon_west)/2.0;
                    info_3d_elem.n=lat_north;
                    info_3d_elem.s=lat_south;
                    info_3d_elem.e=lon_east;
                    info_3d_elem.w=lon_west;
                    info_3d.push_back(info_3d_elem);
//                    printf("N=%f S=%f W=%f E=%f\n", &lat_north, &lat_south, &lon_west, &lon_east);
                } else {
                    printf("#%3d NOT FOUND: X=%3d Y=%3d\n",cnt,x,y);
                }
                cnt++;
            }
        }

        max_x=-1;max_y=-1;
        get_area_data(my_area,max_x,max_y);
        for (y=0; y<extra_octants; y++) {
            window.pollEvent(event);
            str=get_area_data(my_area,max_x,y);
            if (str!="") {
                printf("#%3d FOUND: X=%3d Y=%3d %s (EXTRA)\n",cnt,max_x,y,str.c_str());
                info_3d_elem.filename=str;
                info_3d_elem.pos=glm::ivec2(max_x,y);
                lat_north=0.0;
                lat_south=0.0;
                lon_west=0.0;
                lon_east=0.0;
                if (latitude_longditude!="") {
                    char line[2000];
                    strcpy(line,latitude_longditude.c_str());
//decimal_point
                                            while (replace_str(line,",","."));
//                    while (replace_str(line,".",","));
                    int num=sscanf(line,"N=%lf S=%lf W=%lf E=%lf", &lat_north, &lat_south, &lon_west, &lon_east);
//                        if (num==4) {
//                        }
                }
                info_3d_elem.n=lat_north;
                info_3d_elem.s=lat_south;
                info_3d_elem.e=lon_east;
                info_3d_elem.w=lon_west;
                info_3d_elem.lat=(lat_north+lat_south)/2.0;
                info_3d_elem.lon=(lon_east+lon_west)/2.0;
                info_3d.push_back(info_3d_elem);
            } else {
                printf("#%3d NOT FOUND: X=%3d Y=%3d (EXTRA)\n",cnt,max_x,y);
            }
            cnt++;
        }

    }
    printf("\n");
    int num_vertices=0;
    int num_objects=0;
    int num_uv=0;
    int num_normals=0;
    int num_faces=0;
    int num_materials=0;

    int tot_vertices=0;
    int tot_objects=0;
    int tot_uv=0;
    int tot_normals=0;
    int tot_faces=0;
    int tot_materials=0;

//    for (auto v : info_3d) {
//        printf("LIST:  X=%3d Y=%3d %s\r",v.pos.x,v.pos.y,v.filename.c_str());
//    }
    double xx,yy,zz;
    printf("\nGetting object positions\n");
    int item=0;

    double max_xx_x, max_xx_y, max_xx_z;
    double max_yy_x, max_yy_y, max_yy_z;
    double max_zz_x, max_zz_y, max_zz_z;
    double min_xx_x, min_xx_y, min_xx_z;
    double min_yy_x, min_yy_y, min_yy_z;
    double min_zz_x, min_zz_y, min_zz_z;
    cnt=0;
    for (auto v : info_3d) {

        info_3d[item].ok=false;
        std::string data_filename=v.filename;
        if (data_filename.find_last_of(".") != std::string::npos) data_filename=data_filename.substr(0,data_filename.find_last_of("."))+".dot";
        std::string data_filename_file=GetFileName(GetBaseDir(data_filename)).c_str();

//utrecht
        if (0 && (file_arr = fopen (data_filename.c_str(), "r"))!=NULL) {
            window.pollEvent(event);
            printf("#%3d LOADING: X=%4d Y=%4d %s ",cnt,v.pos.x,v.pos.y,data_filename_file.c_str());

            max_xx_x=0.0; max_xx_y=0.0; max_xx_z=0.0;
            max_yy_x=0.0; max_yy_y=0.0; max_yy_z=0.0;
            max_zz_x=0.0; max_zz_y=0.0; max_zz_z=0.0;
            min_xx_x=0.0; min_xx_y=0.0; min_xx_z=0.0;
            min_yy_x=0.0; min_yy_y=0.0; min_yy_z=0.0;
            min_zz_x=0.0; min_zz_y=0.0; min_zz_z=0.0;

            if (fgets (line,200, file_arr)!=NULL) { while (replace_str(line,",","."));  sscanf(line,"MIN X: X=%lf Y=%lf Z=%lf\n",&min_xx_x,&min_xx_y,&min_xx_z); }
            if (fgets (line,200, file_arr)!=NULL) { while (replace_str(line,",","."));  sscanf(line,"MIN Y: X=%lf Y=%lf Z=%lf\n",&min_yy_x,&min_yy_y,&min_yy_z); }
            if (fgets (line,200, file_arr)!=NULL) { while (replace_str(line,",","."));  sscanf(line,"MIN Z: X=%lf Y=%lf Z=%lf\n",&min_zz_x,&min_zz_y,&min_zz_z); }
            if (fgets (line,200, file_arr)!=NULL) { while (replace_str(line,",","."));  sscanf(line,"MAX X: X=%lf Y=%lf Z=%lf\n",&max_xx_x,&max_xx_y,&max_xx_z); }
            if (fgets (line,200, file_arr)!=NULL) { while (replace_str(line,",","."));  sscanf(line,"MAX Y: X=%lf Y=%lf Z=%lf\n",&max_yy_x,&max_yy_y,&max_yy_z); }
            if (fgets (line,200, file_arr)!=NULL) { while (replace_str(line,",","."));  sscanf(line,"MAX Z: X=%lf Y=%lf Z=%lf\n",&max_zz_x,&max_zz_y,&max_zz_z); }
            if (fgets (line,200, file_arr)!=NULL) {
                sscanf(line,"VERTICES=%d\n",    &num_vertices);
                if (fgets (line,200, file_arr)!=NULL) sscanf(line,"OBJECTS=%d\n",     &num_objects);    else num_vertices=0;
                if (fgets (line,200, file_arr)!=NULL) sscanf(line,"NORMALS=%d\n",     &num_normals);    else num_normals=0;
                if (fgets (line,200, file_arr)!=NULL) sscanf(line,"FACES=%d\n",       &num_faces);      else num_faces=0;
                if (fgets (line,200, file_arr)!=NULL) sscanf(line,"MATERIALS=%d\n",   &num_materials);  else num_materials=0;
            } else {
                num_vertices=0;
                num_objects=0;
                num_uv=0;
                num_normals=0;
                num_faces=0;
                num_materials=0;
            }
//adapted
//            info_3d[item].ok=true;
//            if (num_vertices>0) v.ok=true;
//            else  v.ok=false;
            if (num_vertices>0) info_3d[item].ok=true;
            else  info_3d[item].ok=false;

            fclose(file_arr);
//            printf ("MIN: X=%-+10.3f Y=%-+10.3f Z=%-+10.3f  MAX: X=%-+10.3f Y=%-+10.3f Z=%-+10.3f         \n",
//                      min_xx_x, min_yy_y, min_zz_z, max_xx_x, max_yy_y, max_zz_z);
            printf ("%8dK MIN: X=%-+6d Y=%-+6d Z=%-+6d  MAX: X=%-+6d Y=%-+6d Z=%-+6d  DIFF: X=%-+6d Y=%-+6d Z=%-+6d            \n",(int)(num_vertices/1000),
                        (int)min_xx_x, (int)min_yy_y, (int)min_zz_z,
                        (int)max_xx_x, (int)max_yy_y, (int)max_zz_z,
                        (int)max_xx_x-(int)min_xx_x, (int)max_yy_y-(int)min_yy_y,  (int)max_zz_z-(int)min_zz_z
                        );

//            printf("MIN X: X=%f Y=%f Z=%f\n",min_xx_x,min_xx_y,min_xx_z);
//            printf("MIN Y: X=%f Y=%f Z=%f\n",min_yy_x,min_yy_y,min_yy_z);
//            printf("MIN Z: X=%f Y=%f Z=%f\n",min_zz_x,min_zz_y,min_zz_z);
//            printf("MAX X: X=%f Y=%f Z=%f\n",max_xx_x,max_xx_y,max_xx_z);
//            printf("MAX Y: X=%f Y=%f Z=%f\n",max_yy_x,max_yy_y,max_yy_z);
//            printf("MAX Z: X=%f Y=%f Z=%f\n",max_zz_x,max_zz_y,max_zz_z);

//            v.min_x.x=min_xx_x; v.min_x.y=min_xx_y; v.min_x.z=min_xx_z;
//            v.min_y.x=min_yy_x; v.min_y.y=min_yy_y; v.min_y.z=min_yy_z;
//            v.min_z.x=min_zz_x; v.min_z.y=min_zz_y; v.min_z.z=min_zz_z;
//            v.max_x.x=max_xx_x; v.max_x.y=max_xx_y; v.max_x.z=max_xx_z;
//            v.max_y.x=max_yy_x; v.max_y.y=max_yy_y; v.max_y.z=max_yy_z;
//            v.max_z.x=max_zz_x; v.max_z.y=max_zz_y; v.max_z.z=max_zz_z;

            info_3d[item].min_x.x=min_xx_x; info_3d[item].min_x.y=min_xx_y; info_3d[item].min_x.z=min_xx_z;
            info_3d[item].min_y.x=min_yy_x; info_3d[item].min_y.y=min_yy_y; info_3d[item].min_y.z=min_yy_z;
            info_3d[item].min_z.x=min_zz_x; info_3d[item].min_z.y=min_zz_y; info_3d[item].min_z.z=min_zz_z;
            info_3d[item].max_x.x=max_xx_x; info_3d[item].max_x.y=max_xx_y; info_3d[item].max_x.z=max_xx_z;
            info_3d[item].max_y.x=max_yy_x; info_3d[item].max_y.y=max_yy_y; info_3d[item].max_y.z=max_yy_z;
            info_3d[item].max_z.x=max_zz_x; info_3d[item].max_z.y=max_zz_y; info_3d[item].max_z.z=max_zz_z;

//            printf("\n");


        } else {
            int nn=0;
//gerard

            std::string obj_filename_file=GetFileName(GetBaseDir(v.filename)).c_str();

            std::string nbt_filename=v.filename;
            if (nbt_filename.find_last_of(".") != std::string::npos) nbt_filename=nbt_filename.substr(0,nbt_filename.find_last_of("."))+".nbt";
            std::string nbt_filename_file=GetFileName(GetBaseDir(nbt_filename)).c_str();

            if (file_exists(nbt_filename.c_str())) {
                float minimum[3];
                float maximum[3];
                std::vector<BufferObject> buffers;
                std::vector<tinyobj::material_t> materials;
                NBT_TO_OBJECT3D(buffers, materials, (char*)nbt_filename.c_str(), minimum,maximum);

                if (my_area=="Utrecht" || my_area=="Holland") {
                    if (buffers.size()>0) RECALC_BMIN_BMAX_NEW(buffers, minimum, maximum, v.lat, v.lon);
                }
                else {
                    if (buffers.size()>0) RECALC_BMIN_BMAX(buffers, minimum, maximum, v.lat, v.lon);
                }

                min_xx_x = min_yy_x = min_zz_x = minimum[0];
                min_xx_y = min_yy_y = min_zz_y = minimum[1];
                min_xx_z = min_yy_z = min_zz_z = minimum[2];
                max_xx_x = max_yy_x = max_zz_x = maximum[0];
                max_xx_y = max_yy_y = max_zz_y = maximum[1];
                max_xx_z = max_yy_z = max_zz_z = maximum[2];
                num_faces=0;
                BufferObject one_buffer;
                for (auto u : buffers) {
                    one_buffer=u;
                    num_faces+=(one_buffer.length-sizeof(int)) / (3 + 3 + 3 + 2) / 3 / sizeof(float);
                    free(u.buffer);
                }
                num_vertices=num_faces*3;
                num_normals=num_vertices;
                num_uv=num_vertices;
                num_objects=buffers.size();
                num_materials=materials.size();
                info_3d[item].ok=true;


            } else if ((file_arr = fopen (v.filename.c_str(), "r"))!=NULL) {
                printf("\r#%3d TESTING: X=%4d Y=%4d %s       \r",cnt,v.pos.x,v.pos.y,obj_filename_file.c_str());
                num_vertices=0;
//                printf("Scanning %s\n",v.filename.c_str());

                max_xx_x =-std::numeric_limits<double>::max(), max_xx_y=0.0, max_xx_z=0.0;
                max_yy_x=0.0, max_yy_y =-std::numeric_limits<double>::max(), max_yy_z=0.0;
                max_zz_x=0.0,max_zz_y=0.0, max_zz_z =-std::numeric_limits<double>::max();

                min_xx_x =std::numeric_limits<double>::max(), min_xx_y=0.0, min_xx_z=0.0;
                min_yy_x=0.0, min_yy_y =std::numeric_limits<double>::max(), min_yy_z=0.0;
                min_zz_x=0.0,min_zz_y=0.0, min_zz_z =std::numeric_limits<double>::max();

                num_vertices=0;
                num_objects=0;
                num_uv=0;
                num_normals=0;
                num_faces=0;
                num_materials=0;
                while (fgets (line,200, file_arr)!=NULL) {
                    if (line[0]=='v' && line[1]==' ') {
                        num_vertices++;
                        int l=strlen(line);
                        for (int c=0; c<l; c++) if (line[c]=='.') line[c]=',';
//decimal_point
                        while (replace_str(line,",","."));
////                        while (replace_str(line,".",","));
                        sscanf(line,"v %lf %lf %lf\n",&xx,&yy,&zz);

                        if (xx<min_xx_x) { min_xx_x=xx; min_xx_y=yy; min_xx_z=zz; }
                        if (yy<min_yy_y) { min_yy_x=xx; min_yy_y=yy; min_yy_z=zz; }
                        if (zz<min_zz_z) { min_zz_x=xx; min_zz_y=yy; min_zz_z=zz; }
                        if (xx>max_xx_x) { max_xx_x=xx; max_xx_y=yy; max_xx_z=zz; }
                        if (yy>max_yy_y) { max_yy_x=xx; max_yy_y=yy; max_yy_z=zz; }
                        if (zz>max_zz_z) { max_zz_x=xx; max_zz_y=yy; max_zz_z=zz; }
                        if (++nn==100000) {
                            while (window.pollEvent(event));
                            nn=0;
                            printf("\r#%3d TESTING: X=%4d Y=%4d %s ",cnt,v.pos.x,v.pos.y,obj_filename_file.c_str());
                            printf ("%8dK MIN: X=%-+6d Y=%-+6d Z=%-+6d  MAX: X=%-+6d Y=%-+6d Z=%-+6d    DIFF: X=%-+6d Y=%-+6d Z=%-+6d            \r",(int)(num_vertices/1000),
                                (int)min_xx_x, (int)min_yy_y, (int)min_zz_z,
                                (int)max_xx_x, (int)max_yy_y, (int)max_zz_z,
                                (int)max_xx_x-(int)min_xx_x, (int)max_yy_y-(int)min_yy_y,  (int)max_zz_z-(int)min_zz_z
                                );
                        }
                    } else if (line[0]=='o') num_objects++;
                     else if (line[0]=='v' && line[1]=='t') num_uv++;
                     else if (line[0]=='v' && line[1]=='n') num_normals++;
                     else if (line[0]=='f') num_faces++;
                     else if (line[0]=='u' && line[1]=='s' && line[2]=='e') num_materials++;
                }
                fclose(file_arr);
                if (num_vertices>0) info_3d[item].ok=true;
                else  info_3d[item].ok=false;
            }
            else {
                printf("Cannot open %s for reading\n",data_filename.c_str());
                printf("Cannot open %s for reading\n",nbt_filename.c_str());
                printf("Cannot open %s for reading\n",v.filename.c_str());
            }

            if (info_3d[item].ok) {
                printf("\r#%3d TESTING: X=%4d Y=%4d %s ",cnt,v.pos.x,v.pos.y,obj_filename_file.c_str());
                printf ("%8dK MIN: X=%-+6d Y=%-+6d Z=%-+6d  MAX: X=%-+6d Y=%-+6d Z=%-+6d  DIFF: X=%-+6d Y=%-+6d Z=%-+6d Saving........                               \n",(int)(num_vertices/1000),
                        (int)min_xx_x, (int)min_yy_y, (int)min_zz_z,
                        (int)max_xx_x, (int)max_yy_y, (int)max_zz_z,
                        (int)max_xx_x-(int)min_xx_x, (int)max_yy_y-(int)min_yy_y,  (int)max_zz_z-(int)min_zz_z
                        );
                if ((file_arr = fopen (data_filename.c_str(), "w"))!=NULL) {
                    sprintf(line,"MIN X: X=%f Y=%f Z=%f\n",min_xx_x,min_xx_y,min_xx_z);fprintf(file_arr,line);// printf(line);
                    sprintf(line,"MIN Y: X=%f Y=%f Z=%f\n",min_yy_x,min_yy_y,min_yy_z);fprintf(file_arr,line);// printf(line);
                    sprintf(line,"MIN Z: X=%f Y=%f Z=%f\n",min_zz_x,min_zz_y,min_zz_z);fprintf(file_arr,line);// printf(line);
                    sprintf(line,"MAX X: X=%f Y=%f Z=%f\n",max_xx_x,max_xx_y,max_xx_z);fprintf(file_arr,line);// printf(line);
                    sprintf(line,"MAX Y: X=%f Y=%f Z=%f\n",max_yy_x,max_yy_y,max_yy_z);fprintf(file_arr,line);// printf(line);
                    sprintf(line,"MAX Z: X=%f Y=%f Z=%f\n",max_zz_x,max_zz_y,max_zz_z);fprintf(file_arr,line);// printf(line);
                    sprintf(line,"VERTICES=%d\n",   num_vertices);  fprintf(file_arr,line);// printf(line);
                    sprintf(line,"OBJECTS=%d\n",    num_objects);   fprintf(file_arr,line);// printf(line);
                    sprintf(line,"NORMALS=%d\n",    num_normals);   fprintf(file_arr,line);// printf(line);
                    sprintf(line,"FACES=%d\n",      num_faces);     fprintf(file_arr,line);// printf(line);
                    sprintf(line,"MATERIALS=%d\n",  num_materials); fprintf(file_arr,line);// printf(line);
                    fclose(file_arr);
                } else {
                    printf("Error saving %s\n",data_filename.c_str());
                    printf("MIN X: X=%-+f Y=%-+f Z=%-+f\n",min_xx_x,min_xx_y,min_xx_z);
                    printf("MIN Y: X=%-+f Y=%-+f Z=%-+f\n",min_yy_x,min_yy_y,min_yy_z);
                    printf("MIN Z: X=%-+f Y=%-+f Z=%-+f\n",min_zz_x,min_zz_y,min_zz_z);
                    printf("MAX X: X=%-+f Y=%-+f Z=%-+f\n",max_xx_x,max_xx_y,max_xx_z);
                    printf("MAX Y: X=%-+f Y=%-+f Z=%-+f\n",max_yy_x,max_yy_y,max_yy_z);
                    printf("MAX Z: X=%-+f Y=%-+f Z=%-+f\n",max_zz_x,max_zz_y,max_zz_z);
                }
//                printf("\n");

                info_3d[item].min_x.x=min_xx_x; info_3d[item].min_x.y=min_xx_y; info_3d[item].min_x.z=min_xx_z;
                info_3d[item].min_y.x=min_yy_x; info_3d[item].min_y.y=min_yy_y; info_3d[item].min_y.z=min_yy_z;
                info_3d[item].min_z.x=min_zz_x; info_3d[item].min_z.y=min_zz_y; info_3d[item].min_z.z=min_zz_z;
                info_3d[item].max_x.x=max_xx_x; info_3d[item].max_x.y=max_xx_y; info_3d[item].max_x.z=max_xx_z;
                info_3d[item].max_y.x=max_yy_x; info_3d[item].max_y.y=max_yy_y; info_3d[item].max_y.z=max_yy_z;
                info_3d[item].max_z.x=max_zz_x; info_3d[item].max_z.y=max_zz_y; info_3d[item].max_z.z=max_zz_z;
//                v.min_x.x=min_xx_x; v.min_x.y=min_xx_y; v.min_x.z=min_xx_z;
//                v.min_y.x=min_yy_x; v.min_y.y=min_yy_y; v.min_y.z=min_yy_z;
//                v.min_z.x=min_zz_x; v.min_z.y=min_zz_y; v.min_z.z=min_zz_z;
//                v.max_x.x=max_xx_x; v.max_x.y=max_xx_y; v.max_x.z=max_xx_z;
//                v.max_y.x=max_yy_x; v.max_y.y=max_yy_y; v.max_y.z=max_yy_z;
//                v.max_z.x=max_zz_x; v.max_z.y=max_zz_y; v.max_z.z=max_zz_z;
                info_3d[item].ok=true;
            } else {
                printf("\r#%3d TESTING: X=%4d Y=%4d %s ",cnt,v.pos.x,v.pos.y,obj_filename_file.c_str());
                printf ("%8dK MIN: X=%-+6d Y=%-+6d Z=%-+6d  MAX: X=%-+6d Y=%-+6d Z=%-+6d Saving........                                   \n",
                        (int)(num_vertices/1000),
                        (int)0, (int)0, (int)0, (int)0, (int)0, (int)0);
                if ((file_arr = fopen (data_filename.c_str(), "w"))!=NULL) {
                    sprintf(line,"MIN X: X=%f Y=%f Z=%f\n",0.0,0.0,0.0);fprintf(file_arr,line);// printf(line);
                    sprintf(line,"MIN Y: X=%f Y=%f Z=%f\n",0.0,0.0,0.0);fprintf(file_arr,line);// printf(line);
                    sprintf(line,"MIN Z: X=%f Y=%f Z=%f\n",0.0,0.0,0.0);fprintf(file_arr,line);// printf(line);
                    sprintf(line,"MAX X: X=%f Y=%f Z=%f\n",0.0,0.0,0.0);fprintf(file_arr,line);// printf(line);
                    sprintf(line,"MAX Y: X=%f Y=%f Z=%f\n",0.0,0.0,0.0);fprintf(file_arr,line);// printf(line);
                    sprintf(line,"MAX Z: X=%f Y=%f Z=%f\n",0.0,0.0,0.0);fprintf(file_arr,line);// printf(line);
                    sprintf(line,"VERTICES=%d\n",   0); fprintf(file_arr,line);// printf(line);
                    sprintf(line,"OBJECTS=%d\n",    0); fprintf(file_arr,line);// printf(line);
                    sprintf(line,"NORMALS=%d\n",    0); fprintf(file_arr,line);// printf(line);
                    sprintf(line,"FACES=%d\n",      0); fprintf(file_arr,line);// printf(line);
                    sprintf(line,"MATERIALS=%d\n",  0); fprintf(file_arr,line);// printf(line);
                    fclose(file_arr);
                }
//                v.ok=false;
                info_3d[item].ok=false;
            }
//                printf("\n");
        }
        item++;
        cnt++;
        tot_vertices+= num_vertices;
        tot_objects+=  num_objects;
        tot_uv+=       num_uv;
        tot_normals+=  num_normals;
        tot_faces+=    num_faces;
        tot_materials+=num_materials;
        bmin[0]=std::min(     min_xx_x, bmin[0]);   bmax[0]=std::max(  max_xx_x, bmax[0]);
        bmin[1]=std::min(     min_yy_y, bmin[1]);   bmax[1]=std::max(  max_yy_y, bmax[1]);
        bmin[2]=std::min(     min_zz_z, bmin[2]);   bmax[2]=std::max(  max_zz_z, bmax[2]);
        std::string obj_filename_file=GetFileName(GetBaseDir(v.filename)).c_str();
/*
        printf("\r#%3d TOTAL:   X=%4d Y=%4d %s ",cnt,v.pos.x,v.pos.y,obj_filename_file.c_str());
        printf ("%8dK MIN: X=%-+6d Y=%-+6d Z=%-+6d  MAX: X=%-+6d Y=%-+6d Z=%-+6d  DIFF: X=%-+6d Y=%-+6d Z=%-+6d\n",
                (int)(num_vertices/1000),
                (int)bmin[0],              (int)bmin[1],         (int)bmin[2],
                (int)bmax[0],              (int)bmax[1],         (int)bmax[2],
                (int)bmax[0]-(int)bmin[0], (int)bmax[1]-(int)bmin[1], (int)bmax[2]-(int)bmin[2]
                );
*/


    }
    printf("\n");
    printf("\n");
    printf("TOTAL #VERTICES =%d\n",   tot_vertices);
    printf("TOTAL #OBJECTS  =%d\n",    tot_objects);
    printf("TOTAL #NORMALS  =%d\n",    tot_normals);
    printf("TOTAL #FACES    =%d\n",      tot_faces);
    printf("TOTAL #MATERIALS=%d\n",  tot_materials);
    printf("TOTAL: bmin = %f, %f, %f\n", bmin[0],           bmin[1],            bmin[2]);
    printf("TOTAL: bmax = %f, %f, %f\n", bmax[0],           bmax[1],            bmax[2]);
    printf("TOTAL: diff = %f, %f, %f\n", bmax[0]-bmin[0],   bmax[1]-bmin[1],    bmax[2]-bmin[2]);

    MakeObj(info_3d, my_area);
    printf("\n");
    printf("TOTAL #VERTICES =%d\n",   tot_vertices);
    printf("TOTAL #OBJECTS  =%d\n",    tot_objects);
    printf("TOTAL #NORMALS  =%d\n",    tot_normals);
    printf("TOTAL #FACES    =%d\n",      tot_faces);
    printf("TOTAL #MATERIALS=%d\n",  tot_materials);
    printf("TOTAL: bmin = %f, %f, %f\n", bmin[0],           bmin[1],            bmin[2]);
    printf("TOTAL: bmax = %f, %f, %f\n", bmax[0],           bmax[1],            bmax[2]);
    printf("TOTAL: diff = %f, %f, %f\n", bmax[0]-bmin[0],   bmax[1]-bmin[1],    bmax[2]-bmin[2]);

    FILE* HOP;
    char hop_name[200];
    sprintf(hop_name,"%s.DAT",area.c_str());
    printf("Saving totals to %s\n",hop_name);
    HOP = fopen(hop_name,"w");
    sprintf(line,"TOTAL MIN: X=%24.17f Y=%24.17f Z=%24.17f\n",bmin[0],bmin[1],bmin[2]);                                fprintf(HOP,line);
    sprintf(line,"TOTAL MAX: X=%24.17f Y=%24.17f Z=%24.17f\n",bmax[0],bmax[1],bmax[2]);                                fprintf(HOP,line);
    sprintf(line,"TOTAL DIF: X=%24.17f Y=%24.17f Z=%24.17f\n",bmax[0]-bmin[0],   bmax[1]-bmin[1],    bmax[2]-bmin[2]); fprintf(HOP,line);
    double lat_min=std::numeric_limits<double>::max();
    double lat_max=-std::numeric_limits<double>::max();
    double lon_min=std::numeric_limits<double>::max();
    double lon_max=-std::numeric_limits<double>::max();
    for (auto u : info_3d) {
        if (u.n>lat_max) { lat_max=u.n; }
        if (u.s<lat_min) { lat_min=u.s; }
        if (u.w<lon_min)  { lon_min=u.w;  }
        if (u.e>lon_max)  { lon_max=u.e;  }
    }
    sprintf(line,"LAT: NORTH=%24.17f SOUTH=%24.17f\n",lat_max,lat_min);                                fprintf(HOP,line); printf(line);
//    sprintf(line,"LAT SOUTH=%24.17f\n",lat_min);                                fprintf(HOP,line);
    sprintf(line,"LON:  WEST=%24.17f  EAST=%24.17f\n",lon_min,lon_max);                                fprintf(HOP,line); printf(line);
//    sprintf(line,"LON EAST=%24.17f\n",lon_max);                                fprintf(HOP,line);
    for (auto v : info_3d) {
        info_3d_elem=v;
        sprintf(line,"POS [%3d][%3d]  ", info_3d_elem.pos.x, info_3d_elem.pos.y);        fprintf(HOP,line);
        sprintf(line,"XYZ[%24.17f to %24.17f][%24.17f to %24.17f][%24.17f to %24.17f]  ", info_3d_elem.min_x.x, info_3d_elem.max_x.x, info_3d_elem.min_y.y, info_3d_elem.max_y.y, info_3d_elem.min_z.z,info_3d_elem.max_z.z);        fprintf(HOP,line);
        sprintf(line,"NWSE[%24.17f][%24.17f][%24.17f][%24.17f]  ", info_3d_elem.n, info_3d_elem.w, info_3d_elem.s, info_3d_elem.e);        fprintf(HOP,line);
        sprintf(line,"%s\n", info_3d_elem.filename.c_str());        fprintf(HOP,line);
    }

    fclose(HOP);
    shut_up=0;
    return 1;
}

bool nbt_creating=false;
extern int main_mceditor5_from_file(char* dat_filename,char* voxel_filename);
extern int scan_done0(FILE* report, char* dat_filename, char* voxel_filename);
extern int scan_done0_plot(FILE* report, char* dat_filename, char* voxel_filename);

extern int region_counter[1000][1000];
extern sf::Image scan_image;
extern int MCEDITOR_stop;
extern std::vector<Voxel> voxels_total;
extern bool load_voxels();
extern std::string *extra_octants_belong_to_string_pointer;
extern bool get_area_quick;

bool create_nbt(std::string my_area, sf::RenderWindow& window, int win_num, bool pac_obj2_arr_used[100], Pacman_Object pac_obj2_arr[100]) {
    ShowTaskBar(true);
    bar_on[win_num]=1;
    FILE* report;
//    int region_counter[200][200];
    if (crossing==2 && mirror==3) {
        float minimum[3];
        float maximum[3];
        std::vector<BufferObject> buffers;
        std::vector<tinyobj::material_t> materials;
//                flushing=true;
        WUPPIE_SUBS(buffers, materials, minimum, maximum, 0, 0, my_area);
        return true;

    } else if (crossing==2 && mirror==4) {
        report = fopen ( "report.txt" , "w+" );
        fprintf(report,"Report area=%s\n",my_area.c_str());
        fclose(report);
        if (crossing==2 && mirror==4) {
//            voxels_total.clear();
            if (load_voxels()) {
                if (voxels_total.size()>0) {
                    float minimum[3];
                    float maximum[3];
                    std::vector<BufferObject> buffers;
                    std::vector<tinyobj::material_t> materials;
    //                flushing=true;
                    WUPPIE_SUBS(buffers, materials, minimum, maximum, 0, 0, my_area);
                    return true;
                }
            }
        }
    }

    nbt_creating=true;

    ShowTaskBar(true);
    info_3d.clear();
    info_3d_struct info_3d_elem;
    sf::Event event;

    int x=0,y=0;

    int max_x =-std::numeric_limits<int>::max();
    int max_y =-std::numeric_limits<int>::max();;

    int min_x = std::numeric_limits<int>::max();
    int min_y = std::numeric_limits<int>::max();;


    std::string str;

    FILE *file_arr;
    char line[200];
    int cnt=0;




    printf("Area=%s\n",my_area.c_str());
    std::string OA;
    if (MAKE_NBT) OA="OBJECT_ARRAY.NBT";
    else  OA="OBJECT_ARRAY.TXT";
    if ((file_arr = fopen (OA.c_str(), "r"))!=NULL) {
//    if (0 && (file_arr = fopen ("OBJECT_ARRAY.TXT", "r"))!=NULL) {
        printf("%s detected. Loading object array data...\n",OA.c_str());
        while (fgets (line,200, file_arr)!=NULL ) {
            x=-1;y=-1;
            if (line[0]=='R') {
                int x1=-1,x2=-1,y1=-1,y2=-1;
                int num=sscanf(line,"R:X=%d/%d Y=%d/%d\n", &x1, &x2, &y1, &y2);
                if (num!=4) { printf("Error reading object_array.txt\n"); fclose(file_arr); return false; }
                fclose(file_arr);
                if ((file_arr = fopen ("OBJECT_ARRAY2.TXT", "w"))!=NULL) {
                    for (int x=x1; x<=x2; x++) {
                        for (int y=y1; y<=y2; y++) {
                            fprintf(file_arr,"X=%d Y=%d\n",x,y);
                        }
                    }
                    fclose(file_arr);
                    if ((file_arr = fopen ("OBJECT_ARRAY2.TXT", "r"))!=NULL) {
                        fgets (line,200, file_arr);
                    } else {
                        printf("error opening: OBJECT_ARRAY2.TXT\n");
                    }

                } else {
                    printf("error writing to: OBJECT_ARRAY2.TXT\n");
                    return false;
                }
            }
            int num=sscanf(line,"X=%d Y=%d\n", &x, &y);
            cnt++;
            if (num==2 && line[0]=='X' && x!=-1 && y!=-1) {
                window.pollEvent(event);
//                to_check_pos.push_back(glm::vec2(x,y));
                str=get_area_data(my_area,x,y);
//                to_check_filename.push_back(str);
                if (str!="") {
                    printf("FOUND: X=%4d Y=%4d %s  ",x,y,GetFileName(str).c_str());
//                    printf("lat/lon   : \"%s\"\n",latitude_longditude.c_str());
                    bool ERR=false;
                    for (auto v : info_3d) {
                        if (v.pos.x==x && v.pos.y==y) {
                            ERR=true;
                            printf("DOUBLE X=%4d Y=%4d %s          \n",x,y,GetFileName(str).c_str());
                        }
                    }
                    if (ERR) continue;
                    if (x<min_x) min_x=x;
                    if (y<min_y) min_y=y;
                    if (x>max_x) max_x=x;
                    if (y>max_y) max_y=y;
                    info_3d_elem.filename=str;
                    info_3d_elem.pos=glm::ivec2(x,y);
                    info_3d_elem.pos2=glm::ivec2(x,y);

                    lat_north=0.0;
                    lat_south=0.0;
                    lon_west=0.0;
                    lon_east=0.0;
                    if (latitude_longditude!="") {
                        char line[2000];
                        strcpy(line,latitude_longditude.c_str());
                        while (replace_str(line,",","."));
                        int num=sscanf(line,"N=%lf S=%lf W=%lf E=%lf", &lat_north, &lat_south, &lon_west, &lon_east);
                    }
                    info_3d_elem.lat=(lat_north+lat_south)/2.0;
                    info_3d_elem.lon=(lon_east+lon_west)/2.0;
                    info_3d_elem.n=lat_north;
                    info_3d_elem.s=lat_south;
                    info_3d_elem.e=lon_east;
                    info_3d_elem.w=lon_west;

                    printf("N=%20.16f S=%20.16f W=%20.16f E=%20.16f\n", lat_north, lat_south, lon_west, lon_east);

                    info_3d.push_back(info_3d_elem);

                    max_x=-1;max_y=-1;
                    get_area_data(my_area,max_x,max_y);
                    for (int yyy=0; yyy<extra_octants; yyy++) {
                        window.pollEvent(event);
                        get_area_quick=true;
                        str=get_area_data(my_area,max_x,yyy);
                        get_area_quick=false;
                        if (str!="") {
                            std::string to_test=extra_octants_belong_to_string_pointer[yyy];
                            char octant[100];
                            int xx,yy;
                            int num=sscanf(to_test.c_str(),"%100[^ ] X=%d Y=%d", octant, &xx, &yy);

                            if (xx==x && yy==y) {
                                printf("#%3d FOUND: X=%3d Y=%3d %s (EXTRA)  ",cnt,max_x,yyy,str.c_str());
                                if (num==3) {
                                    str=get_area_data(my_area,max_x,yyy);
                                    info_3d_elem.filename=str;
//                                    info_3d_elem.pos=glm::ivec2(xx,yy);
                                    info_3d_elem.pos=glm::ivec2(max_x,yyy);
                                    info_3d_elem.pos2=glm::ivec2(xx,yy);
//                                    printf("Relocating       (%d,%d) to \"%s\"    \r",max_x,yyy,to_test.c_str());

                                    info_3d.push_back(info_3d_elem);
                                    cnt++;
                                }
                                break;
                            }

                        } else {
                            //printf("#%3d NOT FOUND: X=%3d Y=%3d (EXTRA)\r",cnt,max_x,yyy);
                        }
                    }



                } else {
                    printf("NOT FOUND: X=%4d Y=%4d                                                                                                               \n",x,y);
                }
            } else {
//                printf("Skipping line %d: %s\n",cnt,line);
            }
        }
        fclose(file_arr);
    } else {
//        printf("No OBJECT_ARRAY.TXT found, using corner octants...\n");
        max_x=-1;max_y=-1;
        get_area_data(my_area,max_x,max_y);
//        printf("max_x=%d max_y=%d\n",max_x,max_y);
        min_x=0;min_y=0;
        for (y=0; y<max_y; y++) {
            for (x=0; x<max_x; x++) {
                window.pollEvent(event);
//wuppie

                if (my_area == "Amsterdam" || my_area == "NewYork")
                    if (!(x>1 && x<max_x-1 && y>1 && y<max_y-1)) continue; //outline //used on coords amsterdam

//                if (x!=0 && x!=max_x-1 && y!=0 && y!=max_y-1) continue; //outline
//                if (!(  (x==0 && (y==0 || y==max_y-1)) || (x==max_x-1 && (y==0 || y==max_y-1))  )) continue; //corners
                str=get_area_data(my_area,x,y);
//                printf("Filename x=%d y=%d = %s\n",x,y,str.c_str());

                if (str!="") {
//                    printf(".");
                    printf("#%3d FOUND: X=%3d Y=%3d %s  ",cnt,x,y,str.c_str());
//                    printf("lat/lon   : \"%s\"\n",latitude_longditude.c_str());
                    info_3d_elem.filename=str;
                    info_3d_elem.pos=glm::ivec2(x,y);
                    info_3d_elem.pos2=glm::ivec2(x,y);

                    lat_north=0.0;
                    lat_south=0.0;
                    lon_west=0.0;
                    lon_east=0.0;
                    if (latitude_longditude!="") {
                        char line[2000];
                        strcpy(line,latitude_longditude.c_str());
//decimal_point
//decimal_point
                        while (replace_str(line,",","."));
//                        while (replace_str(line,".",","));
                        int num=sscanf(line,"N=%lf S=%lf W=%lf E=%lf", &lat_north, &lat_south, &lon_west, &lon_east);
                    }
                    info_3d_elem.lat=(lat_north+lat_south)/2.0;
                    info_3d_elem.lon=(lon_east+lon_west)/2.0;
                    info_3d_elem.n=lat_north;
                    info_3d_elem.s=lat_south;
                    info_3d_elem.e=lon_east;
                    info_3d_elem.w=lon_west;
//                    printf("N=%lf S=%lf W=%lf E=%lf\n", lat_north, lat_south, lon_west, lon_east);
                    printf("N=%20.16f S=%20.16f W=%20.16f E=%20.16f\n", lat_north, lat_south, lon_west, lon_east);

                    info_3d.push_back(info_3d_elem);
                } else {
                    printf("#%3d NOT FOUND: X=%3d Y=%3d\n",cnt,x,y);
                }

                cnt++;
            }
        }

        max_x=-1;max_y=-1;
        get_area_data(my_area,max_x,max_y);
        for (y=0; y<extra_octants; y++) {
            window.pollEvent(event);
            str=get_area_data(my_area,max_x,y);
            if (str!="") {
//                printf(".");
                printf("#%3d CREATE: X=%3d Y=%3d %s (EXTRA)  \n",cnt,max_x,y,str.c_str());
//                info_3d_elem.filename=str;
//                info_3d_elem.pos=glm::ivec2(max_x,y);

                std::string to_test=extra_octants_belong_to_string_pointer[y];
                char octant[100];
                int xx,yy;
                int num=sscanf(to_test.c_str(),"%100[^ ] X=%d Y=%d", octant, &xx, &yy);
                if (num==3) {
//                    info_3d_elem.pos=glm::ivec2(xx,yy);
                    info_3d_elem.pos=glm::ivec2(max_x,y);
                    info_3d_elem.pos2=glm::ivec2(xx,yy);
                    info_3d_elem.filename=str;
//                    printf("Relocating octant %s (%d,%d) to (%d,%d)\n",to_test.c_str(),max_x,y,xx,yy);
//                } else {
//                    printf("Can not relocate (%d,%d) to \"%s\"\n",max_x,y,to_test.c_str());
//                    str=get_area_data(my_area,xx,yy);

                    lat_north=0.0;
                    lat_south=0.0;
                    lon_west=0.0;
                    lon_east=0.0;
                    if (latitude_longditude!="") {
                        char line[2000];
                        strcpy(line,latitude_longditude.c_str());
                        while (replace_str(line,",","."));
                        int num=sscanf(line,"N=%lf S=%lf W=%lf E=%lf", &lat_north, &lat_south, &lon_west, &lon_east);
                    }
                    info_3d_elem.lat=(lat_north+lat_south)/2.0;
                    info_3d_elem.lon=(lon_east+lon_west)/2.0;
                    info_3d_elem.n=lat_north;
                    info_3d_elem.s=lat_south;
                    info_3d_elem.e=lon_east;
                    info_3d_elem.w=lon_west;

                    printf("N=%20.16f S=%20.16f W=%20.16f E=%20.16f\n", lat_north, lat_south, lon_west, lon_east);

                    info_3d.push_back(info_3d_elem);
                }

            } else {
                printf("#%3d NOT FOUND: X=%3d Y=%3d (EXTRA)\n",cnt,max_x,y);
            }
            cnt++;
        }

    }
    printf("\n");
//Amsterdam center
//    center_x=46;
//    center_y=103;
    center_x=0;
    center_y=0;
    center_lat=0.0;
    center_lon=0.0;
    int num_octants=0;
    for (auto v : info_3d) {
        center_x+=v.pos.x;
        center_y+=v.pos.y;
        if (v.lat!=0.0 && v.lon!=0.0) {
            num_octants++;
            center_lat+=v.lat;
            center_lon+=v.lon;
        }
    }
    if (info_3d.size()>0) {
        center_x/=info_3d.size();
        center_y/=info_3d.size();
    }
    if (num_octants>0) {
        center_lat/=num_octants;
        center_lon/=num_octants;
    }

    sort_lat_lon=false;
    if (my_area=="DenHaag") {
//        center_x=22;
//        center_y=23;
    } else if (my_area=="Amsterdam") {
        center_x=43;
        center_y=100;
    } else if (my_area=="Utrecht") {
        center_x=227;
        center_y=129;
    } else if (my_area=="Holland") {
        //center
//        center_x=337;
//        center_y=528;
        // Breda
        center_x=276;
        center_y=323;

//        sort_lat_lon=true;
/*        lat_lon_center.push_back(glm::dvec2(51.438273, 5.478636)); // Eindhoven
        lat_lon_center.push_back(glm::dvec2(51.368637, 6.163314)); // Venlo
        lat_lon_center.push_back(glm::dvec2(51.561469, 5.083881)); // Tilburg
        lat_lon_center.push_back(glm::dvec2(51.589059, 4.777077)); // Breda
        lat_lon_center.push_back(glm::dvec2(51.480162, 3.603747)); // Middelburg
        lat_lon_center.push_back(glm::dvec2(50.849641, 5.699629)); // Maastricht
        lat_lon_center.push_back(glm::dvec2(52.265415, 6.793167)); // Hengelo
        lat_lon_center.push_back(glm::dvec2(52.217449, 6.892678)); // Enschede
        lat_lon_center.push_back(glm::dvec2(52.512940, 6.096484)); // Zwolle
        lat_lon_center.push_back(glm::dvec2(53.218785, 6.567774)); // Groningen
        lat_lon_center.push_back(glm::dvec2(53.199248, 5.798004)); // Leeuwarden
        lat_lon_center.push_back(glm::dvec2(52.644307, 4.762205)); // Alkmaar
        lat_lon_center.push_back(glm::dvec2(52.670016, 4.838258)); // Heerhugowaard
        lat_lon_center.push_back(glm::dvec2(51.452968, 3.582514)); // Middelburg
        lat_lon_center.push_back(glm::dvec2(52.375488, 4.900063)); // Amsterdam
*/

//        lat_lon_center.push_back(glm::vec2());
//        center_x=227;
//        center_y=129;
    } else if (my_area=="Rio") {
        center_x=80;
        center_y=22;
//        center_x=60;
//        center_y=108;
    } else if (my_area=="NewYork") {
        center_x=65;
        center_y=51;
        center_lat=40.689242;
        center_lon=-74.044540;
//        sort_lat_lon=true;
    }

    if (!file_exists("sort_octants.off")) {
        if (crossing>0 && my_area!="Models" && my_area!="Canvas") {
    //    if (crossing>0 && crossing!=3) {
            printf("Sorting square\n");
            sort(info_3d.begin(), info_3d.end());
            for (auto v : info_3d) {
                    printf(".");
    //            printf("SORTED: X=%4d Y=%4d %s\n",v.pos.x,v.pos.y,v.filename.c_str());
            }
            printf("\n");
        }
    }
    sort_lat_lon=false;

    cnt=0;
    char new_file_raw[100];
    char new_file_dat[100];
    for (auto v : info_3d) {
        if (crossing==2 && mirror==4) {
//utrecht
            if (crossing>0) {
                std::string str;
                get_area_quick=true;
                str=get_area_data(my_area,v.pos.x,v.pos.y);
                get_area_quick=false;
                sprintf(new_file_dat,"../cut/done/%s.DAT",str.c_str());
                if (file_exists(new_file_dat)) {
                    printf("%s exists                    \r",new_file_dat);
                    cnt++;
                    continue;
                }
            }

            v.filename=get_area_data(my_area,v.pos.x,v.pos.y); //update when moved...

            if (!(v.filename=="")) {
                std::string mtl=str;
                if (mtl.find_last_of(".") != std::string::npos) mtl=mtl.substr(0,mtl.find_last_of("."))+".mtl";
                if (!file_exists(mtl.c_str())) {
                    printf("\nNo .mtl file: %s                 \n",mtl.c_str());
                    continue;
                }
            }

            if (v.filename=="") {
                printf("NOT FOUND: X=%3d Y=%3d X=%3d Y=%3d        \r",v.pos.x,v.pos.y,v.pos2.x,v.pos2.y);

                printf("Doesn't exist, skipping: %s\n",v.filename);
                char out[1000];
                sprintf(out,"echo OCTANT NOT FOUND [%3d][%3d] [%3d][%3d]>>octant_not_found.txt\n",v.pos.x,v.pos.y,v.pos2.x,v.pos2.y);
                system(out);
                continue;

            }
            std::string fn = v.filename;

            fn=GetFileName(fn.substr(0,fn.find_last_of(".")));


            if (crossing==3) {
                if (MCEDITOR_stop==1) return true;
//                scan_image.create(512,512);
                sprintf(new_file_raw,"../cut/%s.RAW",fn.c_str());
                if (file_exists(new_file_raw)) {
                    printf("%s exists\n",new_file_raw);
                    sprintf(new_file_dat,"../cut/%s.DAT",fn.c_str());
                    if (file_exists(new_file_dat)) {
                        printf("And %s exists, crossing==3, scanning/reporting\n",new_file_dat);
                        if (mirror>=1) {
                            scan_done0_plot(report, new_file_dat,new_file_raw);
                            cnt++;
                            continue;
                        }
                        else
                            scan_done0(report, new_file_dat,new_file_raw);

                    }
                } else {
                    sprintf(new_file_raw,"../cut/done/%s.RAW",fn.c_str());
                    if (file_exists(new_file_raw)) {
                        printf("%s exists\n",new_file_raw);
                        sprintf(new_file_dat,"../cut/done/%s.DAT",fn.c_str());
                        if (file_exists(new_file_dat)) {
                            printf("And %s exists, crossing==3, scanning/reporting\n",new_file_dat);
                            if (mirror>=1) {
                                scan_done0_plot(report, new_file_dat,new_file_raw);
                                cnt++;
                                continue;
                            }
                            else
                                scan_done0(report, new_file_dat,new_file_raw);
                        }
                    }
                }

                if (crossing==3) {
//                    mkdir("test");
                    char fn[200];
                    sprintf(fn,"report_sub.txt");
//                    sprintf(fn,"test/%s",v.filename.c_str());
                    report = fopen ( fn , "w" );
                    fprintf(report, "\n");
                    fprintf(report,"X=    0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4 4 4 4 4 4 4 5 5 5 5 5 5 5 5 5 5 6 6 6 6 6 6 6 6 6 6 7 7 7 7 7 7 7 7 7 7 8 8 8 8 8 8 8 8 8 8 9 9 9 9 9 9 9 9 9 9 \n");
                    fprintf(report,"      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 \n");
        //            printf("Y=  0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4 4 4 4 4 4 4 5 5 5 5 5 5 5 5 5 5 6 6 6 6 6 6 6 6 6 6 7 7 7 7 7 7 7 7 7 7 8 8 8 8 8 8 8 8 8 8 9 9 9 9 9 9 9 9 9 9 \n");
        //            printf("Y=  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 \n");

                    for (int z=0; z<100; z++) {
//                        printf("Z=%2d ",z);
                        fprintf(report,"Z=%2d ",z);
                        for (int x=0; x<100; x++) {
//                            printf("%d ",region_counter[x][z]);
                            if (region_counter[x][z]>=9)
                                fprintf(report, " *");
                            else
                                fprintf(report, " %d",region_counter[x][z]);
                        }
//                        printf("\n");
                        fprintf(report,"\n");
                    }
                    fclose(report);
                }

                continue;
            }

            sprintf(new_file_dat,"../cut/%s.DAT",fn.c_str());
            if (file_exists(new_file_dat)) {
                printf("%s exists\n",new_file_dat);
                cnt++;
                continue;

                sprintf(new_file_raw,"../cut/%s.RAW",fn.c_str());
                if (file_exists(new_file_raw)) {
                    if (crossing==2)
                        printf("And %s exists, skipping\n",new_file_raw);
                    else {
                        printf("And %s exists, crossing==1, converting\n",new_file_raw);
                        main_mceditor5_from_file(new_file_dat,new_file_raw);
                    }
                    continue;
                }
            }

            sprintf(new_file_dat,"../cut/done/%s.DAT",fn.c_str());
            if (file_exists(new_file_dat)) {
                printf("%s exists\n",new_file_dat);
                cnt++;

                continue;

                sprintf(new_file_raw,"../cut/done/%s.RAW",fn.c_str());
                if (file_exists(new_file_raw)) {
                    printf("And %s exists, skipping\n",new_file_raw);
                    continue;
                }
            }

        }

        std::string nbt_filename;
//            std::string str=get_area_data(my_area,v.pos.x,v.pos.y);

        nbt_filename=v.filename;
        std::string nbt_filename_file;

        if (strstr(nbt_filename.c_str(), "/nbt/") != NULL) {
            if (nbt_filename.find_last_of(".") != std::string::npos) nbt_filename=nbt_filename.substr(0,nbt_filename.find_last_of("."))+".nbt";
        }
//        nbt_filename_file=GetFileName(nbt_filename.c_str());

        burn=true;
        window.setActive(true);

        if (crossing==2 && mirror==4 || MAKE_NBT) to_gpu=false;

        while (Pacman_Objects[win_num].size()>1) {
//            printf("Erasing: X=%d,Y=%d\n",Pacman_Objects[win_num][0].map_x,Pacman_Objects[win_num][0].map_y);
            erase_one_pacman_objects(Pacman_Objects[win_num][1].map_x,Pacman_Objects[win_num][1].map_y,win_num,pac_obj2_arr_used,pac_obj2_arr);
        }

//wuppie
//ayay
        if (strstr(nbt_filename.c_str(), ".obj") != NULL || (crossing>0 && strstr(nbt_filename.c_str(), ".nbt") != NULL)) {
//        if (!file_exists(nbt_filename.c_str()) || strstr(nbt_filename.c_str(), ".obj") != NULL) {
            if (crossing>0)
                printf("\r#%3d CONVERTING TO MINECRAFT FILES: X=%4d Y=%4d %s\n",cnt,v.pos.x,v.pos.y,v.filename.c_str());
            else
                printf("\r#%3d CONVERTING: X=%4d Y=%4d %s\n",cnt,v.pos.x,v.pos.y,v.filename.c_str());

//willem
//            std::string str=get_area_data(my_area,v.pos.x,v.pos.y);
            std::string str=v.filename;

            int i;
            for (i=0; i<100; i++) {
                if (pac_obj2_arr_used[i]==false) {
//                    printf("Free loc. %d ",i);
                    break;
                }
            }
            if (i==100) { printf("\nError, i>100, adapt pac_obj2_arr size > 100"); return false; }

            pac_obj2_arr[i].bmin[0] = pac_obj2_arr[i].bmin[1] = pac_obj2_arr[i].bmin[2] = std::numeric_limits<float>::max();
            pac_obj2_arr[i].bmax[0] = pac_obj2_arr[i].bmax[1] = pac_obj2_arr[i].bmax[2] = -std::numeric_limits<float>::max();
            pac_obj2_arr[i].gDrawObjects.clear();
            pac_obj2_arr[i].materials.clear();
            pac_obj2_arr[i].textures.clear();
            pac_obj2_arr[i].show=0;
//wuppie
            if (crossing>0) {
                do_wuppie=true;
                burn=true;
//                if (!(cnt%10)) voxel_to_file=true;
                if (cnt==info_3d.size()-1) {
                    flushing=true;
                    voxel_to_file=true;
                }
            }
//serious failure part 2
//            lat_global=v.lat;
//            lon_global=v.lon;
            char kutjelikken[200];
//utrecht

//            sprintf(kutjelikken,"N=%lf S=%lf W=%lf E=%lf", v.n, v.s, v.w, v.e);
            sprintf(kutjelikken,"N=%20.16f S=%20.16f W=%20.16f E=%20.16f", v.n, v.s, v.w, v.e);
//            printf("kutjelikken,N=%20.16f S=%20.16f W=%20.16f E=%20.16f\f", v.n, v.s, v.w, v.e);
//            sprintf(kutjelikken,"N=%f S=%f W=%f E=%f", v.n, v.s, v.w, v.e);
            latitude_longditude=kutjelikken;
//            printf("latitude_longditude=%s\n",latitude_longditude.c_str());
            global_octant_x=v.pos.x;
            global_octant_y=v.pos.y;

//            if (crossing==2 && mirror==4 || MAKE_NBT) to_gpu=false;
            if (true == LoadObjAndConvert_window(pac_obj2_arr[i].bmin, pac_obj2_arr[i].bmax, pac_obj2_arr[i].gDrawObjects, pac_obj2_arr[i].materials, pac_obj2_arr[i].textures, (char*) str.c_str()))
            {
                pac_obj2_arr[i].map_x=v.pos.x;
                pac_obj2_arr[i].map_y=v.pos.y;

                pac_obj2_arr[i].arr_index=i;
                pac_obj2_arr[i].show=1;
                pac_obj2_arr_used[i]=true;

                Pacman_Objects[win_num].push_back(pac_obj2_arr[i]);
            } else {
                printf("Error loading new object: (%d,%d): %s\n",v.pos.x,v.pos.y,str.c_str());
                char out[1000];
                sprintf(out, "echo Error loading new object: (%d,%d): %s>>LOADOBJOBJECT_ERROR.TXT\n",v.pos.x,v.pos.y,str.c_str());
                system(out);
                if ((crossing==2 && mirror==4) || MAKE_NBT) to_gpu=true;
                continue;
//                if (crossing>0) {
//                    voxel_to_file=true;
//                }
//                window.setActive(false);
//                nbt_creating=false;
//                return true;
            }
            if ((crossing==2 && mirror==4)  || MAKE_NBT) to_gpu=true;

        } else {
            printf("\r#%3d NBT EXISTS: X=%4d Y=%4d %s\n",cnt,v.pos.x,v.pos.y,nbt_filename.c_str());
        }
        cnt++;
//wuppie
/*
        if (crossing==2) {
            std::string fn = v.filename;
            fn=GetFileName(fn.substr(0,fn.find_last_of(".")));
            char new_file[100];
            sprintf(new_file,"../cut/%s.RAW",fn.c_str());
            CopyFile("../cut/voxel.raw",new_file,false);
            sprintf(new_file,"../cut/%s.DAT",fn.c_str());
            CopyFile("../cut/voxel.dat",new_file,false);
        }
*/
        if (flushing) {
            printf("FLUSHED....\n");
extern bool automate;
extern char send_message;
            flushing=false;
            if (automate) send_message='x';
        }
    }
    if (crossing==3) {
        report = fopen ( "report.txt" , "a" );
        fprintf(report, "\n");
        fprintf(report,"X=    0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4 4 4 4 4 4 4 5 5 5 5 5 5 5 5 5 5 6 6 6 6 6 6 6 6 6 6 7 7 7 7 7 7 7 7 7 7 8 8 8 8 8 8 8 8 8 8 9 9 9 9 9 9 9 9 9 9 \n");
        fprintf(report,"      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 \n");
        printf("X=    0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4 4 4 4 4 4 4 5 5 5 5 5 5 5 5 5 5 6 6 6 6 6 6 6 6 6 6 7 7 7 7 7 7 7 7 7 7 8 8 8 8 8 8 8 8 8 8 9 9 9 9 9 9 9 9 9 9 \n");
        printf("      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 \n");

        for (int z=0; z<100; z++) {
            printf("Z=%2d ",z);
            fprintf(report,"Z=%2d ",z);
            for (int x=0; x<100; x++) {
                printf("%d ",region_counter[x][z]);
                fprintf(report, " %d",region_counter[x][z]);
            }
            printf("\n");
            fprintf(report,"\n");
        }
        fclose(report);
    }
    while (Pacman_Objects[win_num].size()>1) {
//            printf("Erasing: X=%d,Y=%d\n",Pacman_Objects[win_num][0].map_x,Pacman_Objects[win_num][0].map_y);
        erase_one_pacman_objects(Pacman_Objects[win_num][1].map_x,Pacman_Objects[win_num][1].map_y,win_num,pac_obj2_arr_used,pac_obj2_arr);
    }
    printf("\n");
    nbt_creating=false;
    burn=false;
    return 1;
}

bool Make_Canvas() {
    std::vector<BufferObject> buffers;
    std::vector<tinyobj::material_t> materials;
    float bmin[3];
    float bmax[3];
    float btotmin[3];
    float btotmax[3];
    btotmin[0] = btotmin[1] = btotmin[2] = std::numeric_limits<float>::max();
    btotmax[0] = btotmax[1] = btotmax[2] = -std::numeric_limits<float>::max();

    char filename[2000];
    int picturex,picturey;

    for (picturey=0; picturey<BITMAPSY; picturey++) {
        for (picturex=0; picturex<BITMAPSX; picturex++) {
            CANVAS_OBJECT3D(buffers, materials, filename, bmin, bmax, picturex, picturey);
            for (int k=0; k<3; k++) {
                btotmin[k] = std::min(bmin[k], btotmin[k]);
                btotmax[k] = std::max(bmax[k], btotmax[k]);
            }
        }
    }
    sprintf(filename,"%s/canvas.nbt", MODELS);
    OBJECT3D_TO_NBT(buffers, materials, filename, btotmin,btotmax);
    sprintf(filename,"cd %s && %s/makelist.bat",MODELS,MODELS);
   	while (replace_str(filename,"/","\\"));
    system(filename);
    return true;
}
extern bool MAKE_NBT_EXTERN;

bool create_nbt_fast(std::string my_area, sf::RenderWindow& window, int win_num, bool pac_obj2_arr_used[100], Pacman_Object pac_obj2_arr[100]) {
    ShowTaskBar(true);
    bar_on[win_num]=1;
    FILE* report;
//    int region_counter[200][200];
    if (crossing==2 && mirror==3) {
        float minimum[3];
        float maximum[3];
        std::vector<BufferObject> buffers;
        std::vector<tinyobj::material_t> materials;
//                flushing=true;
        WUPPIE_SUBS(buffers, materials, minimum, maximum, 0, 0, my_area);
        return true;

    } else if (crossing==2 && mirror==4) {
        report = fopen ( "report.txt" , "w+" );
        fprintf(report,"Report area=%s\n",my_area.c_str());
        fclose(report);
        if (crossing==2 && mirror==4) {
//            voxels_total.clear();
            if (load_voxels()) {
                if (voxels_total.size()>0) {
                    float minimum[3];
                    float maximum[3];
                    std::vector<BufferObject> buffers;
                    std::vector<tinyobj::material_t> materials;
    //                flushing=true;
                    WUPPIE_SUBS(buffers, materials, minimum, maximum, 0, 0, my_area);
                    return true;
                }
            }
        }
    }

    nbt_creating=true;

    ShowTaskBar(true);
    info_3d.clear();
    info_3d_struct info_3d_elem;
    sf::Event event;

    int x=0,y=0;

    int max_x =-std::numeric_limits<int>::max();
    int max_y =-std::numeric_limits<int>::max();;

    int min_x = std::numeric_limits<int>::max();
    int min_y = std::numeric_limits<int>::max();;


    std::string str;

    FILE *file_arr;
    char line[200];
    int cnt=0;
    printf("Area=%s\n",my_area.c_str());
    std::string OA;
    if (MAKE_NBT) OA="OBJECT_ARRAY.NBT";
    else  OA="OBJECT_ARRAY.TXT";
    if ((file_arr = fopen (OA.c_str(), "r"))!=NULL) {
//    if (0 && (file_arr = fopen ("OBJECT_ARRAY.TXT", "r"))!=NULL) {
        printf("%s detected. Loading object array data...\n",OA.c_str());
        while (fgets (line,200, file_arr)!=NULL ) {
            x=-1;y=-1;
//            printf("line=%s\n",line);
            if (line[0]=='R') {
                int x1=-1,x2=-1,y1=-1,y2=-1;
                int num=sscanf(line,"R:X=%d/%d Y=%d/%d\n", &x1, &x2, &y1, &y2);
                if (num!=4) { printf("Error reading object_array.txt\n"); fclose(file_arr); return false; }
                fclose(file_arr);
                if ((file_arr = fopen ("OBJECT_ARRAY2.TXT", "w"))!=NULL) {
                    for (int x=x1; x<=x2; x++) {
                        for (int y=y1; y<=y2; y++) {
                            fprintf(file_arr,"X=%d Y=%d\n",x,y);
                        }
                    }
                    fclose(file_arr);
                    if ((file_arr = fopen ("OBJECT_ARRAY2.TXT", "r"))!=NULL) {
                        fgets (line,200, file_arr);
                    } else {
                        printf("error opening: OBJECT_ARRAY2.TXT\n");
                    }

                } else {
                    printf("error writing to: OBJECT_ARRAY2.TXT\n");
                    return false;
                }
            }
            int num=sscanf(line,"X=%d Y=%d\n", &x, &y);
            cnt++;

            if (num==2 && line[0]=='X' && x!=-1 && y!=-1) {
                if (!MAKE_NBT_EXTERN) window.pollEvent(event);
//                to_check_pos.push_back(glm::vec2(x,y));
//                str=get_area_data(my_area,x,y);
//                to_check_filename.push_back(str);

                printf("MAKING: X=%4d Y=%4d    \r",x,y);
                bool ERR=false;
                for (auto v : info_3d) {
                    if (v.pos.x==x && v.pos.y==y) {
                        ERR=true;
                        printf("DOUBLE X=%4d Y=%4d           \n",x,y);
                    }
                }
                if (ERR) continue;
                if (x<min_x) min_x=x;
                if (y<min_y) min_y=y;
                if (x>max_x) max_x=x;
                if (y>max_y) max_y=y;
                info_3d_elem.pos=glm::ivec2(x,y);
                info_3d_elem.pos2=glm::ivec2(x,y);

                get_area_quick=true;
                str=get_area_data(my_area,x,y);
                get_area_quick=false;

                info_3d_elem.filename=str;

                lat_north=0.0;
                lat_south=0.0;
                lon_west=0.0;
                lon_east=0.0;
                if (latitude_longditude!="") {
                    char line[2000];
                    strcpy(line,latitude_longditude.c_str());
        //decimal_point
        //decimal_point
                    while (replace_str(line,",","."));
        //                        while (replace_str(line,".",","));
                    int num=sscanf(line,"N=%lf S=%lf W=%lf E=%lf", &lat_north, &lat_south, &lon_west, &lon_east);
                }
                info_3d_elem.lat=(lat_north+lat_south)/2.0;
                info_3d_elem.lon=(lon_east+lon_west)/2.0;
                info_3d_elem.n=lat_north;
                info_3d_elem.s=lat_south;
                info_3d_elem.e=lon_east;
                info_3d_elem.w=lon_west;




                info_3d.push_back(info_3d_elem);
                cnt++;


                max_x=-1;max_y=-1;
                get_area_data(my_area,max_x,max_y);
                for (int yyy=0; yyy<extra_octants; yyy++) {
                    if (!MAKE_NBT_EXTERN) window.pollEvent(event);
                    get_area_quick=true;
                    str=get_area_data(my_area,max_x,yyy);
                    get_area_quick=false;
                    if (str!="") {


        //                printf(".");
//                        printf("#%3d FOUND: X=%3d Y=%3d %s (EXTRA)  ",cnt,max_x,y,str.c_str());

                        std::string to_test=extra_octants_belong_to_string_pointer[yyy];
                        char octant[100];
                        int xx,yy;
                        int num=sscanf(to_test.c_str(),"%100[^ ] X=%d Y=%d", octant, &xx, &yy);

                        if (xx==x && yy==y) {
                            printf("\n#%3d FOUND: X=%3d Y=%3d %s (EXTRA)\n",cnt,max_x,yyy,str.c_str());

                            if (num==3) {
                                info_3d_elem.filename=str;
//                                str=get_area_data(my_area,max_x,yyy);
//                                info_3d_elem.filename=str;
                                info_3d_elem.pos=glm::ivec2(max_x,yyy);
                                info_3d_elem.pos2=glm::ivec2(xx,yy);
//                                printf("Relocating       (%d,%d) to \"%s\"    \r",max_x,yyy,to_test.c_str());

                                get_area_quick=true;
                                str=get_area_data(my_area,xx,yy);
                                get_area_quick=false;

                                lat_north=0.0;
                                lat_south=0.0;
                                lon_west=0.0;
                                lon_east=0.0;
                                if (latitude_longditude!="") {
                                    char line[2000];
                                    strcpy(line,latitude_longditude.c_str());
                        //decimal_point
                        //decimal_point
                                    while (replace_str(line,",","."));
                        //                        while (replace_str(line,".",","));
                                    int num=sscanf(line,"N=%lf S=%lf W=%lf E=%lf", &lat_north, &lat_south, &lon_west, &lon_east);
                                }
                                info_3d_elem.lat=(lat_north+lat_south)/2.0;
                                info_3d_elem.lon=(lon_east+lon_west)/2.0;
                                info_3d_elem.n=lat_north;
                                info_3d_elem.s=lat_south;
                                info_3d_elem.e=lon_east;
                                info_3d_elem.w=lon_west;

                                info_3d.push_back(info_3d_elem);
                                cnt++;
                                break;
                            } else {
                                printf("Can not relocate (%d,%d) to \"%s\"    \r",max_x,yyy,to_test.c_str());
                            }
                        }
                    }
                }
            }
        }
        fclose(file_arr);
    } else {
//        printf("No OBJECT_ARRAY.TXT found, using corner octants...\n");
        max_x=-1;max_y=-1;
        get_area_data(my_area,max_x,max_y);
//        printf("max_x=%d max_y=%d\n",max_x,max_y);
        min_x=0;min_y=0;
        for (y=0; y<max_y; y++) {
            for (x=0; x<max_x; x++) {
                if (!MAKE_NBT_EXTERN) window.pollEvent(event);
//wuppie

                if (my_area == "Amsterdam" || my_area == "NewYork")
                    if (!(x>1 && x<max_x-1 && y>1 && y<max_y-1)) continue; //outline //used on coords amsterdam

//                if (x!=0 && x!=max_x-1 && y!=0 && y!=max_y-1) continue; //outline
//                if (!(  (x==0 && (y==0 || y==max_y-1)) || (x==max_x-1 && (y==0 || y==max_y-1))  )) continue; //corners
//                str=get_area_data(my_area,x,y);
//                printf("Filename x=%d y=%d = %s\n",x,y,str.c_str());
                get_area_quick=true;
                str=get_area_data(my_area,x,y);
                get_area_quick=false;
                if (str!="") {
//                    printf(".");
                    printf("#%3d MAKING: X=%3d Y=%3d   \r",cnt,x,y);
//                    printf("lat/lon   : \"%s\"\n",latitude_longditude.c_str());
//                    info_3d_elem.filename=str;
                    info_3d_elem.pos=glm::ivec2(x,y);
                    info_3d_elem.pos2=glm::ivec2(x,y);

                    info_3d_elem.filename=str;
                    lat_north=0.0;
                    lat_south=0.0;
                    lon_west=0.0;
                    lon_east=0.0;
                    if (latitude_longditude!="") {
                        char line[2000];
                        strcpy(line,latitude_longditude.c_str());
            //decimal_point
            //decimal_point
                        while (replace_str(line,",","."));
            //                        while (replace_str(line,".",","));
                        int num=sscanf(line,"N=%lf S=%lf W=%lf E=%lf", &lat_north, &lat_south, &lon_west, &lon_east);
                    }
                    info_3d_elem.lat=(lat_north+lat_south)/2.0;
                    info_3d_elem.lon=(lon_east+lon_west)/2.0;
                    info_3d_elem.n=lat_north;
                    info_3d_elem.s=lat_south;
                    info_3d_elem.e=lon_east;
                    info_3d_elem.w=lon_west;

                    info_3d.push_back(info_3d_elem);
                } else {
                    printf("#%3d NOT FOUND: X=%3d Y=%3d                            \r",cnt,x,y);
                }

                cnt++;
            }
        }

        max_x=-1;max_y=-1;
        get_area_data(my_area,max_x,max_y);
        for (y=0; y<extra_octants; y++) {
            if (!MAKE_NBT_EXTERN) window.pollEvent(event);
            get_area_quick=true;
            str=get_area_data(my_area,max_x,y);
            get_area_quick=false;
            if (str!="") {
                info_3d_elem.filename=str;

                printf("#%3d CREATE: X=%3d Y=%3d %s (EXTRA)  \n",cnt,max_x,y,str.c_str());

                std::string to_test=extra_octants_belong_to_string_pointer[y];
                char octant[100];
                int xx,yy;
                int num=sscanf(to_test.c_str(),"%100[^ ] X=%d Y=%d", octant, &xx, &yy);
                if (num==3) {

                    info_3d_elem.pos=glm::ivec2(max_x,y);
                    info_3d_elem.pos2=glm::ivec2(xx,yy);
//                    info_3d_elem.filename=str;

                    get_area_quick=true;
                    str=get_area_data(my_area,xx,yy);
                    get_area_quick=false;

                    lat_north=0.0;
                    lat_south=0.0;
                    lon_west=0.0;
                    lon_east=0.0;
                    if (latitude_longditude!="") {
                        char line[2000];
                        strcpy(line,latitude_longditude.c_str());
                        while (replace_str(line,",","."));
                        int num=sscanf(line,"N=%lf S=%lf W=%lf E=%lf", &lat_north, &lat_south, &lon_west, &lon_east);
                    }
                    info_3d_elem.lat=(lat_north+lat_south)/2.0;
                    info_3d_elem.lon=(lon_east+lon_west)/2.0;
                    info_3d_elem.n=lat_north;
                    info_3d_elem.s=lat_south;
                    info_3d_elem.e=lon_east;
                    info_3d_elem.w=lon_west;

                    info_3d.push_back(info_3d_elem);
                }

            } else {
                printf("#%3d NOT FOUND: X=%3d Y=%3d (EXTRA)\n",cnt,max_x,y);
            }
            cnt++;
        }

    }
    printf("\n");
//Amsterdam center
//    center_x=46;
//    center_y=103;
    center_x=0;
    center_y=0;
    center_lat=0.0;
    center_lon=0.0;
    int num_octants=0;
    for (auto v : info_3d) {
        center_x+=v.pos.x;
        center_y+=v.pos.y;
        if (v.lat!=0.0 && v.lon!=0.0) {
            num_octants++;
            center_lat+=v.lat;
            center_lon+=v.lon;
        }
    }
    if (info_3d.size()>0) {
        center_x/=info_3d.size();
        center_y/=info_3d.size();
    }
    if (num_octants>0) {
        center_lat/=num_octants;
        center_lon/=num_octants;
    }

//jippie!!!
    sort_lat_lon=false;
    if (my_area=="DenHaag") {
//        center_x=22;
//        center_y=23;
    } else if (my_area=="Amsterdam") {
        center_x=43;
        center_y=100;
    } else if (my_area=="Utrecht") {
        center_x=227;
        center_y=129;
//        center_x=227;
//        center_y=129;
    } else if (my_area=="Holland") {
        //center
//        center_x=337;
//        center_y=528;
        // Breda
        center_x=276;
        center_y=323;
        sort_lat_lon=true;
//        lat_lon_center.clear();
//        lat_lon_center.push_back(glm::dvec2(51.438273, 5.478636)); // Eindhoven

        glm::ivec2 one_get_lat_lon;
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3778,	4.9057); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0363	Amsterdam
        one_get_lat_lon = GET_LAT_LON3(my_area,52.341,	4.9546); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0384	Diemen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3308,	4.932 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0437	Amsterdam-Duivendrecht
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3133,	4.8066); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0394	Schiphol
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4429,	4.9148); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0415	Landsmeer
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4905,	5.0673); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0385	Volendam
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4593,	5.0338); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0852	Monnickendam
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3851,	4.7324); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0394	Zwanenburg
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3213,	4.8636); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0362	Amstelveen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3102,	4.9074); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0437	Ouderkerk aan de Amstel
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2308,	5.1766); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0402	Hilversum
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2601,	5.1662); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1942	Bussum
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2564,	5.1821); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0402	Hilversum
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2055,	5.1312); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1696	Loosdrecht
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2724,	5.2249); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0417	Laren
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2771,	5.2116); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0376	Blaricum
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3078,	5.2383); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0406	Huizen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4169,	5.2197); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0034	Almere
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7499,	5.1284); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0420	Wervershoof
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3453,	5.1469); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0034	Almere
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3082,	5.0381); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0457	Weesp
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2731,	4.9723); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0736	Abcoude
        one_get_lat_lon = GET_LAT_LON3(my_area,52.273,	5.0269); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1904	Nigtevecht
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2527,	5.0492); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1696	Nederhorst den Berg
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2592,	4.976 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0736	Baambrugge
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3326,	5.0711); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1942	Muiden
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2655,	5.1954); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0402	Hilversum
        one_get_lat_lon = GET_LAT_LON3(my_area,52.266,	5.191 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1942	Bussum
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2346,	4.8346); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0451	Uithoorn
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2272,	4.8201); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0736	de Hoef
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2276,	4.7875); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0569	Vrouwenakker
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2645,	4.7465); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0358	Aalsmeer
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2662,	4.7312); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0394	Rijsenhout
        one_get_lat_lon = GET_LAT_LON3(my_area,52.5104,	4.9499); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0439	Purmerend
        one_get_lat_lon = GET_LAT_LON3(my_area,52.485,	4.9276); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0415	Purmerland
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4649,	4.9745); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0852	Ilpendam
        one_get_lat_lon = GET_LAT_LON3(my_area,52.5079,	4.9189); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0880	Wijdewormer
        one_get_lat_lon = GET_LAT_LON3(my_area,52.5139,	4.9441); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0370	Zuidoostbeemster
        one_get_lat_lon = GET_LAT_LON3(my_area,52.5314,	4.9667); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0385	Kwadijk
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4735,	4.993 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0852	Purmer
        one_get_lat_lon = GET_LAT_LON3(my_area,52.5616,	4.8597); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0361	De Rijp
        one_get_lat_lon = GET_LAT_LON3(my_area,52.5474,	4.7759); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0383	de Woude
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4379,	4.8284); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0479	Zaandam
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4468,	4.8716); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0431	Oostzaan
        one_get_lat_lon = GET_LAT_LON3(my_area,52.489,	4.7958); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0479	Wormerveer
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4951,	4.8009); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0880	Wormer
        one_get_lat_lon = GET_LAT_LON3(my_area,52.523,	4.7817); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0361	Markenbinnen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4559,	4.8099); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0479	Koog aan de Zaan
        one_get_lat_lon = GET_LAT_LON3(my_area,52.5063,	4.8474); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0880	Jisp
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4624,	4.7736); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0479	Westzaan
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7042,	5.2928); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0388	Enkhuizen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.678,	5.2383); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0498	Venhuizen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6979,	5.2356); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0532	Bovenkarspel
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6906,	5.1555); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0498	Hoogkarspel
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7443,	5.2519); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0420	Andijk
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6359,	5.0567); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0405	Hoorn
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6057,	4.9598); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1598	Oudendijk
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6013,	4.888 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0361	Schermerhorn
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6491,	4.9399); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1598	Spierdijk
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6249,	4.8699); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0361	Ursem
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6431,	5.0255); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1598	Berkhout
        one_get_lat_lon = GET_LAT_LON3(my_area,52.712,	5.0282); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0420	Benningbroek
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7308,	4.992 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0432	De Weere
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7712,	5.1085); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0420	Medemblik
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6633,	5.0633); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0405	Zwaag
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6608,	5.1067); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0498	Oosterblokker
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6714,	5.0836); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0405	Zwaag
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7006,	5.0884); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0420	Hauwert
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6644,	5.1012); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0405	Blokker
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6703,	5.0972); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0498	Oosterblokker
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6742,	4.8447); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0398	Heerhugowaard
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6586,	4.8877); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1598	Hensbroek
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6994,	4.9587); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0432	Spanbroek
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6696,	4.8015); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0416	Broek op Langedijk
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7207,	4.7914); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0441	Oudkarspel
        one_get_lat_lon = GET_LAT_LON3(my_area,52.722,	4.7861); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0416	Oudkarspel
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7619,	4.8892); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1911	Winkel
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7254,	4.8358); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0441	Waarland
        one_get_lat_lon = GET_LAT_LON3(my_area,52.8617,	4.834 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1911	Anna Paulowna
        one_get_lat_lon = GET_LAT_LON3(my_area,52.9638,	4.7703); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0400	Den Helder
        one_get_lat_lon = GET_LAT_LON3(my_area,53.0555,	4.7981); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0448	Den Burg
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0881,	4.9099); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0632	Woerden
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6274,	4.7533); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0361	Alkmaar
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6873,	4.7355); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0416	Koedijk
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6153,	4.8227); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0361	Stompetoren
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6197,	4.7206); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0399	Heiloo
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6649,	4.6864); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0373	Bergen (NH)
        one_get_lat_lon = GET_LAT_LON3(my_area,52.546,	4.6594); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0383	Castricum
        one_get_lat_lon = GET_LAT_LON3(my_area,52.5204,	4.7096); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0450	Uitgeest
        one_get_lat_lon = GET_LAT_LON3(my_area,52.5604,	4.7309); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0383	Akersloot
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6166,	4.6211); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0373	Egmond aan Zee
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4809,	4.655 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0375	Beverwijk
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4744,	4.6491); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0453	Velsen-Noord
        one_get_lat_lon = GET_LAT_LON3(my_area,52.5098,	4.6712); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0396	Heemskerk
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4626,	4.6249); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0453	IJmuiden
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3797,	4.6412); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0392	Haarlem
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3941,	4.6223); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0377	Overveen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3839,	4.6155); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0392	Haarlem
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3763,	4.5303); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0473	Zandvoort
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3856,	4.5975); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0377	Overveen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4159,	4.6754); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0392	Spaarndam gem. Haarlem
        one_get_lat_lon = GET_LAT_LON3(my_area,52.403,	4.6785); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0394	Spaarndam
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4228,	4.6402); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0453	Santpoort-Noord
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3579,	4.6223); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0397	Heemstede
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3657,	4.5789); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0377	Aerdenhout
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3438,	4.5973); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0397	Heemstede
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3461,	4.588 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0377	Vogelenzang
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3661,	4.5764); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0473	Bentveld
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3263,	4.5958); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0377	Bennebroek
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3132,	4.6938); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0394	Hoofddorp
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2141,	4.5884); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1884	Kaag
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2651,	4.559 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0553	Lisse
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2391,	4.5655); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0394	Lisserbroek
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2223,	4.5139); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1525	Sassenheim
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2896,	4.5866); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0534	Hillegom
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3001,	4.5468); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0575	De Zilk
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2221,	4.4823); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1525	Voorhout
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2069,	4.4116); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0537	Katwijk
        one_get_lat_lon = GET_LAT_LON3(my_area,52.141,	4.4078); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0629	Wassenaar
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1207,	4.4456); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0626	Voorschoten
        one_get_lat_lon = GET_LAT_LON3(my_area,52.054,	4.2284); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0518	s-Gravenhage
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1365,	4.4515); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0626	Voorschoten
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0993,	4.3924); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1916	Leidschendam
        one_get_lat_lon = GET_LAT_LON3(my_area,52.059,	4.3361); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0603	Rijswijk
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0259,	4.2839); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1783	Wateringen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1596,	4.479 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0546	Leiden
        one_get_lat_lon = GET_LAT_LON3(my_area,52.181,	4.4493); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0579	Oegstgeest
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1508,	4.5234); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0547	Leiderdorp
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1666,	4.5722); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1884	Hoogmade
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2001,	4.5103); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1525	Warmond
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1936,	4.615 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1884	Roelofarendsveen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1167,	4.4974); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0638	Zoeterwoude
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0956,	4.5994); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0484	Hazerswoude-Dorp
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0855,	4.7466); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1901	Bodegraven
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1329,	4.7623); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0569	Nieuwkoop
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1277,	4.7302); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0484	Aarlanderveen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2257,	4.6782); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1884	Leimuiden
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2128,	4.7247); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0451	De Kwakel
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2125,	4.7242); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1884	Leimuiden
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1663,	4.7068); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0569	Ter Aar
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2067,	4.6687); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1884	Rijnsaterwoude
        one_get_lat_lon = GET_LAT_LON3(my_area,52.105,	4.7299); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0484	Zwammerdam
        one_get_lat_lon = GET_LAT_LON3(my_area,52.167,	4.637 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1884	Woubrugge
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0717,	4.4004); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0518	s-Gravenhage
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0057,	4.3601); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0503	Delft
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0412,	4.391 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1926	Nootdorp
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9963,	4.3274); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1842	Den Hoorn
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0203,	4.4307); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1926	Pijnacker
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9769,	4.43  ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1621	Berkel en Rodenrijs
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9971,	4.2021); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1783	Naaldwijk
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0609,	4.4825); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0637	Zoetermeer
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0787,	4.5443); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0484	Benthuizen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0936,	4.5333); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0638	Gelderswoude
        one_get_lat_lon = GET_LAT_LON3(my_area,52.059,	4.6508); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0627	Waddinxveen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0461,	4.5785); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1892	Moerkapelle
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0911,	4.6918); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0484	Boskoop
        one_get_lat_lon = GET_LAT_LON3(my_area,52.014,	4.7001); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0513	Gouda
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0483,	4.7264); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1901	Reeuwijk
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9706,	4.7733); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1931	Stolwijk
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9948,	4.6803); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1892	Moordrecht
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0154,	4.8389); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1931	Haastrecht
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9143,	4.569 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0502	Capelle aan den IJssel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9643,	4.6215); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1892	Nieuwerkerk aan den IJssel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9126,	4.5801); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0542	Krimpen aan den IJssel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8937,	4.6224); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1931	Krimpen aan de Lek
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8642,	4.6649); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0482	Alblasserdam
        one_get_lat_lon = GET_LAT_LON3(my_area,51.89  ,	4.687 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1978	Nieuw-Lekkerland
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8659,	4.596 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0597	Ridderkerk
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8567,	4.5393); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0489	Barendrecht
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8726,	4.5894); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0597	Ridderkerk
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8487,	4.524 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0489	Barendrecht
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8349,	4.5661); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0642	Heerjansdam
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9202,	4.4811); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0599	Rotterdam
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9136,	4.4015); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0606	Schiedam
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9082,	4.3441); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0622	Vlaardingen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9213,	4.2544); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0556	Maassluis
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9774,	4.1314); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0599	Hoek van Holland
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9378,	4.2754); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1842	Maasland
        one_get_lat_lon = GET_LAT_LON3(my_area,51.857,	4.4164); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0613	Rhoon
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9015,	4.2605); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0599	Rozenburg
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8531,	4.328 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1930	Spijkenisse
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8308,	4.1308); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0530	Hellevoetsluis
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9059,	4.1768); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0501	Vierpolders
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9158,	4.108 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0614	Oostvoorne
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8778,	4.1811); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0501	Vierpolders
        one_get_lat_lon = GET_LAT_LON3(my_area,51.7537,	4.165 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1924	Middelharnis
        one_get_lat_lon = GET_LAT_LON3(my_area,51.7541, 4.1621); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1924	Goeree-Overflakkee
        one_get_lat_lon = GET_LAT_LON3(my_area,51.7146,	4.1662); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1924	Nieuwe-Tonge
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8221,	4.4217); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1963	Oud-Beijerland
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8175,	4.664 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0505	Dordrecht
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8161,	4.6507); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0642	Zwijndrecht
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8409,	4.6576); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0531	Hendrik-Ido-Ambacht
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8247,	4.6815); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0590	Papendrecht
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8166,	4.7845); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0610	Sliedrecht
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8442,	4.7625); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1978	Wijngaarden
        one_get_lat_lon = GET_LAT_LON3(my_area,51.844,	4.7555); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0610	Sliedrecht
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8447,	4.7548); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1978	Wijngaarden
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8293,	4.834 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0523	Hardinxveld-Giessendam
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8498,	4.8925); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1978	Giessenburg
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0237,	5.0404); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0353	IJsselstein
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0082,	4.9813); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0331	Benschop
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0476,	4.9509); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0335	Montfoort
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0238,	4.8715); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0589	Oudewater
        one_get_lat_lon = GET_LAT_LON3(my_area,52.037,	5.0831); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0356	Nieuwegein
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0853,	4.8798); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0632	Woerden
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1079,	5.0126); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0344	Vleuten
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0608,	4.8972); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0335	Linschoten
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0461,	4.8526); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0589	Papekop
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0325,	4.8001); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1901	Driebruggen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0173,	4.8225); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0589	Hekendorp
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1102,	4.8923); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0632	Kamerik
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0926,	5.1156); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0344	Utrecht
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1408,	5.0464); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1904	Maarssen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.139,	5.1264); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0310	Westbroek
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1716,	5.004 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1904	Breukelen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1729,	5.0694); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1696	Breukeleveen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.189,	4.9872); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1904	Nieuwer Ter Aa
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2032,	4.8637); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0736	Mijdrecht
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1531,	4.8632); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0569	Woerdense Verlaat
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1444,	4.8326); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0632	Zegveld
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1374,	4.855 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0569	Woerdense Verlaat
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0813,	5.2399); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0355	Zeist
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1143,	5.192 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0310	Bilthoven
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1454,	5.2443); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0355	Den Dolder
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1253,	5.1461); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0310	Groenekan
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2122,	5.2949); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0308	Baarn
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2543,	5.3829); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0313	Bunschoten-Spakenburg
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2608,	5.2502); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0317	Eemnes
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1827,	5.2963); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0342	Soest
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1371,	5.5946); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0203	Barneveld
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1363,	5.4965); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0327	Achterveld
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1339,	5.5172); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0203	Achterveld
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1545,	5.3882); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0307	Amersfoort
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1361,	5.4361); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0327	Leusden
        one_get_lat_lon = GET_LAT_LON3(my_area,52.164,	5.4624); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0307	Stoutenburg Noord
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3522,	5.6218); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0243	Harderwijk
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2899,	5.6155); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0233	Ermelo
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2234,	5.4845); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0267	Nijkerk
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2606,	5.5955); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0273	Putten
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2311,	5.7149); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0203	Garderen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2565,	5.7836); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0200	Uddel
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3322,	5.544 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0050	Zeewolde
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0256,	5.555 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0345	Veenendaal
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9556,	5.5751); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0340	Rhenen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0767,	5.4795); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0279	Scherpenzeel
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0744,	5.5434); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0339	Renswoude
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0843,	5.4066); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0351	Woudenberg
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0395,	5.3007); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1581	Doorn
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9955,	5.3178); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0352	Cothen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0628,	5.3713); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1581	Maarn
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9709,	5.3486); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0352	Wijk bij Duurstede
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0607,	5.3013); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1581	Driebergen-Rijsenburg
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0643,	5.2059); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0312	Bunnik
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9921,	5.1385); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1961	Ossenwaard
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0261,	5.1651); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0321	Houten
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8881,	5.4322); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0281	Tiel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.898,	5.3927); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0214	Zoelen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8811,	5.3736); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0281	Kapel Avezaath
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8814,	5.3554); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0214	Kapel-Avezaath
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8953,	5.3968); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0281	Kerk Avezaath
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9597,	5.412 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0214	Maurik
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9341,	5.5744); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1740	Kesteren
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8454,	5.3897); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1960	Ophemert
        one_get_lat_lon = GET_LAT_LON3(my_area,51.865,	5.415 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0281	Zennewijnen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8543,	5.4052); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1960	Zennewijnen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8606,	5.4138); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0281	Zennewijnen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8525,	5.4072); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1960	Zennewijnen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8608,	5.3816); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0281	Zennewijnen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8132,	5.3431); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1960	Heesselt
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9599,	5.2224); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0216	Culemborg
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9455,	5.3049); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0214	Zoelmond
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9658,	5.1555); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1961	Everdingen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8823,	5.1154); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1960	Asperen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8791,	5.0789); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1961	Oosterwijk
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8259,	5.1282); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1960	Herwijnen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9208,	5.2784); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0214	Buurmalsen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9217,	5.2793); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1960	Buurmalsen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9061,	5.3006); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0214	Buurmalsen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8944,	5.3013); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1960	Buurmalsen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8996,	5.302 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0214	Buurmalsen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9141,	5.2783); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1960	Buurmalsen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.901,	5.2944); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0214	Buurmalsen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9074,	5.2863); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1960	Buurmalsen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8974,	5.3085); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0214	Buurmalsen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.83	,4.977); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //7	0512	Gorinchem
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8403,	4.9148); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1978	Schelluinen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8562,	5.0407); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1960	Spijk
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8284,	5.009 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0512	Dalem
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8243,	5.047 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1960	Vuren
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8758,	4.9744); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1978	Hoogblokland
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9192,	4.9946); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1961	Meerkerk
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8647,	4.9976); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1978	Arkel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9033,	5.0145); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1961	Nieuwland
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8151,	4.8956); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1959	Werkendam
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6499,	3.9182); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1676	Zierikzee
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5001,	3.6118); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0687	Middelburg
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5496,	3.6685); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0717	Veere
        one_get_lat_lon = GET_LAT_LON3(my_area,51.4427,	3.5787); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0718	Vlissingen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.4948,	4.0498); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0703	Yerseke
        one_get_lat_lon = GET_LAT_LON3(my_area,51.4867,	3.9578); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0678	Kapelle
        one_get_lat_lon = GET_LAT_LON3(my_area,51.4583,	3.8992); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0654	s-Gravenpolder
        one_get_lat_lon = GET_LAT_LON3(my_area,51.4915,	3.8223); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0664	s-Heer Arendskerke
        one_get_lat_lon = GET_LAT_LON3(my_area,51.4909,	3.9273); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0678	Kloetinge
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5568,	3.801 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1695	Kortgene
        one_get_lat_lon = GET_LAT_LON3(my_area,51.3282,	3.4801); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1714	Oostburg
        one_get_lat_lon = GET_LAT_LON3(my_area,51.3259,	3.6878); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0715	Biervliet
        one_get_lat_lon = GET_LAT_LON3(my_area,51.3342,	3.6289); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1714	Biervliet
        one_get_lat_lon = GET_LAT_LON3(my_area,51.3349,	3.823 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0715	Terneuzen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.2801,	4.0499); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0677	Hulst
        one_get_lat_lon = GET_LAT_LON3(my_area,51.2625,	3.9152); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0715	Axel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.3246,	3.9861); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0677	Vogelwaarde
        one_get_lat_lon = GET_LAT_LON3(my_area,51.3008,	3.9759); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0715	Axel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.3058,	4.0067); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0677	Vogelwaarde
        one_get_lat_lon = GET_LAT_LON3(my_area,51.492,	4.2882); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0748	Bergen op Zoom
        one_get_lat_lon = GET_LAT_LON3(my_area,51.433,	4.3172); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0873	Hoogerheide
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5885,	4.3278); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0851	Steenbergen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5165,	4.3004); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0748	Halsteren
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6316,	4.3674); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0851	Dinteloord
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6518,	4.3787); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1709	Heijningen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6387,	4.3782); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0851	Dinteloord
        one_get_lat_lon = GET_LAT_LON3(my_area,51.616,	4.1623); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0716	Sint Philipsland
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5881,	4.215 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0851	Nieuw-Vossemeer
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5365,	4.2264); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0716	Tholen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5319,	4.4564); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1674	Roosendaal
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5512,	4.5929); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0840	St. Willebrord
        one_get_lat_lon = GET_LAT_LON3(my_area,51.542,	4.5135); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1674	Roosendaal
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5491,	4.5416); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0840	Rucphen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5235,	4.3899); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1674	Wouw
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5862,	4.5391); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1655	Oudenbosch
        one_get_lat_lon = GET_LAT_LON3(my_area,51.555,	4.5157); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0840	Zegge
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5834,	4.5865); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1655	Hoeven
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5655,	4.4077); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0851	Kruisland
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6115,	4.5178); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1709	Standdaarbuiten
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6676,	4.6904); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1719	Zevenbergschen Hoek
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6389,	4.6385); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1709	Langeweg
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5935,	4.7773); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0758	Breda
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6985,	4.8607); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0779	Geertruidenberg
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5951,	4.7183); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0758	Prinsenbeek
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6438,	4.752 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1719	Terheijden
        one_get_lat_lon = GET_LAT_LON3(my_area,51.609,	4.817 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0758	Teteringen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5906,	4.8636); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0826	Dorst
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5508,	4.7996); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0758	Ulvenhout
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5277,	4.7779); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1723	Galder
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5817,	4.6398); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0777	Etten-Leur
        one_get_lat_lon = GET_LAT_LON3(my_area,51.4713,	4.6578); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0879	Zundert
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6519,	4.8566); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0826	Oosterhout
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6805,	4.7996); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1719	Made
        one_get_lat_lon = GET_LAT_LON3(my_area,51.7063,	4.8622); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0779	Geertruidenberg
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5352,	4.2242); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0716	Tholen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5794,	5.0904); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0855	Tilburg
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5195,	5.0678); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0785	Goirle
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5774,	5.1369); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0855	Berkel-Enschot
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5839,	5.1607); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0824	Heukelom
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6128,	5.1524); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0855	Udenhout
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6151,	5.1838); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0788	Biezenmortel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.4839,	5.1375); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0798	Hilvarenbeek
        one_get_lat_lon = GET_LAT_LON3(my_area,51.4673,	5.2481); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0823	Oost West en Middelbeers
        one_get_lat_lon = GET_LAT_LON3(my_area,51.4049,	5.1472); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1667	Lage Mierde
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6255,	4.9346); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0766	Dongen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.4478,	4.9293); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0744	Baarle-Nassau
        one_get_lat_lon = GET_LAT_LON3(my_area,51.4301,	5.45  ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0772	Eindhoven
        one_get_lat_lon = GET_LAT_LON3(my_area,51.4473,	4.9187); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0744	Baarle-Nassau
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5905,	4.9024); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0784	Rijen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.4936,	4.9559); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1723	Alphen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.537,	4.9955); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0785	Riel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6884,	5.0484); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0867	Waalwijk
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6883,	5.116 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0797	Drunen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6782,	4.9867); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0867	Sprang-Capelle
        one_get_lat_lon = GET_LAT_LON3(my_area,51.4225,	5.4569); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0772	Eindhoven
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6563,	5.0294); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0809	Kaatsheuvel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6883,	5.2944); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0796	s-Hertogenbosch
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6942,	5.2248); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0797	Vlijmen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6811,	5.4016); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0845	Berlicum
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6691,	5.2936); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0865	Vught
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6335,	5.2321); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0788	Helvoirt
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6384,	5.3506); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0845	Sint-Michielsgestel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5915,	5.3278); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0757	Boxtel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6166,	5.3548); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0845	Gemonde
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6127,	5.2834); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0788	Esch
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5652,	5.373 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0757	Liempde
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8133,	5.2484); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0297	Zaltbommel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.7485,	5.2454); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0263	Hedel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.7729,	5.5236); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0828	Oss
        one_get_lat_lon = GET_LAT_LON3(my_area,51.7564,	5.7305); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0786	Grave
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8242,	5.5604); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0828	Megen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.7469,	5.6303); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1685	Schaijk
        one_get_lat_lon = GET_LAT_LON3(my_area,51.7071,	5.4661); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0796	Vinkel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.7132,	5.4956); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1721	Vinkel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.7165,	5.4827); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0796	Vinkel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.7139,	5.4867); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1721	Vinkel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.7101,	5.4972); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0796	Vinkel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.7114,	5.5003); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1721	Vinkel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.7167,	5.4811); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0796	Vinkel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.7105,	5.5013); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1721	Vinkel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.7069,	5.4816); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0796	Vinkel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6986,	5.4863); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1721	Vinkel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6926,	5.4533); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0796	Vinkel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.7322,	5.5328); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1721	Heesch
        one_get_lat_lon = GET_LAT_LON3(my_area,51.7425,	5.4597); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0828	Geffen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.7039,	5.5586); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1721	Nistelrode
        one_get_lat_lon = GET_LAT_LON3(my_area,51.7301,	5.4328); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0796	Nuland
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8262,	5.5023); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0828	Oijen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6618,	5.6057); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0856	Uden
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6947,	5.6793); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1685	Zeeland
        one_get_lat_lon = GET_LAT_LON3(my_area,51.554,	5.704 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1652	Gemert
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6025,	5.6731); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0755	Boekel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.7385,	5.8747); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1684	Cuijk
        one_get_lat_lon = GET_LAT_LON3(my_area,51.7419,	5.7801); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0786	Gassel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.7511,	5.8426); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1684	Linden
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6975,	5.9321); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0756	Oeffelt
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6902,	5.863 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1684	Haps
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6184,	5.7925); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1702	Landhorst
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6574,	5.8846); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0756	Rijkevoort
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6511,	5.8712); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1702	Rijkevoort-De Walsert
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6898,	5.7793); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0815	Mill
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6192,	5.54  ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1948	Veghel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6824,	5.5037); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1721	Loosbroek
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6219,	5.4292); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1948	Schijndel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.422,	5.3964); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0861	Veldhoven
        one_get_lat_lon = GET_LAT_LON3(my_area,51.3892,	5.373 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0770	Knegsel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.3895,	5.3809); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0861	Veldhoven
        one_get_lat_lon = GET_LAT_LON3(my_area,51.4006,	5.3483); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0770	Knegsel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.3715,	5.2602); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1728	Hapert
        one_get_lat_lon = GET_LAT_LON3(my_area,51.3543,	5.1612); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1667	Reusel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.344,	5.4304); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0858	Valkenswaard
        one_get_lat_lon = GET_LAT_LON3(my_area,51.3534,	5.3893); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1724	Riethoven
        one_get_lat_lon = GET_LAT_LON3(my_area,51.3898,	5.4369); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0866	Waalre
        one_get_lat_lon = GET_LAT_LON3(my_area,51.3902,	5.5759); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1658	Heeze
        one_get_lat_lon = GET_LAT_LON3(my_area,51.442,	5.4814); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0772	Eindhoven
        one_get_lat_lon = GET_LAT_LON3(my_area,51.4096,	5.5423); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1771	Geldrop
        one_get_lat_lon = GET_LAT_LON3(my_area,51.4757,	5.5393); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0820	Nuenen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5207,	5.398 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0753	Best
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5031,	5.3112); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0823	Oirschot
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5116,	5.4938); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0848	Son en Breugel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.4867,	5.6622); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0794	Helmond
        one_get_lat_lon = GET_LAT_LON3(my_area,51.3828,	5.7094); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0847	Someren
        one_get_lat_lon = GET_LAT_LON3(my_area,51.4033,	5.7429); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0743	Asten
        one_get_lat_lon = GET_LAT_LON3(my_area,51.4389,	5.601 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1771	Mierlo
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5085,	5.6366); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1659	Aarle-Rixtel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.4648,	5.8031); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0762	Deurne
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5046,	5.7455); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1652	Bakel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.444,	5.8782); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1507	Griendtsveen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.3421,	5.8848); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1894	Meijel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5226,	5.9743); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0984	Venray
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6017,	6.008 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0756	Vierlingsbeek
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6096,	5.8752); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1702	Oploo
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6219,	6.0292); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0893	Afferden L
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5296,	6.083 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0984	Wanssum
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5188,	6.0818); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1507	Meerlo
        one_get_lat_lon = GET_LAT_LON3(my_area,51.3691,	6.174 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0983	Venlo
        one_get_lat_lon = GET_LAT_LON3(my_area,51.2801,	6.0762); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0889	Reuver
        one_get_lat_lon = GET_LAT_LON3(my_area,51.4557,	6.0507); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1507	Horst
        one_get_lat_lon = GET_LAT_LON3(my_area,51.3291,	5.9812); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1894	Panningen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.2533,	5.7146); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0988	Weert
        one_get_lat_lon = GET_LAT_LON3(my_area,51.2198,	5.7975); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1640	Ell
        one_get_lat_lon = GET_LAT_LON3(my_area,51.1593,	5.8369); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1641	Thorn
        one_get_lat_lon = GET_LAT_LON3(my_area,51.2629,	5.5745); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1706	Budel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.3439,	5.6307); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1658	Sterksel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.2893,	5.7711); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0946	Nederweert
        one_get_lat_lon = GET_LAT_LON3(my_area,51.2203,	5.8432); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1640	Kelpen-Oler
        one_get_lat_lon = GET_LAT_LON3(my_area,51.1973,	5.7229); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0988	Stramproy
        one_get_lat_lon = GET_LAT_LON3(my_area,51.2135,	6.0012); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0957	Roermond
        one_get_lat_lon = GET_LAT_LON3(my_area,51.1512,	5.8928); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1641	Maasbracht
        one_get_lat_lon = GET_LAT_LON3(my_area,51.1177,	6.0359); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1669	Posterholt
        one_get_lat_lon = GET_LAT_LON3(my_area,51.1574,	5.9512); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1641	Linne
        one_get_lat_lon = GET_LAT_LON3(my_area,51.2625,	5.9855); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1640	Neer
        one_get_lat_lon = GET_LAT_LON3(my_area,51.2141,	6.0425); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0957	Swalmen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.1541,	6.007 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1669	Melick
        one_get_lat_lon = GET_LAT_LON3(my_area,51.2269,	5.9498); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1640	Haelen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.2472,	5.814 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0946	Leveroy
        one_get_lat_lon = GET_LAT_LON3(my_area,51.2456,	5.9069); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1640	Heythuysen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.193,	5.7255); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0988	Stramproy
        one_get_lat_lon = GET_LAT_LON3(my_area,51.2508,	5.903 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1640	Heythuysen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.1796,	5.9004); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1641	Heel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.1083,	5.8558); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1711	Echt
        one_get_lat_lon = GET_LAT_LON3(my_area,51.1205,	5.8375); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1641	Stevensweert
        one_get_lat_lon = GET_LAT_LON3(my_area,51.1051,	5.9079); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1711	Sint Joost
        one_get_lat_lon = GET_LAT_LON3(my_area,51.034,	5.8024); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1883	Born
        one_get_lat_lon = GET_LAT_LON3(my_area,51.0052,	5.7729); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0971	Urmond
        one_get_lat_lon = GET_LAT_LON3(my_area,50.9962,	5.8567); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1883	Sittard
        one_get_lat_lon = GET_LAT_LON3(my_area,50.9499,	5.8754); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1954	Puth
        one_get_lat_lon = GET_LAT_LON3(my_area,50.9642,	5.8166); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1883	Geleen
        one_get_lat_lon = GET_LAT_LON3(my_area,50.9799,	5.7775); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0971	Stein
        one_get_lat_lon = GET_LAT_LON3(my_area,50.9642,	5.8465); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1954	Sweikhuizen
        one_get_lat_lon = GET_LAT_LON3(my_area,50.9321,	5.8408); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0888	Spaubeek
        one_get_lat_lon = GET_LAT_LON3(my_area,50.9557,	5.7847); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0971	Elsloo
        one_get_lat_lon = GET_LAT_LON3(my_area,50.9396,	5.793 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0888	Beek
        one_get_lat_lon = GET_LAT_LON3(my_area,50.859,	5.6944); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0935	Maastricht
        one_get_lat_lon = GET_LAT_LON3(my_area,50.8732,	5.7406); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0938	Meerssen
        one_get_lat_lon = GET_LAT_LON3(my_area,50.7674,	5.7116); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1903	Eijsden
        one_get_lat_lon = GET_LAT_LON3(my_area,50.8167,	5.9021); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1729	Gulpen
        one_get_lat_lon = GET_LAT_LON3(my_area,50.771,	6.0234); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0981	Vaals
        one_get_lat_lon = GET_LAT_LON3(my_area,50.8566,	5.8355); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0994	Valkenburg
        one_get_lat_lon = GET_LAT_LON3(my_area,50.8278,	5.8476); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1903	Scheulder
        one_get_lat_lon = GET_LAT_LON3(my_area,50.864,	5.8864); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0986	Ransdaal
        one_get_lat_lon = GET_LAT_LON3(my_area,50.8315,	5.8904); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1729	Wijlre
        one_get_lat_lon = GET_LAT_LON3(my_area,50.8603,	5.7782); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0994	Berg en Terblijt
        one_get_lat_lon = GET_LAT_LON3(my_area,50.8903,	5.8182); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1954	Schimmert
        one_get_lat_lon = GET_LAT_LON3(my_area,50.8639,	5.8701); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0994	Walem
        one_get_lat_lon = GET_LAT_LON3(my_area,50.8779,	5.8828); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0986	Klimmen
        one_get_lat_lon = GET_LAT_LON3(my_area,50.8235,	5.983 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0965	Bocholtz
        one_get_lat_lon = GET_LAT_LON3(my_area,50.9118,	5.8934); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1954	Nuth
        one_get_lat_lon = GET_LAT_LON3(my_area,50.8756,	5.9355); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0986	Voerendaal
        one_get_lat_lon = GET_LAT_LON3(my_area,50.834,	5.9844); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0965	Simpelveld
        one_get_lat_lon = GET_LAT_LON3(my_area,50.9057,	6.0202); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0882	Landgraaf
        one_get_lat_lon = GET_LAT_LON3(my_area,50.8878,	5.9708); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0917	Heerlen
        one_get_lat_lon = GET_LAT_LON3(my_area,50.9373,	5.9284); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1954	Amstenrade
        one_get_lat_lon = GET_LAT_LON3(my_area,50.9516,	5.9753); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0899	Brunssum
        one_get_lat_lon = GET_LAT_LON3(my_area,50.9516,	5.9474); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1954	Merkelbeek
        one_get_lat_lon = GET_LAT_LON3(my_area,50.8683,	6.0639); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0928	Kerkrade
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8461,	5.8548); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0268	Nijmegen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8547,	5.8208); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0209	Weurt
        one_get_lat_lon = GET_LAT_LON3(my_area,51.785,	5.9297); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1945	Groesbeek
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8233,	5.8913); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0268	Nijmegen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8217,	5.8851); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1945	Heilig Landstichting
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8093,	5.8816); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0268	Nijmegen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.809,	5.8798); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1945	Heilig Landstichting
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8269,	5.9034); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0268	Nijmegen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.826,	5.9009); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1945	Berg en Dal
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8301,	5.9069); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0268	Nijmegen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8318,	5.9053); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1945	Ubbergen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8299,	5.9072); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0268	Nijmegen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8325,	5.9058); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1945	Ubbergen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.7779,	5.8531); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0252	Malden
        one_get_lat_lon = GET_LAT_LON3(my_area,51.7606,	5.8711); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0944	Molenhoek
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6941,	5.969 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0907	Gennep
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8127,	5.7199); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0296	Wijchen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.7653,	5.7809); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0252	Overasselt
        one_get_lat_lon = GET_LAT_LON3(my_area,51.7864,	5.7191); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0296	Balgoij
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8405,	5.4213); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0668	Dreumel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8155,	5.3882); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0263	Heerewaarden
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8207,	5.4744); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0668	Alphen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.858,	5.6078); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0225	Horssen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8217,	5.629 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0296	Batenburg
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8615,	5.7894); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0209	Beuningen Gld
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8929,	5.6134); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0225	Druten
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8853,	5.5635); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0668	Boven-Leeuwen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9271,	5.8438); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1734	Elst
        one_get_lat_lon = GET_LAT_LON3(my_area,51.869,	5.8539); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0268	Lent
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9648,	5.8235); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1734	Driel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9094,	5.6585); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1740	Dodewaard
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9305,	5.7145); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1734	Zetten
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8925,	5.8987); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1705	Bemmel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9681,	5.6674); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0289	Wageningen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0431,	5.6696); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0228	Ede
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9847,	5.9069); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0202	Arnhem
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9399,	5.9409); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1705	Huissen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.992,	5.8071); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0274	Oosterbeek
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0971,	5.9383); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0228	Deelen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0004,	5.985 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0275	Velp
        one_get_lat_lon = GET_LAT_LON3(my_area,52.001,	5.9608); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0277	Rozendaal
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9254,	6.0751); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0299	Zevenaar
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9539,	6.0127); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0226	Duiven
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9306,	5.968 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1705	Loo Gld
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9224,	5.9888); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0226	Loo Gld
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9713,	5.9783); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0293	Westervoort
        one_get_lat_lon = GET_LAT_LON3(my_area,51.952,	5.9853); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0226	Duiven
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9527,	5.9841); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0293	Westervoort
        one_get_lat_lon = GET_LAT_LON3(my_area,51.939,	6.1245); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1955	Didam
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0459,	6.1034); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0275	Dieren
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1071,	6.051 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0213	Eerbeek
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0654,	6.0003); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0277	Rozendaal
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0992,	6.0758); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0213	Eerbeek
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0191,	6.1316); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0221	Doesburg
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9933,	6.1307); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0299	Angerlo
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0088,	6.0239); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0275	Rheden
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0061,	6.1721); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1876	Drempt
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9665,	6.2905); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0222	Doetinchem
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0066,	6.3496); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1876	Zelhem
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9607,	6.2105); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0222	Wehl
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9392,	6.2317); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1955	Kilder
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9437,	6.4604); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1509	Varsseveld
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8637,	6.4888); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0197	Dinxperlo
        one_get_lat_lon = GET_LAT_LON3(my_area,51.975,	6.7177); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0294	Winterswijk
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9293,	6.5807); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0197	Aalten
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9864,	6.5529); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1586	Lichtenvoorde
        one_get_lat_lon = GET_LAT_LON3(my_area,52.101,	6.6536); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1859	Eibergen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1452,	6.2049); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0301	Zutphen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1594,	6.2211); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0262	Eefde
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0643,	6.1866); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1876	Steenderen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1428,	6.2213); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0301	Warnsveld
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1062,	6.2638); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1876	Vierakker
        one_get_lat_lon = GET_LAT_LON3(my_area,52.162,	6.4148); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0262	Lochem
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1031,	6.3124); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1876	Vorden
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0859,	6.4455); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1859	Ruurlo
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0218,	6.489 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1586	Mariënvelde
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1176,	6.5277); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1859	Borculo
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2166,	5.9617); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0200	Apeldoorn
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1242,	5.8345); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0228	Hoenderloo
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1353,	5.8845); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0200	Hoenderloo
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1117,	5.8765); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0228	Hoenderloo
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1563,	5.9616); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0200	Beekbergen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.171,	6.0656); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0285	Klarenbeek
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1501,	6.1417); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0213	Empe
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2477,	6.1656); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0150	Deventer
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2472,	6.1479); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0285	Steenenkamer
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3607,	6.4618); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0163	Nijverdal
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2814,	6.4249); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1742	Holten
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3261,	6.4772); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0189	Zuna
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2344,	6.5939); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1735	Goor
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1671,	6.7548); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0158	Haaksbergen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2626,	6.7126); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1735	Delden
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2185,	6.8931); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0153	Enschede
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2663,	6.7893); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0164	Hengelo
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3004,	6.8324); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1774	Deurningen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3103,	6.876 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0173	Deurningen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2632,	7.0066); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0168	Losser
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3731,	7.0108); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1774	Denekamp
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3502,	6.666 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0141	Almelo
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3791,	6.7074); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0183	Mariaparochie
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3048,	6.7255); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0147	Borne
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3251,	6.6239); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0141	Bornerbroek
        one_get_lat_lon = GET_LAT_LON3(my_area,52.41	,6.899); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1774	Ootmarsum
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3651,	6.5907); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0189	Wierden
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4027,	6.7869); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0183	Tubbergen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4134,	6.6304); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1700	Vriezenveen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4199,	6.7386); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0183	Geesteren
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4597,	6.5718); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1700	Vroomshoop
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4937,	6.5732); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0175	Beerzerveld
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4763,	6.5635); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1700	Geerdijk
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4433,	6.5771); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0163	Daarlerveen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.5266,	6.6103); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0160	Bergentheim
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4885,	6.6555); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1700	Sibculo
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4898,	6.6564); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0160	Sibculo
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4908,	6.666 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1700	Kloosterhaar
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4966,	6.6756); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0160	Kloosterhaar
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4934,	6.6719); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1700	Kloosterhaar
        one_get_lat_lon = GET_LAT_LON3(my_area,52.5035,	6.6699); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0160	Kloosterhaar
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6238,	6.482 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1690	Drogteropslagen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6009,	6.3892); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0160	Balkbrug
        one_get_lat_lon = GET_LAT_LON3(my_area,52.5745,	6.2912); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0148	Nieuwleusen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6185,	6.2684); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0180	Punthorst
        one_get_lat_lon = GET_LAT_LON3(my_area,52.5078,	6.2631); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0148	Dalfsen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.5086,	6.4227); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0175	Ommen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6682,	6.7515); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0109	Coevorden
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2644,	6.2204); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0150	Deventer
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6559,	6.7516); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0109	Coevorden
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6576,	6.8972); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0114	Schoonebeek
        one_get_lat_lon = GET_LAT_LON3(my_area,52.5761,	6.613 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0160	Hardenberg
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7817,	6.8912); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0114	Emmen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7727,	6.8028); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0109	Sleen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7142,	6.8506); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0114	Veenoord
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7319,	6.7994); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0109	Holsloot
        one_get_lat_lon = GET_LAT_LON3(my_area,52.8836,	6.7421); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1681	Eeserveen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7598,	6.7152); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0109	Oosterhesselen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.8337,	6.8587); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1681	Klijndijk
        one_get_lat_lon = GET_LAT_LON3(my_area,52.8125,	7.0476); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0114	Emmer-Compascuum
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7331,	6.4742); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0118	Hoogeveen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7389,	6.5877); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1731	Nieuweroord
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7178,	6.5615); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0118	Nieuweroord
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7273,	6.6343); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0109	Geesbrug
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7038,	6.6108); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0118	Nieuwlande
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6796,	6.4301); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1690	Zuidwolde
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7718,	6.4955); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1731	Stuifzand
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6971,	6.635 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0109	Nieuwlande Coevorden
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7339,	6.4466); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0118	Fluitenberg
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7172,	6.4018); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1690	Echten
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7728,	6.4507); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0118	Pesse
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7838,	6.4291); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1701	Pesse
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7687,	6.4561); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0118	Pesse
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7972,	6.4475); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1701	Pesse
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7896,	6.4552); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0118	Pesse
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7803,	6.4396); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1690	Eursinge
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7457,	6.5449); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0118	Tiendeveen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.765,	6.5216); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1731	Tiendeveen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6987,	6.19  ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0119	Meppel
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7047,	6.124 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1708	Wanneperveen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7304,	6.1644); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0119	Nijeveen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6471,	6.207 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0180	Staphorst
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6758,	6.2836); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1690	de Wijk
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7833,	6.375 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1701	Ruinen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7799,	6.3583); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1690	Ruinen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.784,	6.3686); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1701	Ruinen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7789,	6.3548); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1690	Ruinen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.782,	6.356 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1701	Ruinen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7772,	6.3488); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1690	Ruinen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7868,	6.3569); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1701	Ansen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7904,	6.3435); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1690	Ansen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6984,	6.2652); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0119	Broekhuizen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7787,	6.2442); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1701	Havelte
        one_get_lat_lon = GET_LAT_LON3(my_area,52.511,	6.0847); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0193	Zwolle
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4648,	6.0686); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0244	Hattem
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4681,	6.1919); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0177	Laag Zuthem
        one_get_lat_lon = GET_LAT_LON3(my_area,52.5959,	6.0921); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1896	Hasselt
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6696,	6.0511); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1708	Belt-Schutsloot
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3717,	5.7855); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0302	Nunspeet
        one_get_lat_lon = GET_LAT_LON3(my_area,52.517,	5.8745); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0269	Noordeinde Gld
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4395,	5.8244); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0230	Elburg
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4625,	5.9933); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0269	Wezep
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3889,	6.2701); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0177	Raalte
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3407,	6.106 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1773	Olst
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4353,	6.236 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0177	Heino
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4717,	6.3447); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0175	Dalmsholte
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4489,	6.3431); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0148	Lemelerveld
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3617,	5.9854); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0232	Epe
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3892,	6.043 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0246	Heerde
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3142,	6.0893); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1773	Welsum
        one_get_lat_lon = GET_LAT_LON3(my_area,52.5351,	5.5192); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0995	Lelystad
        one_get_lat_lon = GET_LAT_LON3(my_area,52.52	,5.708); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // 	0303	Dronten
        one_get_lat_lon = GET_LAT_LON3(my_area,52.5569,	5.9189); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0166	Kampen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6207,	6.0427); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1896	Genemuiden
        one_get_lat_lon = GET_LAT_LON3(my_area,52.5637,	5.9927); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0166	Mastenbroek
        one_get_lat_lon = GET_LAT_LON3(my_area,52.5674,	6.0277); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1896	Mastenbroek
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7093,	5.7524); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0171	Emmeloord
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6647,	5.609 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0184	Urk
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6811,	5.9501); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1708	Vollenhove
        one_get_lat_lon = GET_LAT_LON3(my_area,52.8103,	6.2113); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1701	Wapserveen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7537,	6.0842); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1708	Giethoorn
        one_get_lat_lon = GET_LAT_LON3(my_area,52.8572,	6.2056); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1701	Vledder
        one_get_lat_lon = GET_LAT_LON3(my_area,52.8996,	6.1713); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0098	Oosterstreek
        one_get_lat_lon = GET_LAT_LON3(my_area,52.9977,	6.0658); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0086	Gorredijk
        one_get_lat_lon = GET_LAT_LON3(my_area,52.9926,	6.0978); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0074	Jubbega
        one_get_lat_lon = GET_LAT_LON3(my_area,52.9222,	6.1124); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0085	Oldeberkoop
        one_get_lat_lon = GET_LAT_LON3(my_area,52.9211,	6.2553); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1701	Zorgvlied
        one_get_lat_lon = GET_LAT_LON3(my_area,52.9672,	5.925 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0074	Heerenveen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.9507,	5.9013); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1940	Rottum
        one_get_lat_lon = GET_LAT_LON3(my_area,52.9925,	5.881 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0074	Haskerdijken
        one_get_lat_lon = GET_LAT_LON3(my_area,52.881,	5.9893); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0098	Wolvega
        one_get_lat_lon = GET_LAT_LON3(my_area,53.0534,	5.8461); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0074	Akkrum
        one_get_lat_lon = GET_LAT_LON3(my_area,53.0378,	5.7777); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1940	Terherne
        one_get_lat_lon = GET_LAT_LON3(my_area,53.0783,	5.8314); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0074	Nes
        one_get_lat_lon = GET_LAT_LON3(my_area,53.0841,	5.9164); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0090	Goëngahuizen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.9701,	5.7904); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1940	Joure
        one_get_lat_lon = GET_LAT_LON3(my_area,52.9585,	5.6565); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1900	Koufurderrige
        one_get_lat_lon = GET_LAT_LON3(my_area,52.8369,	5.7227); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1940	Lemmer
        one_get_lat_lon = GET_LAT_LON3(my_area,52.9398,	5.6247); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1900	Woudsend
        one_get_lat_lon = GET_LAT_LON3(my_area,52.8949,	5.6462); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1940	Sloten
        one_get_lat_lon = GET_LAT_LON3(my_area,52.8799,	5.4568); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1900	Hemelum
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1849,	5.5489); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1949	Franeker
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1345,	5.4195); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1900	Kimswerd
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1555,	5.614 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1949	Winsum
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1599,	5.6678); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0080	Húns
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1653,	5.6377); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1949	Baaium
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1241,	5.6277); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1900	Hinnaard
        one_get_lat_lon = GET_LAT_LON3(my_area,53.2371,	5.5519); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1949	Tzummarum
        one_get_lat_lon = GET_LAT_LON3(my_area,53.2026,	5.4465); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0072	Wijnaldum
        one_get_lat_lon = GET_LAT_LON3(my_area,53.3586,	5.215 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0093	West-Terschelling
        one_get_lat_lon = GET_LAT_LON3(my_area,53.2962,	5.0723); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0096	Vlieland
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1978,	5.7882); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0080	Leeuwarden
        one_get_lat_lon = GET_LAT_LON3(my_area,53.0995,	5.7602); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1900	Raerd
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1285,	5.7204); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0080	Mantgum
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1773,	5.7313); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1949	Boksum
        one_get_lat_lon = GET_LAT_LON3(my_area,53.2658,	5.7561); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0080	Stiens
        one_get_lat_lon = GET_LAT_LON3(my_area,53.2364,	5.8976); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0737	Gytsjerk
        one_get_lat_lon = GET_LAT_LON3(my_area,53.272,	5.8939); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1891	Readtsjerk
        one_get_lat_lon = GET_LAT_LON3(my_area,53.2823,	5.7257); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0080	Alde Leie
        one_get_lat_lon = GET_LAT_LON3(my_area,53.2944,	5.6537); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1949	Nij Altoenae
        one_get_lat_lon = GET_LAT_LON3(my_area,53.3272,	5.804 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1970	Marrum
        one_get_lat_lon = GET_LAT_LON3(my_area,53.2859,	5.5944); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1949	Westhoek
        one_get_lat_lon = GET_LAT_LON3(my_area,53.2252,	5.8185); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0080	Lekkum
        one_get_lat_lon = GET_LAT_LON3(my_area,53.2435,	5.8331); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0737	Wyns
        one_get_lat_lon = GET_LAT_LON3(my_area,53.3316,	5.9988); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1970	Dokkum
        one_get_lat_lon = GET_LAT_LON3(my_area,53.3049,	6.0103); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1891	Damwâld
        one_get_lat_lon = GET_LAT_LON3(my_area,53.3124,	5.918 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1970	Jannum
        one_get_lat_lon = GET_LAT_LON3(my_area,53.2755,	6.0047); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1891	Broeksterwâld
        one_get_lat_lon = GET_LAT_LON3(my_area,53.3052,	5.8833); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1970	Burdaard
        one_get_lat_lon = GET_LAT_LON3(my_area,53.3029,	6.0254); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1891	Wâlterswâld
        one_get_lat_lon = GET_LAT_LON3(my_area,53.3415,	5.9956); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1970	Aalsum
        one_get_lat_lon = GET_LAT_LON3(my_area,53.4382,	5.6523); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0060	Hollum
        one_get_lat_lon = GET_LAT_LON3(my_area,53.4796,	6.1629); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0088	Schiermonnikoog
        one_get_lat_lon = GET_LAT_LON3(my_area,53.3605,	5.862 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1970	Blije
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1144,	6.0803); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0090	Drachten
        one_get_lat_lon = GET_LAT_LON3(my_area,53.0944,	6.1367); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0086	Drachten-Azeven
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1134,	6.1416); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0090	Drachten
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1767,	6.1522); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0059	Surhuisterveen
        one_get_lat_lon = GET_LAT_LON3(my_area,53.0579,	6.2062); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0086	Wijnjewoude
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1978,	5.9882); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0737	Burgum
        one_get_lat_lon = GET_LAT_LON3(my_area,53.2515,	6.0089); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1891	Feanwâlden
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1813,	6.1331); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0059	Harkema
        one_get_lat_lon = GET_LAT_LON3(my_area,53.286,	6.1464); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1970	Kollum
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1375,	6.4336); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1699	Roden
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1633,	6.3931); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1969	Leek
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1542,	6.3845); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1699	Nietap
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1603,	6.3904); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1969	Leek
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1165,	6.3653); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1699	Nieuw-Roden
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1144,	6.3604); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1969	Zevenhuizen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.9984,	6.5661); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0106	Assen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.8605,	6.5114); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1731	Beilen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.8178,	6.4592); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1701	Spier
        one_get_lat_lon = GET_LAT_LON3(my_area,52.8186,	6.4701); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1731	Spier
        one_get_lat_lon = GET_LAT_LON3(my_area,52.9098,	6.3685); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1701	Hoogersmilde
        one_get_lat_lon = GET_LAT_LON3(my_area,52.9184,	6.3859); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1731	Hoogersmilde
        one_get_lat_lon = GET_LAT_LON3(my_area,52.9043,	6.7009); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1680	Schoonloo
        one_get_lat_lon = GET_LAT_LON3(my_area,53.093,	6.6861); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1730	Zuidlaren
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1226,	6.6673); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0014	Noordlaren
        one_get_lat_lon = GET_LAT_LON3(my_area,53.0781,	6.5805); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1730	Vries
        one_get_lat_lon = GET_LAT_LON3(my_area,53.0344,	6.5721); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0106	Rhee
        one_get_lat_lon = GET_LAT_LON3(my_area,53.048,	6.5478); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1730	Zeijen
        one_get_lat_lon = GET_LAT_LON3(my_area,53.0491,	6.5744); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0106	Ubbena
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1141,	6.6035); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1730	De Punt
        one_get_lat_lon = GET_LAT_LON3(my_area,52.9925,	6.9523); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0037	Stadskanaal
        one_get_lat_lon = GET_LAT_LON3(my_area,53.0059,	6.8433); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1680	Gieterveen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.9375,	6.8872); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1681	Nieuw-Buinen
        one_get_lat_lon = GET_LAT_LON3(my_area,53.0248,	7.1043); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1950	Vlagtwedde
        one_get_lat_lon = GET_LAT_LON3(my_area,52.9185,	7.0252); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1681	Zandberg
        one_get_lat_lon = GET_LAT_LON3(my_area,53.0569,	7.1229); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1950	Veelerveen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.9003,	6.9183); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1681	2e Exloërmond
        one_get_lat_lon = GET_LAT_LON3(my_area,52.936,	7.0074); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0037	Musselkanaal
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1674,	6.7562); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1952	Hoogezand
        one_get_lat_lon = GET_LAT_LON3(my_area,53.2246,	6.6453); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0014	Meerstad
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1852,	6.7592); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1952	Kolham
        one_get_lat_lon = GET_LAT_LON3(my_area,53.252,	6.7023); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0014	Lageland GN
        one_get_lat_lon = GET_LAT_LON3(my_area,53.239,	6.7167); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1952	Lageland
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1197,	6.8177); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0047	Borgercompagnie
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1328,	6.8082); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1952	Borgercompagnie
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1068,	6.8803); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0047	Veendam
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1359,	6.8663); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1952	Muntendam
        one_get_lat_lon = GET_LAT_LON3(my_area,53.0852,	6.7905); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1680	Annerveenschekanaal
        one_get_lat_lon = GET_LAT_LON3(my_area,53.0418,	7.0241); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0037	Alteveer
        one_get_lat_lon = GET_LAT_LON3(my_area,53.0863,	6.9761); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0765	Nieuwe Pekela
        one_get_lat_lon = GET_LAT_LON3(my_area,53.141,	7.0356); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1895	Winschoten
        one_get_lat_lon = GET_LAT_LON3(my_area,53.0999,	7.1435); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1950	Bellingwolde
        one_get_lat_lon = GET_LAT_LON3(my_area,53.2137,	6.5615); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0014	Groningen
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1934,	6.4509); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1699	Matsloot
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1767,	6.601 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0014	Haren Gn
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1406,	6.5668); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1730	Eelde
        one_get_lat_lon = GET_LAT_LON3(my_area,53.2944,	6.5339); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1966	Sauwerd
        one_get_lat_lon = GET_LAT_LON3(my_area,53.2725,	6.6971); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0014	Ten Boer
        one_get_lat_lon = GET_LAT_LON3(my_area,53.2472,	6.4063); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1969	Zuidhorn
        one_get_lat_lon = GET_LAT_LON3(my_area,53.2735,	6.23  ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1970	Burum
        one_get_lat_lon = GET_LAT_LON3(my_area,53.2166,	6.2889); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1969	Grootegast
        one_get_lat_lon = GET_LAT_LON3(my_area,53.239,	6.2156); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0059	Stroobos
        one_get_lat_lon = GET_LAT_LON3(my_area,53.2867,	6.3233); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1969	Kommerzijl
        one_get_lat_lon = GET_LAT_LON3(my_area,53.3147,	6.3558); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1966	Zuurdijk
        one_get_lat_lon = GET_LAT_LON3(my_area,53.3112,	6.4053); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1969	Oldehove
        one_get_lat_lon = GET_LAT_LON3(my_area,53.32,	6.8544); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0003	Appingedam
        one_get_lat_lon = GET_LAT_LON3(my_area,53.3536,	6.8501); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0010	Krewerd
        one_get_lat_lon = GET_LAT_LON3(my_area,53.3367,	6.808 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0024	Oosterwijtwerd
        one_get_lat_lon = GET_LAT_LON3(my_area,53.3709,	6.6978); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1966	Startenhuizen
        one_get_lat_lon = GET_LAT_LON3(my_area,53.335,	6.903 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0010	Delfzijl
        one_get_lat_lon = GET_LAT_LON3(my_area,53.2782,	6.8609); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1952	Tjuchem
        one_get_lat_lon = GET_LAT_LON3(my_area,53.2208,	6.9437); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1895	t Waar
        one_get_lat_lon = GET_LAT_LON3(my_area,53.2588,	6.9268); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0010	Wagenborgen
        one_get_lat_lon = GET_LAT_LON3(my_area,53.3316,	6.5155); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1966	Winsum
        one_get_lat_lon = GET_LAT_LON3(my_area,53.4011,	6.7718); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0024	Zijldijk
        one_get_lat_lon = GET_LAT_LON3(my_area,53.4003,	6.6104); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1966	Usquert
        one_get_lat_lon = GET_LAT_LON3(my_area,53.3472,	6.6427); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	0024	Middelstum
        one_get_lat_lon = GET_LAT_LON3(my_area,53.3608,	6.6243); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); //	1966	Kantens

/*
        one_get_lat_lon = GET_LAT_LON3(my_area,51.368637, 6.163314); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon));  // Venlo
        one_get_lat_lon = GET_LAT_LON3(my_area,51.561469, 5.083881); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon));  // Tilburg
        one_get_lat_lon = GET_LAT_LON3(my_area,51.589059, 4.777077); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon));  // Breda
        one_get_lat_lon = GET_LAT_LON3(my_area,51.480162, 3.603747); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon));  // Middelburg
        one_get_lat_lon = GET_LAT_LON3(my_area,50.849641, 5.699629); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon));  // Maastricht
        one_get_lat_lon = GET_LAT_LON3(my_area,52.265415, 6.793167); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon));  // Hengelo
        one_get_lat_lon = GET_LAT_LON3(my_area,52.217449, 6.892678); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon));  // Enschede
        one_get_lat_lon = GET_LAT_LON3(my_area,52.512940, 6.096484); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon));  // Zwolle
        one_get_lat_lon = GET_LAT_LON3(my_area,53.218785, 6.567774); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon));  // Groningen
        one_get_lat_lon = GET_LAT_LON3(my_area,53.199248, 5.798004); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon));  // Leeuwarden
        one_get_lat_lon = GET_LAT_LON3(my_area,52.644307, 4.762205); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon));  // Alkmaar
        one_get_lat_lon = GET_LAT_LON3(my_area,52.670016, 4.838258); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon));  // Heerhugowaard
        one_get_lat_lon = GET_LAT_LON3(my_area,51.452968, 3.582514); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon));  // Middelburg
        one_get_lat_lon = GET_LAT_LON3(my_area,52.375488, 4.900063); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon));  // Amsterdam
*/
/*
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3778,	4.9057); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Amsterdam
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3092,	4.9311); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Amsterdam
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2308,	5.1766); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Hilversum
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4169,	5.2197); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Almere
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2804,	5.1639); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Bussum
        one_get_lat_lon = GET_LAT_LON3(my_area,52.4379,	4.8284); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Zaandam
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7042,	5.2928); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Enkhuizen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6742,	4.8447); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Heerhugowaard
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0881,	4.9099); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Woerden
        one_get_lat_lon = GET_LAT_LON3(my_area,52.546,	4.6594); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Castricum
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3797,	4.6412); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Haarlem
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3579,	4.6223); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Heemstede
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2183,	4.4334); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Noordwijk
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1596,	4.479 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Leiden
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1446,	4.6546); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Alphen aan den Rijn
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0785,	4.3123); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // s-Gravenhage
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0057,	4.3601); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Delft
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0609,	4.4825); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Zoetermeer
        one_get_lat_lon = GET_LAT_LON3(my_area,52.014,	4.7001); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Gouda
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9143,	4.569 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Capelle aan den IJssel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9202,	4.4811); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Rotterdam
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9136,	4.4015); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Schiedam
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8531,	4.328 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Spijkenisse
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8175,	4.664 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Dordrecht
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0237,	5.0404); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // IJsselstein
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0926,	5.1156); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Utrecht
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1408,	5.0464); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Maarssen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0813,	5.2399); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Zeist
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1545,	5.3882); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Amersfoort
        one_get_lat_lon = GET_LAT_LON3(my_area,52.0256,	5.555 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Veenendaal
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8881,	5.4322); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Tiel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9599,	5.2224); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Culemborg
        one_get_lat_lon = GET_LAT_LON3(my_area,51.83,	4.9777); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Gorinchem
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6499,	3.9182); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Zierikzee
        one_get_lat_lon = GET_LAT_LON3(my_area,51.4948,	4.0498); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Yerseke
        one_get_lat_lon = GET_LAT_LON3(my_area,51.3282,	3.4801); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Oostburg
        one_get_lat_lon = GET_LAT_LON3(my_area,51.492,	4.2882); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Bergen op Zoom
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5319,	4.4564); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Roosendaal
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5935,	4.7773); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Breda
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6519,	4.8566); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Oosterhout
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5794,	5.0904); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Tilburg
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6255,	4.9346); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Dongen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6883,	5.2944); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // s-Hertogenbosch
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8133,	5.2484); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Zaltbommel
        one_get_lat_lon = GET_LAT_LON3(my_area,51.6618,	5.6057); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Uden
        one_get_lat_lon = GET_LAT_LON3(my_area,51.422,	5.3964); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Veldhoven
        one_get_lat_lon = GET_LAT_LON3(my_area,51.442,	5.4814); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Eindhoven
        one_get_lat_lon = GET_LAT_LON3(my_area,51.4867,	5.6622); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Helmond
        one_get_lat_lon = GET_LAT_LON3(my_area,51.5226,	5.9743); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Venray
        one_get_lat_lon = GET_LAT_LON3(my_area,51.3691,	6.174 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Venlo
        one_get_lat_lon = GET_LAT_LON3(my_area,51.2533,	5.7146); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Weert
        one_get_lat_lon = GET_LAT_LON3(my_area,51.1083,	5.8558); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Echt
        one_get_lat_lon = GET_LAT_LON3(my_area,50.859,	5.6944); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Maastricht
        one_get_lat_lon = GET_LAT_LON3(my_area,50.8566,	5.8355); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Valkenburg
        one_get_lat_lon = GET_LAT_LON3(my_area,50.8878,	5.9708); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Heerlen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8461,	5.8548); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Nijmegen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.8127,	5.7199); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Wijchen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9681,	5.6674); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Wageningen
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9847,	5.9069); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Arnhem
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9254,	6.0751); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Zevenaar
        one_get_lat_lon = GET_LAT_LON3(my_area,51.9665,	6.2905); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Doetinchem
        one_get_lat_lon = GET_LAT_LON3(my_area,51.975,	6.7177); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Winterswijk
        one_get_lat_lon = GET_LAT_LON3(my_area,52.1452,	6.2049); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Zutphen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2166,	5.9617); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Apeldoorn
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2477,	6.1656); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Deventer
        one_get_lat_lon = GET_LAT_LON3(my_area,52.2185,	6.8931); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Enschede
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3502,	6.666 ); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Almelo
        one_get_lat_lon = GET_LAT_LON3(my_area,52.6044,	6.4529); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Dedemsvaart
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7817,	6.8912); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Emmen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7331,	6.4742); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Hoogeveen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.511,	6.0847); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Zwolle
        one_get_lat_lon = GET_LAT_LON3(my_area,52.3889,	6.2701); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Raalte
        one_get_lat_lon = GET_LAT_LON3(my_area,52.5351,	5.5192); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Lelystad
        one_get_lat_lon = GET_LAT_LON3(my_area,52.7093,	5.7524); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Emmeloord
        one_get_lat_lon = GET_LAT_LON3(my_area,52.9977,	6.0658); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Gorredijk
        one_get_lat_lon = GET_LAT_LON3(my_area,52.9701,	5.7904); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Joure
        one_get_lat_lon = GET_LAT_LON3(my_area,53.0305,	5.6629); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Sneek
        one_get_lat_lon = GET_LAT_LON3(my_area,53.0588,	5.5368); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Bolsward
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1849,	5.5489); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Franeker
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1978,	5.7882); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Leeuwarden
        one_get_lat_lon = GET_LAT_LON3(my_area,53.0977,	5.8409); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Grou
        one_get_lat_lon = GET_LAT_LON3(my_area,53.3316,	5.9988); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Dokkum
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1144,	6.0803); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Drachten
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1375,	6.4336); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Roden
        one_get_lat_lon = GET_LAT_LON3(my_area,52.9984,	6.5661); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Assen
        one_get_lat_lon = GET_LAT_LON3(my_area,52.9925,	6.9523); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Stadskanaal
        one_get_lat_lon = GET_LAT_LON3(my_area,53.1674,	6.7562); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Hoogezand
        one_get_lat_lon = GET_LAT_LON3(my_area,53.2137,	6.5615); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Groningen
        one_get_lat_lon = GET_LAT_LON3(my_area,53.2472,	6.4063); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Zuidhorn
        one_get_lat_lon = GET_LAT_LON3(my_area,53.32,	6.8544); if (one_get_lat_lon.x!=999 && one_get_lat_lon.y!=999) lat_lon_center.push_back(glm::dvec2(one_get_lat_lon)); // Appingedam
*/
    } else if (my_area=="Rio") {
        center_x=80;
        center_y=22;
//        center_x=60;
//        center_y=108;
    } else if (my_area=="NewYork") {
        center_x=65;
        center_y=51;
        center_lat=40.689242;
        center_lon=-74.044540;
//        sort_lat_lon=true;
    }

    if (!file_exists("sort_octants.off")) {
        if (1 || (crossing>0 && my_area!="Models" && my_area!="Canvas")) {
    //    if (crossing>0 && crossing!=3) {
            printf("Sorting square\n");
            sort(info_3d.begin(), info_3d.end());
            FILE* F=fopen("OCTANTS_SORTED.TXT","w");

            if (F==NULL) printf("Error opening OCTANTS_SORTED.TXT for writing\n");
            else {
                int i=0;
                //std::string str;
                //get_area_quick=true;
                for (auto v : info_3d) {
                    //str=get_area_data(my_area,v.pos.x,v.pos.y);
                    if (i++==1000) {
                        printf(".");
                        i=0;
                    }

//                    fprintf(F,"%s\n",str.c_str());
                    fprintf(F,"%s\n",v.filename.c_str());
        //            printf("SORTED: X=%4d Y=%4d %s\n",v.pos.x,v.pos.y,v.filename.c_str());
                }
//                get_area_quick=false;
                fclose(F);
            }

            printf("\n");
        }
    }
    sort_lat_lon=false;

    cnt=0;
    int cnt2=0;
    char new_file_raw[100];
    char new_file_dat[100];
    for (auto v : info_3d) {
        cnt++;

        if (crossing==2 && mirror==4) {
            std::string str;
            get_area_quick=true;
            str=get_area_data(my_area,v.pos.x,v.pos.y);
            get_area_quick=false;
            sprintf(new_file_dat,"../cut/done/%s.DAT",str.c_str());
            if (file_exists(new_file_dat)) {
                printf("%s exists                        \r",new_file_dat);
                continue;
            }

        }

        v.filename=get_area_data(my_area,v.pos.x,v.pos.y); //update when moved...
        std::string str;
        std::string fn = v.filename;
        str=v.filename;

        if (!(str=="")) {
            std::string mtl=str;
            if (mtl.find_last_of(".") != std::string::npos) mtl=mtl.substr(0,mtl.find_last_of("."))+".mtl";
            if (!file_exists(mtl.c_str())) {
                printf("\nNo .mtl file: %s                 \n",mtl.c_str());
                continue;
            }
        }

        if (str=="") {
            printf("#%3d of %3d NOT FOUND: X=%3d Y=%3d X=%3d Y=%3d      \r",cnt,cnt2+cnt,v.pos.x,v.pos.y,v.pos2.x,v.pos2.y);
            char out[1000];
            sprintf(out,"echo OCTANT NOT FOUND [%3d][%3d] [%3d][%3d]>>octant_not_found.txt\n",v.pos.x,v.pos.y,v.pos2.x,v.pos2.y);
            system(out);
//            cnt++;
            continue;
        }
        if (strstr(str.c_str(), "/nbt/") != NULL) {
            if (!(crossing==2 && mirror==4) ) {
                printf("\r#%3d NBT EXISTS: X=%4d Y=%4d %s        \r",cnt,v.pos.x,v.pos.y,str.c_str());
//                cnt++;
                continue;
            }
        }

        lat_north=0.0;
        lat_south=0.0;
        lon_west=0.0;
        lon_east=0.0;
        if (latitude_longditude!="") {
            char line[2000];
            strcpy(line,latitude_longditude.c_str());
//decimal_point
//decimal_point
            while (replace_str(line,",","."));
//                        while (replace_str(line,".",","));
            int num=sscanf(line,"N=%lf S=%lf W=%lf E=%lf", &lat_north, &lat_south, &lon_west, &lon_east);
        }
        v.lat=(lat_north+lat_south)/2.0;
        v.lon=(lon_east+lon_west)/2.0;
        v.n=lat_north;
        v.s=lat_south;
        v.e=lon_east;
        v.w=lon_west;
//                    printf("N=%lf S=%lf W=%lf E=%lf\n", lat_north, lat_south, lon_west, lon_east);
        printf("N=%20.16f S=%20.16f W=%20.16f E=%20.16f   \r", lat_north, lat_south, lon_west, lon_east);


        if (crossing>0) {
//utrecht
//            cnt++;
            if (str!="") {
//                    printf(".");
//utrecht2
                printf("#%3d FOUND: X=%3d Y=%3d %s  ",cnt,v.pos.x,v.pos.y,str.c_str());
//                    printf("lat/lon   : \"%s\"\n",latitude_longditude.c_str());
                info_3d_elem.filename=str;
//                info_3d_elem.pos=glm::ivec2(x,y);

//                info_3d.push_back(info_3d_elem);
            } else {
                printf("#%3d of %3d NOT FOUND: X=%3d Y=%3d         \r",cnt2,cnt,v.pos.x,v.pos.y);
                cnt2++;
              continue;
            }

            fn=GetFileName(fn.substr(0,fn.find_last_of(".")));

            if (crossing==3) {
                if (MCEDITOR_stop==1) return true;
//                scan_image.create(512,512);
                sprintf(new_file_raw,"../cut/%s.RAW",fn.c_str());
                if (file_exists(new_file_raw)) {
                    printf("%s exists\n",new_file_raw);
                    sprintf(new_file_dat,"../cut/%s.DAT",fn.c_str());
                    if (file_exists(new_file_dat)) {
                        printf("And %s exists, crossing==3, scanning/reporting\n",new_file_dat);
                        if (mirror>=1) {
                            scan_done0_plot(report, new_file_dat,new_file_raw);
                            continue;
                        }
                        else
                            scan_done0(report, new_file_dat,new_file_raw);

                    }
                } else {
                    sprintf(new_file_raw,"../cut/done/%s.RAW",fn.c_str());
                    if (file_exists(new_file_raw)) {
                        printf("%s exists\n",new_file_raw);
                        sprintf(new_file_dat,"../cut/done/%s.DAT",fn.c_str());
                        if (file_exists(new_file_dat)) {
                            printf("And %s exists, crossing==3, scanning/reporting\n",new_file_dat);
                            if (mirror>=1) {
                                scan_done0_plot(report, new_file_dat,new_file_raw);
                                continue;
                            }
                            else
                                scan_done0(report, new_file_dat,new_file_raw);
                        }
                    }
                }

                if (crossing==3) {
//                    mkdir("test");
                    char fn[200];
                    sprintf(fn,"report_sub.txt");
//                    sprintf(fn,"test/%s",v.filename.c_str());
                    report = fopen ( fn , "w" );
                    fprintf(report, "\n");
                    fprintf(report,"X=    0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4 4 4 4 4 4 4 5 5 5 5 5 5 5 5 5 5 6 6 6 6 6 6 6 6 6 6 7 7 7 7 7 7 7 7 7 7 8 8 8 8 8 8 8 8 8 8 9 9 9 9 9 9 9 9 9 9 \n");
                    fprintf(report,"      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 \n");
        //            printf("Y=  0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4 4 4 4 4 4 4 5 5 5 5 5 5 5 5 5 5 6 6 6 6 6 6 6 6 6 6 7 7 7 7 7 7 7 7 7 7 8 8 8 8 8 8 8 8 8 8 9 9 9 9 9 9 9 9 9 9 \n");
        //            printf("Y=  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 \n");

                    for (int z=0; z<100; z++) {
//                        printf("Z=%2d ",z);
                        fprintf(report,"Z=%2d ",z);
                        for (int x=0; x<100; x++) {
//                            printf("%d ",region_counter[x][z]);
                            if (region_counter[x][z]>=9)
                                fprintf(report, " *");
                            else
                                fprintf(report, " %d",region_counter[x][z]);
                        }
//                        printf("\n");
                        fprintf(report,"\n");
                    }
                    fclose(report);
                }

                continue;
            }

            sprintf(new_file_dat,"../cut/%s.DAT",fn.c_str());
            if (file_exists(new_file_dat)) {
                printf("%s exists\n",new_file_dat);

                continue;

                sprintf(new_file_raw,"../cut/%s.RAW",fn.c_str());
                if (file_exists(new_file_raw)) {
                    if (crossing==2)
                        printf("And %s exists, skipping\n",new_file_raw);
                    else {
                        printf("And %s exists, crossing==1, converting\n",new_file_raw);
                        main_mceditor5_from_file(new_file_dat,new_file_raw);
                    }
                    continue;
                }
            }

            sprintf(new_file_dat,"../cut/done/%s.DAT",fn.c_str());
            if (file_exists(new_file_dat)) {
                printf("%s exists\n",new_file_dat);

                continue;

                sprintf(new_file_raw,"../cut/done/%s.RAW",fn.c_str());
                if (file_exists(new_file_raw)) {
                    printf("And %s exists, skipping\n",new_file_raw);
                    continue;
                }
            }

        }

        std::string nbt_filename;
        nbt_filename=v.filename;
        std::string nbt_filename_file;

        if (strstr(nbt_filename.c_str(), "/nbt/") != NULL) {
            if (nbt_filename.find_last_of(".") != std::string::npos) nbt_filename=nbt_filename.substr(0,nbt_filename.find_last_of("."))+".nbt";
        }
//        nbt_filename_file=GetFileName(nbt_filename.c_str());

        if ((crossing==2 && mirror==4) || MAKE_NBT) to_gpu=false;
        burn=true;
        if (!MAKE_NBT_EXTERN) {
            window.setActive(true);
            while (Pacman_Objects[win_num].size()>1) {
                erase_one_pacman_objects(Pacman_Objects[win_num][1].map_x,Pacman_Objects[win_num][1].map_y,win_num,pac_obj2_arr_used,pac_obj2_arr);
            }
        } else {
            while (Pacman_Objects[win_num].size()>0) {
//                Pacman_Objects[win_num].clear();
                erase_one_pacman_objects(Pacman_Objects[win_num][0].map_x,Pacman_Objects[win_num][0].map_y,win_num,pac_obj2_arr_used,pac_obj2_arr);
            }
        }

//wuppie
//ayay
        if (strstr(nbt_filename.c_str(), ".obj") != NULL || (crossing>0 && strstr(nbt_filename.c_str(), ".nbt") != NULL)) {
//        if (!file_exists(nbt_filename.c_str()) || strstr(nbt_filename.c_str(), ".obj") != NULL) {
            if (crossing>0)
                printf("\r#%3d CONVERTING TO MINECRAFT FILES: X=%4d Y=%4d %s\n",cnt,v.pos.x,v.pos.y,v.filename.c_str());
            else
                printf("\r#%3d CONVERTING: X=%4d Y=%4d %s\n",cnt,v.pos.x,v.pos.y,v.filename.c_str());

//willem
//            std::string str=get_area_data(my_area,v.pos.x,v.pos.y);
            std::string str=v.filename;

            int i;
            for (i=0; i<100; i++) {
                if (pac_obj2_arr_used[i]==false) {
//                    printf("Free loc. %d ",i);
                    break;
                }
            }
            if (i==100) { printf("\nError, i>100, adapt pac_obj2_arr size > 100"); return false; }

            pac_obj2_arr[i].bmin[0] = pac_obj2_arr[i].bmin[1] = pac_obj2_arr[i].bmin[2] = std::numeric_limits<float>::max();
            pac_obj2_arr[i].bmax[0] = pac_obj2_arr[i].bmax[1] = pac_obj2_arr[i].bmax[2] = -std::numeric_limits<float>::max();
            pac_obj2_arr[i].gDrawObjects.clear();
            pac_obj2_arr[i].materials.clear();
            pac_obj2_arr[i].textures.clear();
            pac_obj2_arr[i].show=0;
//wuppie
            if (crossing>0) {
                do_wuppie=true;
                burn=true;
//                if (!(cnt%10)) voxel_to_file=true;
                if (cnt==info_3d.size()-1) {
                    flushing=true;
                    voxel_to_file=true;
                }
            }
            char kutjelikken[200];
            sprintf(kutjelikken,"N=%20.16f S=%20.16f W=%20.16f E=%20.16f", v.n, v.s, v.w, v.e);
            latitude_longditude=kutjelikken;
            global_octant_x=v.pos.x;
            global_octant_y=v.pos.y;

//            if ((crossing==2 && mirror==4) || MAKE_NBT) to_gpu=false;
            if (true == LoadObjAndConvert_window(pac_obj2_arr[i].bmin, pac_obj2_arr[i].bmax, pac_obj2_arr[i].gDrawObjects, pac_obj2_arr[i].materials, pac_obj2_arr[i].textures, (char*) str.c_str()))
            {
                pac_obj2_arr[i].map_x=v.pos.x;
                pac_obj2_arr[i].map_y=v.pos.y;

                pac_obj2_arr[i].arr_index=i;
                pac_obj2_arr[i].show=1;
                pac_obj2_arr_used[i]=true;

                Pacman_Objects[win_num].push_back(pac_obj2_arr[i]);
                printf("\n");
            } else {
                printf("Error loading new object: (%d,%d): %s\n",v.pos.x,v.pos.y,str.c_str());
                char out[1000];
                sprintf(out, "echo Error loading new object: (%d,%d): %s>>LOADOBJOBJECT_ERROR.TXT\n",v.pos.x,v.pos.y,str.c_str());
                system(out);
                if ((crossing==2 && mirror==4) || MAKE_NBT) to_gpu=true;
                continue;
//                if (crossing>0) {
//                    voxel_to_file=true;
//                }
//                window.setActive(false);
//                nbt_creating=false;
//                return true;
            }
            if ((crossing==2 && mirror==4) || MAKE_NBT) to_gpu=true;

        } else {
            printf("\r#%3d NBT EXISTS: X=%4d Y=%4d %s\n",cnt,v.pos.x,v.pos.y,nbt_filename.c_str());
        }
//        cnt++;
//wuppie
/*
        if (crossing==2) {
            std::string fn = v.filename;
            fn=GetFileName(fn.substr(0,fn.find_last_of(".")));
            char new_file[100];
            sprintf(new_file,"../cut/%s.RAW",fn.c_str());
            CopyFile("../cut/voxel.raw",new_file,false);
            sprintf(new_file,"../cut/%s.DAT",fn.c_str());
            CopyFile("../cut/voxel.dat",new_file,false);
        }
*/
        if (flushing) {
            printf("FLUSHED....\n");
extern bool automate;
extern char send_message;
            flushing=false;
            if (automate) send_message='x';
        }
    }
    if (crossing==3) {
        report = fopen ( "report.txt" , "a" );
        fprintf(report, "\n");
        fprintf(report,"X=    0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4 4 4 4 4 4 4 5 5 5 5 5 5 5 5 5 5 6 6 6 6 6 6 6 6 6 6 7 7 7 7 7 7 7 7 7 7 8 8 8 8 8 8 8 8 8 8 9 9 9 9 9 9 9 9 9 9 \n");
        fprintf(report,"      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 \n");
        printf("X=    0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4 4 4 4 4 4 4 5 5 5 5 5 5 5 5 5 5 6 6 6 6 6 6 6 6 6 6 7 7 7 7 7 7 7 7 7 7 8 8 8 8 8 8 8 8 8 8 9 9 9 9 9 9 9 9 9 9 \n");
        printf("      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 \n");

        for (int z=0; z<100; z++) {
            printf("Z=%2d ",z);
            fprintf(report,"Z=%2d ",z);
            for (int x=0; x<100; x++) {
                printf("%d ",region_counter[x][z]);
                fprintf(report, " %d",region_counter[x][z]);
            }
            printf("\n");
            fprintf(report,"\n");
        }
        fclose(report);
    }
    if (!MAKE_NBT_EXTERN) {
        window.setActive(true);
        while (Pacman_Objects[win_num].size()>1) {
            erase_one_pacman_objects(Pacman_Objects[win_num][1].map_x,Pacman_Objects[win_num][1].map_y,win_num,pac_obj2_arr_used,pac_obj2_arr);
        }
    } else {
        if ((crossing==2 && mirror==4) || MAKE_NBT) to_gpu=false;
        while (Pacman_Objects[win_num].size()>0) {
//                Pacman_Objects[win_num].clear();
            erase_one_pacman_objects(Pacman_Objects[win_num][0].map_x,Pacman_Objects[win_num][0].map_y,win_num,pac_obj2_arr_used,pac_obj2_arr);
        }
        if ((crossing==2 && mirror==4) || MAKE_NBT) to_gpu=true;
    }
    printf("\n");
    nbt_creating=false;
    burn=false;
    return 1;
}




static bool MakeObj(std::vector<struct info_3d_struct>& info_3d, std::string my_area)
{
    char filename[2000];
    sprintf(filename,"%s/%s.obj",MODELS,my_area.c_str());
    sf::Event event;
    FILE* out;
    mkdir(MODELS);
    if ( (out=fopen(filename,"w"))==NULL) {
        printf("Cannot open %s for writing.\n",filename);
    }
//    out=fopen("../Models/3d_object.obj","w");
    char line[2000];
    int sub=0;
    int cnt=0;

    for (auto v : info_3d) {
        if (!v.ok) continue;
//        printf("X=%d Y=%d Dir: %s Filename: %s\n",v.pos.x,v.pos.y,GetBaseDir(v.filename).c_str(),GetFileName(GetBaseDir(v.filename)).c_str());
        printf("Creating object: #%3d X=%02d Y=%02d Dir: %s Filename: %s\n",cnt,v.pos.x,v.pos.y,GetBaseDir(v.filename).c_str(),GetFileName(v.filename).c_str());
        sprintf(line, "o %d_%d_%s\n", v.pos.x,v.pos.y,GetFileName(GetBaseDir(v.filename)).c_str()); fprintf(out,line); // printf(line);
//        sprintf(line, "o %s\n", v.filename.c_str());fprintf(out,line);  printf(line, "o %s\r", v.filename.c_str()); // printf(line);
        cnt++;
//        printf("# vertices\n");
        fprintf(out, "# vertices\n");

extern void ROTJE(glm::vec3 &torot, float bmin[3], float bmax[3], double lat, double lon);

        float bmin[3];
        float bmax[3];
        bmin[0]=v.min_x.x; bmin[1]=v.min_y.y; bmin[2]=v.min_z.z;
        bmax[0]=v.max_x.x; bmax[1]=v.max_y.y; bmax[2]=v.max_z.z;

        glm::vec3 p1(v.min_x.x,v.min_y.y,v.min_z.z); ROTJE(p1, bmin, bmax, v.lat, v.lon);
        glm::vec3 p2(v.max_x.x,v.min_y.y,v.min_z.z); ROTJE(p2, bmin, bmax, v.lat, v.lon);

        glm::vec3 p3(v.max_x.x,v.max_y.y,v.min_z.z); ROTJE(p3, bmin, bmax, v.lat, v.lon);
        glm::vec3 p4(v.min_x.x,v.max_y.y,v.min_z.z); ROTJE(p4, bmin, bmax, v.lat, v.lon);

        glm::vec3 p5(v.max_x.x,v.min_y.y,v.max_z.z); ROTJE(p5, bmin, bmax, v.lat, v.lon);
        glm::vec3 p6(v.min_x.x,v.min_y.y,v.max_z.z); ROTJE(p6, bmin, bmax, v.lat, v.lon);

        glm::vec3 p7(v.min_x.x,v.max_y.y,v.max_z.z); ROTJE(p7, bmin, bmax, v.lat, v.lon);
        glm::vec3 p8(v.max_x.x,v.max_y.y,v.max_z.z); ROTJE(p8, bmin, bmax, v.lat, v.lon);

        glm::vec3 p9((v.max_x.x+v.min_x.x)/2.0,(v.max_y.y+v.min_y.y)/2.0,(v.max_z.z+v.min_z.z)/2.0); ROTJE(p9, bmin, bmax, v.lat, v.lon);

        sprintf(line,"v %f %f %f\n",p1.x,p1.y,p1.z);fprintf(out,line);    //1 printf(line);
        sprintf(line,"v %f %f %f\n",p2.x,p2.y,p2.z);fprintf(out,line);    //1 printf(line);

        sprintf(line,"v %f %f %f\n",p3.x,p3.y,p3.z);fprintf(out,line);    //1 printf(line);
        sprintf(line,"v %f %f %f\n",p4.x,p4.y,p4.z);fprintf(out,line);    //1 printf(line);

        sprintf(line,"v %f %f %f\n",p5.x,p5.y,p5.z);fprintf(out,line);    //1 printf(line);
        sprintf(line,"v %f %f %f\n",p6.x,p6.y,p6.z);fprintf(out,line);    //1 printf(line);

        sprintf(line,"v %f %f %f\n",p7.x,p7.y,p7.z);fprintf(out,line);    //1 printf(line);
        sprintf(line,"v %f %f %f\n",p8.x,p8.y,p8.z);fprintf(out,line);    //1 printf(line);
        sprintf(line,"v %f %f %f\n",p9.x,p9.y,p9.z);fprintf(out,line);    //1 printf(line);


/*
        sprintf(line,"v %f %f %f\n",v.min_x.x,v.min_y.y,v.min_z.z);fprintf(out,line);    //1 printf(line);
        sprintf(line,"v %f %f %f\n",v.max_x.x,v.min_y.y,v.min_z.z);fprintf(out,line);    //2 printf(line);

        sprintf(line,"v %f %f %f\n",v.max_x.x,v.max_y.y,v.min_z.z);fprintf(out,line);    //3 printf(line);
        sprintf(line,"v %f %f %f\n",v.min_x.x,v.max_y.y,v.min_z.z);fprintf(out,line);    //4 printf(line);

        sprintf(line,"v %f %f %f\n",v.max_x.x,v.min_y.y,v.max_z.z);fprintf(out,line);    //5 printf(line);
        sprintf(line,"v %f %f %f\n",v.min_x.x,v.min_y.y,v.max_z.z);fprintf(out,line);    //6 printf(line);

        sprintf(line,"v %f %f %f\n",v.min_x.x,v.max_y.y,v.max_z.z);fprintf(out,line);    //7 printf(line);
        sprintf(line,"v %f %f %f\n",v.max_x.x,v.max_y.y,v.max_z.z);fprintf(out,line);    //8 printf(line);

        sprintf(line,"v %f %f %f\n",(double)(v.max_x.x+v.min_x.x)/2.0,(double)(v.max_y.y+v.min_y.y)/2.0,(double)(v.max_z.z+v.min_z.z)/2.0);fprintf(out,line);    //9 printf(line);

*/
        int tot_x;
        int tot_y;
        int tot_z;
        glm::vec3 square(v.max_x.x-v.min_x.x,v.max_y.y-v.min_y.y,v.max_z.z-v.min_z.z);
        square=glm::normalize(square)*glm::vec3(12.0);
        tot_x=2+square.x;
        tot_y=2+square.y;
        tot_z=2+square.z;

        for (int z=0; z<tot_z; z++) {
            for (int y=0; y<tot_y; y++) {
                for (int x=0; x<tot_x; x++) {
//                    if (!(x==0 || x==tot_x-1 || y==0 || y==tot_y-1 || z==0 || z==tot_z-1)) continue;
                    double add_x1=(v.max_x.x-v.min_x.x)*(double)x/(double)tot_x;
                    double add_y1=(v.max_y.y-v.min_y.y)*(double)y/(double)tot_y;
                    double add_z1=(v.max_z.z-v.min_z.z)*(double)z/(double)tot_z;
                    double add_x2=(v.max_x.x-v.min_x.x)*((double)x+1.0)/(double)tot_x;
                    double add_y2=(v.max_y.y-v.min_y.y)*((double)y+1.0)/(double)tot_y;
                    double add_z2=(v.max_z.z-v.min_z.z)*((double)z+1.0)/(double)tot_z;


//                    double add_x2=(v.max_x.x-v.min_x.x)*(double)(x+1)/3.0;
//                    double add_y2=(v.max_y.y-v.min_y.y)*(double)(y+1)/3.0;
//                    double add_z2=(v.max_z.z-v.min_z.z)*(double)(z+1)/3.0;

                    p1=glm::vec3(v.min_x.x+add_x1,v.min_y.y+add_y1,v.min_z.z+add_z1); ROTJE(p1, bmin, bmax, v.lat, v.lon);
                    p2=glm::vec3(v.min_x.x+add_x2,v.min_y.y+add_y1,v.min_z.z+add_z1); ROTJE(p2, bmin, bmax, v.lat, v.lon);
                    p3=glm::vec3(v.min_x.x+add_x2,v.min_y.y+add_y2,v.min_z.z+add_z1); ROTJE(p3, bmin, bmax, v.lat, v.lon);
                    p4=glm::vec3(v.min_x.x+add_x1,v.min_y.y+add_y2,v.min_z.z+add_z1); ROTJE(p4, bmin, bmax, v.lat, v.lon);
                    p5=glm::vec3(v.min_x.x+add_x2,v.min_y.y+add_y1,v.min_z.z+add_z2); ROTJE(p5, bmin, bmax, v.lat, v.lon);
                    p6=glm::vec3(v.min_x.x+add_x1,v.min_y.y+add_y1,v.min_z.z+add_z2); ROTJE(p6, bmin, bmax, v.lat, v.lon);
                    p7=glm::vec3(v.min_x.x+add_x1,v.min_y.y+add_y2,v.min_z.z+add_z2); ROTJE(p7, bmin, bmax, v.lat, v.lon);
                    p8=glm::vec3(v.min_x.x+add_x2,v.min_y.y+add_y2,v.min_z.z+add_z2); ROTJE(p8, bmin, bmax, v.lat, v.lon);

//                    glm::vec3 p9(v.min_x.x+diag*(double)(add_x1+add_x2)/2.0,v.min_y.y+diag*(double)(add_y1+add_y2)/2.0,v.min_z.z+diag*(double)(add_z1+add_z2)/2.0); ROTJE(p9, bmin, bmax, v.lat, v.lon);
//                    glm::vec3 p9(v.min_x.x+diag*(double)(add_x1+add_x2)/2.0,v.min_y.y+diag*(double)(add_y1+add_y2)/2.0,v.min_z.z+diag*(double)(add_z1+add_z2)/2.0); ROTJE(p9, bmin, bmax, v.lat, v.lon);

//                    glm::vec3 p9(extra_x+v.min_x.x+(double)(add_x1+add_x2)/2.0,extra_y+v.min_y.y+(double)(add_y1+add_y2)/2.0,v.min_z.z+(double)(add_z1+add_z2)/2.0); ROTJE(p9, bmin, bmax, v.lat, v.lon);
                    float out_x=(float)(add_x2-add_x1)*(rand()%21-10)/20.0;
                    float out_y=(float)(add_y2-add_y1)*(rand()%21-10)/20.0;
                    float out_z=(float)(add_z2-add_z1)*(rand()%21-10)/20.0;
                    glm::vec3 p9(v.min_x.x+(double)(add_x1+add_x2)/(2.0)+out_x,
                                 v.min_y.y+(double)(add_y1+add_y2)/(2.0)+out_y,
                                 v.min_z.z+(double)(add_z1+add_z2)/(2.0)+out_z);
                    ROTJE(p9, bmin, bmax, v.lat, v.lon);
//                    glm::vec3 p9(v.min_x.x+(double)(add_x1+add_x2)/2.0,v.min_y.y+(double)(add_y1+add_y2)/2.0,v.min_z.z+(double)(add_z1+add_z2)/2.0); ROTJE(p9, bmin, bmax, v.lat, v.lon);


                    sprintf(line,"v %f %f %f\n",p1.x,p1.y,p1.z);fprintf(out,line);    //2 printf(line);
                    sprintf(line,"v %f %f %f\n",p2.x,p2.y,p2.z);fprintf(out,line);    //1 printf(line);
                    sprintf(line,"v %f %f %f\n",p3.x,p3.y,p3.z);fprintf(out,line);    //3 printf(line);
                    sprintf(line,"v %f %f %f\n",p4.x,p4.y,p4.z);fprintf(out,line);    //4 printf(line);
                    sprintf(line,"v %f %f %f\n",p5.x,p5.y,p5.z);fprintf(out,line);    //5 printf(line);
                    sprintf(line,"v %f %f %f\n",p6.x,p6.y,p6.z);fprintf(out,line);    //6 printf(line);
                    sprintf(line,"v %f %f %f\n",p7.x,p7.y,p7.z);fprintf(out,line);    //7 printf(line);
                    sprintf(line,"v %f %f %f\n",p8.x,p8.y,p8.z);fprintf(out,line);    //8 printf(line);
                    sprintf(line,"v %f %f %f\n",p9.x,p9.y,p9.z);fprintf(out,line);    //9 printf(line);

/*
                    sprintf(line,"v %f %f %f\n",v.min_x.x+add_x1,v.min_y.y+add_y1,v.min_z.z+add_z1);fprintf(out,line);    //1 printf(line);
                    sprintf(line,"v %f %f %f\n",v.min_x.x+add_x2,v.min_y.y+add_y1,v.min_z.z+add_z1);fprintf(out,line);    //2 printf(line);
                    sprintf(line,"v %f %f %f\n",v.min_x.x+add_x2,v.min_y.y+add_y2,v.min_z.z+add_z1);fprintf(out,line);    //3 printf(line);
                    sprintf(line,"v %f %f %f\n",v.min_x.x+add_x1,v.min_y.y+add_y2,v.min_z.z+add_z1);fprintf(out,line);    //4 printf(line);
                    sprintf(line,"v %f %f %f\n",v.min_x.x+add_x2,v.min_y.y+add_y1,v.min_z.z+add_z2);fprintf(out,line);    //5 printf(line);
                    sprintf(line,"v %f %f %f\n",v.min_x.x+add_x1,v.min_y.y+add_y1,v.min_z.z+add_z2);fprintf(out,line);    //6 printf(line);
                    sprintf(line,"v %f %f %f\n",v.min_x.x+add_x1,v.min_y.y+add_y2,v.min_z.z+add_z2);fprintf(out,line);    //7 printf(line);
                    sprintf(line,"v %f %f %f\n",v.min_x.x+add_x2,v.min_y.y+add_y2,v.min_z.z+add_z2);fprintf(out,line);    //8 printf(line);
                    sprintf(line,"v %f %f %f\n",v.min_x.x+(double)(add_x1+add_x2)/2.0,v.min_y.y+(double)(add_y1+add_y2)/2.0,v.min_z.z+(double)(add_z1+add_z2)/2.0);fprintf(out,line);    //9 printf(line);
*/
                }
            }
        }


//        printf("# faces\n");
        fprintf(out, "# faces\n");

/*
        sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",1+sub,1+sub,1+sub, 3+sub,3+sub,3+sub, 2+sub,2+sub,2+sub); fprintf(out,line);//printf(line);
        sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",3+sub,3+sub,3+sub, 1+sub,1+sub,1+sub, 4+sub,4+sub,4+sub); fprintf(out,line);//printf(line);
        sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",2+sub,2+sub,2+sub, 8+sub,8+sub,8+sub, 5+sub,5+sub,5+sub); fprintf(out,line);//printf(line);
        sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",8+sub,8+sub,8+sub, 2+sub,2+sub,2+sub, 3+sub,3+sub,3+sub); fprintf(out,line);//printf(line);
        sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",6+sub,6+sub,6+sub, 4+sub,4+sub,4+sub, 1+sub,1+sub,1+sub); fprintf(out,line);//printf(line);
        sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",4+sub,4+sub,4+sub, 6+sub,6+sub,6+sub, 7+sub,7+sub,7+sub); fprintf(out,line);//printf(line);

        sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",5+sub,5+sub,5+sub, 7+sub,7+sub,7+sub, 6+sub,6+sub,6+sub); fprintf(out,line);//printf(line);
        sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",7+sub,7+sub,7+sub, 5+sub,5+sub,5+sub, 8+sub,8+sub,8+sub); fprintf(out,line);//printf(line);
        sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",4+sub,4+sub,4+sub, 8+sub,8+sub,8+sub, 3+sub,3+sub,3+sub); fprintf(out,line);//printf(line);
        sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",8+sub,8+sub,8+sub, 4+sub,4+sub,4+sub, 7+sub,7+sub,7+sub); fprintf(out,line);//printf(line);
        sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",6+sub,6+sub,6+sub, 2+sub,2+sub,2+sub, 5+sub,5+sub,5+sub); fprintf(out,line);//printf(line);
        sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",2+sub,2+sub,2+sub, 6+sub,6+sub,6+sub, 1+sub,1+sub,1+sub); fprintf(out,line);//printf(line);

        sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",1+sub,1+sub,1+sub, 3+sub,3+sub,3+sub, 9+sub,9+sub,9+sub); fprintf(out,line);//printf(line);
        sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",3+sub,3+sub,3+sub, 1+sub,1+sub,1+sub, 9+sub,9+sub,9+sub); fprintf(out,line);//printf(line);
        sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",2+sub,2+sub,2+sub, 8+sub,8+sub,8+sub, 9+sub,9+sub,9+sub); fprintf(out,line);//printf(line);
        sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",8+sub,8+sub,8+sub, 2+sub,2+sub,2+sub, 9+sub,9+sub,9+sub); fprintf(out,line);//printf(line);
        sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",6+sub,6+sub,6+sub, 4+sub,4+sub,4+sub, 9+sub,9+sub,9+sub); fprintf(out,line);//printf(line);
        sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",4+sub,4+sub,4+sub, 6+sub,6+sub,6+sub, 9+sub,9+sub,9+sub); fprintf(out,line);//printf(line);

        sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",5+sub,5+sub,5+sub, 7+sub,7+sub,7+sub, 9+sub,9+sub,9+sub); fprintf(out,line);//printf(line);
        sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",7+sub,7+sub,7+sub, 5+sub,5+sub,5+sub, 9+sub,9+sub,9+sub); fprintf(out,line);//printf(line);
        sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",4+sub,4+sub,4+sub, 8+sub,8+sub,8+sub, 9+sub,9+sub,9+sub); fprintf(out,line);//printf(line);
        sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",8+sub,8+sub,8+sub, 4+sub,4+sub,4+sub, 9+sub,9+sub,9+sub); fprintf(out,line);//printf(line);
        sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",6+sub,6+sub,6+sub, 2+sub,2+sub,2+sub, 9+sub,9+sub,9+sub); fprintf(out,line);//printf(line);
        sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",2+sub,2+sub,2+sub, 6+sub,6+sub,6+sub, 9+sub,9+sub,9+sub); fprintf(out,line);//printf(line);
*/
//        sub=sub+9;
        int n=0;
        for (int z=0; z<tot_z; z++) {
            for (int y=0; y<tot_y; y++) {
                for (int x=0; x<tot_x; x++) {
//                    if (!(x==0 || x==tot_x-1 || y==0 || y==tot_y-1 || z==0 || z==tot_z-1)) continue;
//                    int n=(x+y*3+z*3*3)*9;
                    sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",1+sub+9+n,1+sub+9+n,1+sub+9+n, 3+sub+9+n,3+sub+9+n,3+sub+9+n, 2+sub+9+n,2+sub+9+n,2+sub+9+n); fprintf(out,line);//printf(line);
                    sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",3+sub+9+n,3+sub+9+n,3+sub+9+n, 1+sub+9+n,1+sub+9+n,1+sub+9+n, 4+sub+9+n,4+sub+9+n,4+sub+9+n); fprintf(out,line);//printf(line);
                    sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",2+sub+9+n,2+sub+9+n,2+sub+9+n, 8+sub+9+n,8+sub+9+n,8+sub+9+n, 5+sub+9+n,5+sub+9+n,5+sub+9+n); fprintf(out,line);//printf(line);
                    sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",8+sub+9+n,8+sub+9+n,8+sub+9+n, 2+sub+9+n,2+sub+9+n,2+sub+9+n, 3+sub+9+n,3+sub+9+n,3+sub+9+n); fprintf(out,line);//printf(line);
                    sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",6+sub+9+n,6+sub+9+n,6+sub+9+n, 4+sub+9+n,4+sub+9+n,4+sub+9+n, 1+sub+9+n,1+sub+9+n,1+sub+9+n); fprintf(out,line);//printf(line);
                    sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",4+sub+9+n,4+sub+9+n,4+sub+9+n, 6+sub+9+n,6+sub+9+n,6+sub+9+n, 7+sub+9+n,7+sub+9+n,7+sub+9+n); fprintf(out,line);//printf(line);
                    sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",5+sub+9+n,5+sub+9+n,5+sub+9+n, 7+sub+9+n,7+sub+9+n,7+sub+9+n, 6+sub+9+n,6+sub+9+n,6+sub+9+n); fprintf(out,line);//printf(line);
                    sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",7+sub+9+n,7+sub+9+n,7+sub+9+n, 5+sub+9+n,5+sub+9+n,5+sub+9+n, 8+sub+9+n,8+sub+9+n,8+sub+9+n); fprintf(out,line);//printf(line);
                    sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",4+sub+9+n,4+sub+9+n,4+sub+9+n, 8+sub+9+n,8+sub+9+n,8+sub+9+n, 3+sub+9+n,3+sub+9+n,3+sub+9+n); fprintf(out,line);//printf(line);
                    sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",8+sub+9+n,8+sub+9+n,8+sub+9+n, 4+sub+9+n,4+sub+9+n,4+sub+9+n, 7+sub+9+n,7+sub+9+n,7+sub+9+n); fprintf(out,line);//printf(line);
                    sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",6+sub+9+n,6+sub+9+n,6+sub+9+n, 2+sub+9+n,2+sub+9+n,2+sub+9+n, 5+sub+9+n,5+sub+9+n,5+sub+9+n); fprintf(out,line);//printf(line);
                    sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",2+sub+9+n,2+sub+9+n,2+sub+9+n, 6+sub+9+n,6+sub+9+n,6+sub+9+n, 1+sub+9+n,1+sub+9+n,1+sub+9+n); fprintf(out,line);//printf(line);

                    sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",1+sub+9+n,1+sub+9+n,1+sub+9+n, 3+sub+9+n,3+sub+9+n,3+sub+9+n, 9+sub+9+n,9+sub+9+n,9+sub+9+n); fprintf(out,line);//printf(line);
                    sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",3+sub+9+n,3+sub+9+n,3+sub+9+n, 1+sub+9+n,1+sub+9+n,1+sub+9+n, 9+sub+9+n,9+sub+9+n,9+sub+9+n); fprintf(out,line);//printf(line);
                    sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",2+sub+9+n,2+sub+9+n,2+sub+9+n, 8+sub+9+n,8+sub+9+n,8+sub+9+n, 9+sub+9+n,9+sub+9+n,9+sub+9+n); fprintf(out,line);//printf(line);
                    sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",8+sub+9+n,8+sub+9+n,8+sub+9+n, 2+sub+9+n,2+sub+9+n,2+sub+9+n, 9+sub+9+n,9+sub+9+n,9+sub+9+n); fprintf(out,line);//printf(line);
                    sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",6+sub+9+n,6+sub+9+n,6+sub+9+n, 4+sub+9+n,4+sub+9+n,4+sub+9+n, 9+sub+9+n,9+sub+9+n,9+sub+9+n); fprintf(out,line);//printf(line);
                    sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",4+sub+9+n,4+sub+9+n,4+sub+9+n, 6+sub+9+n,6+sub+9+n,6+sub+9+n, 9+sub+9+n,9+sub+9+n,9+sub+9+n); fprintf(out,line);//printf(line);
                    sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",5+sub+9+n,5+sub+9+n,5+sub+9+n, 7+sub+9+n,7+sub+9+n,7+sub+9+n, 9+sub+9+n,9+sub+9+n,9+sub+9+n); fprintf(out,line);//printf(line);
                    sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",7+sub+9+n,7+sub+9+n,7+sub+9+n, 5+sub+9+n,5+sub+9+n,5+sub+9+n, 9+sub+9+n,9+sub+9+n,9+sub+9+n); fprintf(out,line);//printf(line);
                    sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",4+sub+9+n,4+sub+9+n,4+sub+9+n, 8+sub+9+n,8+sub+9+n,8+sub+9+n, 9+sub+9+n,9+sub+9+n,9+sub+9+n); fprintf(out,line);//printf(line);
                    sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",8+sub+9+n,8+sub+9+n,8+sub+9+n, 4+sub+9+n,4+sub+9+n,4+sub+9+n, 9+sub+9+n,9+sub+9+n,9+sub+9+n); fprintf(out,line);//printf(line);
                    sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",6+sub+9+n,6+sub+9+n,6+sub+9+n, 2+sub+9+n,2+sub+9+n,2+sub+9+n, 9+sub+9+n,9+sub+9+n,9+sub+9+n); fprintf(out,line);//printf(line);
                    sprintf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",2+sub+9+n,2+sub+9+n,2+sub+9+n, 6+sub+9+n,6+sub+9+n,6+sub+9+n, 9+sub+9+n,9+sub+9+n,9+sub+9+n); fprintf(out,line);//printf(line);
//                    n+=tot_x*2+tot_y*2+tot_z*2;
                    n+=9;
                }
            }
        }
        sub=sub+9+n;
//        sub=sub+9+9*(tot_x-1)*(tot_y-1)*2;
//        sub=sub+9+9*3*3*3;
    }

    printf("\n");

    fclose(out);
/*
    out=fopen("../models/3d_object.obj","r");
    while (fgets (line,200, out)!=NULL) {
        printf(line);
    }
    fclose(out);
*/
    sprintf(filename,"cd %s && %s/makelist.bat",MODELS,MODELS);
   	while (replace_str(filename,"/","\\"));
    system(filename);
    printf("system(%s);\n",filename);

    return true;
}

std::vector<glm::ivec3> load_objects_pos;
std::vector<std::string> load_objects_dir;
std::vector<std::string> load_objects_latlon;


bool get_one_3d_init(int cur_x, std::string& my_area, int win_num, bool pac_obj2_arr_used[100],Pacman_Object pac_obj2_arr[100], sf::RenderWindow& window) {
    int cur_y=0;
    char line[2000]="";

    std::string filename=get_area_data(std::string() + "Models",cur_x,cur_y);
    filename=filename.substr(0,filename.length());

    std::string marker_filename=filename.substr(0,filename.length()-3) + "cam";

    my_area=GetFileName(filename);
    my_area=my_area.substr(0,my_area.length()-4);

    printf("Area: %s Got %s\n",my_area.c_str(),marker_filename.c_str());

    FILE* in;
    if ((in=fopen(marker_filename.c_str(),"r"))==NULL) {
        printf("get_one_3d_init(): Can not open file: %s\n",marker_filename.c_str());
        return false;
    }
//    char fline[2000]="";
    if (fgets (line,2000, in)!=NULL ) {
        sscanf(line,"QUATS=%e %e %e %e EYE=%e %e %e LOOKAT=%e %e %e TRANSLATION=%e %e %e PERSPECTIVE=%e %e %e %e BMIN=%e %e %e BMAX=%e %e %e FRUSTUM=%d\n",
            &int_q[0], &int_q[1], &int_q[2], &int_q[3],
            &int_e[0], &int_e[1], &int_e[2],
            &int_l[0], &int_l[1], &int_l[2],
            &int_t[0], &int_t[1], &int_t[2],
            &int_p[0], &int_p[1], &int_p[2], &int_p[3],
            &int_bmin[0], &int_bmin[1], &int_bmin[2],
            &int_bmax[0], &int_bmax[1], &int_bmax[2], &int_frustum_toggle);
        printf("LOAD: q0=%-+f q1=%-+f q2=%-+f q3=%-+f  e0=%-+f e1=%-+f e2=%-+f  l0=%-+f l1=%-+f l2=%-+f  t0=%-+f t1=%-+f t2=%-+f  p0=%-+f  bmin=%-+f %-+f %-+f  bmax=%-+f %-+f %-+f  frustum=%d\n",
                int_q[0],int_q[1],int_q[2],int_q[3],
                int_e[0],int_e[1],int_e[2],
                int_l[0],int_l[1],int_l[2],
                int_t[0],int_t[1],int_t[2],
                int_p[0],
                int_bmin[0], int_bmin[1], int_bmin[2],
                int_bmax[0], int_bmax[1], int_bmax[2], int_frustum_toggle
               );
    } else {
        printf("error reading file cam position: %s\n",marker_filename.c_str());
        return false;
    }
    char area[30];
    if (fgets (line,2000, in)!=NULL ) {
        float pos_x,pos_y,size_x,size_y;
//decimal_point
                        while (replace_str(line,",","."));
//        while (replace_str(line,".",","));
        sscanf(line,"POSITION_X=%e POSITION_Y=%e SIZE_X=%e SIZE_Y=%e FRUSTUMS_X=%d FRUSTUMS_Y=%d AREA=%30[^\n]",
            &pos_x,&pos_y,&size_x,&size_y,&frustum_size_x,&frustum_size_y,area);

        rectangle.setPosition(sf::Vector2f(pos_x,pos_y));
        rectangle.setSize(sf::Vector2f(size_x,size_y));

        printf("POSITION_X=%f POSITION_Y=%f SIZE_X=%f SIZE_Y=%f FRUSTUMS_X=%d FRUSTUMS_Y=%d AREA=%s\n",
                rectangle.getPosition().x, rectangle.getPosition().y,
                rectangle.getSize().x, rectangle.getSize().y,
                frustum_size_x,frustum_size_y,area);
        if (strcmp(area,my_area.c_str())==0) printf("Area names match ok.\n");
        else printf("Area names don't match!\n%s\n%s\n",area,my_area.c_str());
    } else {
        printf("error reading file frustum size/number: %s\n",marker_filename.c_str());
        return false;
    }
    COLOR_ARRAY=false;
    TEXTURE_ARRAY=true;
    WIRE_FRAME=false;

    frustum_object.clear();
    while (fgets (line,2000, in)!=NULL ) {
        int curr_x,curr_y;
        int fc_x,fc_y;
        sscanf(line,"FRUSTUM_X=%d FRUSTUM_Y=%d OBJECT_X=%d OBJECT_Y=%d", &fc_x,&fc_y,&curr_x,&curr_y);
        frustum_object.push_back(glm::ivec4(fc_x,fc_y,curr_x,curr_y));
//        printf("FRUSTUM X=%2d,Y=%2d OBJECT X=%02d,Y=%02d\r", fc_x,fc_y,curr_x,curr_y);
//        printf(".");
    }
    printf("\n");
    fclose(in);
    if (frustum_object.size()==0) {
        printf("No data present: %s\n",filename.c_str());
        return false;
    }

    if ((in=fopen(filename.c_str(),"r"))==NULL) {
        printf("get_one_3d_init(): Can not open file: %s\n",filename.c_str());
        return false;
    }
    char line_new[2000]="";
    char dir[99]="";

    printf("Loading object data %s....",filename.c_str());
    load_objects_pos.clear();
    load_objects_dir.clear();
    load_objects_latlon.clear();
    int cnt=0;
    if (in!=NULL) {
        char* ret;
        do {
            int xp; int yp;
            ret=fgets(line_new,2000, in);
            if (ret!=NULL) {
                if (line_new[0]=='o' ) {
                    xp=-1; int yp=-1;
                    int num=sscanf(line_new, "o %d_%d_%99[^\n]", &xp,&yp,dir);
                    if (xp!=-1 && yp!=-1 && num==3) {
                        int load_object=0;
                        for (auto u : frustum_object) {
                            if (u.x==frustum_count_x && u.y==frustum_count_y && u.z==xp && u.w==yp) {
                                load_object=1;
                                break;
                            }
                        }
                        load_objects_pos.push_back(glm::ivec3(xp,yp,load_object));
                        load_objects_dir.push_back(std::string()+dir);
                    } else {
                        num=sscanf(line_new, "o %99[^\n]",dir);
                        load_objects_pos.push_back(glm::ivec3(cnt++,0,1));
                        load_objects_dir.push_back(std::string()+dir);
                        printf("Error reading position from .obj file o marker -> %s\n",line_new);
                    }
                }
            }
        } while ( ret!=NULL );
        fclose(in);
    }
    printf("done.\n");

//    printf("Object array totaly erased, now loading first area %s now loading first frustrum: X=%d,Y=%d\n",my_area.c_str(),frustum_object[0].x,frustum_object[0].y);

//    window.setActive(true);
//    while (Pacman_Objects[win_num].size()>0) {
//        int wn=0;
//        printf("Erasing: X=%d,Y=%d\n",Pacman_Objects[win_num][0].map_x,Pacman_Objects[win_num][0].map_y);
//        erase_one_pacman_objects(Pacman_Objects[win_num][0].map_x,Pacman_Objects[win_num][0].map_y,win_num,pac_obj2_arr_used,pac_obj2_arr);
//    }

//    if (!(load_3d_objects(frustum_object[0].x,frustum_object[0].y, my_area,  pac_obj2_arr_used,pac_obj2_arr, win_num, window))) {
//        return false;
//    } else {
//        printf("Objects first area %s loaded. Frustrum: X=%d,Y=%d\n",my_area.c_str(),frustum_object[0].x,frustum_object[0].y);
//        return true;
//    }

    return true;
}

bool set_view_3d(int cur_x, std::string& my_area, int win_num, bool pac_obj2_arr_used[100],Pacman_Object pac_obj2_arr[100], sf::RenderWindow& window) {
    int cur_y=0;
    char line[2000]="";

    std::string filename=get_area_data(std::string() + "Models",cur_x,cur_y);
    filename=filename.substr(0,filename.length());

    std::string marker_filename=filename.substr(0,filename.length()-3) + "cam";

    FILE* in;
    if ((in=fopen(marker_filename.c_str(),"r"))==NULL) {
        printf("set_view_3d(): Can not open file: %s\n",marker_filename.c_str());
        return false;
    }
//    char fline[2000]="";
    if (fgets (line,2000, in)!=NULL ) {
        sscanf(line,"QUATS=%e %e %e %e EYE=%e %e %e LOOKAT=%e %e %e TRANSLATION=%e %e %e PERSPECTIVE=%e %e %e %e BMIN=%e %e %e BMAX=%e %e %e FRUSTUM=%d\n",
            &int_q[0], &int_q[1], &int_q[2], &int_q[3],
            &int_e[0], &int_e[1], &int_e[2],
            &int_l[0], &int_l[1], &int_l[2],
            &int_t[0], &int_t[1], &int_t[2],
            &int_p[0], &int_p[1], &int_p[2], &int_p[3],
            &int_bmin[0], &int_bmin[1], &int_bmin[2],
            &int_bmax[0], &int_bmax[1], &int_bmax[2], &int_frustum_toggle);
        printf("LOAD: q0=%-+f q1=%-+f q2=%-+f q3=%-+f  e0=%-+f e1=%-+f e2=%-+f  l0=%-+f l1=%-+f l2=%-+f  t0=%-+f t1=%-+f t2=%-+f  p0=%-+f  bmin=%-+f %-+f %-+f  bmax=%-+f %-+f %-+f  frustum=%d\n",
                int_q[0],int_q[1],int_q[2],int_q[3],
                int_e[0],int_e[1],int_e[2],
                int_l[0],int_l[1],int_l[2],
                int_t[0],int_t[1],int_t[2],
                int_p[0],
                int_bmin[0], int_bmin[1], int_bmin[2],
                int_bmax[0], int_bmax[1], int_bmax[2], int_frustum_toggle
               );
    } else {
        printf("error reading file cam position: %s\n",marker_filename.c_str());
        fclose(in);
        return false;
    }
    char area[30];
    if (fgets (line,2000, in)!=NULL ) {
        float pos_x,pos_y,size_x,size_y;
//decimal_point
                        while (replace_str(line,",","."));
////        while (replace_str(line,".",","));
        sscanf(line,"POSITION_X=%e POSITION_Y=%e SIZE_X=%e SIZE_Y=%e FRUSTUMS_X=%d FRUSTUMS_Y=%d AREA=%30[^\n]",
            &pos_x,&pos_y,&size_x,&size_y,&frustum_size_x,&frustum_size_y,area);

        rectangle.setPosition(sf::Vector2f(pos_x,pos_y));
        rectangle.setSize(sf::Vector2f(size_x,size_y));

        printf("POSITION_X=%f POSITION_Y=%f SIZE_X=%f SIZE_Y=%f FRUSTUMS_X=%d FRUSTUMS_Y=%d AREA=%s\n",
                rectangle.getPosition().x, rectangle.getPosition().y,
                rectangle.getSize().x, rectangle.getSize().y,
                frustum_size_x,frustum_size_y,area);
    } else {
        printf("error reading file frustum size/number: %s\n",marker_filename.c_str());
        fclose(in);
        return false;
    }

    frustum_object.clear();
    while (fgets (line,2000, in)!=NULL ) {
        int curr_x,curr_y;
        int fc_x,fc_y;
        sscanf(line,"FRUSTUM_X=%d FRUSTUM_Y=%d OBJECT_X=%d OBJECT_Y=%d", &fc_x,&fc_y,&curr_x,&curr_y);
        frustum_object.push_back(glm::ivec4(fc_x,fc_y,curr_x,curr_y));
//        printf("FRUSTUM X=%2d,Y=%2d OBJECT X=%02d,Y=%02d\n", fc_x,fc_y,curr_x,curr_y);
//        printf(".");
    }
    printf("\n");
    fclose(in);
    if (frustum_object.size()==0) {
        printf("No data present: %s\n",filename.c_str());
        return false;
    }

    if ((in=fopen(filename.c_str(),"r"))==NULL) {
        printf("set_view_3d(): Can not open file: %s\n",filename.c_str());
        return false;
    }
    char line_new[2000]="";
    char dir[40]="";

    printf("Loading object data %s....",filename.c_str());
    load_objects_pos.clear();
    load_objects_dir.clear();
    if (in!=NULL) {
        char* ret;
        do {
            ret=fgets(line_new,2000, in);
            if (ret!=NULL) {
                if (line_new[0]=='o' ) {
                    int xp=-1; int yp=-1;
                    sscanf(line_new, "o %d_%d_%40[^\n]", &xp,&yp,dir);
                    if (xp!=-1 && yp!=-1) {
                        int load_object=0;
                        for (auto u : frustum_object) {
                            if (u.x==frustum_count_x && u.y==frustum_count_y && u.z==xp && u.w==yp) {
                                load_object=1;
                                break;
                            }
                        }
                        load_objects_pos.push_back(glm::ivec3(xp,yp,load_object));
                        load_objects_dir.push_back(std::string()+dir);
                    } else {
                        printf("Error reading position from .obj file o marker -> %s\n",line_new);
                    }
                }
            }
        } while ( ret!=NULL );
        fclose(in);
    }
    printf("done.\n");

    return true;
}

bool get_one_3d_init_load_obj_data(int cur_x, std::string& my_area, int win_num, bool pac_obj2_arr_used[100],Pacman_Object pac_obj2_arr[100], sf::RenderWindow& window) {
    int cur_y=0;
    char line[2000]="";

    load_objects_pos.clear();
    load_objects_dir.clear();

    std::string filename=get_area_data(std::string() + "Models",cur_x,cur_y);
    filename=filename.substr(0,filename.length());

    FILE* in;

    if ((in=fopen(filename.c_str(),"r"))==NULL) {
        printf("get_one_3d_init_load_obj_data(): Can not open file: %s\n",filename.c_str());
        return false;
    }
    char line_new[2000];
    char dir[40];
    int err=0;
    int n=0;
    if (in!=NULL) {
        char* ret;
        do {
            ret=fgets(line_new,2000, in);
            if (line_new[0]=='o' && ret!=NULL ) {
                int xp=-1; int yp=-1;
                sscanf(line_new, "o %d_%d_%40[^\n]", &xp,&yp,dir);
                if (xp!=-1 && yp!=-1) {
                    int load_object=0;
                    for (auto u : frustum_object) {
                        if (u.x==frustum_count_x && u.y==frustum_count_y && u.z==xp && u.w==yp) {
                            load_object=1;
                            break;
                        }
                    }
                    load_objects_pos.push_back(glm::ivec3(xp,yp,load_object));
                    load_objects_dir.push_back(std::string()+dir);
                } else {
                    printf("Error reading position from .obj file o marker -> %s\n",line_new);
                    err=1;
                    break;
//                    load_objects_pos.push_back(glm::ivec3(n,0,1));
//                    load_objects_dir.push_back(std::string()+line_new);
                }
                n++;
            }
        } while ( ret!=NULL );
        fclose(in);
    }

    return true;
}

bool get_one_3d_update_load_obj_data() {
    int n=0;
    bool first=true;
    int load_object;
    int xp;
    int yp;
    for (auto v : load_objects_pos) {
        load_object=0;
        xp=v.x;
        yp=v.y;

        for (auto u : frustum_object) {
            if (u.x==frustum_count_x && u.y==frustum_count_y && u.z==xp && u.w==yp) {
                load_object=1;
                if (first) {
                    printf("FOUND: FRUSTUM X=%2d,Y=%2d (%2d,%2d) ",frustum_count_x,frustum_count_y,xp,yp);
                    first=false;
                }
                else
                    printf("(%2d,%2d) ",xp,yp);
                break;
            }
        }
//        else printf("FOUND: nothing\n");
        load_objects_pos[n].z=load_object;
        n++;
    }
    if (!first) printf("\n");
    return true;
}

bool load_3d_objects(int frustum_count_x,int frustum_count_y,std::string my_area, bool pac_obj2_arr_used[100],Pacman_Object pac_obj2_arr[100], int win_num, sf::RenderWindow& window) {
    window.setActive(true);
    std::vector<glm::ivec2> load_objects;

    printf("=> Loading objects for frustum:  X=%02d,Y=%02d   \n",frustum_count_x,frustum_count_y);
    for (auto u : frustum_object) {
        if (u.x==frustum_count_x && u.y==frustum_count_y) {
            load_objects.push_back(glm::ivec2(u.z,u.w));
        }
    }

    if (load_objects.size()==0) {
        window.setActive(false);
        return false;
    }

    printf("Needed:  ");

    for (auto u : load_objects) {
        printf("(%2d,%2d) ",u.x,u.y);
    }
    printf("(%d)\n",load_objects.size());
    bool cleaning=true;
    bool first=true;
    int cnt=0;
    while (cleaning) {
        cleaning=false;
        for (auto q : Pacman_Objects[win_num]) {
            bool found=false;
            for (auto p : load_objects) {
                if (q.map_x==p.x && q.map_y==p.y) {
                    found=true;
                }
            }
            if (!found) {
                q.show=0;
                if (first) printf("Erasing: (%2d,%2d)",q.map_x,q.map_y);
                else printf(" (%2d,%2d)",q.map_x,q.map_y);
                cnt++;
                first=false;
                erase_one_pacman_objects(q.map_x,q.map_y,win_num,pac_obj2_arr_used,pac_obj2_arr);
                cleaning=true;
                break;
            }
        }
    }
    if (cnt>0) printf(" (%d)",cnt);
    if (!first) printf("\n");
    first=true;
    for (auto q : Pacman_Objects[win_num]) {
        if (first) printf("Keeping: (%2d,%2d)",q.map_x,q.map_y);
        else printf(" (%2d,%2d)",q.map_x,q.map_y);
        first=false;
    }
    if (!first) printf(" (%d)\n",Pacman_Objects[win_num].size());

    cnt=0;
    first=true;
    std::vector<glm::ivec2> load_objects2;
    for (auto p : load_objects) {
        bool found=false;
        for (auto q : Pacman_Objects[win_num]) {
            if (q.map_x==p.x && q.map_y==p.y) {
                found=true;
                break;
            }
        }
        if (!found) {
            load_objects2.push_back(glm::ivec2(p.x,p.y));
            if (first) printf("To load: (%2d,%2d)",p.x,p.y);
            else printf(" (%2d,%2d)",p.x,p.y);
            cnt++;
            first=false;
        }
    }
    if (!first) printf(" (%d)\n",load_objects2.size());
    for (auto p : load_objects2) {
        bool found=false;
/*
        for (auto q : Pacman_Objects[win_num]) {
            if (q.map_x==p.x && q.map_y==p.y) {
                found=true;
            }
        }
*/
        if (!found) {
            std::string str=get_area_data(my_area,p.x,p.y);
            printf("\rLoading: (%2d,%2d) %s ",p.x,p.y,str.c_str());

            int i;
            for (i=0; i<100; i++) {
                if (pac_obj2_arr_used[i]==false) {
                    printf("Free loc. %d ",i);
                    break;
                }
            }
            if (i==100) { printf("\nError, i>100, adapt pac_obj2_arr size > 100"); return false; }

            char line[2000];
            strcpy(line,latitude_longditude.c_str());
//decimal_point
                        while (replace_str(line,",","."));
//            while (replace_str(line,".",","));
            double lat_north=0.0;
            double lat_south=0.0;
            double lon_west=0.0;
            double lon_east=0.0;
            int num=sscanf(line,"N=%lf S=%lf W=%lf E=%lf", &lat_north, &lat_south, &lon_west, &lon_east);
            if (num==4) {
                char lat_str[100];
                char lon_str[100];
                sprintf(lat_str,"%lf",(lat_north+lat_south)/2.0); while (replace_str(lat_str,",","."));
                sprintf(lon_str,"%lf",(lon_east+lon_west)/2.0); while (replace_str(lon_str,",","."));
                printf("https://www.google.com/maps/@%s,%s,17.00z\n",lat_str,lon_str);
            }

            pac_obj2_arr[i].bmin[0] = pac_obj2_arr[i].bmin[1] = pac_obj2_arr[i].bmin[2] = std::numeric_limits<float>::max();
            pac_obj2_arr[i].bmax[0] = pac_obj2_arr[i].bmax[1] = pac_obj2_arr[i].bmax[2] = -std::numeric_limits<float>::max();
            pac_obj2_arr[i].gDrawObjects.clear();
            pac_obj2_arr[i].materials.clear();
            pac_obj2_arr[i].textures.clear();
            pac_obj2_arr[i].show=0;
            global_octant_x=p.x;
            global_octant_y=p.y;
            burn=true;
            if (true == LoadObjAndConvert_window(pac_obj2_arr[i].bmin, pac_obj2_arr[i].bmax, pac_obj2_arr[i].gDrawObjects, pac_obj2_arr[i].materials, pac_obj2_arr[i].textures, (char*) str.c_str()))
            {
                pac_obj2_arr[i].map_x=p.x;
                pac_obj2_arr[i].map_y=p.y;
                pac_obj2_arr[i].arr_index=i;
                pac_obj2_arr[i].show=1;
                pac_obj2_arr_used[i]=true;

                Pacman_Objects[win_num].push_back(pac_obj2_arr[i]);
//                pac_obj2_arr_size=i;

//                printf("New object loaded: %d,%d: %s\n",p.x,p.y,str.c_str());

            } else {
                printf("Error loading new object: (%d,%d): %s\n",p.x,p.y,str.c_str());
                window.setActive(false);
                return true;
            }
//            window.setActive(false);

//            reset_text(win_num);
        }
    }
    if (Pacman_Objects[win_num].size()>0) {
        printf("\rGot:    ");
        for (auto q : Pacman_Objects[win_num]) {
            printf(" (%2d,%2d)",q.map_x,q.map_y);
        }
        printf(" (%d)",Pacman_Objects[win_num].size());
        printf("\n");
    } else {
        printf("No objects: X=%d,Y=%d\n",frustum_count_x,frustum_count_y);

    }
    window.setActive(false);
    return true;
}

void erase_one_pacman_objects(int map_x,int map_y,int win_num, bool pac_obj2_arr_used[100],Pacman_Object pac_obj2_arr[100]) {
    int num_p=0;
    int num_pb=0;
    int num_p1=0;
    int num_p1b=0;
    int num_p2=0;

    int n=0;
    bool deleted=false;
    for (auto p : Pacman_Objects[win_num]) {
        if (p.map_x==map_x && p.map_y==map_y) {
            {
                if (to_gpu) {
                    num_p1=0;
                    GLuint gluint_arr[p.textures.size()];
                    int num_com=0;
                    for (auto u : p.textures) {
                        gluint_arr[num_com++]=u.second;
                        num_p++;
                        num_p1++;
                    }
                    glDeleteTextures((GLsizei)p.textures.size(), gluint_arr);
                }
            }
            {
                if (to_gpu) {
                    num_p1b=0;
                    GLuint gluint_arr[p.gDrawObjects.size()];
                    int num_com=0;
                    for (auto u : p.gDrawObjects) {
                        gluint_arr[num_com++]=u.vb_id;
                        num_pb++;
                        num_p1b++;
                    }
                    glDeleteBuffers((GLsizei)p.gDrawObjects.size(), gluint_arr);
                }
            }

            p.map_x=-1;
            p.map_y=-1;
            pac_obj2_arr_used[p.arr_index]=false;
            num_p2++;

            pac_obj2_arr[p.arr_index].gDrawObjects.clear();
            pac_obj2_arr[p.arr_index].materials.clear();
            pac_obj2_arr[p.arr_index].textures.clear();
            p.gDrawObjects.clear();
            p.materials.clear();
            p.textures.clear();
            Pacman_Objects[win_num].erase(Pacman_Objects[win_num].begin()+n);
            return;
        }
        n++;
    }
//    Pacman_Objects[win_num].clear();
}
//bool analyse_3d(std::string my_area, int cur_x, int win_num, sf::RenderWindow& window, float eye2[3], float perspective[4],int frustum_toggle) {

bool reanalyse_3d(int cur_x, std::string& my_area, int win_num, bool pac_obj2_arr_used[100],Pacman_Object pac_obj2_arr[100], sf::RenderWindow& window) {
    int cur_y=0;
    char line[2000]="";

    std::string filename=get_area_data(std::string() + "Models",cur_x,cur_y);
    filename=filename.substr(0,filename.length());

    std::string marker_filename=filename.substr(0,filename.length()-3) + "cam";

    my_area=GetFileName(filename);
//    std::string my_area=GetFileName(filename);
    my_area=my_area.substr(0,my_area.length()-4);

    printf("Area: %s Got %s\n",my_area.c_str(),marker_filename.c_str());

    FILE* in;
    if ((in=fopen(marker_filename.c_str(),"r"))==NULL) {
        printf("get_one_3d_init(): Can not open file: %s\n",marker_filename.c_str());
        return false;
    }
//    char fline[2000]="";
    if (fgets (line,2000, in)!=NULL ) {
        sscanf(line,"QUATS=%e %e %e %e EYE=%e %e %e LOOKAT=%e %e %e TRANSLATION=%e %e %e PERSPECTIVE=%e %e %e %e BMIN=%e %e %e BMAX=%e %e %e FRUSTUM=%d\n",
            &int_q[0], &int_q[1], &int_q[2], &int_q[3],
            &int_e[0], &int_e[1], &int_e[2],
            &int_l[0], &int_l[1], &int_l[2],
            &int_t[0], &int_t[1], &int_t[2],
            &int_p[0], &int_p[1], &int_p[2], &int_p[3],
            &int_bmin[0], &int_bmin[1], &int_bmin[2],
            &int_bmax[0], &int_bmax[1], &int_bmax[2], &int_frustum_toggle);
        printf("LOAD:q0=%-+f q1=%-+f q2=%-+f q3=%-+f  e0=%-+f e1=%-+f e2=%-+f  l0=%-+f l1=%-+f l2=%-+f  t0=%-+f t1=%-+f t2=%-+f  p0=%-+f  bmin=%-+f %-+f %-+f  bmax=%-+f %-+f %-+f  frustum=%d\n",
                int_q[0],int_q[1],int_q[2],int_q[3],
                int_e[0],int_e[1],int_e[2],
                int_l[0],int_l[1],int_l[2],
                int_t[0],int_t[1],int_t[2],
                int_p[0],
                int_bmin[0], int_bmin[1], int_bmin[2],
                int_bmax[0], int_bmax[1], int_bmax[2], int_frustum_toggle
               );
    } else {
        printf("error reading file cam position: %s\n",marker_filename.c_str());
        return false;
    }
    char area[30];
    if (fgets (line,2000, in)!=NULL ) {
        float pos_x,pos_y,size_x,size_y;
//decimal_point
                        while (replace_str(line,",","."));
////        while (replace_str(line,".",","));
        sscanf(line,"POSITION_X=%e POSITION_Y=%e SIZE_X=%e SIZE_Y=%e FRUSTUMS_X=%d FRUSTUMS_Y=%d AREA=%30[^\n]",
            &pos_x,&pos_y,&size_x,&size_y,&frustum_size_x,&frustum_size_y,area);

        rectangle.setPosition(sf::Vector2f(pos_x,pos_y));
        rectangle.setSize(sf::Vector2f(size_x,size_y));

        printf("POSITION_X=%f POSITION_Y=%f SIZE_X=%f SIZE_Y=%f FRUSTUMS_X=%d FRUSTUMS_Y=%d AREA=%s\n",
                rectangle.getPosition().x, rectangle.getPosition().y,
                rectangle.getSize().x, rectangle.getSize().y,
                frustum_size_x,frustum_size_y,area);
        if (strcmp(area,my_area.c_str())==0) printf("Area names match ok.\n");
        else printf("Area names don't match!\n%s\n%s\n",area,my_area.c_str());
    } else {
        printf("error reading file frustum size/number: %s\n",marker_filename.c_str());
        return false;
    }
}

bool analyse_3d(double lat, double lon, std::string my_area, int cur_x, int win_num, sf::RenderWindow& window, float eye2[3],
                       float perspective[4],int frustum_toggle, glm::mat4 adapt, float maxExtent,
                       float lookat2[3], float up2[3], float move_object_x, float move_object_y, float move_object_z,
                       float translation[3],float curr_quat2[4], float bmin[3], float bmax[3]) {
    ShowTaskBar(true);

    int cur_y=0;
    char line[2000]="";
    char line_new[2000]="";
    char* l=&line_new[2];
    std::string filename=get_area_data(my_area,cur_x,cur_y);
    filename=filename.substr(0,filename.length());
    printf("Got %s\n",filename.c_str());

    my_area=GetFileName(filename);
    my_area=my_area.substr(0,my_area.length()-4);

    FILE* in;
    if ((in=fopen(filename.c_str(),"r"))==NULL) {
        printf("analyse_3d(): Can not open file: %s\n",filename.c_str());
        return false;
    }

    {
        FILE* marker_file=NULL;
        std::string marker_filename=filename.substr(0,filename.length()-3) + "cam";
        double qx,qy,qz,qw;
        double lx,ly,lz;
        double ex,ey,ez;
        double tx,ty,tz;
        double p0,p1,p2,p3;
        double bmin0,bmin1,bmin2;
        double bmax0,bmax1,bmax2;

        qx=curr_quat2[0]; qy=curr_quat2[1]; qz=curr_quat2[2]; qw=curr_quat2[3];
        if (frustum_toggle==1) {
            ex=eye2[0]+move_object_x/window.getSize().x;  ey=eye2[1]+move_object_y/window.getSize().y;    ez=eye2[2] + move_object_z/1000.0;
            lx=lookat2[0]+move_object_x/window.getSize().x;  ly=lookat2[1]+move_object_y/window.getSize().y;    lz=lookat2[2]+move_object_z/1000.0;
        } else {
            ex=eye2[0]+move_object_x/window.getSize().x;  ey=eye2[1]+move_object_y/window.getSize().y;    ez=eye2[2] + move_object_z/1000.0;
            lx=lookat2[0]+move_object_x/window.getSize().x;  ly=lookat2[1]+move_object_y/window.getSize().y;    lz=lookat2[2]+move_object_z/1000.0;
        }

        tx=translation[0]; ty=translation[1]; tz=translation[2];
        p0=perspective[0];p1=perspective[1];p2=perspective[2];p3=perspective[3];
        bmin0=bmin[0];bmin1=bmin[1];bmin2=bmin[2];
        bmax0=bmax[0];bmax1=bmax[1];bmax2=bmax[2];
        char test[1000];
        marker_file = fopen (marker_filename.c_str(), "w");
        if (marker_file==NULL) {
            printf("Cannot open %s for writing.",marker_filename.c_str());
            return false;
        }
        fprintf(marker_file, "QUATS=%-+e %-+e %-+e %-+e EYE=%-+e %-+e %-+e LOOKAT=%-+e %-+e %-+e TRANSLATION=%-+e %-+e %-+e PERSPECTIVE=%-+e %-+e %-+e %-+e BMIN=%-+e %-+e %-+e BMAX=%-+e %-+e %-+e FRUSTUM=%d\n",
                  qx,   qy,  qz,  qw,
                  ex,   ey,  ez,
                  lx,   ly,  lz,
                  tx,   ty,  tz,
                  p0,   p1,  p2,  p3,
                  bmin0,bmin1,bmin2,
                  bmax0,bmax1,bmax2,frustum_toggle);
        fclose(marker_file);
        printf("MARK: q0=%-+f q1=%-+f q2=%-+f q3=%-+f  e0=%-+f e1=%-+f e2=%-+f  l0=%-+f l1=%-+f l2=%-+f  t0=%-+f t1=%-+f t2=%-+f  p0=%-+f  bmin=%-+f %-+f %-+f  bmax=%-+f %-+f %-+f FRUSTUM=%d\n",
                  (float)qx,   (float)qy,  (float)qz,  (float)qw,
                  (float)ex,   (float)ey,  (float)ez,
                  (float)lx,   (float)ly,  (float)lz,
                  (float)tx,   (float)ty,  (float)tz,
                  (float)p0,  // (float)p1,  (float)p2,  (float)p3,
                  (float)bmin0,(float)bmin1,(float)bmin2,
                  (float)bmax0,(float)bmax1,(float)bmax2,frustum_toggle);
    }

    int lc=0,lf=0;
    std::string frustum_filename=filename.substr(0,filename.length()-3) + "cam";
    FILE* frustum_file=NULL;

    frustum_file = fopen (frustum_filename.c_str(), "a");
    sprintf(line,"POSITION_X=%-+e POSITION_Y=%-+e SIZE_X=%-+e SIZE_Y=%-+e FRUSTUMS_X=%d FRUSTUMS_Y=%d AREA=%s\n",
            (double)rectangle.getPosition().x, (double)rectangle.getPosition().y,
            (double)rectangle.getSize().x, (double)rectangle.getSize().y,
            frustum_size_x,frustum_size_y,my_area.c_str());
    fprintf(frustum_file,line);
//    fprintf(frustum_file,"POSITION_X=%f POSITION_Y=%f SIZE_X=%f SIZE_Y=%f FRUSTUMS_X=%d FRUSTUMS_Y=%d AREA=%s\n",
//            rectangle.getPosition().x, rectangle.getPosition().y,
//            rectangle.getSize().x, rectangle.getSize().y,
//            frustum_size_x,frustum_size_y,my_area.c_str());
    fclose(frustum_file);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    int do_size=Pacman_Objects[win_num][0].gDrawObjects.size();
    printf("DrawObjects.size()=%d\n",do_size);
    char* ret;
    std::vector<glm::ivec2> pos;
    int xp,yp;
    int xp_min=999999,xp_max=-999999;
    int yp_min=999999,yp_max=-999999;
    char dir[200];
    if (in!=NULL) {
        if (strstr(filename.c_str(), "canvas.nbt") != NULL) {
            fclose(in);
            for (int y=0; y<15; y++) {
                for (int x=0; x<30; x++) {
                    pos.push_back(glm::ivec2(x,y));
                }
            }
            xp_min=0;
            yp_min=0;
            xp_max=BITMAPSX-1;
            yp_max=BITMAPSY-1;
            lf=lc=BITMAPSX*BITMAPSY;
        } else {
            while ((ret=fgets(line_new,2000, in))!=NULL) {
                if (line_new[0]=='o') {
                    lc++;
                    xp=-1;yp=-1;
                    sscanf(line_new, "o %d_%d_%199[^\n]", &xp,&yp,dir);
                    if (xp!=-1 && yp!=-1) {
                        pos.push_back(glm::ivec2(xp,yp));
                        if (xp<xp_min) xp_min=xp;
                        if (yp<yp_min) yp_min=yp;
                        if (xp>xp_max) xp_max=xp;
                        if (yp>yp_max) yp_max=yp;
                    } else {
                        printf("\nError reading position from .obj file o marker -> %s\n",line_new);
                    }

                } else if (strcmp(line_new,"# faces\n")==0) {
                    lf++;
                }
            }
            fclose(in);
        }
    }
    int xp_diff=xp_max-xp_min;
    int yp_diff=yp_max-yp_min;
    printf("Object X %d TO %d\n",xp_min,xp_max);
    printf("Object Y %d TO %d\n",yp_min,yp_max);
    printf("faces=%4d objects=%4d in %s\n",lf,lc,filename.c_str());
    if (lf!=lc) printf("                                                      ERROR: faces!=objects\n");
    else printf("faces==objects\n OK!");
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    sf::Event event;
    int size=Pacman_Objects[win_num][0].gDrawObjects.size();
    window.setActive(false);
    window.setVerticalSyncEnabled(true);
    bool is_active=true;
    window.setActive(true);
    COLOR_ARRAY=false;
    TEXTURE_ARRAY=false;
    WIRE_FRAME=true;
    for (int n=0; n<120; n++) {
        COLOR_ARRAY=!COLOR_ARRAY;
        if (n%2) TEXTURE_ARRAY=!TEXTURE_ARRAY;
        if (n%4) WIRE_FRAME=!WIRE_FRAME;
//            if (!is_active) { window.setActive(true); is_active=true; }

        if (!is_active) { window.setActive(true); is_active=true; }
        glClearColor(0.0,0.0,0.0,0.0);
        glEnable(GL_DEPTH_TEST); glDepthMask(GL_TRUE); glClearDepth(1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_TEXTURE_2D);


//fixed1
                static glm::vec3 move_object;

                move_object = glm::vec3(move_object_x, move_object_y, move_object_z);
                glm::vec3 add_xyz = glm::vec3(0.0, 0.0, 0.0);

                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                make_lookat( perspective, frustum_toggle, eye2, lookat2, up2, move_object, window.getSize(), true, maxExtent);

                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                glm::mat4 test;
                rotate_around_point(move_object, add_xyz, area, lat, lon, true, interpolate_on, rot_mat, test, curr_quat2, maxExtent, bmin, bmax);

                glScalef(1.0f / maxExtent, 1.0f / maxExtent, 1.0f / maxExtent);

                if ( !(interpolate_on  || burn) ) {
                    translation[0]=-0.5 * (bmax[0] + bmin[0])+add_xyz.x;
                    translation[1]=-0.5 * (bmax[1] + bmin[1])+add_xyz.y;
                    translation[2]=-0.5 * (bmax[2] + bmin[2])+add_xyz.z;
                }
                glTranslatef(translation[0] ,translation[1] ,  translation[2]);

/*
        glMatrixMode(GL_PROJECTION); glLoadIdentity();
        makeFrustum(perspective[0],perspective[1],perspective[2],perspective[3],frustum_toggle, eye2);
        if (frustum_toggle==1) {
            gluLookAt(
                        eye2[0],       eye2[1],     eye2[2]+3.0f ,
                        lookat2[0],    lookat2[1],    lookat2[2],
                        up2[0],   up2[1], up2[2]);
        } else {
            gluLookAt(  eye2[0],       eye2[1],     eye2[2],
                        lookat2[0],    lookat2[1],    lookat2[2],
                        up2[0],   up2[1], up2[2]);
        }
        glMatrixMode(GL_MODELVIEW);  glLoadIdentity(); glMultMatrixf((float*)&adapt);
            glScalef(1.0f / maxExtent, 1.0f / maxExtent, 1.0f / maxExtent); glTranslatef(translation[0] ,translation[1] ,  translation[2]);

        if (smooth) glShadeModel(GL_SMOOTH); else glShadeModel(GL_FLAT);

*/








        window.pollEvent(event);
        for (int m=0; m<do_size; m++) {

            if (m<pos.size()) {
                xp=pos[m].x; yp=pos[m].y;
            } else {
                printf("Error reading position from vector -> m=%d pos.size()=%d\n",m,pos.size());
                xp=-1; yp=-1;
            }

//            GLubyte color[3];
            float blue= ((float)n*3.0+(1.0+(float)xp)*(1.0+(float)yp)/16.0)/16.0;
//            blue=(blue-floor(blue))*255;
//            color[0]=(GLubyte)xp;
//            color[1]=(GLubyte)yp;
//            color[2]=(GLubyte) blue;
            glm::vec3 colorf;
            colorf.x=(float)xp/255.0;
            colorf.y=(float)yp/255.0;
            colorf.z= blue;
//            float colorf[3];
//            colorf[0]=(float)xp/255.0;
//            colorf[1]=(float)yp/255.0;
//            colorf[2]= blue;
            Draw_one_shape(Pacman_Objects[win_num][0].gDrawObjects, Pacman_Objects[win_num][0].materials, Pacman_Objects[win_num][0].textures, m,
                           colorf);
//                           glm::ivec3(xp,yp,(int)blue));

        }
        if (is_active) { window.setActive(false); is_active=false; }
        window.display();
    }

    remember_911=true;

    int map[xp_max+1][yp_max+1];
    for (int y=0; y<=yp_max; y++) {
        for (int x=0; x<=xp_max; x++) {
            if (xp>=xp_min && xp<=xp_max && yp>=yp_min && yp<=yp_max) map[x][y]=-1;
            else map[x][y]=-2;
        }
    }
    for (int m=0; m<do_size; m++) {
        if (m<pos.size()) {
            xp=pos[m].x; yp=pos[m].y;
            if (xp>=xp_min && xp<=xp_max && yp>=yp_min && yp<=yp_max)
                map[xp][yp]=m;
            else
                printf("\nError(1): Object# %d pos x=%d, pos y=%d !!!!!!!!!!!!!!!!!!!!!!!\n",m,xp,yp);
        } else {
            printf("\nError(2): Object# %d pos x=%d, pos y=%d !!!!!!!!!!!!!!!!!!!!!!!!\n",m,xp,yp);
        }
    }
    window.clear(sf::Color(255,0,0,255));
    window.display();
//    window.setVerticalSyncEnabled(true);
    int total_count=0;
    window.setActive(true);
    glShadeModel(GL_FLAT);
    COLOR_ARRAY=false;
    TEXTURE_ARRAY=false;
    WIRE_FRAME=true;
    glLineWidth(2.0);
    frustum_file = fopen (frustum_filename.c_str(), "a");
    int init=2;
    int x_o=-1;
    int y_o=-1;
    int ending=0;
//    for (int y=0; y<frustum_size_y; y++) {
    for (int y=0; y<=frustum_size_y; y++) {
        for (int x=0; x<frustum_size_x; x++) {
            frustum_count_x=x;
            frustum_count_y=y;

            window.setActive(true);

            glClearColor(0.0,0.0,0.0,0.0);
            glEnable(GL_DEPTH_TEST); glDepthMask(GL_TRUE); glClearDepth(1.f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_TEXTURE_2D);



//fixed2
                static glm::vec3 move_object;

                move_object = glm::vec3(move_object_x, move_object_y, move_object_z);
                glm::vec3 add_xyz = glm::vec3(0.0, 0.0, 0.0);

                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                make_lookat( perspective, frustum_toggle, eye2, lookat2, up2, move_object, window.getSize(), true, maxExtent);

                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                glm::mat4 test;
                rotate_around_point( move_object, add_xyz, area, lat, lon, true, interpolate_on, rot_mat, test, curr_quat2, maxExtent, bmin, bmax);

                glScalef(1.0f / maxExtent, 1.0f / maxExtent, 1.0f / maxExtent);

                if ( !(interpolate_on  || burn) ) {
                    translation[0]=-0.5 * (bmax[0] + bmin[0])+add_xyz.x;
                    translation[1]=-0.5 * (bmax[1] + bmin[1])+add_xyz.y;
                    translation[2]=-0.5 * (bmax[2] + bmin[2])+add_xyz.z;
                }
                glTranslatef(translation[0] ,translation[1] ,  translation[2]);

/*

            glMatrixMode(GL_PROJECTION); glLoadIdentity();
            makeFrustum(perspective[0],perspective[1],perspective[2],perspective[3],frustum_toggle, eye2);
            if (frustum_toggle==1) {
                gluLookAt(
                            eye2[0],       eye2[1],     eye2[2]+3.0f ,
                            lookat2[0],    lookat2[1],    lookat2[2],
                            up2[0],   up2[1], up2[2]);
            } else {
                gluLookAt(  eye2[0],       eye2[1],     eye2[2],
                            lookat2[0],    lookat2[1],    lookat2[2],
                            up2[0],   up2[1], up2[2]);
            }
            glMatrixMode(GL_MODELVIEW);  glLoadIdentity();
            glMultMatrixf((float*)&adapt);
            glScalef(1.0f / maxExtent, 1.0f / maxExtent, 1.0f / maxExtent); glTranslatef(translation[0] ,translation[1] ,  translation[2]);

*/





            int hits=0;
            glm::vec3 colorf;
            int yp1;
            for (int m=0; m<do_size; m++) {
                xp=pos[m].x; yp=pos[m].y;
//                xp=xp+1;
//                yp=yp+1;
                if (xp==128) printf("xp=%d,yp=%d m=%d!!!!!!!!!!!!!!!!!!!!!!!\n",xp,yp,m);
                yp1=yp/256;
                yp=yp-yp1*256;
                colorf.x=(float)(xp)/255.0;
                colorf.y=(float)(yp)/255.0;
//                colorf.x=(float)(xp)/256.0;
//                colorf.y=(float)(yp)/256.0;
                colorf.z=(float)(yp1)/255.0;
//                colorf.z=1.0-(float)(yp1)/256.0;
                Draw_one_shape(Pacman_Objects[win_num][0].gDrawObjects, Pacman_Objects[win_num][0].materials, Pacman_Objects[win_num][0].textures, m,
                               colorf);
            }

            window.setActive(false);
//            window.draw(sprite_shit);
            window.display();
//            window.setActive(true);
//            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//            window.setActive(false);
            if (x_o>-1) {
                texture1_local.update(window);
                frustum_count_x=x_o;
                frustum_count_y=y_o;
//                frustum_count_x=x;
//                frustum_count_y=y;

                image_test=texture1_local.copyToImage();

//                char naam[2000];
//                mkdir("../Models/analyse");
//                sprintf(naam,"../Models/analyse/picture.%06d.%06d.png",(frustum_count_y),(frustum_count_x));
//                image_test.saveToFile(naam);

                while (window.pollEvent(event));

                int count=0;
                int count2=0;
                for (int y=0; y<1080; y++) {
                    for (int x=0; x<1920; x++) {
                        pixel_test=image_test.getPixel(x,y);
//joehoe
                        if (pixel_test.a>0) {
                            count2++;
//                            int m=(int)(pixel_test.r/2)-1+127*((int)(pixel_test.g/2)-1);
//                            int m=pixel_test.r+256*pixel_test.g;
//                            xp=pos[m].x; yp=pos[m].y;
                            xp=pixel_test.r;
                            yp=pixel_test.g;
                            int yp1;
                            yp1=pixel_test.b;
//                            yp1=255-pixel_test.b;
                            yp=yp+yp1*256;
//                            xp=xp-1;
//                            yp=yp-1;
//                            if (yp>255) printf("map[%d][%d]=%d\n",xp,yp,map[xp][yp]);

//                            if (xp>=xp_min && xp<=xp_max && yp>=yp_min && yp<=yp_max) {
                                if (map[xp][yp]>=0) {
    //                                printf("\nreceived: red=%d green=%d\n",(int)pixel_test.r,(int)pixel_test.g);
                                    count++;
                                    map[xp][yp]=-10-map[xp][yp];
                                    if (count==1) printf("\r#objects=%d frustum X=%02d,Y=%02d Found: ",do_size,frustum_count_x,frustum_count_y);
                                    printf("#%4d(%2d,%2d) ",-map[xp][yp]-10,xp,yp);
                                    fprintf(frustum_file,"FRUSTUM_X=%d FRUSTUM_Y=%d OBJECT_X=%d OBJECT_Y=%d OBJ=%s\n",
                                            frustum_count_x,frustum_count_y,xp,yp,get_area_data(my_area,xp,yp).c_str());


                                } else if (map[xp][yp]==-1) {
                                    printf("\n#objects=%d frustum X=%02d,Y=%02d ERROR(4): ",do_size,frustum_count_x,frustum_count_y);
                                    printf("#%d(%d,%d)\n",map[xp][yp],xp,yp);
//joehoe
                                    map[xp][yp]=-2;
                                }
//                            } else {
//                                printf("\nERROR(5): #objects=%d frustum X=%02d,Y=%02d ERROR: ",do_size,frustum_count_x,frustum_count_y);
//                                printf("#%d(%d,%d)\n",-map[xp][yp]-10,xp,yp);
//                            }
                        }
                    }
                }
                if (count>0) printf("Total=%d  Pixels=%f%%\n",count,(float)count2*100.0/(1920.0*1080.0));
                else printf("Nothing: FRUSTUM_X=%d FRUSTUM_Y=%d\n",frustum_count_x,frustum_count_y);
                for (int y=yp_min; y<=yp_max; y++) {
                    for (int x=xp_min; x<=xp_max; x++) {
                        if (xp>=xp_min && xp<=xp_max && yp>=yp_min && yp<=yp_max) map[x][y]=-1;
                        else map[x][y]=-2;
                    }
                }
                for (int m=0; m<do_size; m++) {
                    if (m<pos.size()) {
                        xp=pos[m].x; yp=pos[m].y;
                        if (xp>=xp_min && xp<=xp_max && yp>=yp_min && yp<=yp_max)
                            map[xp][yp]=m;
                        else
                            printf("\nError(6): Object# %d pos x=%d, pos y=%d\n",m,xp,yp);
                    } else {
                        printf("\nError(7): Object# %d pos x=%d, pos y=%d\n",m,xp,yp);
                    }
                }
            }
            x_o=x;
            y_o=y;
            if (frustum_count_x==frustum_size_y-1 && frustum_count_y==frustum_size_x-1) {ending=1; break; }
//            printf("");

//            sf::sleep(sf::milliseconds(10000.0/60.0));

//            if (is_active) { window.setActive(false); is_active=false; }

//            window.display();
//            printf("frustum x=%d y=%d\n",x,y);
//            sf::sleep(sf::milliseconds(100));
        }
        if (ending==1) {break; }
    }
    fclose(frustum_file);
    printf("\n");
    glLineWidth(1.0);
    COLOR_ARRAY=true;
    TEXTURE_ARRAY=true;
    WIRE_FRAME=false;
    remember_911=false;
//    window.setVerticalSyncEnabled(true);
}

bool plot_it(double& lat, double& lon, std::string& my_area, int win_num, sf::RenderWindow& window, float eye2[3],
                       float perspective[4],int frustum_toggle, float maxExtent,
                       float lookat2[3], float up2[3], float move_object_x, float move_object_y, float move_object_z,
                       float translation[3],float curr_quat2[4], float bmin[3], float bmax[3]) {

    static int counter=60;
    if (burn) remember_911_2=true;

    window.setActive(true);

    glDepthMask(GL_TRUE);
    glClearDepth(1.f);

//    glClearColor(0,0,0,0);
    glClearColor(0.7,0.8,1.0,0);

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);

    static glm::vec3 move_object;
    static glm::vec3 add_xyz;
    move_object = glm::vec3(move_object_x, move_object_y, move_object_z);
    add_xyz = glm::vec3(0.0, 0.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    make_lookat( perspective, frustum_toggle, eye2, lookat2, up2, move_object, window.getSize(), true, maxExtent);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glm::mat4 test(1.0f);

    rotate_around_point( move_object, add_xyz, my_area, lat, lon, true, interpolate_on, rot_mat, test, curr_quat2, maxExtent, bmin, bmax);

    glScalef(1.0f / maxExtent, 1.0f / maxExtent, 1.0f / maxExtent);

    if ( !(interpolate_on  || burn) ) {
        translation[0]=-0.5 * (bmax[0] + bmin[0])+add_xyz.x;
        translation[1]=-0.5 * (bmax[1] + bmin[1])+add_xyz.y;
        translation[2]=-0.5 * (bmax[2] + bmin[2])+add_xyz.z;
    }
    glTranslatef(translation[0] ,translation[1] ,  translation[2]);

    if (smooth)
        glShadeModel(GL_SMOOTH);
    else
        glShadeModel(GL_FLAT);

    int size_o=load_objects_pos.size();

    static int rr=0;
    rr++;
    counter--;
    if (counter==0) counter=60;
    if (Pacman_Objects[win_num].size()>0) {
        for (auto u : Pacman_Objects[win_num]) {
            if (!burn && !(formula==1 && shade_map==0)) {
                int do_size=u.gDrawObjects.size();
                for (int m=0; m<do_size; m++) {
                    if (m<size_o) {
                        int load_objects=load_objects_pos[m].z;
                        int red=255-(float)load_objects_pos[m].x;
                        int green=255-(float)load_objects_pos[m].y;
                        int blue=255-255*(float)m/(float)do_size;

                        if ((load_objects==1) || (selector_pos.x==load_objects_pos[m].x && selector_pos.y==load_objects_pos[m].y)) {

                            static int ox=-1,oy=-1;
                            if (load_objects==0 && (!remember_911_2 && (ox!=selector_pos.x || oy!=selector_pos.y))) {
                                selector_dir=load_objects_dir[m];
                                printf("POS: X=%d,Y=%d %s\n",selector_pos.x,selector_pos.y,selector_dir.c_str()); //
                            }
                            ox=selector_pos.x;
                            oy=selector_pos.y;

                            int red=(int)(128+get_fast_sin( M_PI/2.0+(float)m/(float)do_size*2.0*M_PI )*127);
                            int green=(int)(128+get_fast_sin( M_PI/2.0+(float)(m+rr*2)/(float)do_size*2.0*M_PI )*127);
                            int blue=(int)(255*((float)m/(float)do_size));
                            if (counter<30) WIRE_FRAME=!WIRE_FRAME;
                            if (counter<30) COLOR_ARRAY=!COLOR_ARRAY;

                            glm::vec3 colorf;
                            colorf.x=(float)red/255.0;
                            colorf.y=(float)green/255.0;
                            colorf.z=(float)blue/255.0;

                            Draw_one_shape(u.gDrawObjects, u.materials, u.textures, m, colorf);
//                                Draw_one_shape(u.gDrawObjects, u.materials, u.textures, m, glm::ivec3(red,green,blue ));
                            if (counter<30) WIRE_FRAME=!WIRE_FRAME;
                            if (counter<30) COLOR_ARRAY=!COLOR_ARRAY;
                        } else {
//                                GLubyte color[3];
//                                color[0]=(GLubyte)red;
//                                color[1]=(GLubyte)green;
//                                color[2]=(GLubyte)blue;
//                                float colorf[3];
//                                colorf[0]=(float)red/255.0;
//                                colorf[1]=(float)green/255.0;
//                                colorf[2]=(float)blue/255.0;
                            glm::vec3 colorf;
                            colorf.x=(float)red/255.0;
                            colorf.y=(float)green/255.0;
                            colorf.z=(float)blue/255.0;
                            Draw_one_shape(u.gDrawObjects, u.materials, u.textures, m, colorf);
//                                Draw_one_shape(u.gDrawObjects, u.materials, u.textures, m, glm::ivec3(red,green,blue ));
                        }
                    } else {
                        if (selector_pos.x==m) {
                            static int ox=-1;
                            if (ox!=selector_pos.x) {
                                printf("POS: N=%d %s\n",selector_pos.x,load_objects_dir[m].c_str());
                                ox=selector_pos.x;
                            }
                            int red=128+get_fast_sin(M_PI/2.0 + (float)m/(float)do_size*2.0*M_PI )*127;
                            int green=128+get_fast_sin( (float)(m+rr*2.0)/(float)do_size*2.0*M_PI )*127;
                            int blue=255*((float)m/(float)do_size);
//                                GLubyte color[3];
//                                color[0]=(GLubyte)red;
//                                color[1]=(GLubyte)green;
//                                color[2]=(GLubyte)blue;
//                                float colorf[3];
//                                colorf[0]=(float)red/255.0;
//                                colorf[1]=(float)green/255.0;
//                                colorf[2]=(float)blue/255.0;
                            glm::vec3 colorf;
                            colorf.x=(float)red/255.0;
                            colorf.y=(float)green/255.0;
                            colorf.z=(float)blue/255.0;

                            Draw_one_shape(u.gDrawObjects, u.materials, u.textures, m, colorf);
                        } else {
                            int red=128+get_fast_sin( (float)m/(float)do_size*2.0*M_PI )*127;
                            int green=128+get_fast_sin( (float)(m+rr)/(float)do_size*2.0*M_PI )*127;
                            int blue=255*(1.0-(float)m/(float)do_size);
//                                GLubyte color[3];
//                                color[0]=(GLubyte)red;
//                                color[1]=(GLubyte)green;
//                                color[2]=(GLubyte)blue;
//                                GLfloat colorf[3];
//                                colorf[0]=(float)red/255.0;
//                                colorf[1]=(float)green/255.0;
//                                colorf[2]=(float)blue/255.0;
                            glm::vec3 colorf;
                            colorf.x=(float)red/255.0;
                            colorf.y=(float)green/255.0;
                            colorf.z=(float)blue/255.0;
                            Draw_one_shape(u.gDrawObjects, u.materials, u.textures, m, colorf);
                        }
                    }
                }
            } else {
                    Draw(u.gDrawObjects, u.materials, u.textures);
            }
        }
    }
    window.setActive(false);
//    window.display();
}



bool analyse_3d_depth(double lat, double lon, std::string my_area, int cur_x, int win_num, sf::RenderWindow& window, float eye2[3],
                       float perspective[4],int frustum_toggle, glm::mat4 adapt, float maxExtent,
                       float lookat2[3], float up2[3], float move_object_x, float move_object_y, float move_object_z,
                       float translation[3],float curr_quat2[4], float bmin[3], float bmax[3]) {
    ShowTaskBar(true);

    sf::Shader depth_shader;
    if (!depth_shader.loadFromFile("shaders/depth_shader.frag", sf::Shader::Fragment))
    {
        printf("FRAGMENT SHADER ERROR: %s\n","shaders/depth_shader.frag");
        return false;
    }
    sf::Shader::bind(&depth_shader);
//    depth_shader.setUniform("texture_in", sf::Shader::CurrentTexture);
//    depth_shader.setUniform("texture_buffer", texture_from_buffer.getTexture());
//    depth_shader.setUniform("iResolution",  sf::Vector2f( (float)texture_from_ffmpeg.getSize().x,(float)texture_from_ffmpeg.getSize().y) );


    int cur_y=0;
    char line[2000]="";
    char line_new[2000]="";
    char* l=&line_new[2];
    std::string filename=get_area_data(my_area,cur_x,cur_y);
    filename=filename.substr(0,filename.length());
    printf("Got %s\n",filename.c_str());

    my_area=GetFileName(filename);
    my_area=my_area.substr(0,my_area.length()-4);

    FILE* in;
    if ((in=fopen(filename.c_str(),"r"))==NULL) {
        printf("analyse_3d(): Can not open file: %s\n",filename.c_str());
        return false;
    }

    {
        FILE* marker_file=NULL;
        std::string marker_filename=filename.substr(0,filename.length()-3) + "cam";
        double qx,qy,qz,qw;
        double lx,ly,lz;
        double ex,ey,ez;
        double tx,ty,tz;
        double p0,p1,p2,p3;
        double bmin0,bmin1,bmin2;
        double bmax0,bmax1,bmax2;

        qx=curr_quat2[0]; qy=curr_quat2[1]; qz=curr_quat2[2]; qw=curr_quat2[3];
        if (frustum_toggle==1) {
            ex=eye2[0]+move_object_x/window.getSize().x;  ey=eye2[1]+move_object_y/window.getSize().y;    ez=eye2[2] + move_object_z/1000.0;
            lx=lookat2[0]+move_object_x/window.getSize().x;  ly=lookat2[1]+move_object_y/window.getSize().y;    lz=lookat2[2]+move_object_z/1000.0;
        } else {
            ex=eye2[0]+move_object_x/window.getSize().x;  ey=eye2[1]+move_object_y/window.getSize().y;    ez=eye2[2] + move_object_z/1000.0;
            lx=lookat2[0]+move_object_x/window.getSize().x;  ly=lookat2[1]+move_object_y/window.getSize().y;    lz=lookat2[2]+move_object_z/1000.0;
        }
        tx=translation[0]; ty=translation[1]; tz=translation[2];
        p0=perspective[0];p1=perspective[1];p2=perspective[2];p3=perspective[3];
        bmin0=bmin[0];bmin1=bmin[1];bmin2=bmin[2];
        bmax0=bmax[0];bmax1=bmax[1];bmax2=bmax[2];
        char test[1000];
        marker_file = fopen (marker_filename.c_str(), "w");
        fprintf(marker_file, "QUATS=%-+e %-+e %-+e %-+e EYE=%-+e %-+e %-+e LOOKAT=%-+e %-+e %-+e TRANSLATION=%-+e %-+e %-+e PERSPECTIVE=%-+e %-+e %-+e %-+e BMIN=%-+e %-+e %-+e BMAX=%-+e %-+e %-+e FRUSTUM=%d\n",
                  qx,   qy,  qz,  qw,
                  ex,   ey,  ez,
                  lx,   ly,  lz,
                  tx,   ty,  tz,
                  p0,   p1,  p2,  p3,
                  bmin0,bmin1,bmin2,
                  bmax0,bmax1,bmax2,frustum_toggle);
        fclose(marker_file);
        printf("MARK: q0=%-+f q1=%-+f q2=%-+f q3=%-+f  e0=%-+f e1=%-+f e2=%-+f  l0=%-+f l1=%-+f l2=%-+f  t0=%-+f t1=%-+f t2=%-+f  p0=%-+f  bmin=%-+f %-+f %-+f  bmax=%-+f %-+f %-+f FRUSTUM=%d\n",
                  (float)qx,   (float)qy,  (float)qz,  (float)qw,
                  (float)ex,   (float)ey,  (float)ez,
                  (float)lx,   (float)ly,  (float)lz,
                  (float)tx,   (float)ty,  (float)tz,
                  (float)p0,  // (float)p1,  (float)p2,  (float)p3,
                  (float)bmin0,(float)bmin1,(float)bmin2,
                  (float)bmax0,(float)bmax1,(float)bmax2,frustum_toggle);
    }

    int lc=0,lf=0;
    std::string frustum_filename=filename.substr(0,filename.length()-3) + "cam";
    FILE* frustum_file=NULL;

    frustum_file = fopen (frustum_filename.c_str(), "a");
    sprintf(line,"POSITION_X=%-+e POSITION_Y=%-+e SIZE_X=%-+e SIZE_Y=%-+e FRUSTUMS_X=%d FRUSTUMS_Y=%d AREA=%s\n",
            (double)rectangle.getPosition().x, (double)rectangle.getPosition().y,
            (double)rectangle.getSize().x, (double)rectangle.getSize().y,
            frustum_size_x,frustum_size_y,my_area.c_str());
    fprintf(frustum_file,line);
//    fprintf(frustum_file,"POSITION_X=%f POSITION_Y=%f SIZE_X=%f SIZE_Y=%f FRUSTUMS_X=%d FRUSTUMS_Y=%d AREA=%s\n",
//            rectangle.getPosition().x, rectangle.getPosition().y,
//            rectangle.getSize().x, rectangle.getSize().y,
//            frustum_size_x,frustum_size_y,my_area.c_str());
    fclose(frustum_file);


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    int do_size=Pacman_Objects[win_num][0].gDrawObjects.size();
    printf("DrawObjects.size()=%d\n",do_size);
    char* ret;
    std::vector<glm::ivec2> pos;
    int xp,yp;
    int xp_min=999999,xp_max=-999999;
    int yp_min=999999,yp_max=-999999;
    char dir[200];
    if (in!=NULL) {
        while ((ret=fgets(line_new,2000, in))!=NULL) {
            if (line_new[0]=='o') {
                lc++;
                xp=-1;yp=-1;
                sscanf(line_new, "o %d_%d_%199[^\n]", &xp,&yp,dir);
                if (xp!=-1 && yp!=-1) {
                    pos.push_back(glm::ivec2(xp,yp));
                    if (xp<xp_min) xp_min=xp;
                    if (yp<yp_min) yp_min=yp;
                    if (xp>xp_max) xp_max=xp;
                    if (yp>yp_max) yp_max=yp;
                } else {
                    printf("\nError reading position from .obj file o marker -> %s\n",line_new);
                }

    //            printf("faces=%4d objects=%4d %s\r",lf,lc,l);
            } else if (strcmp(line_new,"# faces\n")==0) {
                lf++;
    //            printf("faces=%4d objects=%4d %s\r",lf,lc,l);
            }
        }
        fclose(in);
    }
    int xp_diff=xp_max-xp_min;
    int yp_diff=yp_max-yp_min;
    printf("Object X %d TO %d\n",xp_min,xp_max);
    printf("Object Y %d TO %d\n",yp_min,yp_max);
    printf("faces=%4d objects=%4d in %s\n",lf,lc,filename.c_str());
    if (lf!=lc) printf("                                                      ERROR: faces!=objects\n");
    else printf("faces==objects\n OK!");

//    glEnable(GL_DEPTH_TEST);
//    glDepthMask(GL_TRUE);
//    glDisable(GL_DEPTH_TEST);
//    glDepthMask(GL_FALSE);
    sf::Event event;
    int size=Pacman_Objects[win_num][0].gDrawObjects.size();
    window.setActive(false);
    window.setVerticalSyncEnabled(true);
    bool is_active=true;
    window.setActive(true);
    COLOR_ARRAY=false;
    TEXTURE_ARRAY=false;
    WIRE_FRAME=true;
    for (int n=0; n<120; n++) {
        COLOR_ARRAY=!COLOR_ARRAY;
        if (n%2) TEXTURE_ARRAY=!TEXTURE_ARRAY;
        if (n%4) WIRE_FRAME=!WIRE_FRAME;

        if (!is_active) { window.setActive(true); is_active=true; }

        glClearColor(0.0,0.0,0.0,0.0);
        glEnable(GL_DEPTH_TEST); glDepthMask(GL_TRUE); glClearDepth(1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_TEXTURE_2D);

        glMatrixMode(GL_PROJECTION); glLoadIdentity();
        makeFrustum(perspective[0],perspective[1],perspective[2],perspective[3],frustum_toggle, eye2);

        if (frustum_toggle==1) { gluLookAt( eye2[0]+move_object_x/window.getSize().x,       eye2[1]+move_object_y/window.getSize().y,       eye2[2]+3.0f + move_object_z/1000.0, lookat2[0]+move_object_x/window.getSize().x,    lookat2[1]+move_object_y/window.getSize().y,    lookat2[2]+move_object_z/1000.0,up2[0],   up2[1], up2[2]); }
        else {                   gluLookAt( eye2[0]+move_object_x/window.getSize().x,       eye2[1]+move_object_y/window.getSize().y,       eye2[2]+move_object_z/1000.0,lookat2[0]+move_object_x/window.getSize().x,    lookat2[1]+move_object_y/window.getSize().y,    lookat2[2]+move_object_z/1000.0,up2[0],   up2[1], up2[2]); }
        glMatrixMode(GL_MODELVIEW);  glLoadIdentity(); glMultMatrixf((float*)&adapt);
        glScalef(1.0f / maxExtent, 1.0f / maxExtent, 1.0f / maxExtent); glTranslatef(translation[0] ,translation[1] ,  translation[2]);
        if (smooth) glShadeModel(GL_SMOOTH); else glShadeModel(GL_FLAT);

        window.pollEvent(event);
        for (int m=0; m<do_size; m++) {

            if (m<pos.size()) {
                xp=pos[m].x; yp=pos[m].y;
            } else {
                printf("Error reading position from vector -> m=%d pos.size()=%d\n",m,pos.size());
                xp=-1; yp=-1;
            }

//            GLubyte color[3];
            float blue= ((float)n*3.0+(1.0+(float)xp)*(1.0+(float)yp)/16.0)/16.0;
            glm::vec3 colorf;
            colorf.x=(float)xp/255.0;
            colorf.y=(float)yp/255.0;
            colorf.z= blue;
            Draw_one_shape(Pacman_Objects[win_num][0].gDrawObjects, Pacman_Objects[win_num][0].materials, Pacman_Objects[win_num][0].textures, m,
                           colorf);

        }
        if (is_active) { window.setActive(false); is_active=false; }
        window.display();
    }

    remember_911=true;

    int map[xp_max+1][yp_max+1];
    for (int y=0; y<=yp_max; y++) {
        for (int x=0; x<=xp_max; x++) {
            if (xp>=xp_min && xp<=xp_max && yp>=yp_min && yp<=yp_max) map[x][y]=-1;
            else map[x][y]=-2;
        }
    }
    for (int m=0; m<do_size; m++) {
        if (m<pos.size()) {
            xp=pos[m].x; yp=pos[m].y;
            if (xp>=xp_min && xp<=xp_max && yp>=yp_min && yp<=yp_max)
                map[xp][yp]=m;
            else
                printf("\nError(1): Object# %d pos x=%d, pos y=%d !!!!!!!!!!!!!!!!!!!!!!!\n",m,xp,yp);
        } else {
            printf("\nError(2): Object# %d pos x=%d, pos y=%d !!!!!!!!!!!!!!!!!!!!!!!!\n",m,xp,yp);
        }
    }
    window.clear(sf::Color(255,0,0,255));
    window.display();
//    window.setVerticalSyncEnabled(true);
    int total_count=0;
    window.setActive(true);
    glShadeModel(GL_FLAT);
    COLOR_ARRAY=false;
    TEXTURE_ARRAY=false;
    WIRE_FRAME=true;
    glLineWidth(2.0);
    frustum_file = fopen (frustum_filename.c_str(), "a");
    int init=2;
    int x_o=-1;
    int y_o=-1;
    int ending=0;
//    for (int y=0; y<frustum_size_y; y++) {
    for (int y=0; y<=frustum_size_y; y++) {
        for (int x=0; x<frustum_size_x; x++) {
            frustum_count_x=x;
            frustum_count_y=y;

            window.setActive(true);

            glClearColor(0.0,0.0,0.0,0.0);
            glEnable(GL_DEPTH_TEST); glDepthMask(GL_TRUE); glClearDepth(1.f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_TEXTURE_2D); glMatrixMode(GL_PROJECTION); glLoadIdentity();
            makeFrustum(perspective[0],perspective[1],perspective[2],perspective[3],frustum_toggle, eye2);
            if (frustum_toggle==1) { gluLookAt( eye2[0]+move_object_x/window.getSize().x,       eye2[1]+move_object_y/window.getSize().y,       eye2[2]+3.0f + move_object_z/1000.0, lookat2[0]+move_object_x/window.getSize().x,    lookat2[1]+move_object_y/window.getSize().y,    lookat2[2]+move_object_z/1000.0, up2[0],   up2[1], up2[2]); }
            else {                   gluLookAt( eye2[0]+move_object_x/window.getSize().x,       eye2[1]+move_object_y/window.getSize().y,       eye2[2]+move_object_z/1000.0,lookat2[0]+move_object_x/window.getSize().x,    lookat2[1]+move_object_y/window.getSize().y,    lookat2[2]+move_object_z/1000.0, up2[0],   up2[1], up2[2]); }
            glMatrixMode(GL_MODELVIEW);  glLoadIdentity();
/*
            glm::mat4 test(1.0f);
            glm::mat4 rot_matrix2;
            build_rotmatrix_glm(rot_matrix2, curr_quat2);
            glm::mat4 adapt;
            adapt = rot_matrix2 * test;
*/
            glMultMatrixf((float*)&adapt);
            glScalef(1.0f / maxExtent, 1.0f / maxExtent, 1.0f / maxExtent); glTranslatef(translation[0] ,translation[1] ,  translation[2]);
            int hits=0;
            glm::vec3 colorf;
            int yp1;
            for (int m=0; m<do_size; m++) {
                xp=pos[m].x; yp=pos[m].y;
                yp1=yp/256;
                yp=yp-yp1*256;
                colorf.x=(float)(xp)/255.0;
                colorf.y=(float)(yp)/255.0;
                colorf.z=(float)(yp1)/255.0;
                Draw_one_shape(Pacman_Objects[win_num][0].gDrawObjects, Pacman_Objects[win_num][0].materials, Pacman_Objects[win_num][0].textures, m,
                               colorf);
            }

            window.setActive(false);
//            window.draw(sprite_shit);
            window.display();
            if (x_o>-1) {
                texture1_local.update(window);
                frustum_count_x=x_o;
                frustum_count_y=y_o;

                image_test=texture1_local.copyToImage();

//                char naam[2000];
//                mkdir("../Models/analyse");
//                sprintf(naam,"../Models/analyse/picture.%06d.%06d.png",(frustum_count_y),(frustum_count_x));
//                image_test.saveToFile(naam);

                while (window.pollEvent(event));

                int count=0;
                int count2=0;
                for (int y=0; y<1080; y++) {
                    for (int x=0; x<1920; x++) {
                        pixel_test=image_test.getPixel(x,y);
//joehoe
                        if (pixel_test.a>0) {
                            count2++;
//                            int m=(int)(pixel_test.r/2)-1+127*((int)(pixel_test.g/2)-1);
//                            int m=pixel_test.r+256*pixel_test.g;
//                            xp=pos[m].x; yp=pos[m].y;
                            xp=pixel_test.r;
                            yp=pixel_test.g;
                            int yp1;
                            yp1=pixel_test.b;
//                            yp1=255-pixel_test.b;
                            yp=yp+yp1*256;
//                            xp=xp-1;
//                            yp=yp-1;
//                            if (yp>255) printf("map[%d][%d]=%d\n",xp,yp,map[xp][yp]);

//                            if (xp>=xp_min && xp<=xp_max && yp>=yp_min && yp<=yp_max) {
                                if (map[xp][yp]>=0) {
    //                                printf("\nreceived: red=%d green=%d\n",(int)pixel_test.r,(int)pixel_test.g);
                                    count++;
                                    map[xp][yp]=-10-map[xp][yp];
                                    if (count==1) printf("\r#objects=%d frustum X=%02d,Y=%02d Found: ",do_size,frustum_count_x,frustum_count_y);
                                    printf("#%4d(%2d,%2d) ",-map[xp][yp]-10,xp,yp);
                                    fprintf(frustum_file,"FRUSTUM_X=%d FRUSTUM_Y=%d OBJECT_X=%d OBJECT_Y=%d OBJ=%s\n",
                                            frustum_count_x,frustum_count_y,xp,yp,get_area_data(my_area,xp,yp).c_str());


                                } else if (map[xp][yp]==-1) {
                                    printf("\n#objects=%d frustum X=%02d,Y=%02d ERROR(4): ",do_size,frustum_count_x,frustum_count_y);
                                    printf("#%d(%d,%d)\n",map[xp][yp],xp,yp);
//joehoe
                                    map[xp][yp]=-2;
                                }
//                            } else {
//                                printf("\nERROR(5): #objects=%d frustum X=%02d,Y=%02d ERROR: ",do_size,frustum_count_x,frustum_count_y);
//                                printf("#%d(%d,%d)\n",-map[xp][yp]-10,xp,yp);
//                            }
                        }
                    }
                }
                if (count>0) printf("Total=%d  Pixels=%f%%\n",count,(float)count2*100.0/(1920.0*1080.0));
                else printf("Nothing: FRUSTUM_X=%d FRUSTUM_Y=%d\n",frustum_count_x,frustum_count_y);
                for (int y=yp_min; y<=yp_max; y++) {
                    for (int x=xp_min; x<=xp_max; x++) {
                        if (xp>=xp_min && xp<=xp_max && yp>=yp_min && yp<=yp_max) map[x][y]=-1;
                        else map[x][y]=-2;
                    }
                }
                for (int m=0; m<do_size; m++) {
                    if (m<pos.size()) {
                        xp=pos[m].x; yp=pos[m].y;
                        if (xp>=xp_min && xp<=xp_max && yp>=yp_min && yp<=yp_max)
                            map[xp][yp]=m;
                        else
                            printf("\nError(6): Object# %d pos x=%d, pos y=%d\n",m,xp,yp);
                    } else {
                        printf("\nError(7): Object# %d pos x=%d, pos y=%d\n",m,xp,yp);
                    }
                }
            }
            x_o=x;
            y_o=y;
            if (frustum_count_x==frustum_size_y-1 && frustum_count_y==frustum_size_x-1) {ending=1; break; }
//            printf("");

//            sf::sleep(sf::milliseconds(10000.0/60.0));

//            if (is_active) { window.setActive(false); is_active=false; }

//            window.display();
//            printf("frustum x=%d y=%d\n",x,y);
//            sf::sleep(sf::milliseconds(100));
        }
        if (ending==1) {break; }
    }
    fclose(frustum_file);
    printf("\n");
    glLineWidth(1.0);
    COLOR_ARRAY=true;
    TEXTURE_ARRAY=true;
    WIRE_FRAME=false;
    remember_911=false;
    window.setActive(true);
    sf::Shader::bind(NULL);
    window.setActive(false);
//    window.setVerticalSyncEnabled(true);
}

extern double found_lat;
extern double found_lon;
extern bool lat_lon_found;

glm::ivec2 get_lat_lon(std::string my_area) {
    on_hold=true;
    FILE* file;
    bool lat_found=false;
    bool lon_found=false;
    int y=0;
    int x=0;

    double lat_north=0.0;
    double lat_south=0.0;
    double lon_west=0.0;
    double lon_east=0.0;
    double lat=0.0;
    double lon=0.0;

    if ( (file=fopen("lat_lon.txt","r"))!=NULL) {
        char line[2000];
        if (fgets (line,2000, file)!=NULL ) {
            fclose(file);
//decimal_point
                        while (replace_str(line,",","."));
//            while (replace_str(line,".",","));
            char rest[999]="";
            char rest2[999]="";
            int num=sscanf(line,"LAT=%lf LON=%lf %999[^\n]", &lat, &lon, rest);
            if (num<2) {
                num=sscanf(line,"%999[^\@]@%lf\,%lf\,%999[^\n]",rest, &lat, &lon, rest2);
                if (num==4) num=2;
                printf("lat=%f lon=%f rest=%s rest2=%s\n",lat,lon,rest,rest2);
            } else {
                if (num==2) printf("lat=%f lon=%f\n",lat,lon);
                else printf("lat=%f lon=%f rest=%s\n",lat,lon,rest);
                if (num==3) num=2;
            }
            int max_x=-1; int max_y=-1;
            if (num==2) {
                get_area_data(my_area,max_x,max_y);
                x=max_x/2;
                for (y=0; y<max_y; y++) {
                    get_area_quick=true;
                    get_area_data(my_area,x,y);
                    get_area_quick=false;
                    strcpy(line,latitude_longditude.c_str());
//decimal_point
                        while (replace_str(line,",","."));
//                    while (replace_str(line,".",","));
                    int num=sscanf(line,"N=%lf S=%lf W=%lf E=%lf", &lat_north, &lat_south, &lon_west, &lon_east);
                    if (num==4 && lat>=lat_south && lat<=lat_north) {
                        printf("FOUND!!!! LAT: LAT=%lf LON=%lf Testing: N=%lf S=%lf W=%lf E=%lf\n",lat,lon, lat_north, lat_south, lon_west, lon_east);
                        lat_found=true;
                        break;
                    } else {
    //                    printf("Searching LAT: LAT=%lf LON=%lf Testing: N=%lf S=%lf W=%lf E=%lf\n",lat,lon, lat_north, lat_south, lon_west, lon_east);
                    }
                }
            }
            if (lat_found) {
                for (x=0; x<max_x; x++) {
                    get_area_quick=true;
                    get_area_data(my_area,x,y);
                    get_area_quick=false;
                    strcpy(line,latitude_longditude.c_str());
//decimal_point
                        while (replace_str(line,",","."));
//                    while (replace_str(line,".",","));
                    int num=sscanf(line,"N=%lf S=%lf W=%lf E=%lf", &lat_north, &lat_south, &lon_west, &lon_east);
                    if (num==4 && lon>=lon_west && lon<=lon_east) {
                        printf("\nFOUND!!!! LON: LAT=%lf LON=%lf Testing: N=%lf S=%lf W=%lf E=%lf\n",lat,lon, lat_north, lat_south, lon_west, lon_east);
                        lon_found=true;
                        break;
                    } else {
//                        printf("Searching LON: LAT=%lf LON=%lf Testing: N=%lf S=%lf W=%lf E=%lf\n",lat,lon, lat_north, lat_south, lon_west, lon_east);
                    }
                }
            } else {
                printf("\nLat not found: LAT=%lf\n",lat,lon);
            }
        } else fclose(file);
    }
    if (lat_found && lon_found) {

        printf("\nFound: X=%d,Y=%d %s ",x,y,get_area_data(my_area,x,y).c_str());

        char lat_str[100];
        char lon_str[100];
//        sprintf(lat_str,"%lf",(lat_north+lat_south)/2.0); while (replace_str(lat_str,",","."));
//        sprintf(lon_str,"%lf",(lon_east+lon_west)/2.0); while (replace_str(lon_str,",","."));
        sprintf(lat_str,"%lf",lat); while (replace_str(lat_str,",","."));
        sprintf(lon_str,"%lf",lon); while (replace_str(lon_str,",","."));
        printf("\nhttps://www.google.com/maps/@%s,%s,17.00z\n",lat_str,lon_str);
        found_lat=lat;
        found_lon=lon;
        lat_lon_found=true;
        return glm::ivec2(x,y);
    }
    else {
        if (my_area!="Models" && my_area!="Canvas") printf("\nNot found: LAT=%lf LON=%lf\n",lat,lon);
        return glm::ivec2(999.0,999.0);
    }
}

glm::ivec2 GET_LAT_LON2(std::string my_area) {
    on_hold=true;
    FILE* file;
    bool lat_found=false;
    bool lon_found=false;
    int y=0;
    int x=0;

    double lat_north=0.0;
    double lat_south=0.0;
    double lon_west=0.0;
    double lon_east=0.0;
    double lat=0.0;
    double lon=0.0;

    char line[2000]="";
    int ret=GET_LAT_LON_FROM_FILE_LIST(line);
    printf("Got %d : %s from ../LAT_LON/list.txt\n",ret,line);
    if ( ret!=0) {
        if (strlen(line)!=0 ) {
//decimal_point
                        while (replace_str(line,",","."));
//            while (replace_str(line,".",","));
            char rest[999]="";
            char rest2[999]="";
            int num=sscanf(line,"LAT=%lf LON=%lf %999[^\n]", &lat, &lon, rest);
            if (num<2) {
                num=sscanf(line,"%999[^\@]@%lf\,%lf\,%999[^\n]",rest, &lat, &lon, rest2);
                if (num==4) num=2;
                printf("lat=%f lon=%f rest=%s rest2=%s\n",lat,lon,rest,rest2);
            } else {
                if (num==2) printf("lat=%f lon=%f\n",lat,lon);
                else printf("lat=%f lon=%f rest=%s\n",lat,lon,rest);
                if (num==3) num=2;
            }
            int max_x=-1; int max_y=-1;
            if (num==2) {
                get_area_data(my_area,max_x,max_y);
                x=max_x/2;
                for (y=0; y<max_y; y++) {
                    get_area_quick=true;
                    get_area_data(my_area,x,y);
                    get_area_quick=false;
                    strcpy(line,latitude_longditude.c_str());
//decimal_point
                        while (replace_str(line,",","."));
//                    while (replace_str(line,".",","));
                    int num=sscanf(line,"N=%lf S=%lf W=%lf E=%lf", &lat_north, &lat_south, &lon_west, &lon_east);
                    if (num==4 && lat>=lat_south && lat<=lat_north) {
                        printf("FOUND!!!! LAT: LAT=%lf LON=%lf Testing: N=%lf S=%lf W=%lf E=%lf\n",lat,lon, lat_north, lat_south, lon_west, lon_east);
                        lat_found=true;
                        break;
                    } else {
    //                    printf("Searching LAT: LAT=%lf LON=%lf Testing: N=%lf S=%lf W=%lf E=%lf\n",lat,lon, lat_north, lat_south, lon_west, lon_east);
                    }
                }
            }
            if (lat_found) {
                for (x=0; x<max_x; x++) {
                    get_area_quick=true;
                    get_area_data(my_area,x,y);
                    get_area_quick=false;
                    strcpy(line,latitude_longditude.c_str());
//decimal_point
                        while (replace_str(line,",","."));
//                    while (replace_str(line,".",","));
                    int num=sscanf(line,"N=%lf S=%lf W=%lf E=%lf", &lat_north, &lat_south, &lon_west, &lon_east);
                    if (num==4 && lon>=lon_west && lon<=lon_east) {
                        printf("FOUND!!!! LON: LAT=%lf LON=%lf Testing: N=%lf S=%lf W=%lf E=%lf\n",lat,lon, lat_north, lat_south, lon_west, lon_east);
                        lon_found=true;
                        break;
                    } else {
//                        printf("Searching LON: LAT=%lf LON=%lf Testing: N=%lf S=%lf W=%lf E=%lf\n",lat,lon, lat_north, lat_south, lon_west, lon_east);
                    }
                }
            } else {
                printf("\nLat not found: LAT=%lf\n",lat,lon);
            }
        } else fclose(file);
    }
    if (lat_found && lon_found) {

        printf("Found: X=%d,Y=%d %s ",x,y,get_area_data(my_area,x,y).c_str());

        char lat_str[100];
        char lon_str[100];
//        sprintf(lat_str,"%lf",(lat_north+lat_south)/2.0); while (replace_str(lat_str,",","."));
//        sprintf(lon_str,"%lf",(lon_east+lon_west)/2.0); while (replace_str(lon_str,",","."));
        sprintf(lat_str,"%lf",lat); while (replace_str(lat_str,",","."));
        sprintf(lon_str,"%lf",lon); while (replace_str(lon_str,",","."));
        printf("https://www.google.com/maps/@%s,%s,17.00z\n",lat_str,lon_str);
        found_lat=lat;
        found_lon=lon;
        lat_lon_found=true;
        return glm::ivec2(x,y);
    } else {
        printf("\nNot found: LAT=%lf LON=%lf\n",lat,lon);
        return glm::ivec2(999.0,999.0);
    }
}

//    lat_north=0.0;
//    lat_south=0.0;
//    lon_west=0.0;
//    lon_east=0.0;

glm::ivec2 GET_LAT_LON3(std::string my_area, double lat, double lon) {
    on_hold=true;
    FILE* file;
    bool lat_found=false;
    bool lon_found=false;
    int y=0;
    int x=0;

    lat_north=0.0;
    lat_south=0.0;
    lon_west=0.0;
    lon_east=0.0;

    char line[2000]="";
    int ret=1;
    printf("Got : lat=%f , lon=%f\n",lat,lon);
    sprintf(line,"LAT=%f LON=%f\n",lat,lon);
    if ( ret!=0) {
        if (strlen(line)!=0 ) {
//decimal_point
            while (replace_str(line,",","."));
//            while (replace_str(line,".",","));
            char rest[999]="";
            char rest2[999]="";
            int num=sscanf(line,"LAT=%lf LON=%lf %999[^\n]", &lat, &lon, rest);
            if (num<2) {
                num=sscanf(line,"%999[^\@]@%lf\,%lf\,%999[^\n]",rest, &lat, &lon, rest2);
                if (num==4) num=2;
                printf("lat=%f lon=%f rest=%s rest2=%s\n",lat,lon,rest,rest2);
            } else {
                if (num==2) printf("lat=%f lon=%f\n",lat,lon);
                else printf("lat=%f lon=%f rest=%s\n",lat,lon,rest);
                if (num==3) num=2;
            }
            int max_x=-1; int max_y=-1;
            if (num==2) {
                get_area_data(my_area,max_x,max_y);
                x=max_x/2;
                for (y=0; y<max_y; y++) {
                    get_area_quick=true;
                    get_area_data(my_area,x,y);
                    get_area_quick=false;
                    strcpy(line,latitude_longditude.c_str());
//decimal_point
                        while (replace_str(line,",","."));
//                    while (replace_str(line,".",","));
                    int num=sscanf(line,"N=%lf S=%lf W=%lf E=%lf", &lat_north, &lat_south, &lon_west, &lon_east);
                    if (num==4 && lat>=lat_south && lat<=lat_north) {
                        printf("FOUND!!!! LAT: LAT=%lf LON=%lf Testing: N=%lf S=%lf W=%lf E=%lf\n",lat,lon, lat_north, lat_south, lon_west, lon_east);
                        lat_found=true;
                        break;
                    } else {
    //                    printf("Searching LAT: LAT=%lf LON=%lf Testing: N=%lf S=%lf W=%lf E=%lf\n",lat,lon, lat_north, lat_south, lon_west, lon_east);
                    }
                }
            }
            if (lat_found) {
                for (x=0; x<max_x; x++) {
                    get_area_quick=true;
                    get_area_data(my_area,x,y);
                    get_area_quick=false;
                    strcpy(line,latitude_longditude.c_str());
//decimal_point
                        while (replace_str(line,",","."));
//                    while (replace_str(line,".",","));
                    int num=sscanf(line,"N=%lf S=%lf W=%lf E=%lf", &lat_north, &lat_south, &lon_west, &lon_east);
                    if (num==4 && lon>=lon_west && lon<=lon_east) {
                        printf("FOUND!!!! LON: LAT=%lf LON=%lf Testing: N=%lf S=%lf W=%lf E=%lf\n",lat,lon, lat_north, lat_south, lon_west, lon_east);
                        lon_found=true;
                        break;
                    } else {
//                        printf("Searching LON: LAT=%lf LON=%lf Testing: N=%lf S=%lf W=%lf E=%lf\n",lat,lon, lat_north, lat_south, lon_west, lon_east);
                    }
                }
            } else {
                printf("\nLat not found: LAT=%lf\n",lat,lon);
            }
        } else fclose(file);
    }
    if (lat_found && lon_found) {

        printf("Found: X=%d,Y=%d %s ",x,y,get_area_data(my_area,x,y).c_str());

        char lat_str[100];
        char lon_str[100];
//        sprintf(lat_str,"%lf",(lat_north+lat_south)/2.0); while (replace_str(lat_str,",","."));
//        sprintf(lon_str,"%lf",(lon_east+lon_west)/2.0); while (replace_str(lon_str,",","."));
        sprintf(lat_str,"%lf",lat); while (replace_str(lat_str,",","."));
        sprintf(lon_str,"%lf",lon); while (replace_str(lon_str,",","."));
        printf("https://www.google.com/maps/@%s,%s,17.00z\n",lat_str,lon_str);
        found_lat=lat;
        found_lon=lon;
        lat_lon_found=true;
        return glm::ivec2(x,y);
    }
    else {
        if (my_area!="Models" && my_area!="Canvas") printf("\nNot found: LAT=%lf LON=%lf\n",lat,lon);
        return glm::ivec2(999.0,999.0);
    }
}

bool plot_quick_func(double& lat, double& lon, std::string& my_area, int win_num, sf::RenderWindow& window, float eye2[3],
                       float perspective[4],int frustum_toggle, float maxExtent,
                       float lookat2[3], float up2[3], float move_object_x, float move_object_y, float move_object_z,
                       float translation[3],float curr_quat2[4], float bmin[3], float bmax[3]) {

    static int counter=60;
    if (burn) remember_911_2=true;

    window.setActive(true);

    glDepthMask(GL_TRUE);
    glClearDepth(1.f);

    glClearColor(0.7,0.8,1.0,0);

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);

    static glm::vec3 move_object;
    static glm::vec3 add_xyz;
    move_object = glm::vec3(move_object_x, move_object_y, move_object_z);
    add_xyz = glm::vec3(0.0, 0.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    make_lookat( perspective, frustum_toggle, eye2, lookat2, up2, move_object, window.getSize(), true, maxExtent);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glm::mat4 test(1.0f);

    rotate_around_point( move_object, add_xyz, my_area, lat, lon, true, interpolate_on, rot_mat, test, curr_quat2, maxExtent, bmin, bmax);

    glScalef(1.0f / maxExtent, 1.0f / maxExtent, 1.0f / maxExtent);

    if ( !(interpolate_on  || burn) ) {
        translation[0]=-0.5 * (bmax[0] + bmin[0])+add_xyz.x;
        translation[1]=-0.5 * (bmax[1] + bmin[1])+add_xyz.y;
        translation[2]=-0.5 * (bmax[2] + bmin[2])+add_xyz.z;
    }
    glTranslatef(translation[0] ,translation[1] ,  translation[2]);

    if (smooth)
        glShadeModel(GL_SMOOTH);
    else
        glShadeModel(GL_FLAT);

    for (auto u : Pacman_Objects[win_num]) Draw(u.gDrawObjects, u.materials, u.textures);
    window.setActive(false);
//    window.display();
}

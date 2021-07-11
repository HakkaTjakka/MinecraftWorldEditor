
float playbackspeed=0.015;

FILE* movement_file=NULL;
extern int extra_octants;
//extern bool show_text;
extern int GET_LAT_LON_FROM_FILE_LIST(char *naam);

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




struct info_3d_struct {
    glm::ivec2 pos;
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
            double dist=sqrt( (lat-center_lat)*(lat-center_lat) + (lon-center_lon)*(lon-center_lon) );
            double Bdist=sqrt( (B.lat-center_lat)*(B.lat-center_lat) + (B.lon-center_lon)*(B.lon-center_lon) );
            return( dist < Bdist );
        } else {
/*
            double s = sin(0.01);
            double c = cos(0.01);
            double x1=(pos.x-center_x)*1.23;
            double y1=(pos.y-center_y);
            double x2=(B.pos.x-center_x)*1.23;
            double y2=(B.pos.y-center_y);
            double x1_new = x1 * c - y1 * s;
            double y1_new = x1 * s + y1 * c;
            double x2_new = x2 * c - y2 * s;
            double y2_new = x2 * s + y2 * c;
//            double d1=std::min(fabs(x1_new),fabs(y1_new));
//            double d2=std::min(fabs(x2_new),fabs(y2_new));
            double d1=std::max(fabs(x1_new),fabs(y1_new));
            double d2=std::max(fabs(x2_new),fabs(y2_new));
//            double d1=fabs(x1_new)+fabs(y1_new);
//            double d2=fabs(x2_new)+fabs(y2_new);
            return ( d1 < d2 );

//            double dist    = fabs(  pos.x-center_x)*320.0/412.0   + fabs(  pos.y-center_y);
//            double Bdist   = fabs(B.pos.x-center_x)*320.0/412.0   + fabs(B.pos.y-center_y);
//            return( dist < Bdist );
*/
            double dist=sqrt( (pos.x-center_x)*(pos.x-center_x)*1.23 +(pos.y-center_y)*(pos.y-center_y) );
            double Bdist=sqrt( (B.pos.x-center_x)*(B.pos.x-center_x)*1.23 + (B.pos.y-center_y)*(B.pos.y-center_y) );
            return( dist < Bdist );
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

                if (my_area=="Utrecht") {
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
    if ((file_arr = fopen ("OBJECT_ARRAY.TXT", "r"))!=NULL) {
//    if (0 && (file_arr = fopen ("OBJECT_ARRAY.TXT", "r"))!=NULL) {
        printf("OBJECT_ARRAY.TXT detected. Loading object array data...\n");
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
//                    printf("N=%lf S=%lf W=%lf E=%lf\n", lat_north, lat_south, lon_west, lon_east);

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
                printf("#%3d FOUND: X=%3d Y=%3d %s (EXTRA)  ",cnt,max_x,y,str.c_str());
                info_3d_elem.filename=str;
                info_3d_elem.pos=glm::ivec2(max_x,y);

                std::string to_test=extra_octants_belong_to_string_pointer[y];
                char octant[100];
                int xx,yy;
                int num=sscanf(to_test.c_str(),"%100[^ ] X=%d Y=%d", octant, &xx, &yy);
                if (num==3) {
                    info_3d_elem.pos=glm::ivec2(xx,yy);
                    printf("Relocating octant %s (%d,%d) to (%d,%d)\n",to_test.c_str(),max_x,y,xx,yy);
                } else {
                    printf("Can not relocate (%d,%d) to \"%s\"\n",max_x,y,to_test.c_str());
                }

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
//                    printf("N=%f S=%f W=%f E=%f\n", &lat_north, &lat_south, &lon_west, &lon_east);
                }
                info_3d_elem.lat=(lat_north+lat_south)/2.0;
                info_3d_elem.lon=(lon_east+lon_west)/2.0;
                info_3d_elem.n=lat_north;
                info_3d_elem.s=lat_south;
                info_3d_elem.e=lon_east;
                info_3d_elem.w=lon_west;

                printf("N=%20.16f S=%20.16f W=%20.16f E=%20.16f\n", lat_north, lat_south, lon_west, lon_east);
//                printf("N=%lf S=%lf W=%lf E=%lf\n", lat_north, lat_south, lon_west, lon_east);

                info_3d.push_back(info_3d_elem);
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
    sort_lat_lon=false;

    cnt=0;
    for (auto v : info_3d) {
        if (crossing>0) {
//utrecht
            v.filename=get_area_data(my_area,v.pos.x,v.pos.y); //update when moved...

            std::string fn = v.filename;

            fn=GetFileName(fn.substr(0,fn.find_last_of(".")));

            char new_file_raw[100];
            char new_file_dat[100];

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

        burn=true;
        window.setActive(true);
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

            if (crossing==2 && mirror==4) to_gpu=false;
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
                if (crossing>0) {
                    voxel_to_file=true;
                }
//                window.setActive(false);
//                nbt_creating=false;
//                return true;
            }
            if (crossing==2 && mirror==4) to_gpu=true;

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
            {

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
                for (y=0; y<max_y; y++) {
                    get_area_data(my_area,x,y);
                    strcpy(line,latitude_longditude.c_str());
//decimal_point
                        while (replace_str(line,",","."));
//                    while (replace_str(line,".",","));
                    int num=sscanf(line,"N=%lf S=%lf W=%lf E=%lf", &lat_north, &lat_south, &lon_west, &lon_east);
                    if (num==4 && lat>=lat_south && lat<=lat_north) {
    //                    printf("FOUND!!!! LAT: LAT=%lf LON=%lf Testing: N=%lf S=%lf W=%lf E=%lf\n",lat,lon, lat_north, lat_south, lon_west, lon_east);
                        lat_found=true;
                        break;
                    } else {
    //                    printf("Searching LAT: LAT=%lf LON=%lf Testing: N=%lf S=%lf W=%lf E=%lf\n",lat,lon, lat_north, lat_south, lon_west, lon_east);
                    }
                }
            }
            if (lat_found) {
                for (x=0; x<max_x; x++) {
                    get_area_data(my_area,x,y);
                    strcpy(line,latitude_longditude.c_str());
//decimal_point
                        while (replace_str(line,",","."));
//                    while (replace_str(line,".",","));
                    int num=sscanf(line,"N=%lf S=%lf W=%lf E=%lf", &lat_north, &lat_south, &lon_west, &lon_east);
                    if (num==4 && lon>=lon_west && lon<=lon_east) {
//                        printf("FOUND!!!! LON: LAT=%lf LON=%lf Testing: N=%lf S=%lf W=%lf E=%lf\n",lat,lon, lat_north, lat_south, lon_west, lon_east);
                        lon_found=true;
                        break;
                    } else {
//                        printf("Searching LON: LAT=%lf LON=%lf Testing: N=%lf S=%lf W=%lf E=%lf\n",lat,lon, lat_north, lat_south, lon_west, lon_east);
                    }
                }
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
        if (my_area!="Models" && my_area!="Canvas") printf("Not found: LAT=%lf LON=%lf\n",lat,lon);
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
                for (y=0; y<max_y; y++) {
                    get_area_data(my_area,x,y);
                    strcpy(line,latitude_longditude.c_str());
//decimal_point
                        while (replace_str(line,",","."));
//                    while (replace_str(line,".",","));
                    int num=sscanf(line,"N=%lf S=%lf W=%lf E=%lf", &lat_north, &lat_south, &lon_west, &lon_east);
                    if (num==4 && lat>=lat_south && lat<=lat_north) {
    //                    printf("FOUND!!!! LAT: LAT=%lf LON=%lf Testing: N=%lf S=%lf W=%lf E=%lf\n",lat,lon, lat_north, lat_south, lon_west, lon_east);
                        lat_found=true;
                        break;
                    } else {
    //                    printf("Searching LAT: LAT=%lf LON=%lf Testing: N=%lf S=%lf W=%lf E=%lf\n",lat,lon, lat_north, lat_south, lon_west, lon_east);
                    }
                }
            }
            if (lat_found) {
                for (x=0; x<max_x; x++) {
                    get_area_data(my_area,x,y);
                    strcpy(line,latitude_longditude.c_str());
//decimal_point
                        while (replace_str(line,",","."));
//                    while (replace_str(line,".",","));
                    int num=sscanf(line,"N=%lf S=%lf W=%lf E=%lf", &lat_north, &lat_south, &lon_west, &lon_east);
                    if (num==4 && lon>=lon_west && lon<=lon_east) {
//                        printf("FOUND!!!! LON: LAT=%lf LON=%lf Testing: N=%lf S=%lf W=%lf E=%lf\n",lat,lon, lat_north, lat_south, lon_west, lon_east);
                        lon_found=true;
                        break;
                    } else {
//                        printf("Searching LON: LAT=%lf LON=%lf Testing: N=%lf S=%lf W=%lf E=%lf\n",lat,lon, lat_north, lat_south, lon_west, lon_east);
                    }
                }
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
        printf("Not found: LAT=%lf LON=%lf\n",lat,lon);
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
                for (y=0; y<max_y; y++) {
                    get_area_data(my_area,x,y);
                    strcpy(line,latitude_longditude.c_str());
//decimal_point
                        while (replace_str(line,",","."));
//                    while (replace_str(line,".",","));
                    int num=sscanf(line,"N=%lf S=%lf W=%lf E=%lf", &lat_north, &lat_south, &lon_west, &lon_east);
                    if (num==4 && lat>=lat_south && lat<=lat_north) {
    //                    printf("FOUND!!!! LAT: LAT=%lf LON=%lf Testing: N=%lf S=%lf W=%lf E=%lf\n",lat,lon, lat_north, lat_south, lon_west, lon_east);
                        lat_found=true;
                        break;
                    } else {
    //                    printf("Searching LAT: LAT=%lf LON=%lf Testing: N=%lf S=%lf W=%lf E=%lf\n",lat,lon, lat_north, lat_south, lon_west, lon_east);
                    }
                }
            }
            if (lat_found) {
                for (x=0; x<max_x; x++) {
                    get_area_data(my_area,x,y);
                    strcpy(line,latitude_longditude.c_str());
//decimal_point
                        while (replace_str(line,",","."));
//                    while (replace_str(line,".",","));
                    int num=sscanf(line,"N=%lf S=%lf W=%lf E=%lf", &lat_north, &lat_south, &lon_west, &lon_east);
                    if (num==4 && lon>=lon_west && lon<=lon_east) {
//                        printf("FOUND!!!! LON: LAT=%lf LON=%lf Testing: N=%lf S=%lf W=%lf E=%lf\n",lat,lon, lat_north, lat_south, lon_west, lon_east);
                        lon_found=true;
                        break;
                    } else {
//                        printf("Searching LON: LAT=%lf LON=%lf Testing: N=%lf S=%lf W=%lf E=%lf\n",lat,lon, lat_north, lat_south, lon_west, lon_east);
                    }
                }
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
        if (my_area!="Models" && my_area!="Canvas") printf("Not found: LAT=%lf LON=%lf\n",lat,lon);
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

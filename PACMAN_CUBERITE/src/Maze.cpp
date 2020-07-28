#define SFML_STATIC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <fcntl.h>
#include <iostream>

extern int movex1;
extern int movex2;
extern int movey1;
extern int movey2;
extern int monitor_off;

int print_mime = 1;
int solve = 0;
int html = 0;

#define GIF_GREY 0xcc

#define GO_LEFT		1
#define GO_RIGHT	2
#define GO_UP		4
#define GO_DOWN		8
#define USED		16
#define SOLUTION	32
#define BLOCKED 	64

#define M(x,y) maze_data[(x)+1+((y)+1)*(c+2)]

extern int combine;
extern char **Maze;
extern char **Maze2;
extern char **maze_plot;
extern int maze_plotsizex;
extern int maze_plotsizey;

void gen_maze(int gif, int c, int r, int w, int h, int s) {
	char *maze_data;

	int arx=1;
	int ary=1;

	int x, y;
	int *xt, *yt;

	if (c < 1 || r < 1 || w < 1 || h < 1)
		return;

	maze_data = (char *)calloc(r+2, c+2);
	xt = (int *)malloc(c*r*sizeof(int));
	yt = (int *)malloc(c*r*sizeof(int));

	for (x=0; x<c; x++)
		for (y=0; y<r; y++) {
			xt[x+y*c] = x;
			yt[x+y*c] = y;
		}

//	if (combine==0) {
        for (x=-1; x<=c; x++) {
            M(x, -1) = USED;
            M(x, r) = USED;
        }
//	}
	for (y=0; y<=r; y++) {
		M(-1, y) = USED;
		M(c, y) = USED;
	}

    M(-1,0) |= USED | GO_RIGHT;
	M(0,0) |= USED | GO_LEFT;

	if (combine==1) {
	}

	int num_left = r*c-1;

    if (combine==1) {
        for (x=0; x<=c; x++) {
            for (y=0; y<=r; y++) {
                if (!(M(x, y) & USED)) {
                    if ( ((-59+maze_plotsizex+y)%maze_plotsizex)==movex1 && ((-30+maze_plotsizey+x)%maze_plotsizey)==movey1) {
                        M(x-1,y) |= USED | GO_RIGHT;
                        M(x,y) |= USED | GO_LEFT;
                    } else if ( ((-59+maze_plotsizex+y)%maze_plotsizex)==movex2 && ((-30+maze_plotsizey+x)%maze_plotsizey)==movey2) {
                        M(x,y-1) |= USED | GO_LEFT;
                        M(x-1,y-1) |= USED | GO_RIGHT;
                    }
                    if ((maze_plot[(-59+maze_plotsizex+y)%maze_plotsizex][(-30+maze_plotsizey+x)%maze_plotsizey]&15)==0) {
                        M(x,y) |= USED;
                        M(x,y) |= BLOCKED;
                        num_left--;
/*
                        if (maze_plot[(-59+maze_plotsizex+y)%maze_plotsizex][(-30+maze_plotsizey+x)%maze_plotsizey]&1) M(x,y) |= GO_LEFT;
                        if (maze_plot[(-59+maze_plotsizex+y)%maze_plotsizex][(-30+maze_plotsizey+x)%maze_plotsizey]&2) M(x,y) |= GO_RIGHT;
                        if (maze_plot[(-59+maze_plotsizex+y)%maze_plotsizex][(-30+maze_plotsizey+x)%maze_plotsizey]&4) M(x,y) |= GO_UP;
                        if (maze_plot[(-59+maze_plotsizex+y)%maze_plotsizex][(-30+maze_plotsizey+x)%maze_plotsizey]&8) M(x,y) |= GO_DOWN;
*/
                    }
                }
                maze_plot[(-59+maze_plotsizex+y)%maze_plotsizex][(-30+maze_plotsizey+x)%maze_plotsizey]=0;
            }
        }
    }
/*
	for (y=0; y<maze_plotsizey; y++) {
        for (x=0; x<maze_plotsizex; x++) {
            if (!(M(y, x) & USED)) {
                if ((maze_plot[(-59+maze_plotsizex+x)%maze_plotsizex][(-30+maze_plotsizey+y)%maze_plotsizey]&15)>0) {
                    M(y,x) |= USED;
                    num_left--;
                }
            }
        }
	}
*/

/*
	for (y=0; y<maze_plotsizey; y++) {
        for (x=0; x<maze_plotsizex; x++) {
            if (x!=0 || y!=0) {
                if ((maze_plot[(-59+maze_plotsizex+x)%maze_plotsizex][(-30+maze_plotsizey+y)%maze_plotsizey]&1)>0) M(y,x) |= GO_LEFT;
                if ((maze_plot[(-59+maze_plotsizex+x)%maze_plotsizex][(-30+maze_plotsizey+y)%maze_plotsizey]&2)>0) M(y,x) |= GO_RIGHT;
                if ((maze_plot[(-59+maze_plotsizex+x)%maze_plotsizex][(-30+maze_plotsizey+y)%maze_plotsizey]&4)>0) M(y,x) |= GO_UP;
                if ((maze_plot[(-59+maze_plotsizex+x)%maze_plotsizex][(-30+maze_plotsizey+y)%maze_plotsizey]&8)>0) M(y,x) |= GO_DOWN;
            }
        }
	}
*/


//    M(2,3) = USED;

	if (s == 0)
		s = time(0);
	srand(s);
//   srand((unsigned int)time(NULL));

    for (x=r*c-1; x>0; x--) {
//        y = rand() % (r*c);
        y = rand() % (x+1);
        if (y!=x ) {
            int t = xt[x];
            xt[x] = xt[y];
            xt[y] = t;
            t = yt[x];
            yt[x] = yt[y];
            yt[y] = t;
        }
    }


/*
	for (int xx=c-1; xx>=0; xx--)
		for (int yy=r-1; yy>=0; yy--) {
		    x=xx+yy*c;
            int yc=rand()%(xx+1);
            int yr=rand()%(yy+1);
            y=yc+yr*c;
//            y = rand() % (x+1);
            int px1 = xt[x];
			int py1 = yt[x];
            int px2 = xt[y];
			int py2 = yt[y];
            if ((M(px1, py1) & USED)) continue;
            if ((M(px2, py2) & USED)) continue;
            if (y!=x) {
                int t = xt[x];
                xt[x] = xt[y];
                xt[y] = t;
                t = yt[x];
                yt[x] = yt[y];
                yt[y] = t;
            }
		}
        y = rand() % (x+1);

*/



/*
    int count=r*c*20000;
    for (int p=count; p>0; p--) {
        x=rand()%(r*c);
        y=rand()%(r*c);
//        y = rand()%(x+1);
        if (y!=x ) {
            int t = xt[x];
            xt[x] = xt[y];
            xt[y] = t;
            t = yt[x];
            yt[x] = yt[y];
            yt[y] = t;
        }
    }
*/

    int old_num_left=num_left;
    int ways[20], wp;
extern void kiki();
extern void toggle();
	while (num_left) {
//		for (x=0; x<(c+combine); x++) {
//			for (y=0; y<(r+combine); y++) {
        monitor_off=1;
        kiki();
        toggle();
		for (x=0; x<c; x++) {
			for (y=0; y<r; y++) {
				while (1) {
					int px = xt[(x+y*c)%(r*c)];
					int py = yt[(x+y*c)%(r*c)];
//					int px = xt[x+y*c];
//					int py = yt[x+y*c];
//					if ((M(px, py) & BLOCKED))
					if (!(M(px, py) & USED) || (M(px, py) & BLOCKED))
						break;

					while (1) {
						wp = 0;
						if (!(M(px,py-1) & USED) && !(M(px,py-1) & BLOCKED)) {
                                ways[wp++] = GO_UP;
                                ways[wp++] = GO_UP;
						}

						if (!(M(px,py+1) & USED) && !(M(px,py+1) & BLOCKED)) {
//						if (!(M(px,py+1) & USED) && !(M(px,py+1) & BLOCKED)) {
                                ways[wp++] = GO_DOWN;
						}

						if (!(M(px-1,py) & USED) && !(M(px-1,py) & BLOCKED)) {
                                ways[wp++] = GO_LEFT;
                                ways[wp++] = GO_LEFT;
						}

						if (!(M(px+1,py) & USED) && !(M(px+1,py) & BLOCKED)) {
//						if (!(M(px+1,py) & USED) && !(M(px+1,py) & BLOCKED)) {
                                ways[wp++] = GO_RIGHT;
						}

						if (wp == 0) {
							break;		// blocked at this point
						}
                        wp = rand() % wp;

						switch (ways[wp]) {
							case GO_LEFT:
								M(px,py) |= GO_LEFT;
								px--;
								M(px,py) |= GO_RIGHT | USED;
								break;
							case GO_RIGHT:
								M(px,py) |= GO_RIGHT;
								px++;
								M(px,py) |= GO_LEFT | USED;
								break;
							case GO_UP:
								M(px,py) |= GO_UP;
								py--;
								M(px,py) |= GO_DOWN | USED;
								break;
							case GO_DOWN:
								M(px,py) |= GO_DOWN;
								py++;
								M(px,py) |= GO_UP | USED;
								break;
						}
						num_left--;
//                        if (combine==1)
//                            printf("num_left=%d\n",num_left);
					}
					if (px == xt[(x+y*c)%(r*c)] && py == yt[(x+y*c)%(r*c)])
						break;
				}
			}
		}
        if (num_left==old_num_left) break;
		old_num_left=num_left;
	}


	M(c,r-1) |= USED | GO_LEFT;
	M(c-1,r-1) |= USED | GO_RIGHT;

	if (solve) {
		for (x=0; x<c; x++)
			for (y=0; y<r; y++)
				M(x,y) |= SOLUTION;
		M(-1,0) |= SOLUTION;
		M(0,0) |= SOLUTION;
		M(c,r-1) |= SOLUTION;
		M(c-1,r-1) |= SOLUTION;

		for (x=0; x<c; x++)
			for (y=0; y<r; y++) {
				int px = x;
				int py = y;
				int ways[4], wp;

				while (1) {
					wp = 0;

					if (M(px,py) & GO_UP && M(px,py-1) & SOLUTION)
						ways[wp++] = GO_UP;
					if (M(px,py) & GO_DOWN && M(px,py+1) & SOLUTION)
						ways[wp++] = GO_DOWN;
					if (M(px,py) & GO_LEFT && M(px-1,py) & SOLUTION)
						ways[wp++] = GO_LEFT;
					if (M(px,py) & GO_RIGHT && M(px+1,py) & SOLUTION)
						ways[wp++] = GO_RIGHT;
					if (wp != 1)
						break;		// not a dead end

					switch (ways[0]) {
						case GO_LEFT:
							M(px,py) &= ~SOLUTION;
							px--;
							break;
						case GO_RIGHT:
							M(px,py) &= ~SOLUTION;
							px++;
							break;
						case GO_UP:
							M(px,py) &= ~SOLUTION;
							py--;
							break;
						case GO_DOWN:
							M(px,py) &= ~SOLUTION;
							py++;
							break;
					}
				}
			}
	}

	if (!gif) {
		int i;
		for (y=0; y<=r; y++) {
            monitor_off=1;
            kiki();
            toggle();
 			Maze[ary][arx]='#';
			arx++;
			//putchar('0');
//			for (x=0; x<(c+combine); x++) {
			for (x=0; x<c; x++) {
				if (M(x,y) & GO_UP || x==-1)
					for (i=1; i<w; i++) {
						//putchar((M(x,y)&SOLUTION && M(x,y-1)&SOLUTION) ? '0' : ' ');
						Maze[ary][arx]=((M(x,y)&SOLUTION && M(x,y-1)&SOLUTION) ? '#' : ' ');
						arx++;
					}

				else
					for (i=1; i<w; i++) {
						//putchar('0');
						Maze[ary][arx]='#';
						arx++;
					}
				Maze[ary][arx]='#';
				arx++;
				//printf("0");
			}
			arx=1;
			ary++;
			//printf("\n");
//			if (y<(r+combine))
			if (y<r)
				for (int dy=1; dy<h; dy++) {
					if (M(0,y) & GO_LEFT) {
						//putchar((M(0,y)&SOLUTION && M(-1,y)&SOLUTION) ? '0' : ' ');
						Maze[ary][arx]=((M(0,y)&SOLUTION && M(-1,y)&SOLUTION) ? '#' : ' ');
						arx++;
					} else {
						//putchar('0');
						Maze[ary][arx]='#';
						arx++;
					}

//					for (x=0; x<c; x++) {
					for (x=0; x<c+combine; x++) {
						for (i=1; i<w; i++) {
							//putchar(M(x,y)&SOLUTION?'0':' ');
							Maze[ary][arx]=(M(x,y)&SOLUTION?'#':' ');
							arx++;
						}
						if (M(x,y) & GO_RIGHT) {
							//putchar((M(x,y)&SOLUTION && M(x+1,y)&SOLUTION) ? '0' : ' ');
//							Maze[ary][arx]=((M(x,y)&SOLUTION && M((x+1)%(c+1),y)&SOLUTION) ? '#' : ' ');
							Maze[ary][arx]=((M(x,y)&SOLUTION && M(x+1,y)&SOLUTION) ? '#' : ' ');
							arx++;
						}

						else {
							//printf("0");
							Maze[ary][arx]='#';
							arx++;
						}
					}
					//printf("\n");
					arx=1;
					ary++;
				}
		}
	}

	free(maze_data);
	free(xt);
	free(yt);

}

void gen_maze2(int gif, int c, int r, int w, int h, int s) {
	char *maze_data;

	int arx=1;
	int ary=1;
//  Maze[ary][arx]=

	int x, y;
	int *xt, *yt;

	if (c < 1 || r < 1 || w < 1 || h < 1)
		return;

	maze_data = (char *)calloc(r+2, c+2);
	xt = (int *)malloc(c*r*sizeof(int));
	yt = (int *)malloc(c*r*sizeof(int));

	for (x=0; x<c; x++)
		for (y=0; y<r; y++) {
			xt[x+y*c] = x;
			yt[x+y*c] = y;
		}

	for (x=-1; x<=c; x++) {
		M(x, -1) = USED;
		M(x, r) = USED;
	}
	for (y=0; y<=r; y++) {
		M(-1, y) = USED;
		M(c, y) = USED;
	}

	if (s == 0)
		s = time(0);
	srand(s);
//   srand((unsigned int)time(NULL));

	for (x=r*c-1; x>0; x--) {
		y = rand() % (x+1);
		if (y!=x) {
			int t = xt[x];
			xt[x] = xt[y];
			xt[y] = t;
			t = yt[x];
			yt[x] = yt[y];
			yt[y] = t;
		}
	}

	M(-1,0) |= USED | GO_RIGHT;
	M(0,0) |= USED | GO_LEFT;

	int num_left = r*c-1;
	while (num_left)
		for (x=0; x<c; x++)
			for (y=0; y<r; y++) {
				while (1) {
					int px = xt[x+y*c];
					int py = yt[x+y*c];
					int ways[8], wp;
					if (!(M(px, py) & USED))
						break;

					while (1) {
						wp = 0;

						if (!(M(px,py-1) & USED))
							ways[wp++] = GO_UP;
//						if (!(M(px,py-1) & USED))
//							ways[wp++] = GO_UP;
						if (!(M(px,py+1) & USED))
							ways[wp++] = GO_DOWN;
						if (!(M(px-1,py) & USED))
							ways[wp++] = GO_LEFT;
//						if (!(M(px-1,py) & USED))
//							ways[wp++] = GO_LEFT;
						if (!(M(px+1,py) & USED))
							ways[wp++] = GO_RIGHT;
						if (wp == 0) {
							break;		// blocked at this point
						}

						wp = rand() % wp;

						switch (ways[wp]) {
							case GO_LEFT:
								M(px,py) |= GO_LEFT;
								px--;
								M(px,py) |= GO_RIGHT | USED;
								break;
							case GO_RIGHT:
								M(px,py) |= GO_RIGHT;
								px++;
								M(px,py) |= GO_LEFT | USED;
								break;
							case GO_UP:
								M(px,py) |= GO_UP;
								py--;
								M(px,py) |= GO_DOWN | USED;
								break;
							case GO_DOWN:
								M(px,py) |= GO_DOWN;
								py++;
								M(px,py) |= GO_UP | USED;
								break;
						}
						num_left--;
					}
					if (px == xt[x+y*c] && py == yt[x+y*c])
						break;
				}
			}

	M(c,r-1) |= USED | GO_LEFT;
	M(c-1,r-1) |= USED | GO_RIGHT;

	if (solve) {
		for (x=0; x<c; x++)
			for (y=0; y<r; y++)
				M(x,y) |= SOLUTION;
		M(-1,0) |= SOLUTION;
		M(0,0) |= SOLUTION;
		M(c,r-1) |= SOLUTION;
		M(c-1,r-1) |= SOLUTION;

		for (x=0; x<c; x++)
			for (y=0; y<r; y++) {
				int px = x;
				int py = y;
				int ways[4], wp;

				while (1) {
					wp = 0;

					if (M(px,py) & GO_UP && M(px,py-1) & SOLUTION)
						ways[wp++] = GO_UP;
					if (M(px,py) & GO_DOWN && M(px,py+1) & SOLUTION)
						ways[wp++] = GO_DOWN;
					if (M(px,py) & GO_LEFT && M(px-1,py) & SOLUTION)
						ways[wp++] = GO_LEFT;
					if (M(px,py) & GO_RIGHT && M(px+1,py) & SOLUTION)
						ways[wp++] = GO_RIGHT;
					if (wp != 1)
						break;		// not a dead end

					switch (ways[0]) {
						case GO_LEFT:
							M(px,py) &= ~SOLUTION;
							px--;
							break;
						case GO_RIGHT:
							M(px,py) &= ~SOLUTION;
							px++;
							break;
						case GO_UP:
							M(px,py) &= ~SOLUTION;
							py--;
							break;
						case GO_DOWN:
							M(px,py) &= ~SOLUTION;
							py++;
							break;
					}
				}
			}
	}

	if (!gif) {
		int i;
		for (y=0; y<=r; y++) {
			Maze2[ary][arx]='#';
			arx++;
			//putchar('0');
			for (x=0; x<c; x++) {
				if (M(x,y) & GO_UP || x==-1)
					for (i=1; i<w; i++) {
						//putchar((M(x,y)&SOLUTION && M(x,y-1)&SOLUTION) ? '0' : ' ');
						Maze2[ary][arx]=((M(x,y)&SOLUTION && M(x,y-1)&SOLUTION) ? '#' : ' ');
						arx++;
					}

				else
					for (i=1; i<w; i++) {
						//putchar('0');
						Maze2[ary][arx]='#';
						arx++;
					}
				Maze2[ary][arx]='#';
				arx++;
				//printf("0");
			}
			arx=1;
			ary++;
			//printf("\n");
			if (y<r)
				for (int dy=1; dy<h; dy++) {
					if (M(0,y) & GO_LEFT) {
						//putchar((M(0,y)&SOLUTION && M(-1,y)&SOLUTION) ? '0' : ' ');
						Maze2[ary][arx]=((M(0,y)&SOLUTION && M(-1,y)&SOLUTION) ? '#' : ' ');
						arx++;
					} else {
						//putchar('0');
						Maze2[ary][arx]='#';
						arx++;
					}

					for (x=0; x<c; x++) {
						for (i=1; i<w; i++) {
							//putchar(M(x,y)&SOLUTION?'0':' ');
							Maze2[ary][arx]=(M(x,y)&SOLUTION?'#':' ');
							arx++;
						}
						if (M(x,y) & GO_RIGHT) {
							//putchar((M(x,y)&SOLUTION && M(x+1,y)&SOLUTION) ? '0' : ' ');
							Maze2[ary][arx]=((M(x,y)&SOLUTION && M(x+1,y)&SOLUTION) ? '#' : ' ');
							arx++;
						}

						else {
							//printf("0");
							Maze2[ary][arx]='#';
							arx++;
						}
					}
					//printf("\n");
					arx=1;
					ary++;
				}
		}
	}

	free(maze_data);
	free(xt);
	free(yt);

}


void generate_maze(int width,int height,int seed) {
//	char *maze_data;
	int c=width, r=height, w=2, h=2, s=0, gif=0;

	s=seed;
//    s = (int)time(0);

	solve=0;
	gen_maze(gif, c, r, w, h, s);
    printf("\n");
//	solve=1;
//	gen_maze2(gif, c, r, w, h, s);
}



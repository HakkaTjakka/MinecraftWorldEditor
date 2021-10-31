#!/usr/bin/python3

import numpy as np
import jnius_config
import sys
import math

EARTH_RADIUS = 6371000
#EARTH_RADIUS = 6378137.0

utrecht_x = 3899275.0
utrecht_y = 348997.0
utrecht_z = 5026376.0

jnius_config.set_classpath('terra121_classes')
from jnius import autoclass

A = 6378137.0
B = 6356752.3142

ModifiedAirocean = autoclass("io.github.terra121.projection.ModifiedAirocean")
ScaleProjection = autoclass("io.github.terra121.projection.ScaleProjection")
GeographicProjection = autoclass("io.github.terra121.projection.GeographicProjection")
Orientation = autoclass("io.github.terra121.projection.GeographicProjection$Orientation")

base_projection = GeographicProjection.orientProjection(ModifiedAirocean(), Orientation.none)
projection = ScaleProjection(base_projection, 7318261.522857145, -7318261.522857145)

if __name__ == "__main__":
#    print ('__main__')
    if len(sys.argv)==1:
#        print ('converting from pipe')
        COUNTER = 0
        fd=0
        fd_out = open("result.txt", "w")
        fd = 1
        for line in sys.stdin:
#            print('LINE: ' + line)
            lines = np.array([line], dtype=str)
            v = lines
            v = np.char.split(v, " ")
            v = np.array(list(v))[:, 0:2]
            for i in range(len(v)):
#                if v[i,0] == 'dummy':
#                    print('got dummy')
                if v[i,0] != 'ready' and v[i,0] != 'dummy':
                    if fd==0:
                        fd_out = open("result.txt", "w")
                        fd = 1
                    COUNTER=COUNTER + 1

                    REGIONX=float(v[i, 0].astype(float))
                    REGIONZ=float(v[i, 1].astype(float))
#                    print( 'IN: ' + str(REGIONX) + ' ' + str(REGIONZ) + ' (' + str(COUNTER) + ')' )
                    INT_REGIONX=int(REGIONX)
                    INT_REGIONZ=int(REGIONZ)
                    COORDS=projection.toGeo(*np.array([(REGIONX)*512, (REGIONZ)*512]))

#                    print(
#                        '{:17.13f}'.format(COORDS[0]) + ' ' + '{:17.13f}'.format(COORDS[1]) + ' '
#                        'r' + '.' + str(INT_REGIONX) + '.' + str(INT_REGIONZ) + ' ' +
#                        '[' + '{:.4f}'.format( (REGIONX) ) + ',' + '{:.4f}'.format( (REGIONZ) ) + ']'
#                    )
                    fd_out.write(
                        '{:17.13f}'.format(COORDS[0]) + ' ' + '{:17.13f}'.format(COORDS[1]) + ' ' +
                        'r' + '.' + str(INT_REGIONX) + '.' + str(INT_REGIONZ) + ' ' +
                        '[' + '{:.4f}'.format( (REGIONX) ) + ',' + '{:.4f}'.format( (REGIONZ) ) + ']' +
                        '\n'
                    )
                else:
#                    print('got ready')
                    fd_out.close()
                    fd_out = open("geo_ready.txt", "w")
                    fd_out.write( 'ready. ' + str(COUNTER) + ' converted' + '\n')
                    fd_out.close()
                    fd=0;


    if len(sys.argv)==3:
            REGIONX=float(sys.argv[1])
            REGIONZ=float(sys.argv[2])
            print( 'IN: ' + str(REGIONX) + ' ' + str(REGIONZ) )
            INT_REGIONX=int(REGIONX)
            INT_REGIONZ=int(REGIONZ)
            COORDS=projection.toGeo(*np.array([REGIONX*512, REGIONZ*512]))

            fd_out = open("result.txt", "w")
#            print(
#                '{:17.13f}'.format(COORDS[0]) + ' ' + '{:17.13f}'.format(COORDS[1]) + ' '
#                'r' + '.' + str(INT_REGIONX) + '.' + str(INT_REGIONZ) + ' ' +
#                '[' + '{:.4f}'.format( (REGIONX) ) + ',' + '{:.4f}'.format( (REGIONZ) ) + ']'
#            )
            fd_out.write(
                '{:17.13f}'.format(COORDS[0]) + ' ' + '{:17.13f}'.format(COORDS[1]) + ' ' +
                'r' + '.' + str(INT_REGIONX) + '.' + str(INT_REGIONZ) + ' ' +
                '[' + '{:.4f}'.format( (REGIONX) ) + ',' + '{:.4f}'.format( (REGIONZ) ) + ']' +
                '\n'
            )

            fd_out.close()
            fd_out = open("geo_ready.txt", "w")
            fd_out.write( 'ready.')
            fd_out.close()


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
    LINE='# '
    if len(sys.argv)>=3:
        for i in range(len(sys.argv)):
            if i>2:
                LINE+=sys.argv[i]
                if i != len(sys.argv):
                    LINE+=' '

        LON=float(sys.argv[1])
        LAT=float(sys.argv[2])
        COORDS=projection.fromGeo(LON,LAT)
#        REGIONX=int(10000*COORDS[0])/10000
#        REGIONZ=int(10000*COORDS[1])/10000
        REGIONX=int(COORDS[0]+0.5)
        REGIONZ=int(COORDS[1]+0.5)

        X=int(COORDS[0]/512)
        Z=int(COORDS[1]/512)
        if X<0:
            X=X-1
        if Z<0:
            Z=Z-1
#        print ( 'r.=' + str(X) + '.' + str(Z) + '.mca' )
        
        print ( '/tp ' + str(REGIONX) + ' ~ ' + str(REGIONZ)  + ' @ ' + 'r.=' + str(X) + '.' + str(Z) + '.mca ' + "{:.8f}".format(LON) + ' ' +"{:.8f}".format(LAT) + ' ' + LINE)
#        print ( '/tp ' + str(REGIONX) + ' ~ ' + str(REGIONZ))
        


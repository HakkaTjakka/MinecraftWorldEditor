#!/usr/bin/python3

import numpy as np
import jnius_config
import sys
import math

#EARTH_RADIUS = 6371000
EARTH_RADIUS = 6378137.0

offset_x = 3899275.0
offset_y = 348997.0
offset_z = 5026376.0

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
#    multiprocessing.freeze_support()
#    print(projection.fromGeo(0, 51.5))
#    print(projection.toGeo(*projection.fromGeo(0, 51.5)))

#    print ('Number of arguments:', len(sys.argv), 'arguments.')
#    print ('Argument List:', str(sys.argv))

    if len(sys.argv)==3:
#        print ('arg[1]='+sys.argv[1])
#        print ('arg[2]='+sys.argv[2])
        LON=float(sys.argv[1])
        LAT=float(sys.argv[2])
#        print (LAT)
#        print (LON)
        COORDS=projection.fromGeo(LON,LAT)
        print ( 'X=' + str(COORDS[0]) + ' , Z=' + str(COORDS[1]) )
        print ( 'region ' + str(COORDS[0]/512) + '.' + str(COORDS[1]/512) )
        REGIONX=int(COORDS[0]/512)
        REGIONZ=int(COORDS[1]/512)
        print ( 'region ' + str(REGIONX) + '.' + str(REGIONZ) )

 
        
    elif len(sys.argv)==5:
        LON_WEST=float(sys.argv[1])
        LAT_NORTH=float(sys.argv[2])
        LON_EAST=float(sys.argv[3])
        LAT_SOUTH=float(sys.argv[4])
        TOP_LEFT=projection.fromGeo(LON_WEST,LAT_NORTH)
        TOP_RIGHT=projection.fromGeo(LON_EAST,LAT_NORTH)
        BOTTOM_LEFT=projection.fromGeo(LON_WEST,LAT_SOUTH)
        BOTTOM_RIGHT=projection.fromGeo(LON_EAST,LAT_SOUTH)
        
#        print ('top left:    ' + 'X=' + str(TOP_LEFT[0]) + ' , Z=' + str(TOP_LEFT[1]) )
#        print ('top right:   ' + 'X=' + str(TOP_RIGHT[0]) + ' , Z=' + str(TOP_RIGHT[1]) )
#        print ('bottom left: ' + 'X=' + str(BOTTOM_LEFT[0]) + ' , Z=' + str(BOTTOM_LEFT[1]) )
#        print ('bottom right:' + 'X=' + str(BOTTOM_RIGHT[0]) + ' , Z=' + str(BOTTOM_RIGHT[1]) )
        print ('TOP_LEFT(' + 'X=' + str(TOP_LEFT[0]) + ' Z=' + str(TOP_LEFT[1]) + ')')
        print ('TOP_RIGHT(' + 'X=' + str(TOP_RIGHT[0]) + ' Z=' + str(TOP_RIGHT[1]) + ')')
        print ('BOT_LEFT(' + 'X=' + str(BOTTOM_LEFT[0]) + ' Z=' + str(BOTTOM_LEFT[1]) + ')')
        print ('BOT_RIGHT(' + 'X=' + str(BOTTOM_RIGHT[0]) + ' Z=' + str(BOTTOM_RIGHT[1]) + ')')

        LEN_TOP=   math.sqrt( (TOP_RIGHT[0]-TOP_LEFT[0])*(TOP_RIGHT[0]-TOP_LEFT[0]) + (TOP_RIGHT[1]-TOP_LEFT[1])*(TOP_RIGHT[1]-TOP_LEFT[1]) ) 
        LEN_BOT=   math.sqrt( (BOTTOM_RIGHT[0]-BOTTOM_LEFT[0])*(BOTTOM_RIGHT[0]-BOTTOM_LEFT[0]) + (BOTTOM_RIGHT[1]-BOTTOM_LEFT[1])*(BOTTOM_RIGHT[1]-BOTTOM_LEFT[1]) ) 
        LEN_RIGHT= math.sqrt( (TOP_RIGHT[0]-BOTTOM_RIGHT[0])*(TOP_RIGHT[0]-TOP_RIGHT[0]) + (TOP_RIGHT[1]-BOTTOM_RIGHT[1])*(TOP_RIGHT[1]-BOTTOM_RIGHT[1]) ) 
        LEN_LEFT=  math.sqrt( (TOP_LEFT[0]-BOTTOM_LEFT[0])*(TOP_LEFT[0]-TOP_LEFT[0]) + (TOP_LEFT[1]-BOTTOM_LEFT[1])*(TOP_LEFT[1]-BOTTOM_LEFT[1]) ) 

        SURFACE=((LEN_TOP+LEN_BOT)/2.0) * ((LEN_RIGHT+LEN_LEFT)/2.0) / (512.0*512.0)

        print ('SURFACE=' + str(SURFACE) + ' REGION FILES')

        print( "LEN_TOP=  " + str( math.sqrt( (TOP_RIGHT[0]-TOP_LEFT[0])*(TOP_RIGHT[0]-TOP_LEFT[0]) + (TOP_RIGHT[1]-TOP_LEFT[1])*(TOP_RIGHT[1]-TOP_LEFT[1]) ) ) )
        print( "LEN_BOT=  " + str( math.sqrt( (BOTTOM_RIGHT[0]-BOTTOM_LEFT[0])*(BOTTOM_RIGHT[0]-BOTTOM_LEFT[0]) + (BOTTOM_RIGHT[1]-BOTTOM_LEFT[1])*(BOTTOM_RIGHT[1]-BOTTOM_LEFT[1]) ) ) )
        print( "LEN_RIGHT=" + str( math.sqrt( (TOP_RIGHT[0]-BOTTOM_RIGHT[0])*(TOP_RIGHT[0]-TOP_RIGHT[0]) + (TOP_RIGHT[1]-BOTTOM_RIGHT[1])*(TOP_RIGHT[1]-BOTTOM_RIGHT[1]) ) ) )
        print( "LEN_LEFT= " + str( math.sqrt( (TOP_LEFT[0]-BOTTOM_LEFT[0])*(TOP_LEFT[0]-TOP_LEFT[0]) + (TOP_LEFT[1]-BOTTOM_LEFT[1])*(TOP_LEFT[1]-BOTTOM_LEFT[1]) ) ) )
    elif len(sys.argv)==6:
#        print ('arg[1]='+sys.argv[1])
#        print ('arg[2]='+sys.argv[2])
        LON=float(sys.argv[1])
        LAT=float(sys.argv[2])
        offset_x =float(sys.argv[3])
        offset_y =float(sys.argv[4])
        offset_z =float(sys.argv[5])
        
#        print (LAT)
#        print (LON)
        COORDS=projection.fromGeo(LON,LAT)
        print ( 'X=' + str(COORDS[0]) + ' , Z=' + str(COORDS[1]) )
        print ( 'region ' + str(COORDS[0]/512) + '.' + str(COORDS[1]/512) )
        REGIONX=int(COORDS[0]/512)
        REGIONZ=int(COORDS[1]/512)
        print ( 'region ' + str(REGIONX) + '.' + str(REGIONZ) )

#       MIN X: X=-31506.3662904785 Y=20341.558763549256 Z=22746.06043269392


        v = [[offset_x,offset_y,offset_z]]
#        v = [[offset_x,offset_y,offset_z]]
        v = np.array(v, dtype=float)

        rad = np.linalg.norm(v, axis=1)[None, :]
        lat = np.arcsin(v[:, 2]/rad)*180/np.pi
        lon = (np.arctan2(v[:, 1], v[:, 0])*180/np.pi)[None, :]
        rad -= EARTH_RADIUS  # TODO: find the correct way to get elevation (this is bad but ellipsoid was worse)
        v = np.array([lat, lon, rad]).transpose()[:, 0]

        # pick the first point, and use it as the origin to find the local transformation matrix
        old_origin = v[0, :2]
        new_origin = np.array(projection.fromGeo(old_origin[1], old_origin[0]))
        i = np.array(projection.fromGeo(old_origin[1], old_origin[0] + 0.01)) - new_origin
        j = np.array(projection.fromGeo(old_origin[1] + 0.01, old_origin[0])) - new_origin
        basis = 100*np.array((i, j))

        # apply the transformation to every lat,lon in the array
        v[:, :2] -= old_origin
        v[:, :2] = np.einsum("ij,ni->nj", basis, v[:, :2])
        v[:, :2] += new_origin

        # swap y and z because minecraft is sideways
        v[:, 2], v[:, 1] = v[:, 1].copy(), v[:, 2].copy()

        print( 'HOPPA: ' + str(v[:, 0]) + ' ' + str(v[:, 1]) + ' ' + str(v[:, 2]) )
        print( 'HOPPA: ' + str(v[:, 0]-COORDS[0]) + ' ' + str(v[:, 1]) + ' ' + str(v[:, 2]-COORDS[1]) )

    elif len(sys.argv)==8:
        LON_WEST=float(sys.argv[1])
        LAT_NORTH=float(sys.argv[2])
        LON_EAST=float(sys.argv[3])
        LAT_SOUTH=float(sys.argv[4])
        offset_x =float(sys.argv[5])
        offset_y =float(sys.argv[6])
        offset_z =float(sys.argv[7])

        TOP_LEFT=projection.fromGeo(LON_WEST,LAT_NORTH)
        TOP_RIGHT=projection.fromGeo(LON_EAST,LAT_NORTH)
        BOTTOM_LEFT=projection.fromGeo(LON_WEST,LAT_SOUTH)
        BOTTOM_RIGHT=projection.fromGeo(LON_EAST,LAT_SOUTH)

        
#        print ('top left:    ' + 'X=' + str(TOP_LEFT[0]) + ' , Z=' + str(TOP_LEFT[1]) )
#        print ('top right:   ' + 'X=' + str(TOP_RIGHT[0]) + ' , Z=' + str(TOP_RIGHT[1]) )
#        print ('bottom left: ' + 'X=' + str(BOTTOM_LEFT[0]) + ' , Z=' + str(BOTTOM_LEFT[1]) )
#        print ('bottom right:' + 'X=' + str(BOTTOM_RIGHT[0]) + ' , Z=' + str(BOTTOM_RIGHT[1]) )
        print ('TOP_LEFT(' + 'X=' + str(TOP_LEFT[0]) + ' Z=' + str(TOP_LEFT[1]) + ')')
        print ('TOP_RIGHT(' + 'X=' + str(TOP_RIGHT[0]) + ' Z=' + str(TOP_RIGHT[1]) + ')')
        print ('BOT_LEFT(' + 'X=' + str(BOTTOM_LEFT[0]) + ' Z=' + str(BOTTOM_LEFT[1]) + ')')
        print ('BOT_RIGHT(' + 'X=' + str(BOTTOM_RIGHT[0]) + ' Z=' + str(BOTTOM_RIGHT[1]) + ')')

        v = [[offset_x,offset_y,offset_z]]
#        v = [[offset_x,offset_y,offset_z]]
        v = np.array(v, dtype=float)

        rad = np.linalg.norm(v, axis=1)[None, :]
        lat = np.arcsin(v[:, 2]/rad)*180/np.pi
        lon = (np.arctan2(v[:, 1], v[:, 0])*180/np.pi)[None, :]
        rad -= EARTH_RADIUS  # TODO: find the correct way to get elevation (this is bad but ellipsoid was worse)
        v = np.array([lat, lon, rad]).transpose()[:, 0]
        # pick the first point, and use it as the origin to find the local transformation matrix
        old_origin = v[0, :2]
        new_origin = np.array(projection.fromGeo(old_origin[1], old_origin[0]))
        i = np.array(projection.fromGeo(old_origin[1], old_origin[0] + 0.01)) - new_origin
        j = np.array(projection.fromGeo(old_origin[1] + 0.01, old_origin[0])) - new_origin
        basis = 100*np.array((i, j))

        # apply the transformation to every lat,lon in the array
        v[:, :2] -= old_origin
        v[:, :2] = np.einsum("ij,ni->nj", basis, v[:, :2])
        v[:, :2] += new_origin

        # swap y and z because minecraft is sideways
        v[:, 2], v[:, 1] = v[:, 1].copy(), v[:, 2].copy()

        COORDS=projection.fromGeo(LON_EAST,LAT_NORTH)

        print ('PROJECTION(' + 'X=' + str(v[:, 0]) + ' Y=' + str(v[:, 1]) + ' Z=' + str(v[:, 2]) + ')')
        print( 'rad=' + str(rad) + ' lat=' + str(lat) + ' lon=' + str(lon) )


#        x = (EARTH_RADIUS+v[:, 1]) * np.cos(lat*np.pi/180) * np.cos(lon*np.pi/180)
#        y = (EARTH_RADIUS+v[:, 1]) * np.cos(lat*np.pi/180) * np.sin(lon*np.pi/180)
#        z = (EARTH_RADIUS+v[:, 1]) * np.sin(lat*np.pi/180)
#        print('-------------')
#        print ('REVERSED(' + 'X=' + str(x) + ' Y=' + str(y) + ' Z=' + str(z) + ')')
#        print('-------------')
#        print ('DIFFERENCE(' + 'X=' + str(x-offset_x) + ' Y=' + str(y-offset_y) + ' Z=' + str(z-offset_z) + ')')
#        print('-------------')

        x = (EARTH_RADIUS+v[:, 1]) * np.cos(LAT_NORTH*np.pi/180) * np.cos(LON_WEST*np.pi/180)
        y = (EARTH_RADIUS+v[:, 1]) * np.cos(LAT_NORTH*np.pi/180) * np.sin(LON_WEST*np.pi/180)
        z = (EARTH_RADIUS+v[:, 1]) * np.sin(LAT_NORTH*np.pi/180)
        print('-------------')
        print ('REVERSED LAT_NORTH/LON_WEST(' + 'X=' + str(x) + ' Y=' + str(y) + ' Z=' + str(z) + ')')
        print('-------------')
        print ('DIFFERENCE(' + 'X=' + str(x-offset_x) + ' Y=' + str(y-offset_y) + ' Z=' + str(z-offset_z) + ')')
        print('-------------')

        x = (EARTH_RADIUS+v[:, 1]) * np.cos(LAT_SOUTH*np.pi/180) * np.cos(LON_EAST*np.pi/180)
        y = (EARTH_RADIUS+v[:, 1]) * np.cos(LAT_SOUTH*np.pi/180) * np.sin(LON_EAST*np.pi/180)
        z = (EARTH_RADIUS+v[:, 1]) * np.sin(LAT_SOUTH*np.pi/180)
        print('-------------')
        print ('REVERSED LAT_SOUTH/LON_EAST(' + 'X=' + str(x) + ' Y=' + str(y) + ' Z=' + str(z) + ')')
        print('-------------')
        print ('DIFFERENCE(' + 'X=' + str(x-offset_x) + ' Y=' + str(y-offset_y) + ' Z=' + str(z-offset_z) + ')')
        print('-------------')



        rad = 6378137.0
        alt = 0
        f = 1.0/298.257223563
        ls = np.arctan((1 - f)**2 * np.tan(lat*np.pi/180))    # lambda

        x = alt * np.cos(ls*np.pi/180) * np.cos(LON_WEST*np.pi/180) + rad * np.cos(LAT_NORTH*np.pi/180) * np.cos(LON_WEST*np.pi/180)
        y = alt * np.cos(ls*np.pi/180) * np.sin(LON_WEST*np.pi/180) + rad * np.cos(LAT_NORTH*np.pi/180) * np.sin(LON_WEST*np.pi/180)
        z = alt * np.sin(ls*np.pi/180) + rad * np.sin(LAT_NORTH*np.pi/180)
        print('-------------')
        print ('REVERSED LAT_NORTH/LON_WEST(' + 'X=' + str(x) + ' Y=' + str(y) + ' Z=' + str(z) + ')')
        print('-------------')
        print ('DIFFERENCE(' + 'X=' + str(x-offset_x) + ' Y=' + str(y-offset_y) + ' Z=' + str(z-offset_z) + ')')
        print('-------------')
        x = alt * np.cos(ls*np.pi/180) * np.cos(LON_EAST*np.pi/180) + rad * np.cos(LAT_SOUTH*np.pi/180) * np.cos(LON_EAST*np.pi/180)
        y = alt * np.cos(ls*np.pi/180) * np.sin(LON_EAST*np.pi/180) + rad * np.cos(LAT_SOUTH*np.pi/180) * np.sin(LON_EAST*np.pi/180)
        z = alt * np.sin(ls*np.pi/180) + rad * np.sin(LAT_SOUTH*np.pi/180)
        print('-------------')
        print ('REVERSED LAT_SOUTH/LON_EAST(' + 'X=' + str(x) + ' Y=' + str(y) + ' Z=' + str(z) + ')')
        print('-------------')
        print ('DIFFERENCE(' + 'X=' + str(x-offset_x) + ' Y=' + str(y-offset_y) + ' Z=' + str(z-offset_z) + ')')
        print('-------------')


#        x = alt * np.cos(ls*np.pi/180) * np.cos(lon*np.pi/180) + rad * np.cos(lat*np.pi/180) * np.cos(lon*np.pi/180)
#        y = alt * np.cos(ls*np.pi/180) * np.sin(lon*np.pi/180) + rad * np.cos(lat*np.pi/180) * np.sin(lon*np.pi/180)
#        z = alt * np.sin(ls*np.pi/180) + rad * np.sin(lat*np.pi/180)
#
#        print('-------------')
#        print ('REVERSED(' + 'X=' + str(x) + ' Y=' + str(y) + ' Z=' + str(z) + ')')
#        print('-------------')
#        print ('DIFFERENCE(' + 'X=' + str(x-offset_x) + ' Y=' + str(y-offset_y) + ' Z=' + str(z-offset_z) + ')')
#        print('-------------')

#        r = EARTH_RADIUS + v[:, 1]
#        x = r * np.cos(lon) * np.cos(lat)
#        y = r * np.sin(lon) * np.cos(lat)
#        z = r * np.sin(lat)
#        print ('REVERSED(' + 'X=' + str(x) + ' Y=' + str(y) + ' Z=' + str(z) + ')')


#        alt=v[:, 1]
#        rad = 6378137.0
#        f = 1.0/298.257223563
#        cosLat = np.cos(lat)
#        sinLat = np.sin(lat)
#        FF     = (1.0-f)**2
#        C      = 1/np.sqrt(cosLat**2 + FF * sinLat**2)
#        S      = C * FF
#
#        x = (rad * C + alt)*cosLat * np.cos(lon)
#        y = (rad * C + alt)*cosLat * np.sin(lon)
#        z = (rad * S + alt)*sinLat
#        print ('REVERSED(' + 'X=' + str(x) + ' Y=' + str(y) + ' Z=' + str(z) + ')')


        print( 'HOPPA: ' + str(v[:, 0]) + ' ' + str(v[:, 1]) + ' ' + str(v[:, 2]) )
        print( 'HOPPA: ' + str(v[:, 0]-COORDS[0]) + ' ' + str(v[:, 1]) + ' ' + str(v[:, 2]-COORDS[1]) )

        LEN_TOP=   math.sqrt( (TOP_RIGHT[0]-TOP_LEFT[0])*(TOP_RIGHT[0]-TOP_LEFT[0]) + (TOP_RIGHT[1]-TOP_LEFT[1])*(TOP_RIGHT[1]-TOP_LEFT[1]) ) 
        LEN_BOT=   math.sqrt( (BOTTOM_RIGHT[0]-BOTTOM_LEFT[0])*(BOTTOM_RIGHT[0]-BOTTOM_LEFT[0]) + (BOTTOM_RIGHT[1]-BOTTOM_LEFT[1])*(BOTTOM_RIGHT[1]-BOTTOM_LEFT[1]) ) 
        LEN_RIGHT= math.sqrt( (TOP_RIGHT[0]-BOTTOM_RIGHT[0])*(TOP_RIGHT[0]-TOP_RIGHT[0]) + (TOP_RIGHT[1]-BOTTOM_RIGHT[1])*(TOP_RIGHT[1]-BOTTOM_RIGHT[1]) ) 
        LEN_LEFT=  math.sqrt( (TOP_LEFT[0]-BOTTOM_LEFT[0])*(TOP_LEFT[0]-TOP_LEFT[0]) + (TOP_LEFT[1]-BOTTOM_LEFT[1])*(TOP_LEFT[1]-BOTTOM_LEFT[1]) ) 

        SURFACE=((LEN_TOP+LEN_BOT)/2.0) * ((LEN_RIGHT+LEN_LEFT)/2.0) / (512.0*512.0)

        print ('SURFACE=' + str(SURFACE) + ' REGION FILES')

        print( "LEN_TOP=  " + str( math.sqrt( (TOP_RIGHT[0]-TOP_LEFT[0])*(TOP_RIGHT[0]-TOP_LEFT[0]) + (TOP_RIGHT[1]-TOP_LEFT[1])*(TOP_RIGHT[1]-TOP_LEFT[1]) ) ) )
        print( "LEN_BOT=  " + str( math.sqrt( (BOTTOM_RIGHT[0]-BOTTOM_LEFT[0])*(BOTTOM_RIGHT[0]-BOTTOM_LEFT[0]) + (BOTTOM_RIGHT[1]-BOTTOM_LEFT[1])*(BOTTOM_RIGHT[1]-BOTTOM_LEFT[1]) ) ) )
        print( "LEN_RIGHT=" + str( math.sqrt( (TOP_RIGHT[0]-BOTTOM_RIGHT[0])*(TOP_RIGHT[0]-TOP_RIGHT[0]) + (TOP_RIGHT[1]-BOTTOM_RIGHT[1])*(TOP_RIGHT[1]-BOTTOM_RIGHT[1]) ) ) )
        print( "LEN_LEFT= " + str( math.sqrt( (TOP_LEFT[0]-BOTTOM_LEFT[0])*(TOP_LEFT[0]-TOP_LEFT[0]) + (TOP_LEFT[1]-BOTTOM_LEFT[1])*(TOP_LEFT[1]-BOTTOM_LEFT[1]) ) ) )

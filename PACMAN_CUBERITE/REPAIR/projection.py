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
        print ('LON=' + str(LON))
        print ('LAT=' + str(LAT))
        COORDS=projection.fromGeo(LON,LAT)
        print ( 'X=' + str(COORDS[0]) + ' , Z=' + str(COORDS[1]) )
        print ( 'region ' + str(COORDS[0]/512) + '.' + str(COORDS[1]/512) )
        REGIONX=int(COORDS[0]/512)
        REGIONZ=int(COORDS[1]/512)
        print ( 'REGIONX=' + str(REGIONX) + ' REGIONZ=' + str(REGIONZ) )

 
        
    elif len(sys.argv)==4:
#        print ('arg[1]='+sys.argv[1])
#        print ('arg[2]='+sys.argv[2])
        if sys.argv[1]=='togeo':
            REGIONX=float(sys.argv[2])
            REGIONZ=float(sys.argv[3])
#            print ('REGIONX=' + str(REGIONX))
#            print ('REGIONZ=' + str(REGIONZ))
            #v = np.array([REGIONX*512, REGIONZ*512])
            #print(v)
            
            COORDS=projection.toGeo(*np.array([REGIONX*512, REGIONZ*512]))
            #COORDS=projection.toGeo(*np.array(REGIONZ*512,REGIONX*512))
#            print ( 'LON=' + str(COORDS[0]) + ' , LAT=' + str(COORDS[1]) )
            print ( '[' + str(COORDS[0]) + '][' + str(COORDS[1]) + ']')
#            print ( 'region ' + str(COORDS[0]/512) + '.' + str(COORDS[1]/512) )
#            REGIONX=int(COORDS[0]/512)
#            REGIONZ=int(COORDS[1]/512)
#            print ( 'region ' + str(REGIONX) + '.' + str(REGIONZ) )
    
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
        SURFACE=((LEN_TOP+LEN_BOT)/2.0) * ((LEN_RIGHT+LEN_LEFT)/2.0) / (1000.0*1000.0)
        print ('SURFACE=' + str(SURFACE) + ' SQUARE KILOMETERS')

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

        print ('TOP_LEFT(' + 'X=' + str(TOP_LEFT[0]) + ' Z=' + str(TOP_LEFT[1]) + ')')
        print ('TOP_RIGHT(' + 'X=' + str(TOP_RIGHT[0]) + ' Z=' + str(TOP_RIGHT[1]) + ')')
        print ('BOT_LEFT(' + 'X=' + str(BOTTOM_LEFT[0]) + ' Z=' + str(BOTTOM_LEFT[1]) + ')')
        print ('BOT_RIGHT(' + 'X=' + str(BOTTOM_RIGHT[0]) + ' Z=' + str(BOTTOM_RIGHT[1]) + ')')

        v = [[offset_x,offset_y,offset_z]]
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

    elif len(sys.argv)==11:
        LON_WEST=float(sys.argv[1])
        LAT_NORTH=float(sys.argv[2])
        LON_EAST=float(sys.argv[3])
        LAT_SOUTH=float(sys.argv[4])
        offset_x1 =float(sys.argv[5])
        offset_y1 =float(sys.argv[6])
        offset_z1 =float(sys.argv[7])
        offset_x2 =float(sys.argv[8])
        offset_y2 =float(sys.argv[9])
        offset_z2 =float(sys.argv[10])

        TOP_LEFT=projection.fromGeo(LON_WEST,LAT_NORTH)
        TOP_RIGHT=projection.fromGeo(LON_EAST,LAT_NORTH)
        BOTTOM_LEFT=projection.fromGeo(LON_WEST,LAT_SOUTH)
        BOTTOM_RIGHT=projection.fromGeo(LON_EAST,LAT_SOUTH)

        print ('TOP_LEFT(' + 'X=' + str(TOP_LEFT[0]) + ' Z=' + str(TOP_LEFT[1]) + ')')
        print ('TOP_RIGHT(' + 'X=' + str(TOP_RIGHT[0]) + ' Z=' + str(TOP_RIGHT[1]) + ')')
        print ('BOT_LEFT(' + 'X=' + str(BOTTOM_LEFT[0]) + ' Z=' + str(BOTTOM_LEFT[1]) + ')')
        print ('BOT_RIGHT(' + 'X=' + str(BOTTOM_RIGHT[0]) + ' Z=' + str(BOTTOM_RIGHT[1]) + ')')

        v = [[offset_x1,offset_y1,offset_z1]]
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

        print ('PROJECTION1(' + 'X=' + str(v[:, 0]) + ' Y=' + str(v[:, 1]) + ' Z=' + str(v[:, 2]) + ')')

        x1 = (EARTH_RADIUS) * np.cos(LAT_NORTH*np.pi/180) * np.cos(LON_EAST*np.pi/180)
        y1 = (EARTH_RADIUS) * np.cos(LAT_NORTH*np.pi/180) * np.sin(LON_EAST*np.pi/180)
        z1 = (EARTH_RADIUS) * np.sin(LAT_NORTH*np.pi/180)
        print ('GEO_NORTH_EAST(' + 'X=' + str(x1) + ' Y=' + str(y1) + ' Z=' + str(z1) + ')')

        v = [[offset_x2,offset_y2,offset_z2]]
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

        print ('PROJECTION2(' + 'X=' + str(v[:, 0]) + ' Y=' + str(v[:, 1]) + ' Z=' + str(v[:, 2]) + ')')

        x2 = (EARTH_RADIUS) * np.cos(LAT_SOUTH*np.pi/180) * np.cos(LON_WEST*np.pi/180)
        y2 = (EARTH_RADIUS) * np.cos(LAT_SOUTH*np.pi/180) * np.sin(LON_WEST*np.pi/180)
        z2 = (EARTH_RADIUS) * np.sin(LAT_SOUTH*np.pi/180)
        print ('GEO_SOUTH_WEST(' + 'X=' + str(x2) + ' Y=' + str(y2) + ' Z=' + str(z2) + ')')

        print ('DIFFERENCE_NORTH_EAST(' + 'X=' + str(x1-offset_x1) + ' Y=' + str(y1-offset_y1) + ' Z=' + str(z1-offset_z1) + ')')
        print ('DIFFERENCE_SOUTH_WEST(' + 'X=' + str(x2-offset_x2) + ' Y=' + str(y2-offset_y2) + ' Z=' + str(z2-offset_z2) + ')')

        print( 'rad=' + str(rad) + ' lat=' + str(lat) + ' lon=' + str(lon) )

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

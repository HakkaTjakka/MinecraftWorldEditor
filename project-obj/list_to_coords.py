#!/usr/bin/python3

import numpy as np
import jnius_config
import sys
import math
import os

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
        
    if len(sys.argv)==1:
        print ('converting from pipe')
        COUNTER = 0
        fd_out = open("result.txt", "a")
        for line in sys.stdin:
            lines = np.array([line], dtype=str)
            v = lines
            v = np.char.split(v, "*")
            v = np.array(list(v))[:, 0:5]
            for i in range(len(v)):
                #print( v[i, 0] + '.' + v[i, 1] + '.' + v[i, 2]  )

                COUNTER=COUNTER + 1

                LON=float(v[i, 2].astype(float))
                LAT=float(v[i, 3].astype(float))
                COORDS=projection.fromGeo(LON,LAT)

                X=int(COORDS[0]/512)
                Z=int(COORDS[1]/512)
                if X<0:
                    X=X-1
                if Z<0:
                    Z=Z-1
                    print( 
                        'tp' + ' ' + str(int(COORDS[0])) + ' ~ ' + str(int(COORDS[1])) + ' ' +
                        '{:8.4f}'.format(LON) + ' ' + '{:8.4f}'.format(LAT) +
                        ' functions\\' + v[i, 0] + '\\' + v[i, 1] +
                        ' ' + v[i, 4] , end = ''
                    )
                    fd_out.write( 
                        'tp' + ' ' + str(int(COORDS[0])) + ' ~ ' + str(int(COORDS[1])) + ' ' +
                        '{:8.4f}'.format(LON) + ' ' + '{:8.4f}'.format(LAT) +
                        ' functions\\' + v[i, 0] + '\\' + v[i, 1] +
                        ' ' + v[i, 4]
                    )
                    filename='functions\\' + v[i, 0] + '\\' + v[i, 1] + '.mcfunction'
                    fd_out2 = open(filename, "w")
                    fd_out2.write( 
                        'tp' + ' ' + str(int(COORDS[0])) + ' ~ ' + str(int(COORDS[1])) + '\n' +
                        'say ' + v[i, 4]
                    )
                    fd_out2.close()
                    

        fd_out.close()

#            for i in range(len(v)):
#                INT_REGIONX=int(v[i, 1].astype(float))
#                INT_REGIONZ=int(v[i, 2].astype(float))
#                REGIONX=float(v[i, 1].astype(float))
#                REGIONZ=float(v[i, 2].astype(float))
#                COORDS=projection.toGeo(*np.array([REGIONX*512, REGIONZ*512]))
#                print( 'r' + '.' + str(INT_REGIONX) + '.' + str(INT_REGIONZ) + ' ' + str(COORDS[0]) + ' ' + str(COORDS[1]) + ' ' + line, end = '')
#                fd = open("result.txt", "a")
#                fd.write('r' + '.' + str(INT_REGIONX) + '.' + str(INT_REGIONZ) + ' ' + str(COORDS[0]) + ' ' + str(COORDS[1]) )
#                fd.write(' ' + line)
#                fd.close()

    if len(sys.argv)==2:
    #    print (str(len(sys.argv)))
        print ('converting ' + sys.argv[1])
        with open(sys.argv[1]) as fd:
            lines = fd.read().splitlines()
        print('Read ' + sys.argv[1])

        lines = np.array(lines, dtype=str)
        idx = np.where(np.char.startswith(lines, "r."))
        v = lines[idx]
        v = np.char.split(v, ".")
        v = np.array(list(v))[:, 1:3].astype(float)
        print( 'r' + '.' + str(v[:, 0]) + '.' + str(v[:, 1]) + ' - ' + str(v[:, 1]) )
        #print( 'r' + '.' + v[:, 0] + '.' + v[:, 1] )
        print( v )

        for i in range(len(v)):
            REGIONX=float(v[i, 0])
            REGIONZ=float(v[i, 1])
            COORDS=projection.toGeo(*np.array([REGIONX*512, REGIONZ*512]))
            print( 'r' + '.' + str(v[i, 0]) + '.' + str(v[i, 1]) + ' ' + str(COORDS[0]) + ' ' + str(COORDS[1]) )

            #o_out = []
            
            
            #o_out.append("{}".format('r' + '.' + str(v[i, 0]) + '.' + str(v[i, 1]) + ' ' + str(COORDS[0]) + ' ' + str(COORDS[1])))

            #o_out.append( 'r' + '.' + str(v[i, 0]) + '.' + str(v[i, 1]) + ' ' + str(COORDS[0]) + ' ' + str(COORDS[1]) )
            #o_out = np.array(o_out, dtype=str)
            #lines[idx] = o_out
            fd = open("result.txt", "a")
            fd.write('r' + '.' + str(v[i, 0]) + '.' + str(v[i, 1]) + ' ' + str(COORDS[0]) + ' ' + str(COORDS[1]) )
            fd.write("\n")
            fd.close()




            #print( str(COORDS[0]) + ' ' + str(COORDS[1]) )
        


    #v_out.append("v {} {} {}".format(v[i, 0], v[i, 1], v[i, 2]))

###    lines = np.array(lines, dtype=str)
###    v = lines.char.split(v, ".")
###    print(v[:, 0] + '.' + v[:, 1] + '.' + v[:, 2])

###  #lines = np.array(lines, dtype=np.str)
###  lines = np.array(lines, dtype=str)
###  #lines = lines[np.logical_not(np.char.startswith(lines, "vn "))] # delete vertex normals
###  
###  #Utrecht
###  offset_x=3899275.0
###  offset_y=348997.0
###  offset_z=5026376.0
###  
###  
###  #v 3268023.6848134077 27.84330720361322 -5319793.639094348
###  
###  
###  # extract vertices
###  idx = np.where(np.char.startswith(lines, "v "))
###  v = lines[idx]
###  v = np.char.split(v, " ")
###  v = np.array(list(v))[:, 1:].astype(float)
###  
###  
###  o = v
###  
###  
###  v[:, 0]+=offset_x
###  v[:, 1]+=offset_y
###  v[:, 2]+=offset_z
###  
###  
###  
###  # convert to lat/lon/ele
###  rad = np.linalg.norm(v, axis=1)[None, :]
###  lat = np.arcsin(v[:, 2]/rad)*180/np.pi
###  lon = (np.arctan2(v[:, 1], v[:, 0])*180/np.pi)[None, :]
###  rad -= EARTH_RADIUS  # TODO: find the correct way to get elevation (this is bad but ellipsoid was worse)
###  v = np.array([lat, lon, rad]).transpose()[:, 0]
###  
###  # pick the first point, and use it as the origin to find the local transformation matrix
###  old_origin = v[0, :2]
###  new_origin = np.array(projection.fromGeo(old_origin[1], old_origin[0]))
###  i = np.array(projection.fromGeo(old_origin[1], old_origin[0] + 0.01)) - new_origin
###  j = np.array(projection.fromGeo(old_origin[1] + 0.01, old_origin[0])) - new_origin
###  basis = 100*np.array((i, j))
###  
###  # apply the transformation to every lat,lon in the array
###  v[:, :2] -= old_origin
###  v[:, :2] = np.einsum("ij,ni->nj", basis, v[:, :2])
###  v[:, :2] += new_origin
###  
###  # swap y and z because minecraft is sideways
###  v[:, 2], v[:, 1] = v[:, 1].copy(), v[:, 2].copy()
###  
###  o[:, 2]=v[:, 1]
###  
###  o_out = []
###  for i in range(len(o)):
###      o_out.append("v {} {} {}".format(o[i, 0]-offset_x, o[i, 1]-offset_y, o[i, 2]))
###  o_out = np.array(o_out, dtype=str)
###  
###  lines[idx] = o_out
###  
###  if len(sys.argv)==3:
###      outfile=sys.argv[2]
###  elif len(sys.argv)==1:
###      outfile='out.obj'
###  
###  #with open("out2.obj", "w") as fd:
###  with open(outfile, "w") as fd:
###      fd.write("\n".join(lines))
###  
###  
###  
###  # convert to string
###  v_out = []
###  for i in range(len(v)):   
###      v_out.append("v {} {} {}".format(v[i, 0], v[i, 1], v[i, 2]))
###  v_out = np.array(v_out, dtype=str)
###  
###  lines[idx] = v_out
###  with open("out2.obj", "w") as fd:
###      fd.write("\n".join(lines))

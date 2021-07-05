import numpy as np
import sys
from projection import projection

EARTH_RADIUS = 6371000

if len(sys.argv)==3:
#    print (str(len(sys.argv)))
    print ('converting ' + sys.argv[1] + ' to ' + sys.argv[2])
    with open(sys.argv[1]) as fd:
        lines = fd.read().splitlines()
elif len(sys.argv)==1:
    with open("in.obj") as fd:
        lines = fd.read().splitlines()

#lines = np.array(lines, dtype=np.str)
lines = np.array(lines, dtype=str)
#lines = lines[np.logical_not(np.char.startswith(lines, "vn "))] # delete vertex normals

offset_x=3899275.0
offset_y=348997.0
offset_z=5026376.0

#v 3268023.6848134077 27.84330720361322 -5319793.639094348


# extract vertices
idx = np.where(np.char.startswith(lines, "v "))
v = lines[idx]
v = np.char.split(v, " ")
v = np.array(list(v))[:, 1:].astype(float)

o = v


v[:, 0]+=offset_x
v[:, 1]+=offset_y
v[:, 2]+=offset_z



# convert to lat/lon/ele
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

o[:, 2]=v[:, 1]

o_out = []
for i in range(len(o)):
    o_out.append("v {} {} {}".format(o[i, 0]-offset_x, o[i, 1]-offset_y, o[i, 2]))
o_out = np.array(o_out, dtype=str)

lines[idx] = o_out

if len(sys.argv)==3:
    outfile=sys.argv[2]
elif len(sys.argv)==1:
    outfile='out.obj'

#with open("out2.obj", "w") as fd:
with open(outfile, "w") as fd:
    fd.write("\n".join(lines))


## convert to string
#v_out = []
#for i in range(len(v)):
#    v_out.append("v {} {} {}".format(v[i, 0], v[i, 1], v[i, 2]))
#v_out = np.array(v_out, dtype=str)
#
#lines[idx] = v_out
#with open("out.obj", "w") as fd:
#    fd.write("\n".join(lines))

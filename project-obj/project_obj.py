import numpy as np
from projection import projection

EARTH_RADIUS = 6371000

with open("in.obj") as fd:
    lines = fd.read().splitlines()

lines = np.array(lines, dtype=np.str)
lines = lines[np.logical_not(np.char.startswith(lines, "vn "))] # delete vertex normals

# extract vertices
idx = np.where(np.char.startswith(lines, "v "))
v = lines[idx]
v = np.char.split(v, " ")
v = np.array(list(v))[:, 1:].astype(float)

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

# convert to string
v_out = []
for i in range(len(v)):
    v_out.append("v {} {} {}".format(v[i, 0], v[i, 1], v[i, 2]))
v_out = np.array(v_out, dtype=str)

lines[idx] = v_out
with open("out.obj", "w") as fd:
    fd.write("\n".join(lines))

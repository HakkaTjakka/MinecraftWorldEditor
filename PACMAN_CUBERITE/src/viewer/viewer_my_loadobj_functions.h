
bool FileExists(const std::string& abs_filename)
{
    bool ret;
    FILE* fp = fopen(abs_filename.c_str(), "rb");
    if (fp)
    {
        ret = true;
        fclose(fp);
    }
    else
    {
        ret = false;
    }

    return ret;
}

static bool CheckErrors(std::string desc)
{
    GLenum e = glGetError();
    if (e != GL_NO_ERROR)
    {
        fprintf(stderr, "OpenGL error in \"%s\": %d\n", desc.c_str(), e);
        fprintf(stderr, "OpenGL error in \"%s\": 0x%x\n", desc.c_str(), e);
        return false;
    }
    return true;
}

static void CalcNormal(float N[3], float v0[3], float v1[3], float v2[3])
{
    float v10[3];
    v10[0] = v1[0] - v0[0];
    v10[1] = v1[1] - v0[1];
    v10[2] = v1[2] - v0[2];

    float v20[3];
    v20[0] = v2[0] - v0[0];
    v20[1] = v2[1] - v0[1];
    v20[2] = v2[2] - v0[2];

    N[0] = v20[1] * v10[2] - v20[2] * v10[1];
    N[1] = v20[2] * v10[0] - v20[0] * v10[2];
    N[2] = v20[0] * v10[1] - v20[1] * v10[0];

    float len2 = N[0] * N[0] + N[1] * N[1] + N[2] * N[2];
    if (len2 > 0.0f)
    {
        float len = sqrtf(len2);

        N[0] /= len;
        N[1] /= len;
        N[2] /= len;
    }
}

namespace  // Local utility functions
{
struct vec3
{
    float v[3];
    vec3()
    {
        v[0] = 0.0f;
        v[1] = 0.0f;
        v[2] = 0.0f;
    }
};

void normalizeVector(vec3 &v)
{
    float len2 = v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2];
    if (len2 > 0.0f)
    {
        float len = sqrtf(len2);

        v.v[0] /= len;
        v.v[1] /= len;
        v.v[2] /= len;
    }
}

// Check if `mesh_t` contains smoothing group id.
bool hasSmoothingGroup(const tinyobj::shape_t& shape)
{
    for (size_t i = 0; i < shape.mesh.smoothing_group_ids.size(); i++)
    {
        if (shape.mesh.smoothing_group_ids[i] > 0)
        {
            return true;
        }
    }
    return false;
}

void computeSmoothingNormals(const tinyobj::attrib_t& attrib, const tinyobj::shape_t& shape,
                             std::map<int, vec3>& smoothVertexNormals)
{
    smoothVertexNormals.clear();
    std::map<int, vec3>::iterator iter;

    for (size_t f = 0; f < shape.mesh.indices.size() / 3; f++)
    {
        // Get the three indexes of the face (all faces are triangular)
        tinyobj::index_t idx0 = shape.mesh.indices[3 * f + 0];
        tinyobj::index_t idx1 = shape.mesh.indices[3 * f + 1];
        tinyobj::index_t idx2 = shape.mesh.indices[3 * f + 2];

        // Get the three vertex indexes and coordinates
        int vi[3];      // indexes
        float v[3][3];  // coordinates

        for (int k = 0; k < 3; k++)
        {
            vi[0] = idx0.vertex_index;
            vi[1] = idx1.vertex_index;
            vi[2] = idx2.vertex_index;
            if ( vi[0]< 0 || vi[0]< 0 || vi[0]< 0 ) {
                v[0][k] = 0;   v[1][k] = 0;     v[2][k] = 0;
            } else {
                v[0][k] = attrib.vertices[3 * vi[0] + k];
                v[1][k] = attrib.vertices[3 * vi[1] + k];
                v[2][k] = attrib.vertices[3 * vi[2] + k];
            }
//            assert(vi[0] >= 0);
//            assert(vi[1] >= 0);
//            assert(vi[2] >= 0);

        }

        // Compute the normal of the face
        float normal[3];
        CalcNormal(normal, v[0], v[1], v[2]);

        // Add the normal to the three vertexes
        for (size_t i = 0; i < 3; ++i)
        {
            iter = smoothVertexNormals.find(vi[i]);
            if (iter != smoothVertexNormals.end())
            {
                // add
                iter->second.v[0] += normal[0];
                iter->second.v[1] += normal[1];
                iter->second.v[2] += normal[2];
            }
            else
            {
                smoothVertexNormals[vi[i]].v[0] = normal[0];
                smoothVertexNormals[vi[i]].v[1] = normal[1];
                smoothVertexNormals[vi[i]].v[2] = normal[2];
            }
        }

    }  // f

    // Normalize the normals, that is, make them unit vectors
    for (iter = smoothVertexNormals.begin(); iter != smoothVertexNormals.end();
            iter++)
    {
        normalizeVector(iter->second);
    }

}  // computeSmoothingNormals
}  // namespace


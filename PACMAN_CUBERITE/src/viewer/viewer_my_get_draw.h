

struct one_elem {
    GLfloat idx0[3+3+3+2];
    GLfloat idx1[3+3+3+2];
    GLfloat idx2[3+3+3+2];
};

static void Get_Draw2(const std::vector<DrawObject>& drawObjects,  std::vector<tinyobj::material_t>& materials, std::map<std::string, GLuint>& textures)
{


    glPolygonOffset(1.0, 1.0);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glColor3f(1.0f, 1.0f, 1.0f);
//    glEnable(GL_BLEND);
//color out
//  GLsizei stride = (3 + 3 + 2) * sizeof(float);
    GLsizei stride = (3 + 3 + 3 + 2) * sizeof(float);
    for (size_t i = 0; i < drawObjects.size(); i++)
    {
        DrawObject o = drawObjects[i];
        if (o.vb_id < 1)
        {
            continue;
        }
        glBindBuffer(GL_ARRAY_BUFFER, o.vb_id);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);


//color out
//        if (textures.size()==0)
//            glEnableClientState(GL_COLOR_ARRAY);

        if (i<20) {
            printf("Object#: %d(%d) Material id: %d(%d) ",(int)i,(int)drawObjects.size(),(int)o.material_id,materials.size());
        }

        if (TEXTURE_ARRAY) {

            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glBindTexture(GL_TEXTURE_2D, 0);

            if ((o.material_id < materials.size()))
            {
                std::string diffuse_texname = materials[o.material_id].diffuse_texname;
                if (textures.find(diffuse_texname) != textures.end())
                {
                    glBindTexture(GL_TEXTURE_2D, textures[diffuse_texname]);
                    if (i<20) {
                        GLint texDims[2];
                        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &texDims[0]);
                        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &texDims[1]);
                        printf(" Texture size: x=%d,y=%d textures[%s]=%d ",(int)texDims[0],(int)texDims[1],diffuse_texname.c_str(),(int)textures[diffuse_texname]);
                    }
                } else {
                    if (COLOR_ARRAY) glEnableClientState(GL_COLOR_ARRAY);
                    printf(" Texture not found: textures[%s] ",diffuse_texname.c_str());
                }
            } else {
                printf(" Material id > size ");
                if (COLOR_ARRAY) glEnableClientState(GL_COLOR_ARRAY);
            }
        } else {
            if (COLOR_ARRAY) glEnableClientState(GL_COLOR_ARRAY);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }
        if (!COLOR_ARRAY) glDisableClientState(GL_COLOR_ARRAY);

        glVertexPointer(3, GL_FLOAT, stride, (const void*)0);
        glNormalPointer(GL_FLOAT, stride, (const void*)(sizeof(float) * 3));
//color out
        glColorPointer(3, GL_FLOAT, stride, (const void*)(sizeof(float) * 6));

//color out

//        glTexCoordPointer(2, GL_FLOAT, stride, (const void*)(sizeof(float) * 6));
        glTexCoordPointer(2, GL_FLOAT, stride, (const void*)(sizeof(float) * 9));


        if (i<20) {
            printf("#Triangles=%d\n",(int)o.numTriangles);
            if (i<5) {
                GLsizeiptr size=stride*o.numTriangles;
                GLuint target=o.vb_id;
                GLintptr offset=0;
                one_elem *elements = new one_elem [o.numTriangles];
                glGetNamedBufferSubData(target, 	offset, size*3, (GLvoid*)	elements);
                CheckErrors("Huh?");
                size_t T;
                for (T=0; T<o.numTriangles && (T<5);T++) {
        //        for (size_t T=0; T<o.numTriangles;T++) {
                    printf("Triangle %d(%d) of Object#: %d(%d)\n",(int)T,(int)o.numTriangles,(int)i,(int)drawObjects.size());

                    printf("Vertexes: (% 12.7f,% 12.7f,% 12.7f) (% 12.7f,% 12.7f,% 12.7f) (% 12.7f,% 12.7f,% 12.7f)\n",
                             (float)elements[T].idx0[0],(float)elements[T].idx0[1],(float)elements[T].idx0[2],
                             (float)elements[T].idx1[0],(float)elements[T].idx1[1],(float)elements[T].idx1[2],
                             (float)elements[T].idx2[0],(float)elements[T].idx2[1],(float)elements[T].idx2[2]);
                    printf("Normals:  (% 12.7f,% 12.7f,% 12.7f) (% 12.7f,% 12.7f,% 12.7f) (% 12.7f,% 12.7f,% 12.7f)\n",
                             (float)elements[T].idx0[3],(float)elements[T].idx0[4],(float)elements[T].idx0[5],
                             (float)elements[T].idx1[3],(float)elements[T].idx1[4],(float)elements[T].idx1[5],
                             (float)elements[T].idx2[3],(float)elements[T].idx2[4],(float)elements[T].idx2[5]);
                    printf("Color:    (% 12.7f,% 12.7f,% 12.7f) (% 12.7f,% 12.7f,% 12.7f) (% 12.7f,% 12.7f,% 12.7f)\n",
                             (float)elements[T].idx0[6],(float)elements[T].idx0[7],(float)elements[T].idx0[8],
                             (float)elements[T].idx1[6],(float)elements[T].idx1[7],(float)elements[T].idx1[8],
                             (float)elements[T].idx2[6],(float)elements[T].idx2[7],(float)elements[T].idx2[8]);
                    printf("Texture:  (% 12.7f,% 12.7f)              (% 12.7f,% 12.7f)              (% 12.7f,% 12.7f)\n",
                             (float)elements[T].idx0[9],(float)elements[T].idx0[10],
                             (float)elements[T].idx1[9],(float)elements[T].idx1[10],
                             (float)elements[T].idx2[9],(float)elements[T].idx2[10]);
                }
                if (T<o.numTriangles) printf("(bufferdata) etc\n.\n.\n");
                delete [] elements;
            }
        } else {
            if (i==20) printf("(shapes) etc\n.\n.\n");
        }

        glDrawArrays(GL_TRIANGLES, 0, 3 * o.numTriangles);
        CheckErrors("drawarrays");
        glBindTexture(GL_TEXTURE_2D, 0);
    }


    // draw wireframe
    /*
      glDisable(GL_POLYGON_OFFSET_FILL);
      glPolygonMode(GL_FRONT, GL_LINE);
      glPolygonMode(GL_BACK, GL_LINE);

      glColor3f(0.0f, 0.0f, 0.4f);
      for (size_t i = 0; i < drawObjects.size(); i++) {
        DrawObject o = drawObjects[i];
        if (o.vb_id < 1) {
          continue;
        }

        glBindBuffer(GL_ARRAY_BUFFER, o.vb_id);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glVertexPointer(3, GL_FLOAT, stride, (const void*)0);
        glNormalPointer(GL_FLOAT, stride, (const void*)(sizeof(float) * 3));
        glColorPointer(3, GL_FLOAT, stride, (const void*)(sizeof(float) * 6));
        glTexCoordPointer(2, GL_FLOAT, stride, (const void*)(sizeof(float) * 9));

        glDrawArrays(GL_TRIANGLES, 0, 3 * o.numTriangles);
        CheckErrors("drawarrays");
      }
    */

}



/*
    GLint texDims[2];
glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, texDims);
//glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, texDims, 1);


int[] texDims = new int[2];
glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, texDims, 0);
glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, texDims, 1);


void glGetTexImage (GLenum      target,
                    GLint       level,
                    GLenum      format, // GL will convert to this format
                    GLenum      type,   // Using this data type per-pixel
                    GLvoid *    img);
*/


static void Get_Draw(const std::vector<DrawObject>& drawObjects,  std::vector<tinyobj::material_t>& materials, std::map<std::string, GLuint>& textures)
{

    glPolygonOffset(1.0, 1.0);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glColor3f(1.0f, 1.0f, 1.0f);

    GLsizei stride = (3 + 3 + 3 + 2) * sizeof(float);
    for (size_t i = 0; i < drawObjects.size(); i++)
    {
        DrawObject o = drawObjects[i];
        if (o.vb_id < 1)
        {
            continue;
        }
        glBindBuffer(GL_ARRAY_BUFFER, o.vb_id);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);

        if (i<20) {
            printf("Object#: %d(%d) Material id: %d(%d) ",(int)i,(int)drawObjects.size(),(int)o.material_id,materials.size());
        }

        if ((TEXTURE_ARRAY || COLOR_ARRAY) || (!TEXTURE_ARRAY && !COLOR_ARRAY && !WIRE_FRAME)) {
            if (TEXTURE_ARRAY)
            {
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                glBindTexture(GL_TEXTURE_2D, 0);

                if ((o.material_id < materials.size()))
                {
                    std::string diffuse_texname = materials[o.material_id].diffuse_texname;
                    if (textures.find(diffuse_texname) != textures.end())
                    {
                        glBindTexture(GL_TEXTURE_2D, textures[diffuse_texname]);

                        if (i<20) {
                            GLint texDims[2];
                            glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &texDims[0]);
                            glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &texDims[1]);
                            printf(" Texture size: x=%d,y=%d textures[%s]=%d ",(int)texDims[0],(int)texDims[1],diffuse_texname.c_str(),(int)textures[diffuse_texname]);
                        }

//                        depth_shader.setUniform("the_texture", sf::Shader::CurrentTexture);
//                        glUniform1i(glGetUniformLocation(depth_shader.getNativeHandle(), "the_texture"), 0);
//                        glUniform1i(glGetUniformLocation(textures[diffuse_texname], "the_texture"), 0);
                    }
                    else
                    {
                        if (COLOR_ARRAY)
                            glEnableClientState(GL_COLOR_ARRAY);
                    }
                }
                else
                {
                    if (COLOR_ARRAY)
                        glEnableClientState(GL_COLOR_ARRAY);
                }
            }
            else
            {
                if (COLOR_ARRAY)
                    glEnableClientState(GL_COLOR_ARRAY);
                glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            }
            if (!COLOR_ARRAY)
                glDisableClientState(GL_COLOR_ARRAY);

            glVertexPointer(3, GL_FLOAT, stride, (const void*)0);
            glNormalPointer(GL_FLOAT, stride, (const void*)(sizeof(float) * 3));
            glColorPointer(3, GL_FLOAT, stride, (const void*)(sizeof(float) * 6));
            glTexCoordPointer(2, GL_FLOAT, stride, (const void*)(sizeof(float) * 9));

            CheckErrors("Heh?");

            if (i<20) {
                printf("#Triangles=%d\n",(int)o.numTriangles);
                if (i<5) {
                    GLsizeiptr size=3*stride*o.numTriangles;
                    GLuint target=o.vb_id;
                    GLintptr offset=0;
                    one_elem *elements = new one_elem [o.numTriangles];
                    if (elements==NULL) {
                        printf("elements==NULL\n");
                        return;
                    }

                    glGetNamedBufferSubData(target, 	offset, size, (void*)	elements);
//                    glGetNamedBufferSubData(target, 	offset, size*3, (GLvoid*)	elements);
                    size_t T=0;
                    if (CheckErrors("Huh?")==true) {
                        for (T=0; T<o.numTriangles && (T<5);T++) {
                //        for (size_t T=0; T<o.numTriangles;T++) {
                            printf("Triangle %d(%d) of Object#: %d(%d)\n",(int)T,(int)o.numTriangles,(int)i,(int)drawObjects.size());

                            printf("Vertexes: (% 12.7f,% 12.7f,% 12.7f) (% 12.7f,% 12.7f,% 12.7f) (% 12.7f,% 12.7f,% 12.7f)\n",
                                     (float)elements[T].idx0[0],(float)elements[T].idx0[1],(float)elements[T].idx0[2],
                                     (float)elements[T].idx1[0],(float)elements[T].idx1[1],(float)elements[T].idx1[2],
                                     (float)elements[T].idx2[0],(float)elements[T].idx2[1],(float)elements[T].idx2[2]);
                            printf("Normals:  (% 12.7f,% 12.7f,% 12.7f) (% 12.7f,% 12.7f,% 12.7f) (% 12.7f,% 12.7f,% 12.7f)\n",
                                     (float)elements[T].idx0[3],(float)elements[T].idx0[4],(float)elements[T].idx0[5],
                                     (float)elements[T].idx1[3],(float)elements[T].idx1[4],(float)elements[T].idx1[5],
                                     (float)elements[T].idx2[3],(float)elements[T].idx2[4],(float)elements[T].idx2[5]);
                            printf("Color:    (% 12.7f,% 12.7f,% 12.7f) (% 12.7f,% 12.7f,% 12.7f) (% 12.7f,% 12.7f,% 12.7f)\n",
                                     (float)elements[T].idx0[6],(float)elements[T].idx0[7],(float)elements[T].idx0[8],
                                     (float)elements[T].idx1[6],(float)elements[T].idx1[7],(float)elements[T].idx1[8],
                                     (float)elements[T].idx2[6],(float)elements[T].idx2[7],(float)elements[T].idx2[8]);
                            printf("Texture:  (% 12.7f,% 12.7f)              (% 12.7f,% 12.7f)              (% 12.7f,% 12.7f)\n",
                                     (float)elements[T].idx0[9],(float)elements[T].idx0[10],
                                     (float)elements[T].idx1[9],(float)elements[T].idx1[10],
                                     (float)elements[T].idx2[9],(float)elements[T].idx2[10]);
                        }
                    }
                    if (T<o.numTriangles) printf("(bufferdata) etc\n.\n.\n");
                    delete [] elements;
                }
            } else {
                if (i==20) printf("(shapes) etc\n.\n.\n");
            }

            glDrawArrays(GL_TRIANGLES, 0, 3 * o.numTriangles);
            CheckErrors("drawarrays");
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }

    if (WIRE_FRAME)
    {
        // draw wireframe
        glDisable(GL_POLYGON_OFFSET_FILL);
        glPolygonMode(GL_FRONT, GL_LINE);
        glPolygonMode(GL_BACK, GL_LINE);

        glColor3f(1.0f, .5f, 0.0f);
        for (size_t i = 0; i < drawObjects.size(); i++)
        {
            DrawObject o = drawObjects[i];
            if (o.vb_id < 1)
            {
                continue;
            }

            glBindBuffer(GL_ARRAY_BUFFER, o.vb_id);
            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_NORMAL_ARRAY);
            glDisableClientState(GL_COLOR_ARRAY);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            glVertexPointer(3, GL_FLOAT, stride, (const void*)0);
            glNormalPointer(GL_FLOAT, stride, (const void*)(sizeof(float) * 3));
            glColorPointer(3, GL_FLOAT, stride, (const void*)(sizeof(float) * 6));
            glTexCoordPointer(2, GL_FLOAT, stride, (const void*)(sizeof(float) * 9));

            glDrawArrays(GL_TRIANGLES, 0, 3 * o.numTriangles);
            CheckErrors("drawarrays");
        }

        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_FILL);
//        glEnable(GL_POLYGON_OFFSET_FILL);
    }
}

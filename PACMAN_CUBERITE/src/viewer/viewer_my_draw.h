static void Draw(const std::vector<DrawObject>& drawObjects,
                 std::vector<tinyobj::material_t>& materials,
                 std::map<std::string, GLuint>& textures)
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
//                        glActiveTexture(GL_TEXTURE0 + 0);

                        glBindTexture(GL_TEXTURE_2D, textures[diffuse_texname]);

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
    //color out
            glColorPointer(3, GL_FLOAT, stride, (const void*)(sizeof(float) * 6));

    //color out
    //        glTexCoordPointer(2, GL_FLOAT, stride, (const void*)(sizeof(float) * 6));
            glTexCoordPointer(2, GL_FLOAT, stride, (const void*)(sizeof(float) * 9));

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

static void Draw_one_shape(const std::vector<DrawObject>& drawObjects,
                           std::vector<tinyobj::material_t>& materials,
                           std::map<std::string, GLuint>& textures, int ii,glm::vec3 color)

//                           std::map<std::string, GLuint>& textures, int ii,float color[3])
//                           std::map<std::string, GLuint>& textures, int ii,GLubyte color[3])
{
    if (!(ii>=0 && ii<drawObjects.size()))
    {
        printf("Shape out of bound 0 >= %d >= %d\n",ii,drawObjects.size()-1);
    }

    if (ii==0) {
        glPolygonOffset(1.0, 1.0);
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_CULL_FACE);
        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_FILL);
        glEnable(GL_POLYGON_OFFSET_FILL);
    }

    if (!TEXTURE_ARRAY) glColor3f(color.x,color.y,color.z);
//    if (!TEXTURE_ARRAY) glColor3ub(	color[0],color[1],color[2]);
//    if (!TEXTURE_ARRAY) glColor3ub(	(GLubyte)color.x ,(GLubyte)color.y,(GLubyte)color.z);
//    else glColor3ub(255, 255, 255);
//    if (!TEXTURE_ARRAY) glColor3fv(color);
    else glColor3f(1.0f, 1.0f, 1.0f);

    GLsizei stride = (3 + 3 + 3 + 2) * sizeof(float);
    if ((TEXTURE_ARRAY || COLOR_ARRAY) || (!TEXTURE_ARRAY && !COLOR_ARRAY && !WIRE_FRAME)) {
        for (size_t i = ii; i == ii; i++)
        {
            DrawObject o = drawObjects[i];
            if (o.vb_id < 1)
            {
                continue;
            }
            glBindBuffer(GL_ARRAY_BUFFER, o.vb_id);
            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_NORMAL_ARRAY);


            if (TEXTURE_ARRAY)
            {
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                glBindTexture(GL_TEXTURE_2D, 0);
                if ((o.material_id < materials.size()))
                {
                    std::string diffuse_texname = materials[o.material_id].diffuse_texname;
                    if (textures.find(diffuse_texname) != textures.end())
                    {

//                        glActiveTexture(GL_TEXTURE0 + 0);

                        glBindTexture(GL_TEXTURE_2D, textures[diffuse_texname]);

//                        glUniform1i(glGetUniformLocation(textures[diffuse_texname], "the_texture"), 0);
//                        glUniform1i(glGetUniformLocation(depth_shader.getNativeHandle(), "the_texture"), 0);
//                        depth_shader.setUniform("the_texture", sf::Shader::CurrentTexture);


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

            glDrawArrays(GL_TRIANGLES, 0, 3 * o.numTriangles);
            CheckErrors("drawarrays");
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }

    if (WIRE_FRAME)
    {
        // draw wireframe
        if (ii==0) {
            glDisable(GL_POLYGON_OFFSET_FILL);
            glPolygonMode(GL_FRONT, GL_LINE);
            glPolygonMode(GL_BACK, GL_LINE);
        }
//        glColor3ub(	(GLubyte)color.x ,(GLubyte)color.y,(GLubyte)color.z);
//        glColor3ub(color[0],color[1],color[2]);
        glColor3f(	(GLfloat)color.x,(GLfloat)color.y,(GLfloat)color.z);
//        glColor3f(	color[0],color[1],color[2]);
//        glColor3fv(color);
//        glColor3f(1.0f, 1.0f, 0.0f);
//        glColor3f(0.0f, 0.0f, 0.4f);
        for (size_t i = ii; i == ii; i++)
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

//        glPolygonMode(GL_FRONT, GL_FILL);
//        glPolygonMode(GL_BACK, GL_FILL);
//        glEnable(GL_POLYGON_OFFSET_FILL);
    }
}


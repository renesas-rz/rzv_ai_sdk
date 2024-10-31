/***********************************************************************************************************************
* Copyright 2024 Renesas Electronics Corporation
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
* http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
***********************************************************************************************************************/

#ifndef WAYLAND_H
#define WAYLAND_H


// #include "define.h"
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <wayland-client.h>
#include <wayland-egl.h>

class Wayland
{
    /* structure of Shader settings */
    typedef struct _SShader {
        GLuint unProgram;
        GLint nAttrPos;
        GLint nAttrColor;
    } SShader;

    public:
        Wayland();
        ~Wayland();

        uint8_t init(uint32_t idx, uint32_t w, uint32_t h, uint32_t c, bool overlay = false);
        uint8_t exit();
        uint8_t commit(uint8_t* cam_buffer, uint8_t* ol_buffer);

        struct wl_compositor *compositor = NULL;
        struct wl_shm *shm = NULL;
        struct wl_shell *shell = NULL;

    private:
        uint32_t img_h;
        uint32_t img_w;
        uint32_t img_c;
        bool     img_overlay;

        struct wl_display *display = NULL;
        struct wl_surface *surface;
        struct wl_shell_surface *shell_surface;
        struct wl_registry *registry = NULL;
        EGLDisplay eglDisplay;
        EGLSurface eglSurface;
        SShader sShader;
        GLuint textures[2];

        GLuint LoadShader(GLenum type, const char* shaderSrc);
        GLuint initProgramObject(SShader* pShader);
        uint8_t render(SShader* pShader, GLuint texID);
        uint8_t setupTexture(GLuint texID, uint8_t* src_pixels);
};

#endif

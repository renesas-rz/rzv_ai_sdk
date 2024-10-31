/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
* this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2024 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
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
/***********************************************************************************************************************
* File Name    : wayland.h
* Version      : v5.00
* Description  : RZ/V AI SDK Sample Application for Object Detection
***********************************************************************************************************************/

#ifndef WAYLAND_H
#define WAYLAND_H

#include "define.h"
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

        uint8_t init(uint32_t w, uint32_t h, uint32_t c, bool overlay = false);
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

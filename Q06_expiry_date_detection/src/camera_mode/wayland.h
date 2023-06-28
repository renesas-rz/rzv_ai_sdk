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
* Copyright (C) 2023 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : wayland.h
* Version      : v1.00
* Description  : RZ/V2L AI SDK Sample Application: Expiry Date Extraction
***********************************************************************************************************************/

#ifndef WAYLAND_H
#define WAYLAND_H


#include "define.h"
#include <wayland-client.h>

class Wayland
{
    public:
        Wayland();
        ~Wayland();

        uint8_t init(uint8_t fd, uint32_t w, uint32_t h, uint32_t c);
        uint8_t exit();
        uint8_t commit(uint8_t buf_id);

        struct wl_compositor *compositor = NULL;
        struct wl_shm *shm = NULL;
        struct wl_shell *shell = NULL;

    private:
        uint32_t img_h;
        uint32_t img_w;
        uint32_t img_c;

        struct wl_display *display = NULL;
        struct wl_buffer *buffer[WL_BUF_NUM];

        struct wl_surface *surface = NULL;
        struct wl_shell_surface *shell_surface = NULL;
        struct wl_registry *registry = NULL;

};

#endif

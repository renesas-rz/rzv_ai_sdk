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
 * File Name    : wayland.cpp
 * Version      : v1.00
 * Description  : RZ/V2L AI SDK Sample Application: Expiry Date Extraction
 ***********************************************************************************************************************/

/*****************************************
 * Includes
 ******************************************/
#include "define.h"
#include "wayland.h"
#include <wayland-client.h>


/*****************************************
 * Function Name : registry_global
 * Description   : wl_registry_listener callback
 *                 wayland func bind.
 * Arguments     : data      = The third argument of wl_registry_add_listener() is notified.
 *                 regisry   = The first argument of wl_registry_add_listener() is notified.
 *                 name      = global object ID is notified.
 *                 interface = interface name is notifed.
 *                 version   = interface version is notified.
 * Return value  : -
 ******************************************/
static void registry_global(void *data,
                            struct wl_registry *registry, uint32_t name,
                            const char *interface, uint32_t version)
{
    Wayland *wayland = (Wayland*)data;

    if (strcmp(interface, wl_compositor_interface.name) == 0)
    {
        wayland->compositor = (struct wl_compositor*)wl_registry_bind(registry, name, &wl_compositor_interface, 1);
    }
    else if (strcmp(interface, wl_shm_interface.name) == 0)
    {
        wayland->shm = (struct wl_shm*)wl_registry_bind(registry, name, &wl_shm_interface, 1);
    }
    else if (strcmp(interface, wl_shell_interface.name) == 0)
    {
        wayland->shell = (struct wl_shell*)wl_registry_bind(registry, name, &wl_shell_interface, 1);
    }
}

/* registry callback for listener */
static const struct wl_registry_listener registry_listener = 
{
    .global = registry_global,
};

/*****************************************
 * Function Name : shell_surface_ping
 * Description   : wl_shell_surface_listener callback
 *                 compositer check hungup
 * Arguments     : data           = The third argument of wl_shell_surface_add_listener() is notified.
 *                 shell_surface  = The first argument of wl_shell_surface_add_listener() is notified.
 *                 serial         = Identification ID is notified.
 * Return value  : -
 ******************************************/
static void shell_surface_ping(void *data,
                               struct wl_shell_surface *shell_surface,
                               uint32_t serial)
{
    wl_shell_surface_pong(shell_surface, serial);
}

static const struct wl_shell_surface_listener shell_surface_listener = 
{
    .ping = shell_surface_ping,
};

Wayland::Wayland()
{
}

Wayland::~Wayland()
{
}

/*****************************************
 * Function Name : init
 * Description   : wayland client init
 *                 create buffer.
 * Arguments     : fd = u-dma-buf fd
 *                 w  = width
 *                 c  = color
 * Return value  : 0 if Success
 *                 not 0 otherwise
 ******************************************/
uint8_t Wayland::init(uint8_t fd, uint32_t w, uint32_t h, uint32_t c)
{
    int32_t i;
    uint8_t ret = 0;
    struct wl_shm_pool *pool;
    img_w = w;
    img_h = h;
    img_c = c;

    /* Connects to the display server */
    display = wl_display_connect(NULL);
    if (NULL == display)
    {
        perror("Connecting to display server failed!");
        ret = -errno;
        goto end_wayland_init;
    }

    /* Get registry to work with global object and set listener */
    registry = wl_display_get_registry(display);
    wl_registry_add_listener(registry, &registry_listener, this);

    /* Send request to server */
    wl_display_roundtrip(display);

    /* compositor is already bind in registry callback */
    surface = wl_compositor_create_surface(compositor);
    if (NULL == surface)
    {
        perror("Create surface failed!");
        goto registry_destructor;
    }

    shell_surface = wl_shell_get_shell_surface(shell, surface);
    if (NULL == shell_surface)
    {
        perror("Create shell surface failed!");
        goto shell_destructor;
    }

    /* shell_surface config */
    wl_shell_surface_add_listener(shell_surface, &shell_surface_listener, 0);
    wl_shell_surface_set_toplevel(shell_surface);
    wl_shell_surface_set_user_data(shell_surface, surface);
    wl_surface_set_user_data(surface, NULL);

    /* create and bind buffer to surface */
    pool = wl_shm_create_pool(shm, fd, UDMABUF_OFFSET + img_w * img_h * img_c * WL_BUF_NUM);

    for (i = 0; i < WL_BUF_NUM; i++)
    {
        /* Wayland color channel is in little endian,
         * therefore WL_SHM_FORMATARGB8888 means data order is B,G,R,A in 1 byte unit. */
        buffer[i] = wl_shm_pool_create_buffer(pool, UDMABUF_OFFSET + i * img_w * img_h * img_c,
                                           img_w, img_h, img_w * img_c,
                                           WL_SHM_FORMAT_ARGB8888);
    }

    wl_shm_pool_destroy(pool);

    /* Send request to server */
    wl_display_roundtrip(display);

    ret = 0;
    goto end_wayland_init;

shell_destructor:
    wl_surface_destroy(surface);

registry_destructor:
    wl_shell_destroy(shell);
    wl_shm_destroy(shm);
    wl_compositor_destroy(compositor);

    wl_registry_destroy(registry);

    wl_display_disconnect(display);
    ret = -1;
    goto end_wayland_init;
    
end_wayland_init:
    return ret;
}

/*****************************************
 * Function Name : exit
 * Description   : Exit Wayland
 * Arguments     : -
 * Return value  : 0 if Success
 *                 not 0 otherwise
 ******************************************/
uint8_t Wayland::exit()
{
    int32_t i;
    
    /* Clean up */
    for (i = 0; i < WL_BUF_NUM; i++)
    {
        wl_buffer_destroy(buffer[i]);
    }
    wl_shell_surface_destroy(shell_surface);
    wl_surface_destroy(surface);

    wl_shell_destroy(shell);
    wl_shm_destroy(shm);
    wl_compositor_destroy(compositor);

    wl_registry_destroy(registry);

    wl_display_disconnect(display);
    return 0;
}


/*****************************************
 * Function Name : commit
 * Description   : Commit to update the display image
 * Arguments     : buf_id = buffer id
 * Return value  : 0 if Success
 *                 not 0 otherwise
 ******************************************/
uint8_t Wayland::commit(uint8_t buf_id)
{
    uint8_t ret = 0;
    wl_surface_attach(surface, buffer[buf_id], 0, 0);
    wl_surface_damage(surface, 0, 0, img_w , img_h);
    wl_surface_commit(surface);
    ret = wl_display_dispatch(display);

    return ret;
}

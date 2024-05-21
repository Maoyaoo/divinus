#pragma once

#include "i6_common.h"

#define I6_AENC_CHN_NUM 16

typedef enum {
    I6_AENC_CLK_OFF,
    I6_AENC_CLK_12_288M,
    I6_AENC_CLK_16_384M,
    I6_AENC_CLK_18_432M,
    I6_AENC_CLK_24_576M,
    I6_AENC_CLK_24M,
    I6_AENC_CLK_48M
} i6_aenc_clk;

typedef enum {
    I6_AENC_G726_16K,
    I6_AENC_G726_24K,
    I6_AENC_G726_32K,
    I6_AENC_G726_40K
} i6_aenc_g726t;

typedef enum {
    I6_AENC_INTF_I2S_MASTER,
    I6_AENC_INTF_I2S_SLAVE,
    I6_AENC_INTF_TDM_MASTER,
    I6_AENC_INTF_TDM_SLAVE,
    I6_AENC_INTF_END
} i6_aenc_intf;

typedef enum {
    I6_AENC_SND_MONO,
    I6_AENC_SND_STEREO,
    I6_AENC_SND_QUEUE,
    I6_AENC_SND_END
} i6_aenc_snd;

typedef enum {
    I6_AENC_TYPE_G711A,
    I6_AENC_TYPE_G711U,
    I6_AENC_TYPE_G726,
} i6_aenc_type;

typedef struct {
    int LeftJustOn;
    i6_aenc_clk clock;
    char syncRxClkOn;
} i6_aenc_i2s;

typedef struct {
    // Accept industry standards from 8000 to 96000Hz
    int rate;
    int bit24On;
    i6_aenc_intf intf;
    i6_aenc_snd sound;
    unsigned int frmNum;
    unsigned int packNumPerFrm;
    unsigned int codecChnNum;
    unsigned int chnNum;
    i6_aenc_i2s i2s;
} i6_aenc_cnf;

typedef struct {
    int bit24On;
    i6_aenc_snd sound;
    void *addr[I6_AENC_CHN_NUM];
    unsigned long long timestamp;
    unsigned int sequence;
    unsigned int length;
    unsigned int poolId[2];
    void *pcmAddr[I6_AENC_CHN_NUM];
    unsigned int pcmLength;
} i6_aenc_frm;

typedef struct {
    i6_aenc_frm frame;
    char isValid;
} i6_aenc_efrm;

typedef struct {
    // Accept industry standards from 8000 to 96000Hz
    int rate;
    i6_aenc_snd sound;
} i6_aenc_g711;

typedef struct {
    // Accept industry standards from 8000 to 96000Hz
    int rate;
    i6_aenc_snd sound;
    i6_aenc_g726t type;
} i6_aenc_g726;

typedef struct {
    i6_aenc_type type;
    union {
        i6_aenc_g711 g711;
        i6_aenc_g726t g726;
    };
} i6_aenc_para;

typedef struct {
    void *handle;
    
    int (*fnDisableDevice)(int device);
    int (*fnEnableDevice)(int device);
    int (*fnSetDeviceConfig)(int device, i6_aenc_cnf *config);

    int (*fnDisableChannel)(int device, int channel);
    int (*fnEnableChannel)(int device, int channel);

    int (*fnDisableEncoding)(int device, int channel);
    int (*fnEnableEncoding)(int device, int channel);
    int (*fnSetEncodingParam)(int device, int channel, i6_aenc_para *param);

    int (*fnSetMute)(int device, int channel, char active);
    int (*fnSetVolume)(int device, int channel, int dbLevel);

    int (*fnFreeFrame)(int device, int channel, i6_aenc_frm *frame, i6_aenc_efrm *encFrame);
    int (*fnGetFrame)(int device, int channel, i6_aenc_frm *frame, i6_aenc_efrm *encFrame, int millis);
} i6_aenc_impl;

static int i6_aenc_load(i6_aenc_impl *aenc_lib) {
    if (!(aenc_lib->handle = dlopen("libmi_ai.so", RTLD_LAZY | RTLD_GLOBAL))) {
        fprintf(stderr, "[i6_aenc] Failed to load library!\nError: %s\n", dlerror());
        return EXIT_FAILURE;
    }

    if (!(aenc_lib->fnDisableDevice = (int(*)(int device))
        dlsym(aenc_lib->handle, "MI_AI_Disable"))) {
        fprintf(stderr, "[i6_aenc] Failed to acquire symbol MI_AI_Disable!\n");
        return EXIT_FAILURE;
    }

    if (!(aenc_lib->fnEnableDevice = (int(*)(int device))
        dlsym(aenc_lib->handle, "MI_AI_Enable"))) {
        fprintf(stderr, "[i6_aenc] Failed to acquire symbol MI_AI_Enable!\n");
        return EXIT_FAILURE;
    }

    if (!(aenc_lib->fnSetDeviceConfig = (int(*)(int device, i6_aenc_cnf *config))
        dlsym(aenc_lib->handle, "MI_AI_SetPubAttr"))) {
        fprintf(stderr, "[i6_aenc] Failed to acquire symbol MI_AI_SetPubAttr!\n");
        return EXIT_FAILURE;
    }

    if (!(aenc_lib->fnDisableChannel = (int(*)(int device, int channel))
        dlsym(aenc_lib->handle, "MI_AI_DisableChn"))) {
        fprintf(stderr, "[i6_aenc] Failed to acquire symbol MI_AI_DisableChn!\n");
        return EXIT_FAILURE;
    }

    if (!(aenc_lib->fnEnableChannel = (int(*)(int device, int channel))
        dlsym(aenc_lib->handle, "MI_AI_EnableChn"))) {
        fprintf(stderr, "[i6_aenc] Failed to acquire symbol MI_AI_EnableChn!\n");
        return EXIT_FAILURE;
    }

    if (!(aenc_lib->fnDisableEncoding = (int(*)(int device, int channel))
        dlsym(aenc_lib->handle, "MI_AI_DisableAenc"))) {
        fprintf(stderr, "[i6_aenc] Failed to acquire symbol MI_AI_DisableChn!\n");
        return EXIT_FAILURE;
    }

    if (!(aenc_lib->fnEnableEncoding = (int(*)(int device, int channel))
        dlsym(aenc_lib->handle, "MI_AI_EnableAenc"))) {
        fprintf(stderr, "[i6_aenc] Failed to acquire symbol MI_AI_EnableChn!\n");
        return EXIT_FAILURE;
    }

    if (!(aenc_lib->fnSetEncodingParam = (int(*)(int device, int channel, i6_aenc_para *param))
        dlsym(aenc_lib->handle, "MI_AI_SetAencAttr"))) {
        fprintf(stderr, "[i6_aenc] Failed to acquire symbol MI_AI_SetAencAttr!\n");
        return EXIT_FAILURE;
    }

    if (!(aenc_lib->fnSetMute = (int(*)(int device, int channel, char active))
        dlsym(aenc_lib->handle, "MI_AI_SetMute"))) {
        fprintf(stderr, "[i6_aenc] Failed to acquire symbol MI_AI_SetMute!\n");
        return EXIT_FAILURE;
    }

    if (!(aenc_lib->fnSetVolume = (int(*)(int device, int channel, int dbLevel))
        dlsym(aenc_lib->handle, "MI_AI_SetVqeVolume"))) {
        fprintf(stderr, "[i6_aenc] Failed to acquire symbol MI_AI_SetVqeVolume!\n");
        return EXIT_FAILURE;
    }

    if (!(aenc_lib->fnFreeFrame = (int(*)(int device, int channel, i6_aenc_frm *frame, i6_aenc_efrm *encFrame))
        dlsym(aenc_lib->handle, "MI_AI_ReleaseFrame"))) {
        fprintf(stderr, "[i6_aenc] Failed to acquire symbol MI_AI_ReleaseFrame!\n");
        return EXIT_FAILURE;
    }

    if (!(aenc_lib->fnGetFrame = (int(*)(int device, int channel, i6_aenc_frm *frame, i6_aenc_efrm *encFrame, int millis))
        dlsym(aenc_lib->handle, "MI_AI_GetFrame"))) {
        fprintf(stderr, "[i6_aenc] Failed to acquire symbol MI_AI_GetFrame!\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

static void i6_aenc_unload(i6_aenc_impl *aenc_lib) {
    if (aenc_lib->handle)
        dlclose(aenc_lib->handle = NULL);
    memset(aenc_lib, 0, sizeof(*aenc_lib));
}
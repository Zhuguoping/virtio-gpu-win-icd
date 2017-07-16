#pragma once

#include "win_types.h"

enum virtio_gpu_ctrl_type {
	VIRTIO_GPU_UNDEFINED = 0,

	/* 2d commands */
	VIRTIO_GPU_CMD_GET_DISPLAY_INFO = 0x0100,
	VIRTIO_GPU_CMD_RESOURCE_CREATE_2D,
	VIRTIO_GPU_CMD_RESOURCE_UNREF,
	VIRTIO_GPU_CMD_SET_SCANOUT,
	VIRTIO_GPU_CMD_RESOURCE_FLUSH,
	VIRTIO_GPU_CMD_TRANSFER_TO_HOST_2D,
	VIRTIO_GPU_CMD_RESOURCE_ATTACH_BACKING,
	VIRTIO_GPU_CMD_RESOURCE_DETACH_BACKING,
	VIRTIO_GPU_CMD_GET_CAPSET_INFO,
	VIRTIO_GPU_CMD_GET_CAPSET,

	/* 3d commands */
	VIRTIO_GPU_CMD_CTX_CREATE = 0x0200,
	VIRTIO_GPU_CMD_CTX_DESTROY,
	VIRTIO_GPU_CMD_CTX_ATTACH_RESOURCE,
	VIRTIO_GPU_CMD_CTX_DETACH_RESOURCE,
	VIRTIO_GPU_CMD_RESOURCE_CREATE_3D,
	VIRTIO_GPU_CMD_TRANSFER_TO_HOST_3D,
	VIRTIO_GPU_CMD_TRANSFER_FROM_HOST_3D,
	VIRTIO_GPU_CMD_SUBMIT_3D,

	/* cursor commands */
	VIRTIO_GPU_CMD_UPDATE_CURSOR = 0x0300,
	VIRTIO_GPU_CMD_MOVE_CURSOR,

	/* success responses */
	VIRTIO_GPU_RESP_OK_NODATA = 0x1100,
	VIRTIO_GPU_RESP_OK_DISPLAY_INFO,
	VIRTIO_GPU_RESP_OK_CAPSET_INFO,
	VIRTIO_GPU_RESP_OK_CAPSET,

	/* error responses */
	VIRTIO_GPU_RESP_ERR_UNSPEC = 0x1200,
	VIRTIO_GPU_RESP_ERR_OUT_OF_MEMORY,
	VIRTIO_GPU_RESP_ERR_INVALID_SCANOUT_ID,
	VIRTIO_GPU_RESP_ERR_INVALID_RESOURCE_ID,
	VIRTIO_GPU_RESP_ERR_INVALID_CONTEXT_ID,
	VIRTIO_GPU_RESP_ERR_INVALID_PARAMETER,

	/* custom */
	VIRTIO_GPU_CMD_API_FORWARDING,
	VIRTIO_GPU_CMD_SHOW_DEBUG,
};
#define VIRTIO_GPU_EVENT_DISPLAY (1 << 0)

enum virtio_gpu_formats {
    VIRTIO_GPU_FORMAT_B8G8R8A8_UNORM  = 1,
    VIRTIO_GPU_FORMAT_B8G8R8X8_UNORM  = 2,
    VIRTIO_GPU_FORMAT_A8R8G8B8_UNORM  = 3,
    VIRTIO_GPU_FORMAT_X8R8G8B8_UNORM  = 4,

    VIRTIO_GPU_FORMAT_R8G8B8A8_UNORM  = 67,
    VIRTIO_GPU_FORMAT_X8B8G8R8_UNORM  = 68,

    VIRTIO_GPU_FORMAT_A8B8G8R8_UNORM  = 121,
    VIRTIO_GPU_FORMAT_R8G8B8X8_UNORM  = 134,
};

enum virtio_gpu_3D_cmd {
   VIRGL_CCMD_NOP = 0,
   VIRGL_CCMD_CREATE_OBJECT = 1,
   VIRGL_CCMD_BIND_OBJECT,
   VIRGL_CCMD_DESTROY_OBJECT,
   VIRGL_CCMD_SET_VIEWPORT_STATE,
   VIRGL_CCMD_SET_FRAMEBUFFER_STATE,
   VIRGL_CCMD_SET_VERTEX_BUFFERS,
   VIRGL_CCMD_CLEAR,
   VIRGL_CCMD_DRAW_VBO,
   VIRGL_CCMD_RESOURCE_INLINE_WRITE,
   VIRGL_CCMD_SET_SAMPLER_VIEWS,
   VIRGL_CCMD_SET_INDEX_BUFFER,
   VIRGL_CCMD_SET_CONSTANT_BUFFER,
   VIRGL_CCMD_SET_STENCIL_REF,
   VIRGL_CCMD_SET_BLEND_COLOR,
   VIRGL_CCMD_SET_SCISSOR_STATE,
   VIRGL_CCMD_BLIT,
   VIRGL_CCMD_RESOURCE_COPY_REGION,
   VIRGL_CCMD_BIND_SAMPLER_STATES,
   VIRGL_CCMD_BEGIN_QUERY,
   VIRGL_CCMD_END_QUERY,
   VIRGL_CCMD_GET_QUERY_RESULT,
   VIRGL_CCMD_SET_POLYGON_STIPPLE,
   VIRGL_CCMD_SET_CLIP_STATE,
   VIRGL_CCMD_SET_SAMPLE_MASK,
   VIRGL_CCMD_SET_STREAMOUT_TARGETS,
   VIRGL_CCMD_SET_RENDER_CONDITION,
   VIRGL_CCMD_SET_UNIFORM_BUFFER,

   VIRGL_CCMD_SET_SUB_CTX,
   VIRGL_CCMD_CREATE_SUB_CTX,
   VIRGL_CCMD_DESTROY_SUB_CTX,
   VIRGL_CCMD_BIND_SHADER,
};

enum virgl_object_type {
    VIRGL_OBJECT_NULL,
    VIRGL_OBJECT_BLEND,
    VIRGL_OBJECT_RASTERIZER,
    VIRGL_OBJECT_DSA,
    VIRGL_OBJECT_SHADER,
    VIRGL_OBJECT_VERTEX_ELEMENTS,
    VIRGL_OBJECT_SAMPLER_VIEW,
    VIRGL_OBJECT_SAMPLER_STATE,
    VIRGL_OBJECT_SURFACE,
    VIRGL_OBJECT_QUERY,
    VIRGL_OBJECT_STREAMOUT_TARGET,
    VIRGL_MAX_OBJECTS,
};

#pragma pack(1)
typedef struct virtio_gpu_ctrl_hdr {
    ULONG type;
    ULONG flags;
    ULONGLONG fence_id;
    ULONG ctx_id;
    ULONG padding;
}GPU_CTRL_HDR, *PGPU_CTRL_HDR;
#pragma pack()

/* VIRTIO_GPU_CMD_RESOURCE_CREATE_2D: create a 2d resource with a format */
#pragma pack(1)
typedef struct virtio_gpu_resource_create_2d {
    GPU_CTRL_HDR hdr;
    ULONG resource_id;
    ULONG format;
    ULONG width;
    ULONG height;
}GPU_RES_CREATE_2D, *PGPU_RES_CREATE_2D;
#pragma pack()

/* VIRTIO_GPU_CMD_RESOURCE_CREATE_3D: create a 3d resource with a format */
#pragma pack(1)
typedef struct virtio_gpu_resource_create_3d {
    GPU_CTRL_HDR hdr;
    ULONG resource_id;
    ULONG target;
    ULONG format;
    ULONG bind;
    ULONG width;
    ULONG height;
    ULONG depth;
    ULONG array_size;
    ULONG last_level;
    ULONG nr_samples;
    ULONG flags;
    ULONG padding;
}GPU_RES_CREATE_3D, *PGPU_RES_CREATE_3D;
#pragma pack()

/* VIRTIO_GPU_CMD_CTX_ATTACH_RESOURCE: attach a resource to a context*/
#pragma pack(1)
typedef struct virtio_gpu_resource_attach {
    GPU_CTRL_HDR hdr;
    ULONG resource_id;
    ULONG padding;
}GPU_RES_ATTACH, *PGPU_RES_ATTACH;
#pragma pack()

/* VIRTIO_GPU_CMD_RESOURCE_ATTACH_BACKING */
#pragma pack(1)
typedef struct virtio_gpu_resource_attach_backing {
    GPU_CTRL_HDR hdr;
    ULONG resource_id;
    ULONG nr_entries;
}GPU_RES_ATTACH_BACKING, *PGPU_RES_ATTACH_BACKING;
#pragma pack()

/* VIRTIO_GPU_CMD_SHOW_DEBUG */
#pragma pack(1)
#define SHOWDEBUG_SIZE 255
typedef struct virtio_gpu_show_debug {
    GPU_CTRL_HDR hdr;
    CHAR message[SHOWDEBUG_SIZE];
}GPU_SHOWDEBUG, *PGPU_SHOWDEBUG;
#pragma pack()

/* VIRTIO_GPU_CMD_CTX_CREATE */
#pragma pack(1)
typedef struct virtio_gpu_ctx_create {
    GPU_CTRL_HDR hdr;
	UINT32 nlen;
    UINT32 padding;
	char debug_name[64];
}GPU_CTX_CREATE, *PGPU_CTX_CREATE;
#pragma pack()

/* VIRTIO_GPU_CMD_CTX_DESTROY */
#pragma pack(1)
typedef struct virtio_gpu_ctx_destroy {
    GPU_CTRL_HDR hdr;
}GPU_CTX_DESTROY, *PGPU_CTX_DESTROY;
#pragma pack()

/* VIRTIO_GPU_CMD_SUBMIT_3D */
#pragma pack(1)
typedef struct virtio_gpu_submit_3d {
    GPU_CTRL_HDR hdr;
    UINT32 size;
    UINT32 padding;
}GPU_SUBMIT_3D, *PGPU_SUBMIT_3D;
#pragma pack()
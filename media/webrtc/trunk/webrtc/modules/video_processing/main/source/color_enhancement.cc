/*
 *  Copyright (c) 2011 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include <stdlib.h>  // NULL

#include "webrtc/modules/video_processing/main/source/color_enhancement.h"
#include "webrtc/modules/video_processing/main/source/color_enhancement_private.h"
#include "webrtc/system_wrappers/interface/trace.h"

namespace webrtc {

namespace VideoProcessing
{ 
    int32_t
    ColorEnhancement(I420VideoFrame* frame)
    {
        assert(frame);
        // pointers to U and V color pixels
        uint8_t* ptrU;
        uint8_t* ptrV;
        uint8_t tempChroma;

        if (frame->IsZeroSize())
        {
            WEBRTC_TRACE(webrtc::kTraceError, webrtc::kTraceVideoPreocessing,
                         -1, "Null frame pointer");
            return VPM_GENERAL_ERROR;
        }

        if (frame->width() == 0 || frame->height() == 0)
        {
            WEBRTC_TRACE(webrtc::kTraceError, webrtc::kTraceVideoPreocessing,
                         -1, "Invalid frame size");
            return VPM_GENERAL_ERROR;
        }

        // set pointers to first U and V pixels (skip luminance)
        ptrU = frame->buffer(kUPlane);
        ptrV = frame->buffer(kVPlane);
        int size_uv = ((frame->width() + 1) / 2) * ((frame->height() + 1) / 2);

        // loop through all chrominance pixels and modify color
        for (int ix = 0; ix < size_uv; ix++)
        {
            tempChroma = colorTable[*ptrU][*ptrV];
            *ptrV = colorTable[*ptrV][*ptrU];
            *ptrU = tempChroma;
            
            // increment pointers
            ptrU++;
            ptrV++;
        }
        return VPM_OK;
    }

}  // namespace

}  // namespace webrtc

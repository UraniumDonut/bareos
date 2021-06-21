/*
 * Copyright (C) 2020-2021 Bareos GmbH & Co. KG
 * Copyright (C) 2010 SCALITY SA. All rights reserved.
 * http://www.scality.com
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY SCALITY SA ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL SCALITY SA OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation
 * are those of the authors and should not be interpreted as representing
 * official policies, either expressed or implied, of SCALITY SA.
 *
 * https://github.com/scality/Droplet
 */
#ifndef BAREOS_DROPLET_LIBDROPLET_INCLUDE_DROPLET_SPROXYD_REQBUILDER_H_
#define BAREOS_DROPLET_LIBDROPLET_INCLUDE_DROPLET_SPROXYD_REQBUILDER_H_

typedef enum
{
  DPL_SPROXYD_REQ_MD_ONLY = (1u << 0),
  DPL_SPROXYD_REQ_CONSISTENT = (1u << 1),
  DPL_SPROXYD_REQ_EXPECT_VERSION = (1u << 2),
  DPL_SPROXYD_REQ_FORCE_VERSION = (1u << 3),
} dpl_sproxyd_req_mask_t;

/* PROTO reqbuilder.c */
/* src/reqbuilder.c */
dpl_status_t dpl_sproxyd_req_build(const dpl_req_t* req,
                                   dpl_sproxyd_req_mask_t req_mask,
                                   uint32_t force_version,
                                   dpl_dict_t** headersp);
#endif  // BAREOS_DROPLET_LIBDROPLET_INCLUDE_DROPLET_SPROXYD_REQBUILDER_H_
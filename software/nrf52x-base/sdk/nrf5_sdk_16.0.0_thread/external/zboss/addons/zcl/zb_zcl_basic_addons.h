/**
 * Copyright (c) 2019 - 2020, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef SDK_NRF5_EXTERNAL_ZBOSS_ADDONS_ZCL_ZB_ZCL_BASIC_ADDONS_H_
#define SDK_NRF5_EXTERNAL_ZBOSS_ADDONS_ZCL_ZB_ZCL_BASIC_ADDONS_H_

#include "sdk_config.h"
#include "zboss_api.h"

/*! \addtogroup zb_zcl_basic_addons */
/*! @{ */

/** @brief Basic cluster attributes according to ZCL Spec 3.2.2.2 */
typedef struct
{
    zb_uint8_t zcl_version;
    zb_uint8_t app_version;
    zb_uint8_t stack_version;
    zb_uint8_t hw_version;
    zb_char_t  mf_name[32];
    zb_char_t  model_id[32];
    zb_char_t  date_code[16];
    zb_uint8_t power_source;
    zb_char_t  location_id[15];
    zb_uint8_t ph_env;
    zb_char_t  sw_ver[17];
} zb_zcl_basic_attrs_ext_t;

/** @} */

#endif /* SDK_NRF5_EXTERNAL_ZBOSS_ADDONS_ZCL_ZB_ZCL_BASIC_ADDONS_H_ */

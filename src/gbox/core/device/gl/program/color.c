/*!The Graphic Box Library
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * Copyright (C) 2009 - 2017, TBOOX Open Source Group.
 *
 * @author      ruki
 * @file        color.c
 * @ingroup     core
 *
 */

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementation
 */
gb_gl_program_ref_t gb_gl_program_init_color()
{
    // the vertex shader
    static tb_char_t const* vshader = 
#if defined(TB_CONFIG_OS_IOS) || defined(TB_CONFIG_OS_ANDROID)
        "precision mediump float;                                               \n"
#endif
        "                                                                       \n"
        "attribute vec4 aColor;                                                 \n"
        "attribute vec4 aVertices;                                              \n"
        "                                                                       \n"
        "varying vec4 vColors;                                                  \n"
        "uniform mat4 uMatrixModel;                                             \n"
        "uniform mat4 uMatrixProject;                                           \n"
        "                                                                       \n"
        "void main()                                                            \n"
        "{                                                                      \n"
        "   vColors = aColor;                                                   \n"  
        "   gl_Position = uMatrixProject * uMatrixModel * aVertices;            \n"
        "}                                                                      \n";
    
    // the fragment shader
    static tb_char_t const* fshader = 
#if defined(TB_CONFIG_OS_IOS) || defined(TB_CONFIG_OS_ANDROID)
        "precision mediump float;                                               \n"
#endif
        "                                                                       \n"
        "varying vec4 vColors;                                                  \n"
        "                                                                       \n"
        "void main()                                                            \n"
        "{                                                                      \n"
        "   gl_FragColor = vColors;                                             \n"
        "}                                                                      \n";


    // init program
    gb_gl_program_ref_t program = gb_gl_program_init(GB_GL_PROGRAM_TYPE_COLOR, vshader, fshader);
    tb_assert_and_check_return_val(program, tb_null);

    // init location
    gb_gl_program_location_set(program, GB_GL_PROGRAM_LOCATION_COLORS,          gb_gl_program_attr(program, "aColor"));  //!< FIXME some name can not work for mac, .e.g aColors aColorx ...
    gb_gl_program_location_set(program, GB_GL_PROGRAM_LOCATION_VERTICES,        gb_gl_program_attr(program, "aVertices"));
    gb_gl_program_location_set(program, GB_GL_PROGRAM_LOCATION_MATRIX_MODEL,    gb_gl_program_unif(program, "uMatrixModel"));
    gb_gl_program_location_set(program, GB_GL_PROGRAM_LOCATION_MATRIX_PROJECT,  gb_gl_program_unif(program, "uMatrixProject"));

    // ok
    return program;
}


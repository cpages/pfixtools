/****************************************************************************/
/*          pfixtools: a collection of postfix related tools                */
/*          ~~~~~~~~~                                                       */
/*  ______________________________________________________________________  */
/*                                                                          */
/*  Redistribution and use in source and binary forms, with or without      */
/*  modification, are permitted provided that the following conditions      */
/*  are met:                                                                */
/*                                                                          */
/*  1. Redistributions of source code must retain the above copyright       */
/*     notice, this list of conditions and the following disclaimer.        */
/*  2. Redistributions in binary form must reproduce the above copyright    */
/*     notice, this list of conditions and the following disclaimer in      */
/*     the documentation and/or other materials provided with the           */
/*     distribution.                                                        */
/*  3. The names of its contributors may not be used to endorse or promote  */
/*     products derived from this software without specific prior written   */
/*     permission.                                                          */
/*                                                                          */
/*  THIS SOFTWARE IS PROVIDED BY THE CONTRIBUTORS ``AS IS'' AND ANY         */
/*  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE       */
/*  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR      */
/*  PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE CONTRIBUTORS BE LIABLE   */
/*  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR            */
/*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF    */
/*  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR         */
/*  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,   */
/*  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE    */
/*  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,       */
/*  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                      */
/*                                                                          */
/*   Copyright (c) 2006-2014 the Authors                                    */
/*   see AUTHORS and source files for details                               */
/****************************************************************************/

#ifndef PFIXTOOLS_CONFIG_H
#define PFIXTOOLS_CONFIG_H

#include "filter.h"

typedef struct config_t config_t;

struct config_t {
    /* SOURCE */
    /* Root configuration file.
     */
    const char *filename;

    /* Parameters.
     */
    A(filter_param_t)  params;


    /* INTERPRETED */
    /* Filters.
     */
    A(filter_t) filters;

    /* Entry point of the filters.
     * (one per smtp state)
     */
    int entry_points[SMTP_count];

    /* Port on which the program have to bind to.
     * The parameter from CLI override the parameter from configuration file.
     */
    uint16_t port;
    bool port_present;
    char *socketfile;

    /* Log message.
     */
    char *log_format;

    /* Resolv.conf to use
     */
    char *resolv_conf;

    /* Include the explanation from the filter in answer message if available.
     */
    bool include_explanation;
};

#define DEFAULT_LOG_FORMAT                                                   \
    "request client=${client_name}[${client_address}] from=<${sender}> "     \
    "to=<${recipient}> at ${protocol_state}"

__attribute__((nonnull(1)))
config_t *config_read(const char *file);

__attribute__((nonnull(1)))
bool config_check(const char *file);

__attribute__((nonnull(1)))
bool config_reload(config_t *config);

void config_delete(config_t **config);

#endif

/* vim:set et sw=4 sts=4 sws=4: */

#ifndef _NGX_HTTP_JSON_ENV_MODULE_H_INCLUDED_
#define _NGX_HTTP_JSON_ENV_MODULE_H_INCLUDED_

#define NGX_HTTP_JSON_ENV_MODULE_VERSION "0.1"

static char *ngx_http_json_env(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
static ngx_uint_t response_size();

#endif

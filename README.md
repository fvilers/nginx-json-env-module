# nginx-json-env-module

A NGINX module to expose environment variables as JSON

## Introduction

This module allows a NGINX location context to expose allowed environment variables as JSON. This is mainly useful for containerized applications served as static assets (React, Angular, etc.).

## Installation

1. Configure NGINX by adding the module using Autotools

```
./configure --with-compat --add-dynamic-module=/path/to/nginx-json-env-module
```

2. Build NGINX and the modules

```
make && make modules
```

3. Configure the module by allowing specific environment variables and by using the `json_env` directive in the location context

```
env FOO;

load_module modules/ngx_http_json_env_module.so;

http {
    server {
      location /env {
        json_env;
      }
    }
}
```

## Docker

Here's a sample `Dockerfile` that can be used to build a NGINX docker image that includes the module.

```
FROM gcc:4.9 as builder
WORKDIR /usr/src
RUN wget https://nginx.org/download/nginx-1.19.4.tar.gz
RUN tar -xzvf nginx-1.19.4.tar.gz
RUN git clone --depth 1 --branch 0.1.0 https://github.com/fvilers/nginx-json-env-module.git
RUN cd nginx-1.19.4/ \
  && ./configure --with-compat --add-dynamic-module=../nginx-json-env-module/src \
  && make modules

FROM nginx:1.19.4
COPY nginx.conf /etc/nginx
COPY --from=builder /usr/src/nginx-1.19.4/objs/ngx_http_json_env_module.so /etc/nginx/modules
EXPOSE 80

```

## Usage

Set your environment variables, for example with the `FOO` variable set to `bar` value and issue a `GET` request to the configured location :

```
$ curl -i http://localhost:8080/env
```

```
HTTP/1.1 200 OK
Server: nginx/1.19.4
Date: Sat, 21 Nov 2020 13:04:16 GMT
Content-Type: application/json; charset=utf-8
Content-Length: 13
Connection: keep-alive

{"FOO":"bar"}
```

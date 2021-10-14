#!/bin/bash
docker run --rm -v $(pwd)/test.lua:/etc/foo.lua -v $(pwd)/lib.so:/usr/local/lib/lua/5.3/lib.so -v $(pwd)/haproxy.cfg:/usr/local/etc/haproxy/haproxy.cfg -p 13377:80 haproxy

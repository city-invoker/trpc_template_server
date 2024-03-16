#!/bin/sh

b=`ps aux | grep trpc_cpp | grep -v color=auto | awk '{print $2}'`
echo ${b}

#!/bin/sh

server_name="trpc_template_server"
pid=`ps aux | grep ${server_name} | grep -v grep | awk '{print $2}'`
if [ -n "${pid}" ]; then
  echo "single instance server ${server_name} already running..." 
  exit 0
fi
dir=$(dirname "$0")
../bin/${server_name} --config=../conf/trpc_cpp_fiber.yaml &

pid=`ps aux | grep ${server_name} | grep -v grep | awk '{print $2}'`
if [ -z "${pid}" ]; then
  echo "start ${server_name} failed!" 
else
  echo "start ${server_name} succ."
fi


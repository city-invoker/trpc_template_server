#!/bin/sh

dir=$(dirname "$0")
server_name="trpc_template_server"
pid=`ps aux | grep ${server_name} | grep -v grep | awk '{print $2}'`
if [ -z "${pid}" ]; then
  echo "${server_name} not running." 
  exit 0
fi

kill -9 ${pid}

pid=`ps aux | grep ${server_name} | grep -v grep | awk '{print $2}'`
if [ -n "${pid}" ]; then
  echo "stop ${server_name} failed!" 
else
  echo "stop ${server_name} succ."
fi


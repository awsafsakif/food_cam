#!/bin/sh
sleep 5;
echo 'starting freefood';
(sudo python ./freefood.py& sudo ./foodButton)&

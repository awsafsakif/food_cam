#!/bin/sh
sleep 5;
echo 'starting freefood';
(sudo python /home/pi/Desktop/freefood/freefood.py& sudo /home/pi/Desktop/freefood/foodButton)&

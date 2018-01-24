import os
import time
import sys
import freeFoodUtils

os.system("echo '%s button pressed' >> ./log.txt" %time.strftime("%a, %d %b %Y %H:%M%S", time.gmtime()))

freeFoodUtils.removeOldPictures()
path=freeFoodUtils.takepicture()
print "Picture path is = %s" %path
freeFoodUtils.sendEmail(path)	

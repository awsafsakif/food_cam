import os
import time
import sys
import threading
import PIL
from PIL import Image
import smtplib
from email.mime.image import MIMEImage
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart

global email, intervalPicture, intervalRemove, emailContent, picturesPath

file = open("./settings.txt").readlines()
#print file
email = ""
intervalPicture = ""
intervalRemove = ""
for x in file:
	param = x.split("=")[0]
	setting = x.split("=")[1][:-1]
	if param == "email":
		email = setting
	elif param == "intervalPicture":
		intervalPicture = setting
	elif param == "intervalRemove":
		intervalRemove = setting
	elif param == "emailContent":
		emailContent = setting
	elif param == "picturesPath":
		picturesPath = setting
text="welcome to DGP"

def takepicture():
	global picturesPath
        pic =picturesPath + str(time.time())
	#os.system("echo '%s taking a picture' >> ./log.txt" %time.strftime("%a, %d %b %Y %H:%M:%S", time.gmtime()))
	os.system("sudo fswebcam -F 50 -r 640x480 -q --set brightness=25%% --no-banner --no-timestamp %s.jpeg" %(pic))
	return pic
	
def removeOldPictures():
	global picturesPath
	#os.system("echo '%s removing pictures' >> ./log.txt" %time.strftime("%a, %d %b %Y %H:%M:%S", time.gmtime()))
	os.system("sudo rm %s*" %picturesPath)
	os.system("sudo find %s. -name \'*.jpeg\' -print0 |sudo xargs -0 rm" %picturesPath)


def sendEmail(pic):
	global email
	print "picture path= %s" %pic
	msg =  MIMEMultipart()
        msg['Subject']='Free Food'
        msg['From']='FreeFoodButton@dgp.toronto.edu'
        msg['To']=email
        body="""There is Free food in the DGP lounge!

 To see what is left right now go to http://freefood.cs.toronto.edu/.

Attachment shows what it looked like when the message was sent."""
        msg.attach(MIMEText(body, 'plain'))	
	#path=pic
	foo=Image.open("%s.jpeg"%(pic)) 
	foo=foo.resize((320,240),Image.ANTIALIAS)
	foo.save("sent.jpeg",quality=95)
        attachfile=open("sent.jpeg", 'rb')
        foodimage=MIMEImage(attachfile.read())
        msg.attach(foodimage)
	os.system("echo '%s sending email' >> ./log.txt" %time.strftime("%a, %d %b %Y %H:%M:%S", time.gmtime()))
	sender = smtplib.SMTP('mail.dgp.toronto.edu')
	sender.login('dgpinfo', 'freeamiga')
        sender.sendmail("FreeFoodButton@dgp.toronto.edu",email, msg.as_string())
  	sender.quit()	
	
def takePictureLoop():
	global intervalPicture
	val=takepicture()
	picTimer = threading.Timer(int(intervalPicture), takePictureLoop)
	picTimer.start()
	return picTimer

def removeOldPicturesLoop():
	global intervalRemove
	removeOldPictures()
	rmTimer = threading.Timer(int(intervalRemove), removeOldPicturesLoop)
	rmTimer.start()
	return rmTimer



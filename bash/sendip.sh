#!/bin/bash

sleep 200

IP=`wget -O - http://checkip.dyndns.org/ | grep -i 'Current IP Address:'  | awk {'print $6'} | awk -F '<' {'print $1'}`

telnet out.alice.it 25 <<_EOF
HELO out.alice.it
MAIL FROM:<bleish@alice.it>
RCPT TO:<bleish@gmail.com>
DATA
From: Bleish <bleish@alice.it>
To: Bleish <bleish@gmail.com>
Subject: myinfo

$IP

.
QUIT
_EOF

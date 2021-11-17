#!/bin/bash
date>> traceroute.txt

traceroute -I flipkart.com >> traceroute.txt 
traceroute -I programmingwithmosh.com >> traceroute.txt
traceroute -I udp.jp >> traceroute.txt
traceroute -I gunjap.net >> traceroute.txt
traceroute -I amazon.com >> traceroute.txt
traceroute -I yuppiechef.com >> traceroute.txt
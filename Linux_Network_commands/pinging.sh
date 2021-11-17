#!/bin/bash
ping -c 25 flipkart.com | grep rtt >> ping_results.txt
ping -c 25 programmingwithmosh.com  | grep rtt >> ping_results.txt
ping -c 25 udp.jp  | grep rtt >> ping_results.txt
ping -c 25 gunjap.net  | grep rtt >> ping_results.txt
ping -c 25 amazon.com  | grep rtt >> ping_results.txt
ping -c 25 yuppiechef.com  | grep rtt >> ping_results.txt

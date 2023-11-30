#bundle exec jekyll serve -H 0.0.0.0
# Get eth0 IP address
IPADDR=`hostname -I | cut -f1 -d' '`
bundle exec jekyll serve -H $IPADDR --port 4000

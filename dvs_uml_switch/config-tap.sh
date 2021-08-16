if [ $# -eq 0 ]
  then
    echo "./config-tap <if> <ip>"
    exit 1
fi

tunctl -u root -t HTAP
brctl addbr bridge1

ifconfig HTAP 0.0.0.0 up
ifconfig $1 $2 up

brctl addif bridge1 HTAP
brctl addif bridge1 $1
brctl show


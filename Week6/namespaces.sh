set -eE -o functrace

failure() {
  local lineno=$1
  local msg=$2
  echo "Failed at $lineno: $msg"
}
trap 'failure ${LINENO} "$BASH_COMMAND"' ERR






# delete namespaces
sudo ip netns delete l1
sudo ip netns delete l2
sudo ip netns delete l3
sudo ip netns delete r1
sudo ip netns delete r2
sudo ip netns delete r3
sudo ip netns delete b1
sudo ip netns delete b2

echo "namespace deleted"

#delete veth pairs
# sudo ip link delete l1b1
# sudo ip link delete l2b1
# sudo ip link delete l3b1
# sudo ip link delete b1b2
# sudo ip link delete r1b2
# sudo ip link delete r2b2
# sudo ip link delete r3b3

# echo "veth pairs deleted"


# create namespaces
sudo ip netns add l1
sudo ip netns add l2
sudo ip netns add l3

sudo ip netns add r1
sudo ip netns add r2
sudo ip netns add r3

sudo ip netns add b1
sudo ip netns add b2

echo "Namespaces created"

# create veth pairs
sudo ip link add l1b1 type veth peer name b1l1
sudo ip link add l2b1 type veth peer name b1l2
sudo ip link add l3b1 type veth peer name b1l3

sudo ip link add b1b2 type veth peer name b2b1

sudo ip link add r1b2 type veth peer name b2r1
sudo ip link add r2b2 type veth peer name b2r2
sudo ip link add r3b2 type veth peer name b2r3

echo "veth pairs created"

# assign veth pairs
sudo ip link set l1b1 netns l1
sudo ip link set l2b1 netns l2
sudo ip link set l3b1 netns l3

sudo ip link set b1l1 netns b1
sudo ip link set b1l2 netns b1
sudo ip link set b1l3 netns b1

sudo ip link set b1b2 netns b1
sudo ip link set b2b1 netns b2
sudo ip link set b2r1 netns b2
sudo ip link set b2r2 netns b2
sudo ip link set b2r3 netns b2
sudo ip link set r1b2 netns r1
sudo ip link set r2b2 netns r2
sudo ip link set r3b2 netns r3

echo "veth pairs assign"

# bring loopback interface up
sudo ip netns exec l1 ip link set lo up
sudo ip netns exec l2 ip link set lo up
sudo ip netns exec l3 ip link set lo up

sudo ip netns exec b1 ip link set lo up
sudo ip netns exec b2 ip link set lo up

sudo ip netns exec r1 ip link set lo up
sudo ip netns exec r2 ip link set lo up
sudo ip netns exec r3 ip link set lo up

echo "brought loopback interface up"

# bring interfaces within namespaces up

sudo ip netns exec l1 ip link set l1b1 up
sudo ip netns exec l2 ip link set l2b1 up
sudo ip netns exec l3 ip link set l3b1 up

sudo ip netns exec b1 ip link set b1l1 up
sudo ip netns exec b1 ip link set b1l2 up
sudo ip netns exec b1 ip link set b1l3 up
sudo ip netns exec b1 ip link set b1b2 up

sudo ip netns exec b2 ip link set b2b1 up
sudo ip netns exec b2 ip link set b2r1 up
sudo ip netns exec b2 ip link set b2r2 up
sudo ip netns exec b2 ip link set b2r3 up

sudo ip netns exec r1 ip link set r1b2 up
sudo ip netns exec r2 ip link set r2b2 up
sudo ip netns exec r3 ip link set r3b2 up

echo "Brought interfaces within namespaces up"

# assign ip address

sudo ip netns exec l1 ip address add 10.0.1.1/24 dev l1b1
sudo ip netns exec b1 ip address add 10.0.1.2/24 dev b1l1 
sudo ip netns exec l2 ip address add 10.0.2.1/24 dev l2b1 
sudo ip netns exec b1 ip address add 10.0.2.2/24 dev b1l2 
sudo ip netns exec l3 ip address add 10.0.3.1/24 dev l3b1 
sudo ip netns exec b1 ip address add 10.0.3.2/24 dev b1l3

sudo ip netns exec b1 ip address add 10.0.4.1/24 dev b1b2
sudo ip netns exec b2 ip address add 10.0.4.2/24 dev b2b1

sudo ip netns exec r1 ip address add 10.0.5.1/24 dev r1b2
sudo ip netns exec b2 ip address add 10.0.5.2/24 dev b2r1 
sudo ip netns exec r2 ip address add 10.0.6.1/24 dev r2b2 
sudo ip netns exec b2 ip address add 10.0.6.2/24 dev b2r2 
sudo ip netns exec r3 ip address add 10.0.7.1/24 dev r3b2 
sudo ip netns exec b2 ip address add 10.0.7.2/24 dev b2r3

echo "Ip addresses assign"

#add gateway

sudo ip netns exec l1 ip route add default via 10.0.1.2 dev l1b1
sudo ip netns exec l2 ip route add default via 10.0.2.2 dev l2b1
sudo ip netns exec l3 ip route add default via 10.0.3.2 dev l3b1

sudo ip netns exec b1 ip route add default via 10.0.4.2 dev b1b2
sudo ip netns exec b2 ip route add default via 10.0.4.1 dev b2b1

sudo ip netns exec r1 ip route add default via 10.0.5.2 dev r1b2
sudo ip netns exec r2 ip route add default via 10.0.6.2 dev r2b2
sudo ip netns exec r3 ip route add default via 10.0.7.2 dev r3b2

# enable ip forwarding

sudo ip netns exec b1 sysctl -w net.ipv4.ip_forward=1
sudo ip netns exec b2 sysctl -w net.ipv4.ip_forward=1

echo "Ip ip forwarding enable"

# ping  2 packets

sudo ip netns exec l1 ping 10.0.5.1 -c 2
sudo ip netns exec l1 ping 10.0.6.1 -c 2 
sudo ip netns exec l1 ping 10.0.7.1 -c 2
sudo ip netns exec r1 ping 10.0.1.1 -c 2
sudo ip netns exec r1 ping 10.0.2.1 -c 2
sudo ip netns exec r1 ping 10.0.3.1 -c 2
sudo ip netns exec l1 ping 10.0.2.1 -c 2
sudo ip netns exec r1 ping 10.0.6.1 -c 2


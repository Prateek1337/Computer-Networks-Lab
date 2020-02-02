#Creating Topology with three namespaces as router's where 
#each router has single namespace attached



set -eE -o functrace

failure() {
  local lineno=$1
  local msg=$2
  echo "Failed at $lineno: $msg"
}
trap 'failure ${LINENO} "$BASH_COMMAND"' ERR

#deleteing namespaces
sudo ip netns delete l1
sudo ip netns delete m1
sudo ip netns delete r1
sudo ip netns delete b1
sudo ip netns delete b2
sudo ip netns delete b3

echo "Namespace deleted"
#creating namespaces

sudo ip netns add l1
sudo ip netns add m1
sudo ip netns add r1
sudo ip netns add b1
sudo ip netns add b2
sudo ip netns add b3

echo "Namespace created"
#creating veth pairs

sudo ip link add l1b1 type veth peer name b1l1
sudo ip link add m1b2 type veth peer name b2m1
sudo ip link add r1b3 type veth peer name b3r1

sudo ip link add b1b2 type veth peer name b2b1
sudo ip link add b2b3 type veth peer name b3b2

echo "Veth pairs created"
#assign veth pairs

sudo ip link set l1b1 netns l1
sudo ip link set m1b2 netns m1
sudo ip link set r1b3 netns r1

sudo ip link set b1l1 netns b1
sudo ip link set b2m1 netns b2
sudo ip link set b3r1 netns b3

sudo ip link set b1b2 netns b1
sudo ip link set b2b1 netns b2
sudo ip link set b2b3 netns b2
sudo ip link set b3b2 netns b3

echo "veth pair assign"

#set loopback ip

sudo ip netns exec l1 ip link set lo up
sudo ip netns exec m1 ip link set lo up
sudo ip netns exec r1 ip link set lo up
sudo ip netns exec b1 ip link set lo up
sudo ip netns exec b2 ip link set lo up
sudo ip netns exec b3 ip link set lo up

echo "loopback up done"

#set interface within namespaces up

sudo ip netns exec l1 ip link set l1b1 up
sudo ip netns exec r1 ip link set r1b3 up
sudo ip netns exec m1 ip link set m1b2 up

sudo ip netns exec b1 ip link set b1l1 up
sudo ip netns exec b2 ip link set b2m1 up
sudo ip netns exec b3 ip link set b3r1 up

sudo ip netns exec b1 ip link set b1b2 up
sudo ip netns exec b2 ip link set b2b1 up
sudo ip netns exec b2 ip link set b2b3 up
sudo ip netns exec b3 ip link set b3b2 up

echo "up interfaces"
#assign ip address
sudo ip netns exec l1 ip address add 10.0.1.1/24 dev l1b1
sudo ip netns exec m1 ip address add 10.0.2.1/24 dev m1b2
sudo ip netns exec r1 ip address add 10.0.3.1/24 dev r1b3

sudo ip netns exec b1 ip address add 10.0.1.2/24 dev b1l1
sudo ip netns exec b1 ip address add 10.0.4.1/24 dev b1b2

sudo ip netns exec b2 ip address add 10.0.4.2/24 dev b2b1
sudo ip netns exec b2 ip address add 10.0.2.2/24 dev b2m1
sudo ip netns exec b2 ip address add 10.0.5.1/24 dev b2b3

sudo ip netns exec b3 ip address add 10.0.3.2/24 dev b3r1
sudo ip netns exec b3 ip address add 10.0.5.2/24 dev b3b2

echo "ip address assign"
#add routing

sudo ip netns exec l1 ip route add default via 10.0.1.2 dev l1b1
sudo ip netns exec m1 ip route add default via 10.0.2.2 dev m1b2
sudo ip netns exec r1 ip route add default via 10.0.3.2 dev r1b3


sudo ip netns exec b1 ip route add default via 10.0.4.2 dev b1b2
# sudo ip netns exec b3 ip route add default via 10.0.5.1 dev b3b2

# sudo ip netns exec b2 ip route add 10.0.1.1 via 10.0.4.1 dev b2b1
# sudo ip netns exec b2 ip route add 10.0.2.1 via 10.0.5.2 dev b2b3

echo "routing added"

#enale ip forwarding

sudo ip netns exec b1 sysctl -w net.ipv4.ip_forward=1
sudo ip netns exec b2 sysctl -w net.ipv4.ip_forward=1
sudo ip netns exec b3 sysctl -w net.ipv4.ip_forward=1

echo "Ip forwarding enables"

#ping

sudo ip netns exec l1 ping 10.0.4.1 -c 2

#checking bandwidth 

echo "open new terminal and run iperf on b1"
sleep 30

echo ==================================================original bandwidth====================================================

sudo ip netns exec l1 iperf -c 10.0.4.1

#changing bandwidth

sudo ip netns exec l1 tc qdisc add dev l1b1 root tbf rate 1mbit burst 100mbit latency 1ms

echo ==================================================changed bandwidth====================================================

sudo ip netns exec l1 iperf -c 10.0.4.1

echo ==================================================Tcp streams bandwidth====================================================


sudo ip netns exec l1 iperf -c 10.0.4.1 -i 1 -P 2








# Hands On

## Ping a network namespace from the default namespace.
// create namespace
sudo ip netns add red

// Bring loopback interfaces up
sudo ip netns exec red ip link set lo up

//ping ip address
udo ip netns exec red ping 10.0.0.3

## Ping a network namespace from another network namespace.
// create namespace
sudo ip netns add red
sudo ip netns add blue

// Create veth pairs
sudo ip link add eth0 type veth peer name eth1

// Set the veth interfaces inside the namespaces
sudo ip link set eth0 netns red
sudo ip link set eth1 netns blue

// Bring loopback interfaces up
sudo ip netns exec red ip link set lo up
sudo ip netns exec blue ip link set lo up

// Bring up the interfaces within namespaces
sudo ip netns exec red ip link set eth0 up
sudo ip netns exec blue ip link set eth1 up

// Assign interfaces within namespaces IP addresses
sudo ip netns exec red ip address add 10.0.0.1/24 dev eth0
sudo ip netns exec blue ip address add 10.0.0.3/24 dev eth1

// Now ping, it works
sudo ip netns exec red ping 10.0.0.3
sudo ip netns exec blue ping 10.0.0.1

## ● Access the Internet from inside a network namespace (without moving any physical NIC
## interface inside it) by using:
## ○ A Linux bridge
## ○ Open vSwitch


// yet to be done

## Ping a network namespace from another network namespace via a Linux bridge.

// create namespace
sudo ip netns add red
sudo ip netns add blue

// Create veth pairs
sudo ip link add eth0 type veth peer name eth1
sudo ip link add eth2 type veth peer name eth3

// Set the veth interfaces inside the namespaces
sudo ip link set eth0 netns red
sudo ip link set eth2 netns blue

// Bring loopback interfaces up
sudo ip netns exec red ip link set lo up
sudo ip netns exec blue ip link set lo up

// Bring up the interfaces within namespaces
sudo ip netns exec red ip link set eth0 up
sudo ip netns exec blue ip link set eth2 up

// Assign interfaces within namespaces IP addresses
sudo ip netns exec red ip address add 10.0.0.1/24 dev eth0
sudo ip netns exec blue ip address add 10.0.0.3/24 dev eth1

// Create bridge using iproute package. Brctl is deprecated
sudo ip link add name br0 type bridge
sudo ip link set dev br0 up

// Set the other lose interfaces into the bridge
sudo ip link set eth1 master br0
sudo ip link set eth3 master br0

//Bring bridge interfaces up
sudo ip link set dev eth1 up
sudo ip link set dev eth3 up

// Now ping, it works
sudo ip netns exec red ping 10.0.0.3
sudo ip netns exec blue ping 10.0.0.1

## Ping a network namespace from another network namespace via a third network namespace.

// Create two namespaces
sudo ip netns add red
sudo ip netns add green

// Create three veth pairs
sudo ip link add eth0 type veth peer name eth1
sudo ip link add eth2 type veth peer name eth3

// Set them into the namespaces
sudo ip link set eth0 netns red
sudo ip link set eth2 netns green

// Bring them up
sudo ip netns exec red ip link set eth0 up
sudo ip netns exec green ip link set eth2 up

// Assign IP address to them (all different subnets)
sudo ip netns exec red ip address add 10.0.0.1/24 dev eth0
sudo ip netns exec green ip address add 10.0.2.1/24 dev eth2

// Create router namespace and add appropriate interfaces into it
sudo ip netns add router
sudo ip link set eth1 netns router
sudo ip link set eth3 netns router

// Bring the interface up
sudo ip netns exec router ip link set eth1 up
sudo ip netns exec router ip link set eth3 up

// Assign IP addresses to the interfaces within router
sudo ip netns exec router ip address add 10.0.0.2/24 dev eth1
sudo ip netns exec router ip address add 10.0.2.2/24 dev eth3

// Bring loopback interfaces up
sudo ip netns exec router ip link set lo up
sudo ip netns exec red ip link set lo up
sudo ip netns exec green ip link set lo up





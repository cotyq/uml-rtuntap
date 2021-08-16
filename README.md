# UML Remote ethernet driver

User Mode Linux remote ethernet driver

## Content

- um folder: correspond to /usr/src/linux/arch/um

- uml_switch folder: correspond to /usr/src/dvs/dvs-apps/uml_switch

## Virtual Machine configuration


## Start working with this code

Clone this code:

```
git clone https://github.com/cotyq/uml-rtuntap.git

cd uml-rtuntap
```


## Comparing VM and repo code.

Create a new branch in uml-rtuntap:

```
git switch -c # UML Remote ethernet driver

User Mode Linux remote ethernet driver

## Content

- um folder: correspond to /usr/src/linux/arch/um

- uml_switch folder: correspond to /usr/src/dvs/dvs-apps/uml_switch

## Virtual Machine configuration


## Start working with this code

Clone this code:

```
git clone https://github.com/cotyq/uml-rtuntap.git

cd uml-rtuntap
```


## Comparing VM and repo code.

Create a new branch in uml-rtuntap:

```
git switch -c update-vm
```

Mount the VM code in um and uml_switch folders:

```
sshfs -o nonempty root@192.168.1.2:/usr/src/linux/arch/um um

sshfs -o nonempty root@192.168.1.2:/usr/src/dvs/dvs-apps/uml_switch uml_switch
```

`update-vm` branch will contain VM code and `master` will contain git code.

To see the difference between VM and repo:

```
git diff --name-status master
```

## Updating VM code.

Following with the previos section instructions.

In case Virtual Machine code is out-of-date:



```

Mount the VM code in um and uml_switch folders:

```
sshfs -o nonempty root@192.168.1.2:/usr/src/linux/arch/um um

sshfs -o nonempty root@192.168.1.2:/usr/src/dvs/dvs-apps/uml_switch uml_switch
```

`update-vm` branch will contain VM code and `master` will contain git code.

To see the difference between VM and repo:

```
git diff --name-status master
```

## Updating VM code.

Following with the previos section instructions.

In case Virtual Machine code is out-of-date:

1. Commit your changes to `update-vm` branch.

```
git status
git add ...
git commit
```

2. Checkout to master branch. Due to um and uml_switch were mounted from VM, checkout changes will be automatically applied in the VM.

```
git checkout master
```


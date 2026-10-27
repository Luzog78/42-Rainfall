<div align="center">

```
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@                                                                              @
@  _____       _       ______    _ _                                           @
@ |  __ \     (_)     |  ____|  | | |                                          @
@ | |__) |__ _ _ _ __ | |__ __ _| | |                                          @
@ |  _  /  _` | | '_ \|  __/ _` | | |                       ___                @
@ | | \ \ (_| | | | | | | | (_| | | |                      | _ )_  _           @
@ |_|  \_\__,_|_|_| |_|_|  \__,_|_|_|                      | _ \ || | ysabik   @
@ Good luck & Have fun                                     |___/\_, | axdubois @
@                                                               |__/           @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
```

# 42 Cursus - Rainfall

<img src="https://cdn.jsdelivr.net/gh/devicons/devicon@latest/icons/ubuntu/ubuntu-original.svg" height="30" alt="ubuntu" />
<img width="12" />
<img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/bash/bash-original.svg" height="30" alt="bash" />
<img width="12" />
<img src="https://cdn.jsdelivr.net/gh/devicons/devicon@latest/icons/ssh/ssh-original.svg" height="30" alt="ssh" />

<br><br>

</div>


## Details


- **Summary:** *This project is an introduction to computer security. Rainfall will help you discover security in various sub-domains, with a developer-oriented approach. You will become familiar with several languages (ASM, Perl, Php, etc.), develop a certain logic to understand unknown programs, and become aware of problems related to simple programming errors.*
- **Author(s):** *[ysabik](https://profile.intra.42.fr/users/ysabik)*, *[axdubois](https://profile.intra.42.fr/users/axdubois)*
- **Public repo:** [GitHub](https://github.com/Luzog78/42-Rainfall)
- **Subject:** [en.subject.pdf *(v3.2)*](https://cdn.intra.42.fr/pdf/pdf/209996/en.subject.pdf)
- **Stack:** *64-bit linux VM ([Rainfall.iso](https://cdn.intra.42.fr/isos/Rainfall.iso))*

<br>

- [[Rainfall]](#42-cursus---Rainfall)
	- [[Details]](#details)
	- [[Overview]](#overview)
	- [[Objectives]](#objectives)


<br><br>

## Overview

The goal of the project is to get to the `end` user.<br>
There are 10 levels, from `level0` to `level9`. For each one, there's a `levelX` user having some vulnerable ressources to get the password of the next level and a `.pass` file containing its own password. The `.pass` files are obviously protected and we need to find a way to get them.<br>
That's all for the mandatory part. The project contains a bonus part that extends the challenge with 4 additional flags (`bonus0` to `bonus3` and the corresponding `flag10` to `flag13`).

How to start:
1. Download the RainFall.iso VM from the 42 intra.
2. Boot the VM (using QEMU, VirtualBox or any other emulator).
3. Connect to the VM using SSH (default credentials: `level0:level0`).
```bash
ssh -p 4242 level0@<machine_ip>
```

4. You can simplify your work by adding the host:
```bash
sudo sed -i '/rainfall/d; $a <machine_ip> rainfall' /etc/hosts
```
> ```bash
> ssh -p 4242 level0@rainfall
> ```
> ```bash
> scp -P 4242 level0@rainfall:/home/user/level0/level0 ./level0
> ```
To clean up the `/etc/hosts` file, you can use the following command:
```bash
sudo sed -i '/rainfall/d' /etc/hosts
```


<br><br>

## Objectives

#### Mandatory

- [x] 1. [level0](./level0/walkthrough.md) ([Flag](./level0/flag))
- [ ] 2. level1
- [ ] 3. level2
- [ ] 4. level3
- [ ] 5. level4
- [ ] 6. level5
- [ ] 7. level6
- [ ] 8. level7
- [ ] 9. level8
- [ ] 10. level9

#### Bonus

- [ ] 11. bonus0
- [ ] 12. bonus1
- [ ] 13. bonus2
- [ ] 14. bonus3

<br><br>

---

<sup><i>This is an educational project proposed by 42 School through the 42Cursus program.</i><sup>

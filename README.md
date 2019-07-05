ps3sdk on docker
----------------

ps3toolchain + psl1ght v2 in one docker image

To build the ps3dev sdk i used docker psl1ght/psl1ght

## Libraries included

- SDK [base](https://github.com/wargio/ps3sdk-docker/tree/base)
	- [ps3toolchain](https://github.com/ps3dev/ps3toolchain)
	- [PSL1GHT](https://github.com/ps3dev/PSL1GHT) version v2
	- [ps3libraries](https://github.com/ps3dev/ps3libraries)

- SDK [complete](https://github.com/wargio/ps3sdk-docker/tree/master)
	- base SDK
	- [RSXGL](https://github.com/gzorin/RSXGL)
	- [e17](https://github.com/kakaroto/e17)
	- [libmove](https://github.com/wargio/libmove)
	- [tiny3D](https://github.com/wargio/tiny3D) version v2
	- [ps3soundlib](https://github.com/wargio/ps3soundlib) version v2

## How to build SDK base:

```bash
git clone --single-branch --branch base --depth=1 https://github.com/wargio/ps3sdk-docker.git
docker build --rm . -t ps3sdk:base
```

## How to build SDK complete:

```bash
git clone --single-branch --branch master --depth=1 https://github.com/wargio/ps3sdk-docker.git
docker build --rm . -t ps3sdk:complete
```

## Issues with libiberty.a being x86_x64

I had to rebuild the `libiberty.a` because it was `x86_x64` instead of `powerpc64`.

Both SDK contains the correct version of it.


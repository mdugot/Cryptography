# Cryptography

Implementation in C of the following cryptologic algorithms :

 * rsa
 * rabin-karp
 * luhn
 * [md5](https://github.com/mdugot/Cryptography/tree/master#md5)
 * sha256
 * base64
 * des
 * des-ecb
 * des-cbc

# Requirements

* ### C Compiler
Need to compile the C source code.

 * ### CMake
*tested with version 3.19* <br/>
[CMake](https://cmake.org/) is used to make the binary.

# Installation

Install the requirements, clone the repository move at the root of the repository and run `build.sh` to make the binary:

```
$> git clone https://github.com/mdugot/Cryptography.git
$> cd Cryptography
$> ./build.sh
```
It should have created the binary `build/crypto`.

# Usage

## MD5

[MD5](https://tools.ietf.org/html/rfc1321) is cryptologic hash function hashing a message of any length into an almost unique 128 bits code. </br>
Use the command `./build/crypto md5 [OPTION] [FILE ...]` to get the hash of one or several files. </br>
If no files are given in argument, the user stdin inputs will be hashed. </br>
The command accept the following options :
 * `-b` output binary hash instead of hexadecimal value
 * `-s [STRING]` hash the string passed as argument
 * `-q` quiet mode
 * `-p` print stdin
 * `-r` reverse output

### Example

```
$> echo -n qwer > /tmp/f1
$> echo -n asdf > /tmp/f2
$> echo -n zxcv > /tmp/f3

$> ./build/crypto md5 /tmp/f1 /tmp/f2 /tmp/f3
MD5 (/tmp/f1) = 962012d09b8170d912f0669f6d7d9d07
MD5 (/tmp/f2) = 912ec803b2ce49e4a541068d495ab570
MD5 (/tmp/f3) = fd2cc6c54239c40495a0d3a93b6380eb

$> ./build/crypto md5 -s qwer
MD5 ("qwer") = 962012d09b8170d912f0669f6d7d9d07

$> ./build/crypto md5 -b /tmp/f2 > /tmp/dump
$> hexdump /tmp/dump
0000000 2e91 03c8 ceb2 e449 41a5 8d06 5a49 70b5
0000010

$> ./build/crypto md5 -q /tmp/f3
fd2cc6c54239c40495a0d3a93b6380eb
```

## SHA256

[SHA256](http://www.iwar.org.uk/comsec/resources/cipher/sha256-384-512.pdf) is cryptologic hash function hashing a message of any length into an almost unique 256 bits code. </br>
Use the command `./build/crypto sha256 [OPTION] [FILE ...]` to get the hash of one or several files. </br>
If no files are given in argument, the user stdin inputs will be hashed. </br>
The command accept the following options :
 * `-b` output binary hash instead of hexadecimal value
 * `-s [STRING]` hash the string passed as argument
 * `-q` quiet mode
 * `-p` print stdin
 * `-r` reverse output
 * `-c` split each byte of the output with colons

### Example

```
$> echo -n qwer > /tmp/f1
$> echo -n asdf > /tmp/f2
$> echo -n zxcv > /tmp/f3

$> ./build/crypto sha256 /tmp/f1 /tmp/f2 /tmp/f3
SHA256 (/tmp/f1) = f6f2ea8f45d8a057c9566a33f99474da2e5c6a6604d736121650e2730c6fb0a3
SHA256 (/tmp/f2) = f0e4c2f76c58916ec258f246851bea091d14d4247a2fc3e18694461b1816e13b
SHA256 (/tmp/f3) = 7020e57625b6a6695ffd51ed494fbfc56c699eaceca4e77bf7ea590c7ebf3879

$> ./build/crypto sha256 -s qwer
SHA256 ("qwer") = f6f2ea8f45d8a057c9566a33f99474da2e5c6a6604d736121650e2730c6fb0a3

$> ./build/crypto sha256 -b /tmp/f2 > /tmp/dump
$> hexdump /tmp/dump
0000000 e4f0 f7c2 586c 6e91 58c2 46f2 1b85 09ea
0000010 141d 24d4 2f7a e1c3 9486 1b46 1618 3be1
0000020

$> ./build/crypto sha256 -c /tmp/f3
SHA256 (/tmp/f3) = 70:20:e5:76:25:b6:a6:69:5f:fd:51:ed:49:4f:bf:c5:6c:69:9e:ac:ec:a4:e7:7b:f7:ea:59:0c:7e:bf:38:79
```


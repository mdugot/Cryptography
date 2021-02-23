# Cryptography

Implementation in C of the following cryptologic algorithms :

 * [rsa](https://github.com/mdugot/Cryptography/blob/master/README.md#rsa)
 * rabin-karp
 * luhn
 * [md5](https://github.com/mdugot/Cryptography/tree/master#md5)
 * [sha256](https://github.com/mdugot/Cryptography/blob/master/README.md#sha256)
 * base64
 * [des](https://github.com/mdugot/Cryptography/blob/master/README.md#des)
 * [des-ecb](https://github.com/mdugot/Cryptography/blob/master/README.md#des)
 * [des-cbc](https://github.com/mdugot/Cryptography/blob/master/README.md#des)

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

## RSA

[RSA](https://en.wikipedia.org/wiki/RSA_(cryptosystem)) is an asymetric key cryptosystem allowing to generate a pair of private and public key based on prime numbers. The public key can then be dstributed and use to encrypt data (often symetric key that can be used for authentification) that can only be decrypted with the private key. This implementation of RSA is limited to 64bits keys that can only encode 32 bits of data.

Use the command `./build/crypto genrsa [OPTION]` to generate the private key. It allows the following options :
 * `-o FILE` file where to save the key, print the key on the stdout by default
 * `-rand FILE` file use to generate prime numbers, use `/dev/urandom` by default

Use the command `./build/crypto rsa [OPTION]` to analyse and convert a rsa key. It allows the following options :
 * `-in FILE` file containing the input key, use stdin by default
 * `-out FILE` where to write the output key, use stdout by default
 * `-inform (PEM|DER)` format of the input key, choose between PEM and DER, PEM by default
 * `-outform (PEM|DER)` format of the output key, choose between PEM and DER, PEM by default
 * `-text` print information about the input key
 * `-modulus` print the modulus of the input key
 * `-check` check if the input key is valid, only private keys can be checked
 * `-pubin` input a public key, expect a private key by default
 * `-pubout` output a public key, output a private key by default
 * `-noout` do not output a key
 * `-des` encode the output key with [DES](https://github.com/mdugot/Cryptography/blob/master/README.md#des)
 * `-passout` password when encoding the output key with DES, by default a prompt will ask the user a passwor 
 * `-passin` password to decode a DES input key, by default a prompt will ask the user a passwor 

Use the command `./build/crypto rsautl [OPTION]` to encrypt data with a public key and decrypt them with a private key. It allows the following options.
 * `-in FILE` input file to encrypt or decrypt, stdin by default
 * `-out FILE` output file, stdout by default
 * `-inkey FILE` file containing the RSA key
 * `-pubin` use a public key for encrypting the data (can not be use for decrypting), private key by default
 * `-decrypt` decrypt mode, encrypt by default
 * `-hexdump` print hexadecimal value of the data

### Example

```
$> printf '%d' {1..1000} > /tmp/myrand
$> ./build/crypto genrsa -o /tmp/private -rand /tmp/myrand
.++++++++++++
.++++++++++++
e is 65537 (0x10001)
$> ./build/crypto rsa -in /tmp/private -noout -text
Private-Key: (64 bit)
modulus: 875986723 (0x34367f23)
public_exponent: 65537 (0x10001)
private_exponent: 754002833 (0x2cf12b91)
prime1: 18587 (0x489b)
prime2: 47129 (0xb819)
exponent1: 5985 (0x1761)
exponent2: 1961 (0x7a9)
coefficient: 9722 (0x25fa)
$> ./build/crypto rsa -in /tmp/private -out /tmp/public -pubout
$> echo 42 > /tmp/auth
$> ./build/crypto rsautl -pubin -inkey /tmp/public  -in /tmp/auth -out /tmp/secret
$> cat /tmp/secret
~0
$> ./build/crypto rsautl -decrypt -inkey /tmp/private  -in /tmp/secret
42
```


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
 * `-s STRING` hash the string passed as argument
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

## DES

[DES](http://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm) is a cypher algorithm used to encrypt or decrypt a message. </br>
Use the command `./build/crypto sha256 [OPTION] -i [INPUT FILE] -o [OUTPUT FILE]` to encrypt a file. </br>
Use the command `./build/crypto sha256 -d [OPTION] -i [INPUT FILE] -o [OUTPUT FILE]` to decrypt a file. </br>
The algorithm need a key and an initialization vector. They can be directly given with the option `-k` and `-v` or generated from a password given with the option `-p`.
The command accept the following options :
 * `-i FILENAME` input file, if not present, use stdin
 * `-o FILENAME` output file, if not present, use stdout
 * `-d` decrypt mode
 * `-k KEY` 64 bits value in hexadecimal corresponding to the key
 * `-v IV` 64 bits value in hexadecimal corresponding to the initialization vector
 * `-p PASSWORD` password, if neither the passord nor the key are given, a prompt will ask the password to the user
 * `-s SALT` 64 bits value in hexadecimal used to salt the password
 * `-a` base 64 mode

### Example

```
$> echo "Never interrupt your enemy when he is making a mistake." > /tmp/msg
$> ./build/crypto des -p josephine -i /tmp/msg | ./build/crypto des -d -p josephine
Never interrupt your enemy when he is making a mistake.
$> ./build/crypto des -p josephine -i /tmp/msg | ./build/crypto des -d -p marielouise
/v^H:htJ@ɹ1h?k05>WC...

$> ./build/crypto des -k FEEDBEEF -v CAFEFACE -i /tmp/msg | ./build/crypto des -d  -k FEEDBEEF -v CAFEFACE
Never interrupt your enemy when he is making a mistake.
$> ./build/crypto des -k FEEDBEEF -v CAFEFACE -i /tmp/msg | ./build/crypto des -d  -k FEEDBEE7 -v CAFEFACE
q7<Gj&,7T CB>=|...
```


## DES-ECB

Same than the [des command](https://github.com/mdugot/Cryptography/blob/master/README.md#des).


## DES-CBC

Variation of the DES  algorithm where each block processed by the cypher is dependant of the all message.
Same usage than the [des command](https://github.com/mdugot/Cryptography/blob/master/README.md#des).

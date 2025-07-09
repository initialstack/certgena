# Certificate Generator

A C++ tool for generating Certificate Authority (CA) keys, certificates, Diffie-Hellman parameters, and service certificates for nginx, redis, rabbitmq, and postgres using OpenSSL.

## Features

- Generates a root CA private key and self-signed certificate
- Creates RSA private keys for various services
- Generates X.509 certificates signed by the CA
- Generates Diffie-Hellman parameters for secure key exchange
- Supports custom OpenSSL configuration files
- Uses a modular design with command execution abstraction

## Requirements

- C++17 compatible compiler (e.g., `g++`)
- OpenSSL installed and available in system PATH
- CMake or GNU Make (optional for building)

## Building

Clone the repository and build using the provided Makefile:

```
$ git clone https://github.com/initialstack/certgen.git
$ cd certgen
$ make
```


This will produce the executable `certgen`.

## Usage

Run the program from the command line:

```
$ ./certgen
```

To see help:

```
$ ./certgen -h
```

## License

This project is licensed under the [MIT License](https://opensource.org/licenses/MIT).

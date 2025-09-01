# file-encryptor-c

### for mac, adapted from linux examples

RC4-based file encrypter written in C.  
It prompts for a key, then streams `infile → outfile` through RC4.

---

## Credit to DR. Jonas Birch for ArcFour

- RC4 implementation (`arcfour.c/.h`) made by **Dr. Jonas Birch**. Youtube at ` @dr-jonas-birch`.
  Please **refer to `LICENSE.txt`** in this repository for licensing terms, and see **Dr. Birch’s personal website** for more of his work.

---

## Features

- Streams in chunks (no need to load the whole file in RAM).
- macOS randomness via `arc4random_buf`.
- Simple CLI: `./fse <infile> <outfile>` then type a key.

---

## Repo layout

```
arcfour.c
arcfour.h          # RC4 implementation
fse.c              # CLI app (encrypts infile to outfile)
fse.h
LICENSE.txt
Makefile           # may build libarcfour.so only; see build notes below
```

---

## Build

### Quick build (no Makefile changes)

```sh
# 1) Build the RC4 object
gcc -O2 -Wall -c arcfour.c

# 2) Build the CLI and link against the object
gcc -O2 -Wall fse.c arcfour.o -o fse
```

### Optional: shared library (already in Makefile)

```sh
# Builds libarcfour.so (mostly useful on Linux)
make
```

> If your `make` only builds `libarcfour.so`, you still need to compile `fse` as shown above.  
> To wire it into Makefile, add a target like:
>
> ```make
> fse: fse.c arcfour.o
> 	$(CC) -O2 -Wall $^ -o $@
> ```

---

## Run

```sh
./fse infile outfile
Key: mysecretkey
```

- The program will prompt `Key:` on stdin.
- It reads `infile`, encrypts with RC4 using your key, and writes to `outfile`.
- To **decrypt**, run the same command again with the **same key** on the encrypted file.

---

## License

See `LICENSE.txt`.

---

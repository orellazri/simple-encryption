# 🔐 Simple Encryption
 Simple symmetric encryption program that lets you encrypt/decrypt messages (strings). Made in C++.

It first encodes the message as base64, then uses Vigenère cipher with a private key to encrypt it.

The decryption process is just the opposite. It first decrypts the Vigenère cipher with the given private key, and then decodes the decrypted contents with base64.

We encode with base64 before running Vigenère cipher to obfuscate characters that could give away the type of the message we want to encrypt. For example `{` and `}` characters in JSON, or `<` and `>` characters in XML. 

### Side notes
_This encryption is neither secure nor unbreakable. It's used as more of a way to quickly obfuscate your messages._

_It is recommended that the key will not be longer than the input._

## Compilation and execution
Compile in your preferred way, for example:
```bash
g++ main.cpp
```
And then run the output file from the command line.

The format is: `[e:Encrypt|d:Decrypt]` `[MESSAGE]` `[KEY]`

Linux:
```bash
./a.out e "This is a secret. Shh..." MyKeyIsPrivate
```

Windows:
```bash
a.exe e "This is a secret. Shh..." MyKeyIsPrivate
```

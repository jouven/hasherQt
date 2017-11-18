# hasherQt
Console application to generate hashes. Input: string/s, file/s. Output: decimal, hex and base64. Hash types: crc32c, xxhash, whirlpool and SHA256

Compilation
-----------
Requires:

Qt library

https://github.com/jouven/criptoQtso

https://github.com/jouven/baseClassQtso

https://github.com/jouven/essentialQtso

Run (in hasherQt source directory or pointing to it):

    qmake

and then:

    make

Command line usage
------------------

    hasherQt -h
    
File explorer usage
-------------------
Drag and drop the file/s into hasherQt, defaults to file input, hex output and xxhash hash

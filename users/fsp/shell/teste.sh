#!/bin/sh

palavra="bash"; if ! grep $palavra /etc/passwd > /dev/null; then echo "sem $palavra"; else echo "com $palavra"; fi

#!/bin/bash
./uccompiler $1 < ../Testes/input/$2.uc | diff -y ../Testes/input/$2.out -
#!/bin/bash

echo `grep -r docker test.txt |awk -F = '{print $1}'`
#!/bin/bash
p1=0
p2=0
for i in {1..100}
do
    eval '../bin/strategy --dev'
    if [ $? -eq 1 ]
        then
        ((p1++))
        else
        ((p2++))
    fi
done
echo 'player1 victories : '$p1
echo 'player2 victories : '$p2

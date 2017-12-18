#!/bin/bash

ln -sf input1 input 
AppCpp > output
diff output output1

ln -sf input2 input 
AppCpp > output
diff output output2

ln -sf input3 input 
AppCpp > output
diff output output3

ln -sf input4 input 
AppCpp > output
diff output output4

ln -sf input5 input 
AppCpp > output
diff output output5

ln -sf input6 input 
AppCpp > output
diff output output6

ln -sf input7 input 
AppCpp > output
diff output output7

ln -sf input8 input 
AppCpp > output
diff output output8

ln -sf input9 input 
AppCpp > output
diff output output9

ln -sf input.me input 
AppCpp > output
diff output output.me

rm input
echo "no difference means passing"

import copy
print ("\033c\033[40;37m\n")

ss="""8086 X86
80186 X86
80286 X86
80386 X86
80486 X86
ARM7 ARM
ARM8 ARM"""

def uppers(s):
    ss=""
    for a in s:
         if ord(a)<=ord('Z') and ord(a)>=ord('A'):
             aa=ord(a)+32
             ss=ss+chr(aa)
         else:
             ss=ss+a
         
    return ss
l=uppers(ss)
print(l)